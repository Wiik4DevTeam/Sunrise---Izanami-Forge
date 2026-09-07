#include "custom_package_builder.h"

#include <Windows.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "../../client/content/items/packages/internal.h"
#include "../../core/logging/log.h"
#include "../../middleware/compression/oodle/runtime.h"
#include "../../middleware/content/packages/reader/internal.h"
#include "../../middleware/content/packages/reader/reader.h"
#include "../../middleware/content/packages/tables/definition_index_table.h"
#include "../../middleware/crypto/aes_gcm_decrypt.h"
#include "../../middleware/crypto/aes_gcm_encrypt.h"
#include "../../middleware/crypto/sha1.h"
#include "../../state/content/content_catalog.h"

namespace sunrise::izanami::core {
namespace log = ::sunrise::core::log;
namespace path = ::sunrise::core::path;
} // namespace sunrise::izanami::core

namespace sunrise::izanami::runtime::custom_package_builder {
namespace {

namespace compression = middleware::compression::oodle;
namespace crypto = middleware::crypto::aes_gcm;
namespace sha1 = middleware::crypto::sha1;
namespace item_packages = client::content::items::packages;
namespace reader = middleware::content::packages::reader;
namespace layout = middleware::content::packages::reader::layout;
namespace tables = middleware::content::packages::tables;

constexpr std::size_t kFileAlignment = 0x1000;
constexpr std::size_t kHeaderFileSizeOffset = 0x164;
constexpr std::byte kNonceBranchByte{0xF9};
constexpr std::uint64_t kMaximumPatchBytes = 128ULL * 1024ULL * 1024ULL;
constexpr int kLzhCompressor = 0;
constexpr int kKrakenCompressor = 8;

/** One pending edge in the bounded map-root dependency walk. */
struct MapNode {
    std::uint32_t tag{};
    std::uint8_t depth{};
};

/** Evidence collected while deriving a Tower scenery-replacement patch. */
struct TowerPatchStats {
    std::size_t nodes{};
    std::size_t tables{};
    std::size_t localTables{};
    std::size_t staticPlacements{};
    std::size_t mutatedPlacements{};
    std::size_t preservedEntityPlacements{};
    std::size_t preservedVisibilityBundlePlacements{};
    std::size_t preservedBaseDirectHavokPlacements{};
    std::size_t entityModelPlacements{};
    std::size_t preservedEntityModelHavokReferences{};
    std::size_t suppressedStandaloneEntities{};
    std::size_t preservedStandaloneInteractiveEntities{};
    std::size_t preservedStandaloneSystemEntities{};
    std::size_t suppressedComponentSceneryEntities{};
    std::size_t preservedComponentInteractiveEntities{};
    std::size_t preservedComponentSystemEntities{};
    std::size_t substitutedStaticMeshCollisionReferences{};
    std::size_t skippedTables{};
};

/** Evidence collected while reducing Pandora's VFX-test map branch to an authored draft. */
struct PandoraSkyDraftStats {
    std::size_t nodes{};
    std::size_t tables{};
    std::size_t placements{};
    std::size_t suppressedPlacements{};
    std::size_t preservedSkyPlacements{};
    std::size_t baseplateTiles{};
    std::size_t preservedInfrastructurePlacements{};
    std::size_t touchedTables{};
    float tileSpacing{};
};

struct PandoraBaseplateTile {
    std::uint32_t tableTag{};
    std::uint32_t sourceParentTag{};
    float gridOffset{};
};

struct StandaloneEntityExpectation {
    std::uint8_t objectType{};
    std::size_t expectedPlacements{};
};

struct ComponentSceneryClassExpectation {
    std::uint32_t resourceClass{};
    std::size_t expectedPlacements{};
};

constexpr std::string_view kPandoraMapRoot = "map:pandora:root";
constexpr std::string_view kTowerMapRoot = "map:city_tower_d2:root";
constexpr std::uint16_t kPandoraMapPackageId = 0x0687U;
/** The first Pandora branch contains the resident VFX shade-test map. */
constexpr std::uint32_t kPandoraVfxMapBranch = 0x8150E00AU;
constexpr std::uint32_t kPandoraVfxSkyTable = 0x8150E150U;
constexpr std::uint32_t kPandoraBaseplateStaticTable = 0x8150E15BU;
/** Three first-bubble aggregate slots form a centered strip without adding package entries. */
constexpr std::array kPandoraBaseplateTiles{
    PandoraBaseplateTile{0x8150E018U, 0x8150E017U, -1.0F},
    PandoraBaseplateTile{kPandoraBaseplateStaticTable, 0x8150E15AU, 0.0F},
    PandoraBaseplateTile{0x8150E14EU, 0x8150E14DU, 1.0F},
};
constexpr std::uint32_t kSkyObjectPlacementResourceClass = 0x80806F91U;
constexpr std::uint32_t kSkyObjectCollectionClass = 0x80806F95U;
constexpr std::size_t kSkyObjectCollectionOffset = 0x8;
constexpr std::uint16_t kTowerMapPackageId = 0x0369U;
/** Patch 8 is the highest field-proven Tower metadata slot. */
constexpr std::uint32_t kTowerPatchSlot = 8;
constexpr std::uint32_t kMapRootClass = 0x808091DEU;
constexpr std::uint32_t kMapDataTableClass = 0x808099D6U;
constexpr std::uint32_t kEntityDefinitionClass = 0x80809C0FU;
constexpr std::uint32_t kStaticMapResourceClass = 0x808071B3U;
constexpr std::uint32_t kTowerVisibilityBundleResourceClass = 0x80807246U;
constexpr std::uint32_t kTowerDirectHavokResourceClass = 0x8080929BU;
constexpr std::uint32_t kTowerEntityModelResourceClass = 0x80806DE0U;
constexpr std::uint32_t kTowerEntityModelHavokTag = 0x80C6D120U;
constexpr std::uint32_t kStaticMapParentClass = 0x80806EF4U;
constexpr std::uint32_t kStaticMeshInstancesClass = 0x8080966DU;
constexpr std::uint32_t kTerrainCompanionClass = 0x80809671U;
constexpr std::uint32_t kTowerStaticCollisionCompanion = 0x80ED3C17U;
constexpr std::size_t kTowerStaticCollisionReferenceOffset = 0x4B080;
constexpr std::uint32_t kTowerStaticCollisionOriginal = 0x80C6CEFEU;
constexpr std::uint32_t kTowerStaticCollisionSmallControl = 0x80ED2CE0U;
constexpr std::size_t kTowerStaticCollisionOriginalBytes = 2672;
constexpr std::size_t kTowerStaticCollisionSmallControlBytes = 960;
constexpr std::uint32_t kHavokPackfileMagic0 = 0x57E0E057U;
constexpr std::uint32_t kHavokPackfileMagic1 = 0x10C0C010U;
constexpr std::uint32_t kHavokPackfileVersion = 9;
constexpr std::size_t kHavokRootClassOffset = 0x11B;
constexpr std::string_view kHavokCompressedMeshRoot = "hkpBvCompressedMeshShape";
constexpr std::size_t kExpectedTowerVisibilityBundles = 6;
constexpr std::size_t kExpectedTowerBaseDirectHavokPlacements = 14;
constexpr std::size_t kExpectedTowerEntityPlacements = 227;
constexpr std::size_t kExpectedTowerEntityModelPlacements = 16;
constexpr std::size_t kExpectedTowerEntityModelHavokReferences = 15;
constexpr std::size_t kTowerEntityModelHavokOffset = 0x40;
constexpr std::size_t kEntityObjectTypeOffset = 0x96;
constexpr std::uint8_t kInteractiveObjectType = 11;
constexpr std::uint8_t kSystemObjectType = 28;
constexpr std::array kSuppressedStandaloneEntityTypes{
    StandaloneEntityExpectation{1, 102},
    StandaloneEntityExpectation{2, 29},
    StandaloneEntityExpectation{5, 22},
    StandaloneEntityExpectation{9, 4},
    StandaloneEntityExpectation{17, 53},
};
constexpr std::size_t kExpectedSuppressedStandaloneEntities = 210;
constexpr std::size_t kExpectedStandaloneInteractiveEntities = 9;
constexpr std::size_t kExpectedStandaloneSystemEntities = 8;
constexpr std::array kSuppressedComponentSceneryTypes{
    StandaloneEntityExpectation{1, 80},
    StandaloneEntityExpectation{2, 79},
    StandaloneEntityExpectation{5, 6},
};
constexpr std::array kSuppressedComponentSceneryClasses{
    ComponentSceneryClassExpectation{0x808038A0U, 110},
    ComponentSceneryClassExpectation{0x80805FA9U, 55},
};
constexpr std::size_t kExpectedSuppressedComponentSceneryEntities = 165;
constexpr std::size_t kExpectedComponentInteractiveEntities = 12;
constexpr std::size_t kExpectedComponentSystemEntities = 1159;
constexpr float kSuppressedStandaloneEntityHeight = -10000.0F;
constexpr float kSuppressedStandaloneEntityScale = 0.0001F;
constexpr std::size_t kMapGraphCapacity = 1024;
constexpr std::uint8_t kMapGraphDepth = 5;
constexpr std::size_t kAuthoredCatalogGraphCapacity = 4096;
constexpr std::uint8_t kAuthoredCatalogGraphDepth = 8;
constexpr std::size_t kMapTableArrayOffset = 0x8;
constexpr std::size_t kMapEntryStride = 0x90;
constexpr std::size_t kMapEntryRotationOffset = 0x10;
constexpr std::size_t kMapEntryTranslationOffset = 0x20;
constexpr std::size_t kMapEntryWorldIdOffset = 0x70;
constexpr std::size_t kMapEntryResourcePointerOffset = 0x78;
constexpr std::size_t kStaticMapParentOffset = 0x10;
constexpr std::size_t kMaximumMapEntries = 4096;
constexpr std::size_t kMaximumPlacementEdits = 32;
constexpr std::size_t kMaximumAuthoredPlacementEdits = 4096;
constexpr std::size_t kReportedPlacementCandidates = 12;
constexpr std::uint32_t kKnownTowerAggregateTable = 0x80ED22FBU;
constexpr std::uint32_t kKnownTowerAggregateEntry = 0;
constexpr std::uint32_t kKnownTowerAggregateParent = 0x80ED22FAU;
constexpr std::uint32_t kKnownTowerAggregatePayload = 0x80ED22F9U;
/** The field-verified six-instance VFX test baseplate, used as geometry rather than an activity. */
constexpr std::uint32_t kPandoraBaseplateStaticParent = 0x8150E15AU;
/** Shadowkeep inline-array identifiers inside the Tower aggregate payload. */
constexpr std::uint32_t kShadowkeepArrayMarker = 0x80809FBDU;
constexpr std::uint32_t kShadowkeepTransformClass = 0x808071A3U;
constexpr std::uint32_t kShadowkeepStaticClass = 0x8080967DU;
constexpr std::uint32_t kShadowkeepGroupClass = 0x80807190U;
constexpr std::size_t kShadowkeepArrayHeaderSize = 20;
constexpr std::size_t kShadowkeepTransformStride = 0x30;
constexpr std::size_t kShadowkeepStaticStride = sizeof(std::uint32_t);
constexpr std::size_t kShadowkeepGroupStride = 0x8;
constexpr std::size_t kTowerAggregatePayloadSize = 54112;
constexpr std::uint32_t kTowerAggregateTransformCount = 1057;
constexpr std::uint32_t kTowerAggregateStaticCount = 260;
constexpr std::uint32_t kTowerAggregateGroupCount = 260;
constexpr std::uint32_t kTowerLocalBaseplateGroup = 13;
constexpr std::uint32_t kTowerLocalBaseplateTransform = 122;
constexpr std::uint32_t kTowerLocalBaseplateStaticIndex = 13;
constexpr std::uint32_t kTowerLocalBaseplateMesh = 0x815B621CU;
constexpr std::array<std::uint32_t, 2> kTowerLocalBaseplateGroupWords{0x007A000EU, 0x0007000DU};
constexpr std::array<std::uint32_t, 12> kTowerLocalBaseplateTransformWords{
    0xB48BA305U,
    0xB4304A51U,
    0xBF7FFA34U,
    0x3C59C9FEU,
    0xC26328CCU,
    0x41B5D32EU,
    0x40FF813CU,
    0x3F800000U,
    0x3F800000U,
    0x3F800000U,
    0x00013CA8U,
    0x00000000U,
};

/** Fixed fields and offsets needed to rebuild one latest-patch file. */
struct PackageFile {
    std::vector<std::byte> bytes{};
    reader::Path stem{};
    reader::Path latestPath{};
    std::uint64_t entryTable{};
    std::uint64_t blockTable{};
    std::uint32_t entryCount{};
    std::uint32_t blockCount{};
    std::uint32_t latestPatch{};
    std::uint16_t packageId{};
};

/** One original patch file that remains the physical owner of one or more changed blocks. */
struct OwnerPatchFile {
    std::vector<std::byte> bytes{};
    reader::Path path{};
    std::uint64_t blockTable{};
    std::uint32_t blockCount{};
    std::uint32_t patchId{};
};

/** One decoded package block carrying one or more staged entry mutations. */
struct MutableBlock {
    std::uint32_t index{};
    std::vector<std::byte> decoded{};
    layout::BlockRecord record{};
};

/** Reports one package-authoring stage. */
void report(std::string_view stage,
            std::string_view result,
            std::uint16_t packageId = 0,
            std::uint32_t patch = 0,
            std::uint32_t block = 0,
            std::size_t bytes = 0) noexcept {
    std::array<char, core::log::kLineCapacity> line{};
    const int written = std::snprintf(
        line.data(),
        line.size(),
        "ev=izanami_package_build stage=%.*s result=%.*s package=0x%04X patch=%u block=%u "
        "bytes=%zu",
        static_cast<int>(stage.size()),
        stage.data(),
        static_cast<int>(result.size()),
        result.data(),
        static_cast<unsigned>(packageId),
        static_cast<unsigned>(patch),
        static_cast<unsigned>(block),
        bytes);
    if (written > 0) {
        core::log::write(core::log::Channel::client,
                         result == "ok" ? core::log::Level::info : core::log::Level::warn,
                         {line.data(), static_cast<std::size_t>(written)});
    }
}

/** Reports the bounded evidence behind one generated Tower patch. */
void report_tower_plan(std::string_view result,
                       std::uint16_t packageId,
                       const TowerPatchStats& stats) noexcept {
    std::array<char, core::log::kLineCapacity> line{};
    const int written =
        std::snprintf(line.data(),
                      line.size(),
                      "ev=izanami_tower_patch_plan result=%.*s package=0x%04X nodes=%zu tables=%zu "
                      "local_tables=%zu static=%zu mutated=%zu preserved_entities=%zu "
                      "preserved_visibility_bundles=%zu preserved_base_direct_havok=%zu "
                      "entity_models=%zu preserved_entity_model_havok=%zu "
                      "suppressed_standalone_entities=%zu preserved_standalone_interactive=%zu "
                      "preserved_standalone_system=%zu suppressed_component_scenery=%zu "
                      "preserved_component_interactive=%zu preserved_component_system=%zu "
                      "skipped=%zu",
                      static_cast<int>(result.size()),
                      result.data(),
                      static_cast<unsigned>(packageId),
                      stats.nodes,
                      stats.tables,
                      stats.localTables,
                      stats.staticPlacements,
                      stats.mutatedPlacements,
                      stats.preservedEntityPlacements,
                      stats.preservedVisibilityBundlePlacements,
                      stats.preservedBaseDirectHavokPlacements,
                      stats.entityModelPlacements,
                      stats.preservedEntityModelHavokReferences,
                      stats.suppressedStandaloneEntities,
                      stats.preservedStandaloneInteractiveEntities,
                      stats.preservedStandaloneSystemEntities,
                      stats.suppressedComponentSceneryEntities,
                      stats.preservedComponentInteractiveEntities,
                      stats.preservedComponentSystemEntities,
                      stats.skippedTables);
    if (written > 0) {
        core::log::write(core::log::Channel::client,
                         result == "ok" ? core::log::Level::info : core::log::Level::warn,
                         {line.data(), static_cast<std::size_t>(written)});
    }
}

/** Reports every native static placement changed by the current Tower composition. */
void report_tower_mutation(std::uint32_t tableTag,
                           std::size_t entry,
                           std::uint32_t sourceParent,
                           std::uint32_t targetParent,
                           const core::Transform& before,
                           const core::Transform& after) noexcept {
    std::array<char, core::log::kLineCapacity> line{};
    const int written =
        std::snprintf(line.data(),
                      line.size(),
                      "ev=izanami_tower_mutation table=0x%08X entry=%zu source_parent=0x%08X "
                      "target_parent=0x%08X "
                      "from=(%.3f,%.3f,%.3f,%.3f) to=(%.3f,%.3f,%.3f,%.3f)",
                      static_cast<unsigned>(tableTag),
                      entry,
                      static_cast<unsigned>(sourceParent),
                      static_cast<unsigned>(targetParent),
                      before.translation.x,
                      before.translation.y,
                      before.translation.z,
                      before.uniformScale,
                      after.translation.x,
                      after.translation.y,
                      after.translation.z,
                      after.uniformScale);
    if (written > 0) {
        core::log::write(core::log::Channel::client,
                         core::log::Level::info,
                         {line.data(), static_cast<std::size_t>(written)});
    }
}

/** Reports the smallest static-map payload candidates without dumping proprietary payload bytes. */
void report_tower_candidate(std::size_t rank, const StaticPlacementCandidate& candidate) noexcept {
    std::array<char, core::log::kLineCapacity> line{};
    const core::Transform& transform = candidate.binding.sourceTransform;
    const int written =
        std::snprintf(line.data(),
                      line.size(),
                      "ev=izanami_tower_candidate rank=%zu table=0x%08X entry=%u parent=0x%08X "
                      "entity=0x%08X data=0x%08X parent_bytes=%zu data_bytes=%zu "
                      "position=(%.3f,%.3f,%.3f) scale=%.3f",
                      rank,
                      static_cast<unsigned>(candidate.binding.tableTag),
                      static_cast<unsigned>(candidate.binding.entryIndex),
                      static_cast<unsigned>(candidate.binding.parentTag),
                      static_cast<unsigned>(candidate.entityTag),
                      static_cast<unsigned>(candidate.dataTag),
                      candidate.parentBytes,
                      candidate.dataBytes,
                      transform.translation.x,
                      transform.translation.y,
                      transform.translation.z,
                      transform.uniformScale);
    if (written > 0) {
        core::log::write(core::log::Channel::client,
                         core::log::Level::info,
                         {line.data(), static_cast<std::size_t>(written)});
    }
}

/** Reports the stored representation chosen for one authored package block. */
void report_block_encoding(std::uint32_t index,
                           std::size_t decodedBytes,
                           std::size_t storedBytes,
                           std::uint16_t flags,
                           int compressor) noexcept {
    std::array<char, core::log::kLineCapacity> line{};
    const int written =
        std::snprintf(line.data(),
                      line.size(),
                      "ev=izanami_block_encode block=%u decoded=%zu stored=%zu flags=0x%X "
                      "compressor=%d",
                      static_cast<unsigned>(index),
                      decodedBytes,
                      storedBytes,
                      static_cast<unsigned>(flags),
                      compressor);
    if (written > 0) {
        core::log::write(core::log::Channel::client,
                         core::log::Level::info,
                         {line.data(), static_cast<std::size_t>(written)});
    }
}

/** Maps the source block's Oodle 2.3 stream header to its compressor enum. */
[[nodiscard]] bool source_compressor(std::span<const std::byte> stream, int& compressor) noexcept {
    compressor = -1;
    if (stream.size() < 2 || stream[0] != std::byte{0x8C}) {
        return false;
    }
    const unsigned framing = std::to_integer<unsigned>(stream[1]);
    if (framing == 0x07) {
        compressor = kLzhCompressor;
        return true;
    }
    if (framing == 0x06) {
        compressor = kKrakenCompressor;
        return true;
    }
    return false;
}

/** Reports a non-secret prefix that identifies one Oodle stream's framing and codec. */
void report_oodle_stream(std::string_view kind,
                         std::uint32_t index,
                         std::span<const std::byte> stream) noexcept {
    std::array<unsigned, 8> prefix{};
    const std::size_t count = (std::min)(stream.size(), prefix.size());
    for (std::size_t byte = 0; byte < count; ++byte) {
        prefix[byte] = std::to_integer<unsigned>(stream[byte]);
    }
    std::array<char, core::log::kLineCapacity> line{};
    const int written = std::snprintf(line.data(),
                                      line.size(),
                                      "ev=izanami_oodle_stream kind=%.*s block=%u bytes=%zu prefix="
                                      "%02X%02X%02X%02X%02X%02X%02X%02X",
                                      static_cast<int>(kind.size()),
                                      kind.data(),
                                      static_cast<unsigned>(index),
                                      stream.size(),
                                      prefix[0],
                                      prefix[1],
                                      prefix[2],
                                      prefix[3],
                                      prefix[4],
                                      prefix[5],
                                      prefix[6],
                                      prefix[7]);
    if (written > 0) {
        core::log::write(core::log::Channel::client,
                         core::log::Level::info,
                         {line.data(), static_cast<std::size_t>(written)});
    }
}

template <typename Value>
[[nodiscard]] bool
read_value(std::span<const std::byte> bytes, std::size_t offset, Value& value) noexcept {
    value = {};
    if (offset > bytes.size() || bytes.size() - offset < sizeof value) {
        return false;
    }
    std::memcpy(&value, bytes.data() + offset, sizeof value);
    return true;
}

template <typename Value>
[[nodiscard]] bool
write_value(std::span<std::byte> bytes, std::size_t offset, const Value& value) noexcept {
    if (offset > bytes.size() || bytes.size() - offset < sizeof value) {
        return false;
    }
    std::memcpy(bytes.data() + offset, &value, sizeof value);
    return true;
}

/** Resolves a Tiger relative pointer without signed or size overflow. */
[[nodiscard]] bool relative_target(std::size_t base,
                                   std::int64_t relative,
                                   std::size_t limit,
                                   std::size_t& target) noexcept {
    if (base > limit) {
        return false;
    }
    if (relative < 0) {
        const std::uint64_t magnitude = static_cast<std::uint64_t>(-(relative + 1)) + 1U;
        if (magnitude > base) {
            return false;
        }
        target = base - static_cast<std::size_t>(magnitude);
    } else {
        const std::uint64_t magnitude = static_cast<std::uint64_t>(relative);
        if (magnitude > limit - base) {
            return false;
        }
        target = base + static_cast<std::size_t>(magnitude);
    }
    return target <= limit;
}

/** Validates the placement array shared by every installed map-data table. */
[[nodiscard]] bool map_table_layout(std::span<const std::byte> table,
                                    std::size_t& entriesOffset,
                                    std::uint32_t& count) noexcept {
    constexpr std::size_t kCountOffset = kMapTableArrayOffset;
    constexpr std::size_t kPointerOffset = kMapTableArrayOffset + sizeof(std::uint64_t);
    constexpr std::size_t kPointerBias = 0x10;
    entriesOffset = 0;
    count = 0;
    std::int64_t relative = 0;
    return read_value(table, kCountOffset, count) && count <= kMaximumMapEntries
           && read_value(table, kPointerOffset, relative)
           && table.size() >= kPointerOffset + kPointerBias
           && relative_target(kPointerOffset + kPointerBias, relative, table.size(), entriesOffset)
           && count <= (table.size() - entriesOffset) / kMapEntryStride;
}

/** Returns the inline resource location and class for one checked placement row. */
[[nodiscard]] bool map_resource(std::span<const std::byte> table,
                                std::size_t entryOffset,
                                std::size_t& resourceOffset,
                                std::uint32_t& resourceClass) noexcept {
    resourceOffset = 0;
    resourceClass = 0;
    if (entryOffset > table.size()
        || kMapEntryResourcePointerOffset + sizeof(std::int64_t) > table.size() - entryOffset) {
        return false;
    }
    const std::size_t pointerOffset = entryOffset + kMapEntryResourcePointerOffset;
    std::int64_t relative = 0;
    return read_value(table, pointerOffset, relative) && relative != 0
           && relative_target(pointerOffset, relative, table.size(), resourceOffset)
           && resourceOffset >= sizeof(resourceClass)
           && read_value(table, resourceOffset - sizeof(resourceClass), resourceClass);
}

/** Resolves one uniquely typed definition tag embedded in an inline map resource. */
[[nodiscard]] bool linked_resource_tag(std::span<const std::byte> table,
                                       std::size_t resourceOffset,
                                       const reader::Source& source,
                                       reader::Scratch& scratch,
                                       std::uint32_t expectedClass,
                                       std::uint32_t& linkedTag,
                                       std::vector<std::byte>& linkedBytes) noexcept {
    linkedTag = 0;
    linkedBytes.clear();
    if (resourceOffset > table.size()) {
        return false;
    }
    std::vector<std::byte> candidateBytes{};
    for (std::size_t offset = resourceOffset; offset + sizeof(std::uint32_t) <= table.size();
         offset += sizeof(std::uint32_t)) {
        std::uint32_t candidate = 0;
        std::uint32_t candidateClass = 0;
        if (!read_value(table, offset, candidate) || candidate < tables::kTagLowerBound
            || candidate >= tables::kTagUpperBound
            || !reader::read_tag(source, scratch, candidate, candidateBytes, candidateClass)
            || candidateClass != expectedClass) {
            continue;
        }
        if (linkedTag != 0 && linkedTag != candidate) {
            linkedTag = 0;
            linkedBytes.clear();
            return false;
        }
        linkedTag = candidate;
        linkedBytes = candidateBytes;
    }
    return linkedTag != 0 && !linkedBytes.empty();
}

/** Checks that one null-resource map row names an actual entity definition. */
[[nodiscard]] bool map_entity(std::span<const std::byte> table,
                              std::size_t entryOffset,
                              const reader::Source& source,
                              reader::Scratch& scratch,
                              std::vector<std::byte>& entityBytes) noexcept {
    const std::size_t pointerOffset = entryOffset + kMapEntryResourcePointerOffset;
    std::int64_t resourceRelative = 0;
    std::uint32_t entityTag = 0;
    if (!read_value(table, pointerOffset, resourceRelative) || resourceRelative != 0
        || !read_value(table, entryOffset, entityTag) || entityTag < tables::kTagLowerBound
        || entityTag >= tables::kTagUpperBound) {
        return false;
    }
    std::uint32_t entityClass = 0;
    return reader::read_tag(source, scratch, entityTag, entityBytes, entityClass)
           && entityClass == kEntityDefinitionClass;
}

/** Resolves the entity-definition owner shared by standalone and component-backed rows. */
[[nodiscard]] bool map_entity_owner(std::span<const std::byte> table,
                                    std::size_t entryOffset,
                                    const reader::Source& source,
                                    reader::Scratch& scratch,
                                    std::vector<std::byte>& entityBytes) noexcept {
    std::uint32_t entityTag = 0;
    if (!read_value(table, entryOffset, entityTag) || entityTag < tables::kTagLowerBound
        || entityTag >= tables::kTagUpperBound) {
        return false;
    }
    std::uint32_t entityClass = 0;
    return reader::read_tag(source, scratch, entityTag, entityBytes, entityClass)
           && entityClass == kEntityDefinitionClass;
}

/** Reads the object type from one source-validated Shadowkeep entity definition. */
[[nodiscard]] bool entity_object_type(std::span<const std::byte> entityBytes,
                                      std::uint8_t& objectType) noexcept {
    objectType = 0;
    return read_value(entityBytes, kEntityObjectTypeOffset, objectType);
}

[[nodiscard]] const StandaloneEntityExpectation*
suppressed_standalone_entity_type(std::uint8_t objectType) noexcept {
    const auto found = std::find_if(kSuppressedStandaloneEntityTypes.begin(),
                                    kSuppressedStandaloneEntityTypes.end(),
                                    [objectType](const StandaloneEntityExpectation& expected) {
                                        return expected.objectType == objectType;
                                    });
    return found == kSuppressedStandaloneEntityTypes.end() ? nullptr : &*found;
}

[[nodiscard]] const StandaloneEntityExpectation*
suppressed_component_scenery_type(std::uint8_t objectType) noexcept {
    const auto found = std::find_if(kSuppressedComponentSceneryTypes.begin(),
                                    kSuppressedComponentSceneryTypes.end(),
                                    [objectType](const StandaloneEntityExpectation& expected) {
                                        return expected.objectType == objectType;
                                    });
    return found == kSuppressedComponentSceneryTypes.end() ? nullptr : &*found;
}

[[nodiscard]] const ComponentSceneryClassExpectation*
suppressed_component_scenery_class(std::uint32_t resourceClass) noexcept {
    const auto found =
        std::find_if(kSuppressedComponentSceneryClasses.begin(),
                     kSuppressedComponentSceneryClasses.end(),
                     [resourceClass](const ComponentSceneryClassExpectation& expected) {
                         return expected.resourceClass == resourceClass;
                     });
    return found == kSuppressedComponentSceneryClasses.end() ? nullptr : &*found;
}

/** Reads the complete package-authored transform stored in one placement row. */
[[nodiscard]] bool read_map_transform(std::span<const std::byte> table,
                                      std::size_t entryOffset,
                                      core::Transform& transform) noexcept {
    std::array<float, 4> rotation{};
    std::array<float, 4> translationScale{};
    if (!read_value(table, entryOffset + kMapEntryRotationOffset, rotation)
        || !read_value(table, entryOffset + kMapEntryTranslationOffset, translationScale)) {
        return false;
    }
    transform.translation = {translationScale[0], translationScale[1], translationScale[2]};
    transform.rotation = {rotation[0], rotation[1], rotation[2], rotation[3]};
    transform.uniformScale = translationScale[3];
    return transform.is_finite() && transform.uniformScale > 0.0F;
}

/** Writes the complete package-authored transform stored in one placement row. */
[[nodiscard]] bool write_map_transform(std::span<std::byte> table,
                                       std::size_t entryOffset,
                                       const core::Transform& transform) noexcept {
    if (!transform.is_finite() || transform.uniformScale <= 0.0F) {
        return false;
    }
    const std::array<float, 4> rotation{
        transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w};
    const std::array<float, 4> translationScale{transform.translation.x,
                                                transform.translation.y,
                                                transform.translation.z,
                                                transform.uniformScale};
    return write_value(table, entryOffset + kMapEntryRotationOffset, rotation)
           && write_value(table, entryOffset + kMapEntryTranslationOffset, translationScale);
}

[[nodiscard]] bool near_float(float left, float right) noexcept {
    return std::fabs(left - right) <= 0.0001F;
}

/** Prevents a stale Forge binding from silently editing a different package record. */
[[nodiscard]] bool same_transform(const core::Transform& left,
                                  const core::Transform& right) noexcept {
    return near_float(left.translation.x, right.translation.x)
           && near_float(left.translation.y, right.translation.y)
           && near_float(left.translation.z, right.translation.z)
           && near_float(left.rotation.x, right.rotation.x)
           && near_float(left.rotation.y, right.rotation.y)
           && near_float(left.rotation.z, right.rotation.z)
           && near_float(left.rotation.w, right.rotation.w)
           && near_float(left.uniformScale, right.uniformScale);
}

/** Applies exactly one source-validated Forge placement edit to one map table. */
[[nodiscard]] bool apply_placement_edit(std::uint32_t tableTag,
                                        std::span<std::byte> table,
                                        const MapPlacementEdit& edit) noexcept {
    if (!edit.binding.is_valid() || edit.binding.tableTag != tableTag || !edit.transform.is_finite()
        || edit.transform.uniformScale <= 0.0F) {
        return false;
    }
    std::size_t entriesOffset = 0;
    std::uint32_t entries = 0;
    if (!map_table_layout(table, entriesOffset, entries) || edit.binding.entryIndex >= entries) {
        return false;
    }
    const std::size_t entryOffset =
        entriesOffset + static_cast<std::size_t>(edit.binding.entryIndex) * kMapEntryStride;
    std::size_t resourceOffset = 0;
    std::uint32_t resourceClass = 0;
    std::uint32_t parent = 0;
    core::Transform source{};
    if (!map_resource(table, entryOffset, resourceOffset, resourceClass)
        || resourceClass != kStaticMapResourceClass || resourceOffset > table.size()
        || kStaticMapParentOffset + sizeof(parent) > table.size() - resourceOffset
        || !read_value(table, resourceOffset + kStaticMapParentOffset, parent)
        || parent != edit.binding.parentTag || !read_map_transform(table, entryOffset, source)
        || !same_transform(source, edit.binding.sourceTransform)
        || !write_map_transform(table, entryOffset, edit.transform)) {
        return false;
    }
    const std::uint32_t targetParent =
        edit.replacementParentTag == 0 ? parent : edit.replacementParentTag;
    if (targetParent != parent
        && !write_value(table, resourceOffset + kStaticMapParentOffset, targetParent)) {
        return false;
    }
    report_tower_mutation(
        tableTag, edit.binding.entryIndex, parent, targetParent, source, edit.transform);
    return true;
}

/** Applies one generic map-row transform only after every cataloged source field still matches. */
[[nodiscard]] bool apply_authored_placement_edit(std::uint32_t tableTag,
                                                 std::span<std::byte> table,
                                                 const AuthoredPlacementEdit& edit) noexcept {
    if (!edit.binding.is_valid() || edit.binding.tableTag != tableTag
        || !edit.targetTransform.is_finite() || edit.targetTransform.uniformScale <= 0.0F) {
        return false;
    }
    std::size_t entriesOffset = 0;
    std::uint32_t entries = 0;
    if (!map_table_layout(table, entriesOffset, entries) || edit.binding.entryIndex >= entries) {
        return false;
    }
    const std::size_t entryOffset =
        entriesOffset + static_cast<std::size_t>(edit.binding.entryIndex) * kMapEntryStride;
    std::uint32_t entityTag = 0;
    if (!read_value(table, entryOffset, entityTag) || entityTag != edit.entityTag) {
        return false;
    }

    if (edit.resourceClass == 0) {
        std::int64_t resourceRelative = 0;
        if (!read_value(table, entryOffset + kMapEntryResourcePointerOffset, resourceRelative)
            || resourceRelative != 0 || edit.resourceTag != entityTag) {
            return false;
        }
    } else {
        std::size_t resourceOffset = 0;
        std::uint32_t resourceClass = 0;
        if (!map_resource(table, entryOffset, resourceOffset, resourceClass)
            || resourceClass != edit.resourceClass) {
            return false;
        }
        if (edit.resourceTag != 0) {
            std::size_t tagOffset = 0;
            if (resourceClass == kStaticMapResourceClass) {
                tagOffset = kStaticMapParentOffset;
            } else if (resourceClass == kSkyObjectPlacementResourceClass) {
                tagOffset = kSkyObjectCollectionOffset;
            } else {
                return false;
            }
            std::uint32_t resourceTag = 0;
            if (resourceOffset > table.size()
                || tagOffset + sizeof(resourceTag) > table.size() - resourceOffset
                || !read_value(table, resourceOffset + tagOffset, resourceTag)
                || resourceTag != edit.resourceTag) {
                return false;
            }
        }
    }

    core::Transform source{};
    return read_map_transform(table, entryOffset, source)
           && same_transform(source, edit.binding.sourceTransform)
           && write_map_transform(table, entryOffset, edit.targetTransform);
}

/** Resolves an allowlisted replacement through its static-map parent and instances payload. */
[[nodiscard]] bool validate_static_parent(const reader::Source& source,
                                          reader::Scratch& scratch,
                                          std::uint32_t parentTag) noexcept {
    std::vector<std::byte> parent{};
    std::vector<std::byte> instances{};
    std::uint32_t parentClass = 0;
    std::uint32_t instancesClass = 0;
    std::uint32_t instancesTag = 0;
    return reader::read_tag(source, scratch, parentTag, parent, parentClass)
           && parentClass == kStaticMapParentClass && parent.size() >= 0xC
           && read_value(parent, 0x8, instancesTag)
           && reader::read_tag(source, scratch, instancesTag, instances, instancesClass)
           && instancesClass == kStaticMeshInstancesClass && !instances.empty();
}

/** Walks the named root and retains only map-data tables actually reachable from it. */
[[nodiscard]] bool collect_map_tables(std::uint32_t rootTag,
                                      const reader::Source& source,
                                      reader::Scratch& scratch,
                                      std::vector<std::uint32_t>& mapTables,
                                      TowerPatchStats& stats,
                                      std::uint8_t maximumDepth = kMapGraphDepth,
                                      std::size_t graphCapacity = kMapGraphCapacity) noexcept {
    std::vector<MapNode> queue{};
    std::vector<std::uint32_t> visited{};
    queue.reserve(graphCapacity);
    visited.reserve(graphCapacity);
    queue.push_back(MapNode{rootTag, 0});
    std::vector<std::byte> bytes{};
    const auto known = [&queue, &visited](std::uint32_t tag) {
        return std::find(visited.begin(), visited.end(), tag) != visited.end()
               || std::find_if(queue.begin(), queue.end(), [tag](const MapNode& node) {
                      return node.tag == tag;
                  }) != queue.end();
    };
    for (std::size_t cursor = 0; cursor < queue.size() && cursor < graphCapacity; ++cursor) {
        const MapNode node = queue[cursor];
        if (std::find(visited.begin(), visited.end(), node.tag) != visited.end()) {
            continue;
        }
        std::uint32_t classId = 0;
        if (!reader::read_tag(source, scratch, node.tag, bytes, classId)) {
            continue;
        }
        visited.push_back(node.tag);
        if (classId == kMapDataTableClass) {
            mapTables.push_back(node.tag);
        }
        if (node.depth >= maximumDepth) {
            continue;
        }
        for (std::size_t offset = 0;
             offset + sizeof(std::uint32_t) <= bytes.size() && queue.size() < graphCapacity;
             offset += sizeof(std::uint32_t)) {
            std::uint32_t child = 0;
            std::memcpy(&child, bytes.data() + offset, sizeof child);
            if (child >= tables::kTagLowerBound && child < tables::kTagUpperBound
                && !known(child)) {
                queue.push_back(MapNode{child, static_cast<std::uint8_t>(node.depth + 1)});
            }
        }
        const std::uint16_t packageId = tables::package_of(node.tag);
        for (std::size_t offset = 0;
             offset + 2 * sizeof(std::uint32_t) + sizeof(std::uint64_t) <= bytes.size()
             && queue.size() < graphCapacity;
             offset += sizeof(std::uint32_t)) {
            std::uint32_t isHash32 = 0;
            std::uint64_t hash64 = 0;
            std::memcpy(&isHash32, bytes.data() + offset + sizeof(std::uint32_t), sizeof isHash32);
            std::memcpy(&hash64, bytes.data() + offset + 2 * sizeof(std::uint32_t), sizeof hash64);
            std::uint32_t child = 0;
            std::uint32_t childClass = 0;
            if (isHash32 == 0 && hash64 != 0
                && reader::resolve_hash64(source.directory, packageId, hash64, child, childClass)
                && child >= tables::kTagLowerBound && child < tables::kTagUpperBound
                && !known(child)) {
                queue.push_back(MapNode{child, static_cast<std::uint8_t>(node.depth + 1)});
            }
        }
    }
    std::sort(mapTables.begin(), mapTables.end());
    mapTables.erase(std::unique(mapTables.begin(), mapTables.end()), mapTables.end());
    stats.nodes = visited.size();
    stats.tables = mapTables.size();
    return !mapTables.empty();
}

/** Resolves the exact Tower map root used by the proven carrier package chain. */
[[nodiscard]] bool resolve_tower_root(std::string_view rootName,
                                      state::content::Definition& root) noexcept {
    root = {};
    std::array<state::content::Definition, 16> matches{};
    std::size_t matchCount = 0;
    if (rootName != kTowerMapRoot || !state::content::lookup(rootName, matches, matchCount)
        || matchCount == 0) {
        return false;
    }
    const auto found =
        std::find_if(matches.begin(),
                     matches.begin() + static_cast<std::ptrdiff_t>(matchCount),
                     [](const state::content::Definition& candidate) {
                         return candidate.classId == kMapRootClass
                                && tables::package_of(candidate.tag) == kTowerMapPackageId;
                     });
    if (found == matches.begin() + static_cast<std::ptrdiff_t>(matchCount)) {
        return false;
    }
    root = *found;
    return true;
}

/** Resolves one named installed map root for read-only placement cataloging. */
[[nodiscard]] bool resolve_map_root(std::string_view rootName,
                                    state::content::Definition& root) noexcept {
    root = {};
    std::array<state::content::Definition, 16> matches{};
    std::size_t matchCount = 0;
    if (rootName.empty() || !state::content::lookup(rootName, matches, matchCount)
        || matchCount == 0) {
        return false;
    }
    const auto found =
        std::find_if(matches.begin(),
                     matches.begin() + static_cast<std::ptrdiff_t>(matchCount),
                     [](const state::content::Definition& candidate) {
                         return candidate.classId == kMapRootClass
                                && tables::package_of(candidate.tag) != tables::kAbsentPackageId;
                     });
    if (found == matches.begin() + static_cast<std::ptrdiff_t>(matchCount)) {
        return false;
    }
    root = *found;
    return true;
}

/** Collects readable static placements and enough payload metadata to rank their likely scope. */
[[nodiscard]] bool collect_static_candidates(std::span<const std::uint32_t> mapTables,
                                             const reader::Source& source,
                                             reader::Scratch& scratch,
                                             std::vector<StaticPlacementCandidate>& candidates,
                                             TowerPatchStats& stats,
                                             std::uint16_t packageFilter) noexcept {
    candidates.clear();
    std::vector<std::byte> table{};
    std::vector<std::byte> parentBytes{};
    std::vector<std::byte> dataBytes{};
    for (const std::uint32_t tableTag : mapTables) {
        if (packageFilter != tables::kAbsentPackageId
            && tables::package_of(tableTag) != packageFilter) {
            ++stats.skippedTables;
            continue;
        }
        ++stats.localTables;
        std::uint32_t tableClass = 0;
        std::size_t entriesOffset = 0;
        std::uint32_t entries = 0;
        if (!reader::read_tag(source, scratch, tableTag, table, tableClass)
            || tableClass != kMapDataTableClass
            || !map_table_layout(table, entriesOffset, entries)) {
            ++stats.skippedTables;
            continue;
        }
        for (std::uint32_t index = 0; index < entries; ++index) {
            const std::size_t entryOffset =
                entriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            std::size_t resourceOffset = 0;
            std::uint32_t resourceClass = 0;
            std::uint32_t parentTag = 0;
            std::uint32_t entityTag = 0;
            core::Transform transform{};
            if (!map_resource(table, entryOffset, resourceOffset, resourceClass)
                || resourceClass != kStaticMapResourceClass || resourceOffset > table.size()
                || kStaticMapParentOffset + sizeof(parentTag) > table.size() - resourceOffset
                || !read_value(table, resourceOffset + kStaticMapParentOffset, parentTag)
                || parentTag < tables::kTagLowerBound || parentTag >= tables::kTagUpperBound
                || !read_value(table, entryOffset, entityTag)
                || !read_map_transform(table, entryOffset, transform)) {
                continue;
            }

            std::uint32_t parentClass = 0;
            std::uint32_t dataTag = 0;
            std::uint32_t dataClass = 0;
            if (!reader::read_tag(source, scratch, parentTag, parentBytes, parentClass)
                || parentBytes.size() < 0xC || !read_value(parentBytes, 0x8, dataTag)
                || dataTag < tables::kTagLowerBound || dataTag >= tables::kTagUpperBound
                || !reader::read_tag(source, scratch, dataTag, dataBytes, dataClass)
                || dataBytes.empty()) {
                continue;
            }
            StaticPlacementCandidate candidate{};
            candidate.binding = {tableTag, index, parentTag, transform};
            candidate.entityTag = entityTag;
            candidate.dataTag = dataTag;
            candidate.parentBytes = parentBytes.size();
            candidate.dataBytes = dataBytes.size();
            candidates.push_back(candidate);
            ++stats.staticPlacements;
        }
    }
    return !candidates.empty();
}

[[nodiscard]] double distance_squared(const core::Transform& transform) noexcept {
    const double x = transform.translation.x;
    const double y = transform.translation.y;
    const double z = transform.translation.z;
    return x * x + y * y + z * z;
}

/** Smaller payloads rank first; proximity breaks ties to improve in-game observability. */
[[nodiscard]] bool candidate_less(const StaticPlacementCandidate& left,
                                  const StaticPlacementCandidate& right) noexcept {
    if (left.dataBytes != right.dataBytes) {
        return left.dataBytes < right.dataBytes;
    }
    const double leftDistance = distance_squared(left.binding.sourceTransform);
    const double rightDistance = distance_squared(right.binding.sourceTransform);
    if (leftDistance != rightDistance) {
        return leftDistance < rightDistance;
    }
    if (left.parentBytes != right.parentBytes) {
        return left.parentBytes < right.parentBytes;
    }
    if (left.binding.tableTag != right.binding.tableTag) {
        return left.binding.tableTag < right.binding.tableTag;
    }
    return left.binding.entryIndex < right.binding.entryIndex;
}

[[nodiscard]] bool is_known_tower_aggregate(const StaticPlacementCandidate& candidate) noexcept {
    return candidate.binding.tableTag == kKnownTowerAggregateTable
           && candidate.binding.entryIndex == kKnownTowerAggregateEntry
           && candidate.binding.parentTag == kKnownTowerAggregateParent;
}

/** Reads an entire bounded package patch file. */
[[nodiscard]] bool read_file(const reader::Path& path, std::vector<std::byte>& output) noexcept {
    output.clear();
    const HANDLE file = CreateFileW(path.chars.data(),
                                    GENERIC_READ,
                                    FILE_SHARE_READ,
                                    nullptr,
                                    OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL,
                                    nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }
    LARGE_INTEGER size{};
    const bool sized = GetFileSizeEx(file, &size) != FALSE && size.QuadPart > 0
                       && static_cast<std::uint64_t>(size.QuadPart) <= kMaximumPatchBytes;
    if (!sized) {
        CloseHandle(file);
        return false;
    }
    output.resize(static_cast<std::size_t>(size.QuadPart));
    DWORD read = 0;
    const bool complete =
        ReadFile(file, output.data(), static_cast<DWORD>(output.size()), &read, nullptr) != FALSE
        && read == output.size();
    CloseHandle(file);
    if (!complete) {
        output.clear();
    }
    return complete;
}

/** Writes a complete staged file and flushes it before reporting success. */
[[nodiscard]] bool write_file(const std::wstring& path, std::span<const std::byte> bytes) noexcept {
    if (bytes.empty() || bytes.size() > (std::numeric_limits<DWORD>::max)()) {
        return false;
    }
    const HANDLE file = CreateFileW(
        path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD written = 0;
    const bool complete =
        WriteFile(file, bytes.data(), static_cast<DWORD>(bytes.size()), &written, nullptr) != FALSE
        && written == bytes.size() && FlushFileBuffers(file) != FALSE;
    CloseHandle(file);
    return complete;
}

/** Loads and structurally validates the latest patch header and tables. */
[[nodiscard]] bool
load_package(std::wstring_view directory, std::uint16_t packageId, PackageFile& output) noexcept {
    output = {};
    output.packageId = packageId;
    if (!reader::find_latest(directory, packageId, output.stem, output.latestPatch)
        || output.latestPatch == (std::numeric_limits<std::uint16_t>::max)()
        || !reader::build_path(output.stem, output.latestPatch, output.latestPath)
        || !read_file(output.latestPath, output.bytes)
        || output.bytes.size() < layout::kHeaderSize) {
        return false;
    }
    std::uint16_t version = 0;
    std::uint32_t entryTableRelative = 0;
    if (!read_value(output.bytes, layout::HeaderOffsets::kVersion, version)
        || version != layout::kSupportedVersion
        || !read_value(output.bytes, layout::HeaderOffsets::kEntryCount, output.entryCount)
        || !read_value(output.bytes, layout::HeaderOffsets::kBlockCount, output.blockCount)
        || !read_value(output.bytes, layout::HeaderOffsets::kEntryTable, entryTableRelative)) {
        return false;
    }
    output.entryTable =
        static_cast<std::uint64_t>(entryTableRelative) + layout::kEntryTableAdjustment;
    output.blockTable =
        output.entryTable
        + static_cast<std::uint64_t>(output.entryCount) * sizeof(layout::EntryRecord)
        + layout::kBlockTableGap;
    const std::uint64_t tableEnd =
        output.blockTable
        + static_cast<std::uint64_t>(output.blockCount) * sizeof(layout::BlockRecord);
    return output.entryCount != 0 && output.blockCount != 0 && tableEnd <= output.bytes.size();
}

/** Loads one exact package patch for use as an authenticated block-body carrier. */
[[nodiscard]] bool load_patch_body_file(const reader::Path& stem,
                                        std::uint16_t packageId,
                                        std::uint32_t patchId,
                                        reader::Path& path,
                                        std::vector<std::byte>& bytes,
                                        std::uint64_t& blockTable,
                                        std::uint32_t& blockCount) noexcept {
    bytes.clear();
    blockTable = 0;
    blockCount = 0;
    std::uint16_t version = 0;
    std::uint16_t storedPackage = 0;
    std::uint16_t storedPatch = 0;
    std::uint32_t storedSize = 0;
    std::uint32_t entryCount = 0;
    std::uint32_t entryTableRelative = 0;
    if (!reader::build_path(stem, patchId, path) || !read_file(path, bytes)
        || bytes.size() < layout::kHeaderSize
        || !read_value(bytes, layout::HeaderOffsets::kVersion, version)
        || version != layout::kSupportedVersion
        || !read_value(bytes, layout::HeaderOffsets::kPackageId, storedPackage)
        || storedPackage != packageId
        || !read_value(bytes, layout::HeaderOffsets::kPatchId, storedPatch)
        || storedPatch != patchId || !read_value(bytes, kHeaderFileSizeOffset, storedSize)
        || storedSize != bytes.size()
        || !read_value(bytes, layout::HeaderOffsets::kEntryCount, entryCount)
        || !read_value(bytes, layout::HeaderOffsets::kBlockCount, blockCount)
        || !read_value(bytes, layout::HeaderOffsets::kEntryTable, entryTableRelative)) {
        return false;
    }
    const std::uint64_t entryTable =
        static_cast<std::uint64_t>(entryTableRelative) + layout::kEntryTableAdjustment;
    blockTable = entryTable + static_cast<std::uint64_t>(entryCount) * sizeof(layout::EntryRecord)
                 + layout::kBlockTableGap;
    const std::uint64_t tableEnd =
        blockTable + static_cast<std::uint64_t>(blockCount) * sizeof(layout::BlockRecord);
    return entryCount != 0 && blockCount != 0 && tableEnd <= bytes.size();
}

/** Loads every distinct non-latest physical owner referenced by the changed block rows. */
[[nodiscard]] bool load_owner_patch_files(const PackageFile& package,
                                          std::span<const MutableBlock> blocks,
                                          std::uint32_t latestPatch,
                                          std::vector<OwnerPatchFile>& owners) noexcept {
    owners.clear();
    for (const MutableBlock& block : blocks) {
        const std::uint32_t ownerPatch = block.record.patchId;
        if (ownerPatch == latestPatch) {
            continue;
        }
        if (ownerPatch > package.latestPatch
            || std::any_of(owners.begin(), owners.end(), [ownerPatch](const OwnerPatchFile& owner) {
                   return owner.patchId == ownerPatch;
               })) {
            if (ownerPatch > package.latestPatch) {
                return false;
            }
            continue;
        }
        OwnerPatchFile owner{};
        owner.patchId = ownerPatch;
        if (!load_patch_body_file(package.stem,
                                  package.packageId,
                                  ownerPatch,
                                  owner.path,
                                  owner.bytes,
                                  owner.blockTable,
                                  owner.blockCount)) {
            return false;
        }
        owners.push_back(std::move(owner));
    }
    return true;
}

/** Builds the package-wide nonce used by every encrypted block. */
[[nodiscard]] std::array<std::byte, crypto::kNonceSize>
package_nonce(const reader::BlockKeys& keys, std::uint16_t packageId) noexcept {
    std::array<std::byte, crypto::kNonceSize> nonce = keys.nonceBase;
    nonce[0] ^= static_cast<std::byte>((packageId >> 8U) & 0xFFU);
    nonce[1] = kNonceBranchByte;
    nonce[11] ^= static_cast<std::byte>(packageId & 0xFFU);
    return nonce;
}

/** Reads and decrypts an original block body without decompressing its Oodle stream. */
[[nodiscard]] bool read_encoded_block(const PackageFile& package,
                                      const reader::BlockKeys& keys,
                                      const layout::BlockRecord& record,
                                      std::vector<std::byte>& encoded) noexcept {
    encoded.clear();
    reader::Path path{};
    std::vector<std::byte> file{};
    if (record.size == 0 || !reader::build_path(package.stem, record.patchId, path)
        || !read_file(path, file) || record.offset > file.size()
        || record.size > file.size() - record.offset) {
        return false;
    }
    const auto stored = std::span<const std::byte>(file).subspan(record.offset, record.size);
    if ((record.flags & layout::BlockFlags::kEncrypted) == 0) {
        encoded.assign(stored.begin(), stored.end());
        return true;
    }
    encoded.resize(stored.size());
    const auto nonce = package_nonce(keys, package.packageId);
    const auto& key =
        (record.flags & layout::BlockFlags::kAlternateKey) != 0 ? keys.alternate : keys.primary;
    return crypto::decrypt(std::span<const std::byte, crypto::kKeySize>(key),
                           nonce,
                           stored,
                           std::span<const std::byte, crypto::kTagSize>(record.tag),
                           encoded);
}

/** Compresses and encrypts one decoded block according to its existing table flags. */
[[nodiscard]] bool encode_block(std::span<const std::byte> decoded,
                                const reader::BlockKeys& keys,
                                std::uint16_t packageId,
                                layout::BlockRecord& record,
                                int compressor,
                                std::vector<std::byte>& encoded,
                                std::vector<std::byte>& stored) noexcept {
    encoded.clear();
    stored.clear();
    const HMODULE oodle = GetModuleHandleW(L"oo2core_3_win64.dll");
    if ((record.flags & layout::BlockFlags::kCompressed) != 0) {
        std::size_t capacity = 0;
        std::size_t written = 0;
        if (oodle == nullptr || !compression::required_capacity(oodle, decoded.size(), capacity)) {
            return false;
        }
        encoded.resize(capacity);
        if (!compression::compress_with_codec(oodle, compressor, decoded, encoded, written)) {
            return false;
        }
        encoded.resize(written);
    } else {
        encoded.assign(decoded.begin(), decoded.end());
    }
    if ((record.flags & layout::BlockFlags::kEncrypted) == 0) {
        stored = encoded;
        return !stored.empty();
    }
    stored.resize(encoded.size());
    const auto nonce = package_nonce(keys, packageId);
    const auto& key =
        (record.flags & layout::BlockFlags::kAlternateKey) != 0 ? keys.alternate : keys.primary;
    return crypto::encrypt(std::span<const std::byte, crypto::kKeySize>(key),
                           nonce,
                           encoded,
                           stored,
                           std::span<std::byte, crypto::kTagSize>(record.tag));
}

/** Decodes the newly generated body and proves it exactly reproduces the source block. */
[[nodiscard]] bool validate_block(std::span<const std::byte> stored,
                                  std::span<const std::byte> expected,
                                  const reader::BlockKeys& keys,
                                  std::uint16_t packageId,
                                  const layout::BlockRecord& record) noexcept {
    std::vector<std::byte> plaintext{};
    std::span<const std::byte> encoded = stored;
    if ((record.flags & layout::BlockFlags::kEncrypted) != 0) {
        plaintext.resize(stored.size());
        const auto nonce = package_nonce(keys, packageId);
        const auto& key =
            (record.flags & layout::BlockFlags::kAlternateKey) != 0 ? keys.alternate : keys.primary;
        if (!crypto::decrypt(std::span<const std::byte, crypto::kKeySize>(key),
                             nonce,
                             stored,
                             std::span<const std::byte, crypto::kTagSize>(record.tag),
                             plaintext)) {
            return false;
        }
        encoded = plaintext;
    }
    if ((record.flags & layout::BlockFlags::kCompressed) == 0) {
        return std::ranges::equal(encoded, expected);
    }
    std::vector<std::byte> decoded(expected.size());
    const HMODULE oodle = GetModuleHandleW(L"oo2core_3_win64.dll");
    return oodle != nullptr && compression::decompress(oodle, encoded, decoded)
           && std::ranges::equal(decoded, expected);
}

/** Rounds one file offset up to package block alignment. */
[[nodiscard]] constexpr std::size_t aligned(std::size_t value) noexcept {
    return (value + kFileAlignment - 1) & ~(kFileAlignment - 1);
}

/** Returns one mutable, single-block entry while sharing decoded blocks across mutations. */
[[nodiscard]] bool mutable_entry(const reader::Source& source,
                                 reader::Scratch& scratch,
                                 const PackageFile& package,
                                 std::uint32_t tag,
                                 std::vector<MutableBlock>& blocks,
                                 std::span<std::byte>& bytes,
                                 std::uint32_t& classId) noexcept {
    bytes = {};
    classId = 0;
    if (tag < layout::kTagBase
        || static_cast<std::uint16_t>((tag - layout::kTagBase) >> layout::kTagEntryBits)
               != package.packageId) {
        return false;
    }
    const std::uint32_t entryIndex = (tag - layout::kTagBase) & layout::kTagEntryMask;
    layout::EntryRecord entry{};
    if (entryIndex >= package.entryCount
        || !read_value(package.bytes,
                       package.entryTable + static_cast<std::uint64_t>(entryIndex) * sizeof entry,
                       entry)) {
        return false;
    }
    classId = entry.reference;
    const layout::EntryPlacement placement = layout::placement(entry);
    if (placement.size == 0 || placement.startBlock >= package.blockCount
        || placement.startOffset > layout::kBlockSize
        || placement.size > layout::kBlockSize - placement.startOffset) {
        return false;
    }

    auto found = std::find_if(blocks.begin(), blocks.end(), [placement](const MutableBlock& row) {
        return row.index == placement.startBlock;
    });
    if (found == blocks.end()) {
        MutableBlock block{};
        block.index = placement.startBlock;
        if (!reader::read_block(
                source, scratch, package.packageId, block.index, block.decoded, block.record)) {
            return false;
        }
        blocks.push_back(std::move(block));
        found = std::prev(blocks.end());
    }
    if (placement.startOffset > found->decoded.size()
        || placement.size > found->decoded.size() - placement.startOffset) {
        return false;
    }
    bytes = std::span(found->decoded).subspan(placement.startOffset, placement.size);
    return true;
}

/** Returns one mutable field from an entry that may span multiple package blocks. */
[[nodiscard]] bool mutable_entry_field(const reader::Source& source,
                                       reader::Scratch& scratch,
                                       const PackageFile& package,
                                       std::uint32_t tag,
                                       std::size_t fieldOffset,
                                       std::size_t fieldSize,
                                       std::vector<MutableBlock>& blocks,
                                       std::span<std::byte>& bytes,
                                       std::uint32_t& classId) noexcept {
    bytes = {};
    classId = 0;
    if (tag < layout::kTagBase
        || static_cast<std::uint16_t>((tag - layout::kTagBase) >> layout::kTagEntryBits)
               != package.packageId) {
        return false;
    }
    const std::uint32_t entryIndex = (tag - layout::kTagBase) & layout::kTagEntryMask;
    layout::EntryRecord entry{};
    if (entryIndex >= package.entryCount
        || !read_value(package.bytes,
                       package.entryTable + static_cast<std::uint64_t>(entryIndex) * sizeof entry,
                       entry)) {
        return false;
    }
    classId = entry.reference;
    const layout::EntryPlacement placement = layout::placement(entry);
    if (placement.size == 0 || fieldSize == 0 || fieldOffset > placement.size
        || fieldSize > placement.size - fieldOffset) {
        return false;
    }

    const std::size_t streamOffset = placement.startOffset + fieldOffset;
    const std::uint32_t blockIndex =
        placement.startBlock + static_cast<std::uint32_t>(streamOffset / layout::kBlockSize);
    const std::size_t blockOffset = streamOffset % layout::kBlockSize;
    if (blockIndex >= package.blockCount || fieldSize > layout::kBlockSize - blockOffset) {
        return false;
    }

    auto found = std::find_if(blocks.begin(), blocks.end(), [blockIndex](const MutableBlock& row) {
        return row.index == blockIndex;
    });
    if (found == blocks.end()) {
        MutableBlock block{};
        block.index = blockIndex;
        if (!reader::read_block(
                source, scratch, package.packageId, block.index, block.decoded, block.record)) {
            return false;
        }
        blocks.push_back(std::move(block));
        found = std::prev(blocks.end());
    }
    if (blockOffset > found->decoded.size() || fieldSize > found->decoded.size() - blockOffset) {
        return false;
    }
    bytes = std::span(found->decoded).subspan(blockOffset, fieldSize);
    return true;
}

/** One uniquely identified inline Shadowkeep array inside a serialized payload. */
struct ShadowkeepArray {
    std::size_t countOffset{};
    std::size_t dataOffset{};
    std::uint32_t count{};
};

/** Finds one fingerprinted inline array without trusting an unbounded count or pointer. */
[[nodiscard]] bool find_shadowkeep_array(std::span<const std::byte> payload,
                                         std::uint32_t elementClass,
                                         std::size_t stride,
                                         ShadowkeepArray& output) noexcept {
    output = {};
    bool found = false;
    for (std::size_t marker = 0; marker + kShadowkeepArrayHeaderSize <= payload.size();
         marker += sizeof(std::uint32_t)) {
        std::uint32_t arrayMarker = 0;
        std::uint32_t count = 0;
        std::uint32_t classId = 0;
        if (!read_value(payload, marker, arrayMarker) || arrayMarker != kShadowkeepArrayMarker
            || !read_value(payload, marker + sizeof(std::uint32_t), count)
            || !read_value(payload, marker + 3 * sizeof(std::uint32_t), classId)
            || classId != elementClass) {
            continue;
        }
        const std::size_t dataOffset = marker + kShadowkeepArrayHeaderSize;
        if (stride == 0 || count > (payload.size() - dataOffset) / stride || found) {
            return false;
        }
        output = {marker + sizeof(std::uint32_t), dataOffset, count};
        found = true;
    }
    return found;
}

[[nodiscard]] core::Quat multiply_quaternion(const core::Quat& left,
                                             const core::Quat& right) noexcept {
    return {left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y,
            left.w * right.y - left.x * right.z + left.y * right.w + left.z * right.x,
            left.w * right.z + left.x * right.y - left.y * right.x + left.z * right.w,
            left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z};
}

[[nodiscard]] core::Vec3 rotate_vector(const core::Quat& rotation,
                                       const core::Vec3& value) noexcept {
    const core::Vec3 doubledCross{2.0F * (rotation.y * value.z - rotation.z * value.y),
                                  2.0F * (rotation.z * value.x - rotation.x * value.z),
                                  2.0F * (rotation.x * value.y - rotation.y * value.x)};
    return {value.x + rotation.w * doubledCross.x + rotation.y * doubledCross.z
                - rotation.z * doubledCross.y,
            value.y + rotation.w * doubledCross.y + rotation.z * doubledCross.x
                - rotation.x * doubledCross.z,
            value.z + rotation.w * doubledCross.z + rotation.x * doubledCross.y
                - rotation.y * doubledCross.x};
}

[[nodiscard]] core::Transform compose_transform(const core::Transform& parent,
                                                const core::Transform& local) noexcept {
    const core::Vec3 scaled{local.translation.x * parent.uniformScale,
                            local.translation.y * parent.uniformScale,
                            local.translation.z * parent.uniformScale};
    const core::Vec3 translated = rotate_vector(parent.rotation, scaled);
    core::Transform world{};
    world.translation = {parent.translation.x + translated.x,
                         parent.translation.y + translated.y,
                         parent.translation.z + translated.z};
    world.rotation = multiply_quaternion(parent.rotation, local.rotation);
    world.uniformScale = parent.uniformScale * local.uniformScale;
    return world;
}

[[nodiscard]] bool read_static_instance_transform(std::span<const std::byte> payload,
                                                  const ShadowkeepArray& transforms,
                                                  std::uint32_t index,
                                                  core::Transform& transform) noexcept {
    if (index >= transforms.count) {
        return false;
    }
    const std::size_t offset =
        transforms.dataOffset + static_cast<std::size_t>(index) * kShadowkeepTransformStride;
    std::array<float, 4> rotation{};
    std::array<float, 4> translationScale{};
    if (!read_value(payload, offset, rotation)
        || !read_value(payload, offset + 0x10, translationScale)) {
        return false;
    }
    transform.translation = {translationScale[0], translationScale[1], translationScale[2]};
    transform.rotation = {rotation[0], rotation[1], rotation[2], rotation[3]};
    transform.uniformScale = translationScale[3];
    return transform.is_finite() && transform.uniformScale > 0.0F;
}

/** Derives a conservative tile interval from the six proven baseplate instance centers. */
[[nodiscard]] bool pandora_baseplate_tile_spacing(const reader::Source& source,
                                                  reader::Scratch& scratch,
                                                  float& spacing) noexcept {
    spacing = 0.0F;
    std::vector<std::byte> parent{};
    std::vector<std::byte> payload{};
    std::uint32_t parentClass = 0;
    std::uint32_t payloadClass = 0;
    std::uint32_t payloadTag = 0;
    if (!reader::read_tag(
            source, scratch, kPandoraBaseplateStaticParent, parent, parentClass)
        || parentClass != kStaticMapParentClass || parent.size() < 0xC
        || !read_value(parent, 0x8, payloadTag)
        || !reader::read_tag(source, scratch, payloadTag, payload, payloadClass)
        || payloadClass != kStaticMeshInstancesClass || payload.empty()) {
        return false;
    }

    ShadowkeepArray transforms{};
    ShadowkeepArray statics{};
    ShadowkeepArray groups{};
    if (!find_shadowkeep_array(
            payload, kShadowkeepTransformClass, kShadowkeepTransformStride, transforms)
        || !find_shadowkeep_array(payload, kShadowkeepStaticClass, kShadowkeepStaticStride, statics)
        || !find_shadowkeep_array(payload, kShadowkeepGroupClass, kShadowkeepGroupStride, groups)) {
        return false;
    }

    std::vector<float> xCoordinates{};
    std::vector<float> yCoordinates{};
    for (std::uint32_t groupIndex = 0; groupIndex < groups.count; ++groupIndex) {
        std::array<std::uint32_t, 2> words{};
        const std::size_t groupOffset =
            groups.dataOffset + static_cast<std::size_t>(groupIndex) * kShadowkeepGroupStride;
        if (!read_value(payload, groupOffset, words)) {
            return false;
        }
        const std::uint32_t transformStart = words[0] >> 16U;
        const std::uint32_t transformCount = words[1] >> 16U;
        const std::uint32_t staticIndex = words[1] & 0xFFFFU;
        if (transformCount == 0 || staticIndex >= statics.count
            || transformStart > transforms.count
            || transformCount > transforms.count - transformStart) {
            return false;
        }
        for (std::uint32_t offset = 0; offset < transformCount; ++offset) {
            core::Transform transform{};
            if (!read_static_instance_transform(
                    payload, transforms, transformStart + offset, transform)) {
                return false;
            }
            xCoordinates.push_back(transform.translation.x);
            yCoordinates.push_back(transform.translation.y);
        }
    }
    if (xCoordinates.size() != 6 || yCoordinates.size() != xCoordinates.size()) {
        return false;
    }

    const auto axis_interval = [](std::vector<float> coordinates) {
        std::sort(coordinates.begin(), coordinates.end());
        float minimumStep = (std::numeric_limits<float>::max)();
        for (std::size_t index = 1; index < coordinates.size(); ++index) {
            const float difference = coordinates[index] - coordinates[index - 1];
            if (difference > 0.001F) {
                minimumStep = (std::min)(minimumStep, difference);
            }
        }
        const float span = coordinates.back() - coordinates.front();
        return minimumStep == (std::numeric_limits<float>::max)() ? 0.0F
                                                                  : span + minimumStep;
    };
    const float xInterval = axis_interval(std::move(xCoordinates));
    const float yInterval = axis_interval(std::move(yCoordinates));
    spacing = (std::max)(xInterval, yInterval);
    if (spacing <= 0.001F) {
        spacing = 24.0F;
    }
    return std::isfinite(spacing) && spacing >= 4.0F && spacing <= 256.0F;
}

[[nodiscard]] core::Transform tiled_pandora_transform(const core::Transform& baseplate,
                                                       float spacing,
                                                       float gridOffset) noexcept {
    core::Transform result = baseplate;
    const core::Vec3 localOffset{spacing * gridOffset * baseplate.uniformScale, 0.0F, 0.0F};
    const core::Vec3 worldOffset = rotate_vector(baseplate.rotation, localOffset);
    result.translation.x += worldOffset.x;
    result.translation.y += worldOffset.y;
    result.translation.z += worldOffset.z;
    return result;
}

[[nodiscard]] AuthoredPlacementKind authored_resource_kind(std::uint32_t resourceClass) noexcept {
    if (resourceClass == kStaticMapResourceClass) {
        return AuthoredPlacementKind::staticAggregate;
    }
    if (resourceClass == kSkyObjectPlacementResourceClass) {
        return AuthoredPlacementKind::sky;
    }
    if (resourceClass == kTowerVisibilityBundleResourceClass) {
        return AuthoredPlacementKind::visibility;
    }
    if (resourceClass == kTowerDirectHavokResourceClass) {
        return AuthoredPlacementKind::collision;
    }
    if (resourceClass == kTowerEntityModelResourceClass) {
        return AuthoredPlacementKind::entityModel;
    }
    if (suppressed_component_scenery_class(resourceClass) != nullptr) {
        return AuthoredPlacementKind::component;
    }
    return AuthoredPlacementKind::resource;
}

/** Expands only fully bounded Shadowkeep StaticMeshInstances groups. */
[[nodiscard]] bool append_static_instances(std::uint32_t parentCandidateIndex,
                                           const AuthoredPlacementCandidate& parent,
                                           std::span<const std::byte> payload,
                                           std::vector<AuthoredPlacementCandidate>& candidates,
                                           AuthoredPlacementStats& stats) noexcept {
    constexpr std::size_t kMaximumExpandedInstances = 65536;
    ShadowkeepArray transforms{};
    ShadowkeepArray statics{};
    ShadowkeepArray groups{};
    if (!find_shadowkeep_array(
            payload, kShadowkeepTransformClass, kShadowkeepTransformStride, transforms)
        || !find_shadowkeep_array(payload, kShadowkeepStaticClass, kShadowkeepStaticStride, statics)
        || !find_shadowkeep_array(payload, kShadowkeepGroupClass, kShadowkeepGroupStride, groups)
        || transforms.count == 0 || statics.count == 0 || groups.count == 0) {
        return false;
    }

    std::size_t instanceCount = 0;
    for (std::uint32_t groupIndex = 0; groupIndex < groups.count; ++groupIndex) {
        std::array<std::uint32_t, 2> words{};
        const std::size_t groupOffset =
            groups.dataOffset + static_cast<std::size_t>(groupIndex) * kShadowkeepGroupStride;
        if (!read_value(payload, groupOffset, words)) {
            return false;
        }
        const std::uint32_t transformStart = words[0] >> 16U;
        const std::uint32_t transformCount = words[1] >> 16U;
        const std::uint32_t staticIndex = words[1] & 0xFFFFU;
        std::uint32_t meshTag = 0;
        if (transformCount == 0 || staticIndex >= statics.count || transformStart > transforms.count
            || transformCount > transforms.count - transformStart
            || !read_value(payload,
                           statics.dataOffset
                               + static_cast<std::size_t>(staticIndex) * kShadowkeepStaticStride,
                           meshTag)
            || meshTag < tables::kTagLowerBound || meshTag >= tables::kTagUpperBound
            || transformCount > kMaximumExpandedInstances - instanceCount) {
            return false;
        }
        for (std::uint32_t offset = 0; offset < transformCount; ++offset) {
            core::Transform local{};
            if (!read_static_instance_transform(
                    payload, transforms, transformStart + offset, local)) {
                return false;
            }
        }
        instanceCount += transformCount;
    }

    candidates.reserve(candidates.size() + instanceCount);
    for (std::uint32_t groupIndex = 0; groupIndex < groups.count; ++groupIndex) {
        std::array<std::uint32_t, 2> words{};
        const std::size_t groupOffset =
            groups.dataOffset + static_cast<std::size_t>(groupIndex) * kShadowkeepGroupStride;
        (void)read_value(payload, groupOffset, words);
        const std::uint32_t transformStart = words[0] >> 16U;
        const std::uint32_t transformCount = words[1] >> 16U;
        const std::uint32_t staticIndex = words[1] & 0xFFFFU;
        std::uint32_t meshTag = 0;
        (void)read_value(payload,
                         statics.dataOffset
                             + static_cast<std::size_t>(staticIndex) * kShadowkeepStaticStride,
                         meshTag);
        for (std::uint32_t offset = 0; offset < transformCount; ++offset) {
            core::Transform local{};
            (void)read_static_instance_transform(
                payload, transforms, transformStart + offset, local);
            AuthoredPlacementCandidate child{};
            child.binding = parent.binding;
            child.binding.sourceTransform =
                compose_transform(parent.binding.sourceTransform, local);
            child.parentCandidateIndex = parentCandidateIndex;
            child.entityTag = parent.entityTag;
            child.resourceClass = parent.resourceClass;
            child.resourceTag = parent.resourceTag;
            child.dataTag = parent.dataTag;
            child.meshTag = meshTag;
            child.worldId = parent.worldId;
            child.groupIndex = groupIndex;
            child.transformIndex = transformStart + offset;
            child.dataBytes = parent.dataBytes;
            child.kind = AuthoredPlacementKind::staticInstance;
            child.transformKnown = child.binding.sourceTransform.is_finite();
            candidates.push_back(child);
            ++stats.staticInstances;
        }
    }
    return instanceCount != 0;
}

[[nodiscard]] bool collect_authored_candidates(std::span<const std::uint32_t> mapTables,
                                               const reader::Source& source,
                                               reader::Scratch& scratch,
                                               std::vector<AuthoredPlacementCandidate>& candidates,
                                               AuthoredPlacementStats& stats,
                                               std::uint16_t editablePackage) noexcept {
    candidates.clear();
    stats.mapTables = mapTables.size();
    std::vector<std::byte> table{};
    std::vector<std::byte> entityBytes{};
    std::vector<std::byte> linkedBytes{};
    std::vector<std::byte> dataBytes{};
    for (const std::uint32_t tableTag : mapTables) {
        std::uint32_t tableClass = 0;
        std::size_t entriesOffset = 0;
        std::uint32_t entries = 0;
        if (!reader::read_tag(source, scratch, tableTag, table, tableClass)
            || tableClass != kMapDataTableClass
            || !map_table_layout(table, entriesOffset, entries)) {
            continue;
        }
        for (std::uint32_t index = 0; index < entries; ++index) {
            const std::size_t entryOffset =
                entriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            std::uint32_t entityTag = 0;
            core::Transform transform{};
            if (!read_value(table, entryOffset, entityTag)
                || !read_map_transform(table, entryOffset, transform)) {
                continue;
            }

            AuthoredPlacementCandidate candidate{};
            candidate.entityTag = entityTag;
            (void)read_value(table, entryOffset + kMapEntryWorldIdOffset, candidate.worldId);
            candidate.binding.tableTag = tableTag;
            candidate.binding.entryIndex = index;
            candidate.binding.sourceTransform = transform;
            candidate.transformKnown = true;
            candidate.stageEditable = editablePackage == kPandoraMapPackageId
                                      && tables::package_of(tableTag) == editablePackage;

            std::size_t resourceOffset = 0;
            std::uint32_t resourceClass = 0;
            if (!map_resource(table, entryOffset, resourceOffset, resourceClass)) {
                std::uint8_t objectType = 0;
                if (!map_entity(table, entryOffset, source, scratch, entityBytes)
                    || !entity_object_type(entityBytes, objectType)) {
                    continue;
                }
                candidate.binding.parentTag = entityTag;
                candidate.resourceTag = entityTag;
                candidate.objectType = objectType;
                candidate.objectTypeKnown = true;
                candidate.kind = AuthoredPlacementKind::entity;
                candidates.push_back(candidate);
                ++stats.placementRows;
                ++stats.entityPlacements;
                continue;
            }

            candidate.resourceClass = resourceClass;
            candidate.kind = authored_resource_kind(resourceClass);
            std::uint8_t objectType = 0;
            if (map_entity_owner(table, entryOffset, source, scratch, entityBytes)
                && entity_object_type(entityBytes, objectType)) {
                candidate.objectType = objectType;
                candidate.objectTypeKnown = true;
            }
            if (candidate.kind == AuthoredPlacementKind::staticAggregate) {
                std::uint32_t parentTag = 0;
                if (resourceOffset <= table.size()
                    && kStaticMapParentOffset + sizeof(parentTag) <= table.size() - resourceOffset
                    && read_value(table, resourceOffset + kStaticMapParentOffset, parentTag)) {
                    candidate.resourceTag = parentTag;
                    candidate.binding.parentTag = parentTag;
                    std::uint32_t parentClass = 0;
                    std::uint32_t dataClass = 0;
                    std::uint32_t dataTag = 0;
                    if (reader::read_tag(source, scratch, parentTag, linkedBytes, parentClass)
                        && parentClass == kStaticMapParentClass && linkedBytes.size() >= 0xC
                        && read_value(linkedBytes, 0x8, dataTag)
                        && reader::read_tag(source, scratch, dataTag, dataBytes, dataClass)
                        && dataClass == kStaticMeshInstancesClass && !dataBytes.empty()) {
                        candidate.dataTag = dataTag;
                        candidate.dataBytes = dataBytes.size();
                    }
                }
            } else if (candidate.kind == AuthoredPlacementKind::sky) {
                std::uint32_t collectionTag = 0;
                if (linked_resource_tag(table,
                                        resourceOffset,
                                        source,
                                        scratch,
                                        kSkyObjectCollectionClass,
                                        collectionTag,
                                        linkedBytes)) {
                    candidate.resourceTag = collectionTag;
                    candidate.binding.parentTag = collectionTag;
                    candidate.dataBytes = linkedBytes.size();
                }
            }
            if (candidate.binding.parentTag == 0) {
                candidate.binding.parentTag = entityTag;
            }

            const std::uint32_t parentCandidateIndex =
                static_cast<std::uint32_t>(candidates.size());
            candidates.push_back(candidate);
            ++stats.placementRows;
            ++stats.resourcePlacements;
            if (candidate.kind == AuthoredPlacementKind::staticAggregate) {
                ++stats.staticAggregates;
                if (candidate.dataTag != 0 && !dataBytes.empty()) {
                    (void)append_static_instances(
                        parentCandidateIndex, candidate, dataBytes, candidates, stats);
                }
            } else if (candidate.kind == AuthoredPlacementKind::resource) {
                ++stats.unsupportedResources;
            }
        }
    }
    return stats.placementRows != 0;
}

/** Isolates one broad, thin, Tower-resident floor group while preserving native culling data. */
[[nodiscard]] bool apply_tower_local_baseplate_payload(const reader::Source& source,
                                                       reader::Scratch& scratch,
                                                       const PackageFile& package,
                                                       std::vector<MutableBlock>& blocks) noexcept {
    std::span<std::byte> payload{};
    std::uint32_t classId = 0;
    if (!mutable_entry(
            source, scratch, package, kKnownTowerAggregatePayload, blocks, payload, classId)
        || classId != kStaticMeshInstancesClass || payload.size() != kTowerAggregatePayloadSize) {
        return false;
    }

    ShadowkeepArray transforms{};
    ShadowkeepArray statics{};
    ShadowkeepArray groups{};
    if (!find_shadowkeep_array(
            payload, kShadowkeepTransformClass, kShadowkeepTransformStride, transforms)
        || !find_shadowkeep_array(payload, kShadowkeepStaticClass, kShadowkeepStaticStride, statics)
        || !find_shadowkeep_array(payload, kShadowkeepGroupClass, kShadowkeepGroupStride, groups)
        || transforms.count != kTowerAggregateTransformCount
        || statics.count != kTowerAggregateStaticCount
        || (groups.count != kTowerAggregateGroupCount && groups.count != 1)
        || kTowerLocalBaseplateTransform >= transforms.count
        || kTowerLocalBaseplateStaticIndex >= statics.count
        || groups.dataOffset
                   + (static_cast<std::size_t>(kTowerLocalBaseplateGroup) + 1)
                         * kShadowkeepGroupStride
               > payload.size()) {
        return false;
    }

    std::uint32_t mesh = 0;
    std::array<std::uint32_t, 2> groupWords{};
    std::array<std::uint32_t, 12> transformWords{};
    const std::size_t selectedGroup =
        groups.dataOffset
        + static_cast<std::size_t>(kTowerLocalBaseplateGroup) * kShadowkeepGroupStride;
    const std::size_t selectedTransform =
        transforms.dataOffset
        + static_cast<std::size_t>(kTowerLocalBaseplateTransform) * kShadowkeepTransformStride;
    if (!read_value(payload,
                    statics.dataOffset
                        + static_cast<std::size_t>(kTowerLocalBaseplateStaticIndex)
                              * kShadowkeepStaticStride,
                    mesh)
        || mesh != kTowerLocalBaseplateMesh || !read_value(payload, selectedGroup, groupWords)
        || groupWords != kTowerLocalBaseplateGroupWords
        || !read_value(payload, selectedTransform, transformWords)
        || transformWords != kTowerLocalBaseplateTransformWords) {
        return false;
    }

    constexpr std::uint32_t isolatedGroupCount = 1;
    if (!write_value(payload, groups.countOffset, isolatedGroupCount)) {
        return false;
    }
    std::memmove(
        payload.data() + groups.dataOffset, payload.data() + selectedGroup, kShadowkeepGroupStride);
    const std::uint32_t isolatedGroupWord =
        (kTowerLocalBaseplateGroupWords[0] & 0xFFFF0000U) | isolatedGroupCount;
    return write_value(payload, groups.dataOffset, isolatedGroupWord);
}

/** Validates the complete field-tested Tower collision baseline without mutating it. */
[[nodiscard]] bool validate_tower_collision_baseline(std::span<const std::uint32_t> mapTables,
                                                     const reader::Source& source,
                                                     reader::Scratch& scratch,
                                                     TowerPatchStats& stats) noexcept {
    std::vector<std::byte> sourceTable{};
    std::vector<std::byte> entityBytes{};
    for (const std::uint32_t tableTag : mapTables) {
        if (tables::package_of(tableTag) != kTowerMapPackageId) {
            continue;
        }
        std::uint32_t sourceClass = 0;
        std::size_t entriesOffset = 0;
        std::uint32_t entries = 0;
        if (!reader::read_tag(source, scratch, tableTag, sourceTable, sourceClass)
            || sourceClass != kMapDataTableClass
            || !map_table_layout(sourceTable, entriesOffset, entries)) {
            continue;
        }

        for (std::uint32_t index = 0; index < entries; ++index) {
            const std::size_t entryOffset =
                entriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            const std::size_t pointerOffset = entryOffset + kMapEntryResourcePointerOffset;
            std::int64_t resourceRelative = 0;
            if (!read_value(sourceTable, pointerOffset, resourceRelative)) {
                continue;
            }
            if (resourceRelative == 0) {
                if (map_entity(sourceTable, entryOffset, source, scratch, entityBytes)) {
                    ++stats.preservedEntityPlacements;
                }
                continue;
            }
            std::size_t resourceOffset = 0;
            std::uint32_t resourceClass = 0;
            if (!map_resource(sourceTable, entryOffset, resourceOffset, resourceClass)) {
                continue;
            }
            if (resourceClass == kTowerVisibilityBundleResourceClass) {
                ++stats.preservedVisibilityBundlePlacements;
            } else if (resourceClass == kTowerDirectHavokResourceClass) {
                ++stats.preservedBaseDirectHavokPlacements;
            } else if (resourceClass == kTowerEntityModelResourceClass) {
                ++stats.entityModelPlacements;
                std::uint32_t havokTag = 0;
                if (!read_value(
                        sourceTable, resourceOffset + kTowerEntityModelHavokOffset, havokTag)) {
                    return false;
                }
                if (havokTag == kTowerEntityModelHavokTag) {
                    ++stats.preservedEntityModelHavokReferences;
                }
            }
        }
    }
    return stats.preservedEntityPlacements == kExpectedTowerEntityPlacements
           && stats.preservedVisibilityBundlePlacements == kExpectedTowerVisibilityBundles
           && stats.preservedBaseDirectHavokPlacements == kExpectedTowerBaseDirectHavokPlacements
           && stats.entityModelPlacements == kExpectedTowerEntityModelPlacements
           && stats.preservedEntityModelHavokReferences == kExpectedTowerEntityModelHavokReferences;
}

/** Proves one Havok payload is the expected 2012 binary compressed-mesh packfile. */
[[nodiscard]] bool is_compressed_mesh_packfile(std::span<const std::byte> bytes,
                                               std::size_t expectedSize) noexcept {
    std::uint32_t magic0 = 0;
    std::uint32_t magic1 = 0;
    std::uint32_t version = 0;
    return bytes.size() == expectedSize && read_value(bytes, 0, magic0)
           && read_value(bytes, sizeof magic0, magic1)
           && read_value(bytes, 3 * sizeof(std::uint32_t), version)
           && magic0 == kHavokPackfileMagic0 && magic1 == kHavokPackfileMagic1
           && version == kHavokPackfileVersion && kHavokRootClassOffset <= bytes.size()
           && kHavokCompressedMeshRoot.size() <= bytes.size() - kHavokRootClassOffset
           && std::memcmp(bytes.data() + kHavokRootClassOffset,
                          kHavokCompressedMeshRoot.data(),
                          kHavokCompressedMeshRoot.size())
                  == 0;
}

/** Replaces one clean StaticMap terrain mesh with a tiny same-package, type-compatible control. */
[[nodiscard]] bool substitute_tower_static_collision_mesh(const reader::Source& source,
                                                          reader::Scratch& scratch,
                                                          const PackageFile& package,
                                                          std::vector<MutableBlock>& blocks,
                                                          TowerPatchStats& stats) noexcept {
    std::vector<std::byte> original{};
    std::vector<std::byte> control{};
    std::uint32_t originalClass = 0;
    std::uint32_t controlClass = 0;
    if (!reader::read_tag(
            source, scratch, kTowerStaticCollisionOriginal, original, originalClass)) {
        report("tower_collision_original_read", "fail", kTowerMapPackageId);
        return false;
    }
    if (!reader::read_tag(
            source, scratch, kTowerStaticCollisionSmallControl, control, controlClass)) {
        report("tower_collision_control_read", "fail", kTowerMapPackageId);
        return false;
    }
    if (!is_compressed_mesh_packfile(original, kTowerStaticCollisionOriginalBytes)) {
        report("tower_collision_original_shape",
               "fail",
               kTowerMapPackageId,
               0,
               originalClass,
               original.size());
        return false;
    }
    if (!is_compressed_mesh_packfile(control, kTowerStaticCollisionSmallControlBytes)) {
        report("tower_collision_control_shape",
               "fail",
               kTowerMapPackageId,
               0,
               controlClass,
               control.size());
        return false;
    }

    std::span<std::byte> referenceBytes{};
    std::uint32_t companionClass = 0;
    std::uint32_t currentReference = 0;
    if (!mutable_entry_field(source,
                             scratch,
                             package,
                             kTowerStaticCollisionCompanion,
                             kTowerStaticCollisionReferenceOffset,
                             sizeof currentReference,
                             blocks,
                             referenceBytes,
                             companionClass)) {
        report("tower_collision_field_map", "fail", kTowerMapPackageId);
        return false;
    }
    if (companionClass != kTerrainCompanionClass) {
        report("tower_collision_companion_class",
               "fail",
               kTowerMapPackageId,
               0,
               companionClass,
               referenceBytes.size());
        return false;
    }
    if (!read_value(referenceBytes, 0, currentReference)) {
        report("tower_collision_reference_read", "fail", kTowerMapPackageId);
        return false;
    }
    if (currentReference != kTowerStaticCollisionOriginal) {
        report("tower_collision_reference_match",
               "fail",
               kTowerMapPackageId,
               0,
               currentReference,
               referenceBytes.size());
        return false;
    }
    if (!write_value(referenceBytes, 0, kTowerStaticCollisionSmallControl)) {
        report("tower_collision_reference_write", "fail", kTowerMapPackageId);
        return false;
    }
    ++stats.substitutedStaticMeshCollisionReferences;
    return true;
}

/** Moves only standalone scenery entities, keeping spawn-sensitive System and Interactive rows. */
[[nodiscard]] bool suppress_tower_standalone_scenery(std::span<const std::uint32_t> mapTables,
                                                     const reader::Source& source,
                                                     reader::Scratch& scratch,
                                                     const PackageFile& package,
                                                     std::vector<MutableBlock>& blocks,
                                                     std::vector<std::uint32_t>& touchedTables,
                                                     TowerPatchStats& stats) noexcept {
    std::array<std::size_t, kSuppressedStandaloneEntityTypes.size()> observed{};
    std::vector<std::byte> sourceTable{};
    std::vector<std::byte> entityBytes{};
    for (const std::uint32_t tableTag : mapTables) {
        if (tables::package_of(tableTag) != kTowerMapPackageId) {
            continue;
        }
        std::uint32_t sourceClass = 0;
        std::size_t sourceEntriesOffset = 0;
        std::uint32_t entries = 0;
        if (!reader::read_tag(source, scratch, tableTag, sourceTable, sourceClass)
            || sourceClass != kMapDataTableClass
            || !map_table_layout(sourceTable, sourceEntriesOffset, entries)) {
            return false;
        }

        std::span<std::byte> mutableTable{};
        std::size_t mutableEntriesOffset = 0;
        bool tableTouched = false;
        for (std::uint32_t index = 0; index < entries; ++index) {
            const std::size_t sourceEntryOffset =
                sourceEntriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            if (!map_entity(sourceTable, sourceEntryOffset, source, scratch, entityBytes)) {
                continue;
            }
            std::uint8_t objectType = 0;
            if (!entity_object_type(entityBytes, objectType)) {
                return false;
            }
            if (objectType == kInteractiveObjectType) {
                ++stats.preservedStandaloneInteractiveEntities;
                continue;
            }
            if (objectType == kSystemObjectType) {
                ++stats.preservedStandaloneSystemEntities;
                continue;
            }
            const StandaloneEntityExpectation* const expected =
                suppressed_standalone_entity_type(objectType);
            if (expected == nullptr) {
                return false;
            }
            const std::size_t typeIndex =
                static_cast<std::size_t>(expected - kSuppressedStandaloneEntityTypes.data());
            ++observed[typeIndex];

            if (mutableTable.empty()) {
                std::uint32_t mutableClass = 0;
                std::uint32_t mutableEntries = 0;
                if (!mutable_entry(
                        source, scratch, package, tableTag, blocks, mutableTable, mutableClass)
                    || mutableClass != kMapDataTableClass
                    || !map_table_layout(mutableTable, mutableEntriesOffset, mutableEntries)
                    || mutableEntries != entries) {
                    return false;
                }
            }
            const std::size_t mutableEntryOffset =
                mutableEntriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            core::Transform transform{};
            if (!read_map_transform(mutableTable, mutableEntryOffset, transform)) {
                return false;
            }
            transform.translation.z = kSuppressedStandaloneEntityHeight;
            transform.uniformScale = kSuppressedStandaloneEntityScale;
            if (!write_map_transform(mutableTable, mutableEntryOffset, transform)) {
                return false;
            }
            ++stats.suppressedStandaloneEntities;
            tableTouched = true;
        }
        if (tableTouched) {
            touchedTables.push_back(tableTag);
        }
    }

    for (std::size_t index = 0; index < observed.size(); ++index) {
        if (observed[index] != kSuppressedStandaloneEntityTypes[index].expectedPlacements) {
            return false;
        }
    }
    return stats.suppressedStandaloneEntities == kExpectedSuppressedStandaloneEntities
           && stats.preservedStandaloneInteractiveEntities == kExpectedStandaloneInteractiveEntities
           && stats.preservedStandaloneSystemEntities == kExpectedStandaloneSystemEntities;
}

/** Moves only component-backed scenery owners, preserving every System and Interactive row. */
[[nodiscard]] bool suppress_tower_component_scenery(std::span<const std::uint32_t> mapTables,
                                                    const reader::Source& source,
                                                    reader::Scratch& scratch,
                                                    const PackageFile& package,
                                                    std::vector<MutableBlock>& blocks,
                                                    std::vector<std::uint32_t>& touchedTables,
                                                    TowerPatchStats& stats) noexcept {
    std::array<std::size_t, kSuppressedComponentSceneryTypes.size()> observedTypes{};
    std::array<std::size_t, kSuppressedComponentSceneryClasses.size()> observedClasses{};
    std::vector<std::byte> sourceTable{};
    std::vector<std::byte> entityBytes{};
    for (const std::uint32_t tableTag : mapTables) {
        if (tables::package_of(tableTag) != kTowerMapPackageId) {
            continue;
        }
        std::uint32_t sourceClass = 0;
        std::size_t sourceEntriesOffset = 0;
        std::uint32_t entries = 0;
        if (!reader::read_tag(source, scratch, tableTag, sourceTable, sourceClass)
            || sourceClass != kMapDataTableClass
            || !map_table_layout(sourceTable, sourceEntriesOffset, entries)) {
            return false;
        }

        std::span<std::byte> mutableTable{};
        std::size_t mutableEntriesOffset = 0;
        bool tableTouched = false;
        for (std::uint32_t index = 0; index < entries; ++index) {
            const std::size_t sourceEntryOffset =
                sourceEntriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            std::size_t resourceOffset = 0;
            std::uint32_t resourceClass = 0;
            if (!map_resource(sourceTable, sourceEntryOffset, resourceOffset, resourceClass)) {
                continue;
            }
            if (!map_entity_owner(sourceTable, sourceEntryOffset, source, scratch, entityBytes)) {
                return false;
            }
            std::uint8_t objectType = 0;
            if (!entity_object_type(entityBytes, objectType)) {
                return false;
            }
            if (objectType == kInteractiveObjectType) {
                ++stats.preservedComponentInteractiveEntities;
                continue;
            }
            if (objectType == kSystemObjectType) {
                ++stats.preservedComponentSystemEntities;
                continue;
            }

            const StandaloneEntityExpectation* const expectedType =
                suppressed_component_scenery_type(objectType);
            const ComponentSceneryClassExpectation* const expectedClass =
                suppressed_component_scenery_class(resourceClass);
            if (expectedType == nullptr || expectedClass == nullptr) {
                return false;
            }
            const std::size_t typeIndex =
                static_cast<std::size_t>(expectedType - kSuppressedComponentSceneryTypes.data());
            const std::size_t classIndex =
                static_cast<std::size_t>(expectedClass - kSuppressedComponentSceneryClasses.data());
            ++observedTypes[typeIndex];
            ++observedClasses[classIndex];

            if (mutableTable.empty()) {
                std::uint32_t mutableClass = 0;
                std::uint32_t mutableEntries = 0;
                if (!mutable_entry(
                        source, scratch, package, tableTag, blocks, mutableTable, mutableClass)
                    || mutableClass != kMapDataTableClass
                    || !map_table_layout(mutableTable, mutableEntriesOffset, mutableEntries)
                    || mutableEntries != entries) {
                    return false;
                }
            }
            const std::size_t mutableEntryOffset =
                mutableEntriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            core::Transform transform{};
            if (!read_map_transform(mutableTable, mutableEntryOffset, transform)) {
                return false;
            }
            transform.translation.z = kSuppressedStandaloneEntityHeight;
            transform.uniformScale = kSuppressedStandaloneEntityScale;
            if (!write_map_transform(mutableTable, mutableEntryOffset, transform)) {
                return false;
            }
            ++stats.suppressedComponentSceneryEntities;
            tableTouched = true;
        }
        if (tableTouched) {
            touchedTables.push_back(tableTag);
        }
    }

    for (std::size_t index = 0; index < observedTypes.size(); ++index) {
        if (observedTypes[index] != kSuppressedComponentSceneryTypes[index].expectedPlacements) {
            return false;
        }
    }
    for (std::size_t index = 0; index < observedClasses.size(); ++index) {
        if (observedClasses[index]
            != kSuppressedComponentSceneryClasses[index].expectedPlacements) {
            return false;
        }
    }
    return stats.suppressedComponentSceneryEntities == kExpectedSuppressedComponentSceneryEntities
           && stats.preservedComponentInteractiveEntities == kExpectedComponentInteractiveEntities
           && stats.preservedComponentSystemEntities == kExpectedComponentSystemEntities;
}

/** Opens one single-entry Shadowkeep static-map table and validates its inline resource shape. */
[[nodiscard]] bool static_map_table(const reader::Source& source,
                                    reader::Scratch& scratch,
                                    const PackageFile& package,
                                    std::uint32_t tableTag,
                                    std::vector<MutableBlock>& blocks,
                                    std::span<std::byte>& table,
                                    std::uint32_t& resourceTag) noexcept {
    constexpr std::uint32_t kMapDataTableClass = 0x808099D6;
    constexpr std::uint32_t kMapDataEntryClass = 0x808099D8;
    constexpr std::uint32_t kMapDataResourceClass = 0x808071B3;
    constexpr std::size_t kTableSize = 0xE0;
    constexpr std::size_t kFileSizeOffset = 0;
    constexpr std::size_t kPlacementCountOffset = 0x8;
    constexpr std::size_t kPlacementPointerOffset = 0x10;
    constexpr std::size_t kEntryClassOffset = 0x28;
    constexpr std::size_t kResourceClassOffset = 0xC4;
    constexpr std::size_t kResourceTagOffset = 0xD8;
    constexpr std::int64_t kInlinePlacementPointer = 0x10;

    table = {};
    resourceTag = 0;
    std::uint32_t classId = 0;
    if (!mutable_entry(source, scratch, package, tableTag, blocks, table, classId)
        || classId != kMapDataTableClass || table.size() != kTableSize) {
        return false;
    }
    std::uint64_t fileSize = 0;
    std::uint32_t count = 0;
    std::int64_t placementPointer = 0;
    std::uint32_t entryClass = 0;
    std::uint32_t resourceClass = 0;
    return read_value(table, kFileSizeOffset, fileSize) && fileSize == table.size()
           && read_value(table, kPlacementCountOffset, count) && count == 1
           && read_value(table, kPlacementPointerOffset, placementPointer)
           && placementPointer == kInlinePlacementPointer
           && read_value(table, kEntryClassOffset, entryClass) && entryClass == kMapDataEntryClass
           && read_value(table, kResourceClassOffset, resourceClass)
           && resourceClass == kMapDataResourceClass
           && read_value(table, kResourceTagOffset, resourceTag) && resourceTag >= layout::kTagBase;
}

/** Encodes changed blocks while preserving every block's existing physical owner patch. */
[[nodiscard]] bool append_modified_blocks(PackageFile& package,
                                          std::span<MutableBlock> blocks,
                                          const reader::BlockKeys& keys,
                                          std::uint32_t newPatch,
                                          std::span<OwnerPatchFile> owners = {}) noexcept {
    if (blocks.empty() || newPatch > (std::numeric_limits<std::uint16_t>::max)()) {
        return false;
    }
    for (MutableBlock& block : blocks) {
        std::vector<std::byte> sourceEncoded{};
        std::vector<std::byte> authoredEncoded{};
        std::vector<std::byte> stored{};
        int compressor = -1;
        if (!read_encoded_block(package, keys, block.record, sourceEncoded)
            || ((block.record.flags & layout::BlockFlags::kCompressed) != 0
                && !source_compressor(sourceEncoded, compressor))
            || !encode_block(block.decoded,
                             keys,
                             package.packageId,
                             block.record,
                             compressor,
                             authoredEncoded,
                             stored)
            || !validate_block(stored, block.decoded, keys, package.packageId, block.record)) {
            return false;
        }
        report_oodle_stream("source", block.index, sourceEncoded);
        report_oodle_stream("authored", block.index, authoredEncoded);
        report_block_encoding(
            block.index, block.decoded.size(), stored.size(), block.record.flags, compressor);
        sha1::Digest storedDigest{};
        if (!sha1::hash(stored, storedDigest)) {
            return false;
        }
        block.record.opaque = storedDigest;
        const std::uint32_t bodyPatch = block.record.patchId;
        const auto owner =
            std::find_if(owners.begin(), owners.end(), [bodyPatch](const auto& file) {
                return file.patchId == bodyPatch;
            });
        const bool preserveOwner = bodyPatch != newPatch;
        if (preserveOwner && (owner == owners.end() || block.index >= owner->blockCount)) {
            return false;
        }
        std::vector<std::byte>& bodyFile = preserveOwner ? owner->bytes : package.bytes;
        const std::size_t bodyOffset = aligned(bodyFile.size());
        bodyFile.resize(bodyOffset);
        bodyFile.insert(bodyFile.end(), stored.begin(), stored.end());
        if (bodyOffset > (std::numeric_limits<std::uint32_t>::max)()
            || stored.size() > (std::numeric_limits<std::uint32_t>::max)()) {
            return false;
        }
        block.record.offset = static_cast<std::uint32_t>(bodyOffset);
        block.record.size = static_cast<std::uint32_t>(stored.size());
        block.record.patchId = static_cast<std::uint16_t>(bodyPatch);
        if (!write_value(package.bytes,
                         package.blockTable
                             + static_cast<std::uint64_t>(block.index) * sizeof block.record,
                         block.record)) {
            return false;
        }
        if (preserveOwner
            && !write_value(owner->bytes,
                            owner->blockTable
                                + static_cast<std::uint64_t>(block.index) * sizeof block.record,
                            block.record)) {
            return false;
        }
    }
    package.bytes.resize(aligned(package.bytes.size()));
    for (OwnerPatchFile& owner : owners) {
        owner.bytes.resize(aligned(owner.bytes.size()));
    }
    if (package.bytes.size() > (std::numeric_limits<std::uint32_t>::max)()
        || package.bytes.size() > kMaximumPatchBytes) {
        return false;
    }
    const std::uint16_t patchField = static_cast<std::uint16_t>(newPatch);
    const std::uint32_t fileSize = static_cast<std::uint32_t>(package.bytes.size());
    bool complete = write_value(package.bytes, layout::HeaderOffsets::kPatchId, patchField)
                    && write_value(package.bytes, kHeaderFileSizeOffset, fileSize);
    for (OwnerPatchFile& owner : owners) {
        if (!complete || owner.bytes.size() > (std::numeric_limits<std::uint32_t>::max)()
            || owner.bytes.size() > kMaximumPatchBytes) {
            return false;
        }
        const std::uint32_t ownerSize = static_cast<std::uint32_t>(owner.bytes.size());
        complete = write_value(owner.bytes, kHeaderFileSizeOffset, ownerSize);
    }
    return complete;
}

} // namespace

/** Builds a staged VFX-branch draft containing its sky and, optionally, a tiled baseplate. */
bool stage_pandora_map_root(std::string_view rootName, bool includeTiledBaseplate) noexcept {
    state::content::Definition root{};
    if (rootName != kPandoraMapRoot || !resolve_map_root(rootName, root)
        || tables::package_of(root.tag) != kPandoraMapPackageId
        || tables::package_of(kPandoraVfxMapBranch) != kPandoraMapPackageId) {
        report("resolve_root", "missing");
        return false;
    }

    reader::BlockKeys keys{};
    core::path::Buffer directory{};
    if (!item_packages::collect_keys(keys) || !item_packages::package_directory(directory)) {
        SecureZeroMemory(&keys, sizeof keys);
        report("keys", "unavailable", kPandoraMapPackageId);
        return false;
    }
    const reader::Source source{directory.chars.data(), &keys};
    auto scratch = std::make_unique<reader::Scratch>();
    PackageFile package{};
    TowerPatchStats graphStats{};
    PandoraSkyDraftStats stats{};
    std::vector<std::uint32_t> mapTables{};
    bool complete =
        scratch != nullptr && load_package(source.directory, kPandoraMapPackageId, package)
        && collect_map_tables(kPandoraVfxMapBranch, source, *scratch, mapTables, graphStats);
    stats.nodes = graphStats.nodes;
    if (complete) {
        const auto append_table = [&mapTables](std::uint32_t tableTag) {
            if (std::find(mapTables.begin(), mapTables.end(), tableTag) == mapTables.end()) {
                mapTables.push_back(tableTag);
            }
        };
        append_table(kPandoraVfxSkyTable);
        if (includeTiledBaseplate) {
            for (const PandoraBaseplateTile& tile : kPandoraBaseplateTiles) {
                append_table(tile.tableTag);
            }
        }
    }
    stats.tables = mapTables.size();

    std::vector<MutableBlock> blocks{};
    std::vector<std::uint32_t> touchedTables{};
    std::vector<std::byte> sourceTable{};
    std::vector<std::byte> entityBytes{};
    core::Transform baseplateTransform{};
    if (complete && includeTiledBaseplate) {
        std::uint32_t sourceClass = 0;
        std::size_t entriesOffset = 0;
        std::uint32_t entryCount = 0;
        std::size_t resourceOffset = 0;
        std::uint32_t resourceClass = 0;
        std::uint32_t parentTag = 0;
        complete = reader::read_tag(source,
                                    *scratch,
                                    kPandoraBaseplateStaticTable,
                                    sourceTable,
                                    sourceClass)
                   && sourceClass == kMapDataTableClass
                   && map_table_layout(sourceTable, entriesOffset, entryCount) && entryCount == 1
                   && map_resource(sourceTable, entriesOffset, resourceOffset, resourceClass)
                   && resourceClass == kStaticMapResourceClass
                   && resourceOffset <= sourceTable.size()
                   && kStaticMapParentOffset + sizeof(parentTag)
                          <= sourceTable.size() - resourceOffset
                   && read_value(
                       sourceTable, resourceOffset + kStaticMapParentOffset, parentTag)
                   && parentTag == kPandoraBaseplateStaticParent
                   && read_map_transform(sourceTable, entriesOffset, baseplateTransform)
                   && validate_static_parent(source, *scratch, kPandoraBaseplateStaticParent);
        if (complete
            && !pandora_baseplate_tile_spacing(source, *scratch, stats.tileSpacing)) {
            stats.tileSpacing = 24.0F;
            report("pandora_baseplate_spacing",
                   "fallback",
                   kPandoraMapPackageId,
                   package.latestPatch,
                   kPandoraBaseplateStaticParent,
                   24);
        }
        report("pandora_baseplate_preflight",
               complete ? "ok" : "fail",
               kPandoraMapPackageId,
               sourceClass,
               entryCount,
               parentTag);
    }
    for (const std::uint32_t tableTag : mapTables) {
        if (!complete) {
            break;
        }
        if (tables::package_of(tableTag) != kPandoraMapPackageId) {
            continue;
        }
        std::uint32_t sourceClass = 0;
        std::size_t entriesOffset = 0;
        std::uint32_t entryCount = 0;
        if (!reader::read_tag(source, *scratch, tableTag, sourceTable, sourceClass)
            || sourceClass != kMapDataTableClass
            || !map_table_layout(sourceTable, entriesOffset, entryCount)) {
            complete = false;
            break;
        }

        const auto tile = std::find_if(
            kPandoraBaseplateTiles.begin(),
            kPandoraBaseplateTiles.end(),
            [tableTag](const PandoraBaseplateTile& candidate) {
                return candidate.tableTag == tableTag;
            });
        const bool tileTable = includeTiledBaseplate && tile != kPandoraBaseplateTiles.end();
        if (tileTable && entryCount != 1) {
            complete = false;
            break;
        }
        std::vector<std::uint32_t> suppressed{};
        suppressed.reserve(entryCount);
        for (std::uint32_t index = 0; index < entryCount; ++index) {
            const std::size_t entryOffset =
                entriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            std::size_t resourceOffset = 0;
            std::uint32_t resourceClass = 0;
            if (!map_resource(sourceTable, entryOffset, resourceOffset, resourceClass)) {
                std::uint8_t objectType = 0;
                if (!map_entity(sourceTable, entryOffset, source, *scratch, entityBytes)
                    || !entity_object_type(entityBytes, objectType)) {
                    complete = false;
                    break;
                }
                ++stats.placements;
                if (suppressed_standalone_entity_type(objectType) != nullptr) {
                    suppressed.push_back(index);
                } else {
                    ++stats.preservedInfrastructurePlacements;
                }
                continue;
            }
            ++stats.placements;
            if (resourceClass == kSkyObjectPlacementResourceClass) {
                std::uint32_t collectionTag = 0;
                std::vector<std::byte> collection{};
                const bool exactVfxSky =
                    tableTag == kPandoraVfxSkyTable && index == 0 && entryCount == 1
                    && linked_resource_tag(sourceTable,
                                           resourceOffset,
                                           source,
                                           *scratch,
                                           kSkyObjectCollectionClass,
                                           collectionTag,
                                           collection);
                report("pandora_sky_collection",
                       exactVfxSky ? "ok" : "fail",
                       kPandoraMapPackageId,
                       package.latestPatch,
                       collectionTag,
                       collection.size());
                if (!exactVfxSky) {
                    complete = false;
                    break;
                }
                ++stats.preservedSkyPlacements;
                continue;
            }
            if (tileTable && index == 0) {
                std::uint32_t parentTag = 0;
                const bool exactBaseplateSlot =
                    resourceClass == kStaticMapResourceClass
                    && resourceOffset <= sourceTable.size()
                    && kStaticMapParentOffset + sizeof(parentTag)
                           <= sourceTable.size() - resourceOffset
                    && read_value(
                        sourceTable, resourceOffset + kStaticMapParentOffset, parentTag)
                    && (parentTag == tile->sourceParentTag
                        || parentTag == kPandoraBaseplateStaticParent);
                if (!exactBaseplateSlot) {
                    complete = false;
                    break;
                }
                ++stats.baseplateTiles;
                continue;
            }
            if (resourceClass == kTowerVisibilityBundleResourceClass
                || resourceClass == kTowerDirectHavokResourceClass
                || resourceClass == kTowerEntityModelResourceClass) {
                ++stats.preservedInfrastructurePlacements;
                continue;
            }
            if (resourceClass != kStaticMapResourceClass) {
                std::uint8_t objectType = 0;
                if (!map_entity_owner(
                        sourceTable, entryOffset, source, *scratch, entityBytes)
                    || !entity_object_type(entityBytes, objectType)
                    || suppressed_standalone_entity_type(objectType) == nullptr) {
                    ++stats.preservedInfrastructurePlacements;
                    continue;
                }
            }
            suppressed.push_back(index);
        }
        if (!complete || (suppressed.empty() && !tileTable)) {
            continue;
        }

        std::span<std::byte> table{};
        std::uint32_t mutableClass = 0;
        if (!mutable_entry(source, *scratch, package, tableTag, blocks, table, mutableClass)
            || mutableClass != kMapDataTableClass) {
            complete = false;
            break;
        }
        if (tileTable) {
            const std::size_t entryOffset = entriesOffset;
            std::size_t resourceOffset = 0;
            std::uint32_t resourceClass = 0;
            std::uint32_t parentTag = 0;
            const core::Transform target = tiled_pandora_transform(
                baseplateTransform, stats.tileSpacing, tile->gridOffset);
            if (!map_resource(table, entryOffset, resourceOffset, resourceClass)
                || resourceClass != kStaticMapResourceClass || resourceOffset > table.size()
                || kStaticMapParentOffset + sizeof(parentTag) > table.size() - resourceOffset
                || !read_value(table, resourceOffset + kStaticMapParentOffset, parentTag)
                || (parentTag != tile->sourceParentTag
                    && parentTag != kPandoraBaseplateStaticParent)
                || !write_value(table,
                                resourceOffset + kStaticMapParentOffset,
                                kPandoraBaseplateStaticParent)
                || !write_map_transform(table, entryOffset, target)) {
                complete = false;
                break;
            }
        }
        for (const std::uint32_t index : suppressed) {
            const std::size_t entryOffset =
                entriesOffset + static_cast<std::size_t>(index) * kMapEntryStride;
            core::Transform transform{};
            if (!read_map_transform(table, entryOffset, transform)) {
                complete = false;
                break;
            }
            transform.translation.z = kSuppressedStandaloneEntityHeight;
            transform.uniformScale = kSuppressedStandaloneEntityScale;
            if (!write_map_transform(table, entryOffset, transform)) {
                complete = false;
                break;
            }
            ++stats.suppressedPlacements;
        }
        if (complete) {
            touchedTables.push_back(tableTag);
        }
    }
    std::sort(touchedTables.begin(), touchedTables.end());
    touchedTables.erase(std::unique(touchedTables.begin(), touchedTables.end()),
                        touchedTables.end());
    stats.touchedTables = touchedTables.size();
    complete = complete && stats.tables != 0 && stats.placements != 0
               && stats.preservedSkyPlacements == 1
               && stats.baseplateTiles
                          == (includeTiledBaseplate ? kPandoraBaseplateTiles.size() : 0)
               && stats.suppressedPlacements + stats.preservedSkyPlacements
                              + stats.baseplateTiles
                              + stats.preservedInfrastructurePlacements
                      == stats.placements
               && !blocks.empty();

    const std::uint32_t newPatch = package.latestPatch + 1;
    std::vector<OwnerPatchFile> owners{};
    if (complete) {
        complete = load_owner_patch_files(package, blocks, newPatch, owners)
                   && append_modified_blocks(package, blocks, keys, newPatch, owners);
    }

    std::size_t stagedBytes = package.bytes.size();
    if (complete) {
        reader::Path nextPath{};
        std::wstring stagedPath{};
        complete = reader::build_path(package.stem, newPatch, nextPath);
        if (complete) {
            stagedPath.assign(nextPath.chars.data());
            stagedPath += L".izanami-stage";
            for (const OwnerPatchFile& owner : owners) {
                std::wstring ownerStagedPath{owner.path.chars.data()};
                ownerStagedPath += L".izanami-owner-stage";
                if (!write_file(ownerStagedPath, owner.bytes)) {
                    complete = false;
                    break;
                }
                stagedBytes += owner.bytes.size();
            }
            complete = complete && write_file(stagedPath, package.bytes);
        }
    }
    if (scratch != nullptr) {
        reader::close_files(*scratch);
    }
    SecureZeroMemory(&keys, sizeof keys);
    report(includeTiledBaseplate ? "stage_pandora_blank_baseplate" : "stage_pandora_vfx_sky",
           complete ? "ok" : "fail",
           kPandoraMapPackageId,
           newPatch,
           static_cast<std::uint32_t>(blocks.size()),
           complete ? stagedBytes : 0);
    std::array<char, core::log::kLineCapacity> line{};
    const int written = std::snprintf(line.data(),
                                      line.size(),
                                      "ev=izanami_package stage=%s result=%s "
                                      "branch=%08X nodes=%zu tables=%zu placements=%zu "
                                      "suppressed=%zu preserved_sky=%zu baseplate_tiles=%zu "
                                      "preserved_infrastructure=%zu tile_spacing=%.3f "
                                      "touched_tables=%zu",
                                      includeTiledBaseplate ? "pandora_blank_baseplate_plan"
                                                            : "pandora_sky_plan",
                                      complete ? "ok" : "fail",
                                      kPandoraVfxMapBranch,
                                      stats.nodes,
                                      stats.tables,
                                      stats.placements,
                                      stats.suppressedPlacements,
                                      stats.preservedSkyPlacements,
                                      stats.baseplateTiles,
                                      stats.preservedInfrastructurePlacements,
                                      static_cast<double>(stats.tileSpacing),
                                      stats.touchedTables);
    if (written > 0) {
        core::log::write(core::log::Channel::server,
                         complete ? core::log::Level::info : core::log::Level::warn,
                         {line.data(), static_cast<std::size_t>(written)});
    }
    return complete;
}

/** Catalogs source-validated Tower placements for binding into Forge scene objects. */
bool discover_static_placements(std::string_view rootName,
                                std::span<StaticPlacementCandidate> output,
                                std::size_t& count) noexcept {
    count = 0;
    state::content::Definition root{};
    if (output.empty() || !resolve_tower_root(rootName, root)) {
        report("catalog_tower_placements", "root_unavailable", kTowerMapPackageId);
        return false;
    }

    reader::BlockKeys keys{};
    core::path::Buffer directory{};
    if (!item_packages::collect_keys(keys) || !item_packages::package_directory(directory)) {
        SecureZeroMemory(&keys, sizeof keys);
        report("catalog_tower_placements", "keys_unavailable", kTowerMapPackageId);
        return false;
    }
    const reader::Source source{directory.chars.data(), &keys};
    auto scratch = std::make_unique<reader::Scratch>();
    TowerPatchStats stats{};
    std::vector<std::uint32_t> mapTables{};
    std::vector<StaticPlacementCandidate> candidates{};
    bool complete = scratch != nullptr
                    && collect_map_tables(root.tag, source, *scratch, mapTables, stats)
                    && collect_static_candidates(
                        mapTables, source, *scratch, candidates, stats, kTowerMapPackageId);
    if (complete) {
        std::sort(candidates.begin(), candidates.end(), candidate_less);
        count = (std::min)(output.size(), candidates.size());
        std::copy_n(candidates.begin(), count, output.begin());

        const auto aggregate =
            std::find_if(candidates.begin(), candidates.end(), is_known_tower_aggregate);
        if (aggregate != candidates.end()) {
            const bool copied =
                std::any_of(output.begin(), output.begin() + count, is_known_tower_aggregate);
            if (!copied && count != 0) {
                output[count - 1] = *aggregate;
            }
        }
        const std::size_t reportCount = (std::min)(candidates.size(), kReportedPlacementCandidates);
        for (std::size_t index = 0; index < reportCount; ++index) {
            report_tower_candidate(index, candidates[index]);
        }
        if (aggregate != candidates.end()
            && static_cast<std::size_t>(aggregate - candidates.begin()) >= reportCount) {
            report_tower_candidate(static_cast<std::size_t>(aggregate - candidates.begin()),
                                   *aggregate);
        }
    }
    if (scratch != nullptr) {
        reader::close_files(*scratch);
    }
    SecureZeroMemory(&keys, sizeof keys);
    complete = complete && count != 0;
    report_tower_plan(complete ? "ok" : "fail", kTowerMapPackageId, stats);
    report("catalog_tower_placements",
           complete ? "ok" : "fail",
           kTowerMapPackageId,
           0,
           static_cast<std::uint32_t>(count));
    return complete;
}

bool discover_authored_static_placements(std::string_view rootName,
                                         std::span<StaticPlacementCandidate> output,
                                         std::size_t& count) noexcept {
    count = 0;
    state::content::Definition root{};
    if (output.empty() || !resolve_map_root(rootName, root)) {
        report("catalog_map_placements", "root_unavailable");
        return false;
    }

    reader::BlockKeys keys{};
    core::path::Buffer directory{};
    if (!item_packages::collect_keys(keys) || !item_packages::package_directory(directory)) {
        SecureZeroMemory(&keys, sizeof keys);
        report("catalog_map_placements", "keys_unavailable");
        return false;
    }
    const reader::Source source{directory.chars.data(), &keys};
    auto scratch = std::make_unique<reader::Scratch>();
    TowerPatchStats stats{};
    std::vector<std::uint32_t> mapTables{};
    std::vector<StaticPlacementCandidate> candidates{};
    bool complete = scratch != nullptr
                    && collect_map_tables(root.tag, source, *scratch, mapTables, stats)
                    && collect_static_candidates(
                        mapTables, source, *scratch, candidates, stats, tables::kAbsentPackageId);
    if (complete) {
        std::sort(candidates.begin(), candidates.end(), candidate_less);
        count = (std::min)(output.size(), candidates.size());
        std::copy_n(candidates.begin(), count, output.begin());
    }
    if (scratch != nullptr) {
        reader::close_files(*scratch);
    }
    SecureZeroMemory(&keys, sizeof keys);
    complete = complete && count != 0;
    report("catalog_map_placements",
           complete ? "ok" : "fail",
           tables::package_of(root.tag),
           static_cast<std::uint32_t>(mapTables.size()),
           static_cast<std::uint32_t>(count));
    return complete;
}

bool discover_authored_placements(std::string_view rootName,
                                  std::span<AuthoredPlacementCandidate> output,
                                  std::size_t& count,
                                  AuthoredPlacementStats& stats) noexcept {
    count = 0;
    stats = {};
    state::content::Definition root{};
    if (output.empty() || !resolve_map_root(rootName, root)) {
        report("catalog_authored_world", "root_unavailable");
        return false;
    }

    reader::BlockKeys keys{};
    core::path::Buffer directory{};
    if (!item_packages::collect_keys(keys) || !item_packages::package_directory(directory)) {
        SecureZeroMemory(&keys, sizeof keys);
        report("catalog_authored_world", "keys_unavailable", tables::package_of(root.tag));
        return false;
    }
    const reader::Source source{directory.chars.data(), &keys};
    auto scratch = std::make_unique<reader::Scratch>();
    TowerPatchStats graphStats{};
    std::vector<std::uint32_t> mapTables{};
    std::vector<AuthoredPlacementCandidate> candidates{};
    bool complete =
        scratch != nullptr
        && collect_map_tables(root.tag,
                              source,
                              *scratch,
                              mapTables,
                              graphStats,
                              kAuthoredCatalogGraphDepth,
                              kAuthoredCatalogGraphCapacity)
        && collect_authored_candidates(
            mapTables, source, *scratch, candidates, stats, tables::package_of(root.tag));
    if (complete) {
        count = (std::min)(output.size(), candidates.size());
        std::copy_n(candidates.begin(), count, output.begin());
        stats.emitted = count;
        stats.truncated = count != candidates.size();
    }
    if (scratch != nullptr) {
        reader::close_files(*scratch);
    }
    SecureZeroMemory(&keys, sizeof keys);
    complete = complete && count != 0;
    report("catalog_authored_world",
           complete ? "ok" : "fail",
           tables::package_of(root.tag),
           static_cast<std::uint32_t>(stats.mapTables),
           static_cast<std::uint32_t>(stats.placementRows),
           stats.emitted);
    return complete;
}

bool stage_authored_map_root(std::string_view rootName,
                             std::span<const AuthoredPlacementEdit> edits) noexcept {
    state::content::Definition root{};
    if (rootName != kPandoraMapRoot || edits.empty()
        || edits.size() > kMaximumAuthoredPlacementEdits || !resolve_map_root(rootName, root)
        || tables::package_of(root.tag) != kPandoraMapPackageId) {
        report("stage_authored_edits", "invalid", kPandoraMapPackageId);
        return false;
    }
    for (std::size_t index = 0; index < edits.size(); ++index) {
        const AuthoredPlacementEdit& edit = edits[index];
        if (!edit.binding.is_valid() || !edit.targetTransform.is_finite()
            || edit.targetTransform.uniformScale <= 0.0F
            || tables::package_of(edit.binding.tableTag) != kPandoraMapPackageId) {
            report("stage_authored_edits", "edit_invalid", kPandoraMapPackageId);
            return false;
        }
        for (std::size_t other = index + 1; other < edits.size(); ++other) {
            if (edit.binding.same_record(edits[other].binding)) {
                report("stage_authored_edits", "duplicate", kPandoraMapPackageId);
                return false;
            }
        }
    }

    reader::BlockKeys keys{};
    core::path::Buffer directory{};
    if (!item_packages::collect_keys(keys) || !item_packages::package_directory(directory)) {
        SecureZeroMemory(&keys, sizeof keys);
        report("stage_authored_edits", "keys_unavailable", kPandoraMapPackageId);
        return false;
    }
    const reader::Source source{directory.chars.data(), &keys};
    auto scratch = std::make_unique<reader::Scratch>();
    PackageFile package{};
    TowerPatchStats graphStats{};
    std::vector<std::uint32_t> mapTables{};
    bool complete = scratch != nullptr
                    && load_package(source.directory, kPandoraMapPackageId, package)
                    && collect_map_tables(root.tag,
                                          source,
                                          *scratch,
                                          mapTables,
                                          graphStats,
                                          kAuthoredCatalogGraphDepth,
                                          kAuthoredCatalogGraphCapacity);
    std::vector<MutableBlock> blocks{};
    blocks.reserve(edits.size());
    std::size_t applied = 0;
    for (const AuthoredPlacementEdit& edit : edits) {
        if (!complete) {
            break;
        }
        if (std::find(mapTables.begin(), mapTables.end(), edit.binding.tableTag)
            == mapTables.end()) {
            complete = false;
            break;
        }
        std::span<std::byte> table{};
        std::uint32_t tableClass = 0;
        if (!mutable_entry(
                source, *scratch, package, edit.binding.tableTag, blocks, table, tableClass)
            || tableClass != kMapDataTableClass
            || !apply_authored_placement_edit(edit.binding.tableTag, table, edit)) {
            complete = false;
            break;
        }
        ++applied;
    }
    complete = complete && applied == edits.size() && !blocks.empty();

    const std::uint32_t newPatch = package.latestPatch + 1;
    std::vector<OwnerPatchFile> owners{};
    if (complete) {
        complete = load_owner_patch_files(package, blocks, newPatch, owners)
                   && append_modified_blocks(package, blocks, keys, newPatch, owners);
    }
    std::size_t stagedBytes = package.bytes.size();
    if (complete) {
        reader::Path nextPath{};
        std::wstring stagedPath{};
        complete = reader::build_path(package.stem, newPatch, nextPath);
        if (complete) {
            stagedPath.assign(nextPath.chars.data());
            stagedPath += L".izanami-stage";
            for (const OwnerPatchFile& owner : owners) {
                std::wstring ownerStagedPath{owner.path.chars.data()};
                ownerStagedPath += L".izanami-owner-stage";
                if (!write_file(ownerStagedPath, owner.bytes)) {
                    complete = false;
                    break;
                }
                stagedBytes += owner.bytes.size();
            }
            complete = complete && write_file(stagedPath, package.bytes);
        }
    }
    if (scratch != nullptr) {
        reader::close_files(*scratch);
    }
    SecureZeroMemory(&keys, sizeof keys);
    report("stage_authored_edits",
           complete ? "ok" : "fail",
           kPandoraMapPackageId,
           newPatch,
           static_cast<std::uint32_t>(applied),
           complete ? stagedBytes : 0);
    return complete;
}

/** Builds a Tower patch from explicit Forge-bound placements only. */
bool stage_tower_map_root(std::string_view rootName,
                          std::span<const MapPlacementEdit> edits) noexcept {
    state::content::Definition root{};
    if (edits.empty() || edits.size() > kMaximumPlacementEdits
        || !resolve_tower_root(rootName, root)) {
        report("resolve_tower_edits", "invalid", kTowerMapPackageId);
        return false;
    }
    const bool localBaseplateRequested =
        std::any_of(edits.begin(), edits.end(), [](const MapPlacementEdit& edit) {
            return edit.binding.tableTag == kKnownTowerAggregateTable
                   && edit.binding.entryIndex == kKnownTowerAggregateEntry
                   && edit.binding.parentTag == kKnownTowerAggregateParent
                   && edit.replacementParentTag == 0;
        });
    for (std::size_t index = 0; index < edits.size(); ++index) {
        if (!edits[index].binding.is_valid() || !edits[index].transform.is_finite()
            || edits[index].transform.uniformScale <= 0.0F
            || tables::package_of(edits[index].binding.tableTag) != kTowerMapPackageId) {
            report("validate_tower_edits", "invalid", kTowerMapPackageId);
            return false;
        }
        if (edits[index].replacementParentTag != 0
            && (edits[index].binding.tableTag != kKnownTowerAggregateTable
                || edits[index].binding.entryIndex != kKnownTowerAggregateEntry
                || edits[index].binding.parentTag != kKnownTowerAggregateParent
                || edits[index].replacementParentTag != kPandoraBaseplateStaticParent)) {
            report("validate_tower_edits", "replacement_denied", kTowerMapPackageId);
            return false;
        }
        for (std::size_t other = index + 1; other < edits.size(); ++other) {
            if (edits[index].binding.same_record(edits[other].binding)) {
                report("validate_tower_edits", "duplicate", kTowerMapPackageId);
                return false;
            }
        }
    }

    reader::BlockKeys keys{};
    core::path::Buffer directory{};
    if (!item_packages::collect_keys(keys) || !item_packages::package_directory(directory)) {
        SecureZeroMemory(&keys, sizeof keys);
        report("tower_keys", "unavailable", kTowerMapPackageId);
        return false;
    }
    const reader::Source source{directory.chars.data(), &keys};
    auto scratch = std::make_unique<reader::Scratch>();
    PackageFile package{};
    TowerPatchStats stats{};
    std::vector<std::uint32_t> mapTables{};
    bool complete = scratch != nullptr
                    && load_package(source.directory, kTowerMapPackageId, package)
                    && collect_map_tables(root.tag, source, *scratch, mapTables, stats);
    if (complete && package.latestPatch > kTowerPatchSlot) {
        complete = false;
        report("tower_patch_slot", "unsupported", kTowerMapPackageId, package.latestPatch);
    }
    std::vector<MutableBlock> blocks{};
    blocks.reserve(edits.size());
    std::vector<std::uint32_t> touchedTables{};
    for (const MapPlacementEdit& edit : edits) {
        if (!complete) {
            break;
        }
        if (std::find(mapTables.begin(), mapTables.end(), edit.binding.tableTag)
            == mapTables.end()) {
            complete = false;
            break;
        }
        if (edit.replacementParentTag != 0
            && !validate_static_parent(source, *scratch, edit.replacementParentTag)) {
            complete = false;
            report("validate_tower_edits", "replacement_unavailable", kTowerMapPackageId);
            break;
        }
        std::span<std::byte> table{};
        std::uint32_t tableClass = 0;
        if (!mutable_entry(
                source, *scratch, package, edit.binding.tableTag, blocks, table, tableClass)
            || tableClass != kMapDataTableClass
            || !apply_placement_edit(edit.binding.tableTag, table, edit)) {
            complete = false;
            break;
        }
        touchedTables.push_back(edit.binding.tableTag);
        ++stats.staticPlacements;
        ++stats.mutatedPlacements;
    }
    if (complete && localBaseplateRequested) {
        complete = validate_tower_collision_baseline(mapTables, source, *scratch, stats);
        report("tower_collision_baseline",
               complete ? "ok" : "fail",
               kTowerMapPackageId,
               package.latestPatch,
               static_cast<std::uint32_t>(stats.entityModelPlacements),
               stats.preservedEntityModelHavokReferences);
    }
    if (complete && localBaseplateRequested) {
        complete = substitute_tower_static_collision_mesh(source, *scratch, package, blocks, stats);
        report("tower_static_collision_mesh",
               complete ? "ok" : "fail",
               kTowerMapPackageId,
               package.latestPatch,
               static_cast<std::uint32_t>(stats.substitutedStaticMeshCollisionReferences),
               kTowerStaticCollisionSmallControlBytes);
    }
    if (complete && localBaseplateRequested) {
        complete = suppress_tower_standalone_scenery(
            mapTables, source, *scratch, package, blocks, touchedTables, stats);
        report("tower_standalone_scenery",
               complete ? "ok" : "fail",
               kTowerMapPackageId,
               package.latestPatch,
               static_cast<std::uint32_t>(stats.suppressedStandaloneEntities),
               stats.preservedStandaloneInteractiveEntities
                   + stats.preservedStandaloneSystemEntities);
    }
    if (complete && localBaseplateRequested) {
        complete = suppress_tower_component_scenery(
            mapTables, source, *scratch, package, blocks, touchedTables, stats);
        report("tower_component_scenery",
               complete ? "ok" : "fail",
               kTowerMapPackageId,
               package.latestPatch,
               static_cast<std::uint32_t>(stats.suppressedComponentSceneryEntities),
               stats.preservedComponentInteractiveEntities
                   + stats.preservedComponentSystemEntities);
    }
    if (complete && localBaseplateRequested) {
        complete = apply_tower_local_baseplate_payload(source, *scratch, package, blocks);
        report("tower_local_baseplate_payload",
               complete ? "ok" : "fail",
               kTowerMapPackageId,
               package.latestPatch,
               kTowerLocalBaseplateGroup,
               kTowerAggregatePayloadSize);
    }
    std::sort(touchedTables.begin(), touchedTables.end());
    touchedTables.erase(std::unique(touchedTables.begin(), touchedTables.end()),
                        touchedTables.end());
    stats.localTables = touchedTables.size();
    complete = complete && stats.mutatedPlacements == edits.size();
    report_tower_plan(complete ? "ok" : "fail", kTowerMapPackageId, stats);

    const std::uint32_t newPatch =
        package.latestPatch < kTowerPatchSlot ? package.latestPatch + 1 : kTowerPatchSlot;
    std::vector<OwnerPatchFile> owners{};
    if (complete) {
        complete = load_owner_patch_files(package, blocks, newPatch, owners)
                   && append_modified_blocks(package, blocks, keys, newPatch, owners);
    }
    if (complete) {
        reader::Path nextPath{};
        std::wstring stagedPath{};
        complete = reader::build_path(package.stem, newPatch, nextPath);
        if (complete) {
            stagedPath.assign(nextPath.chars.data());
            stagedPath += L".izanami-stage";
            for (const OwnerPatchFile& owner : owners) {
                std::wstring ownerStagedPath{owner.path.chars.data()};
                ownerStagedPath += L".izanami-owner-stage";
                if (!write_file(ownerStagedPath, owner.bytes)) {
                    complete = false;
                    break;
                }
            }
            complete = complete && write_file(stagedPath, package.bytes);
        }
    }
    if (scratch != nullptr) {
        reader::close_files(*scratch);
    }
    SecureZeroMemory(&keys, sizeof keys);
    std::size_t stagedBytes = package.bytes.size();
    for (const OwnerPatchFile& owner : owners) {
        stagedBytes += owner.bytes.size();
    }
    report("stage_tower_baseplate",
           complete ? "ok" : "fail",
           kTowerMapPackageId,
           newPatch,
           static_cast<std::uint32_t>(blocks.size()),
           complete ? stagedBytes : 0);
    return complete;
}

/** Dispatches only to map roots whose no-edit package strategy is fully defined. */
bool stage_map_root(std::string_view rootName) noexcept {
    if (rootName == kPandoraMapRoot) {
        return stage_pandora_map_root(rootName, false);
    }
    report("resolve_root", rootName == kTowerMapRoot ? "tower_edits_required" : "unsupported");
    return false;
}

bool stage_pandora_baseplate_world(std::string_view rootName) noexcept {
    if (rootName != kPandoraMapRoot) {
        report("resolve_root", "unsupported");
        return false;
    }
    return stage_pandora_map_root(rootName, true);
}

/** Dispatches explicit placement edits only to the validated Tower package strategy. */
bool stage_map_root(std::string_view rootName, std::span<const MapPlacementEdit> edits) noexcept {
    if (rootName == kTowerMapRoot) {
        return stage_tower_map_root(rootName, edits);
    }
    report("resolve_root", "placement_edits_unsupported");
    return false;
}

} // namespace sunrise::izanami::runtime::custom_package_builder
