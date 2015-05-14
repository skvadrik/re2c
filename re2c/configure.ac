AC_INIT([re2c],[0.14.1.dev],[re2c-general@lists.sourceforge.net])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])


AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])


AC_SUBST(PACKAGE_DATE, `date +'%d %b %Y'`)
AC_SUBST(PACKAGE_VERSION)
AC_SUBST(PACKAGE_NAME)
AC_SUBST(PACKAGE_TARNAME)
AC_SUBST(PACKAGE_RELEASE, ${PACKAGE_RELEASE:-1})


# --enable-docs
AC_ARG_ENABLE([docs], [AS_HELP_STRING([--enable-docs], [regenerate man page and online documentation])])
AM_CONDITIONAL([REBUILD_DOCS], [test "x$enable_docs" = "xyes"])
AM_COND_IF([REBUILD_DOCS], [
    AC_CHECK_PROG(ASCIIDOC, asciidoc, yes, no)
    AC_CHECK_PROG(A2X, a2x, yes, no)
    AS_IF([test "x$ASCIIDOC" = "xno" -o "x$A2X" = "xno"], [
        AC_MSG_ERROR([need asciidoc and a2x for --enable-docs])
    ])
])


# checks for programs
AC_CHECK_PROG(BISON, bison, yes, no)
AC_PROG_CXX
AC_PROG_INSTALL


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


# checks for library functions
AC_CHECK_FUNCS([strdup])


AC_CONFIG_FILES([\
    Makefile \
    doc/re2c.ad \
])
AC_CONFIG_FILES([run_tests.sh], [chmod +x run_tests.sh])


AC_OUTPUT
