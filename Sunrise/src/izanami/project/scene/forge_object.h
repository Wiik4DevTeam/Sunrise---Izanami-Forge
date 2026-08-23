#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "../../core/ids.h"
#include "../../core/native_map_binding.h"
#include "../../core/transform.h"

namespace sunrise::izanami::project::scene {

struct NativeOverrideRecord {
    std::uint32_t classId{};
    std::vector<std::byte> payload{};
};

struct ScriptBinding {
    std::string moduleName{};
    std::string entityName{};
};

struct ForgeObject {
    core::ForgeUUID id{};
    core::ResourceId resource{};
    core::ObjectKind kind{core::ObjectKind::forgeOnly};
    core::Transform transform{};
    core::ForgeUUID parent{};
    std::string editorName{};
    bool editorVisible{true};
    bool editorLocked{};
    std::optional<core::NativeMapBinding> nativeMapBinding{};
    std::vector<NativeOverrideRecord> nativeOverrides{};
    std::vector<ScriptBinding> scripts{};
};

struct StaticInstance {
    ForgeObject object{};
};

struct PatternInstance {
    ForgeObject object{};
};

[[nodiscard]] ForgeObject make_object(core::ForgeUUID id,
                                      core::ObjectKind kind,
                                      core::ResourceId resource,
                                      core::Transform transform);

[[nodiscard]] StaticInstance
make_static_instance(core::ForgeUUID id, core::ResourceId resource, core::Transform transform);

[[nodiscard]] PatternInstance
make_pattern_instance(core::ForgeUUID id, core::ResourceId resource, core::Transform transform);

} // namespace sunrise::izanami::project::scene
