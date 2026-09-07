#include "map_recipe.h"

#include <Windows.h>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <unordered_map>

namespace sunrise::izanami::fate::recipe {
namespace {

constexpr std::string_view kMagic = "IZANAMI_FATE_MAP";
constexpr std::size_t kMaximumActors = 8192;
constexpr std::size_t kMaximumNameBytes = 160;
int g_moduleAnchor{};

[[nodiscard]] bool valid_actor(const ActorInstruction& actor) noexcept {
    return actor.editorId != 0 && actor.parentId != actor.editorId
           && (actor.virtualGroup ? actor.tag == 0 && actor.objectType == 0 : actor.tag != 0)
           && actor.name.size() <= kMaximumNameBytes && actor.transform.is_finite()
           && actor.transform.uniformScale > 0.0F;
}

[[nodiscard]] std::string clean_name(std::string_view value) {
    std::string result{value.substr(0, kMaximumNameBytes)};
    std::replace_if(
        result.begin(),
        result.end(),
        [](char ch) { return ch == '\r' || ch == '\n' || ch == '\t'; },
        ' ');
    return result.empty() ? std::string{"Unnamed Asset"} : result;
}

[[nodiscard]] bool validate_recipe(const MapRecipe& recipe) {
    if (recipe.name.empty() || recipe.name.size() > kMaximumNameBytes
        || recipe.actors.size() > kMaximumActors) {
        return false;
    }
    std::unordered_map<std::uint64_t, std::size_t> ids;
    ids.reserve(recipe.actors.size());
    for (std::size_t index = 0; index < recipe.actors.size(); ++index) {
        const ActorInstruction& actor = recipe.actors[index];
        if (!valid_actor(actor) || !ids.emplace(actor.editorId, index).second) {
            return false;
        }
    }
    // Walk each parent edge at most twice; grey nodes detect cycles without recursive depth limits.
    std::vector<std::uint8_t> colors(recipe.actors.size());
    for (const ActorInstruction& actor : recipe.actors) {
        std::uint64_t current = actor.editorId;
        while (current != 0) {
            const auto found = ids.find(current);
            if (found == ids.end() || colors[found->second] == 1) {
                return false;
            }
            if (colors[found->second] == 2) {
                break;
            }
            colors[found->second] = 1;
            current = recipe.actors[found->second].parentId;
        }
        current = actor.editorId;
        while (current != 0) {
            const std::size_t index = ids.at(current);
            if (colors[index] == 2) {
                break;
            }
            colors[index] = 2;
            current = recipe.actors[index].parentId;
        }
    }
    return true;
}

} // namespace

bool default_path(std::wstring& output) noexcept {
    output.clear();
    HMODULE module = nullptr;
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                               | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           reinterpret_cast<LPCWSTR>(&g_moduleAnchor),
                           &module)
            == FALSE
        || module == nullptr) {
        return false;
    }
    std::wstring modulePath(32768, L'\0');
    const DWORD length =
        GetModuleFileNameW(module, modulePath.data(), static_cast<DWORD>(modulePath.size()));
    if (length == 0 || length >= modulePath.size()) {
        return false;
    }
    modulePath.resize(length);
    try {
        std::filesystem::path directory =
            std::filesystem::path{modulePath}.parent_path() / L"izanami" / L"projects";
        std::filesystem::create_directories(directory);
        output = (directory / L"quick_save.fate").wstring();
        return true;
    } catch (...) {
        output.clear();
        return false;
    }
}

