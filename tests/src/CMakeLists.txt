cmake_minimum_required (VERSION 3.8)

# Use bitflags's include directories + Google Test include directories
include_directories (
    ${PROJECT_SOURCE_DIR}/include/
    ${GOOGLETEST_INCLUDE}
)

# Find pthread library
find_package (Threads REQUIRED)

link_directories (
    ${GOOGLETEST_LIBRARY}
)

# Link against GoogleTest, bitflags and pthread
# Pthread is required by GoogleTest
link_libraries (
    gtest
    gtest_main
    bitflags
)

add_custom_target (tests)

macro (create_test test_name)
    string (REPLACE "/" "_" binary_name ${test_name})
    set (binary_name "${binary_name}_test")
    add_executable (${binary_name} EXCLUDE_FROM_ALL "${test_name}_test.cpp")
    add_test (${test_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${binary_name})
    add_dependencies (tests ${binary_name})
    if (MSVC)
        target_link_libraries (${binary_name} gtest gtest_main)
    else ()
        target_link_libraries (${binary_name} gtest gtest_main --coverage)
    endif ()
endmacro ()

# Tests

create_test (bitflags)