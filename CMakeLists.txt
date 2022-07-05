cmake_minimum_required(VERSION 3.10)

enable_testing()

project(StampSlicer)

add_subdirectory("core")
add_subdirectory("formats")
add_subdirectory("external/bitmap")
add_subdirectory("external/gtest")
add_subdirectory("external/lunasvg")
add_subdirectory("external/nlohmann")