cmake_minimum_required(VERSION 3.10)



project("StampSlicer_formats")
add_library(${PROJECT_NAME} STATIC
    "src/FormatCbddlp.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC "include")

add_subdirectory("test/FormatCbddlpTest")