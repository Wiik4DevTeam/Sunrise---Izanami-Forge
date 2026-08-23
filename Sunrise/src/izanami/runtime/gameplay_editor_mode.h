#pragma once

namespace sunrise::izanami::runtime::gameplay_editor_mode {

struct ActivationResult {
    bool navigationEnabled{};
    bool uiHidden{};
};

struct NativeDirectorHandoffResult {
    bool requested{};
    bool usedDestinationsTab{};
    bool usedDirector{};
    bool usedFallback{};
    bool accountBindingsConfigured{};
    bool uiHidden{};
};

struct NativeActivityLaunchResult {
    bool requested{};
    bool targetResolved{};
    bool inOrbit{};
    bool uiHidden{};
};

/** Enables the currently available real-game editor footholds. */
[[nodiscard]] ActivationResult enter() noexcept;

/** Enables Fly/Noclip while preserving the standalone Forge interface. */
[[nodiscard]] bool enter_overlay_navigation() noexcept;

/** Requests Destiny's own Director UI as the next activity-load trigger. */
[[nodiscard]] NativeDirectorHandoffResult request_native_director_handoff() noexcept;

/** Queues Destiny's native orbit-to-activity transition without opening the Director. */
[[nodiscard]] NativeActivityLaunchResult
request_native_activity_launch(bool rebuildCarrier = false) noexcept;

/** Queues a catalog destination and recovers resident maps with no usable intro metadata. */
[[nodiscard]] NativeActivityLaunchResult request_native_catalog_activity_launch() noexcept;

/** Restores any settings changed by enter(). */
void leave() noexcept;

/** Restores Forge navigation without cancelling an activity launch already in flight. */
void leave_overlay_navigation() noexcept;

/** @return True while Izanami owns an anchored editor-mode activation. */
[[nodiscard]] bool active() noexcept;

} // namespace sunrise::izanami::runtime::gameplay_editor_mode
