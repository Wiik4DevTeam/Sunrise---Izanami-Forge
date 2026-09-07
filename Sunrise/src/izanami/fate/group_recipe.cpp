#include "group_recipe.h"

#include <Windows.h>

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <unordered_set>

namespace sunrise::izanami::fate::group_recipe {
namespace {

constexpr std::string_view kMagic = "IZANAMI_FATE_GROUP";
constexpr std::size_t kMaximumActors = 1024;
constexpr std::size_t kMaximumNameBytes = 160;
constexpr std::wstring_view kExtension = L".fategroup";
int g_moduleAnchor{};

[[nodiscard]] bool group_directory(std::filesystem::path& output) noexcept {
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
    output = std::filesystem::path{modulePath}.parent_path() / L"izanami" / L"groups";
    return true;
}

[[nodiscard]] std::string clean_name(std::string_view value) {
    std::string result{value.substr(0, kMaximumNameBytes)};
    std::replace_if(
        result.begin(),
        result.end(),
        [](char ch) { return ch == '\r' || ch == '\n' || ch == '\t'; },
        ' ');
    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result.empty() ? std::string{"Combined Asset"} : result;
}

[[nodiscard]] std::wstring file_stem(std::string_view name) {
    std::wstring result;
    result.reserve(name.size());
    for (const unsigned char ch : name) {
        if (std::isalnum(ch) != 0) {
            result.push_back(static_cast<wchar_t>(std::tolower(ch)));
        } else if (!result.empty() && result.back() != L'_') {
            result.push_back(L'_');
        }
    }
    while (!result.empty() && result.back() == L'_') {
        result.pop_back();
    }
    return result.empty() ? std::wstring{L"combined_asset"} : result;
}

[[nodiscard]] bool valid_actor(const recipe::ActorInstruction& actor) noexcept {
    return actor.editorId != 0 && actor.parentId != actor.editorId && actor.tag != 0
           && actor.name.size() <= kMaximumNameBytes && actor.transform.is_finite()
           && actor.transform.uniformScale > 0.0F;
}

[[nodiscard]] bool valid_actors(std::span<const recipe::ActorInstruction> actors) {
    if (actors.empty() || actors.size() > kMaximumActors) {
        return false;
    }
    std::unordered_set<std::uint64_t> ids;
    ids.reserve(actors.size());
    for (const auto& actor : actors) {
        if (!valid_actor(actor) || !ids.insert(actor.editorId).second) {
            return false;
        }
    }
    for (const auto& actor : actors) {
        if (actor.parentId != 0 && !ids.contains(actor.parentId)) {
            return false;
        }
        std::uint64_t parent = actor.parentId;
        for (std::size_t depth = 0; parent != 0 && depth <= actors.size(); ++depth) {
            const auto found =
                std::find_if(actors.begin(), actors.end(), [parent](const auto& row) {
                    return row.editorId == parent;
                });
            if (found == actors.end() || found->editorId == actor.editorId) {
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

void write_actor(std::ostream& stream, const recipe::ActorInstruction& actor) {
    stream << "actor " << actor.editorId << ' ' << actor.parentId << ' '
           << std::quoted(clean_name(actor.name)) << ' ' << std::hex << std::uppercase << actor.tag
           << std::dec << ' ' << static_cast<unsigned>(actor.objectType) << ' '
           << actor.transform.translation.x << ' ' << actor.transform.translation.y << ' '
           << actor.transform.translation.z << ' ' << actor.transform.rotation.x << ' '
           << actor.transform.rotation.y << ' ' << actor.transform.rotation.z << ' '
           << actor.transform.rotation.w << ' ' << actor.transform.uniformScale << '\n';
}

[[nodiscard]] bool read_group(const std::filesystem::path& path, GroupAsset& output) {
    output = {};
    std::ifstream stream(path, std::ios::binary);
    std::string magic;
    std::uint32_t version = 0;
    if (!(stream >> magic >> version) || magic != kMagic || version != kFormatVersion) {
        return false;
    }
    std::string keyword;
    if (!(stream >> keyword >> std::quoted(output.name)) || keyword != "group"
        || output.name.empty() || output.name.size() > kMaximumNameBytes) {
        return false;
    }
    while (stream >> keyword) {
        if (keyword != "actor" || output.actors.size() >= kMaximumActors) {
            return false;
        }
        recipe::ActorInstruction actor{};
        unsigned type = 0;
        if (!(stream >> actor.editorId >> actor.parentId >> std::quoted(actor.name) >> std::hex
              >> actor.tag >> std::dec >> type >> actor.transform.translation.x
              >> actor.transform.translation.y >> actor.transform.translation.z
              >> actor.transform.rotation.x >> actor.transform.rotation.y
              >> actor.transform.rotation.z >> actor.transform.rotation.w
              >> actor.transform.uniformScale)
            || type > (std::numeric_limits<std::uint8_t>::max)()) {
            return false;
        }
        actor.objectType = static_cast<std::uint8_t>(type);
        output.actors.push_back(std::move(actor));
    }
    if (!stream.eof() || !valid_actors(output.actors)) {
        return false;
    }
    output.path = path.wstring();
    return true;
}

} // namespace

recipe::IoResult save(std::string_view name,
                      std::span<const recipe::ActorInstruction> actors) noexcept {
    recipe::IoResult result{};
    try {
        const std::string groupName = clean_name(name);
        if (!valid_actors(actors)) {
            result.message = "Group asset validation failed; select live Forge objects first.";
            return result;
        }
        std::filesystem::path directory;
        if (!group_directory(directory)) {
            result.message = "Group asset directory could not be resolved.";
            return result;
        }
        std::filesystem::create_directories(directory);
        const std::filesystem::path path = directory / (file_stem(groupName) + kExtension.data());
        const std::filesystem::path temporary = path.wstring() + L".tmp";
        std::ofstream stream(temporary, std::ios::binary | std::ios::trunc);
        if (!stream) {
            result.message = "Group asset temporary file could not be opened.";
            return result;
        }
        stream << kMagic << ' ' << kFormatVersion << '\n';
        stream << "group " << std::quoted(groupName) << '\n';
        stream << std::setprecision(std::numeric_limits<float>::max_digits10);
        for (const auto& actor : actors) {
            write_actor(stream, actor);
        }
        stream.flush();
        stream.close();
        if (!stream
            || MoveFileExW(temporary.c_str(),
                           path.c_str(),
                           MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)
                   == FALSE) {
            std::filesystem::remove(temporary);
            result.message = "Group asset write did not complete.";
            return result;
        }
        result.succeeded = true;
        result.instructionCount = actors.size();
        result.message = "Persistent group asset saved.";
    } catch (...) {
        result.message = "Group asset save failed with a filesystem error.";
    }
    return result;
}

recipe::IoResult load_all(std::vector<GroupAsset>& output) noexcept {
    output.clear();
    recipe::IoResult result{};
    try {
        std::filesystem::path directory;
        if (!group_directory(directory)) {
            result.message = "Group asset directory could not be resolved.";
            return result;
        }
        if (!std::filesystem::exists(directory)) {
            std::filesystem::create_directories(directory);
            result.succeeded = true;
            result.message = "Group asset library ready.";
            return result;
        }
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (!entry.is_regular_file() || entry.path().extension() != kExtension) {
                continue;
            }
            GroupAsset group;
            if (read_group(entry.path(), group)) {
                result.instructionCount += group.actors.size();
                output.push_back(std::move(group));
            }
        }
        std::sort(output.begin(), output.end(), [](const auto& left, const auto& right) {
            return left.name < right.name;
        });
        result.succeeded = true;
        result.message = "Persistent group asset library loaded.";
    } catch (...) {
        output.clear();
        result.message = "Group asset library load failed with a filesystem error.";
    }
    return result;
}

} // namespace sunrise::izanami::fate::group_recipe
