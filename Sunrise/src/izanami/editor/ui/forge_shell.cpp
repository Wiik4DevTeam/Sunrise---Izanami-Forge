#include "forge_shell.h"

#include <Windows.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <imgui.h>
#include <iterator>
#include <limits>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "../../../client/content/items/packages/internal.h"
#include "../../../client/hooks/fly/fly.h"
#include "../../../client/hooks/spawn/spawn_runtime.h"
#include "../../../client/hooks/teleport/runtime.h"
#include "../../../client/movement/movement_settings_store.h"
#include "../../../core/logging/log.h"
#include "../../../middleware/content/packages/named_tags.h"
#include "../../../middleware/content/packages/reader/reader.h"
#include "../../../middleware/content/packages/tables/scenario_reader.h"
#include "../../../state/build_data/runtime.h"
#include "../../fate/map_recipe.h"
#include "../../research/native_object_types.h"
#include "../../runtime/custom_package_builder.h"
#include "../workspace/editor_workspace.h"
#include "asset_metadata_store.h"
#include "izanami_panel.h"

namespace sunrise::izanami::editor::ui::forge_shell {
namespace {

namespace item_packages = sunrise::client::content::items::packages;
namespace fly = sunrise::client::hooks::fly;
namespace native_spawn = sunrise::client::hooks::spawn;
namespace teleport = sunrise::client::hooks::teleport;
namespace movement = sunrise::client::movement;
namespace package_reader = sunrise::middleware::content::packages::reader;
namespace recipe = sunrise::izanami::fate::recipe;
namespace research = sunrise::izanami::research;
namespace workspace = sunrise::izanami::editor::workspace;

constexpr std::uint32_t kEntityDefinitionClass = 0x80809C0FU;
constexpr std::uint32_t kFieldProvenChandelierTag = 0x80B6C246U;
constexpr std::uint32_t kInvalidHandle = 0xFFFFFFFFU;
constexpr float kQuarantineDepth = 10000.0F;
constexpr float kQuarantineScale = 0.0001F;
constexpr char kAssetPayload[] = "IZANAMI_ASSET_TAG";
constexpr char kActorPayload[] = "IZANAMI_TRACKED_ACTOR";
constexpr char kNativeDeleteBlocker[] =
    "Experimental remove: Forge objects are undoable; supported map objects restore on reload";
constexpr float kTopBarHeight = 44.0F;
constexpr float kRibbonHeight = 60.0F;
constexpr float kOutputHeight = 72.0F;
constexpr float kStatusHeight = 22.0F;
constexpr float kBodyBottomReserve = 6.0F;
constexpr float kAssetPanelMinimumWidth = 190.0F;
constexpr float kAssetPanelMaximumWidth = 300.0F;
constexpr float kRightPanelMinimumWidth = 230.0F;
constexpr float kRightPanelMaximumWidth = 340.0F;
constexpr std::uint64_t kMapActorIdMask = 0x8000000000000000ULL;
constexpr std::uint64_t kAuthoredActorIdMask = 0x4000000000000000ULL;
constexpr std::size_t kAuthoredPlacementCapacity = 4096;
constexpr std::size_t kEntityObjectTypeOffset = 0x96;
constexpr std::size_t kCatalogReadsPerFrame = 32;
constexpr std::size_t kResidencyChecksPerFrame = 256;

enum class ActorSource : std::uint8_t {
    forge,
    liveMap,
    authoredMap,
};

enum class RibbonTab : std::uint8_t {
    file,
    home,
    view,
    test,
};

enum class TransformMode : std::uint8_t {
    select,
    move,
    rotate,
    scale,
};

enum class AssetScope : std::uint8_t {
    all,
    renamed,
    unknown,
    unnamed,
};

enum class AssetAvailability : std::uint8_t {
    all,
    resident,
    nonresident,
};

enum class AssetSort : std::uint8_t {
    tag,
    nameAscending,
    nameDescending,
    category,
    source,
};

enum class Icon : std::uint8_t {
    save,
    load,
    select,
    move,
    rotate,
    scale,
    undo,
    redo,
    duplicate,
    remove,
    refresh,
    probe,
    close,
};

struct AssetRecord {
    std::uint32_t tag{};
    std::uint32_t definitionSize{};
    std::uint8_t objectType{};
    std::array<char, 96> packageFamily{};
    bool typeKnown{};
    bool definitionRead{};
    bool resident{};
};

struct WorldCatalogRecord {
    std::string name{};
    std::string mapRoot{};
    std::uint32_t tag{};
    std::uint8_t bubbleCount{};
    std::uint8_t rosterGroupCount{};
    std::uint8_t packageCount{};
    std::uint32_t patchIndex{};
    bool validatedLayout{};
};

struct TrackedActor {
    std::uint64_t editorId{};
    std::uint64_t parentId{};
    std::string name{};
    std::uint32_t tag{};
    std::uint32_t handle{kInvalidHandle};
    std::uint32_t tableTag{};
    std::uint32_t entryIndex{};
    std::uint32_t parentTag{};
    std::uint8_t objectType{};
    core::Transform transform{};
    ActorSource source{ActorSource::forge};
    native_spawn::WorldObjectIdentity identity{native_spawn::WorldObjectIdentity::definitionTag};
    bool transformKnown{true};
    bool nativeExpired{};
};

struct SpawnCommand {
    std::uint64_t editorId{};
    std::uint64_t parentId{};
    std::string name{};
    std::uint32_t tag{};
    std::uint8_t objectType{};
    core::Transform transform{};
    bool absolute{};
    bool additiveSelection{};
};

struct TransformEdit {
    std::uint64_t actorId{};
    core::Transform before{};
    core::Transform after{};
};

enum class GizmoAxis : std::uint8_t {
    none,
    x,
    y,
    z,
};

struct GizmoDrag {
    std::uint64_t actorId{};
    GizmoAxis axis{GizmoAxis::none};
    TransformMode mode{TransformMode::select};
    ImVec2 startMouse{};
    ImVec2 screenDirection{};
    core::Transform startTransform{};
    float worldUnitsPerPixel{};
    bool active{};
};

struct ShellState {
    RibbonTab ribbon{RibbonTab::home};
    TransformMode transformMode{TransformMode::select};
    bool showAssetBrowser{true};
    bool showExplorer{true};
    bool showProperties{true};
    bool showOutput{true};
    float spawnDistance{20.0F};
    float projectionHorizontalFov{82.0F};
    char assetFilter[96]{};
    char explorerFilter[96]{};
    char renameBuffer[160]{};
    char worldFilter[96]{};
    std::uint64_t renameActorId{};
    std::string loadTemplateId{"tower_carrier_control"};
    std::string loadWorldScenario{"city_tower_social_d2"};
    std::string loadedWorldName{"city_tower_social_d2"};
    std::string loadedMapRoot{"map:city_tower_d2:root"};
    bool loadCatalogWorld{true};
    int typeFilter{-1};
    AssetScope assetScope{AssetScope::all};
    AssetAvailability assetAvailability{AssetAvailability::all};
    AssetSort assetSort{AssetSort::tag};
    std::array<char, 96> assetSourceFilter{};
    std::vector<AssetRecord> assets{};
    std::vector<WorldCatalogRecord> worlds{};
    bool worldCatalogReady{};
    bool worldCatalogValidated{};
    std::vector<asset_metadata::Entry> assetMetadata{};
    std::array<std::size_t, 256> typeCounts{};
    package_reader::ScanResult scan{};
    std::unique_ptr<package_reader::Scratch> catalogScratch{};
    std::size_t catalogDecodeCursor{};
    std::size_t catalogDecodeFailures{};
    std::size_t catalogResidencyCursor{};
    std::size_t catalogResidentCount{};
    double nextResidencySweep{};
    bool catalogScanned{};
    bool catalogReady{};
    bool catalogDecodeActive{};
    bool catalogMetadataComplete{};
    bool catalogResidencyExpanded{};
    bool assetMetadataLoaded{};
    std::uint32_t assetContextTag{};
    char assetContextName[97]{};
    std::array<float, 3> assetContextColor{};
    bool assetContextCustomColor{};
    std::vector<TrackedActor> actors{};
    std::vector<TrackedActor> quarantinedActors{};
    native_spawn::WorldObjectScan worldScan{};
    bool worldObjectsScanned{};
    std::vector<SpawnCommand> spawnQueue{};
    std::vector<TransformEdit> undo{};
    std::vector<TransformEdit> redo{};
    GizmoDrag gizmoDrag{};
    std::uint64_t nextActorId{1};
    std::uint64_t selectedActorId{};
    std::uint64_t selectionAnchorId{};
    std::vector<std::uint64_t> selectedActorIds{};
    std::uint32_t selectedAssetTag{};
    std::uint64_t submittedSequence{};
    bool spawnInFlight{};
    native_spawn::RaycastProbe probe{};
    bool probeAttempted{};
    double nextLifetimeCheck{};
    std::array<char, 320> status{"Forge ready"};
};

std::atomic_bool g_cameraControl{};
std::atomic_bool g_worldRefreshRequested{true};

[[nodiscard]] ShellState& state() noexcept {
    static ShellState value;
    return value;
}

template <typename... Arguments>
void set_status(ShellState& shell, const char* format, Arguments... arguments) noexcept {
    (void)std::snprintf(shell.status.data(), shell.status.size(), format, arguments...);
}

[[nodiscard]] std::string lowercase(std::string_view value) {
    std::string result;
    result.reserve(value.size());
    for (char ch : value) {
        result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    }
    return result;
}

[[nodiscard]] bool contains_lower(std::string_view value, std::string_view filter) {
    return filter.empty() || lowercase(value).find(filter) != std::string::npos;
}

[[nodiscard]] std::string
world_map_root(const state::build_data::scenarios::Definition& definition) {
    if (definition.spawnStemLength == 0
        || definition.spawnStemLength > definition.spawnStem.size()) {
        return {};
    }
    std::string result{"map:"};
    result.append(definition.spawnStem.data(), definition.spawnStemLength);
    result += ":root";
    return result;
}

[[nodiscard]] int world_sort_rank(std::string_view name) noexcept {
    if (name == "city_tower_social_d2") {
        return 0;
    }
    if (name == "vfx_shade_test") {
        return 1;
    }
    return 2;
}

[[nodiscard]] std::string_view world_display_name(std::string_view name) noexcept {
    if (name == "city_tower_social_d2") {
        return "Tower (Normal D2)";
    }
    if (name == "vfx_shade_test") {
        return "VFX Shade Test Map";
    }
    return name;
}

bool collect_named_world(void* context,
                         const middleware::content::packages::named_tags::Entry& entry) noexcept {
    constexpr std::string_view kScenarioSuffix = ":scenario_client";
    auto& shell = *static_cast<ShellState*>(context);
    const std::string_view fullName{entry.name.data(), entry.nameLength};
    if (entry.classId != middleware::content::packages::tables::kScenarioClass
        || !fullName.ends_with(kScenarioSuffix)) {
        return true;
    }
    const std::string_view name = fullName.substr(0, fullName.size() - kScenarioSuffix.size());
    if (name.empty() || name.size() > state::build_data::scenarios::kNameCapacity) {
        return true;
    }
    const auto found = std::find_if(shell.worlds.begin(),
                                    shell.worlds.end(),
                                    [name](const auto& row) { return row.name == name; });
    if (found != shell.worlds.end()) {
        if (entry.patchIndex >= found->patchIndex) {
            found->tag = entry.tag;
            found->patchIndex = entry.patchIndex;
        }
        return true;
    }
    WorldCatalogRecord world{};
    world.name = name;
    world.tag = entry.tag;
    world.patchIndex = entry.patchIndex;
    if (name == "city_tower_social_d2") {
        world.mapRoot = "map:city_tower_d2:root";
    } else if (name == "vfx_shade_test") {
        world.mapRoot = "map:pandora:root";
    }
    shell.worlds.push_back(std::move(world));
    return true;
}

void sort_world_catalog(ShellState& shell) {
    std::sort(shell.worlds.begin(), shell.worlds.end(), [](const auto& left, const auto& right) {
        const int leftRank = world_sort_rank(left.name);
        const int rightRank = world_sort_rank(right.name);
        return leftRank == rightRank ? left.name < right.name : leftRank < rightRank;
    });
}

void refresh_world_catalog(ShellState& shell) {
    shell.worlds.clear();
    shell.worldCatalogReady = false;
    shell.worldCatalogValidated = false;
    std::array<state::build_data::scenarios::Definition,
               state::build_data::scenarios::kDefinitionCapacity>
        definitions{};
    std::size_t count = 0;
    if (!state::build_data::snapshot_scenario_layouts(definitions, count)) {
        ::sunrise::core::path::Buffer directory{};
        middleware::content::packages::named_tags::DirectoryResult result{};
        if (!item_packages::package_directory(directory)
            || !middleware::content::packages::named_tags::extract_directory(
                directory.chars.data(), &collect_named_world, &shell, result)) {
            return;
        }
        sort_world_catalog(shell);
        shell.worldCatalogReady = !shell.worlds.empty();
        return;
    }
    shell.worlds.reserve(count);
    for (const auto& definition : std::span(definitions).first(count)) {
        if (definition.nameLength == 0 || definition.nameLength > definition.name.size()) {
            continue;
        }
        WorldCatalogRecord world{};
        world.name.assign(definition.name.data(), definition.nameLength);
        world.mapRoot = world_map_root(definition);
        world.tag = definition.tag;
        world.bubbleCount = definition.bubbleCount;
        world.rosterGroupCount = definition.rosterGroupCount;
        world.packageCount = definition.packageCount;
        world.validatedLayout = true;
        shell.worlds.push_back(std::move(world));
    }
    sort_world_catalog(shell);
    shell.worldCatalogReady = !shell.worlds.empty();
    shell.worldCatalogValidated = shell.worldCatalogReady;
}

void family_text(std::wstring_view family, std::span<char> output) noexcept {
    std::fill(output.begin(), output.end(), '\0');
    const std::size_t count = (std::min)(family.size(), output.size() - 1);
    for (std::size_t index = 0; index < count; ++index) {
        output[index] =
            family[index] >= 32 && family[index] <= 126 ? static_cast<char>(family[index]) : '?';
    }
}

bool collect_asset(void* context, const package_reader::ClassEntry& entry) noexcept {
    auto& shell = *static_cast<ShellState*>(context);
    AssetRecord asset{};
    asset.tag = entry.tag;
    family_text(entry.packageFamily, asset.packageFamily);
    asset.resident = native_spawn::is_tag_resident(entry.tag);
    asset.typeKnown = asset.resident && native_spawn::object_type(entry.tag, asset.objectType);
    shell.assets.push_back(asset);
    return true;
}

void close_catalog_reader(ShellState& shell) noexcept {
    if (shell.catalogScratch != nullptr) {
        package_reader::close_files(*shell.catalogScratch);
        shell.catalogScratch.reset();
    }
    shell.catalogDecodeActive = false;
}

void recount_catalog(ShellState& shell) noexcept {
    shell.typeCounts = {};
    shell.catalogResidentCount = 0;
    shell.catalogResidencyExpanded = false;
    for (const AssetRecord& asset : shell.assets) {
        if (asset.typeKnown) {
            ++shell.typeCounts[asset.objectType];
        }
        if (asset.resident) {
            ++shell.catalogResidentCount;
        }
    }
}

void refresh_catalog(ShellState& shell) noexcept {
    close_catalog_reader(shell);
    shell.assets.clear();
    shell.typeCounts = {};
    shell.scan = {};
    shell.catalogDecodeCursor = 0;
    shell.catalogDecodeFailures = 0;
    shell.catalogResidencyCursor = 0;
    shell.catalogResidentCount = 0;
    shell.catalogScanned = true;
    shell.catalogReady = false;
    shell.catalogMetadataComplete = false;
    ::sunrise::core::path::Buffer directory{};
    if (!item_packages::package_directory(directory)) {
        set_status(shell, "Asset catalog unavailable: package directory was not resolved.");
        return;
    }
    shell.catalogReady = package_reader::scan_class_entries(
        directory.chars.data(), kEntityDefinitionClass, &collect_asset, &shell, shell.scan);
    package_reader::release_caches();
    std::sort(shell.assets.begin(), shell.assets.end(), [](const auto& left, const auto& right) {
        return left.tag < right.tag;
    });
    shell.assets.erase(
        std::unique(shell.assets.begin(),
                    shell.assets.end(),
                    [](const auto& left, const auto& right) { return left.tag == right.tag; }),
        shell.assets.end());
    recount_catalog(shell);
    if (shell.catalogReady && !shell.assets.empty()) {
        try {
            shell.catalogScratch = std::make_unique<package_reader::Scratch>();
            shell.catalogDecodeActive = true;
        } catch (...) {
            shell.catalogDecodeActive = false;
        }
    }
    if (shell.catalogReady && !shell.catalogDecodeActive) {
        shell.catalogMetadataComplete = true;
    }
    if (!shell.catalogReady) {
        set_status(shell, "Installed asset catalog scan failed.");
    } else if (!shell.catalogDecodeActive) {
        set_status(shell,
                   "Installed catalog indexed %zu definitions; metadata decoder unavailable.",
                   shell.assets.size());
    } else {
        set_status(shell,
                   "Installed catalog indexed %zu definitions; decoding package metadata.",
                   shell.assets.size());
    }
    g_worldRefreshRequested.store(true, std::memory_order_release);
}

void service_catalog_decode(ShellState& shell) noexcept {
    if (!shell.catalogDecodeActive || shell.catalogScratch == nullptr
        || shell.catalogDecodeCursor >= shell.assets.size()) {
        return;
    }

    package_reader::BlockKeys keys{};
    ::sunrise::core::path::Buffer directory{};
    if (!item_packages::package_directory(directory) || !item_packages::collect_keys(keys)) {
        SecureZeroMemory(&keys, sizeof keys);
        return;
    }

    const package_reader::Source source{directory.chars.data(), &keys};
    std::vector<std::byte> bytes;
    bytes.reserve(512);
    std::size_t processed = 0;
    while (shell.catalogDecodeCursor < shell.assets.size() && processed < kCatalogReadsPerFrame) {
        AssetRecord& asset = shell.assets[shell.catalogDecodeCursor++];
        const bool typeWasKnown = asset.typeKnown;
        const std::uint8_t priorType = asset.objectType;
        const bool wasResident = asset.resident;
        std::uint32_t classId = 0;
        const bool read =
            package_reader::read_tag(source, *shell.catalogScratch, asset.tag, bytes, classId);
        if (read && classId == kEntityDefinitionClass && bytes.size() > kEntityObjectTypeOffset) {
            asset.definitionRead = true;
            asset.definitionSize = static_cast<std::uint32_t>(
                (std::min)(bytes.size(),
                           static_cast<std::size_t>((std::numeric_limits<std::uint32_t>::max)())));
            asset.objectType = std::to_integer<std::uint8_t>(bytes[kEntityObjectTypeOffset]);
            asset.typeKnown = true;
        } else {
            ++shell.catalogDecodeFailures;
        }
        asset.resident = native_spawn::is_tag_resident(asset.tag);
        if (typeWasKnown && (!asset.typeKnown || priorType != asset.objectType)) {
            --shell.typeCounts[priorType];
        }
        if (asset.typeKnown && (!typeWasKnown || priorType != asset.objectType)) {
            ++shell.typeCounts[asset.objectType];
        }
        if (wasResident != asset.resident) {
            if (asset.resident) {
                ++shell.catalogResidentCount;
            } else if (shell.catalogResidentCount != 0) {
                --shell.catalogResidentCount;
            }
        }
        ++processed;
    }
    SecureZeroMemory(&keys, sizeof keys);

    if (shell.catalogDecodeCursor < shell.assets.size()) {
        return;
    }

    recount_catalog(shell);
    shell.catalogMetadataComplete = true;
    close_catalog_reader(shell);
    set_status(shell,
               "Installed catalog ready: %zu definitions, %zu resident, %zu unreadable.",
               shell.assets.size(),
               shell.catalogResidentCount,
               shell.catalogDecodeFailures);
    g_worldRefreshRequested.store(true, std::memory_order_release);
}

void service_catalog_residency(ShellState& shell) noexcept {
    if (!shell.catalogReady || shell.assets.empty()) {
        return;
    }
    if (!native_spawn::ready()) {
        if (shell.catalogResidentCount != 0) {
            for (AssetRecord& asset : shell.assets) {
                asset.resident = false;
            }
            shell.catalogResidentCount = 0;
        }
        return;
    }

    const double now = ImGui::GetTime();
    if (shell.catalogResidencyCursor == 0 && now < shell.nextResidencySweep) {
        return;
    }
    std::size_t processed = 0;
    while (shell.catalogResidencyCursor < shell.assets.size()
           && processed < kResidencyChecksPerFrame) {
        AssetRecord& asset = shell.assets[shell.catalogResidencyCursor++];
        const bool resident = native_spawn::is_tag_resident(asset.tag);
        shell.catalogResidencyExpanded =
            shell.catalogResidencyExpanded || (resident && !asset.resident);
        asset.resident = resident;
        if (resident && !asset.typeKnown) {
            asset.typeKnown = native_spawn::object_type(asset.tag, asset.objectType);
        }
        ++processed;
    }
    if (shell.catalogResidencyCursor >= shell.assets.size()) {
        shell.catalogResidencyCursor = 0;
        shell.nextResidencySweep = now + 0.75;
        recount_catalog(shell);
        if (shell.catalogResidencyExpanded) {
            g_worldRefreshRequested.store(true, std::memory_order_release);
        }
        shell.catalogResidencyExpanded = false;
    }
}

[[nodiscard]] const AssetRecord* find_asset(const ShellState& shell, std::uint32_t tag) noexcept {
    const auto found = std::find_if(shell.assets.begin(),
                                    shell.assets.end(),
                                    [tag](const auto& item) { return item.tag == tag; });
    return found == shell.assets.end() ? nullptr : &*found;
}

[[nodiscard]] asset_metadata::Entry* find_asset_metadata(ShellState& shell,
                                                         std::uint32_t tag) noexcept {
    const auto found = std::find_if(shell.assetMetadata.begin(),
                                    shell.assetMetadata.end(),
                                    [tag](const auto& entry) { return entry.tag == tag; });
    return found == shell.assetMetadata.end() ? nullptr : &*found;
}

[[nodiscard]] const asset_metadata::Entry* find_asset_metadata(const ShellState& shell,
                                                               std::uint32_t tag) noexcept {
    const auto found = std::find_if(shell.assetMetadata.begin(),
                                    shell.assetMetadata.end(),
                                    [tag](const auto& entry) { return entry.tag == tag; });
    return found == shell.assetMetadata.end() ? nullptr : &*found;
}

void ensure_asset_metadata(ShellState& shell) noexcept {
    if (shell.assetMetadataLoaded) {
        return;
    }
    shell.assetMetadataLoaded = true;
    std::string message;
    if (!asset_metadata::load(shell.assetMetadata, message)) {
        set_status(shell, "%s", message.c_str());
    }
}

[[nodiscard]] ImVec4 default_asset_color(std::uint8_t objectType) noexcept {
    const float hue = std::fmod(0.08F + static_cast<float>(objectType) * 0.173F, 1.0F);
    ImVec4 color = ImColor::HSV(hue, 0.34F, 0.18F, 0.97F);
    color.w = 0.97F;
    return color;
}

[[nodiscard]] ImVec4 asset_color(const ShellState& shell, const AssetRecord& asset) noexcept {
    const asset_metadata::Entry* const metadata = find_asset_metadata(shell, asset.tag);
    if (metadata == nullptr || !metadata->hasCustomColor) {
        if (!asset.typeKnown) {
            return {0.075F, 0.08F, 0.085F, 0.97F};
        }
        return default_asset_color(asset.objectType);
    }
    return {metadata->color[0], metadata->color[1], metadata->color[2], 0.97F};
}

[[nodiscard]] std::string_view custom_asset_name(const ShellState& shell,
                                                 std::uint32_t tag) noexcept {
    const asset_metadata::Entry* const metadata = find_asset_metadata(shell, tag);
    return metadata == nullptr ? std::string_view{} : std::string_view{metadata->name};
}

[[nodiscard]] std::string_view trim_name(std::string_view name) noexcept {
    while (!name.empty() && std::isspace(static_cast<unsigned char>(name.front())) != 0) {
        name.remove_prefix(1);
    }
    while (!name.empty() && std::isspace(static_cast<unsigned char>(name.back())) != 0) {
        name.remove_suffix(1);
    }
    return name;
}

[[nodiscard]] bool unknown_asset_name(std::string_view name) {
    name = trim_name(name);
    return !name.empty() && lowercase(name) == "unknown";
}

[[nodiscard]] bool asset_matches_scope(const ShellState& shell, const AssetRecord& asset) {
    const std::string_view name = trim_name(custom_asset_name(shell, asset.tag));
    switch (shell.assetScope) {
    case AssetScope::all:
        return true;
    case AssetScope::renamed:
        return !name.empty() && !unknown_asset_name(name);
    case AssetScope::unknown:
        return unknown_asset_name(name);
    case AssetScope::unnamed:
        return name.empty();
    }
    return true;
}

[[nodiscard]] bool asset_matches_availability(const ShellState& shell,
                                              const AssetRecord& asset) noexcept {
    switch (shell.assetAvailability) {
    case AssetAvailability::all:
        return true;
    case AssetAvailability::resident:
        return asset.resident;
    case AssetAvailability::nonresident:
        return !asset.resident;
    }
    return true;
}

[[nodiscard]] std::string_view asset_type_name(const AssetRecord& asset) noexcept {
    return asset.typeKnown ? research::native_object_type_name(asset.objectType)
                           : std::string_view{"Unclassified"};
}

[[nodiscard]] std::string_view asset_display_name(const ShellState& shell,
                                                  const AssetRecord& asset) noexcept {
    const std::string_view customName = custom_asset_name(shell, asset.tag);
    return customName.empty() ? asset_type_name(asset) : customName;
}

[[nodiscard]] bool case_insensitive_less(std::string_view left, std::string_view right) noexcept {
    const std::size_t count = (std::min)(left.size(), right.size());
    for (std::size_t index = 0; index < count; ++index) {
        const unsigned char leftByte = static_cast<unsigned char>(left[index]);
        const unsigned char rightByte = static_cast<unsigned char>(right[index]);
        const int leftLower = std::tolower(leftByte);
        const int rightLower = std::tolower(rightByte);
        if (leftLower != rightLower) {
            return leftLower < rightLower;
        }
    }
    return left.size() < right.size();
}

void persist_asset_metadata(ShellState& shell) noexcept {
    std::string message;
    const bool saved = asset_metadata::save(shell.assetMetadata, message);
    set_status(shell, "%s", message.c_str());
    if (!saved) {
        return;
    }
    std::sort(shell.assetMetadata.begin(),
              shell.assetMetadata.end(),
              [](const auto& left, const auto& right) { return left.tag < right.tag; });
}

void prepare_asset_context(ShellState& shell, const AssetRecord& asset) noexcept {
    shell.assetContextTag = asset.tag;
    shell.assetContextName[0] = '\0';
    const ImVec4 color = asset_color(shell, asset);
    shell.assetContextColor = {color.x, color.y, color.z};
    shell.assetContextCustomColor = false;
    if (const asset_metadata::Entry* const metadata = find_asset_metadata(shell, asset.tag);
        metadata != nullptr) {
        const std::size_t count =
            (std::min)(metadata->name.size(), sizeof(shell.assetContextName) - 1);
        std::memcpy(shell.assetContextName, metadata->name.data(), count);
        shell.assetContextName[count] = '\0';
        shell.assetContextCustomColor = metadata->hasCustomColor;
    }
}

void apply_asset_context(ShellState& shell, const AssetRecord& asset) noexcept {
    asset_metadata::Entry* metadata = find_asset_metadata(shell, asset.tag);
    if (metadata == nullptr) {
        shell.assetMetadata.push_back({.tag = asset.tag});
        metadata = &shell.assetMetadata.back();
    }
    metadata->name = shell.assetContextName;
    metadata->color = shell.assetContextColor;
    metadata->hasCustomColor = shell.assetContextCustomColor;
    if (metadata->name.empty() && !metadata->hasCustomColor) {
        shell.assetMetadata.erase(
            std::remove_if(shell.assetMetadata.begin(),
                           shell.assetMetadata.end(),
                           [&asset](const auto& entry) { return entry.tag == asset.tag; }),
            shell.assetMetadata.end());
    }
    persist_asset_metadata(shell);
}

[[nodiscard]] TrackedActor* find_actor(ShellState& shell, std::uint64_t id) noexcept {
    const auto found = std::find_if(shell.actors.begin(),
                                    shell.actors.end(),
                                    [id](const auto& actor) { return actor.editorId == id; });
    return found == shell.actors.end() ? nullptr : &*found;
}

[[nodiscard]] const TrackedActor* find_actor(const ShellState& shell, std::uint64_t id) noexcept {
    const auto found = std::find_if(shell.actors.begin(),
                                    shell.actors.end(),
                                    [id](const auto& actor) { return actor.editorId == id; });
    return found == shell.actors.end() ? nullptr : &*found;
}

[[nodiscard]] bool actor_selected(const ShellState& shell, std::uint64_t id) noexcept {
    return std::find(shell.selectedActorIds.begin(), shell.selectedActorIds.end(), id)
           != shell.selectedActorIds.end();
}

void clear_actor_selection(ShellState& shell) noexcept {
    shell.selectedActorId = 0;
    shell.selectionAnchorId = 0;
    shell.selectedActorIds.clear();
}

void add_actor_selection(ShellState& shell, std::uint64_t id) {
    if (find_actor(shell, id) == nullptr) {
        return;
    }
    if (!actor_selected(shell, id)) {
        shell.selectedActorIds.push_back(id);
    }
    shell.selectedActorId = id;
    shell.selectedAssetTag = 0;
}

void select_only_actor(ShellState& shell, std::uint64_t id) {
    clear_actor_selection(shell);
    add_actor_selection(shell, id);
    shell.selectionAnchorId = id;
}

void prune_actor_selection(ShellState& shell) {
    shell.selectedActorIds.erase(
        std::remove_if(shell.selectedActorIds.begin(),
                       shell.selectedActorIds.end(),
                       [&shell](std::uint64_t id) { return find_actor(shell, id) == nullptr; }),
        shell.selectedActorIds.end());
    if (find_actor(shell, shell.selectedActorId) == nullptr) {
        shell.selectedActorId = shell.selectedActorIds.empty() ? 0 : shell.selectedActorIds.back();
    }
    if (find_actor(shell, shell.selectionAnchorId) == nullptr) {
        shell.selectionAnchorId = shell.selectedActorId;
    }
}

[[nodiscard]] std::string actor_name(std::uint32_t tag, std::uint8_t objectType) {
    if (tag == kFieldProvenChandelierTag) {
        return "Field-Proven Chandelier";
    }
    const std::string_view type = research::native_object_type_name(objectType);
    std::array<char, 96> buffer{};
    (void)std::snprintf(buffer.data(),
                        buffer.size(),
                        "%.*s %08X",
                        static_cast<int>(type.size()),
                        type.data(),
                        static_cast<unsigned>(tag));
    return buffer.data();
}

struct WorldImportContext {
    const ShellState* shell{};
    std::vector<TrackedActor>* actors{};
};

bool collect_world_object(void* context,
                          const native_spawn::WorldObjectObservation& observation) noexcept {
    auto& import = *static_cast<WorldImportContext*>(context);
    const bool alreadyTracked =
        std::any_of(import.shell->actors.begin(),
                    import.shell->actors.end(),
                    [&](const auto& actor) {
                        return actor.source == ActorSource::forge
                               && actor.handle == observation.handle;
                    })
        || std::any_of(import.shell->quarantinedActors.begin(),
                       import.shell->quarantinedActors.end(),
                       [&](const auto& actor) { return actor.handle == observation.handle; });
    if (alreadyTracked || import.actors->size() == import.actors->capacity()) {
        return true;
    }

    TrackedActor actor{};
    actor.editorId = kMapActorIdMask | observation.handle;
    const std::string_view customName = custom_asset_name(*import.shell, observation.tag);
    actor.name = customName.empty() ? actor_name(observation.tag, observation.objectType)
                                    : std::string{customName};
    actor.tag = observation.tag;
    actor.handle = observation.handle;
    actor.objectType = observation.objectType;
    actor.source = ActorSource::liveMap;
    actor.identity = observation.identity;
    actor.transformKnown = false;
    import.actors->push_back(std::move(actor));
    return true;
}

[[nodiscard]] std::uint64_t authored_actor_id(std::uint32_t tableTag,
                                              std::uint32_t entryIndex) noexcept {
    const std::uint64_t table = static_cast<std::uint64_t>(tableTag & 0x3FFFFFFFU) << 24U;
    return kAuthoredActorIdMask | table | (entryIndex & 0xFFFFFFU);
}

void append_authored_placements(ShellState& shell,
                                std::vector<TrackedActor>& imported,
                                std::size_t& authoredCount) {
    authoredCount = 0;
    if (shell.loadedMapRoot.empty()) {
        return;
    }
    std::vector<runtime::custom_package_builder::StaticPlacementCandidate> candidates(
        kAuthoredPlacementCapacity);
    std::size_t candidateCount = 0;
    if (!runtime::custom_package_builder::discover_authored_static_placements(
            shell.loadedMapRoot, candidates, candidateCount)) {
        return;
    }
    for (const auto& candidate : std::span(candidates).first(candidateCount)) {
        TrackedActor actor{};
        actor.editorId =
            authored_actor_id(candidate.binding.tableTag, candidate.binding.entryIndex);
        actor.tag = candidate.binding.parentTag;
        actor.handle = kInvalidHandle;
        actor.tableTag = candidate.binding.tableTag;
        actor.entryIndex = candidate.binding.entryIndex;
        actor.parentTag = candidate.binding.parentTag;
        actor.transform = candidate.binding.sourceTransform;
        actor.source = ActorSource::authoredMap;
        actor.transformKnown = true;
        const std::string_view customName = custom_asset_name(shell, actor.tag);
        if (!customName.empty()) {
            actor.name = customName;
        } else {
            std::array<char, 128> name{};
            (void)std::snprintf(name.data(),
                                name.size(),
                                "Static Placement %08X:%u",
                                static_cast<unsigned>(actor.tableTag),
                                static_cast<unsigned>(actor.entryIndex));
            actor.name = name.data();
        }
        imported.push_back(std::move(actor));
        ++authoredCount;
    }
}

void refresh_world_objects(ShellState& shell) {
    shell.quarantinedActors.erase(
        std::remove_if(shell.quarantinedActors.begin(),
                       shell.quarantinedActors.end(),
                       [](const auto& actor) { return !native_spawn::object_live(actor.handle); }),
        shell.quarantinedActors.end());

    std::vector<native_spawn::WorldObjectDefinition> definitions;
    definitions.reserve(shell.assets.size());
    for (const AssetRecord& asset : shell.assets) {
        if (asset.resident && asset.typeKnown) {
            definitions.push_back({asset.tag, asset.objectType});
        }
    }

    std::vector<TrackedActor> imported;
    imported.reserve((1U << 13U) + kAuthoredPlacementCapacity);
    WorldImportContext context{&shell, &imported};
    native_spawn::WorldObjectScan scan{};
    const bool liveScanned =
        shell.catalogReady && native_spawn::ready() && !definitions.empty()
        && native_spawn::visit_world_objects(definitions, &context, &collect_world_object, scan);
    std::size_t authoredCount = 0;
    append_authored_placements(shell, imported, authoredCount);
    const bool authoredScanned = authoredCount != 0;
    if (!liveScanned && !authoredScanned) {
        shell.worldObjectsScanned = false;
        set_status(shell,
                   "Map-object scan unavailable: no live datum identities or authored placements "
                   "were resolved for %s.",
                   shell.loadedMapRoot.empty() ? "the current world" : shell.loadedMapRoot.c_str());
        return;
    }
    std::sort(imported.begin(), imported.end(), [](const auto& left, const auto& right) {
        if (left.objectType != right.objectType) {
            return left.objectType < right.objectType;
        }
        return left.tag == right.tag ? left.handle < right.handle : left.tag < right.tag;
    });

    shell.actors.erase(
        std::remove_if(shell.actors.begin(),
                       shell.actors.end(),
                       [](const auto& actor) { return actor.source != ActorSource::forge; }),
        shell.actors.end());
    shell.actors.insert(shell.actors.end(),
                        std::make_move_iterator(imported.begin()),
                        std::make_move_iterator(imported.end()));
    prune_actor_selection(shell);
    shell.worldScan = scan;
    shell.worldObjectsScanned = true;
    const std::size_t liveCount = static_cast<std::size_t>(
        std::count_if(shell.actors.begin(), shell.actors.end(), [](const auto& actor) {
            return actor.source == ActorSource::liveMap;
        }));
    set_status(shell,
               "Explorer mapped %zu live object(s) and %zu authored static placement(s): %zu "
               "handles, %zu ambiguous, %zu unstable.",
               liveCount,
               authoredCount,
               scan.liveHandles,
               scan.ambiguousObjects,
               scan.unstableObjects);
}

void queue_camera_spawn(ShellState& shell, const AssetRecord& asset) {
    if (!native_spawn::ready() || !native_spawn::is_tag_resident(asset.tag)) {
        set_status(shell,
                   "0x%08X is installed but not resident in the current destination.",
                   static_cast<unsigned>(asset.tag));
        return;
    }
    SpawnCommand command{};
    command.editorId = shell.nextActorId++;
    const std::string_view customName = custom_asset_name(shell, asset.tag);
    command.name =
        customName.empty() ? actor_name(asset.tag, asset.objectType) : std::string{customName};
    command.tag = asset.tag;
    command.objectType = asset.objectType;
    command.transform.uniformScale = 1.0F;
    shell.spawnQueue.push_back(std::move(command));
    set_status(shell,
               "Queued 0x%08X at %.1f units in front of the camera.",
               static_cast<unsigned>(asset.tag),
               static_cast<double>(shell.spawnDistance));
}

void queue_duplicate(ShellState& shell, const TrackedActor& actor, bool additiveSelection) {
    SpawnCommand command{};
    command.editorId = shell.nextActorId++;
    command.parentId = actor.parentId;
    command.name = actor.name + " Copy";
    command.tag = actor.tag;
    command.objectType = actor.objectType;
    command.transform = actor.transform;
    command.transform.translation.x += 1.0F;
    command.absolute = true;
    command.additiveSelection = additiveSelection;
    shell.spawnQueue.push_back(std::move(command));
}

void duplicate_selected(ShellState& shell) {
    const std::vector<std::uint64_t> selected = shell.selectedActorIds;
    std::vector<std::uint64_t> duplicable;
    duplicable.reserve(selected.size());
    for (const std::uint64_t id : selected) {
        const TrackedActor* const actor = find_actor(shell, id);
        if (actor != nullptr && actor->transformKnown
            && actor->source != ActorSource::authoredMap) {
            duplicable.push_back(id);
        }
    }
    if (duplicable.empty()) {
        set_status(shell, "Duplicate unavailable: no selected actor has a known transform.");
        return;
    }

    clear_actor_selection(shell);
    for (const std::uint64_t id : duplicable) {
        if (const TrackedActor* const actor = find_actor(shell, id); actor != nullptr) {
            queue_duplicate(shell, *actor, true);
        }
    }
    set_status(shell,
               "Queued %zu duplicate%s; each copy becomes selected when created.",
               duplicable.size(),
               duplicable.size() == 1 ? "" : "s");
}

[[nodiscard]] bool selected_actor_can_duplicate(const ShellState& shell) noexcept {
    return std::any_of(
        shell.selectedActorIds.begin(), shell.selectedActorIds.end(), [&shell](std::uint64_t id) {
            const TrackedActor* const actor = find_actor(shell, id);
            return actor != nullptr && actor->transformKnown
                   && actor->source != ActorSource::authoredMap;
        });
}

[[nodiscard]] bool activation_transform_type(std::uint8_t type) noexcept {
    return type == 8 || type == 11 || type == 20 || type == 21;
}

[[nodiscard]] bool can_quarantine_actor(const TrackedActor* actor) noexcept {
    return actor != nullptr
           && ((actor->source == ActorSource::forge && actor->transformKnown)
               || (actor->source == ActorSource::liveMap
                   && activation_transform_type(actor->objectType)));
}

void erase_actor_record(ShellState& shell, std::vector<TrackedActor>::iterator actor) {
    const std::uint64_t editorId = actor->editorId;
    const std::uint64_t parentId = actor->parentId;
    for (TrackedActor& child : shell.actors) {
        if (child.parentId == editorId) {
            child.parentId = parentId;
        }
    }
    shell.undo.erase(
        std::remove_if(shell.undo.begin(),
                       shell.undo.end(),
                       [editorId](const auto& edit) { return edit.actorId == editorId; }),
        shell.undo.end());
    shell.redo.erase(
        std::remove_if(shell.redo.begin(),
                       shell.redo.end(),
                       [editorId](const auto& edit) { return edit.actorId == editorId; }),
        shell.redo.end());
    shell.actors.erase(actor);
    shell.selectedActorIds.erase(
        std::remove(shell.selectedActorIds.begin(), shell.selectedActorIds.end(), editorId),
        shell.selectedActorIds.end());
    if (shell.selectedActorId == editorId) {
        shell.selectedActorId = shell.selectedActorIds.empty() ? 0 : shell.selectedActorIds.back();
    }
    if (shell.selectionAnchorId == editorId) {
        shell.selectionAnchorId = shell.selectedActorId;
    }
}

void service_actor_lifetimes(ShellState& shell) {
    const double now = ImGui::GetTime();
    if (now < shell.nextLifetimeCheck) {
        return;
    }
    shell.nextLifetimeCheck = now + 0.5;
    for (TrackedActor& actor : shell.actors) {
        if (actor.source == ActorSource::forge && actor.handle != kInvalidHandle) {
            actor.nativeExpired = !native_spawn::object_live(actor.handle);
        }
    }
}

[[nodiscard]] bool has_restorable_quarantine(const ShellState& shell) noexcept {
    return std::any_of(shell.quarantinedActors.begin(),
                       shell.quarantinedActors.end(),
                       [](const auto& actor) { return actor.transformKnown; });
}

bool quarantine_actor(ShellState& shell, std::uint64_t actorId) {
    const auto found =
        std::find_if(shell.actors.begin(), shell.actors.end(), [actorId](const auto& actor) {
            return actor.editorId == actorId;
        });
    if (found == shell.actors.end() || !can_quarantine_actor(&*found)) {
        set_status(shell,
                   "Remove blocked: this native object type has no source-backed transform path.");
        return false;
    }

    if (found->source == ActorSource::forge && !native_spawn::object_live(found->handle)) {
        const std::uint32_t handle = found->handle;
        erase_actor_record(shell, found);
        set_status(shell,
                   "Removed expired Forge record 0x%08X; Destiny had already destroyed it.",
                   static_cast<unsigned>(handle));
        return true;
    }

    const bool restorable = found->transformKnown;
    core::Transform quarantine{};
    quarantine.rotation.w = 1.0F;
    quarantine.translation.z = -kQuarantineDepth;
    quarantine.uniformScale = kQuarantineScale;
    if (restorable) {
        quarantine = found->transform;
        quarantine.translation.z -= kQuarantineDepth;
        quarantine.uniformScale = kQuarantineScale;
    }
    const std::array<float, 3> position{
        quarantine.translation.x, quarantine.translation.y, quarantine.translation.z};
    const std::array<float, 4> rotation{
        quarantine.rotation.x, quarantine.rotation.y, quarantine.rotation.z, quarantine.rotation.w};
    if (!native_spawn::request_transform(
            found->handle, position, rotation, quarantine.uniformScale)) {
        set_status(shell,
                   "Experimental remove rejected for stale handle 0x%08X.",
                   static_cast<unsigned>(found->handle));
        return false;
    }

    const std::uint32_t handle = found->handle;
    shell.quarantinedActors.push_back(std::move(*found));
    erase_actor_record(shell, found);
    shell.redo.clear();
    if (restorable) {
        set_status(shell,
                   "Experimental remove queued for 0x%08X. Undo restores it; allocation remains.",
                   static_cast<unsigned>(handle));
    } else {
        set_status(shell,
                   "Map-object remove queued for 0x%08X. Reload the world to restore it.",
                   static_cast<unsigned>(handle));
    }
    return true;
}

void delete_selected(ShellState& shell) {
    const std::vector<std::uint64_t> selected = shell.selectedActorIds;
    std::size_t removed = 0;
    std::size_t blocked = 0;
    for (const std::uint64_t id : selected) {
        const TrackedActor* const actor = find_actor(shell, id);
        if (!can_quarantine_actor(actor)) {
            ++blocked;
            continue;
        }
        if (quarantine_actor(shell, id)) {
            ++removed;
        } else {
            ++blocked;
        }
    }
    if (removed == 0) {
        set_status(shell,
                   selected.empty()
                       ? "Remove unavailable: no object is selected."
                       : "Remove blocked: selected map types have no recovered transform path.");
        return;
    }
    set_status(shell,
               "Removed %zu selected object%s%s.",
               removed,
               removed == 1 ? "" : "s",
               blocked == 0 ? "" : "; unsupported map objects were left selected");
}

[[nodiscard]] bool selected_actor_can_delete(const ShellState& shell) noexcept {
    return std::any_of(
        shell.selectedActorIds.begin(), shell.selectedActorIds.end(), [&shell](std::uint64_t id) {
            return can_quarantine_actor(find_actor(shell, id));
        });
}

void focus_selected_actor(ShellState& shell) {
    const TrackedActor* const actor = find_actor(shell, shell.selectedActorId);
    if (actor == nullptr || !actor->transformKnown || actor->nativeExpired) {
        set_status(shell, "Focus unavailable: select a live Forge object with a known transform.");
        return;
    }

    teleport::Vector player{};
    teleport::Vector camera{};
    teleport::Vector forward{};
    if (!teleport::current_position(player) || !teleport::current_camera_pose(camera, forward)) {
        set_status(shell, "Focus unavailable: player or camera pose is not published yet.");
        return;
    }

    const float distance = (std::clamp)(8.0F + actor->transform.uniformScale * 2.0F, 8.0F, 40.0F);
    teleport::Vector destination{};
    const std::array<float, 3> target{actor->transform.translation.x,
                                      actor->transform.translation.y,
                                      actor->transform.translation.z};
    for (std::size_t lane = 0; lane < teleport::kVectorLanes; ++lane) {
        const float cameraOffset = camera[lane] - player[lane];
        destination[lane] = target[lane] - forward[lane] * distance - cameraOffset;
    }
    if (!teleport::request_local_player_move(destination)) {
        set_status(shell, "Focus failed: the local player physics body is unavailable.");
        return;
    }
    set_status(shell, "Focus queued for %s from %.1f units.", actor->name.c_str(), distance);
}

bool restore_quarantined_actor(ShellState& shell) {
    const auto found = std::find_if(shell.quarantinedActors.rbegin(),
                                    shell.quarantinedActors.rend(),
                                    [](const auto& actor) { return actor.transformKnown; });
    if (found == shell.quarantinedActors.rend()) {
        return false;
    }
    TrackedActor& actor = *found;
    if (!native_spawn::object_live(actor.handle)) {
        set_status(shell,
                   "Restore unavailable: handle 0x%08X expired with the prior world.",
                   static_cast<unsigned>(actor.handle));
        shell.quarantinedActors.erase(std::next(found).base());
        return true;
    }
    const std::array<float, 3> position{actor.transform.translation.x,
                                        actor.transform.translation.y,
                                        actor.transform.translation.z};
    const std::array<float, 4> rotation{actor.transform.rotation.x,
                                        actor.transform.rotation.y,
                                        actor.transform.rotation.z,
                                        actor.transform.rotation.w};
    if (!native_spawn::request_transform(
            actor.handle, position, rotation, actor.transform.uniformScale)) {
        set_status(shell,
                   "Restore queue rejected for handle 0x%08X.",
                   static_cast<unsigned>(actor.handle));
        return true;
    }

    const std::uint64_t editorId = actor.editorId;
    const std::uint32_t handle = actor.handle;
    shell.actors.push_back(std::move(actor));
    shell.quarantinedActors.erase(std::next(found).base());
    select_only_actor(shell, editorId);
    set_status(shell, "Restored quarantined handle 0x%08X.", static_cast<unsigned>(handle));
    return true;
}

void complete_spawn(ShellState& shell,
                    const SpawnCommand& command,
                    const native_spawn::SpawnObservation& observation) {
    if (!observation.succeeded) {
        const std::string_view outcome = native_spawn::spawn_outcome_text(observation.outcome);
        set_status(shell,
                   "Spawn failed for 0x%08X: %.*s.",
                   static_cast<unsigned>(command.tag),
                   static_cast<int>(outcome.size()),
                   outcome.data());
        return;
    }
    TrackedActor actor{};
    actor.editorId = command.editorId;
    actor.parentId = command.parentId;
    actor.name = command.name;
    actor.tag = command.tag;
    actor.handle = observation.handle;
    actor.objectType = observation.objectType;
    actor.transform.translation = {
        observation.position[0], observation.position[1], observation.position[2]};
    actor.transform.rotation = {observation.rotation[0],
                                observation.rotation[1],
                                observation.rotation[2],
                                observation.rotation[3]};
    actor.transform.uniformScale = observation.scale;
    shell.actors.push_back(std::move(actor));
    if (!command.additiveSelection) {
        clear_actor_selection(shell);
    }
    add_actor_selection(shell, command.editorId);
    shell.selectionAnchorId = command.editorId;
    set_status(shell,
               "Created 0x%08X with native handle 0x%08X.",
               static_cast<unsigned>(command.tag),
               static_cast<unsigned>(observation.handle));
}

void service_spawn_queue(ShellState& shell) {
    const native_spawn::SpawnObservation observation = native_spawn::last_spawn_observation();
    if (shell.spawnInFlight) {
        if (observation.sequence <= shell.submittedSequence || shell.spawnQueue.empty()) {
            return;
        }
        const SpawnCommand& command = shell.spawnQueue.front();
        if (observation.tag != command.tag) {
            shell.submittedSequence = observation.sequence;
            return;
        }
        complete_spawn(shell, command, observation);
        shell.spawnQueue.erase(shell.spawnQueue.begin());
        shell.spawnInFlight = false;
    }
    if (shell.spawnQueue.empty() || native_spawn::busy()) {
        return;
    }
    const SpawnCommand& command = shell.spawnQueue.front();
    bool accepted = false;
    if (command.absolute) {
        const std::array<float, 3> position{command.transform.translation.x,
                                            command.transform.translation.y,
                                            command.transform.translation.z};
        const std::array<float, 4> rotation{command.transform.rotation.x,
                                            command.transform.rotation.y,
                                            command.transform.rotation.z,
                                            command.transform.rotation.w};
        accepted = native_spawn::request_at(
            command.tag, position, rotation, command.transform.uniformScale);
    } else {
        native_spawn::Settings settings{};
        settings.lift = 0.0F;
        settings.rayDistance = shell.spawnDistance;
        settings.scale = command.transform.uniformScale;
        accepted = native_spawn::request(command.tag, native_spawn::Origin::cameraRay, 1, settings);
    }
    if (accepted) {
        shell.submittedSequence = observation.sequence;
        shell.spawnInFlight = true;
    } else if (!native_spawn::ready() || !native_spawn::is_tag_resident(command.tag)) {
        set_status(shell,
                   "Spawn rejected before submission for 0x%08X.",
                   static_cast<unsigned>(command.tag));
        shell.spawnQueue.erase(shell.spawnQueue.begin());
    }
}

[[nodiscard]] bool same_transform(const core::Transform& left,
                                  const core::Transform& right) noexcept {
    return std::memcmp(&left, &right, sizeof(core::Transform)) == 0;
}

void write_actor_transform(ShellState& shell,
                           TrackedActor& actor,
                           const core::Transform& transform,
                           bool recordHistory) {
    if (actor.source == ActorSource::authoredMap) {
        set_status(shell,
                   "Authored placement transforms are read-only until package edit replay is "
                   "connected to the live world.");
        return;
    }
    if (actor.nativeExpired) {
        set_status(shell, "Transform blocked: Destiny already destroyed this transient object.");
        return;
    }
    if (!actor.transformKnown || !transform.is_finite() || transform.uniformScale <= 0.0F) {
        set_status(shell, "Transform blocked: this live map object's transform is not decoded.");
        return;
    }
    const core::Transform before = actor.transform;
    actor.transform = transform;
    const std::array<float, 3> position{
        transform.translation.x, transform.translation.y, transform.translation.z};
    const std::array<float, 4> rotation{
        transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w};
    const bool queued =
        native_spawn::request_transform(actor.handle, position, rotation, transform.uniformScale);
    if (recordHistory && !same_transform(before, transform)) {
        shell.undo.push_back({actor.editorId, before, transform});
        shell.redo.clear();
    }
    set_status(shell,
               queued ? "Transform queued for handle 0x%08X."
                      : "Transform queue rejected for handle 0x%08X.",
               static_cast<unsigned>(actor.handle));
}

void undo_transform(ShellState& shell, workspace::EditorWorkspace& editor) {
    if (restore_quarantined_actor(shell)) {
        return;
    }
    if (!shell.undo.empty()) {
        const TransformEdit edit = shell.undo.back();
        shell.undo.pop_back();
        if (TrackedActor* const actor = find_actor(shell, edit.actorId); actor != nullptr) {
            write_actor_transform(shell, *actor, edit.before, false);
            shell.redo.push_back(edit);
        }
        return;
    }
    (void)editor.undo();
}

void redo_transform(ShellState& shell, workspace::EditorWorkspace& editor) {
    if (!shell.redo.empty()) {
        const TransformEdit edit = shell.redo.back();
        shell.redo.pop_back();
        if (TrackedActor* const actor = find_actor(shell, edit.actorId); actor != nullptr) {
            write_actor_transform(shell, *actor, edit.after, false);
            shell.undo.push_back(edit);
        }
        return;
    }
    (void)editor.redo();
}

void quick_save(ShellState& shell, const workspace::EditorWorkspace& editor) {
    std::wstring path;
    if (!recipe::default_path(path)) {
        set_status(shell, "Fate quick-save path could not be resolved.");
        return;
    }
    std::vector<recipe::ActorInstruction> instructions;
    instructions.reserve(shell.actors.size());
    for (const TrackedActor& actor : shell.actors) {
        if (actor.source != ActorSource::forge) {
            continue;
        }
        instructions.push_back({actor.editorId,
                                actor.parentId,
                                actor.name,
                                actor.tag,
                                actor.objectType,
                                actor.transform});
    }
    const recipe::IoResult result =
        recipe::save(path, editor.active_template().displayName, instructions);
    set_status(shell, "%s %zu instruction(s).", result.message.c_str(), result.instructionCount);
}

void quick_load(ShellState& shell) {
    std::wstring path;
    if (!recipe::default_path(path)) {
        set_status(shell, "Fate quick-load path could not be resolved.");
        return;
    }
    recipe::MapRecipe loaded;
    const recipe::IoResult result = recipe::load(path, loaded);
    if (!result.succeeded) {
        set_status(shell, "%s", result.message.c_str());
        return;
    }
    std::vector<std::pair<std::uint64_t, std::uint64_t>> ids;
    ids.reserve(loaded.actors.size());
    for (const recipe::ActorInstruction& instruction : loaded.actors) {
        ids.emplace_back(instruction.editorId, shell.nextActorId++);
    }
    const auto remap = [&ids](std::uint64_t oldId) {
        if (oldId == 0) {
            return std::uint64_t{};
        }
        const auto found = std::find_if(
            ids.begin(), ids.end(), [oldId](const auto& pair) { return pair.first == oldId; });
        return found == ids.end() ? std::uint64_t{} : found->second;
    };
    for (const recipe::ActorInstruction& instruction : loaded.actors) {
        SpawnCommand command{};
        command.editorId = remap(instruction.editorId);
        command.parentId = remap(instruction.parentId);
        command.name = instruction.name;
        command.tag = instruction.tag;
        command.objectType = instruction.objectType;
        command.transform = instruction.transform;
        command.absolute = true;
        shell.spawnQueue.push_back(std::move(command));
    }
    set_status(shell, "Queued %zu Fate instruction(s) for live replay.", result.instructionCount);
}

[[nodiscard]] bool can_load_world_template(const workspace::BaseplateTemplate& value) noexcept {
    return value.id == std::string_view{"tower_carrier_control"}
           || (value.hasLaunchTarget && value.id != std::string_view{"pandora_carrier_lab"});
}

[[nodiscard]] const WorldCatalogRecord* selected_catalog_world(const ShellState& shell) noexcept {
    const auto found =
        std::find_if(shell.worlds.begin(), shell.worlds.end(), [&shell](const auto& world) {
            return world.name == shell.loadWorldScenario;
        });
    return found == shell.worlds.end() ? nullptr : &*found;
}

void draw_world_catalog_row(ShellState& shell, const WorldCatalogRecord& world) {
    const bool active = shell.loadCatalogWorld && shell.loadWorldScenario == world.name;
    const std::string_view label = world_display_name(world.name);
    ImGui::PushID(world.name.c_str());
    if (ImGui::Selectable(label.data(), active)) {
        shell.loadCatalogWorld = true;
        shell.loadWorldScenario = world.name;
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
        if (world.validatedLayout) {
            ImGui::SetTooltip("%s\nTag %08X | %u bubbles | %u packages | map root %s",
                              world.name.c_str(),
                              static_cast<unsigned>(world.tag),
                              static_cast<unsigned>(world.bubbleCount),
                              static_cast<unsigned>(world.packageCount),
                              world.mapRoot.empty() ? "not named" : world.mapRoot.c_str());
        } else {
            ImGui::SetTooltip("%s\nTag %08X | layout pending | installed-name launch fallback",
                              world.name.c_str(),
                              static_cast<unsigned>(world.tag));
        }
    }
    if (active) {
        ImGui::SetItemDefaultFocus();
    }
    ImGui::PopID();
}

void draw_world_template_loader(ShellState& shell, workspace::EditorWorkspace& editor) {
    if (!shell.worldCatalogReady
        || (!shell.worldCatalogValidated && state::build_data::scenario_layouts_ready())) {
        refresh_world_catalog(shell);
    }
    const std::span<const workspace::BaseplateTemplate> templates = editor.templates();
    const workspace::BaseplateTemplate* selectedTemplate = nullptr;
    std::size_t selectedTemplateIndex = 0;
    for (std::size_t index = 0; index < templates.size(); ++index) {
        if (can_load_world_template(templates[index])
            && templates[index].id == shell.loadTemplateId) {
            selectedTemplate = &templates[index];
            selectedTemplateIndex = index;
            break;
        }
    }
    if (selectedTemplate == nullptr) {
        for (std::size_t index = 0; index < templates.size(); ++index) {
            if (can_load_world_template(templates[index])) {
                selectedTemplate = &templates[index];
                selectedTemplateIndex = index;
                shell.loadTemplateId = templates[index].id;
                break;
            }
        }
    }

    const WorldCatalogRecord* selectedWorld = selected_catalog_world(shell);
    if (shell.loadCatalogWorld && selectedWorld == nullptr && !shell.worlds.empty()) {
        shell.loadWorldScenario = shell.worlds.front().name;
        selectedWorld = &shell.worlds.front();
    }
    std::string preview = "No loadable worlds";
    if (shell.loadCatalogWorld && selectedWorld != nullptr) {
        preview = world_display_name(selectedWorld->name);
    } else if (selectedTemplate != nullptr) {
        preview = selectedTemplate->displayName;
    }

    ImGui::SetNextItemWidth(300.0F);
    ImGui::SetNextWindowSizeConstraints({430.0F, 260.0F}, {620.0F, 620.0F});
    if (ImGui::BeginCombo("##world_template", preview.c_str())) {
        ImGui::SetNextItemWidth(-1.0F);
        ImGui::InputTextWithHint("##world_filter",
                                 "Search installed destinations",
                                 shell.worldFilter,
                                 sizeof(shell.worldFilter));
        const std::string filter = lowercase(shell.worldFilter);
        ImGui::TextDisabled("PINNED DESTINATIONS");
        for (const WorldCatalogRecord& world : shell.worlds) {
            if (world_sort_rank(world.name) >= 2 || !contains_lower(world.name, filter)) {
                continue;
            }
            draw_world_catalog_row(shell, world);
        }
        ImGui::Separator();
        ImGui::TextDisabled("FORGE CARRIERS");
        for (std::size_t index = 0; index < templates.size(); ++index) {
            const workspace::BaseplateTemplate& candidate = templates[index];
            if (!can_load_world_template(candidate)
                || (!filter.empty() && !contains_lower(candidate.displayName, filter)
                    && !contains_lower(candidate.packageName, filter))) {
                continue;
            }
            const bool active = !shell.loadCatalogWorld && selectedTemplate != nullptr
                                && candidate.id == selectedTemplate->id;
            if (ImGui::Selectable(candidate.displayName.data(), active)) {
                shell.loadCatalogWorld = false;
                shell.loadTemplateId = candidate.id;
                selectedTemplate = &candidate;
                selectedTemplateIndex = index;
            }
            if (active) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::Separator();
        ImGui::TextDisabled("INSTALLED DESTINATIONS (%zu)", shell.worlds.size());
        for (const WorldCatalogRecord& world : shell.worlds) {
            if (world_sort_rank(world.name) < 2
                || (!contains_lower(world.name, filter)
                    && !contains_lower(world.mapRoot, filter))) {
                continue;
            }
            draw_world_catalog_row(shell, world);
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    const bool canLoad =
        shell.loadCatalogWorld ? selectedWorld != nullptr : selectedTemplate != nullptr;
    ImGui::BeginDisabled(!canLoad);
    if (ImGui::Button("LOAD WORLD", {118.0F, 0.0F})) {
        workspace::LaunchResult result{};
        if (shell.loadCatalogWorld && selectedWorld != nullptr) {
            shell.loadedWorldName = selectedWorld->name;
            shell.loadedMapRoot = selectedWorld->mapRoot;
            result = editor.launch_scenario(selectedWorld->name);
        } else {
            editor.return_to_launcher();
            if (!editor.select_template(selectedTemplateIndex)) {
                set_status(shell, "The selected world template is no longer available.");
                ImGui::EndDisabled();
                return;
            }
            shell.loadedWorldName = selectedTemplate->packageName;
            shell.loadedMapRoot =
                selectedTemplate->packageName == "vfx_shade_test"         ? "map:pandora:root"
                : selectedTemplate->packageName == "city_tower_social_d2" ? "map:city_tower_d2:root"
                                                                          : shell.loadedMapRoot;
            result = editor.launch_selected_template();
        }
        set_status(shell, "%.*s", static_cast<int>(result.message.size()), result.message.data());
        g_worldRefreshRequested.store(true, std::memory_order_release);
    }
    ImGui::EndDisabled();
}

class StyleScope final {
public:
    StyleScope() noexcept {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {8.0F, 8.0F});
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {8.0F, 5.0F});
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {6.0F, 5.0F});
        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, {7.0F, 5.0F});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0F);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0F);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0F);
        ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 0.0F);
        ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 0.0F);
        ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 0.0F);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0F);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0F);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{0.92F, 0.94F, 0.95F, 1.0F});
        ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImVec4{0.48F, 0.53F, 0.56F, 1.0F});
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{0.02F, 0.025F, 0.03F, 0.96F});
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.025F, 0.03F, 0.035F, 0.94F});
        ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4{0.025F, 0.03F, 0.035F, 0.98F});
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4{0.28F, 0.32F, 0.34F, 0.78F});
        ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4{0.0F, 0.0F, 0.0F, 0.0F});
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4{0.08F, 0.095F, 0.105F, 0.92F});
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4{0.17F, 0.20F, 0.21F, 0.96F});
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4{0.23F, 0.25F, 0.24F, 1.0F});
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.07F, 0.08F, 0.09F, 0.90F});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.20F, 0.22F, 0.21F, 1.0F});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.55F, 0.45F, 0.24F, 0.92F});
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4{0.24F, 0.22F, 0.17F, 0.86F});
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4{0.42F, 0.35F, 0.21F, 0.92F});
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4{0.64F, 0.51F, 0.25F, 0.94F});
        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4{0.58F, 0.50F, 0.32F, 0.78F});
        ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4{0.91F, 0.75F, 0.36F, 1.0F});
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4{0.78F, 0.66F, 0.39F, 1.0F});
        ImGui::PushStyleColor(ImGuiCol_DragDropTarget, ImVec4{0.94F, 0.78F, 0.38F, 0.95F});
    }

    ~StyleScope() {
        ImGui::PopStyleColor(20);
        ImGui::PopStyleVar(12);
    }
};

