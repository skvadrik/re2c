cmake_minimum_required(VERSION 3.0)
project(re2c VERSION 1.3 HOMEPAGE_URL "https://re2c.org/")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Re2cAutotoolsHelpers)
include(Re2cBootstrapLexer)
include(Re2cBootstrapParser)
include(Re2cBootstrapCompiledHelp)
include(Re2cBootstrapManual)
include(Re2cTryCXXFlag)

ac_subst(PACKAGE_VERSION "${PROJECT_VERSION}")

option(RE2C_REBUILD_DOCS "Regenerate manpage" OFF)
if (RE2C_REBUILD_DOCS)
    find_program(RST2MAN NAMES rst2man rst2man.py)
    if (NOT RST2MAN)
        message(FATAL_ERROR "need rst2man or rst2man.py for RE2C_REBUILD_DOCS=YES")
    endif()
endif()

option(RE2C_BUILD_LIBS "Build libraries" OFF)

# checks for programs

find_package(BISON)

# checks for C++ compiler flags

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # make sure object libraries work with shared libraries
if(NOT CMAKE_BUILD_TYPE)
    try_cxxflag("-O2")
endif()
try_cxxflag("-W")
try_cxxflag("-Wall")
try_cxxflag("-Wextra")
try_cxxflag("-Weffc++")
try_cxxflag("-pedantic")
try_cxxflag("-Wformat=2")
try_cxxflag("-Wredundant-decls")
try_cxxflag("-Wsuggest-attribute=format")
try_cxxflag("-Wconversion")
try_cxxflag("-Wsign-conversion")
try_cxxflag("-Werror=return-type")
try_cxxflag("-Weverything"
    "-Wno-unknown-warning-option" # CLANG eats some GCC options only to warn they are unknown
    "-Wno-reserved-id-macro" # to allow header guards of the form '_RE2C_PATH_TO_HEADER_BASENAME_'
    "-Wno-padded"
    "-Wno-old-style-cast" # RE2C-generated lexer has lots of C-syle casts because of 're2c:yych:conversion = 1;'
    "-Wno-nested-anon-types"
    "-Wno-global-constructors" # initialization of global constants with std::numeric_limits<...> (mostly for size_t)
    "-Wno-shadow-field-in-constructor" # using same names in ctor seems more like a feature
    "-Wno-undefined-func-template" # explicit specialization to reduce build dependencies
)

# needed by src/c99_stdint.h
ac_check_headers("stdint.h")
# needed for POSIX file API
ac_check_headers("sys/types.h")
ac_check_headers("sys/stat.h")
ac_check_headers("fcntl.h")
ac_check_headers("unistd.h")
ac_check_headers("io.h") # windows POSIX-like API

# list of possible types to use in typedefs
ac_check_sizeof("char")
ac_check_sizeof("short")
ac_check_sizeof("int")
ac_check_sizeof("long")
ac_check_sizeof("long long")
ac_check_sizeof("__int64")
# size of pointers
ac_check_sizeof("void *")
# 64-bit integer constant suffix
ac_check_sizeof("0l")
ac_check_sizeof("0ll")
ac_check_sizeof("0i8")

set(top_srcdir "${CMAKE_CURRENT_SOURCE_DIR}")
configure_file(doc/manpage.rst.in doc/manpage.rst @ONLY)
configure_file(doc/help.rst.in doc/help.rst @ONLY)

configure_file(run_tests.sh.in run_tests.sh @ONLY)
set(RE2C_RUN_TESTS "${CMAKE_CURRENT_BINARY_DIR}/run_tests.sh")
if(CMAKE_HOST_UNIX)
    execute_process(COMMAND chmod +x "${RE2C_RUN_TESTS}")
endif()

ac_config_headers("config.h")

# Makefile.am
set(RE2C_STDLIB_DIR "${CMAKE_INSTALL_PREFIX}/share/re2c/stdlib")
add_compile_definitions(
  "RE2C_STDLIB_DIR=\"${RE2C_STDLIB_DIR}\""
  $<$<CONFIG:Debug>:RE2C_DEBUG>
  $<$<CONFIG:RelWithDebInfo>:RE2C_DEBUG>
)
include_directories(. "${CMAKE_CURRENT_BINARY_DIR}")

