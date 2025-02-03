cmake_minimum_required(VERSION 3.15)
project(re2c VERSION 4.0.2 HOMEPAGE_URL "https://re2c.org/")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(Re2cAutotoolsHelpers)
include(Re2cBootstrapLexer)
include(Re2cBootstrapParser)
include(Re2cBootstrapSyntax)
include(Re2cBuildType)
include(Re2cGenDocs)
include(Re2cCompilerFlags)

ac_subst(PACKAGE_VERSION "${PROJECT_VERSION}")

# check whether re2c is the root project
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(RE2C_IS_ROOT_PROJECT TRUE)
else()
    set(RE2C_IS_ROOT_PROJECT FALSE)
endif()

option(RE2C_REBUILD_LEXERS "Regenerate lexers" OFF)
if(RE2C_REBUILD_LEXERS AND NOT RE2C_FOR_BUILD)
    message(FATAL_ERROR "option RE2C_FOR_BUILD is required for RE2C_REBUILD_LEXERS")
endif()

option(RE2C_REBUILD_PARSERS "Regenerate parsers with Bison" OFF)
if(RE2C_REBUILD_PARSERS AND NOT RE2C_FOR_BUILD)
    find_package(BISON REQUIRED)
endif()

option(RE2C_REBUILD_SYNTAX "Regenerate default syntax files" OFF)
option(RE2C_REBUILD_DOCS "Regenerate manpage" OFF)
option(RE2C_BUILD_LIBS "Build libraries" OFF)

option(RE2C_BUILD_RE2D "Build re2d executable (an alias for `re2c --lang d`)" ON)
option(RE2C_BUILD_RE2GO "Build re2go executable (an alias for `re2c --lang go`)" ON)
option(RE2C_BUILD_RE2HS "Build re2hs executable (an alias for `re2c --lang haskell`)" ON)
option(RE2C_BUILD_RE2JAVA "Build re2java executable (an alias for `re2c --lang java`)" ON)
option(RE2C_BUILD_RE2JS "Build re2js executable (an alias for `re2c --lang js`)" ON)
option(RE2C_BUILD_RE2OCAML "Build re2ocaml executable (an alias for `re2c --lang ocaml`)" ON)
option(RE2C_BUILD_RE2PY "Build re2py executable (an alias for `re2c --lang python`)" ON)
option(RE2C_BUILD_RE2RUST "Build re2rust executable (an alias for `re2c --lang rust`)" ON)
option(RE2C_BUILD_RE2V "Build re2v executable (an alias for `re2c --lang v`)" ON)
option(RE2C_BUILD_RE2ZIG "Build re2zig executable (an alias for `re2c --lang zig`)" ON)

option(RE2C_BUILD_BENCHMARKS "Build benchmarks" OFF)
option(RE2C_REGEN_BENCHMARKS "Regenerate C code for benchmarks" OFF)

# test targets are enabled by default only if re2c is the root project
option(RE2C_BUILD_TESTS "Build tests" "${RE2C_IS_ROOT_PROJECT}")

# checks for programs
if(RE2C_REBUILD_DOCS OR RE2C_BUILD_TESTS OR RE2C_BUILD_BENCHMARKS)
    find_package(Python3 3.7 REQUIRED COMPONENTS Interpreter)
endif()

if(RE2C_REBUILD_DOCS)
    execute_process(
        COMMAND "${Python3_EXECUTABLE}" -c "import docutils"
        RESULT_VARIABLE EXIT_CODE
        OUTPUT_QUIET
    )
    if (NOT ${EXIT_CODE} EQUAL 0)
        message(FATAL_ERROR "python package docutils (needed for docs) not found")
    endif()
endif()

# Use C++11 standard. Note that without `set(CMAKE_CXX_EXTENSIONS OFF)` this enables
# -std=gnu++11, not -std=c++11. Extensions are needed to enable POSIX functions on
# Cygwin and NetBSD.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # fail if the C++ compiler does not support this standard
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # make sure object libraries work with shared libraries

# needed for POSIX file API
ac_check_headers("sys/types.h")
ac_check_headers("sys/stat.h")
ac_check_headers("fcntl.h")
ac_check_headers("unistd.h")
# windows POSIX-like API
ac_check_headers("io.h")