void draw_icon(ImDrawList* draw, Icon icon, ImVec2 center, ImU32 color) {
    const float x = center.x;
    const float y = center.y;
    switch (icon) {
    case Icon::save:
        draw->AddRect({x - 8, y - 9}, {x + 8, y + 9}, color, 0.0F, 0, 1.4F);
        draw->AddRect({x - 5, y - 7}, {x + 4, y - 2}, color, 0.0F, 0, 1.2F);
        draw->AddRect({x - 4, y + 2}, {x + 4, y + 8}, color, 0.0F, 0, 1.2F);
        break;
    case Icon::load:
        draw->AddRect({x - 9, y - 5}, {x + 9, y + 8}, color, 0.0F, 0, 1.4F);
        draw->AddLine({x, y - 10}, {x, y + 3}, color, 1.5F);
        draw->AddLine({x - 4, y - 1}, {x, y + 3}, color, 1.5F);
        draw->AddLine({x + 4, y - 1}, {x, y + 3}, color, 1.5F);
        break;
    case Icon::select:
        draw->AddTriangle({x - 7, y - 9}, {x - 5, y + 8}, {x + 8, y + 3}, color, 1.5F);
        break;
    case Icon::move:
        draw->AddLine({x - 9, y}, {x + 9, y}, color, 1.5F);
        draw->AddLine({x, y - 9}, {x, y + 9}, color, 1.5F);
        draw->AddTriangleFilled({x + 9, y}, {x + 4, y - 3}, {x + 4, y + 3}, color);
        draw->AddTriangleFilled({x, y - 9}, {x - 3, y - 4}, {x + 3, y - 4}, color);
        break;
    case Icon::rotate:
        draw->PathArcTo({x, y}, 8.0F, -2.7F, 2.2F, 18);
        draw->PathStroke(color, 0, 1.5F);
        draw->AddTriangleFilled({x - 7, y - 6}, {x - 10, y - 1}, {x - 4, y - 2}, color);
        break;
    case Icon::scale:
        draw->AddLine({x - 7, y + 7}, {x + 6, y - 6}, color, 1.5F);
        draw->AddRectFilled({x + 4, y - 9}, {x + 10, y - 3}, color);
        draw->AddRect({x - 10, y + 3}, {x - 4, y + 9}, color, 0.0F, 0, 1.3F);
        break;
    case Icon::undo:
    case Icon::redo: {
        const float direction = icon == Icon::undo ? -1.0F : 1.0F;
        draw->PathArcTo({x, y + 1}, 8.0F, -2.6F, 1.9F, 16);
        draw->PathStroke(color, 0, 1.4F);
        draw->AddTriangleFilled({x + direction * -8, y - 4},
                                {x + direction * -3, y - 8},
                                {x + direction * -2, y - 2},
                                color);
        break;
    }
    case Icon::duplicate:
        draw->AddRect({x - 8, y - 8}, {x + 4, y + 5}, color, 0.0F, 0, 1.3F);
        draw->AddRect({x - 3, y - 3}, {x + 9, y + 9}, color, 0.0F, 0, 1.3F);
        break;
    case Icon::remove:
    case Icon::close:
        draw->AddLine({x - 7, y - 7}, {x + 7, y + 7}, color, 1.5F);
        draw->AddLine({x + 7, y - 7}, {x - 7, y + 7}, color, 1.5F);
        break;
    case Icon::refresh:
        draw->AddCircle({x, y}, 8.0F, color, 18, 1.4F);
        draw->AddTriangleFilled({x + 7, y - 7}, {x + 10, y - 1}, {x + 4, y - 2}, color);
        break;
    case Icon::probe:
        draw->AddCircle({x, y}, 7.0F, color, 18, 1.3F);
        draw->AddCircleFilled({x, y}, 2.0F, color);
        draw->AddLine({x - 10, y}, {x - 5, y}, color, 1.2F);
        draw->AddLine({x + 5, y}, {x + 10, y}, color, 1.2F);
        break;
    }
}

