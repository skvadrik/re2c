AC_INIT([re2c],[3.1],[re2c-general@lists.sourceforge.net])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign subdir-objects dist-xz dist-lzip no-dist-gzip])
AM_SILENT_RULES([yes])


AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])


AC_SUBST(PACKAGE_VERSION)
AC_SUBST(PACKAGE_NAME)
AC_SUBST(PACKAGE_TARNAME)
AC_SUBST(PACKAGE_RELEASE, ${PACKAGE_RELEASE:-1})

AM_PATH_PYTHON([3.7])

# without this, --std=c++11 disables POSIX functions on Cygwin and NetBSD
# (alternatively we could use -std=gnu++11, as CMake does)
AC_USE_SYSTEM_EXTENSIONS


# --enable-debug
AC_ARG_ENABLE([debug], [AS_HELP_STRING([--enable-debug],
    [enable checks and assertions])])
AM_CONDITIONAL([DEBUG], [test "x$enable_debug" = "xyes"])


# --enable-docs
AC_ARG_ENABLE([docs], [AS_HELP_STRING([--enable-docs], [regenerate manpage])])
AM_CONDITIONAL([REBUILD_DOCS], [test "x$enable_docs" = "xyes"])
AM_COND_IF([REBUILD_DOCS], [
        AS_IF([$PYTHON -c "import docutils"], [], [
           AC_MSG_ERROR([need docutils (python3 module) for --enable-docs])
    ])
])


# --enable-syntax
AC_ARG_ENABLE([syntax], [AS_HELP_STRING([--enable-syntax], [regenerate syntax files])])
AM_CONDITIONAL([REBUILD_SYNTAX], [test "x$enable_syntax" = "xyes"])


# --enable-lexers
AC_ARG_ENABLE([lexers], [AS_HELP_STRING([--enable-lexers], [regenerate lexers])])
AM_CONDITIONAL([REBUILD_LEXERS], [test "x$enable_lexers" = "xyes"])
AM_COND_IF([REBUILD_LEXERS], [
    AC_ARG_VAR(RE2C_FOR_BUILD, re2c executable used to regenerate lexers)
    AS_IF([test ! -x "$RE2C_FOR_BUILD"], [
        AC_MSG_ERROR([RE2C_FOR_BUILD must be set to an executable file with --enable-lexers])
    ])
])


# --enable-parsers
AC_PATH_PROG(BISON, bison, no)
AC_ARG_ENABLE([parsers], [AS_HELP_STRING([--enable-parsers], [regenerate parsers with Bison])])
AM_CONDITIONAL([REBUILD_PARSERS], [test "x$enable_parsers" = "xyes"])
AM_COND_IF([REBUILD_PARSERS], [
    AS_IF([test "$BISON" = "no" ], [
        AC_MSG_ERROR([need Bison for --enable-parsers])
    ])
])


# --enable-libs
AC_ARG_ENABLE([libs], [AS_HELP_STRING([--enable-libs], [build libraries])])
AM_CONDITIONAL([WITH_LIBS], [test "x$enable_libs" = "xyes"])
AM_COND_IF([WITH_LIBS], [
    AC_SUBST(LDFLAGS_RE2, [])
    AC_LANG_PUSH([C++])
    AC_CHECK_HEADERS([re2/re2.h], [AS_VAR_SET([LDFLAGS_RE2], ["-lre2"])], [], [[]])
    AC_LANG_POP([C++])
])


# --enable-golang
AC_ARG_ENABLE([golang], [AS_HELP_STRING([--enable-golang], [build re2go executable])])
AM_CONDITIONAL([WITH_GOLANG], [test "x$enable_golang" != "xno"])


# --enable-rust
AC_ARG_ENABLE([rust], [AS_HELP_STRING([--enable-rust], [build re2rust executable])])
AM_CONDITIONAL([WITH_RUST], [test "x$enable_rust" != "xno"])


# --enable-benchmarks
AC_ARG_ENABLE([benchmarks], [AS_HELP_STRING([--enable-benchmarks],
    [build benchmarks])])
AM_CONDITIONAL([WITH_BENCHMARKS], [test "x$enable_benchmarks" = "xyes"])
AM_COND_IF([WITH_BENCHMARKS], [
    AC_LANG_PUSH([C++])
    AC_CHECK_HEADERS([benchmark/benchmark.h], [],
        [AC_MSG_ERROR([benchmark library is required with --enable-benchmarks])], [[]])
    AC_LANG_POP([C++])
])
AM_CONDITIONAL([WITH_JAVA], [test -n "$JAVA_HOME"])


# --enable-benchmarks-regenerate
AC_ARG_ENABLE([benchmarks_regenerate],
    [AS_HELP_STRING([--enable-benchmarks-regenerate],
    [regenerate C code for benchmarks])])
