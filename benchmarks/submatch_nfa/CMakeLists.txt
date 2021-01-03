add_executable(bench_submatch_nfa
    "bench.cc"
    "${CMAKE_SOURCE_DIR}/benchmarks/common.cc"
)

set_property(TARGET bench_submatch_nfa PROPERTY CXX_STANDARD 11)

target_link_libraries(bench_submatch_nfa libre2c)

# if present, re2 is used for benchmarks
find_path(RE2_INCLUDE_DIRECTORY "re2/re2.h")
find_library(RE2_LIBRARY re2)
if(RE2_INCLUDE_DIRECTORY AND RE2_LIBRARY)
    target_compile_definitions(bench_submatch_nfa PRIVATE "HAVE_RE2_RE2_H=1")
    target_include_directories(bench_submatch_nfa PRIVATE "${RE2_INCLUDE_DIRECTORY}")
    target_link_libraries(bench_submatch_nfa "${RE2_LIBRARY}")
endif()
