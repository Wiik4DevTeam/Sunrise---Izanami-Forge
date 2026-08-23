#include <cmath>
#include <filesystem>
#include <iostream>
#include <vector>

#include "../Sunrise/src/izanami/fate/map_recipe.h"

namespace recipe = sunrise::izanami::fate::recipe;

namespace {

[[nodiscard]] bool close(float left, float right) {
    return std::abs(left - right) < 1.0e-6F;
}

[[nodiscard]] bool same_transform(const sunrise::izanami::core::Transform& left,
                                  const sunrise::izanami::core::Transform& right) {
    return close(left.translation.x, right.translation.x)
           && close(left.translation.y, right.translation.y)
           && close(left.translation.z, right.translation.z)
           && close(left.rotation.x, right.rotation.x) && close(left.rotation.y, right.rotation.y)
           && close(left.rotation.z, right.rotation.z) && close(left.rotation.w, right.rotation.w)
           && close(left.uniformScale, right.uniformScale);
}

} // namespace

int main() {
    const std::filesystem::path path =
        std::filesystem::temp_directory_path() / L"izanami_map_recipe_roundtrip.fate";
    const std::vector<recipe::ActorInstruction> source{
        {1,
         0,
         "Root Chandelier",
         0x80B6C246U,
         1,
         {{12.25F, -3.5F, 44.0F}, {0.0F, 0.70710677F, 0.0F, 0.70710677F}, 2.5F}},
        {2,
         1,
         "Child with spaces",
         0x80B5A308U,
         7,
         {{-7.0F, 8.125F, 0.25F}, {0.1F, 0.2F, 0.3F, 0.9F}, 0.75F}},
    };

    const recipe::IoResult saved = recipe::save(path.wstring(), "Round Trip Scene", source);
    if (!saved.succeeded || saved.instructionCount != source.size()) {
        std::cerr << "save failed: " << saved.message << '\n';
        return 1;
    }

    recipe::MapRecipe loaded;
    const recipe::IoResult read = recipe::load(path.wstring(), loaded);
    std::filesystem::remove(path);
    if (!read.succeeded || loaded.name != "Round Trip Scene"
        || loaded.actors.size() != source.size()) {
        std::cerr << "load failed: " << read.message << '\n';
        return 2;
    }

    for (std::size_t index = 0; index < source.size(); ++index) {
        const auto& expected = source[index];
        const auto& actual = loaded.actors[index];
        if (expected.editorId != actual.editorId || expected.parentId != actual.parentId
            || expected.name != actual.name || expected.tag != actual.tag
            || expected.objectType != actual.objectType
            || !same_transform(expected.transform, actual.transform)) {
            std::cerr << "actor mismatch at index " << index << '\n';
            return 3;
        }
    }

    std::cout << "map recipe roundtrip passed: " << loaded.actors.size() << " actors\n";
    return 0;
}
