cmake_minimum_required(VERSION 3.10)

project("StampSlicer_core")
add_library(${PROJECT_NAME} STATIC
    "src/LayerGanerator.cpp"
)

target_link_libraries("${PROJECT_NAME}" 
    StampSlicer_formats)

target_include_directories(${PROJECT_NAME} PUBLIC "include")


add_subdirectory("test/LayoutGeneratorTest")