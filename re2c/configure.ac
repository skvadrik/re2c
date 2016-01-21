AC_INIT([re2c],[0.16],[re2c-general@lists.sourceforge.net])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_SILENT_RULES([yes])


AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])


AC_SUBST(PACKAGE_DATE, `date +'%d %b %Y'`)
AC_SUBST(PACKAGE_VERSION)
AC_SUBST(PACKAGE_NAME)
AC_SUBST(PACKAGE_TARNAME)
AC_SUBST(PACKAGE_RELEASE, ${PACKAGE_RELEASE:-1})


# --enable-docs
AC_ARG_ENABLE([docs], [AS_HELP_STRING([--enable-docs], [regenerate manpage])])
AM_CONDITIONAL([REBUILD_DOCS], [test "x$enable_docs" = "xyes"])
AM_COND_IF([REBUILD_DOCS], [
    AC_CHECK_PROGS(RST2MAN, [rst2man rst2man.py], no)
    AS_IF([test "x$RST2MAN" = "xno"], [
        AC_MSG_ERROR([need rst2man or rst2man.py for --enable-docs])
    ])
])


# checks for programs
AC_PATH_PROG(BISON, bison, no)
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
        [AS_VAR_SET([TRY_CXXFLAG_RESULT], [no])]
    )
    AC_LANG_POP([C++])
    AS_VAR_SET([CXXFLAGS], ["$CXXFLAGS_BACKUP"])
    AC_MSG_RESULT([$TRY_CXXFLAG_RESULT])
])
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
TRY_CXXFLAG([-O2])
TRY_CXXFLAG([-Weverything], m4_join([ ],
    [-Wno-unknown-warning-option],  dnl CLANG eats some GCC options only to warn they are unknown
    [-Wno-reserved-id-macro],       dnl to allow header guards of the form '_RE2C_PATH_TO_HEADER_BASENAME_'
    [-Wno-padded],                  dnl perhaps later
    [-Wno-old-style-cast],          dnl RE2C-generated lexer has lots of C-syle casts because of 're2c:yych:conversion = 1;'
    [-Wno-covered-switch-default])) dnl GCC reports false positives in some cases


# needed by src/c99_stdint.h
# avoid AC_INCLUDES_DEFAULT
AC_CHECK_HEADERS([stdint.h], [], [], [[]])
# list of possible types to use in typedefs
AC_CHECK_SIZEOF([char],      [], [[]])
AC_CHECK_SIZEOF([short],     [], [[]])
AC_CHECK_SIZEOF([int],       [], [[]])
AC_CHECK_SIZEOF([long],      [], [[]])
AC_CHECK_SIZEOF([long long], [], [[]])
AC_CHECK_SIZEOF([__int64],   [], [[]])
# size of pointers
AC_CHECK_SIZEOF([void *],    [], [[]])
# 64-bit integer constant suffix
AC_CHECK_SIZEOF([0l],        [], [[]])
AC_CHECK_SIZEOF([0ll],       [], [[]])
AC_CHECK_SIZEOF([0i8],       [], [[]])


AC_CONFIG_FILES([\
    Makefile \
    doc/manpage.rst \
])
AC_CONFIG_FILES([run_tests.sh], [chmod +x run_tests.sh])


AC_OUTPUT
