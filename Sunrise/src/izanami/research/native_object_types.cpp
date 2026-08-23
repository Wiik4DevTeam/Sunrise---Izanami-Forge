#include "native_object_types.h"

namespace sunrise::izanami::research {
namespace {

constexpr std::array kObjectTypes{
    NativeObjectTypeRecord{0, "Inherited", "definition", "Behavior inherited from parent data."},
    NativeObjectTypeRecord{1,
                           "StaticMesh",
                           "static geometry",
                           "Factory spawn and bundled collision are field-proven for 0x80B6C246; "
                           "other definitions remain asset-specific.",
                           ObjectTypeEvidence::fieldCorrelated},
    NativeObjectTypeRecord{2,
                           "PropSimpleDeprecated",
                           "prop",
                           "Legacy simple prop; native factory path is available when resident.",
                           ObjectTypeEvidence::fieldCorrelated},
    NativeObjectTypeRecord{3,
                           "PropExpensiveDeprecated",
                           "prop",
                           "Legacy complex prop; dependencies may be activity-local."},
    NativeObjectTypeRecord{4,
                           "PropCosmeticStatic",
                           "cosmetic prop",
                           "Static decoration or world effect; collision is not implied."},
    NativeObjectTypeRecord{5,
                           "PropCosmeticMovable",
                           "cosmetic prop",
                           "Movable decoration; may require post-factory activation.",
                           ObjectTypeEvidence::fieldCorrelated},
    NativeObjectTypeRecord{6,
                           "PropCosmeticMovableGarbage",
                           "cosmetic prop",
                           "Movable debris/garbage family; behavior is dependency-specific."},
    NativeObjectTypeRecord{
        7,
        "PropNetworkedStatic",
        "networked prop",
        "Static network-aware prop; local factory spawn does not prove replication."},
    NativeObjectTypeRecord{8,
                           "PropNetworkedMovable",
                           "networked prop",
                           "Movable/explodable family; receives a post-factory transform retry."},
    NativeObjectTypeRecord{9,
                           "PropCinematic",
                           "cinematic prop",
                           "Cinematic-owned prop; scripts may overwrite its transform.",
                           ObjectTypeEvidence::fieldCorrelated},
    NativeObjectTypeRecord{10,
                           "Speedtree",
                           "vegetation",
                           "Vegetation entity; rendering and collision can be separate resources."},
    NativeObjectTypeRecord{11,
                           "Interactive",
                           "gameplay",
                           "Interactive entity; receives a post-factory transform retry.",
                           ObjectTypeEvidence::fieldCorrelated},
    NativeObjectTypeRecord{
        12,
        "Biped",
        "actor",
        "Guardian, enemy, or NPC family; activity authority may reject local behavior."},
    NativeObjectTypeRecord{
        13,
        "Creature",
        "actor",
        "Creature actor; complete behavior requires resident dependencies and authority."},
    NativeObjectTypeRecord{14, "Weapon", "equipment", "Weapon prop/actor definition."},
    NativeObjectTypeRecord{
        15, "Vehicle", "vehicle", "Sparrow, Pike, ship, or related vehicle definition."},
    NativeObjectTypeRecord{16, "Turret", "vehicle", "Vehicle-like turret entity."},
    NativeObjectTypeRecord{17,
                           "Emitter",
                           "effect",
                           "Effect or interactive projectile emitter; collision is uncommon.",
                           ObjectTypeEvidence::fieldCorrelated},
    NativeObjectTypeRecord{
        18,
        "Projectile",
        "projectile",
        "Projectile definition; may execute gameplay immediately after creation."},
    NativeObjectTypeRecord{19, "Item", "item", "Generic item entity."},
    NativeObjectTypeRecord{
        20, "ItemAmmo", "item", "Ammo item; receives a post-factory transform retry."},
    NativeObjectTypeRecord{
        21, "ItemLoot", "item", "Loot item; receives a post-factory transform retry."},
    NativeObjectTypeRecord{22, "Gear", "equipment", "Gear entity definition."},
    NativeObjectTypeRecord{23, "HopOn", "attachment", "Mount/attachment root."},
    NativeObjectTypeRecord{24, "HopOnGearBiped", "attachment", "Biped attachment definition."},
    NativeObjectTypeRecord{25, "HopOnGearWeapon", "attachment", "Weapon attachment definition."},
    NativeObjectTypeRecord{26, "HopOnGearShip", "attachment", "Ship attachment definition."},
    NativeObjectTypeRecord{27, "HopOnGearSparrow", "attachment", "Sparrow attachment definition."},
    NativeObjectTypeRecord{28,
                           "System",
                           "runtime system",
                           "World/activity system node; unsafe as a general-purpose prop.",
                           ObjectTypeEvidence::fieldCorrelated},
};

} // namespace

std::span<const NativeObjectTypeRecord> native_object_types() noexcept {
    return kObjectTypes;
}

std::string_view native_object_type_name(std::uint8_t value) noexcept {
    return value < kObjectTypes.size() ? kObjectTypes[value].name : std::string_view{"Unknown"};
}

std::string_view object_type_evidence_text(ObjectTypeEvidence value) noexcept {
    switch (value) {
    case ObjectTypeEvidence::sourceNamed:
        return "source named";
    case ObjectTypeEvidence::fieldCorrelated:
        return "field correlated";
    }
    return "unknown";
}

} // namespace sunrise::izanami::research
