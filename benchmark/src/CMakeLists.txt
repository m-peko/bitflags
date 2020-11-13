cmake_minimum_required (VERSION 3.8)

# Use bitflags's include directories + Google Benchmark include directories
include_directories (
    ${PROJECT_SOURCE_DIR}/include/
    ${GOOGLEBENCH_INCLUDE}
)

link_directories (
    ${GOOGLEBENCH_LIBRARY}
)

# Link against GoogleBenchmark and bitflags
link_libraries (
    benchmark
    bitflags
)

add_executable (bench EXCLUDE_FROM_ALL "benchmark.cpp")
