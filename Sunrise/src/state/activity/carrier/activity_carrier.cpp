#include "activity_carrier.h"

#include <Windows.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <string>

namespace sunrise::state::activity::carrier {
namespace {

SRWLOCK g_lock = SRWLOCK_INIT;
NativeCarrier g_carrier{};
bool g_loaded{};
constexpr std::string_view kMagic = "IZANAMI_NATIVE_CARRIER";
constexpr std::uint32_t kVersion = 1;
int g_moduleAnchor{};

struct ExecutableFingerprint final {
    std::uint64_t size{};
    std::uint64_t writeTime{};
};

[[nodiscard]] bool valid(const NativeCarrier& value) noexcept {
    return value.activityIndex > 0 && value.activityIndex <= destination::kMaximumActivityIndex
           && value.packageNameLength != 0 && value.packageNameLength <= value.packageName.size();
}

[[nodiscard]] bool executable_fingerprint(ExecutableFingerprint& output) noexcept {
    std::wstring path(32768, L'\0');
    const DWORD length = GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
    if (length == 0 || length >= path.size()) {
        return false;
    }
    path.resize(length);
    WIN32_FILE_ATTRIBUTE_DATA attributes{};
    if (GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &attributes) == FALSE) {
        return false;
    }
    output.size =
        (static_cast<std::uint64_t>(attributes.nFileSizeHigh) << 32U) | attributes.nFileSizeLow;
    output.writeTime =
        (static_cast<std::uint64_t>(attributes.ftLastWriteTime.dwHighDateTime) << 32U)
        | attributes.ftLastWriteTime.dwLowDateTime;
    return output.size != 0 && output.writeTime != 0;
}

[[nodiscard]] bool carrier_path(std::filesystem::path& output) noexcept {
    HMODULE module = nullptr;
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                               | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           reinterpret_cast<LPCWSTR>(&g_moduleAnchor),
                           &module)
            == FALSE
        || module == nullptr) {
        return false;
    }
    std::wstring path(32768, L'\0');
    const DWORD length = GetModuleFileNameW(module, path.data(), static_cast<DWORD>(path.size()));
    if (length == 0 || length >= path.size()) {
        return false;
    }
    path.resize(length);
    output =
        std::filesystem::path{path}.parent_path() / L"izanami" / L"carrier" / L"native_carrier.txt";
    return true;
}

[[nodiscard]] bool write_persisted(const NativeCarrier& value) noexcept {
    try {
        ExecutableFingerprint fingerprint{};
        std::filesystem::path path;
        if (!executable_fingerprint(fingerprint) || !carrier_path(path)) {
            return false;
        }
        std::filesystem::create_directories(path.parent_path());
        const std::filesystem::path temporary = path.wstring() + L".tmp";
        std::ofstream stream(temporary, std::ios::binary | std::ios::trunc);
        if (!stream) {
            return false;
        }
        const std::string_view name(value.packageName.data(), value.packageNameLength);
        stream << kMagic << ' ' << kVersion << '\n';
        stream << "exe " << fingerprint.size << ' ' << fingerprint.writeTime << '\n';
        stream << "carrier " << value.activityIndex << ' ' << std::quoted(std::string{name})
               << '\n';
        stream.flush();
        stream.close();
        if (!stream
            || MoveFileExW(temporary.c_str(),
                           path.c_str(),
                           MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)
                   == FALSE) {
            std::filesystem::remove(temporary);
            return false;
        }
        return true;
    } catch (...) {
        return false;
    }
}

[[nodiscard]] bool read_persisted(NativeCarrier& output) noexcept {
    try {
        ExecutableFingerprint current{};
        std::filesystem::path path;
        if (!executable_fingerprint(current) || !carrier_path(path)
            || !std::filesystem::exists(path)) {
            return false;
        }
        std::ifstream stream(path, std::ios::binary);
        std::string magic;
        std::uint32_t version = 0;
        std::string keyword;
        ExecutableFingerprint stored{};
        NativeCarrier candidate{};
        std::string name;
        if (!(stream >> magic >> version) || magic != kMagic || version != kVersion
            || !(stream >> keyword >> stored.size >> stored.writeTime) || keyword != "exe"
            || !(stream >> keyword >> candidate.activityIndex >> std::quoted(name))
            || keyword != "carrier" || name.empty() || name.size() > candidate.packageName.size()
            || stored.size != current.size || stored.writeTime != current.writeTime) {
            return false;
        }
        std::copy(name.begin(), name.end(), candidate.packageName.begin());
        candidate.packageNameLength = static_cast<std::uint8_t>(name.size());
        if (!valid(candidate)) {
            return false;
        }
        output = candidate;
        return true;
    } catch (...) {
        return false;
    }
}

} // namespace

bool publish(std::string_view packageName, std::int16_t activityIndex) noexcept {
    if (packageName.empty() || packageName.size() > destination::kPackageNameCapacity
        || activityIndex <= 0 || activityIndex > destination::kMaximumActivityIndex) {
        return false;
    }

    NativeCarrier candidate{};
    std::copy(packageName.begin(), packageName.end(), candidate.packageName.begin());
    candidate.packageNameLength = static_cast<std::uint8_t>(packageName.size());
    candidate.activityIndex = activityIndex;

    AcquireSRWLockExclusive(&g_lock);
    g_carrier = candidate;
    g_loaded = true;
    ReleaseSRWLockExclusive(&g_lock);
    (void)write_persisted(candidate);
    return true;
}

bool snapshot(NativeCarrier& output) noexcept {
    AcquireSRWLockExclusive(&g_lock);
    if (!g_loaded) {
        g_loaded = true;
        (void)read_persisted(g_carrier);
    }
    output = g_carrier;
    ReleaseSRWLockExclusive(&g_lock);
    return valid(output);
}

void clear() noexcept {
    AcquireSRWLockExclusive(&g_lock);
    g_carrier = {};
    g_loaded = true;
    ReleaseSRWLockExclusive(&g_lock);
}

} // namespace sunrise::state::activity::carrier