AM_CONDITIONAL([REGEN_BENCHMARKS],
    [test "x$enable_benchmarks_regenerate" = "xyes"])


# checks for programs
AC_PROG_CC # used in skeleton tests
AC_PROG_CXX
AC_PROG_INSTALL


# checks for C++ compiler flags
AC_SUBST(CXXFLAGSDEFAULT, [])
# TRY_CXXFLAG (flag [implied-flags])
# Iff C++ compiler recognizes 'flag', append 'flag' and 'implied-flags' to CXXFLAGSDEFAULT
# (Second param 'implied-flags' is needed for warning suppressions '-Wno-<warning>':
# GCC warns about unrecognized suppressions options only in presence of other warnings,
# which makes it hard to test for them with autoconf.)
AC_DEFUN([TRY_CXXFLAG], [
    AC_MSG_CHECKING([C++ compiler flag $1])
    AS_VAR_SET([CXXFLAGS_BACKUP], ["$CXXFLAGS"])
    AS_VAR_SET([CXXFLAGS], ["$CXXFLAGS $1"])
    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM()],
        [
            AS_VAR_SET([TRY_CXXFLAG_RESULT], [yes])
            AS_VAR_SET([CXXFLAGSDEFAULT], ["$CXXFLAGSDEFAULT $1 $2"])
        ],
        [
            AS_VAR_SET([TRY_CXXFLAG_RESULT], [no])
            AS_IF([test "x$3" = "xrequired"], [
                AC_MSG_ERROR([C++ compiler flag $1 is required to build re2c])
            ])
        ]
    )
    AC_LANG_POP([C++])
    AS_VAR_SET([CXXFLAGS], ["$CXXFLAGS_BACKUP"])
    AC_MSG_RESULT([$TRY_CXXFLAG_RESULT])
])
TRY_CXXFLAG([-std=c++11], [], [required])
TRY_CXXFLAG([-W])
TRY_CXXFLAG([-Wall])
TRY_CXXFLAG([-Wextra])
TRY_CXXFLAG([-Weffc++])
TRY_CXXFLAG([-pedantic])
TRY_CXXFLAG([-Wformat=2])
TRY_CXXFLAG([-Wredundant-decls])
TRY_CXXFLAG([-Wsuggest-attribute=format])
TRY_CXXFLAG([-Wconversion])
TRY_CXXFLAG([-Wsign-conversion])
TRY_CXXFLAG([-Wold-style-cast])
TRY_CXXFLAG([-Werror=return-type])
TRY_CXXFLAG([-O2])
TRY_CXXFLAG([-Weverything], m4_join([ ],
    [-Wno-unknown-warning-option], dnl CLANG eats some GCC options only to warn they are unknown
    [-Wno-reserved-id-macro], dnl to allow header guards of the form '_RE2C_PATH_TO_HEADER_BASENAME_'
    [-Wno-padded],
    [-Wno-nested-anon-types],
    [-Wno-reserved-identifier], dnl user-defined literals like `_u8` must start with underscore
    [-Wno-shadow-field-in-constructor] dnl using same names in ctor seems more like a feature
    [-Wno-undefined-func-template] dnl explicit specialization to reduce build dependencies
    [-Wno-c++98-compat], dnl allow using C++11 features like `nullptr`
    [-Wno-c++98-compat-pedantic]))


# needed for POSIX file API
AC_CHECK_HEADERS([sys/types.h], [], [], [[]])
AC_CHECK_HEADERS([sys/stat.h],  [], [], [[]])
AC_CHECK_HEADERS([fcntl.h],     [], [], [[]])
AC_CHECK_HEADERS([unistd.h],    [], [], [[]])
AC_CHECK_HEADERS([io.h],        [], [], [[]]) # windows POSIX-like API


AC_CONFIG_FILES([
    Makefile
    benchmarks/submatch_nfa/Makefile
    benchmarks/submatch_dfa_aot/Makefile
    benchmarks/submatch_dfa_jit/Makefile
    benchmarks/submatch_java/Makefile
    doc/manpage.rst
    doc/help.rst
])
AC_CONFIG_FILES([run_tests.py],
    [chmod +x run_tests.py])
AC_CONFIG_FILES([benchmarks/submatch_dfa_aot/run.py],
    [chmod +x benchmarks/submatch_dfa_aot/run.py])
AC_CONFIG_FILES([benchmarks/submatch_java/run.py],
    [chmod +x benchmarks/submatch_java/run.py])


AC_CONFIG_LINKS([benchmarks/submatch_java/chart.js:benchmarks/submatch_java/chart.js])


LT_INIT([dlopen win32-dll])
AC_CONFIG_MACRO_DIRS([m4])


AC_OUTPUT
