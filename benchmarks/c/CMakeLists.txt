set(BENCHMARKS
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

# binaries
set(RE2C_CXX_FLAGS "-O3" "-g" "-I" "${SRC_DIR}" "-Wall" "-Wno-unused-const-variable")
list(APPEND COMPILERS "g++" "clang++")
list(APPEND COMPNAMES "gcc" "clang")
foreach(compiler IN ZIP_LISTS COMPILERS COMPNAMES)
    set(objects "")
    set(flags ${RE2C_CXX_FLAGS} "-DCXX=\\\"${compiler_1}\\\"")
    foreach(gen_file ${GEN})
        string(REGEX REPLACE
            "^${GEN_DIR}(.+)\.cc$" "${GEN_DIR}\\1-${compiler_1}.o" obj_file "${gen_file}")
        add_custom_command(
            OUTPUT "${obj_file}"
            COMMAND "${compiler_0}" ${flags} -c "${gen_file}" -o "${obj_file}"
            DEPENDS "${gen_file}" "${SRC_DIR}/common.h"
        )
        list(APPEND objects "${obj_file}")
    endforeach()
    # don't use add_executable, as we need to mnually select the toolchain.
    set(inputs ${objects} "${SRC_DIR}/bench.cc")
    set(output "bench-${compiler_1}")
    add_custom_command(
        OUTPUT "${output}"
        COMMAND "${compiler_0}" ${flags} ${inputs} "-o" "${output}" "-lbenchmark"
        DEPENDS ${inputs}
    )
    if(compiler_1 STREQUAL "gcc") # build test only with GCC
        set(test_inputs ${objects} "${SRC_DIR}/test.cc")
        add_custom_command(
            OUTPUT "test"
            COMMAND "${compiler_0}" ${flags} ${test_inputs} "-o" "test" "-lbenchmark"
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
regex_replace_list("^submatch_[0-9]+__([^_]+).*" "\\1" INPUTS ${BENCHMARKS})
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
