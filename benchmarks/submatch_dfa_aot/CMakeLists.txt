set(BENCHMARKS
    "alt1_2" "alt1_4" "alt1_8"
    "alt2_2" "alt2_4" "alt2_8"
    "alt4_2" "alt4_4" "alt4_8"
    "cat2_0" "cat2_4" "cat2_8"
    "cat4_0" "cat4_2" "cat4_4"
    "cat8_0" "cat8_1" "cat8_2"
    "iter_a_4" "iter_a_16" "iter_a_64"
    "iter_b_2_3_5" "iter_b_7_11_13" "iter_b_17_19_23"
    "iter_c_2_3_5" "iter_c_7_11_13" "iter_c_17_19_23"
    "apache_log"
    "datetime"
    "email"
    "ipv4"
    "uri_simple"
    "uri_rfc3986"
    "http_simple"
    "http_rfc7230"
)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(ENG_DIR "${CMAKE_CURRENT_BINARY_DIR}/engines")
set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/gen")
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(PREGEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pregen")

set(GEN "")

# kleenex
file(MAKE_DIRECTORY "${ENG_DIR}/kleenex/")
file(MAKE_DIRECTORY "${GEN_DIR}/kleenex/")
set(KLEENEX "${ENG_DIR}/kleenex/kexc")
add_custom_command(
    OUTPUT "${KLEENEX}"
    COMMAND "${CMAKE_COMMAND}" -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/engines/kleenex/0001-Updating-for-new-GHC.patch"
        "${ENG_DIR}/kleenex/0001-Updating-for-new-GHC.patch"
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/engines/kleenex/getkleenex.sh"
    WORKING_DIRECTORY "${ENG_DIR}/kleenex/"
)
# Masked benchmarks for which Kleenex either generates very large output
# (tens of megabytes of C code), or even causes out of memory condition.
set(KLEENEX_MASKED
    "iter_b_7_11_13" "iter_b_17_19_23"
    "iter_c_7_11_13" "iter_c_17_19_23"
)
list(JOIN KLEENEX_MASKED "|" KLEENEX_MASKED_REGEXP)
set(KLEENEX_BENCHMARKS ${BENCHMARKS})
list(FILTER KLEENEX_BENCHMARKS EXCLUDE REGEX "${KLEENEX_MASKED_REGEXP}")
foreach(bench ${KLEENEX_BENCHMARKS})
    set(src_file "${SRC_DIR}/kleenex/${bench}.kex")
    set(gen_file "${GEN_DIR}/kleenex/${bench}.c")
    set(pregen_file "${PREGEN_DIR}/kleenex/${bench}.c")
    if(RE2C_REGEN_BENCHMARKS)
        file(RELATIVE_PATH rel_src_file "${CMAKE_CURRENT_BINARY_DIR}" "${src_file}")
        file(RELATIVE_PATH rel_gen_file "${CMAKE_CURRENT_BINARY_DIR}" "${gen_file}")
        add_custom_command(
            OUTPUT "${gen_file}"
            COMMAND "${KLEENEX}" compile "${rel_src_file}" --srcout "${rel_gen_file}" --act=false --la=true
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${gen_file}" "${pregen_file}"
            DEPENDS "${src_file}" "${KLEENEX}"
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

# ragel
file(MAKE_DIRECTORY "${ENG_DIR}/ragel/")
file(MAKE_DIRECTORY "${GEN_DIR}/ragel/")
set(RAGEL "${ENG_DIR}/ragel/ragel7")
add_custom_command(
    OUTPUT "${RAGEL}"
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/engines/ragel/getragel7.sh"
    WORKING_DIRECTORY "${ENG_DIR}/ragel/"
)
foreach(bench ${BENCHMARKS})
    set(src_file "${SRC_DIR}/ragel/${bench}.rl")
    set(gen_file "${GEN_DIR}/ragel/${bench}.c")
    set(pregen_file "${PREGEN_DIR}/ragel/${bench}.c")
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
set(RE2C_FLAGS "--reusable" "--tags" "--no-generation-date")
set(COMMON_RE2C
    "${SRC_DIR}/re2c/common.re"
    "${SRC_DIR}/re2c/include_bc/fill.re"
    "${SRC_DIR}/re2c/include_bc/fill_email.re"
    "${SRC_DIR}/re2c/include_eof/fill.re"
    "${SRC_DIR}/re2c/include_eof/fill_email.re"
)
foreach(bench ${BENCHMARKS})
foreach(eof "bc" "eof")
foreach(alg "tdfa1" "tdfa0" "stadfa")
    set(src_file "${SRC_DIR}/re2c/${bench}.re")
    set(gen_file "${GEN_DIR}/re2c/${bench}-${eof}-${alg}.c")
    set(pregen_file "${PREGEN_DIR}/re2c/${bench}-${eof}-${alg}.c")
    if(RE2C_REGEN_BENCHMARKS)
        file(RELATIVE_PATH rel_src_file "${CMAKE_CURRENT_BINARY_DIR}" "${src_file}")
        file(RELATIVE_PATH rel_gen_file "${CMAKE_CURRENT_BINARY_DIR}" "${gen_file}")
        file(RELATIVE_PATH rel_inc_path "${CMAKE_CURRENT_BINARY_DIR}" "${SRC_DIR}/re2c/include_${eof}")
        set(re2c_flags ${RE2C_FLAGS} "-I" "${rel_inc_path}")
        if("${alg}" STREQUAL "tdfa1-es")
            set(re2c_flags ${re2c_flags} "--eager-skip")
        elseif("${alg}" STREQUAL "tdfa0")
            set(re2c_flags ${re2c_flags} "--no-lookahead")
        elseif("${alg}" STREQUAL "stadfa")
            set(re2c_flags ${re2c_flags} "--stadfa")
        endif()
        add_custom_command(
            OUTPUT "${gen_file}"
            COMMAND "${RE2C}" ${re2c_flags} "${rel_src_file}" -o "${rel_gen_file}"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${gen_file}" "${pregen_file}"
            DEPENDS "${src_file}" ${COMMON_RE2C} "${RE2C}"
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
endforeach()
endforeach()

# binaries
set(BIN "")
set(CFLAGS "-O3" "-g" "-I" "${SRC_DIR}")
set(COMMON_SRC "${SRC_DIR}/common.h")
file(MAKE_DIRECTORY "${BIN_DIR}/kleenex/")
file(MAKE_DIRECTORY "${BIN_DIR}/ragel/")
file(MAKE_DIRECTORY "${BIN_DIR}/re2c/")
foreach(gen_file ${GEN})
foreach(compiler "gcc" "clang")
    string(REGEX REPLACE "^${GEN_DIR}(.+)\.c$" "${BIN_DIR}\\1-${compiler}" bin_file "${gen_file}")
    add_custom_command(
        OUTPUT "${bin_file}"
        COMMAND "${compiler}" ${CFLAGS} "${gen_file}" -o "${bin_file}"
        DEPENDS "${gen_file}" ${COMMON_SRC}
    )
    list(APPEND BIN "${bin_file}")
endforeach()
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
## Some benchmarks share the same data, like `uri_simple` and `uri_rfc3986`
regex_replace_list("^([^_]+).*" "\\1" INPUTS ${BENCHMARKS})
list(REMOVE_DUPLICATES INPUTS)
foreach(input ${INPUTS})
    set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/data/${input}")
    set(dst_dir "${CMAKE_CURRENT_BINARY_DIR}/data/${input}")
    file(GLOB script "${src_dir}/gen_${input}\.*")
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

add_custom_target(benchmarks DEPENDS ${BIN} ${DAT})

# benchmark scripts
set(srcdir "${CMAKE_CURRENT_SOURCE_DIR}")
set(builddir ".")
configure_file(verify.sh.in verify.sh @ONLY)
configure_file(run.sh.in run.sh @ONLY)

# clean
add_custom_target(clean_benchmarks)
add_custom_command(
    TARGET clean_benchmarks
    COMMAND "${CMAKE_COMMAND}" -E rm -f ${GEN} ${BIN} ${DAT}
)
