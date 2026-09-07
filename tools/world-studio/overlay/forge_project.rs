// SPDX-License-Identifier: GPL-3.0-or-later
// External static-instance projects. This module never writes Destiny packages.
use std::{
    collections::{BTreeMap, BTreeSet},
    fs::{self, OpenOptions},
    io::{Read, Write},
    path::Path,
    sync::atomic::{AtomicU64, Ordering},
};

use alkahest_pm::package_manager;
use alkahest_renderer::ecs::{
    common::{Hidden, Label},
    hierarchy::Parent,
    render::{static_geometry::StaticInstanceSource, update_entity_transform},
    transform::{OriginalTransform, Transform},
    Scene, SceneInfo,
};
use anyhow::{ensure, Context};
use destiny_pkg::TagHash;
use glam::{Quat, Vec3};
use hecs::Entity;
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};

const FORMAT: &str = "izanami.external-static-project";
const MAX_BYTES: u64 = 64 * 1024 * 1024;
static SAVE_SERIAL: AtomicU64 = AtomicU64::new(0);

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
#[serde(deny_unknown_fields)]
pub struct Pose {
    pub position: [f32; 3],
    pub rotation_xyzw: [f32; 4],
    pub scale: [f32; 3],
}

impl From<Transform> for Pose {
    fn from(t: Transform) -> Self {
        Self {
            position: t.translation.to_array(),
            rotation_xyzw: t.rotation.to_array(),
            scale: t.scale.to_array(),
        }
    }
}

impl Pose {
    fn validate(&self) -> anyhow::Result<()> {
        ensure!(
            self.position
                .iter()
                .chain(&self.rotation_xyzw)
                .chain(&self.scale)
                .all(|v| v.is_finite()),
            "Non-finite transform"
        );
        ensure!(
            self.position.iter().all(|v| v.abs() <= 1.0e7),
            "Position out of range"
        );
        ensure!(
            self.scale
                .iter()
                .all(|v| v.abs() >= 1.0e-5 && v.abs() <= 1.0e5),
            "Singular or excessive scale"
        );
        let length = Quat::from_array(self.rotation_xyzw).length();
        ensure!(
            (length - 1.0).abs() < 0.01,
            "Rotation must be a unit quaternion"
        );
        Ok(())
    }