# sources
add_library(re2c_generated_ver_to_vernum OBJECT
    "${CMAKE_CURRENT_BINARY_DIR}/src/msg/ver_to_vernum.cc"
)

add_executable(re2c
    src/codegen/bitmap.cc
    src/codegen/emit_action.cc
    src/codegen/emit_dfa.cc
    src/codegen/label.cc
    src/codegen/go_construct.cc
    src/codegen/go_destruct.cc
    src/codegen/go_emit.cc
    src/codegen/go_used_labels.cc
    src/codegen/input_api.cc
    src/codegen/output.cc
    src/codegen/print.cc
    src/options/opt.cc
    src/nfa/estimate_size.cc
    src/nfa/re_to_nfa.cc
    src/adfa/adfa.cc
    src/adfa/prepare.cc
    src/debug/dump_adfa.cc
    src/debug/dump_cfg.cc
    src/debug/dump_dfa.cc
    src/debug/dump_dfa_tree.cc
    src/debug/dump_interf.cc
    src/debug/dump_nfa.cc
    src/cfg/cfg.cc
    src/cfg/compact.cc
    src/cfg/dce.cc
    src/cfg/freeze.cc
    src/cfg/interfere.cc
    src/cfg/liveanal.cc
    src/cfg/normalize.cc
    src/cfg/optimize.cc
    src/cfg/rename.cc
    src/cfg/varalloc.cc
    src/dfa/closure.cc
    src/dfa/dead_rules.cc
    src/dfa/determinization.cc
    src/dfa/fallback_tags.cc
    src/dfa/fillpoints.cc
    src/dfa/find_state.cc
    src/dfa/minimization.cc
    src/dfa/stacmd.cc
    src/dfa/tagver_table.cc
    src/dfa/tcmd.cc
    src/encoding/ebcdic/ebcdic_regexp.cc
    src/encoding/enc.cc
    src/encoding/range_suffix.cc
    src/encoding/utf8/utf8_regexp.cc
    src/encoding/utf8/utf8.cc
    src/encoding/utf16/utf16_regexp.cc
    src/encoding/utf16/utf16.cc
    src/msg/msg.cc
    src/msg/warn.cc
    src/regexp/ast_to_re.cc
    src/regexp/default_tags.cc
    src/regexp/fixed_tags.cc
    src/regexp/nullable.cc
    src/regexp/rule.cc
    src/regexp/split_charset.cc
    src/regexp/tag.cc
    src/compile.cc
    src/skeleton/control_flow.cc
    src/skeleton/generate_code.cc
    src/skeleton/generate_data.cc
    src/skeleton/maxpath.cc
    src/skeleton/skeleton.cc
    src/parse/ast.cc
    src/parse/input.cc
    src/parse/normalize.cc
    src/parse/scanner.cc
    src/parse/unescape.cc
    src/parse/validate.cc
    src/util/get_dir.cc
    src/util/s_to_n32_unsafe.cc
    src/util/temp_file.cc
    src/util/range.cc
    src/main.cc
    $<TARGET_OBJECTS:re2c_generated_ver_to_vernum>
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/parser.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/parser.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/lex.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/lex.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/lex_conf.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/options/parse_opts.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/doc/re2c.1" # include this so CMake generates it
)

# target_include_directories(re2c PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/generated")

