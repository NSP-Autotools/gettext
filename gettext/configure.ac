#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([gt], [1.0], [gt-bugs@example.org])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src/gt.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19.7])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in])

AC_OUTPUT
