AC_PREREQ([2.50])
AC_INIT([solitaire],
        [0.3.0],
        [coder@kyleisom.net], [],
        [https://github.com/kisom/solitaire])
AM_INIT_AUTOMAKE([1.11 foreign no-define color-tests parallel-tests])
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([src/card.h])
AC_CHECK_HEADERS
AC_CONFIG_HEADERS([src/config.h])
AC_CANONICAL_HOST
AC_CONFIG_FILES(test/Makefile doc/Makefile src/Makefile Makefile)
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL

dnl need to define _GNU_SOURCE on Linux machines to enable asprintf
if test "x${host_os%-gnu}" = xlinux; then
    AC_DEFINE([_GNU_SOURCE], [], [Linux requires _GNU_SOURCE for asprintf])
fi

dnl set up some additional useful macros
AC_DEFINE([PACKAGE_LICENSE], ["License ISC/public domain:"],
          [license used by the package])
AC_DEFINE([PACKAGE_LICENSE_URL], 
          ["http://www.kyleisom.net/code/license.txt"],
          [where the user can find a copy of the license])
AC_DEFINE([PACKAGE_COPYRIGHT], 
          ["Copyright (c) 2012 Kyle Isom <coder@kyleisom.net>"],
          [copyright tagline])


dnl check for libcunit
AC_SEARCH_LIBS([CU_initialize_registry], [cunit], 
               [have_cunit="yes"], [have_cunit="no"])

if test "x${have_cunit}" = xno; then
    CANNOT_TEST_WARN = "
    CUnit not found; this is required for the unit tests. You will not 
    be able to run the test suite!
    "
    AC_MSG_WARN([${CANNOT_TEST_WARN}])
fi

AC_OUTPUT

