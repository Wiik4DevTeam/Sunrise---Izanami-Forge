#pragma once

#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "../core/native_map_binding.h"
#include "map_recipe.h"

namespace sunrise::izanami::fate::authored_map_recipe {

inline constexpr std::uint32_t kFormatVersion = 1;

struct Instruction {
    core::NativeMapBinding binding{};
    std::uint32_t entityTag{};
    std::uint32_t resourceClass{};
    std::uint32_t resourceTag{};
    core::Transform targetTransform{};
    bool hidden{};
};

struct Recipe {
    std::string mapRoot{};
    std::vector<Instruction> edits{};
};

/** Resolves the persistent authored-edit recipe beside the loaded Sunrise module. */
[[nodiscard]] bool default_path(std::string_view mapRoot, std::wstring& output) noexcept;

/** Atomically replaces one map root's exact authored-row edit recipe. */
[[nodiscard]] recipe::IoResult
save(std::wstring_view path, std::string_view mapRoot, std::span<const Instruction> edits) noexcept;

/** Reads and validates an exact authored-row edit recipe. */
[[nodiscard]] recipe::IoResult load(std::wstring_view path, Recipe& output) noexcept;

} // namespace sunrise::izanami::fate::authored_map_recipe
