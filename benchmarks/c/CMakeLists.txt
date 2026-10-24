find_package(PkgConfig REQUIRED)
pkg_check_modules(GBENCHMARK REQUIRED benchmark)

set(BENCHMARKS
    "lex_00__numbers1"
    "lex_01__numbers2"
    "lex_02__words1"
    "lex_03__words2"
    "lex_04__words3"

    "submatch_00__http_rfc7230"
    "submatch_01__http_simple"
    "submatch_02__uri_rfc3986"
    "submatch_03__uri_simple"
    "submatch_04__apache_log"
    "submatch_05__datetime"
    "submatch_06__email"
    "submatch_07__ipv4"

    "submatch_10__alt1_2"
    "submatch_11__alt1_4"
    "submatch_12__alt1_8"
    "submatch_13__alt2_2"
    "submatch_14__alt2_4"
    "submatch_15__alt2_8"
    "submatch_16__alt4_2"
    "submatch_17__alt4_4"
    "submatch_18__alt4_8"

    "submatch_20__cat2_0"
    "submatch_21__cat2_4"
    "submatch_22__cat2_8"
    "submatch_23__cat4_0"
    "submatch_24__cat4_2"
    "submatch_25__cat4_4"
    "submatch_26__cat8_0"
    "submatch_27__cat8_1"
    "submatch_28__cat8_2"

    "submatch_30__rep_cat_5_3_2"
    "submatch_31__rep_cat_13_11_7"
    "submatch_32__rep_cat_23_19_17"
    "submatch_33__rep_alt_5_3_2"
    "submatch_34__rep_alt_13_11_7"
    "submatch_35__rep_alt_23_19_17"
    "submatch_36__rep_5_rep_3_rep_2"
    "submatch_37__rep_13_rep_11_rep_7"
    "submatch_38__rep_23_rep_19_rep_17"
)

# Benchmarks for `--vectorize-loops`: each one is a single .re file that generates scalar and
# vectorized lexers side by side (see src/re2c/vec_base.re). The generated code uses AVX2
# intrinsics, so these benchmarks are built only on x86 and compiled with -mavx2 (only them, so
# that other benchmarks are not affected); the benchmark and test binaries skip them at run time
# if the CPU does not support AVX2.
set(VEC_BENCHMARKS
    "vec_00__strings"
    "vec_01__strings_fixed"
)
# Per-benchmark syntax files (re2c --syntax), relative to src/re2c.
set(VEC_SYNTAX_vec_01__strings_fixed "vec_fixed.syntax")
# Optional third-party references for the vec_* benchmarks (off by default, found with pkg-config;
# they must be installed separately, see README).
option(RE2C_BENCH_SIMDJSON "Add simdjson reference benchmarks on the json data set" OFF)
option(RE2C_BENCH_HYPERSCAN "Add Hyperscan (or Vectorscan) reference benchmarks" OFF)
set(VEC_INPUTS "strshort" "strmedium" "strlong" "strescape" "json" "csource")
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64|i[3-6]86)$")
    set(RE2C_BENCH_VECTORIZE ON)
else()
    set(RE2C_BENCH_VECTORIZE OFF)
    set(VEC_BENCHMARKS "")
    set(VEC_INPUTS "")
