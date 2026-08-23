#pragma once

#include <array>
#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace sunrise::izanami::editor::ui::asset_metadata {

struct Entry {
    std::uint32_t tag{};
    std::string name{};
    std::array<float, 3> color{};
    bool hasCustomColor{};
};

/** Loads persistent per-tag Asset Browser presentation metadata. */
[[nodiscard]] bool load(std::vector<Entry>& output, std::string& message) noexcept;

/** Atomically stores persistent per-tag Asset Browser presentation metadata. */
[[nodiscard]] bool save(std::span<const Entry> entries, std::string& message) noexcept;

} // namespace sunrise::izanami::editor::ui::asset_metadata
