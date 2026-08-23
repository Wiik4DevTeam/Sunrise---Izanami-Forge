#pragma once

#include <cstdint>

namespace sunrise::client::hooks::director {

enum class ActivityGoalMode : std::uint8_t {
    orbitCarrier = 1,
    activityTransition = 2,
};

struct HandoffResult {
    bool requested{};
    bool usedDestinationsTab{};
    bool usedDirector{};
    bool usedFallback{};
    bool accountBindingsConfigured{};
};

struct ActivityLaunchResult {
    bool requested{};
    bool targetResolved{};
    bool inOrbit{};
};

/**
 * Installs the dormant one-shot local activity carrier during the main-image hook sweep.
 * A miss is diagnostic and must not prevent ordinary Sunrise activation.
 */
[[nodiscard]] bool install_local_carrier() noexcept;

/**
 * Queues Destiny's native orbit-to-activity transition for the next game-thread poll.
 * @param rebuildCarrier True only for experimental package-rewritten catalog destinations.
 * @param goalMode Native world-controller goal mode published with the transition.
 * @param rescueStalledPrologue Advance resident catalog maps whose intro metadata never resolves.
 * @return Resolution and orbit validation details for the request.
 */
[[nodiscard]] ActivityLaunchResult
request_activity_launch(bool rebuildCarrier,
                        ActivityGoalMode goalMode = ActivityGoalMode::activityTransition,
                        bool rescueStalledPrologue = false) noexcept;

/**
 * Requests a short native key pulse that opens Destiny's Director.
 * The pulse is emitted on the next game-frame polls so the game, not Sunrise UI code, owns the
 * transition into its Destinations experience.
 */
[[nodiscard]] HandoffResult request_open_destinations() noexcept;

/** Runs a queued activity transition or Director key pulse. Call from a game-thread hook. */
void poll() noexcept;

/** Cancels pending launch work and releases the spoofed key. */
void cancel() noexcept;

/** Cancels pending work and detaches the local-selection hook before client teardown. */
void shutdown() noexcept;

} // namespace sunrise::client::hooks::director
