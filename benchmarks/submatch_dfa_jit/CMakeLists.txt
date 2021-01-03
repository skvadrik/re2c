add_executable(bench_submatch_dfa_jit
    "bench.cc"
    "${CMAKE_SOURCE_DIR}/benchmarks/common/common.cc"
)

set_property(TARGET bench_submatch_dfa_jit PROPERTY CXX_STANDARD 11)

target_link_libraries(bench_submatch_dfa_jit libre2c)

# if present, re2 is used for benchmarks
find_path(RE2_INCLUDE_DIRECTORY "re2/re2.h")
find_library(RE2_LIBRARY re2)
if(RE2_INCLUDE_DIRECTORY AND RE2_LIBRARY)
    target_compile_definitions(bench_submatch_dfa_jit PRIVATE "HAVE_RE2_RE2_H=1")
    target_include_directories(bench_submatch_dfa_jit PRIVATE "${RE2_INCLUDE_DIRECTORY}")
    target_link_libraries(bench_submatch_dfa_jit "${RE2_LIBRARY}")
endif()
