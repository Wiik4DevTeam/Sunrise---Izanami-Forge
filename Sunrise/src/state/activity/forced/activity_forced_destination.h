#pragma once

#include "../destination/definition.h"
#include "definition.h"

namespace sunrise::state::activity::forced {

/**
 * Replaces the forced destination.
 * @param value Candidate selection, complete or partial.
 * @return True when every named field is inside its wire range and the value was stored.
 */
[[nodiscard]] bool publish(const ForcedDestination& value) noexcept;

/**
 * Copies the forced destination.
 * @param value Receives the stored selection.
 */
void snapshot(ForcedDestination& value) noexcept;

/** Drops the selection and the switch, the same as the interface's clear action. */
void clear() noexcept;

/** @return True while the stored selection is complete and its switch is on. */
[[nodiscard]] bool override_active() noexcept;

/**
 * Rewrites the destination activity in both the decoded selection and its captured descriptor.

 * * @param selection Selection whose carrier identity is being promoted.
 * @param activityIndex
 * Bias-free activity index to encode.
 * @return True when the index was valid and every captured
 * descriptor bit was rewritten.
 */
[[nodiscard]] bool rewrite_carrier_activity(destination::DestinationSelection& selection,
                                            std::int16_t activityIndex) noexcept;

/**
 * Overwrites one committed destination with the forced one. A captured descriptor is renamed
 * in
 * place so its opaque fields and carrier identity survive the redirect.
 * @param selection
 * Destination built from the client's request, replaced in place.
 * @return True when a complete
 * forced destination was applied.
 */
[[nodiscard]] bool apply(destination::DestinationSelection& selection) noexcept;

} // namespace sunrise::state::activity::forced
