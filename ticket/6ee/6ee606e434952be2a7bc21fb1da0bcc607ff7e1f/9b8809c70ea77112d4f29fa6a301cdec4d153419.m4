dnl ---------------------------------------------------------------------------
dnl Macros for wxWidgets build configuration detection. 
dnl Typically used in configure.in/ac as:
dnl
dnl     # basic configure checks
dnl     ...
dnl
dnl     # required library checks
dnl     AM_WXPRESETS
dnl     ...
dnl
dnl     # write the output files
dnl     AC_BAKEFILE([m4_include(autoconf_inc.m4)])
dnl     AC_CONFIG_FILES([Makefile ...])
dnl     AC_OUTPUT
dnl
dnl     # end of the configure.in script
dnl     AM_WXPRESETS_MSG		# optional: just to show a message to the user
dnl
dnl ---------------------------------------------------------------------------


dnl ---------------------------------------------------------------------------
dnl AM_WXFLAGS_CONTAIN([RESULTVAR], [STRING])
dnl 
dnl Sets to nonzero the variable named "WX_$RESULTVAR" if the wxWidgets 
dnl additional CPP flags (taken from $WX_CPPFLAGS) contain the given STRING.
dnl Otherwise the variable will be set to 0.
dnl ---------------------------------------------------------------------------
AC_DEFUN([AM_WXFLAGS_CONTAIN],
        [
		WX_$1=$(expr match "$WX_CPPFLAGS" ".*$2.*")
	])


dnl ---------------------------------------------------------------------------
dnl AM_WXFLAGS_CHECK([RESULTVAR], [STRING], [MSG] [, ACTION-IF-FOUND 
dnl                                               [, ACTION-IF-NOT-FOUND]])
dnl 
dnl Outputs the given MSG. Then searches the given STRING in the wxWidgets 
dnl additional CPP flags and put the result of the search in WX_$RESULTVAR
dnl also adding the "yes" or "no" message result to MSG.
dnl ---------------------------------------------------------------------------
AC_DEFUN([AM_WXFLAGS_CHECK],
        [
		AC_MSG_CHECKING([$3])
		AM_WXFLAGS_CONTAIN([$1], [$2])
		if test "$WX_$1" != "0"; then
			WX_$1=1
			AC_MSG_RESULT([yes])
			ifelse([$4], , :, [$4])
		else
			WX_$1=0
			AC_MSG_RESULT([no])
			ifelse([$5], , :, [$5])
		fi
		dnl echo $WX_$1 		dnl for debugging only !
	])


dnl ---------------------------------------------------------------------------
dnl AM_WXPRESETS_CHECK
dnl 
dnl Sets the WX_UNICODE, WX_DEBUG, WX_SHARED, WX_VERSION variables to the right 
dnl values looking at the current $WX_CPPFLAGS variable.
dnl To set the $WX_CPPFLAGS variable you need to use AM_PATH_WXCONFIG first.
dnl
dnl Then sets the WX_GTKPORT, WX_MOTIFPORT, WX_MACPORT, WXX11PORT, WXMGLPORT
dnl flags to 1 or 0 to match the current wxWidgets port used.
dnl Also sets the WX_PORT var to one of gtk,motif,mac,x11,mgl values.
dnl ---------------------------------------------------------------------------
AC_DEFUN([AM_WXPRESETS_CHECK],
        [
		AM_WXFLAGS_CHECK([UNICODE], [unicode], [if wxWidgets was built with UNICODE enabled])
		AM_WXFLAGS_CHECK([DEBUG], [__WXDEBUG__], [if wxWidgets was built in DEBUG mode])
		AM_WXFLAGS_CHECK([STATIC], [static], [if wxWidgets was built in STATIC mode])
		if test "$WX_STATIC" != "0"; then
			WX_SHARED=0
		else
			WX_SHARED=1
		fi
		
		dnl be sure that the WX_VERSION macro has the same format of the WX_VERSION option
		dnl which is used by wx_win32.bkl (i.e. 25, 26, 27... instead of 2.5.x, 2.6.x, 2.7.x...)
		wx_config_major_version=`echo $WX_VERSION | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
		wx_config_minor_version=`echo $WX_VERSION | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
		WX_VERSION=$wx_config_major_version$wx_config_minor_version

		dnl checks for the wx port used
		WX_PORT=unknown
		AM_WXFLAGS_CHECK([GTKPORT], [__WXGTK__], [if wxWidgets port is wxGTK], [WX_PORT=gtk])
		AM_WXFLAGS_CHECK([MOTIFPORT], [__WXMOTIF__], [if wxWidgets port is wxMotif], [WX_PORT=motif])
		AM_WXFLAGS_CHECK([MACPORT], [__WXMAC__], [if wxWidgets port is wxMac], [WX_PORT=mac])
		AM_WXFLAGS_CHECK([X11PORT], [__WXX11__], [if wxWidgets port is wxX11], [WX_PORT=x11])
		AM_WXFLAGS_CHECK([MGLPORT], [__WXMGL__], [if wxWidgets port is wxMGL], [WX_PORT=mgl])

		dnl nice way to check:
		dnl - that only one of the WX_*PORT variables has been set to 1
		dnl - at least one of the WX_*PORT has been set !
		if [[ "$WX_PORT" = "unknown" ]]; then
			AC_MSG_ERROR([Cannot detect the currently installed wxWidgets port !])
		fi
		if [[ "$(expr $WX_GTKPORT + $WX_MOTIFPORT + $WX_MACPORT + $WX_X11PORT + $WX_MGLPORT)" != "1" ]]; then
			AC_MSG_ERROR([Your 'wx-config --cxxflags' command seems to define more than one port symbol...])
		fi
	])


