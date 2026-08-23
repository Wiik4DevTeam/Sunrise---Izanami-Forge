#pragma once

#include <cstdint>

#include "transform.h"

namespace sunrise::izanami::core {

/** Stable identity and source-state guard for one package-backed native map placement. */
struct NativeMapBinding {
    std::uint32_t tableTag{};
    std::uint32_t entryIndex{};
    std::uint32_t parentTag{};
    Transform sourceTransform{};

    [[nodiscard]] bool is_valid() const noexcept {
        return tableTag != 0 && parentTag != 0 && sourceTransform.is_finite()
               && sourceTransform.uniformScale > 0.0F;
    }

    [[nodiscard]] bool same_record(const NativeMapBinding& other) const noexcept {
        return tableTag == other.tableTag && entryIndex == other.entryIndex;
    }
};

} // namespace sunrise::izanami::core
