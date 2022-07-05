cmake_minimum_required(VERSION 3.10)

project("LayoutGeneratorTest")

add_executable("${PROJECT_NAME}" "LayoutGeneratorTest.cpp")

target_link_libraries("${PROJECT_NAME}" 
    StampSlicer_core
    gtest_main
    )


add_test(NAME ${PROJECT_NAME} 
    COMMAND ${PROJECT_NAME} 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})