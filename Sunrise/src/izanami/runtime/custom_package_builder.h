#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <span>
#include <string_view>

#include "../core/native_map_binding.h"

namespace sunrise::izanami::runtime::custom_package_builder {

struct StaticPlacementCandidate {
    core::NativeMapBinding binding{};
    std::uint32_t entityTag{};
    std::uint32_t dataTag{};
    std::size_t parentBytes{};
    std::size_t dataBytes{};
};

enum class AuthoredPlacementKind : std::uint8_t {
    entity,
    staticAggregate,
    staticInstance,
    sky,
    visibility,
    collision,
    entityModel,
    component,
    resource,
};

constexpr std::uint32_t kNoAuthoredPlacementParent = (std::numeric_limits<std::uint32_t>::max)();

/** One source-validated row, or one validated mesh instance expanded from a static aggregate. */
struct AuthoredPlacementCandidate {
    core::NativeMapBinding binding{};
    std::uint32_t parentCandidateIndex{kNoAuthoredPlacementParent};
    std::uint32_t entityTag{};
    std::uint32_t resourceClass{};
    std::uint32_t resourceTag{};
    std::uint32_t dataTag{};
    std::uint32_t meshTag{};
    std::uint64_t worldId{};
    std::uint32_t groupIndex{kNoAuthoredPlacementParent};
    std::uint32_t transformIndex{kNoAuthoredPlacementParent};
    std::size_t dataBytes{};
    std::uint8_t objectType{};
    AuthoredPlacementKind kind{AuthoredPlacementKind::resource};
    bool objectTypeKnown{};
    bool transformKnown{};
    bool stageEditable{};
};

struct AuthoredPlacementStats {
    std::size_t mapTables{};
    std::size_t placementRows{};
    std::size_t entityPlacements{};
    std::size_t resourcePlacements{};
    std::size_t staticAggregates{};
    std::size_t staticInstances{};
    std::size_t unsupportedResources{};
    std::size_t emitted{};
    bool truncated{};
};

struct MapPlacementEdit {
    core::NativeMapBinding binding{};
    core::Transform transform{};
    /** Optional static-map parent substituted after the source binding has been validated. */
    std::uint32_t replacementParentTag{};
};

/** One exact authored row edit replayed only after its source identity and transform match. */
struct AuthoredPlacementEdit {
    core::NativeMapBinding binding{};
    std::uint32_t entityTag{};
    std::uint32_t resourceClass{};
    std::uint32_t resourceTag{};
    core::Transform targetTransform{};
};

/** Finds the smallest readable static placements reachable from one supported map root. */
[[nodiscard]] bool discover_static_placements(std::string_view rootName,
                                              std::span<StaticPlacementCandidate> output,
                                              std::size_t& count) noexcept;

/** Catalogs static placements from any readable installed map root without staging changes. */
[[nodiscard]] bool discover_authored_static_placements(std::string_view rootName,
                                                       std::span<StaticPlacementCandidate> output,
                                                       std::size_t& count) noexcept;

/** Catalogs every readable authored row and expands validated static-mesh instance arrays. */
[[nodiscard]] bool discover_authored_placements(std::string_view rootName,
                                                std::span<AuthoredPlacementCandidate> output,
                                                std::size_t& count,
                                                AuthoredPlacementStats& stats) noexcept;

/**
 * Builds a non-loadable staged patch for one explicitly supported map root.
 * The `.izanami-stage` suffix keeps Destiny from registering it until every changed block has
 * round-trip validated and a deliberate installation step has succeeded.
 */
[[nodiscard]] bool stage_map_root(std::string_view rootName) noexcept;

/** Builds a staged Pandora draft containing only its sky and tiled baseplate aggregate. */
[[nodiscard]] bool stage_pandora_baseplate_world(std::string_view rootName) noexcept;

/** Builds a staged patch containing only the named, source-validated placement edits. */
[[nodiscard]] bool stage_map_root(std::string_view rootName,
                                  std::span<const MapPlacementEdit> edits) noexcept;

/** Builds a staged Pandora patch containing only exact, source-validated authored-row edits. */
[[nodiscard]] bool stage_authored_map_root(std::string_view rootName,
                                           std::span<const AuthoredPlacementEdit> edits) noexcept;

} // namespace sunrise::izanami::runtime::custom_package_builder