# docs (manpages and help)
set(re2c_manpage_source  "${CMAKE_CURRENT_BINARY_DIR}/doc/manpage.rst")
set(re2c_help_source     "${CMAKE_CURRENT_BINARY_DIR}/doc/help.rst")
set(re2c_manpage_c       "${CMAKE_CURRENT_BINARY_DIR}/doc/re2c.1")
set(re2c_manpage_d       "${CMAKE_CURRENT_BINARY_DIR}/doc/re2d.1")
set(re2c_manpage_go      "${CMAKE_CURRENT_BINARY_DIR}/doc/re2go.1")
set(re2c_manpage_haskell "${CMAKE_CURRENT_BINARY_DIR}/doc/re2hs.1")
set(re2c_manpage_java    "${CMAKE_CURRENT_BINARY_DIR}/doc/re2java.1")
set(re2c_manpage_js      "${CMAKE_CURRENT_BINARY_DIR}/doc/re2js.1")
set(re2c_manpage_ocaml   "${CMAKE_CURRENT_BINARY_DIR}/doc/re2ocaml.1")
set(re2c_manpage_python  "${CMAKE_CURRENT_BINARY_DIR}/doc/re2py.1")
set(re2c_manpage_rust    "${CMAKE_CURRENT_BINARY_DIR}/doc/re2rust.1")
set(re2c_manpage_v       "${CMAKE_CURRENT_BINARY_DIR}/doc/re2v.1")
set(re2c_manpage_zig     "${CMAKE_CURRENT_BINARY_DIR}/doc/re2zig.1")
set(re2c_help_c          "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2c.cc")
set(re2c_help_d          "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2d.cc")
set(re2c_help_go         "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2go.cc")
set(re2c_help_haskell    "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2hs.cc")
set(re2c_help_java       "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2java.cc")
set(re2c_help_js         "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2js.cc")
set(re2c_help_ocaml      "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2ocaml.cc")
set(re2c_help_python     "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2py.cc")
set(re2c_help_rust       "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2rust.cc")
set(re2c_help_v          "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2v.cc")
set(re2c_help_zig        "${CMAKE_CURRENT_BINARY_DIR}/src/msg/help_re2zig.cc")
set(re2c_rst2man         "${CMAKE_CURRENT_SOURCE_DIR}/build/rst2man.py")
set(re2c_rst2txt         "${CMAKE_CURRENT_SOURCE_DIR}/build/rst2txt.py")
set(re2c_splitman        "${CMAKE_CURRENT_SOURCE_DIR}/build/split_man.py")
set(re2c_docs
    "${re2c_manpage_c}"
    "$<$<BOOL:${RE2C_BUILD_RE2D}>:${re2c_manpage_d}>"
    "$<$<BOOL:${RE2C_BUILD_RE2GO}>:${re2c_manpage_go}>"
    "$<$<BOOL:${RE2C_BUILD_RE2HS}>:${re2c_manpage_haskell}>"
    "$<$<BOOL:${RE2C_BUILD_RE2JAVA}>:${re2c_manpage_java}>"
    "$<$<BOOL:${RE2C_BUILD_RE2JS}>:${re2c_manpage_js}>"
    "$<$<BOOL:${RE2C_BUILD_RE2OCAML}>:${re2c_manpage_ocaml}>"
    "$<$<BOOL:${RE2C_BUILD_RE2PY}>:${re2c_manpage_python}>"
    "$<$<BOOL:${RE2C_BUILD_RE2RUST}>:${re2c_manpage_rust}>"
    "$<$<BOOL:${RE2C_BUILD_RE2V}>:${re2c_manpage_v}>"
    "$<$<BOOL:${RE2C_BUILD_RE2ZIG}>:${re2c_manpage_zig}>"
)

# syntax files
set(re2c_stx2cpp "${CMAKE_CURRENT_SOURCE_DIR}/build/stx2cpp.py")

set(top_srcdir "${CMAKE_CURRENT_SOURCE_DIR}")
set(top_builddir "${CMAKE_CURRENT_BINARY_DIR}")
set(PYTHON "${Python3_EXECUTABLE}")

