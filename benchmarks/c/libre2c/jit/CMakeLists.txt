add_executable(bench_submatch_jit
    "bench.cc"
    "${CMAKE_SOURCE_DIR}/benchmarks/c/common/common.cc"
)

target_link_libraries(bench_submatch_jit libre2c)

find_package(benchmark REQUIRED)
target_link_libraries(bench_submatch_jit benchmark::benchmark)

# if present, re2 is used for benchmarks
find_path(RE2_INCLUDE_DIRECTORY "re2/re2.h")
find_library(RE2_LIBRARY re2)
if(RE2_INCLUDE_DIRECTORY AND RE2_LIBRARY)
    set_target_properties(bench_submatch_jit PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)
    target_compile_definitions(bench_submatch_jit PRIVATE "HAVE_RE2_RE2_H=1")
    target_include_directories(bench_submatch_jit PRIVATE "${RE2_INCLUDE_DIRECTORY}")
    target_link_libraries(bench_submatch_jit "${RE2_LIBRARY}")
endif()
