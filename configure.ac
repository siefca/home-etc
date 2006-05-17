AC_INIT([home-etc],[1.2.0],[siefca/at/gnu.org])
AC_CONFIG_HEADER([config.h])
PACKAGE=$PACKAGE_NAME
VERSION=$PACKAGE_VERSION
AM_INIT_AUTOMAKE

RELEASE=1
SUMMARY="HOME-ETC support programs and libraries"
AC_SUBST(RELEASE)
AC_SUBST(SUMMARY)

dnl Checks for Libtool.
LT_CURRENT=1
LT_REVISION=2
LT_AGE=0

AM_PROG_LIBTOOL

AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

dnl Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_AWK
AC_ISC_POSIX
AC_PROG_LN_S

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h stdlib.h string.h strings.h memory.h pwd.h sys/param.h sys/types.h unistd.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

dnl Checks for library functions.
AC_CHECK_FUNCS([bzero endpwent getcwd setenv strrchr strchr memcpy memset])

AC_CONFIG_FILES([Makefile
			 home-etc.spec
			 src/Makefile
			 doc/Makefile
			 sh/Makefile
			 skel/Makefile
			 patchwork/Makefile])

AC_OUTPUT