re2c_bootstrap_lexer("src/parse/lex.re" "src/parse/lex.cc" "src/parse/lex.h")
re2c_bootstrap_lexer("src/parse/lex_conf.re" "src/parse/lex_conf.cc")
re2c_bootstrap_lexer("src/options/parse_opts.re" "src/options/parse_opts.cc")
re2c_bootstrap_lexer("src/msg/ver_to_vernum.re" "src/msg/ver_to_vernum.cc")
re2c_bootstrap_parser("src/parse/parser.ypp" "src/parse/parser.cc" "src/parse/parser.h")
re2c_bootstrap_compiled_help("${CMAKE_CURRENT_BINARY_DIR}/doc/help.rst" "src/msg/help.cc")
re2c_bootstrap_manual("${CMAKE_CURRENT_BINARY_DIR}/doc/manpage.rst" "doc/re2c.1")

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    if(UNIX)
        install(TARGETS re2c RUNTIME DESTINATION bin)
        install(FILES "${CMAKE_CURRENT_BINARY_DIR}/doc/re2c.1" DESTINATION "share/man/man1")
        install(FILES include/unicode_categories.re DESTINATION "${RE2C_STDLIB_DIR}")
    endif()

    if(RE2C_REBUILD_DOCS)
        add_custom_target(docs DEPENDS
            "${CMAKE_CURRENT_BINARY_DIR}/doc/re2c.1"
            "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help.cc"
        )
    else()
        add_custom_target(docs
            COMMAND cmake -E echo "Reconfigure to rebuild docs: cmake -DRE2C_REBUILD_DOCS=YES"
            COMMAND cmake -E false
        )
    endif()

    # rebuild all re2c sources using newly built re2c
    add_custom_target(bootstrap
        COMMAND cmake -E remove_directory "src"
        COMMAND cmake -E remove_directory "doc/re2c.1"
        COMMAND cmake --build "${CMAKE_CURRENT_BINARY_DIR}"
    )

    # tests
    add_custom_target(tests
        DEPENDS "${RE2C_RUN_TESTS}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND "${RE2C_RUN_TESTS}"
    )
    add_dependencies(tests re2c)
    add_custom_target(vtests
        DEPENDS "${RE2C_RUN_TESTS}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND "${RE2C_RUN_TESTS}" --valgrind
    )
    add_dependencies(vtests re2c)
    add_custom_target(wtests
        DEPENDS "${RE2C_RUN_TESTS}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND "${RE2C_RUN_TESTS}" --wine -j1
    )
    add_dependencies(wtests re2c)
    add_executable(re2c_test_range
        src/test/range/test-impl.h
        src/test/range/test.cc
        src/test/range/test.h
        src/util/range.cc
        src/util/range.h
        src/util/static_assert.h
    )
    add_executable(re2c_test_s_to_n32_unsafe
        src/test/s_to_n32_unsafe/test.cc
        src/util/s_to_n32_unsafe.cc
    )
    add_executable(re2c_test_ver_to_vernum
        src/test/ver_to_vernum/test.cc
        $<TARGET_OBJECTS:re2c_generated_ver_to_vernum>
    )
    add_custom_target(check_re2c
        COMMAND ./re2c_test_range
        COMMAND ./re2c_test_s_to_n32_unsafe
        COMMAND ./re2c_test_ver_to_vernum
    )
    add_dependencies(check_re2c
        tests
        re2c_test_range
        re2c_test_s_to_n32_unsafe
        re2c_test_ver_to_vernum
    )
endif()

