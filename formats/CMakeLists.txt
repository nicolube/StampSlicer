cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("StampSlicer_formats")
add_library(${PROJECT_NAME}
    "src/FormatCbddlp.cpp"
    "src/Image.cpp"
    "src/Packager.cpp"
    "src/PrinterConfig.cpp"
    "src/ResinConfig.cpp"
)

target_link_libraries("${PROJECT_NAME}" 
    bitmap)

target_include_directories(${PROJECT_NAME} PUBLIC "include")

add_subdirectory("test/FormatCbddlpTest")
add_subdirectory("test/ImageTest")