IoResult save(std::wstring_view path,
              std::string_view sceneName,
              std::span<const ActorInstruction> actors) noexcept {
    IoResult result{};
    try {
        MapRecipe recipe;
        recipe.name = clean_name(sceneName);
        recipe.actors.assign(actors.begin(), actors.end());
        for (ActorInstruction& actor : recipe.actors) {
            actor.name = clean_name(actor.name);
        }
        if (!validate_recipe(recipe)) {
            result.message = "Recipe validation failed; nothing was written.";
            return result;
        }
        const std::filesystem::path filePath{path};
        if (!filePath.parent_path().empty()) {
            std::filesystem::create_directories(filePath.parent_path());
        }
        const std::filesystem::path temporary = filePath.wstring() + L".tmp";
        std::ofstream stream(temporary, std::ios::binary | std::ios::trunc);
        if (!stream) {
            result.message = "Quick-save recipe could not be opened for writing.";
            return result;
        }
        stream << kMagic << ' ' << kFormatVersion << '\n';
        stream << "scene " << std::quoted(recipe.name) << '\n';
        stream << std::setprecision(std::numeric_limits<float>::max_digits10);
        for (const ActorInstruction& actor : recipe.actors) {
            stream << (actor.virtualGroup ? "group " : "actor ") << actor.editorId << ' '
                   << actor.parentId << ' ' << std::quoted(actor.name) << ' ' << std::hex
                   << std::uppercase << actor.tag << std::dec << ' '
                   << static_cast<unsigned>(actor.objectType) << ' '
                   << actor.transform.translation.x << ' ' << actor.transform.translation.y << ' '
                   << actor.transform.translation.z << ' ' << actor.transform.rotation.x << ' '
                   << actor.transform.rotation.y << ' ' << actor.transform.rotation.z << ' '
                   << actor.transform.rotation.w << ' ' << actor.transform.uniformScale << '\n';
        }
        stream.flush();
        stream.close();
        if (!stream
            || MoveFileExW(temporary.c_str(),
                           filePath.c_str(),
                           MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)
                   == FALSE) {
            std::error_code ignored;
            std::filesystem::remove(temporary, ignored);
            result.message = "Quick-save recipe write did not complete.";
            return result;
        }
        result.succeeded = true;
        result.instructionCount = recipe.actors.size();
        result.message = "Fate quick-save recipe written.";
        return result;
    } catch (...) {
        result.message = "Quick-save recipe failed with a filesystem error.";
        return result;
    }
}

IoResult load(std::wstring_view path, MapRecipe& output) noexcept {
    output = {};
    IoResult result{};
    try {
        std::ifstream stream(std::filesystem::path{path}, std::ios::binary);
        if (!stream) {
            result.message = "No Fate quick-save recipe exists yet.";
            return result;
        }
        std::string magic;
        std::uint32_t version = 0;
        if (!(stream >> magic >> version) || magic != kMagic
            || (version != 1 && version != kFormatVersion)) {
            result.message = "Quick-save recipe has an unsupported header.";
            return result;
        }
        std::string keyword;
        if (!(stream >> keyword >> std::quoted(output.name)) || keyword != "scene") {
            result.message = "Quick-save recipe is missing its scene declaration.";
            output = {};
            return result;
        }
        while (stream >> keyword) {
            const bool isGroup = version >= 2 && keyword == "group";
            if ((keyword != "actor" && !isGroup) || output.actors.size() >= kMaximumActors) {
                result.message = "Quick-save recipe contains an invalid instruction.";
                output = {};
                return result;
            }
            ActorInstruction actor{};
            actor.virtualGroup = isGroup;
            unsigned type = 0;
            if (!(stream >> actor.editorId >> actor.parentId >> std::quoted(actor.name) >> std::hex
                  >> actor.tag >> std::dec >> type >> actor.transform.translation.x
                  >> actor.transform.translation.y >> actor.transform.translation.z
                  >> actor.transform.rotation.x >> actor.transform.rotation.y
                  >> actor.transform.rotation.z >> actor.transform.rotation.w
                  >> actor.transform.uniformScale)
                || type > (std::numeric_limits<std::uint8_t>::max)()) {
                result.message = "Quick-save recipe contains malformed actor data.";
                output = {};
                return result;
            }
            actor.objectType = static_cast<std::uint8_t>(type);
            output.actors.push_back(std::move(actor));
        }
        if (!stream.eof() || !validate_recipe(output)) {
            result.message = "Quick-save recipe failed structural validation.";
            output = {};
            return result;
        }
        result.succeeded = true;
        result.instructionCount = output.actors.size();
        result.message = "Fate quick-save recipe loaded for replay.";
        return result;
    } catch (...) {
        output = {};
        result.message = "Quick-save recipe failed with a filesystem error.";
        return result;
    }
}

} // namespace sunrise::izanami::fate::recipe
