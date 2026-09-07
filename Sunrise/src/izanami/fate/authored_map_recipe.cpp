#include "authored_map_recipe.h"

#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <unordered_set>

namespace sunrise::izanami::fate::authored_map_recipe {
namespace {

constexpr std::string_view kMagic = "IZANAMI_AUTHORED_MAP";
constexpr std::string_view kPandoraMapRoot = "map:pandora:root";
constexpr std::size_t kMaximumEdits = 4096;
constexpr std::size_t kMaximumRootBytes = 160;
int g_moduleAnchor{};

[[nodiscard]] bool valid_instruction(const Instruction& edit) noexcept {
    return edit.binding.is_valid() && edit.entityTag != 0 && edit.targetTransform.is_finite()
           && edit.targetTransform.uniformScale > 0.0F;
}

[[nodiscard]] bool valid_recipe(const Recipe& recipe) {
    if (recipe.mapRoot.empty() || recipe.mapRoot.size() > kMaximumRootBytes
        || recipe.edits.size() > kMaximumEdits) {
        return false;
    }
    std::unordered_set<std::uint64_t> records{};
    records.reserve(recipe.edits.size());
    for (const Instruction& edit : recipe.edits) {
        const std::uint64_t record =
            static_cast<std::uint64_t>(edit.binding.tableTag) << 32U | edit.binding.entryIndex;
        if (!valid_instruction(edit) || !records.insert(record).second) {
            return false;
        }
    }
    return true;
}

void write_transform(std::ostream& stream, const core::Transform& transform) {
    stream << transform.translation.x << ' ' << transform.translation.y << ' '
           << transform.translation.z << ' ' << transform.rotation.x << ' ' << transform.rotation.y
           << ' ' << transform.rotation.z << ' ' << transform.rotation.w << ' '
           << transform.uniformScale;
}

[[nodiscard]] bool read_transform(std::istream& stream, core::Transform& transform) {
    return static_cast<bool>(stream >> transform.translation.x >> transform.translation.y
                             >> transform.translation.z >> transform.rotation.x
                             >> transform.rotation.y >> transform.rotation.z >> transform.rotation.w
                             >> transform.uniformScale)
           && transform.is_finite() && transform.uniformScale > 0.0F;
}

} // namespace

bool default_path(std::string_view mapRoot, std::wstring& output) noexcept {
    output.clear();
    if (mapRoot != kPandoraMapRoot) {
        return false;
    }
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
        const std::filesystem::path directory =
            std::filesystem::path{modulePath}.parent_path() / L"izanami" / L"projects";
        std::filesystem::create_directories(directory);
        output = (directory / L"authored_pandora.fate").wstring();
        return true;
    } catch (...) {
        output.clear();
        return false;
    }
}

recipe::IoResult save(std::wstring_view path,
                      std::string_view mapRoot,
                      std::span<const Instruction> edits) noexcept {
    recipe::IoResult result{};
    try {
        Recipe staged{};
        staged.mapRoot = mapRoot;
        staged.edits.assign(edits.begin(), edits.end());
        if (!valid_recipe(staged)) {
            result.message = "Authored-map recipe validation failed; nothing was written.";
            return result;
        }

        const std::filesystem::path filePath{path};
        std::filesystem::create_directories(filePath.parent_path());
        std::filesystem::path temporary = filePath;
        temporary += L".tmp";
        std::ofstream stream(temporary, std::ios::binary | std::ios::trunc);
        if (!stream) {
            result.message = "Authored-map recipe could not be opened for writing.";
            return result;
        }
        stream << kMagic << ' ' << kFormatVersion << '\n';
        stream << "root " << std::quoted(staged.mapRoot) << '\n';
        stream << std::setprecision(std::numeric_limits<float>::max_digits10);
        for (const Instruction& edit : staged.edits) {
            stream << "edit " << std::hex << std::uppercase << edit.binding.tableTag << ' '
                   << std::dec << edit.binding.entryIndex << ' ' << std::hex
                   << edit.binding.parentTag << ' ' << edit.entityTag << ' ' << edit.resourceClass
                   << ' ' << edit.resourceTag << std::dec << ' ';
            write_transform(stream, edit.binding.sourceTransform);
            stream << ' ';
            write_transform(stream, edit.targetTransform);
            stream << ' ' << (edit.hidden ? 1 : 0) << '\n';
        }
        stream.flush();
        stream.close();
        if (!stream
            || !MoveFileExW(temporary.c_str(),
                            filePath.c_str(),
                            MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
            std::error_code ignored{};
            std::filesystem::remove(temporary, ignored);
            result.message = "Authored-map recipe did not commit atomically.";
            return result;
        }
        result.succeeded = true;
        result.instructionCount = staged.edits.size();
        result.message = "Authored-map recipe saved.";
        return result;
    } catch (...) {
        result.message = "Authored-map recipe failed with a filesystem error.";
        return result;
    }
}

recipe::IoResult load(std::wstring_view path, Recipe& output) noexcept {
    output = {};
    recipe::IoResult result{};
    try {
        std::ifstream stream(std::filesystem::path{path}, std::ios::binary);
        if (!stream) {
            result.succeeded = true;
            result.message = "No authored-map edits have been saved yet.";
            return result;
        }
        std::string magic{};
        std::uint32_t version = 0;
        if (!(stream >> magic >> version) || magic != kMagic || version != kFormatVersion) {
            result.message = "Authored-map recipe has an unsupported header.";
            return result;
        }
        std::string keyword{};
        if (!(stream >> keyword >> std::quoted(output.mapRoot)) || keyword != "root") {
            result.message = "Authored-map recipe is missing its map root.";
            output = {};
            return result;
        }
        while (stream >> keyword) {
            if (keyword != "edit" || output.edits.size() >= kMaximumEdits) {
                result.message = "Authored-map recipe contains an invalid instruction.";
                output = {};
                return result;
            }
            Instruction edit{};
            unsigned hidden = 0;
            if (!(stream >> std::hex >> edit.binding.tableTag >> std::dec >> edit.binding.entryIndex
                  >> std::hex >> edit.binding.parentTag >> edit.entityTag >> edit.resourceClass
                  >> edit.resourceTag >> std::dec)
                || !read_transform(stream, edit.binding.sourceTransform)
                || !read_transform(stream, edit.targetTransform) || !(stream >> hidden)
                || hidden > 1) {
                result.message = "Authored-map recipe contains malformed edit data.";
                output = {};
                return result;
            }
            edit.hidden = hidden != 0;
            output.edits.push_back(edit);
        }
        if (!stream.eof() || !valid_recipe(output)) {
            result.message = "Authored-map recipe failed structural validation.";
            output = {};
            return result;
        }
        result.succeeded = true;
        result.instructionCount = output.edits.size();
        result.message = "Authored-map recipe loaded.";
        return result;
    } catch (...) {
        output = {};
        result.message = "Authored-map recipe failed with a filesystem error.";
        return result;
    }
}

} // namespace sunrise::izanami::fate::authored_map_recipe
