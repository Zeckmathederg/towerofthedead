AC_INIT([towerofthedead],[0.10260])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([foreign])
AC_PROG_CC
AC_PROG_MKDIR_P

AC_ARG_ENABLE([osslsigncode],
	AS_HELP_STRING([--enable-osslsigncode], [Enable signing if compiling for Windows]))
AS_IF([test "x$enable_osslsigncode" != "xno"], [
	AC_PATH_PROG([OSSLSIGNCODE], [osslsigncode], no)
	if test "x$OSSLSIGNCODE" = "xno"; then
	echo "osslsigncode not found and will not be enabled"
	echo "the exe will be considered unsafe as it won't be signed"
	enable_osslsigncode=no
	fi
])

MINGW_W64=false
if test "x$target" = "xx86_64-w64-mingw32"; then
	LIBS="-Lvendor/windows/x86_64/lib/ $LIBS"
	WINARCH="x86_64"
	AC_PATH_PROG([WINDRES], ["$target"-windres], no)
	if test "x$WINDRES" = "xno"; then
		AC_MSG_ERROR(["$target"-windres not found])
	fi
	AC_SEARCH_LIBS([GetDC], [gdi32])
	AC_SUBST(WINARCH)
	AC_SUBST(WINDRES)
	MINGW_W64=true
fi
if test "x$target" = "xi686-w64-mingw32"; then
	LIBS="-Lvendor/windows/x86/lib/ $LIBS"
	WINARCH="x86"
	AC_PATH_PROG([WINDRES], ["$target"-windres], no)
	if test "x$WINDRES" = "xno"; then
		AC_MSG_ERROR(["$target"-windres not found])
	fi
	AC_SEARCH_LIBS(GetDC, [gdi32])
	AC_SUBST(WINARCH)
	AC_SUBST(WINDRES)
	MINGW_W64=true
fi
if test "x$target" = "xx86_64-pc-linux-gnu"; then
	LIBS="-L/usr/lib $LIBS"
	enableosslsigncode=no
	echo "not targeting windows, turning off osslsigncode"
fi
if test "x$target" = "xi686-pc-linux-gnu"; then
	LIBS="-L/usr/lib32 $LIBS"
	enableosslsigncode=no
	echo "not targeting windows, turning off osslsigncode"
fi

AC_SEARCH_LIBS(sin, [m])
AC_SEARCH_LIBS(glfwInit, [glfw])
AC_SEARCH_LIBS(glewInit, [GLEW])
AC_SEARCH_LIBS([glEnable], [OpenGL])

AM_CONDITIONAL([MINGW_W64], [test x$MINGW_W64 = xtrue])
AC_SUBST(MINGW_W64)
if test "x$enable_osslsigncode" != "xno"; then
	AM_CONDITIONAL(ENABLE_OSSLSIGNCODE, true)
else
	AM_CONDITIONAL(ENABLE_OSSLSIGNCODE, false)
fi
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
