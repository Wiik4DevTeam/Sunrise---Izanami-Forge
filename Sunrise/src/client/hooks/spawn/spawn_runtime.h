#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>

#include "../../spawn/spawn_keybind_store.h"

namespace sunrise::client::hooks::spawn {

enum class Origin : std::uint8_t {
    player,
    surfaceRaycast,
    cameraRay,
    world,
};

enum class SpawnOutcome : std::uint8_t {
    none,
    created,
    cameraUnavailable,
    playerUnavailable,
    surfaceMiss,
    factoryRejected,
};

struct Settings {
    float lift{1.0F};
    float rayDistance{10.0F};
    float scale{1.0F};
    std::array<float, 3> offset{};
    std::array<float, 4> rotation{0.0F, 0.0F, 0.0F, 1.0F};
    bool useCameraRotation{};
    bool overrideRotation{};
};

struct SpawnObservation {
    std::uint64_t sequence{};
    std::uint32_t tag{};
    std::uint32_t handle{0xFFFFFFFFU};
    std::uint8_t objectType{};
    SpawnOutcome outcome{SpawnOutcome::none};
    std::array<float, 3> position{};
    std::array<float, 4> rotation{0.0F, 0.0F, 0.0F, 1.0F};
    float scale{1.0F};
    bool succeeded{};
};

struct RaycastProbe {
    std::array<float, 3> start{};
    std::array<float, 3> end{};
    std::array<float, 3> position{};
    float fraction{1.0F};
    std::int32_t material{-1};
    bool nativeResult{};
    bool outputChanged{};
    bool hit{};
};

struct WorldObjectDefinition {
    std::uint32_t tag{};
    std::uint8_t objectType{};
};

enum class WorldObjectIdentity : std::uint8_t {
    definitionTag,
    definitionPointer,
    tagAndPointer,
};

struct WorldObjectObservation {
    std::uint32_t handle{0xFFFFFFFFU};
    std::uint32_t tag{};
    std::uint8_t objectType{};
    WorldObjectIdentity identity{WorldObjectIdentity::definitionTag};
};

struct WorldObjectScan {
    std::size_t slotsScanned{};
    std::size_t liveHandles{};
    std::size_t matchedObjects{};
    std::size_t ambiguousObjects{};
    std::size_t unstableObjects{};
};

using WorldObjectVisitor = bool (*)(void*, const WorldObjectObservation&);

[[nodiscard]] bool install() noexcept;
void uninstall() noexcept;

[[nodiscard]] bool ready() noexcept;
[[nodiscard]] bool busy() noexcept;
[[nodiscard]] bool is_tag_resident(std::uint32_t tag) noexcept;
[[nodiscard]] bool object_live(std::uint32_t handle) noexcept;
[[nodiscard]] bool object_type(std::uint32_t tag, std::uint8_t& type) noexcept;

/**
 * Enumerates validated live object datums and correlates them with caller-supplied resident
 * entity
 * definitions. This is an identity-only diagnostic: it does not infer native transforms
 * or
 * ownership, and records that match more than one definition are excluded.
 */
[[nodiscard]] bool visit_world_objects(std::span<const WorldObjectDefinition> definitions,
                                       void* context,
                                       WorldObjectVisitor visitor,
                                       WorldObjectScan& scan) noexcept;
[[nodiscard]] SpawnObservation last_spawn_observation() noexcept;
[[nodiscard]] std::string_view spawn_outcome_text(SpawnOutcome outcome) noexcept;

/** Executes one read-only native world raycast from the camera through the crosshair. */
[[nodiscard]] bool probe_crosshair(float distance, RaycastProbe& output) noexcept;

[[nodiscard]] bool
request(std::uint32_t tag, Origin origin, std::uint32_t amount, const Settings& settings) noexcept;

/** Queues one resident entity at an exact authored world transform. */
[[nodiscard]] bool request_at(std::uint32_t tag,
                              const std::array<float, 3>& position,
                              const std::array<float, 4>& rotation,
                              float scale) noexcept;

/** Queues a transform write for an existing native entity handle. */
[[nodiscard]] bool request_transform(std::uint32_t handle,
                                     const std::array<float, 3>& position,
                                     const std::array<float, 4>& rotation,
                                     float scale) noexcept;

[[nodiscard]] bool request_line(std::span<const std::uint32_t> tags,
                                Origin origin,
                                std::uint32_t itemsPerRow,
                                float spacing,
                                const Settings& settings) noexcept;

void configure_shortcut(client::spawn::Action action,
                        std::uint32_t tag,
                        std::uint32_t amount,
                        const Settings& settings) noexcept;

void cancel() noexcept;

} // namespace sunrise::client::hooks::spawn
