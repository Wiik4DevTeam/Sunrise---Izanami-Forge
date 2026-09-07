#pragma once

#include <cstddef>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "map_recipe.h"

namespace sunrise::izanami::fate::group_recipe {

inline constexpr std::uint32_t kFormatVersion = 1;

struct GroupAsset {
    std::string name{};
    std::wstring path{};
    std::vector<recipe::ActorInstruction> actors{};
};

/** Atomically writes one reusable group asset beside the live module. */
[[nodiscard]] recipe::IoResult save(std::string_view name,
                                    std::span<const recipe::ActorInstruction> actors) noexcept;

/** Loads every structurally valid reusable group asset from the persistent library. */
[[nodiscard]] recipe::IoResult load_all(std::vector<GroupAsset>& output) noexcept;

} // namespace sunrise::izanami::fate::group_recipe