[[nodiscard]] bool icon_button(
    const char* id, Icon icon, const char* tooltip, bool selected = false, bool enabled = true) {
    ImGui::BeginDisabled(!enabled);
    ImGui::InvisibleButton(id, {36.0F, 36.0F});
    const bool clicked = ImGui::IsItemClicked();
    const bool hovered = ImGui::IsItemHovered();
    const ImVec2 minimum = ImGui::GetItemRectMin();
    const ImVec2 maximum = ImGui::GetItemRectMax();
    ImDrawList* const draw = ImGui::GetWindowDrawList();
    const ImU32 border = IM_COL32(113, 121, 122, enabled ? 210 : 80);
    if (selected || hovered) {
        draw->AddRectFilled(
            minimum, maximum, selected ? IM_COL32(128, 102, 52, 150) : IM_COL32(70, 76, 76, 150));
    }
    draw->AddRect(minimum, maximum, border);
    if (hovered && enabled) {
        const float phase = 0.55F + 0.45F * std::sin(static_cast<float>(ImGui::GetTime()) * 12.0F);
        draw->AddLine({minimum.x, maximum.y - 1.0F},
                      {minimum.x + (maximum.x - minimum.x) * phase, maximum.y - 1.0F},
                      IM_COL32(235, 194, 91, 255),
                      2.0F);
    }
    draw_icon(draw,
              icon,
              {(minimum.x + maximum.x) * 0.5F, (minimum.y + maximum.y) * 0.5F},
              enabled ? IM_COL32(235, 238, 237, 255) : IM_COL32(100, 105, 106, 150));
    if (hovered && tooltip != nullptr) {
        ImGui::SetTooltip("%s", tooltip);
    }
    ImGui::EndDisabled();
    return clicked && enabled;
}