    fn transform(&self) -> Transform {
        Transform::new(
            Vec3::from_array(self.position),
            Quat::from_array(self.rotation_xyzw),
            Vec3::from_array(self.scale),
        )
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct InstanceEdit {
    pub source: String,
    pub mesh_tag: String,
    pub table_tag: String,
    pub instances_tag: String,
    pub transform_index: u32,
    pub original: Pose,
    pub edited: Pose,
    pub hidden: bool,
    pub name: String,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Project {
    pub format: String,
    pub version: u32,
    pub game_schema: String,
    pub map_tag: String,
    pub activity_tag: Option<String>,
    // Hashes cover source descriptors/placements, not the transitive material/texture graph.
    pub source_sha256: BTreeMap<String, String>,
    pub instances: Vec<InstanceEdit>,
}

fn hex_tag(tag: TagHash) -> String {
    format!("{:08X}", tag.0)
}

fn index(scene: &Scene) -> anyhow::Result<BTreeMap<String, Entity>> {
    let mut result = BTreeMap::new();
    for (entity, source) in scene.query::<&StaticInstanceSource>().iter() {
        ensure!(
            result.insert(source.key(), entity).is_none(),
            "Ambiguous repeated source {}; project disabled for this scene",
            source.key()
        );
    }
    Ok(result)
}

fn snapshot(scene: &Scene) -> anyhow::Result<Project> {
    let mut instances = Vec::new();
    for (source, entity) in index(scene)? {
        let record = scene.get::<&StaticInstanceSource>(entity)?;
        let current = *scene.get::<&Transform>(entity)?;
        let original = scene.get::<&OriginalTransform>(entity)?.0;
        let hidden = scene.get::<&Hidden>(entity).is_ok()
            || scene
                .get::<&Parent>(entity)
                .ok()
                .is_some_and(|p| scene.get::<&Hidden>(p.0).is_ok());
        instances.push(InstanceEdit {
            source,
            mesh_tag: hex_tag(record.mesh_tag),
            table_tag: hex_tag(record.table_tag),
            instances_tag: hex_tag(record.instances_tag),
            transform_index: record.transform_index,
            original: original.into(),
            edited: current.into(),
            hidden,
            name: scene
                .get::<&Label>(entity)
                .map(|l| l.label.clone())
                .unwrap_or_default(),
        });
    }
    ensure!(
        !instances.is_empty(),
        "No source-backed static instances in the loaded map"
    );
    Ok(Project {
        format: FORMAT.into(),
        version: 1,
        game_schema: "Destiny2Shadowkeep".into(),
        map_tag: hex_tag(scene.get_map_hash().context("No loaded map")?),
        activity_tag: scene.get_activity_hash().map(hex_tag),
        source_sha256: BTreeMap::new(),
        instances,
    })
}

pub fn capture(scene: &Scene) -> anyhow::Result<Project> {
    let mut project = snapshot(scene)?;
    let mut tags = BTreeSet::new();
    tags.insert(scene.get_map_hash().context("No loaded map")?.0);
    if let Some(activity) = scene.get_activity_hash() {
        tags.insert(activity.0);
    }
    for (_, record) in scene.query::<&StaticInstanceSource>().iter() {
        for tag in [
            record.table_tag,
            record.preheader_tag,
            record.instances_tag,
            record.mesh_tag,
        ] {
            tags.insert(tag.0);
        }
    }
    for tag in tags {
        let bytes = package_manager()
            .read_tag(TagHash(tag))
            .with_context(|| format!("Fingerprint source {tag:08X}"))?;
        project
            .source_sha256
            .insert(format!("{tag:08X}"), format!("{:x}", Sha256::digest(bytes)));
    }
    project.validate()?;
    Ok(project)
}

impl Project {
    fn validate(&self) -> anyhow::Result<()> {
        ensure!(
            self.format == FORMAT && self.version == 1 && self.game_schema == "Destiny2Shadowkeep",
            "Unsupported project format/schema"
        );
        ensure!(
            !self.instances.is_empty() && self.instances.len() <= 250_000,
            "Invalid static instance count"
        );
        ensure!(
            !self.source_sha256.is_empty(),
            "Project has no source fingerprints"
        );
        let mut keys = BTreeSet::new();
        for edit in &self.instances {
            ensure!(
                keys.insert(&edit.source),
                "Duplicate source {}",
                edit.source
            );
            ensure!(
                edit.source.len() <= 256 && edit.name.len() <= 1024,
                "Oversized record"
            );
            edit.original.validate()?;
            edit.edited.validate()?;
        }
        Ok(())
    }

    fn validate_against(&self, current: &Self) -> anyhow::Result<()> {
        self.validate()?;
        current.validate()?;
        ensure!(
            self.map_tag == current.map_tag && self.activity_tag == current.activity_tag,
            "Load the project's original map and activity first"
        );
        ensure!(
            self.source_sha256 == current.source_sha256,
            "Source package records have changed; no edits applied"
        );
        ensure!(
            self.instances.len() == current.instances.len(),
            "Source instance count changed"
        );
        let originals: BTreeMap<_, _> = current.instances.iter().map(|v| (&v.source, v)).collect();
        for edit in &self.instances {
            let original = originals
                .get(&edit.source)
                .context("Source instance missing")?;
            ensure!(
                edit.original == original.original
                    && edit.mesh_tag == original.mesh_tag
                    && edit.table_tag == original.table_tag
                    && edit.instances_tag == original.instances_tag
                    && edit.transform_index == original.transform_index,
                "Source identity/transform changed: {}",
                edit.source
            );
        }
        Ok(())
    }

    pub fn apply(&self, scene: &mut Scene) -> anyhow::Result<usize> {
        let current = capture(scene)?;
        self.apply_checked(scene, &current)
    }

    fn apply_checked(&self, scene: &mut Scene, current: &Self) -> anyhow::Result<usize> {
        self.validate_against(current)?;
        let entities = index(scene)?;
        // Preflight the complete batch before touching any transform or visibility state.
        for edit in &self.instances {
            let entity = *entities
                .get(&edit.source)
                .context("Source instance missing")?;
            scene.get::<&Transform>(entity)?;
        }
        for edit in &self.instances {
            let entity = entities[&edit.source];
            let flags = scene.get::<&Transform>(entity)?.flags;
            let mut transform = edit.edited.transform();
            transform.flags = flags;
            *scene.get::<&mut Transform>(entity)? = transform;
            let parent = scene.get::<&Parent>(entity).ok().map(|p| p.0);
            // A collection's hidden state is flattened into its individual instances in projects.
            if let Some(parent) = parent {
                scene.remove_one::<Hidden>(parent).ok();
            }
            if edit.hidden {
                scene.insert_one(entity, Hidden)?;
            } else {
                scene.remove_one::<Hidden>(entity).ok();
            }
            scene.insert_one(entity, Label::from(edit.name.clone()))?;
            update_entity_transform(scene, entity);
        }
        Ok(self.instances.len())
    }

    pub fn read(path: &Path) -> anyhow::Result<Self> {
        let file = fs::File::open(path)?;
        ensure!(
            file.metadata()?.len() <= MAX_BYTES,
            "Project exceeds 64 MiB"
        );
        let mut bytes = Vec::new();
        file.take(MAX_BYTES + 1).read_to_end(&mut bytes)?;
        ensure!(bytes.len() as u64 <= MAX_BYTES, "Project exceeds 64 MiB");
        let project: Self = serde_json::from_slice(&bytes)?;
        project.validate()?;
        Ok(project)
    }

    pub fn save(&self, path: &Path) -> anyhow::Result<()> {
        self.validate()?;
        ensure!(
            path.extension()
                .is_some_and(|e| e.eq_ignore_ascii_case("json")),
            "External projects must use a .json extension"
        );
        let bytes = serde_json::to_vec_pretty(self)?;
        ensure!(bytes.len() as u64 <= MAX_BYTES, "Project exceeds 64 MiB");
        let serial = SAVE_SERIAL.fetch_add(1, Ordering::Relaxed);
        let name = path
            .file_name()
            .context("Missing project filename")?
            .to_string_lossy();
        let temp = path.with_file_name(format!(".{name}.{}.{serial}.tmp", std::process::id()));
        let mut file = OpenOptions::new()
            .write(true)
            .create_new(true)
            .open(&temp)?;
        let result = (|| -> anyhow::Result<()> {
            file.write_all(&bytes)?;
            file.sync_all()?;
            drop(file);
            fs::rename(&temp, path)
                .context("Could not replace project; previous file preserved")?;
            Ok(())
        })();
        if result.is_err() {
            fs::remove_file(&temp).ok();
        }
        result
    }
}

pub fn restore(scene: &mut Scene) -> anyhow::Result<usize> {
    let mut original = capture(scene)?;
    for edit in &mut original.instances {
        edit.edited = edit.original.clone();
        edit.hidden = false;
    }
    original.apply(scene)
}

pub async fn audit(
    map: TagHash,
    activity: Option<TagHash>,
    output: &Path,
    preview_mesh: Option<TagHash>,
) -> anyhow::Result<()> {
    use alkahest_data::text::StringContainer;
    use alkahest_renderer::{gpu::GpuContext, loaders::map::load_map, renderer::Renderer};
    use std::sync::Arc;
    let gpu = Arc::new(GpuContext::create_headless()?);
    let renderer = Renderer::create(gpu, (960, 640), false)?;
    let mut scene = load_map(
        renderer.clone(),
        map,
        activity,
        Arc::new(StringContainer::default()),
        false,
    )
    .await?;
    let original = capture(&scene)?;
    original.save(output)?;
    let mut edited = original.clone();
    edited.instances[0].edited.position[0] += 3.0;
    edited.instances[0].edited.scale[1] *= 2.0;
    edited.instances[0].hidden = true;
    edited.apply(&mut scene)?;
    let changed = snapshot(&scene)?;
    ensure!(
        changed.instances[0].edited == edited.instances[0].edited && changed.instances[0].hidden,
        "Edit roundtrip failed"
    );
    original.apply(&mut scene)?;
    let restored = snapshot(&scene)?;
    ensure!(
        restored.instances[0].edited == original.instances[0].edited
            && restored.instances[0].hidden == original.instances[0].hidden,
        "Restore failed"
    );
    crate::forge_preview::verify(&renderer, &mut scene, output, preview_mesh)?;
    println!(
        "FORGE_AUDIT_OK map={:08X} static_instances={} source_records={} output={}",
        map.0,
        original.instances.len(),
        original.source_sha256.len(),
        output.display()
    );
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    fn scene() -> Scene {
        let mut scene = Scene::new_with_info(None, TagHash(0x8150E00A));
        for n in 0..2 {
            let transform = Transform::default();
            scene.spawn((
                StaticInstanceSource {
                    table_tag: TagHash(0x8150E15B),
                    resource_offset: 160,
                    world_id: 0,
                    preheader_tag: TagHash(0x8150E15A),
                    instances_tag: TagHash(0x8150E159),
                    group_index: 0,
                    transform_index: n,
                    mesh_tag: TagHash(0x8150E158),
                },
                transform,
                OriginalTransform(transform),
                Label::from("Static Instance"),
            ));
        }
        scene
    }

    fn project(scene: &Scene) -> Project {
        let mut p = snapshot(scene).unwrap();
        p.source_sha256
            .insert("8150E15B".into(), "test-fingerprint".into());
        p
    }

    #[test]
    fn transforms_and_visibility_roundtrip() {
        let mut scene = scene();
        let baseline = project(&scene);
        let mut edited = baseline.clone();
        edited.instances[0].edited.position = [10.0, 20.0, 30.0];
        edited.instances[0].edited.scale = [1.0, 2.0, 3.0];
        edited.instances[0].edited.rotation_xyzw = Quat::from_rotation_z(0.5).to_array();
        edited.instances[0].hidden = true;
        edited.instances[0].name = "Baseplate".into();
        let decoded: Project =
            serde_json::from_slice(&serde_json::to_vec(&edited).unwrap()).unwrap();
        decoded.apply_checked(&mut scene, &baseline).unwrap();
        let result = project(&scene);
        assert_eq!(result.instances[0].edited, edited.instances[0].edited);
        assert_eq!(result.instances[0].name, "Baseplate");
        assert!(result.instances[0].hidden);
        assert_eq!(result.instances[1].edited, baseline.instances[1].edited);
        baseline.apply_checked(&mut scene, &result).unwrap();
        assert_eq!(
            project(&scene).instances[0].edited,
            baseline.instances[0].edited
        );
        assert!(!project(&scene).instances[0].hidden);
    }

    #[test]
    fn invalid_batch_never_partially_applies() {
        let mut scene = scene();
        let baseline = project(&scene);
        let mut edited = baseline.clone();
        edited.instances[0].edited.position[0] = 42.0;
        edited.instances[1].edited.scale[2] = 0.0;
        assert!(edited.apply_checked(&mut scene, &baseline).is_err());
        assert_eq!(
            project(&scene).instances[0].edited,
            baseline.instances[0].edited
        );
    }

    #[test]
    fn rejects_wrong_world_changed_sources_duplicates_and_unknown_version() {
        let scene = scene();
        let baseline = project(&scene);
        let mut p = baseline.clone();
        p.map_tag = "DEADBEEF".into();
        assert!(p.validate_against(&baseline).is_err());
        p = baseline.clone();
        p.source_sha256.clear();
        assert!(p.validate_against(&baseline).is_err());
        p = baseline.clone();
        p.instances[1].source = p.instances[0].source.clone();
        assert!(p.validate_against(&baseline).is_err());
        p = baseline.clone();
        p.version = 2;
        assert!(p.validate_against(&baseline).is_err());
        p = baseline.clone();
        p.instances[0].original.position[1] = 0.1;
        assert!(p.validate_against(&baseline).is_err());
    }

    #[test]
    fn rejects_ambiguous_scene_and_non_finite_transform() {
        let mut scene = scene();
        let source = *scene
            .query::<&StaticInstanceSource>()
            .iter()
            .next()
            .unwrap()
            .1;
        scene.spawn((source,));
        assert!(snapshot(&scene).is_err());
        let mut pose: Pose = Transform::default().into();
        pose.position[2] = f32::NAN;
        assert!(pose.validate().is_err());
        pose = Transform::default().into();
        pose.rotation_xyzw = [0.0; 4];
        assert!(pose.validate().is_err());
    }

    #[test]
    fn preserves_native_quaternion_without_rounding_drift() {
        let mut scene = scene();
        let entity = index(&scene).unwrap().values().next().copied().unwrap();
        let rotation = Quat::from_xyzw(-0.88957083, -0.4186915, 0.06683909, 0.16998136);
        scene.get::<&mut Transform>(entity).unwrap().rotation = rotation;
        let before = project(&scene);
        before.apply_checked(&mut scene, &before).unwrap();
        assert_eq!(scene.get::<&Transform>(entity).unwrap().rotation, rotation);
    }

    #[test]
    fn saves_replace_and_reopen_without_build_directory_dependency() {
        let path =
            std::env::temp_dir().join(format!("forge-project-test-{}.json", std::process::id()));
        let mut p = project(&scene());
        p.save(&path).unwrap();
        p.instances[0].name = "Persistent baseplate".into();
        p.save(&path).unwrap();
        assert_eq!(
            Project::read(&path).unwrap().instances[0].name,
            "Persistent baseplate"
        );
        p.instances[0].edited.scale[0] = 0.0;
        assert!(p.save(&path).is_err());
        assert_eq!(
            Project::read(&path).unwrap().instances[0].name,
            "Persistent baseplate"
        );
        fs::remove_file(path).unwrap();
    }
}
