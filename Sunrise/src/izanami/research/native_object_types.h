#pragma once

#include <array>
#include <cstdint>
#include <span>
#include <string_view>

namespace sunrise::izanami::research {

enum class ObjectTypeEvidence : std::uint8_t {
    sourceNamed,
    fieldCorrelated,
};

struct NativeObjectTypeRecord {
    std::uint8_t value{};
    std::string_view name{};
    std::string_view family{};
    std::string_view spawnNotes{};
    ObjectTypeEvidence evidence{ObjectTypeEvidence::sourceNamed};
};

/** Complete object-type table recovered by Sunrise's resident-entity spawner. */
[[nodiscard]] std::span<const NativeObjectTypeRecord> native_object_types() noexcept;

/** @return A stable label for one native entity-definition object type. */
[[nodiscard]] std::string_view native_object_type_name(std::uint8_t value) noexcept;

/** @return The evidence level behind one object-type label. */
[[nodiscard]] std::string_view object_type_evidence_text(ObjectTypeEvidence value) noexcept;

} // namespace sunrise::izanami::research