[[nodiscard]] bool category_tab(const char* label, RibbonTab value, ShellState& shell) {
    const bool selected = shell.ribbon == value;
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.0F, 0.0F, 0.0F, 0.0F});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.18F, 0.19F, 0.18F, 0.95F});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.28F, 0.25F, 0.18F, 1.0F});
    const bool clicked = ImGui::Button(label, {72.0F, 30.0F});
    ImGui::PopStyleColor(3);
    if (selected) {
        const ImVec2 minimum = ImGui::GetItemRectMin();
        const ImVec2 maximum = ImGui::GetItemRectMax();
        ImGui::GetWindowDrawList()->AddLine({minimum.x, maximum.y - 1.0F},
                                            {maximum.x, maximum.y - 1.0F},
                                            IM_COL32(235, 194, 91, 255),
                                            2.0F);
    }
    if (clicked) {
        shell.ribbon = value;
    }
    return clicked;
}

void draw_sigil(ImDrawList* draw, ImVec2 center) {
    const float angle = static_cast<float>(ImGui::GetTime()) * 0.9F;
    draw->AddCircle(center, 12.0F, IM_COL32(224, 226, 224, 210), 32, 1.0F);
    draw->AddCircle(center, 7.0F, IM_COL32(208, 170, 79, 230), 24, 1.0F);
    for (int index = 0; index < 3; ++index) {
        const float current = angle + static_cast<float>(index) * 2.0943951F;
        draw->AddLine(center,
                      {center.x + std::cos(current) * 15.0F, center.y + std::sin(current) * 15.0F},
                      IM_COL32(224, 226, 224, 180),
                      1.0F);
    }
}

