// SPDX-License-Identifier: GPL-3.0-or-later
// Offscreen verification uses the same renderer and static instance buffers as the editor.
use alkahest_data::dxgi::DxgiFormat;
use alkahest_renderer::{
    camera::{Camera, Viewport},
    ecs::{
        common::Hidden,
        hierarchy::Parent,
        render::{
            static_geometry::{StaticInstanceSource, StaticInstances},
            update_entity_transform,
        },
        resources::SelectedEntity,
        tags::NodeFilterSet,
        transform::Transform,
        Scene,
    },
    renderer::{
        gbuffer::{CpuStagingBuffer, RenderTarget},
        RenderDebugView, RenderFeatureVisibility, RendererSettings, RendererShared,
    },
    resources::Resources,
};
use anyhow::{ensure, Context};
use destiny_pkg::TagHash;
use glam::{UVec2, Vec3};
use std::{
    fs::File,
    path::Path,
    thread,
    time::{Duration, Instant},
};
use windows::Win32::Graphics::Direct3D11::D3D11_MAP_READ;

pub fn verify(
    renderer: &RendererShared,
    scene: &mut Scene,
    output: &Path,
    mesh: Option<TagHash>,
) -> anyhow::Result<()> {
    let deadline = Instant::now() + Duration::from_secs(90);
    loop {
        let mut data = renderer.data.lock();
        data.asset_manager.poll();
        if data.asset_manager.is_idle() {
            break;
        }
        ensure!(
            Instant::now() < deadline,
            "Asset loading exceeded 90 seconds"
        );
        drop(data);
        thread::sleep(Duration::from_millis(10));
    }
    let target = scene
        .query::<(&StaticInstanceSource, &Transform)>()
        .iter()
        .filter(|(_, (s, _))| mesh.is_none_or(|m| s.mesh_tag == m))
        .min_by(|a, b| {
            a.1 .1
                .translation
                .length_squared()
                .total_cmp(&b.1 .1.translation.length_squared())
        })
        .map(|(e, _)| e)
        .context("No matching static instance for preview")?;
    let transform = *scene.get::<&Transform>(target)?;
    let parent = scene.get::<&Parent>(target)?.0;
    let source = *scene.get::<&StaticInstanceSource>(target)?;
    let (center, radius) = {
        let group = scene.get::<&StaticInstances>(parent)?;
        (
            transform
                .local_to_world()
                .transform_point3(group.model.model.mesh_offset),
            (group.model.model.mesh_scale.abs() * transform.scale.abs().max_element()).max(1.0),
        )
    };
    let entities: Vec<_> = scene
        .query::<&StaticInstanceSource>()
        .iter()
        .map(|(e, _)| e)
        .collect();
    for entity in entities {
        if entity != target {
            scene.insert_one(entity, Hidden)?;
        }
    }
    scene.remove_one::<Hidden>(target).ok();
    scene.remove_one::<Hidden>(parent).ok();
    renderer.set_render_settings(RendererSettings {
        debug_view: RenderDebugView::SourceColor,
        feature_terrain: RenderFeatureVisibility::empty(),
        feature_dynamics: RenderFeatureVisibility::empty(),
        feature_sky: RenderFeatureVisibility::empty(),
        feature_decorators: RenderFeatureVisibility::empty(),
        feature_water: RenderFeatureVisibility::empty(),
        ..Default::default()
    });
    let mut camera = Camera::new_fps(Viewport {
        size: UVec2::new(960, 640),
        origin: UVec2::ZERO,
    });
    camera.set_position(center + Vec3::new(1.4, -1.8, 1.2) * radius);
    camera.set_orientation(camera.get_look_angle(center));
    camera.update_matrices();
    let target_buffer = RenderTarget::create(
        (960, 640),
        DxgiFormat::R8G8B8A8_UNORM,
        renderer.gpu.clone(),
        "Forge verification",
    )?;
    *renderer.gpu.swapchain_target.write() = Some(target_buffer.render_target.clone());
    let staging = CpuStagingBuffer::create(
        (960, 640),
        DxgiFormat::R8G8B8A8_UNORM,
        renderer.gpu.clone(),
        "Forge readback",
    )?;
    let mut resources = Resources::default();
    resources.insert(NodeFilterSet::default());
    resources.insert(SelectedEntity::default());
    let original = frame(
        renderer,
        scene,
        &camera,
        &resources,
        &target_buffer,
        &staging,
        &output.with_extension("original.png"),
    )?;
    scene.get::<&mut Transform>(target)?.scale.y *= 1.5;
    update_entity_transform(scene, target);
    let scaled = frame(
        renderer,
        scene,
        &camera,
        &resources,
        &target_buffer,
        &staging,
        &output.with_extension("scaled.png"),
    )?;
    scene.insert_one(target, Hidden)?;
    let hidden = frame(
        renderer,
        scene,
        &camera,
        &resources,
        &target_buffer,
        &staging,
        &output.with_extension("hidden.png"),
    )?;
    scene.remove_one::<Hidden>(target)?;
    *scene.get::<&mut Transform>(target)? = transform;
    update_entity_transform(scene, target);
    let restored = frame(
        renderer,
        scene,
        &camera,
        &resources,
        &target_buffer,
        &staging,
        &output.with_extension("restored.png"),
    )?;
    let changed = |a: &[u8], b: &[u8]| {
        a.chunks_exact(4)
            .zip(b.chunks_exact(4))
            .filter(|(x, y)| x[..3] != y[..3])
            .count()
    };
    let scale_pixels = changed(&original, &scaled);
    let visible_pixels = changed(&original, &hidden);
    let restore_pixels = changed(&original, &restored);
    ensure!(
        scale_pixels > 64 && visible_pixels > 64,
        "Blank/unchanged geometry render"
    );
    ensure!(
        restore_pixels == 0,
        "Restored render differs in {restore_pixels} pixels"
    );
    println!("FORGE_RENDER_OK source={} scaled_pixels={} visible_pixels={} restore_pixels={} center={center:?} radius={radius}",
        source.key(), scale_pixels, visible_pixels, restore_pixels);
    Ok(())
}

fn frame(
    renderer: &RendererShared,
    scene: &Scene,
    camera: &Camera,
    resources: &Resources,
    target: &RenderTarget,
    staging: &CpuStagingBuffer,
    path: &Path,
) -> anyhow::Result<Vec<u8>> {
    renderer.gpu.begin_frame();
    renderer.render_world(camera, scene, resources);
    target.copy_to_staging(staging);
    let rgba = staging.map(D3D11_MAP_READ, |mapped| {
        let mut pixels = Vec::with_capacity(960 * 640 * 4);
        for row in 0..640 {
            // D3D11 returns a padded row pitch; only copy the active RGBA pixels.
            let bytes = unsafe {
                std::slice::from_raw_parts(
                    (mapped.pData as *const u8).add(row * mapped.RowPitch as usize),
                    960 * 4,
                )
            };
            pixels.extend_from_slice(bytes);
        }
        pixels
    })?;
    let mut encoder = png::Encoder::new(File::create(path)?, 960, 640);
    encoder.set_color(png::ColorType::Rgba);
    encoder.set_depth(png::BitDepth::Eight);
    encoder.write_header()?.write_image_data(&rgba)?;
    Ok(rgba)
}
