project("FormatCbddlpTest")

add_executable("${PROJECT_NAME}" "FormatCbddlpTest.cpp")

target_link_libraries("${PROJECT_NAME}" 
    StampSlicer_formats
    gtest_main
    )


add_test(NAME ${PROJECT_NAME} 
    COMMAND ${PROJECT_NAME} 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})