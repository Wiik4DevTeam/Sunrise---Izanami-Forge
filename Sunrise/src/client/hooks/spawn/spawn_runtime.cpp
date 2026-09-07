#include "spawn_runtime.h"
#include "activation_queue.h"

#include <Windows.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <bit>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string_view>
#include <vector>

#include "../../../core/logging/log.h"
#include "../../../core/ui/runtime/ui_visibility_runtime.h"
#include "../../hooking/detour.h"
#include "../../patterns/image_scan.h"
#include "../../patterns/signature_text.h"
#include "../teleport/runtime.h"

namespace sunrise::client::hooks::spawn {
namespace {

using namespace patterns;

constexpr std::string_view kPlacementInitializeText =
    "89 54 24 10 53 48 83 EC 20 48 8B D9 83 FA FF 0F 84 ? ? ? ? 48 8D 54 24 30 "
    "48 8D 4C 24 38 E8 ? ? ? ? 8B 44 24 30 83 F8 FF 0F 84 ? ? ? ? 48 8B 15 ? ? ? ?";
constexpr auto kPlacementInitialize =
    signature<signature_length(kPlacementInitializeText)>(kPlacementInitializeText);

constexpr std::string_view kDirectInitializeText =
    "48 89 5C 24 08 57 48 83 EC 20 8B DA 48 8B F9 83 FA FF 74 33 8B CA E8 ? ? ? ? "
    "48 C7 47 30 00 00 00 00 48 8B CF 48 C7 47 10 00 00 00 00";
constexpr auto kDirectInitialize =
    signature<signature_length(kDirectInitializeText)>(kDirectInitializeText);

constexpr std::string_view kObjectFactoryText =
    "40 53 48 83 EC 20 41 83 C9 FF 41 83 C8 FF 48 8B D9 E8 ? ? ? ? 48 8B C3 "
    "48 83 C4 20 5B C3";
constexpr auto kObjectFactory = signature<signature_length(kObjectFactoryText)>(kObjectFactoryText);

constexpr std::string_view kObjectTransformText =
    "48 89 5C 24 10 57 48 83 EC 70 0F 29 74 24 60 48 8B 05 ? ? ? ? 48 33 C4 "
    "48 89 44 24 50 0F 10 02 48 8B F9 0F 11 81 A0 00 00 00 0F 10 72 10 "
    "0F 29 74 24 30 E8 ? ? ? ? 8B D8 E8 ? ? ? ?";
constexpr auto kObjectTransform =
    signature<signature_length(kObjectTransformText)>(kObjectTransformText);

constexpr std::string_view kWorldRaycastText =
    "48 8B C4 48 89 58 08 48 89 70 10 55 57 41 54 41 56 41 57 48 8D 68 98 "
    "48 81 EC 40 01 00 00 0F 29 70 C8 0F 29 78 B8";
constexpr auto kWorldRaycast = signature<signature_length(kWorldRaycastText)>(kWorldRaycastText);

constexpr std::string_view kPlayerComponentUpdateText =
    "48 89 5C 24 10 55 57 41 54 41 56 41 57 48 8B EC 48 83 EC 70 45 33 E4 "
    "48 89 B4 24 A0 00 00 00 41 8B FC 48 8D 99 FC 02 00 00 4D 8B F0 4C 8B FA";
constexpr auto kPlayerComponentUpdate =
    signature<signature_length(kPlayerComponentUpdateText)>(kPlayerComponentUpdateText);

constexpr std::size_t kResolverCallOperand = 0x17;
constexpr std::size_t kResolverCallEnd = 0x1B;
constexpr std::uint32_t kInvalidDatum = 0xFFFFFFFFU;
constexpr std::size_t kDefinitionObjectType = 0x96;
constexpr std::uint32_t kMaximumAmount = 4096;
constexpr std::size_t kMaximumLineItems = 262144;
constexpr std::size_t kPlacementHeaderBytes = 0x40;
constexpr std::size_t kPlacementPayloadBytes = 0x800;

constexpr std::uintptr_t kObjectDatumDescriptorRva = 0x1F93420;
constexpr std::size_t kObjectDatumBaseOffset = 0x08;
constexpr std::size_t kObjectDatumStrideOffset = 0x10;
constexpr std::size_t kObjectDatumBytes = 0xE0;
constexpr std::size_t kObjectHandleOffset = 0x0C;
constexpr std::size_t kObjectDatumCapacity = 1U << 13U;
// Match the maximum saved combined asset so a full group can be queued together.
constexpr std::size_t kActivationCapacity = 1024;
constexpr std::uint8_t kActivationAttempts = 4;
constexpr std::uint64_t kRequestTimeoutMs = 3000;

using PlacementInitialize = std::uint8_t(__fastcall*)(void*, std::uint32_t);
using ObjectFactory = std::uint32_t*(__fastcall*)(std::uint32_t*, void*);
using ObjectTransform = void(__fastcall*)(void*, const float*);
using TagResolver = const std::byte*(__fastcall*)(std::uint32_t);
using WorldRaycast = bool(__fastcall*)(const float*,
                                       const float*,
                                       const float*,
                                       const float*,
                                       std::int32_t,
                                       std::int32_t,
                                       float,
                                       float*,
                                       float*,
                                       std::int32_t*);
using PlayerComponentUpdate = void(__fastcall*)(void*, void*, void*);

struct alignas(16) PlacementStorage {
    std::array<std::byte, kPlacementHeaderBytes + kPlacementPayloadBytes> bytes{};
};

struct Request {
    std::vector<std::uint32_t> tags{};
    Settings settings{};
    std::array<float, 3> absolutePosition{};
    Origin origin{Origin::player};
    std::uint32_t amount{};
    std::uint32_t itemsPerRow{1};
    float spacing{1.0F};
    std::uint64_t lastProgress{};
    std::size_t cursor{};
    bool line{};
};

struct Shortcut {
    Settings settings{};
    std::uint32_t tag{kInvalidDatum};
    std::uint32_t amount{};
};

struct ResolvedWorldDefinition {
    WorldObjectDefinition definition{};
    const std::byte* address{};
};

enum class HookSlot : std::size_t {
    update,
    transform,
    count,
};

std::array<hooking::detour::Handle, static_cast<std::size_t>(HookSlot::count)> g_hooks{};
std::atomic_bool g_installed{};
PlacementInitialize g_initialize{};
PlacementInitialize g_directInitialize{};
ObjectFactory g_factory{};
ObjectTransform g_transform{};
TagResolver g_resolver{};
WorldRaycast g_raycast{};
HMODULE g_gameModule{};

SRWLOCK g_requestLock{SRWLOCK_INIT};
Request g_request{};
SRWLOCK g_activationLock{SRWLOCK_INIT};
ActivationQueue<kActivationCapacity> g_activations{};
SRWLOCK g_shortcutLock{SRWLOCK_INIT};
std::array<Shortcut, client::spawn::kActionCount> g_shortcuts{};
std::array<std::atomic_bool, client::spawn::kActionCount> g_shortcutDown{};
SRWLOCK g_observationLock{SRWLOCK_INIT};
SpawnObservation g_spawnObservation{};

template <typename T> [[nodiscard]] bool safe_read(const void* source, T& value) noexcept;

struct TransformObservationSlot {
    std::atomic_flag writer = ATOMIC_FLAG_INIT;
    std::atomic_uint32_t sequence{};
    std::atomic_uint32_t handle{kInvalidDatum};
    std::array<std::atomic_uint32_t, 8> lanes{};
};

std::array<TransformObservationSlot, kObjectDatumCapacity> g_transformObservations{};

void clear_transform_observations() noexcept {
    for (TransformObservationSlot& slot : g_transformObservations) {
        slot.writer.clear(std::memory_order_relaxed);
        slot.sequence.store(0, std::memory_order_relaxed);
        slot.handle.store(kInvalidDatum, std::memory_order_relaxed);
        for (std::atomic_uint32_t& lane : slot.lanes) {
            lane.store(0, std::memory_order_relaxed);
        }
    }
}

void observe_transform(void* object, const float* transform) noexcept {
    std::uint32_t handle = kInvalidDatum;
    std::array<float, 8> values{};
    if (object == nullptr || transform == nullptr
        || !safe_read(static_cast<const std::byte*>(object) + kObjectHandleOffset, handle)
        || handle == kInvalidDatum || (handle & 0x1FFFU) >= g_transformObservations.size()
        || !safe_read(transform, values)
        || !std::all_of(
            values.begin(), values.end(), [](float value) { return std::isfinite(value); })
        || values[7] <= 0.0F) {
        return;
    }

    TransformObservationSlot& slot = g_transformObservations[handle & 0x1FFFU];
    if (slot.writer.test_and_set(std::memory_order_acquire)) {
        return;
    }
    (void)slot.sequence.fetch_add(1, std::memory_order_acq_rel);
    slot.handle.store(handle, std::memory_order_relaxed);
    for (std::size_t index = 0; index < values.size(); ++index) {
        slot.lanes[index].store(std::bit_cast<std::uint32_t>(values[index]),
                                std::memory_order_relaxed);
    }
    (void)slot.sequence.fetch_add(1, std::memory_order_release);
    slot.writer.clear(std::memory_order_release);
}

[[nodiscard]] bool observed_transform(std::uint32_t handle,
                                      WorldObjectObservation& observation) noexcept {
    if (handle == kInvalidDatum || (handle & 0x1FFFU) >= g_transformObservations.size()) {
        return false;
    }
    TransformObservationSlot& slot = g_transformObservations[handle & 0x1FFFU];
    for (std::uint8_t attempt = 0; attempt < 3; ++attempt) {
        const std::uint32_t before = slot.sequence.load(std::memory_order_acquire);
        if ((before & 1U) != 0 || slot.handle.load(std::memory_order_relaxed) != handle) {
            continue;
        }
        std::array<float, 8> values{};
        for (std::size_t index = 0; index < values.size(); ++index) {
            values[index] = std::bit_cast<float>(slot.lanes[index].load(std::memory_order_relaxed));
        }
        const std::uint32_t after = slot.sequence.load(std::memory_order_acquire);
        if (before != after || (after & 1U) != 0
            || !std::all_of(
                values.begin(), values.end(), [](float value) { return std::isfinite(value); })
            || values[7] <= 0.0F) {
            continue;
        }
        observation.rotation = {values[0], values[1], values[2], values[3]};
        observation.position = {values[4], values[5], values[6]};
        observation.scale = values[7];
        observation.transformKnown = true;
        return true;
    }
    return false;
}

[[nodiscard]] std::string_view outcome_label(SpawnOutcome outcome) noexcept {
    switch (outcome) {
    case SpawnOutcome::none:
        return "none";
    case SpawnOutcome::created:
        return "created";
    case SpawnOutcome::cameraUnavailable:
        return "camera_unavailable";
    case SpawnOutcome::playerUnavailable:
        return "player_unavailable";
    case SpawnOutcome::surfaceMiss:
        return "surface_miss";
    case SpawnOutcome::factoryRejected:
        return "factory_rejected";
    case SpawnOutcome::timedOut:
        return "timed_out";
    }
    return "unknown";
}

void publish_spawn_observation(std::uint32_t tag,
                               std::uint32_t handle,
                               SpawnOutcome outcome,
                               std::string_view stage,
                               const std::array<float, 3>* position = nullptr,
                               const std::array<float, 4>* rotation = nullptr,
                               float scale = 1.0F) noexcept {
    std::uint8_t type = 0;
    (void)object_type(tag, type);
    const bool succeeded = outcome == SpawnOutcome::created && handle != kInvalidDatum;
    SpawnObservation observation{};
    observation.tag = tag;
    observation.handle = handle;
    observation.objectType = type;
    observation.outcome = outcome;
    if (position != nullptr) {
        observation.position = *position;
    }
    if (rotation != nullptr) {
        observation.rotation = *rotation;
    }
    observation.scale = scale;
    observation.succeeded = succeeded;
    AcquireSRWLockExclusive(&g_observationLock);
    observation.sequence = g_spawnObservation.sequence + 1;
    g_spawnObservation = observation;
    ReleaseSRWLockExclusive(&g_observationLock);

    std::array<char, 192> line{};
    const int written = std::snprintf(line.data(),
                                      line.size(),
                                      "ev=spawn stage=%.*s result=%s outcome=%.*s tag=0x%08X "
                                      "handle=0x%08X",
                                      static_cast<int>(stage.size()),
                                      stage.data(),
                                      succeeded ? "ok" : "fail",
                                      static_cast<int>(outcome_label(outcome).size()),
                                      outcome_label(outcome).data(),
                                      static_cast<unsigned>(tag),
                                      static_cast<unsigned>(handle));
    if (written > 0) {
        core::log::write(core::log::Channel::client,
                         succeeded ? core::log::Level::info : core::log::Level::warn,
                         {line.data(), static_cast<std::size_t>(written)});
    }
}

template <typename T> [[nodiscard]] bool safe_read(const void* source, T& value) noexcept {
    __try {
        std::memcpy(&value, source, sizeof value);
        return true;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        value = {};
        return false;
    }
}

[[nodiscard]] const std::byte* safe_resolve_definition(std::uint32_t tag) noexcept {
    if (g_resolver == nullptr) {
        return nullptr;
    }
    __try {
        return g_resolver(tag);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return nullptr;
    }
}

void reset_storage(PlacementStorage& storage) noexcept {
    storage = {};
    constexpr std::uint64_t zero = 0;
    constexpr std::uint64_t capacity = kPlacementPayloadBytes;
    constexpr std::uint64_t alignment = 0x10;
    std::memcpy(storage.bytes.data(), &zero, sizeof zero);
    std::memcpy(storage.bytes.data() + 0x10, &zero, sizeof zero);
    std::memcpy(storage.bytes.data() + 0x18, &kInvalidDatum, sizeof kInvalidDatum);
    std::memcpy(storage.bytes.data() + 0x20, &capacity, sizeof capacity);
    std::memcpy(storage.bytes.data() + 0x28, &alignment, sizeof alignment);
    std::memcpy(storage.bytes.data() + 0x30, &zero, sizeof zero);
}

[[nodiscard]] void* descriptor_of(PlacementStorage& storage) noexcept {
    std::int64_t relative = 0;
    return safe_read(storage.bytes.data(), relative) && relative != 0
               ? storage.bytes.data() + relative
               : nullptr;
}

[[nodiscard]] std::byte* resolve_object(std::uint32_t handle) noexcept {
    if (handle == kInvalidDatum || g_gameModule == nullptr) {
        return nullptr;
    }
    std::byte* const descriptor =
        reinterpret_cast<std::byte*>(g_gameModule) + kObjectDatumDescriptorRva;
    std::byte* base = nullptr;
    std::uint32_t stride = 0;
    if (!safe_read(descriptor + kObjectDatumBaseOffset, base)
        || !safe_read(descriptor + kObjectDatumStrideOffset, stride) || base == nullptr
        || stride != kObjectDatumBytes) {
        return nullptr;
    }
    std::byte* const object = base + (handle & 0x1FFFU) * stride;
    std::uint32_t live = kInvalidDatum;
    return safe_read(object + kObjectHandleOffset, live) && live == handle ? object : nullptr;
}

[[nodiscard]] const ResolvedWorldDefinition*
find_world_definition_by_tag(std::span<const ResolvedWorldDefinition> definitions,
                             std::uint32_t tag) noexcept {
    const auto found = std::lower_bound(
        definitions.begin(), definitions.end(), tag, [](const auto& candidate, auto value) {
            return candidate.definition.tag < value;
        });
    return found != definitions.end() && found->definition.tag == tag ? &*found : nullptr;
}

[[nodiscard]] const ResolvedWorldDefinition*
find_world_definition_by_address(std::span<const ResolvedWorldDefinition* const> definitions,
                                 const std::byte* address) noexcept {
    const auto found = std::lower_bound(
        definitions.begin(), definitions.end(), address, [](const auto* candidate, auto* value) {
            return reinterpret_cast<std::uintptr_t>(candidate->address)
                   < reinterpret_cast<std::uintptr_t>(value);
        });
    return found != definitions.end() && (*found)->address == address ? *found : nullptr;
}

void consider_world_definition(const ResolvedWorldDefinition* candidate,
                               const ResolvedWorldDefinition*& selected,
                               bool& ambiguous) noexcept {
    if (candidate == nullptr || ambiguous) {
        return;
    }
    if (selected == nullptr) {
        selected = candidate;
    } else if (selected->definition.tag != candidate->definition.tag) {
        ambiguous = true;
    }
}

[[nodiscard]] bool needs_activation(std::uint32_t tag) noexcept {
    if (g_resolver == nullptr) {
        return false;
    }
    const std::byte* definition = nullptr;
    std::uint8_t type = 0;
    __try {
        definition = g_resolver(tag);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
    if (definition == nullptr || !safe_read(definition + kDefinitionObjectType, type)) {
        return false;
    }
    return type == 8 || type == 11 || type == 20 || type == 21;
}

[[nodiscard]] bool queue_activation(std::uint32_t handle,
                                    const std::array<float, 4>& rotation,
                                    const std::array<float, 4>& position) noexcept {
    Activation value{};
    value.handle = handle;
    std::copy(rotation.begin(), rotation.end(), value.transform.begin());
    std::copy(position.begin(), position.end(), value.transform.begin() + 4);
    AcquireSRWLockExclusive(&g_activationLock);
    const bool queued = g_activations.append(std::span(&value, 1));
    ReleaseSRWLockExclusive(&g_activationLock);
    return queued;
}

void service_activations() noexcept {
    if (g_transform == nullptr) {
        return;
    }
    AcquireSRWLockExclusive(&g_activationLock);
    std::size_t index = 0;
    while (index < g_activations.size()) {
        Activation& value = g_activations[index];
        std::byte* const object = resolve_object(value.handle);
        bool finished = false;
        if (object != nullptr) {
            __try {
                g_transform(object, value.transform.data());
                finished = true;
            } __except (EXCEPTION_EXECUTE_HANDLER) {}
        }
        if (finished || ++value.attempts >= kActivationAttempts) {
            if (!finished) {
                core::log::write(
                    core::log::Channel::client,
                    core::log::Level::warn,
                    "ev=spawn stage=transform result=fail reason=activation_exhausted");
            }
            g_activations.erase(index);
            continue;
        }
        ++index;
    }
    ReleaseSRWLockExclusive(&g_activationLock);
}

[[nodiscard]] bool camera_rotation(const std::array<float, 3>& forward,
                                   std::array<float, 4>& rotation) noexcept {
    const float length =
        forward[0] * forward[0] + forward[1] * forward[1] + forward[2] * forward[2];
    if (!std::isfinite(length) || length <= 1.0e-8F) {
        return false;
    }
    const float inverse = 1.0F / std::sqrt(length);
    const std::array<float, 3> unit{
        forward[0] * inverse, forward[1] * inverse, forward[2] * inverse};
    if (unit[0] <= -0.9999F) {
        rotation = {0.0F, 0.0F, 1.0F, 0.0F};
        return true;
    }
    rotation = {0.0F, -unit[2], unit[1], 1.0F + unit[0]};
    const float quaternionLength = rotation[0] * rotation[0] + rotation[1] * rotation[1]
                                   + rotation[2] * rotation[2] + rotation[3] * rotation[3];
    if (!std::isfinite(quaternionLength) || quaternionLength <= 1.0e-8F) {
        return false;
    }
    const float inverseQuaternion = 1.0F / std::sqrt(quaternionLength);
    for (float& lane : rotation) {
        lane *= inverseQuaternion;
    }
    return true;
}

[[nodiscard]] bool crosshair_hit(float distance,
                                 const std::array<float, 3>& camera,
                                 const std::array<float, 3>& forward,
                                 std::array<float, 3>& output,
                                 float* hitFraction = nullptr,
                                 std::int32_t* hitMaterial = nullptr,
                                 bool* nativeResult = nullptr,
                                 bool* outputChanged = nullptr) noexcept {
    if (g_raycast == nullptr || !std::isfinite(distance) || distance <= 0.0F) {
        return false;
    }
    std::array<float, 4> up{0.0F, 0.0F, 1.0F, 0.0F};
    std::array<float, 4> start{camera[0], camera[1], camera[2], 0.0F};
    std::array<float, 4> end{camera[0] + forward[0] * distance,
                             camera[1] + forward[1] * distance,
                             camera[2] + forward[2] * distance,
                             0.0F};
    std::array<float, 4> hit = end;
    float fraction = 1.0F;
    std::int32_t material = -1;
    std::uint32_t controlled = kInvalidDatum;
    (void)teleport::current_controlled_handle(controlled);
    const std::int32_t ignored =
        controlled == kInvalidDatum ? -1 : static_cast<std::int32_t>(controlled);
    bool result = false;
    __try {
        result = g_raycast(up.data(),
                           up.data(),
                           start.data(),
                           end.data(),
                           ignored,
                           ignored,
                           0.0F,
                           &fraction,
                           hit.data(),
                           &material);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        result = false;
    }
    const float deltaX = hit[0] - end[0];
    const float deltaY = hit[1] - end[1];
    const float deltaZ = hit[2] - end[2];
    const bool changed = (std::isfinite(fraction) && fraction >= 0.0F && fraction < 0.99999F)
                         || material != -1
                         || (deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ) > 1.0e-6F;
    output = {hit[0], hit[1], hit[2]};
    if (hitFraction != nullptr) {
        *hitFraction = fraction;
    }
    if (hitMaterial != nullptr) {
        *hitMaterial = material;
    }
    if (nativeResult != nullptr) {
        *nativeResult = result;
    }
    if (outputChanged != nullptr) {
        *outputChanged = changed;
    }
    return result || changed;
}

[[nodiscard]] std::uint32_t spawn_one(std::uint32_t tag,
                                      const std::array<float, 3>& world,
                                      const std::array<float, 4>& rotation,
                                      float scale) noexcept {
    PlacementStorage storage{};
    reset_storage(storage);
    std::uint32_t result = kInvalidDatum;
    __try {
        bool initialized = g_initialize(storage.bytes.data(), tag) != 0;
        if (!initialized && g_resolver(tag) != nullptr) {
            reset_storage(storage);
            initialized = g_directInitialize(storage.bytes.data(), tag) != 0;
        }
        void* const descriptor = initialized ? descriptor_of(storage) : nullptr;
        if (descriptor != nullptr) {
            const std::array<float, 4> position{world[0], world[1], world[2], scale};
            std::memcpy(
                static_cast<std::byte*>(descriptor) + 0x10, rotation.data(), sizeof rotation);
            std::memcpy(
                static_cast<std::byte*>(descriptor) + 0x20, position.data(), sizeof position);
            (void)g_factory(&result, descriptor);
            if (result != kInvalidDatum && needs_activation(tag)) {
                if (!queue_activation(result, rotation, position)) {
                    core::log::write(core::log::Channel::client,
                                     core::log::Level::warn,
                                     "ev=spawn stage=activation result=fail reason=queue_full");
                }
            }
        }
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        result = kInvalidDatum;
    }
    publish_spawn_observation(tag,
                              result,
                              result != kInvalidDatum ? SpawnOutcome::created
                                                      : SpawnOutcome::factoryRejected,
                              "create",
                              &world,
                              &rotation,
                              scale);
    return result;
}

void service_request() noexcept {
    if (!busy()) {
        return;
    }
    std::array<float, 3> camera{};
    std::array<float, 3> forward{};
    const bool hasCamera = teleport::current_camera_pose(camera, forward);

    AcquireSRWLockExclusive(&g_requestLock);
    const std::size_t total = g_request.line ? g_request.tags.size() : g_request.amount;
    if (g_request.tags.empty() || g_request.cursor >= total) {
        g_request = {};
        ReleaseSRWLockExclusive(&g_requestLock);
        return;
    }

    const std::uint32_t tag =
        g_request.line ? g_request.tags[g_request.cursor] : g_request.tags.front();
    const bool needsCamera = g_request.origin == Origin::surfaceRaycast
                             || g_request.origin == Origin::cameraRay || g_request.line
                             || (g_request.settings.useCameraRotation
                                 && !g_request.settings.overrideRotation);
    if (needsCamera && !hasCamera) {
        g_request = {};
        ReleaseSRWLockExclusive(&g_requestLock);
        publish_spawn_observation(tag, kInvalidDatum, SpawnOutcome::cameraUnavailable, "place");
        return;
    }
    std::array<float, 3> position{};
    bool placed = false;
    SpawnOutcome placementFailure = SpawnOutcome::surfaceMiss;
    switch (g_request.origin) {
    case Origin::player:
        placed = teleport::current_position(position);
        placementFailure = SpawnOutcome::playerUnavailable;
        break;
    case Origin::surfaceRaycast:
        placed = crosshair_hit(g_request.settings.rayDistance, camera, forward, position);
        placementFailure = SpawnOutcome::surfaceMiss;
        break;
    case Origin::cameraRay:
        position = {camera[0] + forward[0] * g_request.settings.rayDistance,
                    camera[1] + forward[1] * g_request.settings.rayDistance,
                    camera[2] + forward[2] * g_request.settings.rayDistance};
        placed = std::all_of(
            position.begin(), position.end(), [](float value) { return std::isfinite(value); });
        placementFailure = SpawnOutcome::cameraUnavailable;
        break;
    case Origin::world:
        position = g_request.absolutePosition;
        placed = std::all_of(
            position.begin(), position.end(), [](float value) { return std::isfinite(value); });
        placementFailure = SpawnOutcome::factoryRejected;
        break;
    }
    if (!placed) {
        g_request = {};
        ReleaseSRWLockExclusive(&g_requestLock);
        publish_spawn_observation(tag, kInvalidDatum, placementFailure, "place");
        return;
    }

    const Settings settings = g_request.settings;
    const std::size_t cursor = g_request.cursor++;
    g_request.lastProgress = GetTickCount64();
    if (g_request.line) {
        const std::uint32_t width = (std::max)(g_request.itemsPerRow, 1U);
        const float horizontalLength = std::sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
        const std::array<float, 3> rowForward =
            horizontalLength > 1.0e-5F ? std::array<float, 3>{forward[0] / horizontalLength,
                                                              forward[1] / horizontalLength,
                                                              0.0F}
                                       : std::array<float, 3>{1.0F, 0.0F, 0.0F};
        const std::array<float, 3> right{-rowForward[1], rowForward[0], 0.0F};
        const float column = static_cast<float>(cursor % width);
        const float row = static_cast<float>(cursor / width);
        position[0] +=
            right[0] * column * g_request.spacing + rowForward[0] * row * g_request.spacing;
        position[1] +=
            right[1] * column * g_request.spacing + rowForward[1] * row * g_request.spacing;
    }
    if (g_request.cursor >= total) {
        g_request = {};
    }
    ReleaseSRWLockExclusive(&g_requestLock);

    position[0] += settings.offset[0];
    position[1] += settings.offset[1];
    position[2] += settings.offset[2] + settings.lift;
    std::array<float, 4> rotation = settings.rotation;
    if (!settings.overrideRotation) {
        rotation = {0.0F, 0.0F, 0.0F, 1.0F};
        if (settings.useCameraRotation) {
            (void)camera_rotation(forward, rotation);
        }
    }
    (void)spawn_one(tag, position, rotation, settings.scale);
}

void poll_shortcuts() noexcept {
    const client::spawn::Keybinds keybinds = client::spawn::get();
    DWORD foregroundProcess = 0;
    const HWND foreground = GetForegroundWindow();
    if (foreground != nullptr) {
        (void)GetWindowThreadProcessId(foreground, &foregroundProcess);
    }
    const bool blocked =
        foregroundProcess != GetCurrentProcessId() || core::ui::runtime::snapshot().visible;

    for (std::size_t index = 0; index < keybinds.virtualKeys.size(); ++index) {
        const std::uint32_t key = keybinds.virtualKeys[index];
        const bool down =
            key != client::spawn::kNoKey && (GetAsyncKeyState(static_cast<int>(key)) & 0x8000) != 0;
        if (blocked) {
            g_shortcutDown[index].store(down, std::memory_order_relaxed);
            continue;
        }
        if (!down || g_shortcutDown[index].exchange(true, std::memory_order_acq_rel)) {
            if (!down) {
                g_shortcutDown[index].store(false, std::memory_order_relaxed);
            }
            continue;
        }

        Shortcut shortcut{};
        AcquireSRWLockShared(&g_shortcutLock);
        shortcut = g_shortcuts[index];
        ReleaseSRWLockShared(&g_shortcutLock);
        if (shortcut.tag == kInvalidDatum || shortcut.amount == 0 || busy()) {
            continue;
        }
        const Origin origin = (index & 1U) == 0 ? Origin::player : Origin::surfaceRaycast;
        (void)request(shortcut.tag, origin, shortcut.amount, shortcut.settings);
    }
}

void __fastcall player_component_update(void* object, void* input, void* authored) noexcept {
    const auto next = reinterpret_cast<PlayerComponentUpdate>(
        g_hooks[static_cast<std::size_t>(HookSlot::update)].original);
    if (next != nullptr) {
        next(object, input, authored);
    }
    if (teleport::is_controlled_object(object)) {
        poll_shortcuts();
        service_activations();
        service_request();
    }
}

void __fastcall object_transform_observer(void* object, const float* transform) noexcept {
    const auto next = reinterpret_cast<ObjectTransform>(
        g_hooks[static_cast<std::size_t>(HookSlot::transform)].original);
    if (next != nullptr) {
        next(object, transform);
    }
    if (g_installed.load(std::memory_order_relaxed)) {
        observe_transform(object, transform);
    }
}

[[nodiscard]] bool valid_settings(const Settings& settings) noexcept {
    return std::isfinite(settings.lift) && std::isfinite(settings.rayDistance)
           && settings.rayDistance > 0.0F && std::isfinite(settings.scale) && settings.scale > 0.0F
           && std::all_of(settings.offset.begin(),
                          settings.offset.end(),
                          [](float value) { return std::isfinite(value); })
           && std::all_of(settings.rotation.begin(), settings.rotation.end(), [](float value) {
                  return std::isfinite(value);
              });
}

} // namespace

bool install() noexcept {
    if (g_installed.load(std::memory_order_acquire)) {
        return true;
    }
    std::byte* const initialize =
        scan_main_image_unique(kPlacementInitialize, "spawn_placement_initialize");
    std::byte* const direct = scan_main_image_unique(kDirectInitialize, "spawn_direct_initialize");
    std::byte* const factory = scan_main_image_unique(kObjectFactory, "spawn_object_factory");
    std::byte* const transform = scan_main_image_unique(kObjectTransform, "spawn_object_transform");
    std::byte* const raycast = scan_main_image_unique(kWorldRaycast, "spawn_world_raycast");
    std::byte* const update =
        scan_main_image_unique(kPlayerComponentUpdate, "spawn_player_component_update");
    if (initialize == nullptr || direct == nullptr || factory == nullptr || transform == nullptr
        || raycast == nullptr || update == nullptr) {
        core::log::write(core::log::Channel::client,
                         core::log::Level::warn,
                         "ev=spawn stage=install result=fail reason=target");
        return false;
    }
    g_initialize = reinterpret_cast<PlacementInitialize>(initialize);
    g_directInitialize = reinterpret_cast<PlacementInitialize>(direct);
    g_factory = reinterpret_cast<ObjectFactory>(factory);
    g_transform = reinterpret_cast<ObjectTransform>(transform);
    g_resolver = reinterpret_cast<TagResolver>(
        resolve_relative(direct + kResolverCallOperand, direct + kResolverCallEnd));
    g_raycast = reinterpret_cast<WorldRaycast>(raycast);
    g_gameModule = GetModuleHandleW(nullptr);
    if (g_resolver == nullptr || g_gameModule == nullptr
        || !hooking::detour::install({update, reinterpret_cast<void*>(&player_component_update)},
                                     g_hooks[static_cast<std::size_t>(HookSlot::update)])) {
        uninstall();
        core::log::write(core::log::Channel::client,
                         core::log::Level::warn,
                         "ev=spawn stage=install result=fail reason=attach");
        return false;
    }
    const bool observing =
        hooking::detour::install({transform, reinterpret_cast<void*>(&object_transform_observer)},
                                 g_hooks[static_cast<std::size_t>(HookSlot::transform)]);
    if (!observing) {
        core::log::write(core::log::Channel::client,
                         core::log::Level::warn,
                         "ev=spawn stage=transform_observer result=fail reason=attach");
    }
    clear_transform_observations();
    g_installed.store(true, std::memory_order_release);
    core::log::write(
        core::log::Channel::client, core::log::Level::info, "ev=spawn stage=install result=ok");
    return true;
}

void uninstall() noexcept {
    g_installed.store(false, std::memory_order_release);
    cancel();
    const bool allAttached =
        std::all_of(g_hooks.begin(), g_hooks.end(), [](const auto& hook) { return hook.attached; });
    if (allAttached) {
        (void)hooking::detour::uninstall(g_hooks);
    } else {
        for (hooking::detour::Handle& hook : g_hooks) {
            if (hook.attached) {
                (void)hooking::detour::uninstall(hook);
            }
        }
    }
    g_hooks = {};
    g_initialize = nullptr;
    g_directInitialize = nullptr;
    g_factory = nullptr;
    g_transform = nullptr;
    g_resolver = nullptr;
    g_raycast = nullptr;
    g_gameModule = nullptr;
    AcquireSRWLockExclusive(&g_activationLock);
    g_activations.clear();
    ReleaseSRWLockExclusive(&g_activationLock);
    AcquireSRWLockExclusive(&g_shortcutLock);
    g_shortcuts = {};
    ReleaseSRWLockExclusive(&g_shortcutLock);
    for (std::atomic_bool& down : g_shortcutDown) {
        down.store(false, std::memory_order_relaxed);
    }
    AcquireSRWLockExclusive(&g_observationLock);
    g_spawnObservation = {};
    ReleaseSRWLockExclusive(&g_observationLock);
    clear_transform_observations();
}

bool ready() noexcept {
    return g_installed.load(std::memory_order_acquire);
}

bool busy() noexcept {
    std::uint32_t expiredTag = kInvalidDatum;
    AcquireSRWLockExclusive(&g_requestLock);
    if (!g_request.tags.empty() && GetTickCount64() - g_request.lastProgress >= kRequestTimeoutMs) {
        const std::size_t index = g_request.line ? g_request.cursor : 0;
        if (index < g_request.tags.size()) {
            expiredTag = g_request.tags[index];
        }
        g_request = {};
    }
    const bool value = !g_request.tags.empty();
    ReleaseSRWLockExclusive(&g_requestLock);
    if (expiredTag != kInvalidDatum) {
        publish_spawn_observation(expiredTag, kInvalidDatum, SpawnOutcome::timedOut, "timeout");
    }
    return value;
}

bool is_tag_resident(std::uint32_t tag) noexcept {
    if (!ready() || tag == kInvalidDatum || g_resolver == nullptr) {
        return false;
    }
    __try {
        return g_resolver(tag) != nullptr;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

bool object_live(std::uint32_t handle) noexcept {
    return ready() && resolve_object(handle) != nullptr;
}

bool object_type(std::uint32_t tag, std::uint8_t& type) noexcept {
    type = 0;
    if (!is_tag_resident(tag)) {
        return false;
    }
    __try {
        const std::byte* const definition = g_resolver(tag);
        return definition != nullptr && safe_read(definition + kDefinitionObjectType, type);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

bool visit_world_objects(std::span<const WorldObjectDefinition> definitions,
                         void* context,
                         WorldObjectVisitor visitor,
                         WorldObjectScan& scan) noexcept {
    scan = {};
    if (!ready() || definitions.empty() || visitor == nullptr || g_resolver == nullptr
        || g_gameModule == nullptr) {
        return false;
    }

    std::vector<ResolvedWorldDefinition> resolved;
    resolved.reserve(definitions.size());
    for (const WorldObjectDefinition& definition : definitions) {
        if (definition.tag == 0 || definition.tag == kInvalidDatum) {
            continue;
        }
        const std::byte* const address = safe_resolve_definition(definition.tag);
        if (address != nullptr) {
            resolved.push_back({definition, address});
        }
    }
    std::sort(resolved.begin(), resolved.end(), [](const auto& left, const auto& right) {
        return left.definition.tag < right.definition.tag;
    });
    resolved.erase(std::unique(resolved.begin(),
                               resolved.end(),
                               [](const auto& left, const auto& right) {
                                   return left.definition.tag == right.definition.tag;
                               }),
                   resolved.end());
    if (resolved.empty()) {
        return false;
    }

    std::vector<const ResolvedWorldDefinition*> byAddress;
    byAddress.reserve(resolved.size());
    for (const ResolvedWorldDefinition& definition : resolved) {
        byAddress.push_back(&definition);
    }
    std::sort(byAddress.begin(), byAddress.end(), [](const auto* left, const auto* right) {
        return reinterpret_cast<std::uintptr_t>(left->address)
               < reinterpret_cast<std::uintptr_t>(right->address);
    });

    std::byte* const descriptor =
        reinterpret_cast<std::byte*>(g_gameModule) + kObjectDatumDescriptorRva;
    std::byte* base = nullptr;
    std::uint32_t stride = 0;
    if (!safe_read(descriptor + kObjectDatumBaseOffset, base)
        || !safe_read(descriptor + kObjectDatumStrideOffset, stride) || base == nullptr
        || stride != kObjectDatumBytes) {
        return false;
    }

    for (std::size_t slot = 0; slot < kObjectDatumCapacity; ++slot) {
        ++scan.slotsScanned;
        std::byte* const object = base + slot * stride;
        std::uint32_t before = kInvalidDatum;
        if (!safe_read(object + kObjectHandleOffset, before) || before == kInvalidDatum
            || (before & 0x1FFFU) != slot) {
            continue;
        }
        ++scan.liveHandles;

        std::array<std::byte, kObjectDatumBytes> snapshot{};
        std::uint32_t after = kInvalidDatum;
        if (!safe_read(object, snapshot) || !safe_read(object + kObjectHandleOffset, after)
            || before != after) {
            ++scan.unstableObjects;
            continue;
        }

        const ResolvedWorldDefinition* selected = nullptr;
        bool ambiguous = false;
        bool matchedTag = false;
        bool matchedPointer = false;
        for (std::size_t offset = 0; offset + sizeof(std::uint32_t) <= snapshot.size();
             offset += alignof(std::uint32_t)) {
            if (offset == kObjectHandleOffset) {
                continue;
            }
            std::uint32_t value = 0;
            std::memcpy(&value, snapshot.data() + offset, sizeof value);
            const ResolvedWorldDefinition* const candidate =
                find_world_definition_by_tag(resolved, value);
            if (candidate != nullptr) {
                consider_world_definition(candidate, selected, ambiguous);
                matchedTag = matchedTag || (!ambiguous && selected == candidate);
            }
        }
        for (std::size_t offset = 0; offset + sizeof(const std::byte*) <= snapshot.size();
             offset += alignof(const std::byte*)) {
            const std::byte* value = nullptr;
            std::memcpy(&value, snapshot.data() + offset, sizeof value);
            const ResolvedWorldDefinition* const candidate =
                find_world_definition_by_address(byAddress, value);
            if (candidate != nullptr) {
                consider_world_definition(candidate, selected, ambiguous);
                matchedPointer = matchedPointer || (!ambiguous && selected == candidate);
            }
        }
        if (ambiguous) {
            ++scan.ambiguousObjects;
            continue;
        }
        if (selected == nullptr) {
            continue;
        }

        WorldObjectObservation observation{};
        observation.handle = before;
        observation.tag = selected->definition.tag;
        observation.objectType = selected->definition.objectType;
        observation.identity = matchedTag && matchedPointer ? WorldObjectIdentity::tagAndPointer
                               : matchedPointer             ? WorldObjectIdentity::definitionPointer
                                                            : WorldObjectIdentity::definitionTag;
        if (observed_transform(before, observation)) {
            ++scan.observedTransforms;
        }
        ++scan.matchedObjects;
        if (!visitor(context, observation)) {
            break;
        }
    }
    return true;
}

SpawnObservation last_spawn_observation() noexcept {
    AcquireSRWLockShared(&g_observationLock);
    const SpawnObservation result = g_spawnObservation;
    ReleaseSRWLockShared(&g_observationLock);
    return result;
}

std::string_view spawn_outcome_text(SpawnOutcome outcome) noexcept {
    return outcome_label(outcome);
}

bool probe_crosshair(float distance, RaycastProbe& output) noexcept {
    output = {};
    output.fraction = 1.0F;
    output.material = -1;
    if (!ready() || !std::isfinite(distance) || distance <= 0.0F) {
        return false;
    }

    std::array<float, 3> forward{};
    if (!teleport::current_camera_pose(output.start, forward)) {
        core::log::write(core::log::Channel::client,
                         core::log::Level::warn,
                         "ev=spawn stage=raycast result=unavailable reason=camera");
        return false;
    }
    output.end = {output.start[0] + forward[0] * distance,
                  output.start[1] + forward[1] * distance,
                  output.start[2] + forward[2] * distance};
    output.hit = crosshair_hit(distance,
                               output.start,
                               forward,
                               output.position,
                               &output.fraction,
                               &output.material,
                               &output.nativeResult,
                               &output.outputChanged);
    std::array<char, 384> line{};
    const int written = std::snprintf(
        line.data(),
        line.size(),
        "ev=spawn stage=raycast result=%s native=%u changed=%u fraction=%.6f material=%d "
        "start=%.3f,%.3f,%.3f end=%.3f,%.3f,%.3f output=%.3f,%.3f,%.3f",
        output.hit ? "hit" : "miss",
        output.nativeResult ? 1U : 0U,
        output.outputChanged ? 1U : 0U,
        static_cast<double>(output.fraction),
        output.material,
        static_cast<double>(output.start[0]),
        static_cast<double>(output.start[1]),
        static_cast<double>(output.start[2]),
        static_cast<double>(output.end[0]),
        static_cast<double>(output.end[1]),
        static_cast<double>(output.end[2]),
        static_cast<double>(output.position[0]),
        static_cast<double>(output.position[1]),
        static_cast<double>(output.position[2]));
    if (written > 0) {
        core::log::write(core::log::Channel::client,
                         output.hit ? core::log::Level::info : core::log::Level::warn,
                         {line.data(), static_cast<std::size_t>(written)});
    }
    return true;
}

bool request(std::uint32_t tag,
             Origin origin,
             std::uint32_t amount,
             const Settings& settings) noexcept {
    if (!ready() || origin == Origin::world || !is_tag_resident(tag) || amount == 0
        || amount > kMaximumAmount || !valid_settings(settings)) {
        return false;
    }
    AcquireSRWLockExclusive(&g_requestLock);
    if (!g_request.tags.empty()) {
        ReleaseSRWLockExclusive(&g_requestLock);
        return false;
    }
    g_request = {};
    g_request.tags.push_back(tag);
    g_request.settings = settings;
    g_request.origin = origin;
    g_request.amount = amount;
    g_request.lastProgress = GetTickCount64();
    ReleaseSRWLockExclusive(&g_requestLock);
    return true;
}

bool request_at(std::uint32_t tag,
                const std::array<float, 3>& position,
                const std::array<float, 4>& rotation,
                float scale) noexcept {
    Settings settings{};
    settings.lift = 0.0F;
    settings.scale = scale;
    settings.rotation = rotation;
    settings.overrideRotation = true;
    if (!ready() || !is_tag_resident(tag) || !valid_settings(settings)
        || !std::all_of(
            position.begin(), position.end(), [](float value) { return std::isfinite(value); })) {
        return false;
    }
    AcquireSRWLockExclusive(&g_requestLock);
    if (!g_request.tags.empty()) {
        ReleaseSRWLockExclusive(&g_requestLock);
        return false;
    }
    g_request = {};
    g_request.tags.push_back(tag);
    g_request.settings = settings;
    g_request.absolutePosition = position;
    g_request.origin = Origin::world;
    g_request.amount = 1;
    g_request.lastProgress = GetTickCount64();
    ReleaseSRWLockExclusive(&g_requestLock);
    return true;
}

bool request_transform(std::uint32_t handle,
                       const std::array<float, 3>& position,
                       const std::array<float, 4>& rotation,
                       float scale) noexcept {
    const TransformRequest request{handle, position, rotation, scale};
    return request_transforms(std::span(&request, 1));
}

bool request_transforms(std::span<const TransformRequest> requests) noexcept {
    if (!ready() || requests.empty() || requests.size() > kActivationCapacity) {
        return false;
    }
    std::array<Activation, kActivationCapacity> pending{};
    for (std::size_t index = 0; index < requests.size(); ++index) {
        const TransformRequest& request = requests[index];
        if (request.handle == kInvalidDatum || !object_live(request.handle)
            || !std::isfinite(request.scale) || request.scale <= 0.0F
            || !std::all_of(request.position.begin(),
                            request.position.end(),
                            [](float value) { return std::isfinite(value); })
            || !std::all_of(request.rotation.begin(), request.rotation.end(), [](float value) {
                   return std::isfinite(value);
               })) {
            return false;
        }
        pending[index].handle = request.handle;
        std::copy(
            request.rotation.begin(), request.rotation.end(), pending[index].transform.begin());
        std::copy(
            request.position.begin(), request.position.end(), pending[index].transform.begin() + 4);
        pending[index].transform[7] = request.scale;
    }
    AcquireSRWLockExclusive(&g_activationLock);
    const bool queued = g_activations.append(std::span(pending).first(requests.size()));
    ReleaseSRWLockExclusive(&g_activationLock);
    return queued;
}

bool request_line(std::span<const std::uint32_t> tags,
                  Origin origin,
                  std::uint32_t itemsPerRow,
                  float spacing,
                  const Settings& settings) noexcept {
    if (!ready() || tags.empty() || tags.size() > kMaximumLineItems || itemsPerRow == 0
        || !std::isfinite(spacing) || spacing <= 0.0F || !valid_settings(settings)) {
        return false;
    }
    AcquireSRWLockExclusive(&g_requestLock);
    if (!g_request.tags.empty()) {
        ReleaseSRWLockExclusive(&g_requestLock);
        return false;
    }
    g_request = {};
    g_request.tags.assign(tags.begin(), tags.end());
    g_request.settings = settings;
    g_request.origin = origin;
    g_request.itemsPerRow = itemsPerRow;
    g_request.spacing = spacing;
    g_request.line = true;
    g_request.lastProgress = GetTickCount64();
    ReleaseSRWLockExclusive(&g_requestLock);
    return true;
}

void configure_shortcut(client::spawn::Action action,
                        std::uint32_t tag,
                        std::uint32_t amount,
                        const Settings& settings) noexcept {
    const std::size_t index = static_cast<std::size_t>(action);
    if (index >= g_shortcuts.size()) {
        return;
    }
    Shortcut shortcut{};
    if (tag != kInvalidDatum && amount > 0 && amount <= kMaximumAmount
        && valid_settings(settings)) {
        shortcut.tag = tag;
        shortcut.amount = amount;
        shortcut.settings = settings;
    }
    AcquireSRWLockExclusive(&g_shortcutLock);
    g_shortcuts[index] = shortcut;
    ReleaseSRWLockExclusive(&g_shortcutLock);
}

void cancel() noexcept {
    AcquireSRWLockExclusive(&g_requestLock);
    g_request = {};
    ReleaseSRWLockExclusive(&g_requestLock);
}

} // namespace sunrise::client::hooks::spawn
