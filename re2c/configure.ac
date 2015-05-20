AC_PREREQ([2.57])
AC_INIT(re2c, 0.14.3, re2c-general@lists.sourceforge.net)
AM_INIT_AUTOMAKE(re2c, $PACKAGE_VERSION)
AC_CONFIG_SRCDIR(actions.cc)
AM_CONFIG_HEADER(config.h)

AC_SUBST(PACKAGE_DATE, `date +'%d %b %Y'`)
AC_SUBST(PACKAGE_VERSION)
AC_SUBST(PACKAGE_NAME)
AC_SUBST(PACKAGE_TARNAME)
AC_SUBST(PACKAGE_RELEASE, ${PACKAGE_RELEASE:-1})
AC_SUBST(WINBUILDDIR, Release-2005)

# Checks for programs.
AC_CHECK_PROG(BISON, bison, yes, no)
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

dnl --enable-docs
AC_ARG_ENABLE([docs], [AS_HELP_STRING([--enable-docs], [regenerate man page and online documentation])])
AM_CONDITIONAL([REBUILD_DOCS], [test "x$enable_docs" = "xyes"])
AM_COND_IF([REBUILD_DOCS], [
  AC_CHECK_PROG(ASCIIDOC, asciidoc, yes, no)
  AC_CHECK_PROG(A2X, a2x, yes, no)
  AS_IF([test "x$ASCIIDOC" = "xno" -o "x$A2X" = "xno"], [
      AC_MSG_ERROR([need asciidoc and a2x for --enable-docs])
  ])
])

if test "$GCC" = "yes"; then
  AC_MSG_CHECKING([Testing GCC version])
  GCCVERSION=`$CXX -dumpversion 2>/dev/null`
  if test -z "$GCCVERSION"; then
    AC_MSG_ERROR([GCC version 3 or above required])
  fi
  AC_MSG_RESULT([found version $GCCVERSION])
fi

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC

# We only rely on standard C/C++ headers.  If we ever have a pressing need
# for something non-standard, we should add a check for it here.
# AC_CHECK_HEADERS([stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_C_VOLATILE

# Checks for library functions.
AC_FUNC_MEMCMP
AC_FUNC_MMAP
AC_CHECK_FUNCS([memset munmap strdup strndup])

AC_CHECK_SIZEOF([char])
AC_CHECK_SIZEOF([short])
AC_CHECK_SIZEOF([int])
AC_CHECK_SIZEOF([long])

AC_CONFIG_FILES([\
Makefile \
README \
makerpm \
re2c.ad \
re2c.spec \
run_tests.sh \
config_w32.h \
])
AC_OUTPUT_COMMANDS([chmod +x makerpm run_tests.sh])
AC_OUTPUT