configure_file(doc/manpage.rst.in doc/manpage.rst @ONLY)
configure_file(doc/help.rst.in doc/help.rst @ONLY)

if(RE2C_BUILD_TESTS)
    configure_file(run_tests.py.in run_tests.py @ONLY)
    set(RE2C_RUN_TESTS "${CMAKE_CURRENT_BINARY_DIR}/run_tests.py")
    if(CMAKE_HOST_UNIX)
        execute_process(COMMAND chmod +x "${RE2C_RUN_TESTS}")
    endif()
endif()

ac_config_headers("config.h")

# Makefile.am
set(RE2C_STDLIB_DIR "${CMAKE_INSTALL_PREFIX}/share/re2c/stdlib")
add_compile_definitions(
  "RE2C_STDLIB_DIR=\"${RE2C_STDLIB_DIR}\""
  $<$<CONFIG:Debug>:RE2C_DEBUG>
)
include_directories(. "${CMAKE_CURRENT_BINARY_DIR}")

# Build autogenerated sources into an object library to ensure that they are
# generated once at the beginning of build (as with Automake BUILT_SOURCES).
# WARNING: custom target that depends on autogenerated sources won't do here
# as its dependencies get built multiple times, which ruins parallel builds.
add_library(re2c_objects_autogen OBJECT
    "${CMAKE_CURRENT_BINARY_DIR}/src/options/parse_opts.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/lexer.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/lexer.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/parser.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/parser.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/conf_lexer.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/conf_parser.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/src/parse/conf_parser.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_c.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_d.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_go.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_haskell.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_java.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_js.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_ocaml.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_python.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_rust.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_v.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/default_syntax_zig.h"
    "${re2c_docs}"
)
add_library(re2c_objects_autogen_ver_to_vernum OBJECT
    "${CMAKE_CURRENT_BINARY_DIR}/src/msg/ver_to_vernum.cc"
)

set(re2c_sources
    src/codegen/helpers.cc
    src/codegen/output.cc
    src/codegen/pass1_analyze.cc
    src/codegen/pass2_generate.cc
    src/codegen/pass3_fixup.cc
    src/codegen/pass4_render.cc
    src/options/opt.cc
    src/options/symtab.cc
    src/nfa/re_to_nfa.cc
    src/adfa/adfa.cc
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
    src/dfa/tagver_table.cc
    src/dfa/tcmd.cc
    src/encoding/ebcdic.cc
    src/encoding/enc.cc
    src/encoding/range_suffix.cc
    src/encoding/utf8.cc
    src/encoding/utf16.cc
    src/msg/msg.cc
    src/msg/warn.cc
    src/regexp/ast_to_re.cc
    src/regexp/default_tags.cc
    src/regexp/fixed_tags.cc
    src/regexp/nullable.cc
    src/regexp/regexp.cc
    src/regexp/split_charset.cc
    src/skeleton/control_flow.cc
    src/skeleton/generate_code.cc
    src/skeleton/generate_data.cc
    src/skeleton/maxpath.cc
    src/skeleton/skeleton.cc
    src/parse/ast.cc
    src/parse/input.cc
    src/util/file_utils.cc
    src/util/string_utils.cc
    src/util/range.cc
    src/main.cc
    $<TARGET_OBJECTS:re2c_objects_autogen>
    $<TARGET_OBJECTS:re2c_objects_autogen_ver_to_vernum>
)

re2c_bootstrap_lexer("src/msg/ver_to_vernum.re" "src/msg/ver_to_vernum.cc")
re2c_bootstrap_lexer("src/options/parse_opts.re" "src/options/parse_opts.cc")
re2c_bootstrap_lexer("src/parse/lexer.re" "src/parse/lexer.cc" "src/parse/lexer.h")
re2c_bootstrap_parser("src/parse/parser.ypp" "src/parse/parser.cc" "src/parse/parser.h")
re2c_bootstrap_lexer("src/parse/conf_lexer.re" "src/parse/conf_lexer.cc")
re2c_bootstrap_parser("src/parse/conf_parser.ypp" "src/parse/conf_parser.cc" "src/parse/conf_parser.h")

