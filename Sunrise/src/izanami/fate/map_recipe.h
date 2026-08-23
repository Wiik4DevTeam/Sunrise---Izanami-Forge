#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "../core/transform.h"

namespace sunrise::izanami::fate::recipe {

inline constexpr std::uint32_t kFormatVersion = 1;

struct ActorInstruction {
    std::uint64_t editorId{};
    std::uint64_t parentId{};
    std::string name{};
    std::uint32_t tag{};
    std::uint8_t objectType{};
    core::Transform transform{};
};

struct MapRecipe {
    std::string name{"Quick Save"};
    std::vector<ActorInstruction> actors{};
};

struct IoResult {
    std::string message{};
    std::size_t instructionCount{};
    bool succeeded{};
};

/** Resolves the live module's adjacent Izanami project recipe. */
[[nodiscard]] bool default_path(std::wstring& output) noexcept;

/** Writes a Fate spawn-instruction recipe without modifying native packages. */
[[nodiscard]] IoResult save(std::wstring_view path,
                            std::string_view sceneName,
                            std::span<const ActorInstruction> actors) noexcept;

/** Reads and validates a Fate spawn-instruction recipe. */
[[nodiscard]] IoResult load(std::wstring_view path, MapRecipe& output) noexcept;

} // namespace sunrise::izanami::fate::recipe
