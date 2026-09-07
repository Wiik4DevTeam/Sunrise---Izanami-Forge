cmake_minimum_required(VERSION 3.31)
project(IzanamiRegressionTests LANGUAGES CXX)
enable_testing()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/../../Sunrise/src")

add_executable(map_generator_auth_test map_generator_auth_test.cpp
    "${SRC}/middleware/bap/activity_message/activity_sensor_auth_bodies.cpp"
    "${SRC}/middleware/bap/activity_message/activity_sensor_auth_blocks.cpp"
    "${SRC}/middleware/encoding/bit_reader.cpp"
    "${SRC}/middleware/encoding/bit_writer.cpp")
add_executable(activation_queue_test activation_queue_test.cpp)
add_executable(map_recipe_test map_recipe_test.cpp
    "${SRC}/izanami/fate/map_recipe.cpp"
    "${SRC}/izanami/core/transform.cpp")

foreach(target map_generator_auth_test activation_queue_test map_recipe_test)
    target_include_directories(${target} PRIVATE "${SRC}")
    target_compile_definitions(${target} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX /UNDEBUG)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Werror -UNDEBUG)
    endif()
    add_test(NAME ${target} COMMAND ${target})
endforeach()
