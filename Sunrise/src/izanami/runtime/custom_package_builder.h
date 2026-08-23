#pragma once

#include <cstddef>
#include <cstdint>
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

struct MapPlacementEdit {
    core::NativeMapBinding binding{};
    core::Transform transform{};
    /** Optional static-map parent substituted after the source binding has been validated. */
    std::uint32_t replacementParentTag{};
};

/** Finds the smallest readable static placements reachable from one supported map root. */
[[nodiscard]] bool discover_static_placements(std::string_view rootName,
                                              std::span<StaticPlacementCandidate> output,
                                              std::size_t& count) noexcept;

/** Catalogs static placements from any readable installed map root without staging changes. */
[[nodiscard]] bool discover_authored_static_placements(std::string_view rootName,
                                                       std::span<StaticPlacementCandidate> output,
                                                       std::size_t& count) noexcept;

/**
 * Builds a non-loadable staged patch for one explicitly supported map root.
 * The `.izanami-stage` suffix keeps Destiny from registering it until every changed block has
 * round-trip validated and a deliberate installation step has succeeded.
 */
[[nodiscard]] bool stage_map_root(std::string_view rootName) noexcept;

/** Builds a staged patch containing only the named, source-validated placement edits. */
[[nodiscard]] bool stage_map_root(std::string_view rootName,
                                  std::span<const MapPlacementEdit> edits) noexcept;

} // namespace sunrise::izanami::runtime::custom_package_builder