void panel_header(const char* title) {
    ImGui::TextUnformatted(title);
    const ImVec2 start = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddLine(start,
                                        {start.x + ImGui::GetContentRegionAvail().x, start.y},
                                        IM_COL32(155, 137, 91, 190),
                                        1.0F);
    ImGui::Dummy({0.0F, 4.0F});
}

void draw_top_bar(ShellState& shell) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.015F, 0.018F, 0.021F, 0.98F});
    ImGui::BeginChild("forge_top_bar",
                      {0.0F, kTopBarHeight},
                      true,
                      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    draw_sigil(ImGui::GetWindowDrawList(), {origin.x + 19.0F, origin.y + 18.0F});
    ImGui::SetCursorPosX(44.0F);
    ImGui::TextUnformatted("IZANAMI FORGE");
    ImGui::SameLine(190.0F);
    (void)category_tab("FILE", RibbonTab::file, shell);
    ImGui::SameLine();
    (void)category_tab("HOME", RibbonTab::home, shell);
    ImGui::SameLine();
    (void)category_tab("VIEW", RibbonTab::view, shell);
    ImGui::SameLine();
    (void)category_tab("TEST", RibbonTab::test, shell);
    const float closeX = ImGui::GetWindowWidth() - 45.0F;
    ImGui::SameLine(closeX);
    if (icon_button("##forge_close", Icon::close, "Close Forge")) {
        (void)set_standalone_visible(false);
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

void draw_ribbon(ShellState& shell, workspace::EditorWorkspace& editor) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.035F, 0.041F, 0.044F, 0.97F});
    ImGui::BeginChild("forge_ribbon",
                      {0.0F, kRibbonHeight},
                      true,
                      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::SetCursorPos({10.0F, 12.0F});
    switch (shell.ribbon) {
    case RibbonTab::file:
        if (icon_button("##quick_save", Icon::save, "Save Fate Recipe")) {
            quick_save(shell, editor);
        }
        ImGui::SameLine();
        if (icon_button("##quick_load", Icon::load, "Replay Fate Recipe")) {
            quick_load(shell);
        }
        ImGui::SameLine(96.0F);
        draw_world_template_loader(shell, editor);
        break;
    case RibbonTab::home:
        if (icon_button("##tool_select",
                        Icon::select,
                        "Select Mode",
                        shell.transformMode == TransformMode::select)) {
            shell.transformMode = TransformMode::select;
        }
        ImGui::SameLine();
        if (icon_button("##tool_move",
                        Icon::move,
                        "Move Mode",
                        shell.transformMode == TransformMode::move)) {
            shell.transformMode = TransformMode::move;
        }
        ImGui::SameLine();
        if (icon_button("##tool_rotate",
                        Icon::rotate,
                        "Rotate Mode",
                        shell.transformMode == TransformMode::rotate)) {
            shell.transformMode = TransformMode::rotate;
        }
        ImGui::SameLine();
        if (icon_button("##tool_scale",
                        Icon::scale,
                        "Scale Mode",
                        shell.transformMode == TransformMode::scale)) {
            shell.transformMode = TransformMode::scale;
        }
        ImGui::SameLine(178.0F);
        if (icon_button("##undo",
                        Icon::undo,
                        "Undo",
                        false,
                        has_restorable_quarantine(shell) || !shell.undo.empty()
                            || editor.can_undo())) {
            undo_transform(shell, editor);
        }
        ImGui::SameLine();
        if (icon_button(
                "##redo", Icon::redo, "Redo", false, !shell.redo.empty() || editor.can_redo())) {
            redo_transform(shell, editor);
        }
        ImGui::SameLine(278.0F);
        if (icon_button("##duplicate",
                        Icon::duplicate,
                        "Duplicate Selected",
                        false,
                        selected_actor_can_duplicate(shell))) {
            duplicate_selected(shell);
        }
        ImGui::SameLine();
        if (icon_button("##remove_native",
                        Icon::remove,
                        kNativeDeleteBlocker,
                        false,
                        selected_actor_can_delete(shell))) {
            delete_selected(shell);
        }
        break;
    case RibbonTab::view:
        ImGui::Checkbox("Asset Browser", &shell.showAssetBrowser);
        ImGui::SameLine();
        ImGui::Checkbox("Explorer", &shell.showExplorer);
        ImGui::SameLine();
        ImGui::Checkbox("Properties", &shell.showProperties);
        ImGui::SameLine();
        ImGui::Checkbox("Output", &shell.showOutput);
        ImGui::SameLine(420.0F);
        ImGui::SetNextItemWidth(180.0F);
        ImGui::SliderFloat(
            "Projection FOV", &shell.projectionHorizontalFov, 60.0F, 120.0F, "%.0f deg");
        break;
    case RibbonTab::test:
        if (icon_button("##refresh_catalog", Icon::refresh, "Refresh Installed Asset Catalog")) {
            refresh_catalog(shell);
        }
        ImGui::SameLine();
        if (icon_button("##refresh_world_objects", Icon::refresh, "Refresh Live Map Objects")) {
            refresh_world_objects(shell);
        }
        ImGui::SameLine();
        if (icon_button("##probe_collision", Icon::probe, "Experimental Collision Probe")) {
            shell.probeAttempted = native_spawn::probe_crosshair(30.0F, shell.probe);
            set_status(shell,
                       shell.probeAttempted ? "Probe %s: native=%u changed=%u material=%d."
                                            : "Collision probe unavailable.",
                       shell.probe.hit ? "hit" : "miss",
                       shell.probe.nativeResult ? 1U : 0U,
                       shell.probe.outputChanged ? 1U : 0U,
                       shell.probe.material);
        }
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120.0F);
        ImGui::SliderFloat("Spawn distance", &shell.spawnDistance, 2.0F, 60.0F, "%.1f");
        ImGui::SameLine();
        if (ImGui::Button("Cancel Queue")) {
            native_spawn::cancel();
            shell.spawnQueue.clear();
            shell.spawnInFlight = false;
            set_status(shell, "Spawn queue cancelled.");
        }
        break;
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

[[nodiscard]] std::size_t active_asset_filter_count(const ShellState& shell) noexcept {
    return static_cast<std::size_t>(shell.typeFilter >= 0)
           + static_cast<std::size_t>(shell.assetScope != AssetScope::all)
           + static_cast<std::size_t>(shell.assetAvailability != AssetAvailability::all)
           + static_cast<std::size_t>(shell.assetSourceFilter[0] != '\0')
           + static_cast<std::size_t>(shell.assetSort != AssetSort::tag);
}

void draw_asset_filter_panel(ShellState& shell) {
    ImGui::SetNextWindowSize({360.0F, 0.0F}, ImGuiCond_Appearing);
    if (!ImGui::BeginPopup("asset_filter_panel")) {
        return;
    }

    panel_header("ASSET FILTERS");
    ImGui::TextDisabled("CATEGORY");
    const char* categoryPreview =
        shell.typeFilter < 0 ? "All object types"
        : shell.typeFilter == 256
            ? "Unclassified"
            : research::native_object_type_name(static_cast<std::uint8_t>(shell.typeFilter)).data();
    ImGui::SetNextItemWidth(-1.0F);
    if (ImGui::BeginCombo("##asset_filter_category", categoryPreview)) {
        if (ImGui::Selectable("All object types", shell.typeFilter < 0)) {
            shell.typeFilter = -1;
        }
        const std::size_t unclassified = static_cast<std::size_t>(
            std::count_if(shell.assets.begin(), shell.assets.end(), [](const AssetRecord& asset) {
                return !asset.typeKnown;
            }));
        if (unclassified != 0) {
            std::array<char, 96> label{};
            (void)std::snprintf(label.data(), label.size(), "Unclassified (%zu)", unclassified);
            if (ImGui::Selectable(label.data(), shell.typeFilter == 256)) {
                shell.typeFilter = 256;
            }
        }
        for (const research::NativeObjectTypeRecord& type : research::native_object_types()) {
            if (shell.typeCounts[type.value] == 0) {
                continue;
            }
            std::array<char, 96> label{};
            (void)std::snprintf(label.data(),
                                label.size(),
                                "%.*s (%zu)",
                                static_cast<int>(type.name.size()),
                                type.name.data(),
                                shell.typeCounts[type.value]);
            if (ImGui::Selectable(label.data(), shell.typeFilter == type.value)) {
                shell.typeFilter = type.value;
            }
        }
        ImGui::EndCombo();
    }

    ImGui::TextDisabled("LABEL STATUS");
    const char* scopePreview = "All labels";
    if (shell.assetScope == AssetScope::renamed) {
        scopePreview = "Renamed";
    } else if (shell.assetScope == AssetScope::unknown) {
        scopePreview = "Marked Unknown";
    } else if (shell.assetScope == AssetScope::unnamed) {
        scopePreview = "Unnamed";
    }
    ImGui::SetNextItemWidth(-1.0F);
    if (ImGui::BeginCombo("##asset_filter_labels", scopePreview)) {
        if (ImGui::Selectable("All labels", shell.assetScope == AssetScope::all)) {
            shell.assetScope = AssetScope::all;
        }
        if (ImGui::Selectable("Renamed", shell.assetScope == AssetScope::renamed)) {
            shell.assetScope = AssetScope::renamed;
        }
        if (ImGui::Selectable("Marked Unknown", shell.assetScope == AssetScope::unknown)) {
            shell.assetScope = AssetScope::unknown;
        }
        if (ImGui::Selectable("Unnamed", shell.assetScope == AssetScope::unnamed)) {
            shell.assetScope = AssetScope::unnamed;
        }
        ImGui::EndCombo();
    }

    ImGui::TextDisabled("AVAILABILITY");
    const char* availabilityPreview = "All installed assets";
    if (shell.assetAvailability == AssetAvailability::resident) {
        availabilityPreview = "Resident / spawnable";
    } else if (shell.assetAvailability == AssetAvailability::nonresident) {
        availabilityPreview = "Installed / nonresident";
    }
    ImGui::SetNextItemWidth(-1.0F);
    if (ImGui::BeginCombo("##asset_filter_availability", availabilityPreview)) {
        if (ImGui::Selectable("All installed assets",
                              shell.assetAvailability == AssetAvailability::all)) {
            shell.assetAvailability = AssetAvailability::all;
        }
        if (ImGui::Selectable("Resident / spawnable",
                              shell.assetAvailability == AssetAvailability::resident)) {
            shell.assetAvailability = AssetAvailability::resident;
        }
        if (ImGui::Selectable("Installed / nonresident",
                              shell.assetAvailability == AssetAvailability::nonresident)) {
            shell.assetAvailability = AssetAvailability::nonresident;
        }
        ImGui::EndCombo();
    }

    std::vector<std::string_view> sources;
    sources.reserve(shell.assets.size());
    for (const AssetRecord& asset : shell.assets) {
        if (asset.packageFamily[0] != '\0') {
            sources.emplace_back(asset.packageFamily.data());
        }
    }
    std::sort(sources.begin(), sources.end(), case_insensitive_less);
    sources.erase(std::unique(sources.begin(), sources.end()), sources.end());

    ImGui::TextDisabled("DESTINATION SOURCE / PACKAGE");
    const char* sourcePreview =
        shell.assetSourceFilter[0] == '\0' ? "All source packages" : shell.assetSourceFilter.data();
    ImGui::SetNextItemWidth(-1.0F);
    if (ImGui::BeginCombo("##asset_filter_source", sourcePreview)) {
        if (ImGui::Selectable("All source packages", shell.assetSourceFilter[0] == '\0')) {
            shell.assetSourceFilter[0] = '\0';
        }
        ImGuiListClipper clipper;
        clipper.Begin(static_cast<int>(sources.size()));
        while (clipper.Step()) {
            for (int index = clipper.DisplayStart; index < clipper.DisplayEnd; ++index) {
                const std::string_view source = sources[static_cast<std::size_t>(index)];
                const bool selected = source == shell.assetSourceFilter.data();
                if (ImGui::Selectable(source.data(), selected)) {
                    const std::size_t count =
                        (std::min)(source.size(), shell.assetSourceFilter.size() - 1);
                    std::memcpy(shell.assetSourceFilter.data(), source.data(), count);
                    shell.assetSourceFilter[count] = '\0';
                }
            }
        }
        ImGui::EndCombo();
    }

    ImGui::TextDisabled("SORT");
    const char* sortPreview = "Tag";
    switch (shell.assetSort) {
    case AssetSort::tag:
        break;
    case AssetSort::nameAscending:
        sortPreview = "Name A-Z";
        break;
    case AssetSort::nameDescending:
        sortPreview = "Name Z-A";
        break;
    case AssetSort::category:
        sortPreview = "Category";
        break;
    case AssetSort::source:
        sortPreview = "Destination source";
        break;
    }
    ImGui::SetNextItemWidth(-1.0F);
    if (ImGui::BeginCombo("##asset_filter_sort", sortPreview)) {
        if (ImGui::Selectable("Tag", shell.assetSort == AssetSort::tag)) {
            shell.assetSort = AssetSort::tag;
        }
        if (ImGui::Selectable("Name A-Z", shell.assetSort == AssetSort::nameAscending)) {
            shell.assetSort = AssetSort::nameAscending;
        }
        if (ImGui::Selectable("Name Z-A", shell.assetSort == AssetSort::nameDescending)) {
            shell.assetSort = AssetSort::nameDescending;
        }
        if (ImGui::Selectable("Category", shell.assetSort == AssetSort::category)) {
            shell.assetSort = AssetSort::category;
        }
        if (ImGui::Selectable("Destination source", shell.assetSort == AssetSort::source)) {
            shell.assetSort = AssetSort::source;
        }
        ImGui::EndCombo();
    }

    ImGui::Spacing();
    if (ImGui::Button("RESET FILTERS", {-1.0F, 0.0F})) {
        shell.typeFilter = -1;
        shell.assetScope = AssetScope::all;
        shell.assetAvailability = AssetAvailability::all;
        shell.assetSort = AssetSort::tag;
        shell.assetSourceFilter[0] = '\0';
    }
    ImGui::EndPopup();
}

void draw_asset_tile(ShellState& shell, const AssetRecord& asset, ImVec2 size) {
    ImGui::PushID(static_cast<int>(asset.tag));
    ImGui::InvisibleButton("asset", size);
    const bool hovered = ImGui::IsItemHovered();
    const bool clicked = ImGui::IsItemClicked();
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
        prepare_asset_context(shell, asset);
        ImGui::OpenPopup("asset_context");
    }
    const bool selected = shell.selectedAssetTag == asset.tag;
    const ImVec2 minimum = ImGui::GetItemRectMin();
    const ImVec2 maximum = ImGui::GetItemRectMax();
    ImDrawList* const draw = ImGui::GetWindowDrawList();
    ImVec4 background = asset_color(shell, asset);
    if (!asset.resident) {
        background.x *= 0.66F;
        background.y *= 0.66F;
        background.z *= 0.66F;
    }
    if (hovered) {
        background.x = (std::min)(background.x + 0.08F, 1.0F);
        background.y = (std::min)(background.y + 0.08F, 1.0F);
        background.z = (std::min)(background.z + 0.08F, 1.0F);
    }
    draw->AddRectFilled(minimum, maximum, ImGui::ColorConvertFloat4ToU32(background));
    ImVec4 borderColor{(std::min)(background.x + 0.20F, 1.0F),
                       (std::min)(background.y + 0.20F, 1.0F),
                       (std::min)(background.z + 0.20F, 1.0F),
                       0.92F};
    draw->AddRect(minimum,
                  maximum,
                  selected ? IM_COL32(220, 183, 88, 245)
                           : ImGui::ColorConvertFloat4ToU32(borderColor),
                  0.0F,
                  0,
                  selected ? 2.0F : 1.0F);
    const std::string_view type = asset_type_name(asset);
    const std::string_view displayName = asset_display_name(shell, asset);
    draw->PushClipRect(
        {minimum.x + 8.0F, minimum.y + 8.0F}, {maximum.x - 20.0F, minimum.y + 35.0F}, true);
    draw->AddText({minimum.x + 8.0F, minimum.y + 13.0F},
                  IM_COL32(222, 226, 225, 245),
                  displayName.data(),
                  displayName.data() + displayName.size());
    draw->PopClipRect();
    draw->AddCircleFilled({maximum.x - 10.0F, minimum.y + 13.0F},
                          3.5F,
                          asset.resident ? IM_COL32(111, 211, 162, 240)
                                         : IM_COL32(104, 111, 114, 220));
    draw->AddLine({minimum.x + 8.0F, minimum.y + 38.0F},
                  {maximum.x - 8.0F, minimum.y + 38.0F},
                  IM_COL32(135, 123, 90, 190));
    std::array<char, 32> tag{};
    (void)std::snprintf(tag.data(), tag.size(), "%08X", static_cast<unsigned>(asset.tag));
    draw->AddText({minimum.x + 8.0F, maximum.y - 33.0F}, IM_COL32(225, 188, 92, 240), tag.data());
    const char* familyEnd = asset.packageFamily.data() + std::strlen(asset.packageFamily.data());
    draw->PushClipRect(
        {minimum.x + 8.0F, maximum.y - 18.0F}, {maximum.x - 8.0F, maximum.y - 3.0F}, true);
    draw->AddText({minimum.x + 8.0F, maximum.y - 18.0F},
                  IM_COL32(130, 137, 138, 230),
                  asset.packageFamily.data(),
                  familyEnd);
    draw->PopClipRect();
    if (clicked) {
        shell.selectedAssetTag = asset.tag;
        clear_actor_selection(shell);
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            queue_camera_spawn(shell, asset);
        }
    }
    if (hovered
        && ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayNormal)
        && ImGui::BeginTooltip()) {
        ImGui::PushTextWrapPos(420.0F);
        ImGui::TextUnformatted(displayName.data(), displayName.data() + displayName.size());
        ImGui::Separator();
        ImGui::Text("Tag               %08X", static_cast<unsigned>(asset.tag));
        ImGui::Text("Object type       %.*s (%s)",
                    static_cast<int>(type.size()),
                    type.data(),
                    asset.typeKnown                 ? "decoded"
                    : shell.catalogMetadataComplete ? "unavailable"
                                                    : "pending");
        ImGui::TextWrapped("Source package    %s", asset.packageFamily.data());
        ImGui::Text("Runtime status    %s",
                    asset.resident ? "Resident / spawnable" : "Installed / nonresident");
        if (asset.definitionRead) {
            ImGui::Text("Definition data   %u bytes", static_cast<unsigned>(asset.definitionSize));
        } else {
            ImGui::TextDisabled("Definition data   %s",
                                shell.catalogMetadataComplete ? "unavailable" : "decoding");
        }
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
    if (asset.resident && ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
        ImGui::SetDragDropPayload(kAssetPayload, &asset.tag, sizeof(asset.tag));
        ImGui::Text("0x%08X", static_cast<unsigned>(asset.tag));
        ImGui::EndDragDropSource();
    }
    if (ImGui::BeginPopup("asset_context")) {
        ImGui::Text("ASSET %08X", static_cast<unsigned>(asset.tag));
        ImGui::TextDisabled("%.*s", static_cast<int>(type.size()), type.data());
        ImGui::Separator();
        ImGui::SetNextItemWidth(260.0F);
        bool applyChanges = ImGui::InputTextWithHint("##asset_custom_name",
                                                     "Custom display name",
                                                     shell.assetContextName,
                                                     sizeof(shell.assetContextName),
                                                     ImGuiInputTextFlags_EnterReturnsTrue);
        ImGui::Checkbox("Custom tile color", &shell.assetContextCustomColor);
        ImGui::BeginDisabled(!shell.assetContextCustomColor);
        ImGui::ColorPicker3("##asset_color_wheel",
                            shell.assetContextColor.data(),
                            ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoAlpha
                                | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
        ImGui::SetNextItemWidth(260.0F);
        ImGui::ColorEdit3("##asset_custom_color",
                          shell.assetContextColor.data(),
                          ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_DisplayRGB);
        ImGui::EndDisabled();
        applyChanges |= ImGui::IsKeyPressed(ImGuiKey_Enter, false)
                        || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter, false);
        if (ImGui::Button("Apply", {126.0F, 0.0F}) || applyChanges) {
            apply_asset_context(shell, asset);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset", {126.0F, 0.0F})) {
            shell.assetContextName[0] = '\0';
            shell.assetContextCustomColor = false;
            const ImVec4 defaultColor = asset.typeKnown ? default_asset_color(asset.objectType)
                                                        : ImVec4{0.075F, 0.08F, 0.085F, 0.97F};
            shell.assetContextColor = {defaultColor.x, defaultColor.y, defaultColor.z};
            apply_asset_context(shell, asset);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    ImGui::PopID();
}

void draw_asset_browser(ShellState& shell) {
    if (!shell.catalogScanned) {
        refresh_catalog(shell);
    }
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.025F, 0.03F, 0.033F, 0.97F});
    ImGui::BeginChild("forge_asset_browser", {0.0F, 0.0F}, true);
    panel_header("ASSET BROWSER");
    constexpr float filterButtonWidth = 82.0F;
    ImGui::SetNextItemWidth((std::max)(ImGui::GetContentRegionAvail().x - filterButtonWidth
                                           - ImGui::GetStyle().ItemSpacing.x,
                                       40.0F));
    ImGui::InputTextWithHint("##asset_filter",
                             "Search name, tag, type, source",
                             shell.assetFilter,
                             sizeof(shell.assetFilter));
    ImGui::SameLine();
    std::array<char, 32> filterLabel{};
    const std::size_t activeFilters = active_asset_filter_count(shell);
    if (activeFilters == 0) {
        (void)std::snprintf(filterLabel.data(), filterLabel.size(), "FILTERS");
    } else {
        (void)std::snprintf(filterLabel.data(), filterLabel.size(), "FILTERS %zu", activeFilters);
    }
    if (ImGui::Button(filterLabel.data(), {filterButtonWidth, 0.0F})) {
        ImGui::OpenPopup("asset_filter_panel");
    }
    draw_asset_filter_panel(shell);

    const std::string filter = lowercase(shell.assetFilter);
    std::vector<std::size_t> visible;
    visible.reserve(shell.assets.size());
    for (std::size_t index = 0; index < shell.assets.size(); ++index) {
        const AssetRecord& asset = shell.assets[index];
        if (!asset_matches_scope(shell, asset)) {
            continue;
        }
        if (!asset_matches_availability(shell, asset)) {
            continue;
        }
        if ((shell.typeFilter == 256 && asset.typeKnown)
            || (shell.typeFilter >= 0 && shell.typeFilter < 256
                && (!asset.typeKnown || asset.objectType != shell.typeFilter))) {
            continue;
        }
        if (shell.assetSourceFilter[0] != '\0'
            && std::strcmp(asset.packageFamily.data(), shell.assetSourceFilter.data()) != 0) {
            continue;
        }
        std::array<char, 16> tag{};
        (void)std::snprintf(tag.data(), tag.size(), "%08x", static_cast<unsigned>(asset.tag));
        if (contains_lower(tag.data(), filter) || contains_lower(asset_type_name(asset), filter)
            || contains_lower(custom_asset_name(shell, asset.tag), filter)
            || contains_lower(asset.packageFamily.data(), filter)) {
            visible.push_back(index);
        }
    }
    if (shell.assetSort != AssetSort::tag) {
        std::stable_sort(
            visible.begin(), visible.end(), [&](std::size_t leftIndex, std::size_t rightIndex) {
                const AssetRecord& left = shell.assets[leftIndex];
                const AssetRecord& right = shell.assets[rightIndex];
                bool less = false;
                bool equal = false;
                switch (shell.assetSort) {
                case AssetSort::tag:
                    break;
                case AssetSort::nameAscending: {
                    const std::string_view leftName = asset_display_name(shell, left);
                    const std::string_view rightName = asset_display_name(shell, right);
                    less = case_insensitive_less(leftName, rightName);
                    equal = !less && !case_insensitive_less(rightName, leftName);
                    break;
                }
                case AssetSort::nameDescending: {
                    const std::string_view leftName = asset_display_name(shell, left);
                    const std::string_view rightName = asset_display_name(shell, right);
                    less = case_insensitive_less(rightName, leftName);
                    equal = !less && !case_insensitive_less(leftName, rightName);
                    break;
                }
                case AssetSort::category: {
                    const std::string_view leftType = asset_type_name(left);
                    const std::string_view rightType = asset_type_name(right);
                    less = case_insensitive_less(leftType, rightType);
                    equal = !less && !case_insensitive_less(rightType, leftType);
                    break;
                }
                case AssetSort::source: {
                    const std::string_view leftSource = left.packageFamily.data();
                    const std::string_view rightSource = right.packageFamily.data();
                    less = case_insensitive_less(leftSource, rightSource);
                    equal = !less && !case_insensitive_less(rightSource, leftSource);
                    break;
                }
                }
                return equal ? left.tag < right.tag : less;
            });
    }
    ImGui::TextDisabled("%zu / %zu   RESIDENT %zu%s",
                        visible.size(),
                        shell.assets.size(),
                        shell.catalogResidentCount,
                        shell.catalogDecodeActive ? "   INDEXING" : "");
    ImGui::BeginChild("asset_catalog_scroll", {0.0F, 0.0F}, false);
    constexpr int columns = 2;
    const float tileWidth = (ImGui::GetContentRegionAvail().x - 6.0F) / columns;
    constexpr float tileHeight = 92.0F;
    const int rows = static_cast<int>((visible.size() + columns - 1) / columns);
    ImGuiListClipper clipper;
    clipper.Begin(rows, tileHeight + 6.0F);
    while (clipper.Step()) {
        for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row) {
            for (int column = 0; column < columns; ++column) {
                const std::size_t visibleIndex = static_cast<std::size_t>(row * columns + column);
                if (visibleIndex >= visible.size()) {
                    break;
                }
                if (column != 0) {
                    ImGui::SameLine();
                }
                draw_asset_tile(
                    shell, shell.assets[visible[visibleIndex]], {tileWidth, tileHeight});
            }
        }
    }
    ImGui::EndChild();
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

