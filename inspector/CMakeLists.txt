cmake_minimum_required(VERSION 3.10)

project("FileInspector")

add_executable(${PROJECT_NAME}
    "src/Inspector.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME} PRIVATE
    # StampSlicer_core
    StampSlicer_formats
    -static-libgcc
    -static-libstdc++
)