endif()
set(VEC_CXX_FLAGS "-mavx2")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(ENG_DIR "${CMAKE_CURRENT_BINARY_DIR}/engines")
set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/gen")
set(PREGEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pregen")

set(GEN "")

# ragel
file(MAKE_DIRECTORY "${ENG_DIR}/ragel/")
file(MAKE_DIRECTORY "${GEN_DIR}/ragel/")
set(RAGEL "${ENG_DIR}/ragel/ragel7")
add_custom_command(
    OUTPUT "${RAGEL}"
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/../_engines/ragel/getragel7.sh"
    WORKING_DIRECTORY "${ENG_DIR}/ragel/"
)
foreach(bench ${BENCHMARKS})
    set(src_file "${SRC_DIR}/ragel/${bench}.rl")
    set(gen_file "${GEN_DIR}/ragel/${bench}.cc")
    set(pregen_file "${PREGEN_DIR}/ragel/${bench}.cc")
    # optionally regenerate ragel benchmarks if RE2C_REGEN_BENCHMARKS is set
    if(RE2C_REGEN_BENCHMARKS)
        file(RELATIVE_PATH rel_src_file "${CMAKE_CURRENT_BINARY_DIR}" "${src_file}")
        file(RELATIVE_PATH rel_gen_file "${CMAKE_CURRENT_BINARY_DIR}" "${gen_file}")
        add_custom_command(
            OUTPUT "${gen_file}"
            COMMAND "${RAGEL}" "-G2" "${rel_src_file}" -o "${rel_gen_file}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${gen_file}" "${pregen_file}"
            DEPENDS "${src_file}" "${RAGEL}"
        )
    else()
        add_custom_command(
            OUTPUT "${gen_file}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${pregen_file}" "${gen_file}"
            DEPENDS "${pregen_file}"
        )
    endif()
    list(APPEND GEN "${gen_file}")
endforeach()

# re2c
file(MAKE_DIRECTORY "${GEN_DIR}/re2c/")
set(RE2C "${CMAKE_BINARY_DIR}/re2c")
set(RE2C_FLAGS "--reusable" "--tags" "--no-generation-date" "--no-version" "-i")
# always regenerate re2c benchmarks
foreach(bench ${BENCHMARKS})
    set(src_file "${SRC_DIR}/re2c/${bench}.re")
    set(gen_file "${GEN_DIR}/re2c/${bench}.cc")
    set(pregen_file "${PREGEN_DIR}/re2c/${bench}.cc")
    file(RELATIVE_PATH rel_src_file "${CMAKE_CURRENT_BINARY_DIR}" "${src_file}")
    file(RELATIVE_PATH rel_gen_file "${CMAKE_CURRENT_BINARY_DIR}" "${gen_file}")
    add_custom_command(
        OUTPUT "${gen_file}"
        COMMAND "${RE2C}" ${RE2C_FLAGS} "${rel_src_file}" -o "${rel_gen_file}"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${gen_file}" "${pregen_file}"
        DEPENDS "${src_file}" "${SRC_DIR}/re2c/base.re" "${RE2C}"
    )
    list(APPEND GEN "${gen_file}")
endforeach()
set(VEC_GEN "")
foreach(bench ${VEC_BENCHMARKS})
    set(src_file "${SRC_DIR}/re2c/${bench}.re")
    set(gen_file "${GEN_DIR}/re2c/${bench}.cc")
    set(pregen_file "${PREGEN_DIR}/re2c/${bench}.cc")
    file(RELATIVE_PATH rel_src_file "${CMAKE_CURRENT_BINARY_DIR}" "${src_file}")
    file(RELATIVE_PATH rel_gen_file "${CMAKE_CURRENT_BINARY_DIR}" "${gen_file}")
    set(syntax_flags "")
    set(syntax_deps "")
    if(DEFINED VEC_SYNTAX_${bench})
        # re2c resolves the syntax file like an include, so pass a relative path.
        set(syntax_file "${SRC_DIR}/re2c/${VEC_SYNTAX_${bench}}")
        file(RELATIVE_PATH rel_syntax_file "${CMAKE_CURRENT_BINARY_DIR}" "${syntax_file}")
        set(syntax_flags "--syntax" "${rel_syntax_file}")
        set(syntax_deps "${syntax_file}")
    endif()
    add_custom_command(
        OUTPUT "${gen_file}"
        COMMAND "${RE2C}" ${RE2C_FLAGS} ${syntax_flags} "${rel_src_file}" -o "${rel_gen_file}"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${gen_file}" "${pregen_file}"
        DEPENDS "${src_file}" "${SRC_DIR}/re2c/vec_base.re" "${SRC_DIR}/re2c/vec_strings_rules.re"
            ${syntax_deps} "${RE2C}"
    )
    list(APPEND GEN "${gen_file}")
    list(APPEND VEC_GEN "${gen_file}")
endforeach()

# binaries
if("${GBENCHMARK_INCLUDE_DIR}" STREQUAL "")
    set(GBENCHMARK_INCLUDES "${GBENCHMARK_CFLAGS}")
else()
    set(GBENCHMARK_INCLUDES "-I${GBENCHMARK_INCLUDE_DIR}")
endif()
set(RE2C_CXX_FLAGS "-O3" "-g" "-I" "${SRC_DIR}" "-Wall" "-Wno-unused-const-variable"
    "${GBENCHMARK_INCLUDES}" "-std=c++11") # C++11 is needed for some google-benchmark features
# Hand-written and third-party reference implementations for the vec_* benchmarks (see
# src/ref/vec_ref.h), compiled with the same flags as vec_* objects.
set(VEC_REF_SOURCES "")
set(VEC_REF_LIBS "")
if(RE2C_BENCH_VECTORIZE)
    list(APPEND RE2C_CXX_FLAGS "-DRE2C_BENCH_VECTORIZE")
    list(APPEND VEC_REF_SOURCES "${SRC_DIR}/ref/vec_strings_ref.cc")
    if(RE2C_BENCH_SIMDJSON)
        pkg_check_modules(SIMDJSON REQUIRED simdjson)
        list(APPEND RE2C_CXX_FLAGS "-DRE2C_BENCH_SIMDJSON")
        list(APPEND VEC_REF_SOURCES "${SRC_DIR}/ref/simdjson_ref.cc")
        list(APPEND VEC_REF_LIBS ${SIMDJSON_LDFLAGS})
    endif()
    if(RE2C_BENCH_HYPERSCAN)
        pkg_check_modules(HYPERSCAN REQUIRED libhs)
        list(APPEND RE2C_CXX_FLAGS "-DRE2C_BENCH_HYPERSCAN")
        list(APPEND VEC_REF_SOURCES "${SRC_DIR}/ref/hyperscan_ref.cc")
        list(APPEND VEC_REF_LIBS ${HYPERSCAN_LDFLAGS})
    endif()
endif()
list(APPEND COMPILERS "g++" "clang++")
list(APPEND COMPNAMES "gcc" "clang")
foreach(compiler IN ZIP_LISTS COMPILERS COMPNAMES)
    set(objects "")
    set(flags ${RE2C_CXX_FLAGS} "-DCXX=\\\"${compiler_1}\\\"")
    list(APPEND flags "-DRE2C_BENCH_SOURCE_DIR=\\\"${CMAKE_SOURCE_DIR}\\\"")
    foreach(gen_file ${GEN})
        string(REGEX REPLACE
            "^${GEN_DIR}(.+)\.cc$" "${GEN_DIR}\\1-${compiler_1}.o" obj_file "${gen_file}")
        set(obj_flags ${flags})
        set(obj_deps "${gen_file}" "${SRC_DIR}/common.h")
        if("${gen_file}" IN_LIST VEC_GEN)
            list(APPEND obj_flags ${VEC_CXX_FLAGS})
            list(APPEND obj_deps "${SRC_DIR}/re2c/vec_regimes.h"
                "${SRC_DIR}/re2c/base.h" "${SRC_DIR}/ref/vec_ref.h")
        endif()
        add_custom_command(
            OUTPUT "${obj_file}"
            COMMAND "${compiler_0}" ${obj_flags} -c "${gen_file}" -o "${obj_file}"
            DEPENDS ${obj_deps}
        )
        list(APPEND objects "${obj_file}")
    endforeach()
    foreach(ref_file ${VEC_REF_SOURCES})
        get_filename_component(ref_name "${ref_file}" NAME_WE)
        set(obj_file "${GEN_DIR}/ref/${ref_name}-${compiler_1}.o")
        set(obj_flags ${flags} ${VEC_CXX_FLAGS})
        if(ref_name STREQUAL "simdjson_ref")
            list(REMOVE_ITEM obj_flags "-std=c++11")
            list(APPEND obj_flags "-std=c++17" ${SIMDJSON_CFLAGS})
        elseif(ref_name STREQUAL "hyperscan_ref")
            list(APPEND obj_flags ${HYPERSCAN_CFLAGS})
        endif()
        add_custom_command(
            OUTPUT "${obj_file}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory "${GEN_DIR}/ref"
            COMMAND "${compiler_0}" ${obj_flags} -c "${ref_file}" -o "${obj_file}"
            DEPENDS "${ref_file}" "${SRC_DIR}/ref/vec_ref.h"
        )
        list(APPEND objects "${obj_file}")
    endforeach()
    # don't use add_executable, as we need to mnually select the toolchain.
    set(inputs ${objects} "${SRC_DIR}/bench.cc")
    set(output "bench-${compiler_1}")
    add_custom_command(
        OUTPUT "${output}"
        COMMAND "${compiler_0}" ${flags} ${inputs} "-o" "${output}" ${GBENCHMARK_LINK_LIBRARIES}
            ${VEC_REF_LIBS}
        DEPENDS ${inputs}
    )
    if(compiler_1 STREQUAL "gcc") # build test only with GCC
        set(test_inputs ${objects} "${SRC_DIR}/test.cc")
        add_custom_command(
            OUTPUT "test"
            COMMAND "${compiler_0}" ${flags} ${test_inputs} "-o" "test" ${GBENCHMARK_LINK_LIBRARIES}
                ${VEC_REF_LIBS}
            DEPENDS ${test_inputs}
        )
    endif()
endforeach()

# helper function to transform list
function(regex_replace_list regexp replace var)
    set(result "")
    foreach(arg ${ARGN})
        string(REGEX REPLACE "${regexp}" "${replace}" x "${arg}")
        list(APPEND result "${x}")
    endforeach()
    set(${var} "${result}" PARENT_SCOPE)
endfunction()

# input data
set(DAT)
# Some benchmarks share the same data, like submatch_03__uri_simple and submatch_02__uri_rfc3986.
regex_replace_list("^[a-z]+_[0-9]+__([^_]+).*" "\\1" INPUTS ${BENCHMARKS})
list(APPEND INPUTS ${VEC_INPUTS})
list(REMOVE_DUPLICATES INPUTS)
foreach(input ${INPUTS})
    set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/../_data/${input}")
    set(dst_dir "${CMAKE_CURRENT_BINARY_DIR}/data/${input}")
    file(GLOB script "${CMAKE_CURRENT_SOURCE_DIR}/../_data/gen.py")
    add_custom_command(
        OUTPUT "${dst_dir}/small"
        COMMAND "${CMAKE_COMMAND}" -E copy "${src_dir}/small" "${dst_dir}/small"
        DEPENDS "${src_dir}/small"
    )
    add_custom_command(
        OUTPUT "${dst_dir}/big"
        COMMAND "${script}"
        DEPENDS "${script}" "${dst_dir}/small"
        WORKING_DIRECTORY "${dst_dir}"
    )
    list(APPEND DAT "${dst_dir}/small" "${dst_dir}/big")
endforeach()

add_custom_target(bench_submatch_aot ALL DEPENDS bench-gcc bench-clang test ${DAT})

# benchmark scripts
set(srcdir "${CMAKE_CURRENT_SOURCE_DIR}")
set(builddir ".")
configure_file(run.py.in run.py @ONLY)

# override default clean command to keep engines
set_directory_properties(PROPERTY
    CLEAN_NO_CUSTOM On
    ADDITIONAL_CLEAN_FILES "${GEN};${OBJ};${BIN};${DAT}"
)
