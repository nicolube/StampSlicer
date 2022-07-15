cmake_minimum_required(VERSION 3.10)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

if (${WIN32})
    include(windows.cmake)
endif()

project(StampSlicer)

add_subdirectory("cli")
add_subdirectory("inspector")
add_subdirectory("core")
add_subdirectory("formats")
add_subdirectory("external/bitmap")
add_subdirectory("external/gtest")
add_subdirectory("external/lunasvg")
add_subdirectory("external/nlohmann")