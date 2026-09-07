// SPDX-License-Identifier: GPL-3.0-or-later
use super::MenuBar;
use crate::{
    forge_project::{self, Project},
    maplist::{MapList, MapLoadState},
    resources::Resources,
};
use alkahest_renderer::{
    ecs::render::static_geometry::StaticInstanceSource,
    icons::{
        ICON_CAMERA_CONTROL, ICON_CONTENT_SAVE, ICON_CUBE_OUTLINE, ICON_FOLDER_OPEN, ICON_RESTORE,
    },
};
use anyhow::Context;

impl MenuBar {
    pub(super) fn forge_menu(&mut self, ui: &mut egui::Ui, resources: &Resources) {
        if ui
            .button(format!("{ICON_CUBE_OUTLINE} Static geometry..."))
            .clicked()
        {
            self.forge_sources_open = true;
            ui.close_menu();
        }
        let ready = resources
            .get::<MapList>()
            .current_map()
            .is_some_and(|m| matches!(m.load_state, MapLoadState::Loaded));
        let mut action = 0;
        ui.add_enabled_ui(ready, |ui| {
            if ui
                .button(format!("{ICON_CONTENT_SAVE} Save static project..."))
                .clicked()
            {
                action = 1;
            }
            if ui
                .button(format!("{ICON_FOLDER_OPEN} Open static project..."))
                .clicked()
            {
                action = 2;
            }
            ui.menu_button(format!("{ICON_RESTORE} Restore source geometry"), |ui| {
                if ui
                    .button("Restore all static transforms and visibility")
                    .clicked()
                {
                    action = 3;
                }
            });
        });
        ui.separator();
        if let Some(map) = resources.get::<MapList>().current_map() {
            let count = map.scene.query::<&StaticInstanceSource>().iter().count();
            ui.label(format!("Static instances: {count}"));
            ui.monospace(format!("Native map ID: {:08X}", map.hash.0));
        }
        if !self.forge_status.is_empty() {
            ui.label(&self.forge_status);
        }
        if action == 0 {
            return;
        }
        let result = (|| -> anyhow::Result<String> {
            let mut maps = resources.get_mut::<MapList>();
            let map = maps.current_map_mut().context("No loaded map")?;
            // Make this click observe pending inspector/gizmo changes from the preceding frame.
            map.command_buffer.run_on(&mut map.scene);
            match action {
                1 => {
                    let filename = format!("{:08X}.forge.json", map.hash.0);
                    let Some(path) = native_dialog::FileDialog::new()
                        .add_filter("Forge static project", &["json"])
                        .set_filename(&filename)
                        .show_save_single_file()?
                    else {
                        return Ok("Save canceled".into());
                    };
                    let project = forge_project::capture(&map.scene)?;
                    project.save(&path)?;
                    Ok(format!(
                        "Saved {} instances: {}",
                        project.instances.len(),
                        path.display()
                    ))
                }
                2 => {
                    let Some(path) = native_dialog::FileDialog::new()
                        .add_filter("Forge static project", &["json"])
                        .show_open_single_file()?
                    else {
                        return Ok("Open canceled".into());
                    };
                    let count = Project::read(&path)?.apply(&mut map.scene)?;
                    Ok(format!("Applied {count} static instances"))
                }
                3 => Ok(format!(
                    "Restored {} static instances",
                    forge_project::restore(&mut map.scene)?
                )),
                _ => unreachable!(),
            }
        })();
        self.forge_status = match result {
            Ok(status) => {
                tracing::info!("{status}");
                status
            }
            Err(error) => {
                tracing::error!("Forge project: {error:#}");
                format!("Failed: {error:#}")
            }
        };
    }

    pub(super) fn forge_sources(&mut self, ctx: &egui::Context, resources: &Resources) {
        use alkahest_renderer::ecs::{
            common::Label, resources::SelectedEntity, transform::Transform,
        };
        let maps = resources.get::<MapList>();
        let Some(map) = maps.current_map() else {
            return;
        };
        egui::Window::new("Forge Static Geometry")
            .open(&mut self.forge_sources_open)
            .default_size([520.0, 420.0])
            .show(ctx, |ui| {
                ui.add(
                    egui::TextEdit::singleline(&mut self.forge_source_filter)
                        .hint_text("Search name, native mesh ID, table or transform"),
                );
                let query = self.forge_source_filter.to_ascii_lowercase();
                let mut rows: Vec<_> = map
                    .scene
                    .query::<(&StaticInstanceSource, &Transform)>()
                    .iter()
                    .filter_map(|(entity, (source, _))| {
                        let name = map
                            .scene
                            .get::<&Label>(entity)
                            .map(|l| l.label.clone())
                            .unwrap_or_default();
                        let key = source.key();
                        if !query.is_empty()
                            && !format!("{name} {key}")
                                .to_ascii_lowercase()
                                .contains(&query)
                        {
                            return None;
                        }
                        Some((
                            key,
                            entity,
                            format!("{:08X} / {}", source.mesh_tag.0, source.transform_index),
                            name,
                        ))
                    })
                    .collect();
                rows.sort_by(|a, b| a.0.cmp(&b.0));
                ui.horizontal(|ui| {
                    ui.label(format!("{} instances", rows.len()));
                    let selected = resources.get::<SelectedEntity>().selected();
                    if ui
                        .add_enabled(
                            selected.is_some(),
                            egui::Button::new(ICON_CAMERA_CONTROL.to_string()),
                        )
                        .on_hover_text("Frame selected static instance")
                        .clicked()
                    {
                        if let Some(entity) = selected {
                            frame_static(&map.scene, entity, resources);
                        }
                    }
                });
                ui.separator();
                egui::ScrollArea::vertical()
                    .auto_shrink([false, false])
                    .show_rows(ui, 24.0, rows.len(), |ui, range| {
                        for row in &rows[range] {
                            let selected =
                                resources.get::<SelectedEntity>().selected() == Some(row.1);
                            let clicked = ui
                                .selectable_label(selected, format!("{}   {}", row.2, row.3))
                                .on_hover_text(&row.0);
                            if clicked.clicked() {
                                resources.get_mut::<SelectedEntity>().select(row.1);
                            }
                            if clicked.double_clicked() {
                                frame_static(&map.scene, row.1, resources);
                            }
                        }
                    });
            });
    }
}

fn frame_static(
    scene: &alkahest_renderer::ecs::Scene,
    entity: hecs::Entity,
    resources: &Resources,
) {
    use alkahest_renderer::{
        camera::Camera,
        ecs::{hierarchy::Parent, render::static_geometry::StaticInstances, transform::Transform},
    };
    let Ok(transform) = scene.get::<&Transform>(entity) else {
        return;
    };
    let Ok(parent) = scene.get::<&Parent>(entity) else {
        return;
    };
    let Ok(group) = scene.get::<&StaticInstances>(parent.0) else {
        return;
    };
    let center = transform
        .local_to_world()
        .transform_point3(group.model.model.mesh_offset);
    let radius =
        (group.model.model.mesh_scale.abs() * transform.scale.abs().max_element()).max(1.0);
    let mut camera = resources.get_mut::<Camera>();
    camera.set_position(center + glam::Vec3::new(1.4, -1.8, 1.2) * radius);
    let angle = camera.get_look_angle(center);
    camera.set_orientation(angle);
    camera.update_matrices();
}