re2c_bootstrap_syntax("include/syntax/c" "src/default_syntax_c.h")
re2c_bootstrap_syntax("include/syntax/d" "src/default_syntax_d.h")
re2c_bootstrap_syntax("include/syntax/go" "src/default_syntax_go.h")
re2c_bootstrap_syntax("include/syntax/haskell" "src/default_syntax_haskell.h")
re2c_bootstrap_syntax("include/syntax/java" "src/default_syntax_java.h")
re2c_bootstrap_syntax("include/syntax/js" "src/default_syntax_js.h")
re2c_bootstrap_syntax("include/syntax/ocaml" "src/default_syntax_ocaml.h")
re2c_bootstrap_syntax("include/syntax/python" "src/default_syntax_python.h")
re2c_bootstrap_syntax("include/syntax/rust" "src/default_syntax_rust.h")
re2c_bootstrap_syntax("include/syntax/v" "src/default_syntax_v.h")
re2c_bootstrap_syntax("include/syntax/zig" "src/default_syntax_zig.h")

# docs
file(GLOB_RECURSE re2c_docs_sources CONFIGURE_DEPENDS
    "examples/*"
    "doc/manual/*"
    "${re2c_manpage_source}"
)
re2c_gen_help("${re2c_help_source}" "${re2c_help_c}")
re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_c}")
add_custom_target(docs DEPENDS "${re2c_docs}")

# re2c
add_executable(re2c ${re2c_sources} "${re2c_help_c}")

# re2d
if (RE2C_BUILD_RE2D)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_d}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_d}")
    add_executable(re2d ${re2c_sources} "${re2c_help_d}")
    target_compile_definitions(re2d PUBLIC
        "RE2C_LANG=Lang::D"
        "RE2C_PROG=\"re2d\""
    )
endif()

# re2go
if (RE2C_BUILD_RE2GO)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_go}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_go}")
    add_executable(re2go ${re2c_sources} "${re2c_help_go}")
    target_compile_definitions(re2go PUBLIC
        "RE2C_LANG=Lang::GO"
        "RE2C_PROG=\"re2go\""
    )
endif()

# re2hs
if (RE2C_BUILD_RE2HS)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_haskell}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_haskell}")
    add_executable(re2hs ${re2c_sources} "${re2c_help_haskell}")
    target_compile_definitions(re2hs PUBLIC
        "RE2C_LANG=Lang::HASKELL"
        "RE2C_PROG=\"re2hs\""
    )
endif()

# re2java
if (RE2C_BUILD_RE2JAVA)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_java}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_java}")
    add_executable(re2java ${re2c_sources} "${re2c_help_java}")
    target_compile_definitions(re2java PUBLIC
        "RE2C_LANG=Lang::JAVA"
        "RE2C_PROG=\"re2java\""
    )
endif()

# re2js
if (RE2C_BUILD_RE2JS)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_js}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_js}")
    add_executable(re2js ${re2c_sources} "${re2c_help_js}")
    target_compile_definitions(re2js PUBLIC
        "RE2C_LANG=Lang::JS"
        "RE2C_PROG=\"re2js\""
    )
endif()

# re2ocaml
if (RE2C_BUILD_RE2OCAML)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_ocaml}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_ocaml}")
    add_executable(re2ocaml ${re2c_sources} "${re2c_help_ocaml}")
    target_compile_definitions(re2ocaml PUBLIC
        "RE2C_LANG=Lang::OCAML"
        "RE2C_PROG=\"re2ocaml\""
    )
endif()

# re2py
if (RE2C_BUILD_RE2PY)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_python}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_python}")
    add_executable(re2py ${re2c_sources} "${re2c_help_python}")
    target_compile_definitions(re2py PUBLIC
        "RE2C_LANG=Lang::PYTHON"
        "RE2C_PROG=\"re2py\""
    )
endif()

# re2rust
if (RE2C_BUILD_RE2RUST)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_rust}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_rust}")
    add_executable(re2rust ${re2c_sources} "${re2c_help_rust}")
    target_compile_definitions(re2rust PUBLIC
        "RE2C_LANG=Lang::RUST"
        "RE2C_PROG=\"re2rust\""
    )
