cmake_minimum_required(VERSION 3.10)

project("StampSlicer_formats")
add_library(${PROJECT_NAME} STATIC
    "src/PrinterConfig.cpp"
    "src/ResinConfig.cpp"
    "src/FormatCbddlp.cpp"
    "src/Image.cpp"
)

target_link_libraries("${PROJECT_NAME}" 
    bitmap)

target_include_directories(${PROJECT_NAME} PUBLIC "include")

add_subdirectory("test/FormatCbddlpTest")
add_subdirectory("test/ImageTest")