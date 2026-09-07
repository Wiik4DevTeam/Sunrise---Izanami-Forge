#pragma once

#include <array>
#include <cstdint>
#include <string_view>

#include "../destination/definition.h"

namespace sunrise::state::activity::carrier {

/** One real, non-social client activity that can carry a rebuilt local selection. */
struct NativeCarrier final {
    std::array<char, destination::kPackageNameCapacity> packageName{};
    std::uint8_t packageNameLength{};
    std::int16_t activityIndex{destination::kAbsentActivityIndex};
};

/** Records a nonzero native carrier observed before a forced destination rewrite. */
[[nodiscard]] bool publish(std::string_view packageName, std::int16_t activityIndex) noexcept;

/** Copies the latest carrier captured for this exact Destiny executable fingerprint. */
[[nodiscard]] bool snapshot(NativeCarrier& output) noexcept;

/** Clears the in-memory carrier. The build-scoped on-disk record remains available on restart. */
void clear() noexcept;

} // namespace sunrise::state::activity::carrier
