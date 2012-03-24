AC_PREREQ([2.50])
AC_INIT([solitaire],
        [0.1.0-pre],
        [coder@kyleisom.net], [],
        [https://github.com/kisom/solitaire])
AM_INIT_AUTOMAKE([1.11 foreign no-define color-tests parallel-tests])
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([src/card.h])
AC_CHECK_HEADERS
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES(test/Makefile doc/Makefile src/Makefile Makefile)
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL

dnl set up some additional useful macros
AC_DEFINE([PACKAGE_LICENSE], ["License ISC/public domain:"],
          [license used by the package])
AC_DEFINE([PACKAGE_LICENSE_URL], 
          ["http://www.kyleisom.net/code/license.txt"],
          [where the user can find a copy of the license])
AC_DEFINE([PACKAGE_COPYRIGHT], 
          ["Copyright (c) 2012 Kyle Isom <coder@kyleisom.net>"],
          [copyright tagline])


AC_OUTPUT