[[nodiscard]] bool actor_matches(const TrackedActor& actor, std::string_view filter) {
    if (filter.empty()) {
        return true;
    }
    std::array<char, 32> identity{};
    (void)std::snprintf(identity.data(),
                        identity.size(),
                        "%08x %08x",
                        static_cast<unsigned>(actor.tag),
                        static_cast<unsigned>(actor.handle));
    return contains_lower(actor.name, filter)
           || contains_lower(research::native_object_type_name(actor.objectType), filter)
           || contains_lower(identity.data(), filter);
}

void append_actor_order(const ShellState& shell,
                        std::uint64_t parentId,
                        std::vector<std::uint64_t>& order) {
    for (const TrackedActor& actor : shell.actors) {
        if (actor.source != ActorSource::forge || actor.parentId != parentId) {
            continue;
        }
        order.push_back(actor.editorId);
        append_actor_order(shell, actor.editorId, order);
    }
}

[[nodiscard]] std::vector<std::uint64_t> explorer_actor_order(const ShellState& shell,
                                                              std::string_view filter) {
    std::vector<std::uint64_t> order;
    order.reserve(shell.actors.size());
    if (!filter.empty()) {
        for (const TrackedActor& actor : shell.actors) {
            if (actor_matches(actor, filter)) {
                order.push_back(actor.editorId);
            }
        }
        return order;
    }
    append_actor_order(shell, 0, order);
    for (const TrackedActor& actor : shell.actors) {
        if (actor.source != ActorSource::forge) {
            order.push_back(actor.editorId);
        }
    }
    return order;
}

void select_actor_from_explorer(ShellState& shell,
                                std::uint64_t id,
                                const std::vector<std::uint64_t>& order) {
    const ImGuiIO& io = ImGui::GetIO();
    if (io.KeyShift && shell.selectionAnchorId != 0) {
        const auto anchor = std::find(order.begin(), order.end(), shell.selectionAnchorId);
        const auto clicked = std::find(order.begin(), order.end(), id);
        if (anchor != order.end() && clicked != order.end()) {
            const std::uint64_t retainedAnchor = shell.selectionAnchorId;
            if (!io.KeyCtrl) {
                clear_actor_selection(shell);
            }
            const auto first = (std::min)(anchor, clicked);
            const auto last = (std::max)(anchor, clicked);
            for (auto current = first; current != std::next(last); ++current) {
                add_actor_selection(shell, *current);
            }
            shell.selectedActorId = id;
            shell.selectionAnchorId = retainedAnchor;
            return;
        }
    }

    if (io.KeyCtrl) {
        if (actor_selected(shell, id)) {
            shell.selectedActorIds.erase(
                std::remove(shell.selectedActorIds.begin(), shell.selectedActorIds.end(), id),
                shell.selectedActorIds.end());
            shell.selectedActorId =
                shell.selectedActorIds.empty() ? 0 : shell.selectedActorIds.back();
        } else {
            add_actor_selection(shell, id);
        }
        shell.selectionAnchorId = id;
        shell.selectedAssetTag = 0;
        return;
    }
    select_only_actor(shell, id);
}

[[nodiscard]] bool has_children(const ShellState& shell, std::uint64_t parentId) noexcept {
    return std::any_of(shell.actors.begin(), shell.actors.end(), [parentId](const auto& actor) {
        return actor.source == ActorSource::forge && actor.parentId == parentId;
    });
}

void actor_drag_target(ShellState& shell, std::uint64_t parentId) {
    if (!ImGui::BeginDragDropTarget()) {
        return;
    }
    if (const ImGuiPayload* const payload = ImGui::AcceptDragDropPayload(kActorPayload);
        payload != nullptr && payload->DataSize == sizeof(std::uint64_t)) {
        std::uint64_t child = 0;
        std::memcpy(&child, payload->Data, sizeof(child));
        if (TrackedActor* const actor = find_actor(shell, child);
            actor != nullptr && child != parentId) {
            std::uint64_t ancestor = parentId;
            bool cycle = false;
            while (ancestor != 0) {
                if (ancestor == child) {
                    cycle = true;
                    break;
                }
                const TrackedActor* const parent = find_actor(shell, ancestor);
                ancestor = parent == nullptr ? 0 : parent->parentId;
            }
            if (!cycle) {
                actor->parentId = parentId;
            }
        }
    }
    ImGui::EndDragDropTarget();
}

void draw_actor_node(ShellState& shell,
                     TrackedActor& actor,
                     const std::vector<std::uint64_t>& order) {
    const bool editableHierarchy = actor.source == ActorSource::forge;
    const bool children = editableHierarchy && has_children(shell, actor.editorId);
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;
    if (actor_selected(shell, actor.editorId)) {
        flags |= ImGuiTreeNodeFlags_Selected;
    }
    if (!children) {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }
    std::array<char, 256> label{};
    if (actor.source == ActorSource::authoredMap) {
        (void)std::snprintf(label.data(),
                            label.size(),
                            "%s  [%08X:%u]##%llu",
                            actor.name.c_str(),
                            static_cast<unsigned>(actor.tableTag),
                            static_cast<unsigned>(actor.entryIndex),
                            static_cast<unsigned long long>(actor.editorId));
    } else {
        (void)std::snprintf(label.data(),
                            label.size(),
                            "%s%s  [%08X]##%llu",
                            actor.name.c_str(),
                            actor.nativeExpired ? "  [EXPIRED]" : "",
                            static_cast<unsigned>(actor.handle),
                            static_cast<unsigned long long>(actor.editorId));
    }
    const bool open = ImGui::TreeNodeEx(label.data(), flags);
    if (ImGui::IsItemClicked(ImGuiMouseButton_Left) && !ImGui::IsItemToggledOpen()) {
        select_actor_from_explorer(shell, actor.editorId, order);
    }
    if (editableHierarchy && ImGui::BeginDragDropSource()) {
        ImGui::SetDragDropPayload(kActorPayload, &actor.editorId, sizeof(actor.editorId));
        ImGui::TextUnformatted(actor.name.c_str());
        ImGui::EndDragDropSource();
    }
    if (editableHierarchy) {
        actor_drag_target(shell, actor.editorId);
    }
    if (children && open) {
        const std::uint64_t parentId = actor.editorId;
        for (TrackedActor& child : shell.actors) {
            if (child.parentId == parentId) {
                draw_actor_node(shell, child, order);
            }
        }
        ImGui::TreePop();
    }
}

void draw_actor_group(ShellState& shell,
                      const char* label,
                      ActorSource source,
                      std::size_t count,
                      const std::vector<std::uint64_t>& order) {
    std::array<char, 96> heading{};
    (void)std::snprintf(heading.data(), heading.size(), "%s  (%zu)", label, count);
    const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen
                                     | ImGuiTreeNodeFlags_SpanFullWidth
                                     | ImGuiTreeNodeFlags_OpenOnArrow;
    if (!ImGui::TreeNodeEx(heading.data(), flags)) {
        return;
    }
    for (TrackedActor& actor : shell.actors) {
        if (actor.source == source && actor.parentId == 0) {
            draw_actor_node(shell, actor, order);
        }
    }
    ImGui::TreePop();
}

void draw_explorer(ShellState& shell) {
    ImGui::TextUnformatted("EXPLORER");
    ImGui::SameLine(ImGui::GetContentRegionMax().x - 42.0F);
    if (icon_button("##explorer_refresh", Icon::refresh, "Refresh Live Map Objects")) {
        refresh_world_objects(shell);
    }
    const ImVec2 line = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddLine(
        line, {line.x + ImGui::GetContentRegionAvail().x, line.y}, IM_COL32(155, 137, 91, 190));
    ImGui::Dummy({0.0F, 4.0F});
    ImGui::SetNextItemWidth(-1.0F);
    ImGui::InputTextWithHint("##explorer_filter",
                             "Filter tracked objects",
                             shell.explorerFilter,
                             sizeof(shell.explorerFilter));
    ImGui::BeginChild("explorer_tree_scroll", {0.0F, 0.0F}, false);
    if (ImGui::Selectable("WORLD ROOT",
                          shell.selectedActorIds.empty() && shell.selectedAssetTag == 0)) {
        clear_actor_selection(shell);
        shell.selectedAssetTag = 0;
    }
    actor_drag_target(shell, 0);
    const std::string filter = lowercase(shell.explorerFilter);
    const std::vector<std::uint64_t> order = explorer_actor_order(shell, filter);
    if (filter.empty()) {
        const std::size_t forgeCount = static_cast<std::size_t>(
            std::count_if(shell.actors.begin(), shell.actors.end(), [](const auto& actor) {
                return actor.source == ActorSource::forge;
            }));
        const std::size_t liveMapCount = static_cast<std::size_t>(
            std::count_if(shell.actors.begin(), shell.actors.end(), [](const auto& actor) {
                return actor.source == ActorSource::liveMap;
            }));
        const std::size_t authoredMapCount = shell.actors.size() - forgeCount - liveMapCount;
        draw_actor_group(shell, "FORGE OBJECTS", ActorSource::forge, forgeCount, order);
        draw_actor_group(shell, "LIVE MAP OBJECTS", ActorSource::liveMap, liveMapCount, order);
        draw_actor_group(
            shell, "AUTHORED STATIC PLACEMENTS", ActorSource::authoredMap, authoredMapCount, order);
    } else {
        for (TrackedActor& actor : shell.actors) {
            if (!actor_matches(actor, filter)) {
                continue;
            }
            ImGui::PushID(static_cast<int>(actor.editorId));
            if (ImGui::Selectable(actor.name.c_str(), actor_selected(shell, actor.editorId))) {
                select_actor_from_explorer(shell, actor.editorId, order);
            }
            ImGui::PopID();
        }
    }
    ImGui::EndChild();
}

