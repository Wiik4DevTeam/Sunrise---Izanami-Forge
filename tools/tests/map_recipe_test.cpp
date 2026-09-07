#include <Windows.h>

#include <cassert>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <limits>
#include <vector>

#include "izanami/fate/map_recipe.h"

namespace recipe = sunrise::izanami::fate::recipe;

int main() {
    const auto directory = std::filesystem::temp_directory_path()
                           / (L"izanami_recipe_test_" + std::to_wstring(GetCurrentProcessId()));
    std::filesystem::create_directories(directory);
    const auto path = directory / L"scene.fate";
    const std::vector<recipe::ActorInstruction> source{
        {1, 0, "Outer group", 0, 0, {{2, 3, 4}, {}, 2}, true},
        {2, 1, "Inner group", 0, 0, {{4, 5, 6}, {}, 1}, true},
        {3, 2, "Chandelier \"custom\"", 0x80B6C246, 1, {{5, 6, 7}, {}, 3}},
    };
    assert(recipe::save(path.wstring(), "Grouped scene", source).succeeded);
    recipe::MapRecipe loaded;
    assert(recipe::load(path.wstring(), loaded).succeeded);
    assert(loaded.actors.size() == 3);
    for (std::size_t index = 0; index < source.size(); ++index) {
        const auto& actual = loaded.actors[index];
        const auto& expected = source[index];
        assert(actual.editorId == expected.editorId && actual.parentId == expected.parentId);
        assert(actual.virtualGroup == expected.virtualGroup && actual.tag == expected.tag);
        assert(actual.name == expected.name);
        assert(actual.transform.translation.x == expected.transform.translation.x);
        assert(actual.transform.uniformScale == expected.transform.uniformScale);
    }

    // Deny replacement of the last good save, while allowing staging beside it.
    const HANDLE held = CreateFileW(path.c_str(),
                                    GENERIC_READ,
                                    FILE_SHARE_READ,
                                    nullptr,
                                    OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL,
                                    nullptr);
    assert(held != INVALID_HANDLE_VALUE);
    assert(!recipe::save(path.wstring(), "Must not replace", source).succeeded);
    CloseHandle(held);
    assert(recipe::load(path.wstring(), loaded).succeeded && loaded.name == "Grouped scene");
    assert(!std::filesystem::exists(path.wstring() + L".tmp"));

    auto invalid = source;
    invalid[0].parentId = 2;
    assert(!recipe::save(path.wstring(), "Cycle", invalid).succeeded);
    invalid = source;
    invalid[2].parentId = 99;
    assert(!recipe::save(path.wstring(), "Missing parent", invalid).succeeded);
    invalid = source;
    invalid[2].editorId = 1;
    assert(!recipe::save(path.wstring(), "Duplicate ID", invalid).succeeded);
    invalid = source;
    invalid[2].transform.uniformScale = std::numeric_limits<float>::infinity();
    assert(!recipe::save(path.wstring(), "Invalid scale", invalid).succeeded);
    assert(recipe::load(path.wstring(), loaded).succeeded && loaded.name == "Grouped scene");

    const auto legacy = directory / L"legacy.fate";
    {
        std::ofstream stream(legacy);
        stream << "IZANAMI_FATE_MAP 1\nscene \"Legacy\"\n"
                  "actor 7 0 \"Legacy asset\" 80B6C246 1 0 0 0 0 0 0 1 1\n";
    }
    assert(recipe::load(legacy.wstring(), loaded).succeeded);
    assert(loaded.actors.size() == 1 && !loaded.actors[0].virtualGroup);
    {
        std::ofstream stream(legacy);
        stream << "IZANAMI_FATE_MAP 2\nscene \"Truncated\"\nactor 1 0";
    }
    assert(!recipe::load(legacy.wstring(), loaded).succeeded && loaded.actors.empty());

    // Exercise the format's full actor limit in reverse parent order, without recursive walks.
    std::vector<recipe::ActorInstruction> deep;
    for (std::uint64_t id = 1; id <= 8192; ++id) {
        deep.push_back({id, id == 8192 ? 0 : id + 1, "Nested", 0, 0, {}, true});
    }
    assert(recipe::save(path.wstring(), "Deep hierarchy", deep).succeeded);
    assert(recipe::load(path.wstring(), loaded).succeeded && loaded.actors.size() == 8192);
    deep.back().parentId = 1;
    assert(!recipe::save(path.wstring(), "Long cycle", deep).succeeded);
    assert(recipe::load(path.wstring(), loaded).succeeded && loaded.name == "Deep hierarchy");

    std::filesystem::remove(path);
    std::filesystem::remove(legacy);
    std::filesystem::remove(directory);
    std::puts(
        "Nested groups, legacy loading, invalid hierarchy and failed-save preservation passed.");
}
