#include "asset_metadata_store.h"

#include <Windows.h>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <string_view>
#include <unordered_set>

#include "../../../core/filesystem/path.h"

namespace sunrise::izanami::editor::ui::asset_metadata {
namespace {

constexpr std::string_view kMagic = "IZANAMI_ASSET_METADATA";
constexpr unsigned kFormatVersion = 1;
constexpr std::size_t kMaximumEntries = 65536;
constexpr std::size_t kMaximumNameBytes = 96;
constexpr std::wstring_view kFileSuffix = L"\\asset_metadata.forge";
int g_moduleAnchor{};

[[nodiscard]] bool resolve_path(std::filesystem::path& output) noexcept {
    HMODULE module = nullptr;
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                               | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           reinterpret_cast<LPCWSTR>(&g_moduleAnchor),
                           &module)
            == FALSE
        || module == nullptr) {
        return false;
    }
    core::path::Buffer path{};
    if (!core::path::artifact_directory(module, path) || !core::path::append(path, kFileSuffix)) {
        return false;
    }
    output = path.chars.data();
    return true;
}

[[nodiscard]] bool valid_name(std::string_view name) noexcept {
    return name.size() <= kMaximumNameBytes && std::none_of(name.begin(), name.end(), [](char ch) {
               return ch == '\r' || ch == '\n' || ch == '\t' || ch == '\0';
           });
}

[[nodiscard]] bool valid_color(const std::array<float, 3>& color) noexcept {
    return std::all_of(color.begin(), color.end(), [](float channel) {
        return std::isfinite(channel) && channel >= 0.0F && channel <= 1.0F;
    });
}

[[nodiscard]] bool valid_entry(const Entry& entry) noexcept {
    return entry.tag != 0 && valid_name(entry.name)
           && (!entry.hasCustomColor || valid_color(entry.color));
}

} // namespace

bool load(std::vector<Entry>& output, std::string& message) noexcept {
    output.clear();
    try {
        std::filesystem::path path;
        if (!resolve_path(path)) {
            message = "Asset metadata path could not be resolved.";
            return false;
        }
        if (!std::filesystem::exists(path)) {
            message = "Asset metadata ready; no saved labels yet.";
            return true;
        }
        std::ifstream stream(path, std::ios::binary);
        std::string magic;
        unsigned version = 0;
        if (!(stream >> magic >> version) || magic != kMagic || version != kFormatVersion) {
            message = "Asset metadata header is invalid.";
            return false;
        }
        std::unordered_set<std::uint32_t> tags;
        std::string kind;
        while (stream >> kind) {
            Entry entry{};
            unsigned customColor = 0;
            if (kind != "asset"
                || !(stream >> std::hex >> entry.tag >> std::dec >> std::quoted(entry.name)
                     >> customColor >> entry.color[0] >> entry.color[1] >> entry.color[2])
                || customColor > 1) {
                output.clear();
                message = "Asset metadata contains an invalid entry.";
                return false;
            }
            entry.hasCustomColor = customColor != 0;
            if (!valid_entry(entry) || !tags.insert(entry.tag).second
                || output.size() >= kMaximumEntries) {
                output.clear();
                message = "Asset metadata contains an invalid entry.";
                return false;
            }
            if (!entry.name.empty() || entry.hasCustomColor) {
                output.push_back(std::move(entry));
            }
        }
        if (!stream.eof()) {
            output.clear();
            message = "Asset metadata could not be read completely.";
            return false;
        }
        message = "Persistent asset metadata loaded.";
        return true;
    } catch (...) {
        output.clear();
        message = "Asset metadata load failed with a filesystem error.";
        return false;
    }
}

bool save(std::span<const Entry> entries, std::string& message) noexcept {
    if (entries.size() > kMaximumEntries
        || std::any_of(entries.begin(), entries.end(), [](const Entry& entry) {
               return !valid_entry(entry);
           })) {
        message = "Asset metadata validation failed; nothing was written.";
        return false;
    }
    try {
        std::filesystem::path path;
        if (!resolve_path(path)) {
            message = "Asset metadata path could not be resolved.";
            return false;
        }
        const std::filesystem::path temporary = path.wstring() + L".tmp";
        std::ofstream stream(temporary, std::ios::binary | std::ios::trunc);
        if (!stream) {
            message = "Asset metadata temporary file could not be opened.";
            return false;
        }
        stream << kMagic << ' ' << kFormatVersion << '\n' << std::setprecision(9);
        for (const Entry& entry : entries) {
            if (entry.name.empty() && !entry.hasCustomColor) {
                continue;
            }
            stream << "asset " << std::hex << std::uppercase << entry.tag << std::dec << ' '
                   << std::quoted(entry.name) << ' ' << (entry.hasCustomColor ? 1 : 0) << ' '
                   << entry.color[0] << ' ' << entry.color[1] << ' ' << entry.color[2] << '\n';
        }
        stream.flush();
        if (!stream) {
            stream.close();
            std::filesystem::remove(temporary);
            message = "Asset metadata write did not complete.";
            return false;
        }
        stream.close();
        if (MoveFileExW(
                temporary.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)
            == FALSE) {
            std::filesystem::remove(temporary);
            message = "Asset metadata could not replace the previous file.";
            return false;
        }
        message = "Asset metadata saved.";
        return true;
    } catch (...) {
        message = "Asset metadata save failed with a filesystem error.";
        return false;
    }
}

} // namespace sunrise::izanami::editor::ui::asset_metadata
