cmake_minimum_required (VERSION 3.8)

if (DEFINED PROJECT_NAME)
    set (BITFLAGS_SUBPROJECT ON)
endif ()

set (BITFLAGS_VERSION_MAJOR 1)
set (BITFLAGS_VERSION_MINOR 0)
set (BITFLAGS_VERSION_PATCH 0)

set (BITFLAGS_VERSION "${BITFLAGS_VERSION_MAJOR}.${BITFLAGS_VERSION_MINOR}.${BITFLAGS_VERSION_PATCH}")

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
    project (
        bitflags
            VERSION ${BITFLAGS_VERSION}
            LANGUAGES CXX
            HOMEPAGE_URL "https://github.com/m-peko/smart-enum"
            DESCRIPTION ""
    )
elseif (CMAKE_VERSION VERSION_GREATER_EQUAL "3.9")
    project (
        bitflags
            VERSION ${BITFLAGS_VERSION}
            LANGUAGES CXX
            DESCRIPTION ""
    )
else ()
    project (
        bitflags
            VERSION ${BITFLAGS_VERSION}
            LANGUAGES CXX
    )
endif ()

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# Compilation flags
if (MSVC)
    # Don't always use Wall, since VC's /Wall is too verbose.
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /O2")
else ()
    option (BITFLAGS_ENABLE_COVERAGE "Enable code coverage reporting" OFF)
    if (BITFLAGS_ENABLE_COVERAGE)
        message (STATUS "Code coverage reporting is enabled.")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O0 --coverage")
    else ()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O3")
    endif ()
endif ()

option (BITFLAGS_BUILD_SAMPLES "Build examples" ON)
option (BITFLAGS_BUILD_TESTS "Build tests" ON)

add_library (bitflags INTERFACE)
add_library (bitflags::bitflags ALIAS bitflags)

target_compile_features (bitflags INTERFACE cxx_std_17)
target_include_directories (
    bitflags INTERFACE
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

if (BITFLAGS_BUILD_SAMPLES)
    add_subdirectory (samples)
endif ()

if (BITFLAGS_BUILD_TESTS)
    # Only include googletest if the git submodule has been fetched
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/googletest/CMakeLists.txt")
        # Enable tests and add the test directory
        message (STATUS "Tests have been enabled")
        set (GOOGLETEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/googletest)
        set (GOOGLETEST_INCLUDE ${GOOGLETEST_ROOT}/googletest/include)
        set (GOOGLETEST_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/googletest)
        set (GOOGLETEST_LIBRARY ${GOOGLETEST_BINARY_DIR}/googletest)

        enable_testing ()
        add_subdirectory (googletest)
        add_subdirectory (tests)
    else ()
        message (STATUS "googletest git submodule is absent. Run `git submodule init && git submodule update` to get it")
    endif ()
endif ()

if (NOT BITFLAGS_SUBPROJECT)
    configure_package_config_file (
        bitflags_config.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/bitflags_config.cmake
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bitflags
    )

    write_basic_package_version_file (
        bitflags_config_version.cmake
            COMPATIBILITY AnyNewerVersion
    )

    install (TARGETS bitflags EXPORT bitflags_targets)

    install (
        EXPORT bitflags_targets
        FILE bitflags_targets.cmake
        NAMESPACE bitflags::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bitflags
    )

    install (
        FILES ${CMAKE_CURRENT_BINARY_DIR}/bitflags_config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/bitflags_config_version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bitflags
    )

    install (
        DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/bitflags
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        USE_SOURCE_PERMISSIONS
        PATTERN "*.hpp"
    )
endif ()