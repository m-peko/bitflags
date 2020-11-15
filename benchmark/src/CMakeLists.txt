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

add_custom_target (benchmarks)

macro (create_benchmark benchmark_name)
    string (REPLACE "/" "_" binary_name ${benchmark_name})
    set (binary_name "${binary_name}_benchmark")
    add_executable (${binary_name} EXCLUDE_FROM_ALL "${benchmark_name}_benchmark.cpp")
    add_test (${benchmark_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${binary_name})
    add_dependencies (benchmarks ${binary_name})
endmacro ()

# Benchmarks

create_benchmark (bitset)
create_benchmark (bitflags)
create_benchmark (raw_bitflags)
