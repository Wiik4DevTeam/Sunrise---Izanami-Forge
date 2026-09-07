#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

namespace sunrise::client::hooks::spawn {

struct Activation {
    std::uint32_t handle{0xFFFFFFFFU};
    std::array<float, 8> transform{};
    std::uint8_t attempts{};
};

// Caller owns synchronization. Each full datum has at most one pending transform.
template <std::size_t Capacity> class ActivationQueue {
public:
    [[nodiscard]] bool append(std::span<const Activation> requests) noexcept {
        std::size_t added = 0;
        for (std::size_t index = 0; index < requests.size(); ++index) {
            if (find(requests[index].handle) != count_) {
                continue;
            }
            bool duplicate = false;
            for (std::size_t previous = 0; previous < index; ++previous) {
                duplicate |= requests[previous].handle == requests[index].handle;
            }
            added += duplicate ? 0U : 1U;
            if (added > Capacity - count_) {
                return false;
            }
        }
        // Preflight includes replacements: rejecting a batch must leave all older work intact.
        for (const Activation& request : requests) {
            const std::size_t index = find(request.handle);
            if (index == count_) {
                ++count_;
            }
            entries_[index] = request;
        }
        return true;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return count_;
    }
    Activation& operator[](std::size_t index) noexcept {
        return entries_[index];
    }
    const Activation& operator[](std::size_t index) const noexcept {
        return entries_[index];
    }
    void erase(std::size_t index) noexcept {
        entries_[index] = entries_[--count_];
    }
    void clear() noexcept {
        count_ = 0;
    }

private:
    [[nodiscard]] std::size_t find(std::uint32_t handle) const noexcept {
        for (std::size_t index = 0; index < count_; ++index) {
            if (entries_[index].handle == handle) {
                return index;
            }
        }
        return count_;
    }

    std::array<Activation, Capacity> entries_{};
    std::size_t count_{};
};

} // namespace sunrise::client::hooks::spawn