if (RE2C_BUILD_LIBS)
    add_library(libre2c_objects OBJECT
        lib/regcomp.cc
        lib/regexec.cc
        lib/regexec_dfa.cc
        lib/regexec_nfa_leftmost.cc
        lib/regexec_nfa_leftmost_trie.cc
        lib/regexec_nfa_posix.cc
        lib/regexec_nfa_posix_trie.cc
        lib/regexec_nfa_posix_backward.cc
        lib/regexec_nfa_posix_kuklewicz.cc
        lib/regfree.cc
        lib/stubs.cc
        src/parse/ast.cc
        src/parse/unescape.cc
        src/options/opt.cc
        src/cfg/cfg.cc
        src/cfg/compact.cc
        src/cfg/dce.cc
        src/cfg/freeze.cc
        src/cfg/interfere.cc
        src/cfg/liveanal.cc
        src/cfg/normalize.cc
        src/cfg/optimize.cc
        src/cfg/rename.cc
        src/cfg/varalloc.cc
        src/dfa/closure.cc
        src/debug/dump_adfa.cc
        src/debug/dump_cfg.cc
        src/debug/dump_dfa.cc
        src/debug/dump_dfa_tree.cc
        src/debug/dump_interf.cc
        src/debug/dump_nfa.cc
        src/dfa/dead_rules.cc
        src/dfa/determinization.cc
        src/dfa/fallback_tags.cc
        src/dfa/fillpoints.cc
        src/dfa/find_state.cc
        src/dfa/minimization.cc
        src/dfa/stacmd.cc
        src/dfa/tagver_table.cc
        src/dfa/tcmd.cc
        src/nfa/estimate_size.cc
        src/nfa/re_to_nfa.cc
        src/encoding/enc.cc
        src/encoding/range_suffix.cc
        src/encoding/ebcdic/ebcdic_regexp.cc
        src/encoding/utf16/utf16.cc
        src/encoding/utf16/utf16_regexp.cc
        src/encoding/utf8/utf8.cc
        src/encoding/utf8/utf8_regexp.cc
        src/msg/msg.cc
        src/msg/warn.cc
        src/regexp/ast_to_re.cc
        src/regexp/default_tags.cc
        src/regexp/fixed_tags.cc
        src/regexp/nullable.cc
        src/regexp/rule.cc
        src/regexp/split_charset.cc
        src/regexp/tag.cc
        src/skeleton/control_flow.cc
        src/skeleton/maxpath.cc
        src/skeleton/skeleton.cc
        src/util/range.cc
        src/util/s_to_n32_unsafe.cc
        "${CMAKE_CURRENT_BINARY_DIR}/lib/lex.cc"
        "${CMAKE_CURRENT_BINARY_DIR}/lib/parse.cc"
    )
    set(libre2c_sources $<TARGET_OBJECTS:libre2c_objects> $<TARGET_OBJECTS:re2c_generated_ver_to_vernum>)

    # on Windows add suffix to static libs to avoid collision of .lib files with shared libs
    set(RE2C_STATIC_LIB_SFX "$<$<PLATFORM_ID:Windows>:_static>")

    # build static libraries
    if ((NOT DEFINED BUILD_SHARED_LIBS) OR (NOT BUILD_SHARED_LIBS))
        add_library(libre2c_static STATIC ${libre2c_sources})
        set_target_properties(libre2c_static PROPERTIES OUTPUT_NAME "re2c${RE2C_STATIC_LIB_SFX}")
        if (UNIX)
            install(TARGETS libre2c_static ARCHIVE DESTINATION lib)
        endif()
    endif()

    # build shared libraries
    if ((NOT DEFINED BUILD_SHARED_LIBS) OR BUILD_SHARED_LIBS)
        add_library(libre2c_shared SHARED ${libre2c_sources})
        set_target_properties(libre2c_shared PROPERTIES OUTPUT_NAME "re2c")
        if (UNIX)
            install(TARGETS libre2c_shared LIBRARY DESTINATION lib)
        endif()
    endif()

    # define top-level aliases to either static or shared libraries (default is static)
    if (BUILD_SHARED_LIBS)
        add_library(libre2c ALIAS libre2c_shared)
    else()
        add_library(libre2c ALIAS libre2c_static)
    endif()

    re2c_bootstrap_lexer("lib/lex.re" "lib/lex.cc")
    re2c_bootstrap_parser("lib/parse.ypp" "lib/parse.cc" "lib/parse.h")

    add_executable(test_libre2c lib/test.cc)
    target_link_libraries(test_libre2c libre2c)
    add_custom_target(check_libre2c
        COMMAND ./test_libre2c
    )

    add_executable(bench_libre2c lib/bench.cc)
    set_property(TARGET bench_libre2c PROPERTY CXX_STANDARD 11)
    target_link_libraries(bench_libre2c libre2c)

    find_path(RE2_INCLUDE_DIRECTORY "re2/re2.h")
    find_library(RE2_LIBRARY "re2")
    if (RE2_INCLUDE_DIRECTORY AND RE2_LIBRARY)
        target_compile_definitions(bench_libre2c PRIVATE "HAVE_RE2_RE_H=1")
        target_include_directories(bench_libre2c PRIVATE "${RE2_INCLUDE_DIRECTORY}")
        target_link_libraries(bench_libre2c "${RE2_LIBRARY}")
    endif()
else()
    # empty check target
    add_custom_target(check_libre2c)
endif()

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    add_custom_target(check)
    add_dependencies(check
        check_re2c
        check_libre2c
    )
endif()