void sync_rename(ShellState& shell, const TrackedActor* actor) noexcept {
    if (actor == nullptr) {
        shell.renameActorId = 0;
        shell.renameBuffer[0] = '\0';
        return;
    }
    if (shell.renameActorId == actor->editorId) {
        return;
    }
    shell.renameActorId = actor->editorId;
    const std::size_t count = (std::min)(actor->name.size(), sizeof(shell.renameBuffer) - 1);
    std::memcpy(shell.renameBuffer, actor->name.data(), count);
    shell.renameBuffer[count] = '\0';
}

[[nodiscard]] const char* world_identity_text(native_spawn::WorldObjectIdentity identity) noexcept {
    switch (identity) {
    case native_spawn::WorldObjectIdentity::definitionTag:
        return "entity tag";
    case native_spawn::WorldObjectIdentity::definitionPointer:
        return "definition pointer";
    case native_spawn::WorldObjectIdentity::tagAndPointer:
        return "entity tag + definition pointer";
    }
    return "unknown";
}

void draw_properties(ShellState& shell) {
    panel_header("PROPERTIES");
    TrackedActor* actor = find_actor(shell, shell.selectedActorId);
    sync_rename(shell, actor);
    if (actor == nullptr) {
        if (const AssetRecord* const asset = find_asset(shell, shell.selectedAssetTag);
            asset != nullptr) {
            const std::string_view customName = custom_asset_name(shell, asset->tag);
            if (!customName.empty()) {
                ImGui::TextWrapped(
                    "Name      %.*s", static_cast<int>(customName.size()), customName.data());
            }
            ImGui::Text("Tag       %08X", static_cast<unsigned>(asset->tag));
            const std::string_view type = asset_type_name(*asset);
            ImGui::Text("Type      %.*s", static_cast<int>(type.size()), type.data());
            ImGui::TextWrapped("Package   %s", asset->packageFamily.data());
            ImGui::Text("Runtime   %s",
                        asset->resident ? "Resident / spawnable" : "Installed / nonresident");
            if (asset->definitionRead) {
                ImGui::Text("Data      %u bytes", static_cast<unsigned>(asset->definitionSize));
            }
            ImGui::Spacing();
            ImGui::BeginDisabled(!asset->resident);
            if (ImGui::Button("Spawn Instance", {-1.0F, 0.0F})) {
                queue_camera_spawn(shell, *asset);
            }
            ImGui::EndDisabled();
            if (!asset->resident && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                ImGui::SetTooltip("This definition is not resident in the current destination.");
            }
            return;
        }
        ImGui::TextDisabled("No tracked object selected");
        return;
    }
    if (shell.selectedActorIds.size() > 1) {
        ImGui::TextDisabled("%zu objects selected; editing primary", shell.selectedActorIds.size());
    }
    ImGui::SetNextItemWidth(-1.0F);
    if (ImGui::InputText("##actor_name",
                         shell.renameBuffer,
                         sizeof(shell.renameBuffer),
                         ImGuiInputTextFlags_EnterReturnsTrue)
        && shell.renameBuffer[0] != '\0') {
        actor->name = shell.renameBuffer;
    }
    ImGui::Text("Tag       %08X", static_cast<unsigned>(actor->tag));
    ImGui::Text("Handle    %08X", static_cast<unsigned>(actor->handle));
    const std::string_view type = research::native_object_type_name(actor->objectType);
    ImGui::Text("Type      %.*s", static_cast<int>(type.size()), type.data());
    if (actor->source == ActorSource::liveMap) {
        ImGui::TextUnformatted("Source    Live map datum");
        ImGui::Text("Identity  %s", world_identity_text(actor->identity));
    } else if (actor->source == ActorSource::authoredMap) {
        ImGui::TextUnformatted("Source    Authored package placement");
        ImGui::Text("Table     %08X", static_cast<unsigned>(actor->tableTag));
        ImGui::Text("Entry     %u", static_cast<unsigned>(actor->entryIndex));
        ImGui::Text("Parent    %08X", static_cast<unsigned>(actor->parentTag));
    } else {
        ImGui::TextUnformatted("Source    Forge-created");
        ImGui::Text("State     %s", actor->nativeExpired ? "Expired by Destiny" : "Live");
    }
    ImGui::Spacing();
    if (!actor->transformKnown) {
        ImGui::TextWrapped(
            "Native transform readback is not decoded for imported map objects. Identity and "
            "selection are available; transform, duplicate, and save remain gated. Object types "
            "with the recovered activation transform path can be removed until the world reloads.");
        ImGui::Spacing();
    }
    if (actor->nativeExpired) {
        ImGui::TextWrapped(
            "Destiny removed this transient native object. Delete now removes its stale Forge "
            "record; Duplicate can create a fresh instance.");
        ImGui::Spacing();
    }
    ImGui::BeginDisabled(!actor->transformKnown || actor->nativeExpired
                         || actor->source == ActorSource::authoredMap);
    float position[3]{actor->transform.translation.x,
                      actor->transform.translation.y,
                      actor->transform.translation.z};
    if (ImGui::InputFloat3("Position", position, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) {
        core::Transform transform = actor->transform;
        transform.translation = {position[0], position[1], position[2]};
        write_actor_transform(shell, *actor, transform, true);
    }
    float rotation[4]{actor->transform.rotation.x,
                      actor->transform.rotation.y,
                      actor->transform.rotation.z,
                      actor->transform.rotation.w};
    if (ImGui::InputFloat4("Rotation", rotation, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) {
        core::Transform transform = actor->transform;
        transform.rotation = {rotation[0], rotation[1], rotation[2], rotation[3]};
        write_actor_transform(shell, *actor, transform, true);
    }
    float scale = actor->transform.uniformScale;
    if (ImGui::InputFloat(
            "Scale", &scale, 0.1F, 1.0F, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) {
        core::Transform transform = actor->transform;
        transform.uniformScale = (std::clamp)(scale, 0.05F, 100.0F);
        write_actor_transform(shell, *actor, transform, true);
    }
    ImGui::EndDisabled();
    ImGui::Spacing();
    if (icon_button("##property_duplicate",
                    Icon::duplicate,
                    "Duplicate Selected",
                    false,
                    selected_actor_can_duplicate(shell))) {
        duplicate_selected(shell);
    }
    ImGui::SameLine();
    if (icon_button("##property_delete",
                    Icon::remove,
                    kNativeDeleteBlocker,
                    false,
                    selected_actor_can_delete(shell))) {
        delete_selected(shell);
    }
}

using WorldVector = teleport::Vector;

struct CameraProjection {
    WorldVector position{};
    WorldVector forward{};
    WorldVector right{};
    WorldVector up{};
    ImVec2 center{};
    float focalLength{};
};

struct GizmoHit {
    GizmoAxis axis{GizmoAxis::none};
    ImVec2 screenDirection{};
    float unitsPerPixel{};
    float distance{(std::numeric_limits<float>::max)()};
};

[[nodiscard]] float world_dot(const WorldVector& left, const WorldVector& right) noexcept {
    return left[0] * right[0] + left[1] * right[1] + left[2] * right[2];
}

[[nodiscard]] WorldVector world_cross(const WorldVector& left, const WorldVector& right) noexcept {
    return {left[1] * right[2] - left[2] * right[1],
            left[2] * right[0] - left[0] * right[2],
            left[0] * right[1] - left[1] * right[0]};
}

[[nodiscard]] bool normalize_world(WorldVector& value) noexcept {
    const float lengthSquared = world_dot(value, value);
    if (!std::isfinite(lengthSquared) || lengthSquared <= 0.000001F) {
        return false;
    }
    const float inverseLength = 1.0F / std::sqrt(lengthSquared);
    for (float& lane : value) {
        lane *= inverseLength;
    }
    return true;
}

[[nodiscard]] WorldVector
transformed_point(const WorldVector& point, const WorldVector& axis, float distance) noexcept {
    return {point[0] + axis[0] * distance,
            point[1] + axis[1] * distance,
            point[2] + axis[2] * distance};
}

[[nodiscard]] WorldVector actor_position(const TrackedActor& actor) noexcept {
    return {actor.transform.translation.x,
            actor.transform.translation.y,
            actor.transform.translation.z};
}

[[nodiscard]] WorldVector rotate_vector(const core::Quat& input,
                                        const WorldVector& vector) noexcept {
    float x = input.x;
    float y = input.y;
    float z = input.z;
    float w = input.w;
    const float lengthSquared = x * x + y * y + z * z + w * w;
    if (!std::isfinite(lengthSquared) || lengthSquared <= 0.000001F) {
        return vector;
    }
    const float inverseLength = 1.0F / std::sqrt(lengthSquared);
    x *= inverseLength;
    y *= inverseLength;
    z *= inverseLength;
    w *= inverseLength;
    const WorldVector imaginary{x, y, z};
    const WorldVector crossed = world_cross(imaginary, vector);
    const WorldVector crossedAgain = world_cross(imaginary, crossed);
    return {vector[0] + 2.0F * (w * crossed[0] + crossedAgain[0]),
            vector[1] + 2.0F * (w * crossed[1] + crossedAgain[1]),
            vector[2] + 2.0F * (w * crossed[2] + crossedAgain[2])};
}

[[nodiscard]] std::array<WorldVector, 3> actor_axes(const core::Transform& transform) noexcept {
    return {rotate_vector(transform.rotation, {1.0F, 0.0F, 0.0F}),
            rotate_vector(transform.rotation, {0.0F, 1.0F, 0.0F}),
            rotate_vector(transform.rotation, {0.0F, 0.0F, 1.0F})};
}

[[nodiscard]] std::size_t axis_index(GizmoAxis axis) noexcept {
    switch (axis) {
    case GizmoAxis::x:
        return 0;
    case GizmoAxis::y:
        return 1;
    case GizmoAxis::z:
        return 2;
    case GizmoAxis::none:
        break;
    }
    return 0;
}

[[nodiscard]] bool camera_projection(float horizontalFov, CameraProjection& projection) noexcept {
    if (!teleport::current_camera_pose(projection.position, projection.forward)
        || !normalize_world(projection.forward)) {
        return false;
    }
    projection.right = {projection.forward[1], -projection.forward[0], 0.0F};
    if (!normalize_world(projection.right)) {
        return false;
    }
    projection.up = world_cross(projection.right, projection.forward);
    if (!normalize_world(projection.up)) {
        return false;
    }
    const ImVec2 display = ImGui::GetIO().DisplaySize;
    const float tangent = std::tan(horizontalFov * 0.00872664626F);
    if (display.x <= 1.0F || display.y <= 1.0F || !std::isfinite(tangent) || tangent <= 0.001F) {
        return false;
    }
    projection.center = {display.x * 0.5F, display.y * 0.5F};
    projection.focalLength = display.x * 0.5F / tangent;
    return true;
}

[[nodiscard]] bool project_world(const CameraProjection& projection,
                                 const WorldVector& point,
                                 ImVec2& screen,
                                 float* depthOutput = nullptr) noexcept {
    const WorldVector relative{point[0] - projection.position[0],
                               point[1] - projection.position[1],
                               point[2] - projection.position[2]};
    const float depth = world_dot(relative, projection.forward);
    if (!std::isfinite(depth) || depth <= 0.05F) {
        return false;
    }
    const float horizontal = world_dot(relative, projection.right);
    const float vertical = world_dot(relative, projection.up);
    screen = {projection.center.x + horizontal * projection.focalLength / depth,
              projection.center.y - vertical * projection.focalLength / depth};
    if (depthOutput != nullptr) {
        *depthOutput = depth;
    }
    return std::isfinite(screen.x) && std::isfinite(screen.y);
}

[[nodiscard]] float screen_length(ImVec2 vector) noexcept {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

[[nodiscard]] ImVec2 normalized_screen(ImVec2 vector) noexcept {
    const float length = screen_length(vector);
    return length <= 0.001F ? ImVec2{} : ImVec2{vector.x / length, vector.y / length};
}

void consider_gizmo_segment(GizmoHit& hit,
                            GizmoAxis axis,
                            ImVec2 start,
                            ImVec2 end,
                            float unitsPerPixel,
                            ImVec2 mouse) noexcept {
    const ImVec2 segment{end.x - start.x, end.y - start.y};
    const float lengthSquared = segment.x * segment.x + segment.y * segment.y;
    if (lengthSquared <= 16.0F) {
        return;
    }
    const ImVec2 relative{mouse.x - start.x, mouse.y - start.y};
    const float amount =
        (std::clamp)((relative.x * segment.x + relative.y * segment.y) / lengthSquared, 0.0F, 1.0F);
    const ImVec2 closest{start.x + segment.x * amount, start.y + segment.y * amount};
    const float distance = screen_length({mouse.x - closest.x, mouse.y - closest.y});
    if (distance >= hit.distance) {
        return;
    }
    hit.axis = axis;
    hit.screenDirection = normalized_screen(segment);
    hit.unitsPerPixel = unitsPerPixel;
    hit.distance = distance;
}

[[nodiscard]] core::Quat multiply_quaternion(const core::Quat& left,
                                             const core::Quat& right) noexcept {
    return {left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y,
            left.w * right.y - left.x * right.z + left.y * right.w + left.z * right.x,
            left.w * right.z + left.x * right.y - left.y * right.x + left.z * right.w,
            left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z};
}

[[nodiscard]] core::Quat local_axis_rotation(std::size_t axis, float radians) noexcept {
    const float half = radians * 0.5F;
    const float sine = std::sin(half);
    core::Quat result{};
    result.w = std::cos(half);
    if (axis == 0) {
        result.x = sine;
    } else if (axis == 1) {
        result.y = sine;
    } else {
        result.z = sine;
    }
    return result;
}

void finish_gizmo_drag(ShellState& shell) {
    if (!shell.gizmoDrag.active) {
        return;
    }
    if (TrackedActor* const actor = find_actor(shell, shell.gizmoDrag.actorId);
        actor != nullptr && !same_transform(shell.gizmoDrag.startTransform, actor->transform)) {
        shell.undo.push_back({actor->editorId, shell.gizmoDrag.startTransform, actor->transform});
        shell.redo.clear();
        set_status(shell, "Transform committed for %s.", actor->name.c_str());
    }
    shell.gizmoDrag = {};
}

void service_gizmo_drag(ShellState& shell) {
    if (!shell.gizmoDrag.active) {
        return;
    }
    TrackedActor* const actor = find_actor(shell, shell.gizmoDrag.actorId);
    if (actor == nullptr || actor->nativeExpired || !actor->transformKnown) {
        shell.gizmoDrag = {};
        return;
    }
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        finish_gizmo_drag(shell);
        return;
    }

    const ImVec2 mouse = ImGui::GetIO().MousePos;
    const ImVec2 delta{mouse.x - shell.gizmoDrag.startMouse.x,
                       mouse.y - shell.gizmoDrag.startMouse.y};
    const float signedPixels =
        delta.x * shell.gizmoDrag.screenDirection.x + delta.y * shell.gizmoDrag.screenDirection.y;
    core::Transform transform = shell.gizmoDrag.startTransform;
    const std::size_t selectedAxis = axis_index(shell.gizmoDrag.axis);
    if (shell.gizmoDrag.mode == TransformMode::move) {
        const WorldVector axis = actor_axes(shell.gizmoDrag.startTransform)[selectedAxis];
        const float movement = signedPixels * shell.gizmoDrag.worldUnitsPerPixel;
        transform.translation.x += axis[0] * movement;
        transform.translation.y += axis[1] * movement;
        transform.translation.z += axis[2] * movement;
    } else if (shell.gizmoDrag.mode == TransformMode::rotate) {
        const float radians = signedPixels * shell.gizmoDrag.worldUnitsPerPixel;
        transform.rotation = multiply_quaternion(shell.gizmoDrag.startTransform.rotation,
                                                 local_axis_rotation(selectedAxis, radians));
    } else if (shell.gizmoDrag.mode == TransformMode::scale) {
        transform.uniformScale = (std::clamp)(shell.gizmoDrag.startTransform.uniformScale
                                                  * std::exp(signedPixels * 0.01F),
                                              0.05F,
                                              100.0F);
    }
    if (!same_transform(actor->transform, transform)) {
        write_actor_transform(shell, *actor, transform, false);
    }
}

void begin_gizmo_drag(ShellState& shell, const TrackedActor& actor, const GizmoHit& hit) noexcept {
    shell.gizmoDrag.actorId = actor.editorId;
    shell.gizmoDrag.axis = hit.axis;
    shell.gizmoDrag.mode = shell.transformMode;
    shell.gizmoDrag.startMouse = ImGui::GetIO().MousePos;
    shell.gizmoDrag.screenDirection = hit.screenDirection;
    shell.gizmoDrag.startTransform = actor.transform;
    shell.gizmoDrag.worldUnitsPerPixel = hit.unitsPerPixel;
    shell.gizmoDrag.active = true;
}

constexpr std::array<ImU32, 3> kGizmoAxisColors{
    IM_COL32(232, 76, 71, 255), IM_COL32(82, 205, 115, 255), IM_COL32(78, 151, 244, 255)};
constexpr std::array<const char*, 3> kGizmoAxisLabels{"X", "Y", "Z"};

void draw_linear_gizmo(ShellState& shell,
                       const TrackedActor& actor,
                       const CameraProjection& projection,
                       ImDrawList* draw,
                       ImVec2 anchor,
                       float depth,
                       bool viewportHovered) {
    const std::array<WorldVector, 3> axes = actor_axes(actor.transform);
    const WorldVector origin = actor_position(actor);
    const float worldLength = (std::clamp)(depth * 78.0F / projection.focalLength, 0.25F, 60.0F);
    std::array<ImVec2, 3> endpoints{};
    std::array<bool, 3> valid{};
    GizmoHit hit{};
    for (std::size_t index = 0; index < axes.size(); ++index) {
        valid[index] = project_world(
            projection, transformed_point(origin, axes[index], worldLength), endpoints[index]);
        if (!valid[index]) {
            continue;
        }
        const float pixels =
            screen_length({endpoints[index].x - anchor.x, endpoints[index].y - anchor.y});
        if (pixels < 12.0F) {
            valid[index] = false;
            continue;
        }
        consider_gizmo_segment(hit,
                               static_cast<GizmoAxis>(index + 1),
                               anchor,
                               endpoints[index],
                               worldLength / pixels,
                               ImGui::GetIO().MousePos);
    }
    if (!viewportHovered || hit.distance > 10.0F) {
        hit.axis = GizmoAxis::none;
    }
    const GizmoAxis activeAxis = shell.gizmoDrag.active ? shell.gizmoDrag.axis : hit.axis;
    for (std::size_t index = 0; index < axes.size(); ++index) {
        if (!valid[index]) {
            continue;
        }
        const GizmoAxis axis = static_cast<GizmoAxis>(index + 1);
        const bool active = axis == activeAxis;
        const ImVec2 direction =
            normalized_screen({endpoints[index].x - anchor.x, endpoints[index].y - anchor.y});
        const ImU32 color = kGizmoAxisColors[index];
        draw->AddLine(anchor, endpoints[index], color, active ? 4.0F : 2.2F);
        if (shell.transformMode == TransformMode::move) {
            const ImVec2 perpendicular{-direction.y, direction.x};
            const ImVec2 base{endpoints[index].x - direction.x * 12.0F,
                              endpoints[index].y - direction.y * 12.0F};
            draw->AddTriangleFilled(
                endpoints[index],
                {base.x + perpendicular.x * 5.0F, base.y + perpendicular.y * 5.0F},
                {base.x - perpendicular.x * 5.0F, base.y - perpendicular.y * 5.0F},
                color);
        } else {
            const float half = active ? 6.0F : 5.0F;
            draw->AddRectFilled({endpoints[index].x - half, endpoints[index].y - half},
                                {endpoints[index].x + half, endpoints[index].y + half},
                                color);
        }
        draw->AddText(
            {endpoints[index].x + direction.x * 5.0F, endpoints[index].y + direction.y * 5.0F},
            color,
            kGizmoAxisLabels[index]);
    }
    if (!shell.gizmoDrag.active && hit.axis != GizmoAxis::none
        && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        begin_gizmo_drag(shell, actor, hit);
    }
}

void draw_rotation_gizmo(ShellState& shell,
                         const TrackedActor& actor,
                         const CameraProjection& projection,
                         ImDrawList* draw,
                         ImVec2 anchor,
                         float depth,
                         bool viewportHovered) {
    constexpr std::size_t segments = 48;
    const std::array<WorldVector, 3> axes = actor_axes(actor.transform);
    const WorldVector origin = actor_position(actor);
    const float radius = (std::clamp)(depth * 64.0F / projection.focalLength, 0.2F, 50.0F);
    std::array<std::array<ImVec2, segments + 1>, 3> points{};
    std::array<std::array<bool, segments + 1>, 3> valid{};
    GizmoHit hit{};
    for (std::size_t axis = 0; axis < axes.size(); ++axis) {
        const WorldVector& first = axes[(axis + 1) % 3];
        const WorldVector& second = axes[(axis + 2) % 3];
        for (std::size_t point = 0; point <= segments; ++point) {
            const float angle =
                static_cast<float>(point) * 6.28318530718F / static_cast<float>(segments);
            WorldVector world = transformed_point(origin, first, std::cos(angle) * radius);
            world = transformed_point(world, second, std::sin(angle) * radius);
            valid[axis][point] = project_world(projection, world, points[axis][point]);
            if (point == 0 || !valid[axis][point] || !valid[axis][point - 1]) {
                continue;
            }
            consider_gizmo_segment(hit,
                                   static_cast<GizmoAxis>(axis + 1),
                                   points[axis][point - 1],
                                   points[axis][point],
                                   1.0F / 64.0F,
                                   ImGui::GetIO().MousePos);
        }
    }
    if (!viewportHovered || hit.distance > 9.0F) {
        hit.axis = GizmoAxis::none;
    }
    const GizmoAxis activeAxis = shell.gizmoDrag.active ? shell.gizmoDrag.axis : hit.axis;
    for (std::size_t axis = 0; axis < axes.size(); ++axis) {
        const bool active = static_cast<GizmoAxis>(axis + 1) == activeAxis;
        for (std::size_t point = 1; point <= segments; ++point) {
            if (valid[axis][point] && valid[axis][point - 1]) {
                draw->AddLine(points[axis][point - 1],
                              points[axis][point],
                              kGizmoAxisColors[axis],
                              active ? 3.5F : 1.8F);
            }
        }
    }
    draw->AddCircle(anchor, 5.0F, IM_COL32(235, 238, 237, 220), 16, 1.3F);
    if (!shell.gizmoDrag.active && hit.axis != GizmoAxis::none
        && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        begin_gizmo_drag(shell, actor, hit);
    }
}

void draw_selected_actor_gizmo(ShellState& shell,
                               ImDrawList* draw,
                               ImVec2 viewportMinimum,
                               ImVec2 viewportMaximum,
                               bool viewportHovered) {
    TrackedActor* actor = find_actor(shell, shell.selectedActorId);
    if (actor == nullptr || !actor->transformKnown || actor->nativeExpired) {
        service_gizmo_drag(shell);
        return;
    }
    const core::Transform visualTransform = actor->transform;
    service_gizmo_drag(shell);
    actor = find_actor(shell, shell.selectedActorId);
    if (actor == nullptr || !actor->transformKnown || actor->nativeExpired) {
        return;
    }
    TrackedActor visualActor = *actor;
    if (shell.gizmoDrag.active && shell.gizmoDrag.actorId == actor->editorId) {
        visualActor.transform = visualTransform;
    }
    CameraProjection projection{};
    ImVec2 anchor{};
    float depth = 0.0F;
    if (!camera_projection(shell.projectionHorizontalFov, projection)
        || !project_world(projection, actor_position(visualActor), anchor, &depth)) {
        return;
    }
    const bool anchorNearViewport =
        anchor.x >= viewportMinimum.x - 120.0F && anchor.x <= viewportMaximum.x + 120.0F
        && anchor.y >= viewportMinimum.y - 120.0F && anchor.y <= viewportMaximum.y + 120.0F;
    if (!anchorNearViewport) {
        return;
    }
    draw->AddCircle(anchor, 10.0F, IM_COL32(235, 238, 237, 210), 20, 1.2F);
    draw->AddCircle(anchor, 14.0F, IM_COL32(211, 174, 84, 150), 24, 1.0F);
    if (shell.transformMode == TransformMode::move || shell.transformMode == TransformMode::scale) {
        draw_linear_gizmo(shell, visualActor, projection, draw, anchor, depth, viewportHovered);
    } else if (shell.transformMode == TransformMode::rotate) {
        draw_rotation_gizmo(shell, visualActor, projection, draw, anchor, depth, viewportHovered);
    }
}

void draw_live_viewport(ShellState& shell) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.0F, 0.0F, 0.0F, 0.0F});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0F, 0.0F});
    ImGui::BeginChild("forge_live_viewport",
                      {0.0F, 0.0F},
                      false,
                      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleVar();
    const ImVec2 size = ImGui::GetContentRegionAvail();
    ImGui::InvisibleButton("live_world_canvas",
                           size,
                           ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
    const bool hovered = ImGui::IsItemHovered();
    g_cameraControl.store(hovered && ImGui::IsMouseDown(ImGuiMouseButton_Right),
                          std::memory_order_release);
    const ImVec2 minimum = ImGui::GetItemRectMin();
    const ImVec2 maximum = ImGui::GetItemRectMax();
    ImDrawList* const draw = ImGui::GetWindowDrawList();
    constexpr float bracket = 20.0F;
    constexpr ImU32 edge = IM_COL32(210, 214, 210, 160);
    draw->AddLine(minimum, {minimum.x + bracket, minimum.y}, edge);
    draw->AddLine(minimum, {minimum.x, minimum.y + bracket}, edge);
    draw->AddLine({maximum.x - bracket, minimum.y}, {maximum.x, minimum.y}, edge);
    draw->AddLine({maximum.x, minimum.y}, {maximum.x, minimum.y + bracket}, edge);
    draw->AddLine({minimum.x, maximum.y}, {minimum.x + bracket, maximum.y}, edge);
    draw->AddLine({minimum.x, maximum.y - bracket}, {minimum.x, maximum.y}, edge);
    draw->AddLine({maximum.x - bracket, maximum.y}, maximum, edge);
    draw->AddLine({maximum.x, maximum.y - bracket}, maximum, edge);

    const ImVec2 center{(minimum.x + maximum.x) * 0.5F, (minimum.y + maximum.y) * 0.5F};
    draw->AddCircle(center, 5.0F, IM_COL32(225, 229, 225, 145), 16, 1.0F);
    draw->AddLine({center.x - 10.0F, center.y}, {center.x - 4.0F, center.y}, edge);
    draw->AddLine({center.x + 4.0F, center.y}, {center.x + 10.0F, center.y}, edge);

    draw_selected_actor_gizmo(shell, draw, minimum, maximum, hovered);

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* const payload = ImGui::AcceptDragDropPayload(kAssetPayload);
            payload != nullptr && payload->DataSize == sizeof(std::uint32_t)) {
            std::uint32_t tag = 0;
            std::memcpy(&tag, payload->Data, sizeof(tag));
            if (const AssetRecord* const asset = find_asset(shell, tag); asset != nullptr) {
                queue_camera_spawn(shell, *asset);
            }
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

void service_editor_shortcuts(ShellState& shell) {
    const ImGuiIO& io = ImGui::GetIO();
    const bool cameraControl = g_cameraControl.load(std::memory_order_acquire);
    int vertical = 0;
    if (cameraControl) {
        if (ImGui::IsKeyDown(ImGuiKey_E)) {
            ++vertical;
        }
        if (ImGui::IsKeyDown(ImGuiKey_Q)) {
            --vertical;
        }
    }
    fly::set_editor_vertical_input(vertical);

    if (cameraControl && io.MouseWheel != 0.0F) {
        movement::Settings settings = movement::get();
        const float prior = settings.flySpeed;
        settings.flySpeed = (std::clamp)(settings.flySpeed + io.MouseWheel * 5.0F,
                                         movement::kMinimumFlySpeed,
                                         movement::kMaximumFlySpeed);
        if (settings.flySpeed != prior && movement::publish(settings)) {
            set_status(shell, "Fly speed %.1f units/s.", static_cast<double>(settings.flySpeed));
        }
    }

    if (cameraControl || io.WantTextInput || shell.gizmoDrag.active) {
        return;
    }
    if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_D, false)) {
        duplicate_selected(shell);
        return;
    }
    if (ImGui::IsKeyPressed(ImGuiKey_Delete, false)) {
        delete_selected(shell);
        return;
    }
    if (ImGui::IsKeyPressed(ImGuiKey_F, false)) {
        focus_selected_actor(shell);
        return;
    }
    if (io.KeyCtrl || io.KeyAlt || io.KeyShift) {
        return;
    }
    if (ImGui::IsKeyPressed(ImGuiKey_W, false)) {
        shell.transformMode = TransformMode::move;
    } else if (ImGui::IsKeyPressed(ImGuiKey_E, false)) {
        shell.transformMode = TransformMode::rotate;
    } else if (ImGui::IsKeyPressed(ImGuiKey_R, false)) {
        shell.transformMode = TransformMode::scale;
    }
}

