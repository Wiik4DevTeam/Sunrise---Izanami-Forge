#include <array>
#include <cassert>
#include <cstdio>

#include "client/hooks/spawn/activation_queue.h"

using sunrise::client::hooks::spawn::Activation;
using sunrise::client::hooks::spawn::ActivationQueue;

static Activation move(std::uint32_t handle, float x) {
    Activation result{};
    result.handle = handle;
    result.transform[3] = 1.0F;
    result.transform[4] = x;
    result.transform[7] = 1.0F;
    return result;
}

int main() {
    ActivationQueue<3> queue;
    // The old swap/pop drain could apply positions 1, 3, 2 for one drag.
    for (int index = 1; index <= 100; ++index) {
        const Activation request = move(0x12342000, static_cast<float>(index));
        assert(queue.append(std::span(&request, 1)));
    }
    assert(queue.size() == 1);
    assert(queue[0].transform[4] == 100.0F);

    // Salt/generation bits matter: equal low datum indices must not merge two handles.
    const std::array fill{move(0x56782000, 7.0F), move(0x12342001, 8.0F)};
    assert(queue.append(fill));
    assert(queue.size() == 3);
    const std::array rejected{move(0x12342000, 200.0F), move(0x12342002, 9.0F)};
    assert(!queue.append(rejected));
    assert(queue.size() == 3);
    assert(queue[0].transform[4] == 100.0F);

    const std::array replacement{move(0x56782000, 10.0F), move(0x56782000, 11.0F)};
    assert(queue.append(replacement));
    assert(queue.size() == 3);
    queue.erase(0);
    assert(queue.size() == 2);
    assert(queue[0].handle == 0x12342001);
    assert(queue[1].transform[4] == 11.0F);
    queue.clear();
    assert(queue.size() == 0);
    assert(queue.append(rejected));
    assert(queue.size() == 2);
    std::puts("Latest transform, full-datum identity and atomic batch rejection passed.");
}