dnl ---------------------------------------------------------------------------
dnl AM_WXPRESETS([VERSION])
dnl 
dnl Just a convenience macro for
dnl  AM_OPTIONS_WXCONFIG
dnl  AM_PATH_WXCONFIG([VERSION])
dnl  AM_WXPRESETS_CHECK
dnl macros.
dnl ---------------------------------------------------------------------------
AC_DEFUN([AM_WXPRESETS],
		 [
			dnl Check for wxWidgets
			AM_OPTIONS_WXCONFIG
			AM_PATH_WXCONFIG([$1], [wxWin=1], [wxWin=0])
			if test "$wxWin" != 1; then
				AC_MSG_ERROR([
				   wxWidgets must be installed on your system
				   but wx-config script couldn't be found.
				
				   Please check that wx-config is in path, the directory
				   where wxWidgets libraries are installed (returned by
				   'wx-config --libs' command) is in LD_LIBRARY_PATH or
				   equivalent variable and wxWidgets version is $1 or above.
				])
			else
				dnl do not update CPPFLAGS nor CXXFLAGS doing something like:
				dnl       CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS"
				dnl       CXXFLAGS="$CXXFLAGS $WX_CXXFLAGS"
				dnl otherwise we'll get the
				dnl same settings repetead three times since wxpresets generate a
				dnl Makefile.in which merges these two variables with $WX_CPPFLAGS 
				dnl automatically...
				CFLAGS="$CFLAGS $WX_CFLAGS_ONLY"
				LDFLAGS="$LDFLAGS $WX_LIBS"
			fi
			
			dnl Synch our WX_DEBUG,WX_UNICODE,WX_SHARED variables with wx ones			
			AM_WXPRESETS_CHECK
		])


dnl ---------------------------------------------------------------------------
dnl AM_WXPRESETS_MSG
dnl 
dnl Shows a summary message to the user about the WX_* variable contents.
dnl This macro is used typically at the end of the configure script.
dnl ---------------------------------------------------------------------------
AC_DEFUN([AM_WXPRESETS_MSG],
        [
		echo
		echo "  wxWidgets configuration:"
		if [[ "$WX_DEBUG" = "1" ]]; then
			echo "  - DEBUG build"
		else
			echo "  - RELEASE build"
		fi
		if [[ "$WX_UNICODE" = "1" ]]; then
			echo "  - UNICODE mode"
		else
			echo "  - ANSI mode"
		fi
		if [[ "$WX_SHARED" = "1" ]]; then
			echo "  - SHARED mode"
		else
			echo "  - STATIC mode"
		fi
		echo "  - VERSION: $WX_VERSION"
		echo "  - PORT: $WX_PORT"
	])

 	  	 