void draw_right_panels(ShellState& shell) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.025F, 0.03F, 0.033F, 0.97F});
    ImGui::BeginChild("forge_right_stack", {0.0F, 0.0F}, false);
    if (shell.showExplorer && shell.showProperties) {
        ImGui::BeginChild("forge_explorer", {0.0F, ImGui::GetContentRegionAvail().y * 0.56F}, true);
        draw_explorer(shell);
        ImGui::EndChild();
        ImGui::BeginChild("forge_properties", {0.0F, 0.0F}, true);
        draw_properties(shell);
        ImGui::EndChild();
    } else if (shell.showExplorer) {
        ImGui::BeginChild("forge_explorer", {0.0F, 0.0F}, true);
        draw_explorer(shell);
        ImGui::EndChild();
    } else if (shell.showProperties) {
        ImGui::BeginChild("forge_properties", {0.0F, 0.0F}, true);
        draw_properties(shell);
        ImGui::EndChild();
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

void draw_output(ShellState& shell) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.015F, 0.018F, 0.021F, 0.97F});
    ImGui::BeginChild("forge_output",
                      {0.0F, kOutputHeight},
                      true,
                      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    panel_header("OUTPUT");
    ImGui::TextUnformatted(shell.status.data());
    const native_spawn::SpawnObservation observation = native_spawn::last_spawn_observation();
    const std::string_view outcome = native_spawn::spawn_outcome_text(observation.outcome);
    ImGui::Text("Native spawn %llu: %.*s / tag %08X / handle %08X",
                static_cast<unsigned long long>(observation.sequence),
                static_cast<int>(outcome.size()),
                outcome.data(),
                static_cast<unsigned>(observation.tag),
                static_cast<unsigned>(observation.handle));
    ImGui::Text("Map scan: %zu matched / %zu live / %zu ambiguous / %zu unstable",
                shell.worldScan.matchedObjects,
                shell.worldScan.liveHandles,
                shell.worldScan.ambiguousObjects,
                shell.worldScan.unstableObjects);
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

void draw_status_bar(ShellState& shell) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.012F, 0.015F, 0.017F, 0.99F});
    ImGui::BeginChild("forge_status", {0.0F, kStatusHeight}, true);
    ImGui::SetCursorPos({8.0F, 4.0F});
    ImGui::TextUnformatted(shell.status.data());
    ImGui::SameLine(ImGui::GetWindowWidth() - 250.0F);
    const std::size_t liveMapCount = static_cast<std::size_t>(
        std::count_if(shell.actors.begin(), shell.actors.end(), [](const auto& actor) {
            return actor.source == ActorSource::liveMap;
        }));
    const std::size_t authoredMapCount = static_cast<std::size_t>(
        std::count_if(shell.actors.begin(), shell.actors.end(), [](const auto& actor) {
            return actor.source == ActorSource::authoredMap;
        }));
    ImGui::Text("FORGE %zu   LIVE %zu   AUTHORED %zu   REMOVED %zu   QUEUED %zu   NATIVE %s",
                shell.actors.size() - liveMapCount - authoredMapCount,
                liveMapCount,
                authoredMapCount,
                shell.quarantinedActors.size(),
                shell.spawnQueue.size(),
                native_spawn::ready() ? "READY" : "OFFLINE");
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

} // namespace

void draw(workspace::EditorWorkspace& editor) noexcept {
    StyleScope style;
    ShellState& shell = state();
    ensure_asset_metadata(shell);
    if (!shell.catalogScanned) {
        refresh_catalog(shell);
    }
    service_catalog_decode(shell);
    service_catalog_residency(shell);
    if (g_worldRefreshRequested.exchange(false, std::memory_order_acq_rel)) {
        if (shell.catalogReady) {
            refresh_world_objects(shell);
        } else {
            g_worldRefreshRequested.store(true, std::memory_order_release);
        }
    }
    service_actor_lifetimes(shell);
    service_spawn_queue(shell);
    if (editor.session_state() == workspace::SessionState::launcher) {
        (void)editor.open_selected_template();
    }
    draw_top_bar(shell);
    draw_ribbon(shell, editor);

    const float outputHeight = shell.showOutput ? kOutputHeight : 0.0F;
    const float remainingHeight = ImGui::GetContentRegionAvail().y;
    const float followingGaps = ImGui::GetStyle().ItemSpacing.y * (shell.showOutput ? 2.0F : 1.0F);
    const float bodyHeight = (std::max)(remainingHeight - kStatusHeight - outputHeight
                                            - followingGaps - kBodyBottomReserve,
                                        1.0F);
    const float availableWidth = ImGui::GetContentRegionAvail().x;
    const float assetPanelWidth =
        (std::clamp)(availableWidth * 0.15F, kAssetPanelMinimumWidth, kAssetPanelMaximumWidth);
    const float rightPanelWidth =
        (std::clamp)(availableWidth * 0.17F, kRightPanelMinimumWidth, kRightPanelMaximumWidth);
    if (ImGui::BeginTable("forge_body",
                          3,
                          ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInnerV
                              | ImGuiTableFlags_SizingStretchProp,
                          {0.0F, bodyHeight})) {
        ImGui::TableSetupColumn("Assets",
                                shell.showAssetBrowser ? ImGuiTableColumnFlags_WidthFixed
                                                       : ImGuiTableColumnFlags_Disabled,
                                shell.showAssetBrowser ? assetPanelWidth : 0.0F);
        ImGui::TableSetupColumn("Live World", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn(
            "Explorer",
            shell.showExplorer || shell.showProperties ? ImGuiTableColumnFlags_WidthFixed
                                                       : ImGuiTableColumnFlags_Disabled,
            shell.showExplorer || shell.showProperties ? rightPanelWidth : 0.0F);
        ImGui::TableNextRow();
        if (shell.showAssetBrowser) {
            ImGui::TableSetColumnIndex(0);
            draw_asset_browser(shell);
        }
        ImGui::TableSetColumnIndex(1);
        draw_live_viewport(shell);
        if (shell.showExplorer || shell.showProperties) {
            ImGui::TableSetColumnIndex(2);
            draw_right_panels(shell);
        }
        ImGui::EndTable();
    }
    if (shell.showOutput) {
        draw_output(shell);
    }
    service_editor_shortcuts(shell);
    draw_status_bar(shell);
}

bool camera_control_active() noexcept {
    return g_cameraControl.load(std::memory_order_acquire);
}

void release_input() noexcept {
    finish_gizmo_drag(state());
    g_cameraControl.store(false, std::memory_order_release);
    fly::set_editor_vertical_input(0);
    g_worldRefreshRequested.store(true, std::memory_order_release);
}

} // namespace sunrise::izanami::editor::ui::forge_shell
