#include "map_recipe.h"

#include <Windows.h>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <unordered_set>

namespace sunrise::izanami::fate::recipe {
namespace {

constexpr std::string_view kMagic = "IZANAMI_FATE_MAP";
constexpr std::size_t kMaximumActors = 8192;
constexpr std::size_t kMaximumNameBytes = 160;
int g_moduleAnchor{};

[[nodiscard]] bool valid_actor(const ActorInstruction& actor) noexcept {
    return actor.editorId != 0 && actor.parentId != actor.editorId && actor.tag != 0
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
    std::unordered_set<std::uint64_t> ids;
    ids.reserve(recipe.actors.size());
    for (const ActorInstruction& actor : recipe.actors) {
        if (!valid_actor(actor) || !ids.insert(actor.editorId).second) {
            return false;
        }
    }
    for (const ActorInstruction& actor : recipe.actors) {
        if (actor.parentId != 0 && !ids.contains(actor.parentId)) {
            return false;
        }
        std::uint64_t parent = actor.parentId;
        for (std::size_t depth = 0; parent != 0 && depth <= recipe.actors.size(); ++depth) {
            if (parent == actor.editorId) {
                return false;
            }
            const auto found = std::find_if(recipe.actors.begin(),
                                            recipe.actors.end(),
                                            [parent](const ActorInstruction& candidate) {
                                                return candidate.editorId == parent;
                                            });
            if (found == recipe.actors.end()) {
                return false;
            }
            parent = found->parentId;
        }
        if (parent != 0) {
            return false;
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
        std::filesystem::create_directories(filePath.parent_path());
        std::ofstream stream(filePath, std::ios::binary | std::ios::trunc);
        if (!stream) {
            result.message = "Quick-save recipe could not be opened for writing.";
            return result;
        }
        stream << kMagic << ' ' << kFormatVersion << '\n';
        stream << "scene " << std::quoted(recipe.name) << '\n';
        stream << std::setprecision(std::numeric_limits<float>::max_digits10);
        for (const ActorInstruction& actor : recipe.actors) {
            stream << "actor " << actor.editorId << ' ' << actor.parentId << ' '
                   << std::quoted(actor.name) << ' ' << std::hex << std::uppercase << actor.tag
                   << std::dec << ' ' << static_cast<unsigned>(actor.objectType) << ' '
                   << actor.transform.translation.x << ' ' << actor.transform.translation.y << ' '
                   << actor.transform.translation.z << ' ' << actor.transform.rotation.x << ' '
                   << actor.transform.rotation.y << ' ' << actor.transform.rotation.z << ' '
                   << actor.transform.rotation.w << ' ' << actor.transform.uniformScale << '\n';
        }
        stream.flush();
        if (!stream) {
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
        if (!(stream >> magic >> version) || magic != kMagic || version != kFormatVersion) {
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
            if (keyword != "actor" || output.actors.size() >= kMaximumActors) {
                result.message = "Quick-save recipe contains an invalid instruction.";
                output = {};
                return result;
            }
            ActorInstruction actor{};
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
