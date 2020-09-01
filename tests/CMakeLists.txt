cmake_minimum_required (VERSION 3.8)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src)
include_directories (${gtest_INCLUDE_DIRS})
add_subdirectory (src)