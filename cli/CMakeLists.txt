cmake_minimum_required(VERSION 3.10)

project("StampSlicerCliTool")

add_executable(${PROJECT_NAME}
    "src/CliTool.cpp"
    "src/ParameterProcessor.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME}
    StampSlicer_core
    StampSlicer_formats)