endif()

# re2v
if (RE2C_BUILD_RE2V)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_v}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_v}")
    add_executable(re2v ${re2c_sources} "${re2c_help_v}")
    target_compile_definitions(re2v PUBLIC
        "RE2C_LANG=Lang::V"
        "RE2C_PROG=\"re2v\""
    )
endif()

# re2zig
if (RE2C_BUILD_RE2ZIG)
    re2c_gen_help("${re2c_help_source}" "${re2c_help_zig}")
    re2c_gen_manpage("${re2c_manpage_source}" "${re2c_manpage_zig}")
    add_executable(re2zig ${re2c_sources} "${re2c_help_zig}")
    target_compile_definitions(re2zig PUBLIC
        "RE2C_LANG=Lang::ZIG"
        "RE2C_PROG=\"re2zig\""
    )
endif()

# install targets are enabled only if re2c is the root project
if(RE2C_IS_ROOT_PROJECT)
    # install
    install(TARGETS re2c RUNTIME DESTINATION bin)
    install(FILES "${re2c_manpage_c}" DESTINATION "share/man/man1")
    if(RE2C_BUILD_RE2D)
        install(TARGETS re2d RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_d}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2GO)
        install(TARGETS re2go RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_go}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2HS)
        install(TARGETS re2hs RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_haskell}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2JAVA)
        install(TARGETS re2java RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_java}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2JS)
        install(TARGETS re2js RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_js}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2OCAML)
        install(TARGETS re2ocaml RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_ocaml}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2PY)
        install(TARGETS re2py RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_python}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2RUST)
        install(TARGETS re2rust RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_rust}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2V)
        install(TARGETS re2v RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_v}" DESTINATION "share/man/man1")
    endif()
    if(RE2C_BUILD_RE2ZIG)
        install(TARGETS re2zig RUNTIME DESTINATION bin)
        install(FILES "${re2c_manpage_zig}" DESTINATION "share/man/man1")
    endif()
    install(FILES
        include/syntax/c
        include/syntax/d
        include/syntax/go
        include/syntax/haskell
        include/syntax/java
        include/syntax/js
        include/syntax/ocaml
        include/syntax/python
        include/syntax/rust
        include/syntax/v
        include/syntax/zig
        include/unicode_categories.re
        DESTINATION "${RE2C_STDLIB_DIR}")

    # rebuild all re2c sources using newly built re2c
    add_custom_target(bootstrap
        COMMAND "${CMAKE_COMMAND}" -E remove_directory "src"
        COMMAND "${CMAKE_COMMAND}" -E remove_directory "doc"
        COMMAND "${CMAKE_COMMAND}" --build "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()

if(RE2C_BUILD_TESTS)
    # tests
    add_custom_target(tests
        DEPENDS "${RE2C_RUN_TESTS}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND "${Python3_EXECUTABLE}" "${RE2C_RUN_TESTS}"
    )
    add_dependencies(tests re2c)
    add_custom_target(vtests
        DEPENDS "${RE2C_RUN_TESTS}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND "${Python3_EXECUTABLE}" "${RE2C_RUN_TESTS}" --valgrind
    )
    add_dependencies(vtests re2c)
    add_custom_target(wtests
        DEPENDS "${RE2C_RUN_TESTS}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND "${Python3_EXECUTABLE}" "${RE2C_RUN_TESTS}" --wine -j1
    )
    add_dependencies(wtests re2c)
    add_executable(re2c_test_list
        src/test/list/test.cc
    )
    add_executable(re2c_test_range
        src/test/range/test-impl.h
        src/test/range/test.cc
        src/test/range/test.h
        src/util/range.cc
        src/util/range.h
    )
    add_executable(re2c_test_s_to_n32_unsafe
        src/test/s_to_n32_unsafe/test.cc
        src/util/string_utils.cc
    )
    add_executable(re2c_test_ver_to_vernum
        src/test/ver_to_vernum/test.cc
        $<TARGET_OBJECTS:re2c_objects_autogen_ver_to_vernum>
    )
    add_executable(re2c_test_argsubst
        src/test/argsubst/test.cc
    )
    add_custom_target(check_re2c
        COMMAND ./re2c_test_list
        COMMAND ./re2c_test_range
        COMMAND ./re2c_test_s_to_n32_unsafe
        COMMAND ./re2c_test_ver_to_vernum
        COMMAND ./re2c_test_argsubst
    )
    add_dependencies(check_re2c
        tests
        re2c_test_range
        re2c_test_s_to_n32_unsafe
        re2c_test_ver_to_vernum
        re2c_test_argsubst
    )
endif()

if (RE2C_BUILD_LIBS)
    # Build autogenerated sources into an object library to ensure that they are
    # generated once at the beginning of build (as with Automake BUILT_SOURCES).
    # WARNING: custom target that depends on autogenerated sources won't do here
    # as its dependencies get built multiple times, which ruins parallel builds.
    add_library(libre2c_objects_autogen OBJECT
        "${CMAKE_CURRENT_BINARY_DIR}/lib/lex.cc"
        "${CMAKE_CURRENT_BINARY_DIR}/lib/parse.cc"
    )
    re2c_bootstrap_lexer("lib/lex.re" "lib/lex.cc")
    re2c_bootstrap_parser("lib/parse.ypp" "lib/parse.cc" "lib/parse.h")

    add_library(test_libre2c_objects_autogen OBJECT
        "${CMAKE_CURRENT_BINARY_DIR}/lib/test_helper.cc"
    )
    re2c_bootstrap_lexer("lib/test_helper.re" "lib/test_helper.cc")

    set(libre2c_sources
        lib/regcomp.cc
        lib/regexec.cc
        lib/regexec_dfa.cc
        lib/regexec_dfa_multipass.cc
        lib/regexec_nfa_leftmost.cc
        lib/regexec_nfa_leftmost_trie.cc
        lib/regexec_nfa_posix.cc
        lib/regexec_nfa_posix_trie.cc
        lib/regfree.cc
        lib/stubs.cc
        src/parse/ast.cc
        src/parse/input.cc
        src/options/opt.cc
        src/options/symtab.cc
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
        src/dfa/tagver_table.cc
        src/dfa/tcmd.cc
        src/nfa/re_to_nfa.cc
        src/encoding/enc.cc
        src/encoding/range_suffix.cc
        src/encoding/ebcdic.cc
        src/encoding/utf16.cc
        src/encoding/utf8.cc
        src/msg/msg.cc
        src/msg/warn.cc
        src/regexp/ast_to_re.cc
        src/regexp/default_tags.cc
        src/regexp/fixed_tags.cc
        src/regexp/nullable.cc
        src/regexp/regexp.cc
        src/regexp/split_charset.cc
        src/skeleton/control_flow.cc
        src/skeleton/maxpath.cc
        src/skeleton/skeleton.cc
        src/util/range.cc
        src/util/file_utils.cc
        src/util/string_utils.cc
        $<TARGET_OBJECTS:libre2c_objects_autogen>
        $<TARGET_OBJECTS:re2c_objects_autogen_ver_to_vernum>
    )

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

    # libre2c test
    if(RE2C_BUILD_TESTS)
        add_executable(test_libre2c lib/test.cc)
        target_link_libraries(test_libre2c libre2c)
        target_link_libraries(test_libre2c test_libre2c_objects_autogen)
        add_custom_target(check_libre2c
            COMMAND ./test_libre2c
        )
    endif()

    if(RE2C_BUILD_BENCHMARKS)
        add_subdirectory(benchmarks/c/libre2c/nfa)
        add_subdirectory(benchmarks/c/libre2c/jit)
        add_subdirectory(benchmarks/c/libre2c/java)
    endif()
else()
    # empty check target
    if(RE2C_BUILD_TESTS)
        add_custom_target(check_libre2c)
    endif()
endif()

if(RE2C_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks/c)
endif()

if(RE2C_BUILD_TESTS)
    add_custom_target(check)
    add_dependencies(check check_re2c check_libre2c)
endif()
