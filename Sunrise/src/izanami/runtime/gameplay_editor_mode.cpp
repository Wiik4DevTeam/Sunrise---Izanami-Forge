#include "gameplay_editor_mode.h"

#include "../../client/hooks/cursor/runtime.h"
#include "../../client/hooks/director/director_handoff.h"
#include "../../client/hooks/polled_input/runtime.h"
#include "../../client/movement/movement_settings_store.h"
#include "../../core/ui/runtime/ui_visibility_runtime.h"
#include "../editor/ui/izanami_panel.h"

namespace sunrise::izanami::runtime::gameplay_editor_mode {
namespace {

client::movement::Settings g_previousMovement{};
bool g_hasPreviousMovement{};
bool g_active{};

[[nodiscard]] NativeActivityLaunchResult
request_native_activity_launch_impl(bool rebuildCarrier,
                                    client::hooks::director::ActivityGoalMode goalMode,
                                    bool rescueStalledPrologue = false) noexcept {
    const client::hooks::director::ActivityLaunchResult launch =
        client::hooks::director::request_activity_launch(
            rebuildCarrier, goalMode, rescueStalledPrologue);
    bool uiHidden = false;
    if (launch.requested) {
        uiHidden = core::ui::runtime::set_visible(false);
        (void)editor::ui::set_standalone_visible(false);
        client::hooks::cursor::apply_visibility(false);
        client::hooks::polled_input::apply_visibility(false);
    }
    return {.requested = launch.requested,
            .targetResolved = launch.targetResolved,
            .inOrbit = launch.inOrbit,
            .uiHidden = uiHidden};
}

[[nodiscard]] bool enable_navigation() noexcept {
    if (!g_active) {
        g_previousMovement = client::movement::get();
        g_hasPreviousMovement = true;
    }

    client::movement::Settings movement = client::movement::get();
    movement.noclipEnabled = true;
    movement.flyEnabled = true;
    if (movement.flySpeed < 25.0F) {
        movement.flySpeed = 25.0F;
    }
    g_active = client::movement::publish(movement);
    return g_active;
}

void restore_navigation() noexcept {
    client::movement::Settings movement =
        g_hasPreviousMovement ? g_previousMovement : client::movement::get();
    movement.noclipEnabled = false;
    movement.flyEnabled = false;
    (void)client::movement::publish(movement);
    g_previousMovement = {};
    g_hasPreviousMovement = false;
    g_active = false;
}

} // namespace

/** Enables released Sunrise movement hooks as the first real-game Forge navigation backend. */
ActivationResult enter() noexcept {
    ActivationResult result{};
    result.uiHidden = core::ui::runtime::set_visible(false);
    (void)editor::ui::set_standalone_visible(false);
    client::hooks::cursor::apply_visibility(false);
    client::hooks::polled_input::apply_visibility(false);
    result.navigationEnabled = false;
    return result;
}

bool enter_overlay_navigation() noexcept {
    return enable_navigation();
}

/** Requests Destiny's own Director UI as the next activity-load trigger. */
NativeDirectorHandoffResult request_native_director_handoff() noexcept {
    const bool uiHidden = core::ui::runtime::set_visible(false);
    (void)editor::ui::set_standalone_visible(false);
    client::hooks::cursor::apply_visibility(false);
    client::hooks::polled_input::apply_visibility(false);
    const client::hooks::director::HandoffResult handoff =
        client::hooks::director::request_open_destinations();
    return {.requested = handoff.requested,
            .usedDestinationsTab = handoff.usedDestinationsTab,
            .usedDirector = handoff.usedDirector,
            .usedFallback = handoff.usedFallback,
            .accountBindingsConfigured = handoff.accountBindingsConfigured,
            .uiHidden = uiHidden};
}

/** Queues Destiny's native activity-session creation, then yields the screen to the game. */
NativeActivityLaunchResult request_native_activity_launch(bool rebuildCarrier) noexcept {
    return request_native_activity_launch_impl(
        rebuildCarrier, client::hooks::director::ActivityGoalMode::activityTransition);
}

NativeActivityLaunchResult request_native_catalog_activity_launch() noexcept {
    return request_native_activity_launch_impl(
        false, client::hooks::director::ActivityGoalMode::activityTransition, true);
}

/** Restores movement settings captured before Izanami entered anchored editor mode. */
void leave() noexcept {
    client::hooks::director::cancel();
    restore_navigation();
}

void leave_overlay_navigation() noexcept {
    restore_navigation();
}

/** Reports whether anchored editor mode currently owns movement settings. */
bool active() noexcept {
    return g_active;
}

} // namespace sunrise::izanami::runtime::gameplay_editor_mode
