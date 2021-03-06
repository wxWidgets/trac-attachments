/* setup.h.  Generated automatically by configure.  */
/* This define (__WX_SETUP_H__) is used both to ensure setup.h is included
 * only once and to indicate that we are building using configure. */
#ifndef __WX_SETUP_H__
#define __WX_SETUP_H__

#ifdef __GNUG__
#pragma interface
#endif

/* never undefine inline or const keywords for C++ compilation */
#ifndef __cplusplus

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define as __inline if that's what the C compiler calls it.  */
/* #undef inline */

#endif /* __cplusplus */

/* fill in with the string wxGetOsDescription() will return */
/* #undef WXWIN_OS_DESCRIPTION */

/* the installation location prefix from configure */
/* #undef wxINSTALL_PREFIX */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef gid_t */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef mode_t */

/* Define to `long' if <sys/types.h> doesn't define.  */
/* #undef off_t */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef pid_t */

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* Define if you have the ANSI C header files.  */
/* #undef STDC_HEADERS */

/* Define this to get extra features from GNU libc. */
/* #undef _GNU_SOURCE */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef uid_t */

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
/* #undef WORDS_BIGENDIAN */

/* Define this if your version of GTK+ is greater than 1.2 */
/* #undef __WXGTK12__ */

/* Define this if your version of GTK+ is greater than 1.2.7 */
/* #undef __WXGTK127__ */

/* Define this if your version of GTK+ is greater than 1.3 */
/* #undef __WXGTK20__ */

/*
 * Define to 1 for Unix[-like] system
 */
#define wxUSE_UNIX 1

/* #undef __UNIX__ */
/* #undef __LINUX__ */
/* #undef __SGI__ */
/* #undef __HPUX__ */
/* #undef __SYSV__ */
/* #undef __SVR4__ */
/* #undef __AIX__ */
/* #undef __SUN__ */
/* #undef __SOLARIS__ */
/* #undef __SUNOS__ */
/* #undef __ALPHA__ */
/* #undef __IA64__ */
/* #undef __OSF__ */
/* #undef __BSD__ */
/* #undef __FREEBSD__ */
/* #undef __DARWIN__ */
/* #undef __NETBSD__ */
/* #undef __OPENBSD__ */
/* #undef __VMS__ */
/* #undef __ULTRIX__ */
/* #undef __DATA_GENERAL__ */
/* #undef __EMX__ */

/* NanoX (with wxX11) */
#define wxUSE_NANOX 0

/* PowerPC Darwin & Mac OS X */
/* #undef __POWERPC__ */

/* MS-DOS with DJGPP */
/* #undef __DOS__ */

/* Stupid hack; __WINDOWS__ clashes with wx/defs.h */
#ifndef __WINDOWS__
/* #undef __WINDOWS__ */
#endif

#ifndef __WIN32__
/* #undef __WIN32__ */
#endif
/* #undef __GNUWIN32__ */
/* #undef STRICT */
/* #undef WINVER */

/* enable native status bar under Win32 */
#if defined(__WIN95__) && !defined(__WXUNIVERSAL__)
#define wxUSE_NATIVE_STATUSBAR 1
#define wxUSE_OWNER_DRAWN 1
#endif

#if defined(__WXPM__)
#define wxUSE_OWNER_DRAWN 1
#endif

/* enable rich edit under Win32 */
#if defined(__WIN95__) && !defined(__TWIN32__) && !defined(__GNUWIN32_OLD__)
#define wxUSE_RICHEDIT 1
#else
#define wxUSE_RICHEDIT 0
#endif

/*
 * Supports bool type
 */
/* #undef HAVE_BOOL */

/*
 * Define if your compiler supports the explicit keyword
 */
/* #undef HAVE_EXPLICIT */

/*
 * Use regex support
 */
#define wxUSE_REGEX 1
/*
 * Use zlib
 */
#define wxUSE_ZLIB 1
/*
 * Use libpng
 */
#define wxUSE_LIBPNG 1
/*
 * Use libjpeg
 */
#define wxUSE_LIBJPEG 1
/*
 * Use libtiff
 */
#define wxUSE_LIBTIFF 1
/*
 * Use iODBC
 */
#define wxUSE_ODBC 0
#define wxODBC_FWD_ONLY_CURSORS 1
#define wxODBC_BACKWARD_COMPATABILITY 0
/*
 * Use freetype
 */
#define wxUSE_FREETYPE 0
/*
 * Use Threads
 */
#define wxUSE_THREADS 1
/*
 * Have glibc2
 */
#define wxHAVE_GLIBC2 0
/*
 * Use libXpm
 */
#define wxHAVE_LIB_XPM 0
/*
 * Use OpenGL
 */
#define wxUSE_OPENGL 0
#define wxUSE_GLCANVAS 0

/*
 * Use GUI
 */
#define wxUSE_GUI 1
/*
 * Don't use GUI (defined to 1 when compiling/using base only)
 */
#define wxUSE_NOGUI 0

/*
 * Catch fatal program exceptions
 */
#define wxUSE_ON_FATAL_EXCEPTION 1

/*
 * Use wxSingleInstanceChecker class
 */
#define wxUSE_SNGLINST_CHECKER 1

/*
 * Use constraints mechanism
 */
#define wxUSE_CONSTRAINTS 1

/*
 * Use validators
 */
#define wxUSE_VALIDATORS 1

/*
 * Use wxControl
 */
#define wxUSE_CONTROLS 1

/*
   Use wxPopupWindow (useful in wxUniv only for now)
*/
#define wxUSE_POPUPWIN 0

/*
   Use wxTipWindow
 */
#define wxUSE_TIPWINDOW 1

/*
 * Use accelerators
 */
#define wxUSE_ACCEL 1

/*
 * Use wxCalendarCtrl
 */
#define wxUSE_CALENDARCTRL 1

/*
 * Use wxFileDialog
 */
#define wxUSE_FILEDLG 1

/*
 * Use wxFindReplaceDialog
 */
#define wxUSE_FINDREPLDLG 1

/*
 * Use wxFontDialog
 */
#define wxUSE_FONTDLG 1

/*
 * Use wxMimeTypesManager and related classes
 */
#define wxUSE_MIMETYPE 1

/*
 * Use wxSystemOptions
 */
#define wxUSE_SYSTEM_OPTIONS 1

/*
 * Use wxMessageDialog (and wxMessageBox)
 */
#define wxUSE_MSGDLG 1

/*
 * Use wxNumberEntryDialog
 */
#define wxUSE_NUMBERDLG 1

/*
 * Use wxTextEntryDialog
 */
#define wxUSE_TEXTDLG 1

/*
 * Use startup tips
 */
#define wxUSE_STARTUP_TIPS 1

/*
 * Use progress dialog
 */
#define wxUSE_PROGRESSDLG 1

/*
 * Use chooser dialog
 */
#define wxUSE_CHOICEDLG 1

/*
 * Use colour picker dialog
 */
#define wxUSE_COLOURDLG 1

/*
 * Use directory chooser dialog
 */
#define wxUSE_DIRDLG 1

/*
 * Use wxDragImage class
 */
#define wxUSE_DRAGIMAGE 1

/*
 * Use property sheet classes
 */
#define wxUSE_PROPSHEET 1

/*
 * Use wxWizard
 */
#define wxUSE_WIZARDDLG 1

/*
 * Use splash screen
 */
#define wxUSE_SPLASH 1

/*
 * Joystick support (Linux/GTK only)
 */
#define wxUSE_JOYSTICK 0

/*
 * Use this control
 */
#define wxUSE_BUTTON 1
/*
 * Use this control
 */
#define wxUSE_CARET 1
/*
 * Use this control
 */
#define wxUSE_BMPBUTTON 1
/*
 * Use this control
 */
#define wxUSE_CHECKBOX 1
/*
 * Use this control
 */
#define wxUSE_CHECKLISTBOX 1
/*
 * Use this control
 */
#define wxUSE_COMBOBOX 1
/*
 * Use this control
 */
#define wxUSE_CHOICE 1
/*
 * Use this control
 */
#define wxUSE_GAUGE 1
/*
 * Use this control
 */
#define wxUSE_GRID 1
/*
 * Use this control
 */
#define wxUSE_NEW_GRID 1
/*
 * Use the new prototype wxGrid classes
 * (wxUSE_GRID must also be defined)
 */
#define wxUSE_IMAGLIST 1
/*
 * Use this control
 */
#define wxUSE_LISTBOX 1
/*
 * Use this control
 */
#define wxUSE_LISTCTRL 1
/*
 * Use wxMenuBar, wxMenuItem and wxMenu
 */
#define wxUSE_MENUS 1
/*
 * Use this control
 */
#define wxUSE_NOTEBOOK 1
/*
 * Use this control
 */
#define wxUSE_RADIOBOX 1
/*
 * Use this control
 */
#define wxUSE_RADIOBTN 1
/*
 * Use this control
 */
#define wxUSE_SASH 1
/*
 * Use this control
 */
#define wxUSE_SCROLLBAR 1
/*
 * Use this control
 */
#define wxUSE_SLIDER 1
/*
 * Use this control
 */
#define wxUSE_SPINBTN 1
/*
 * Use this control
 */
#define wxUSE_SPINCTRL 1
/*
 * Use this control
 */
#define wxUSE_SPLITTER 1
/*
 * Use this control
 */
#define wxUSE_STATBMP 1
/*
 * Use this control
 */
#define wxUSE_STATBOX 1
/*
 * Use this control
 */
#define wxUSE_STATLINE 1
/*
 * Use this control
 */
#define wxUSE_STATTEXT 1
/*
 * Use this control
 */
#define wxUSE_STATUSBAR 1
/*
 * Use this control
 */
#define wxUSE_TOGGLEBTN 0
/*
 * Use Tab dialog class - obsolete, use wxNotebook instead
 */
#define wxUSE_TAB_DIALOG 0
/* compatibility */
#define wxUSE_TABDIALOG wxUSE_TAB_DIALOG

/*
 * Use wxTextCtrl
 */
#define wxUSE_TEXTCTRL 1

/*
 * Use wxToollBar
 */
#define wxUSE_TOOLBAR 1

/*
 * If 1, use the native toolbar, otherwise use the generic version
 * (wxToolBarSimple) which may also be use together with the native one.
 */
#define wxUSE_TOOLBAR_NATIVE 1

/*
 * Use generic wxToolBar instead of/together with the native one?
 */
#define wxUSE_TOOLBAR_SIMPLE 1

#if defined(__WXWINE__) || defined(__GNUWIN32__) || defined(__WXPM__)
  #if wxUSE_TOOLBAR
    #define wxUSE_BUTTONBAR 1
  #endif
#endif

/*
 * Use wxTreeLayout class
 */
#define wxUSE_TREELAYOUT 1

/*
 * Use this control
 */
#define wxUSE_TREECTRL 1

/*
 * Use wxLongLong (a.k.a. int64) class
 */
#define wxUSE_LONGLONG 1

/*
 * Use geometry classes
 */
#define wxUSE_GEOMETRY 1

/*
 * Use wxCmdLineParser class
 */
#define wxUSE_CMDLINE_PARSER 1
/*
 * Use wxDateTime
 */
#define wxUSE_DATETIME 1
/*
 * Use wxFile class
 */
#define wxUSE_FILE 1
/*
 * Use wxFFile class
 */
#define wxUSE_FFILE 1
/*
 * Use wxFSVolume class
 */
#define wxUSE_FSVOLUME 1

/*
 * Use wxTextBuffer class
 */
#define wxUSE_TEXTBUFFER 1
/*
 * Use wxTextFile class
 */
#define wxUSE_TEXTFILE 1

/*
 * Use log classes and logging functions
 */
#define wxUSE_LOG 1
/*
 * Use log window
 */
#define wxUSE_LOGWINDOW 1
/*
 * Use standard GUI logger
 */
#define wxUSE_LOGGUI 1
/*
 * Use old log dialog instead of new wxLogGui
 */
#define wxUSE_LOG_DIALOG 1
/*
 * Use wxStopWatch
 */
#define wxUSE_STOPWATCH 1
/*
 * Use time and date classes
 */
#define wxUSE_TIMEDATE 1
/*
 * Use wave class
 */
#define wxUSE_WAVE 0
/*
 * Use config system
 */
#define wxUSE_CONFIG 1
/*
 * Use font mapping/conversion classes
 */
#define wxUSE_FONTMAP 1
/*
 * Use intl system
 */
#define wxUSE_INTL 1
/*
 * Use wxProtocol and related classes
 */
#define wxUSE_PROTOCOL 1
#define wxUSE_PROTOCOL_FILE 1
#define wxUSE_PROTOCOL_FTP 1
#define wxUSE_PROTOCOL_HTTP 1
/*
 * Use streams
 */
#define wxUSE_STREAMS 1
/*
 * Use sockets
 */
#define wxUSE_SOCKETS 1
/*
 * Use dialup manager
 */
#define wxUSE_DIALUP_MANAGER 1
/*
 * Use standard C++ streams if 1. If 0, use wxWin
 * streams implementation.
 */
#define wxUSE_STD_IOSTREAM  0
/*
 * wxLibrary class
 */
#define wxUSE_DYNLIB_CLASS 0
/*
 * Use wxObjectLoader
 */
#define wxUSE_DYNAMIC_LOADER 1

/*
 * Use wxTimer
 */
#define wxUSE_TIMER 1

/*
 * Use font metric files in GetTextExtent for wxPostScriptDC
 * Use consistent PostScript fonts for AFM and printing (!)
 */
#define wxUSE_AFM_FOR_POSTSCRIPT 1
#define wxUSE_NORMALIZED_PS_FONTS 1

/* compatibility */
#define WX_NORMALIZED_PS_FONTS wxUSE_NORMALIZED_PS_FONTS

/*
 * Use PostScript device context
 */
#define wxUSE_POSTSCRIPT 1

/*
 * Compile wxString with some Unicode (wide character) support?
 */
#define wxUSE_WCHAR_T 1

/*
 * Compile wxWindows in Unicode mode (Win32 only for now)?
 */
#define wxUSE_UNICODE 0

/*
 * Use MS Layer for Unicode on Win9X (Win32 only)?
 */
#define wxUSE_UNICODE_MSLU 0

/*
 * Use wxURL class
 */
#define wxUSE_URL 1

/*
 * Work around a bug in GNU libc 5.x wcstombs() implementation.
 *
 * Note that you must link your programs with libc.a if you enable this and you
 * have libc 5 (you should enable this for libc6 where wcsrtombs() is
 * thread-safe version of wcstombs()).
 */
#define wxUSE_WCSRTOMBS 0

/*
 * Use the new experimental implementation of wxString::Printf()?
 *
 * Warning: enabling this may cause internal compiler errors with gcc!
 */
#define wxUSE_EXPERIMENTAL_PRINTF 0

/*
 * Use Interprocess communication
 */
#define wxUSE_IPC 1
/*
 * Use wxGetResource & wxWriteResource (change .Xdefaults)
 */
#define wxUSE_X_RESOURCES 0
/*
 * Use clipboard
 */
#define wxUSE_CLIPBOARD 1
/*
 * Use wxDataObject
 */
#define wxUSE_DATAOBJ 1
/*
 * Use tooltips
 */
#define wxUSE_TOOLTIPS 1
/*
 * Use dnd
 */
#define wxUSE_DRAG_AND_DROP 1
/*
 * Use OLE (MSW only)
 */
#define wxUSE_OLE 0
/*
 * Use spline
 */
#define wxUSE_SPLINES 1

/*
 * Use the mdi architecture
 */
#define wxUSE_MDI_ARCHITECTURE 1
/*
 * Use the document/view architecture
 */
#define wxUSE_DOC_VIEW_ARCHITECTURE 1
/*
 * Use the print/preview architecture
 */
#define wxUSE_PRINTING_ARCHITECTURE 1

/*
 * Use Prolog IO
 */
#define wxUSE_PROLOGIO 0
/*
 * Use wxWindows resource loading (.wxr-files) (Needs wxUSE_PROLOGIO 1)
 */
#define wxUSE_RESOURCES 0

/* for compatibility */
#define wxUSE_WX_RESOURCES wxUSE_RESOURCES

/*
 * Use wxWindows help facility
 */
#define wxUSE_HELP 1
/*
 * Use built-in HTML-based help controller
 */
#define wxUSE_WXHTML_HELP 1
/*
 * Use MS HTML Help controller (win32)
 */
#define wxUSE_MS_HTML_HELP 0

/*
 * Use iostream.h rather than iostream
 */
#define wxUSE_IOSTREAMH 0
/*
 * Use Apple Ieee-double converter
 */
#define wxUSE_APPLE_IEEE 1
/*
 * Compatibility with 2.0 API.
 */
#define WXWIN_COMPATIBILITY_2 0
/*
 * Compatibility with 2.2 API
 */
#define WXWIN_COMPATIBILITY_2_2 1
/*
 * Enables debugging: memory tracing, assert, etc., contains debug level
 */
#define WXDEBUG 1
/*
 * Enables debugging version of wxObject::new and wxObject::delete (IF WXDEBUG)
 * WARNING: this code may not work with all architectures, especially
 * if alignment is an issue.
 */
#define wxUSE_MEMORY_TRACING 0
/*
 * Enable debugging version of global memory operators new and delete
 * Disable it, If this causes problems (e.g. link errors)
 */
#define wxUSE_DEBUG_NEW_ALWAYS 0
/*
 * VZ: What does this one do? (FIXME)
 */
#define wxUSE_DEBUG_CONTEXT 0
/*
 * In debug mode, causes new to be defined to
 * be WXDEBUG_NEW (see object.h). If this causes
 * problems (e.g. link errors), set this to 0.
 */
#define wxUSE_GLOBAL_MEMORY_OPERATORS 0
/*
 * Matthews garbage collection (used for MrEd?)
 */
#define WXGARBAGE_COLLECTION_ON 0
/*
 * Use splines
 */
#define wxUSE_SPLINES 1
/*
 * wxUSE_DYNAMIC_CLASSES is TRUE for the Xt port
 */
#define wxUSE_DYNAMIC_CLASSES 1

/*
 * Support for metafiles
 */
#define wxUSE_METAFILE 1
#define wxUSE_ENH_METAFILE 0

/*
 * wxMiniFrame
 */
#define wxUSE_MINIFRAME 1

/*
 * wxHTML
 */
#define wxUSE_HTML 1

/*
 * (virtual) filesystems code
 */
#define wxUSE_FILESYSTEM 1
#define wxUSE_FS_INET 1
#define wxUSE_FS_ZIP 1

/*
 * A class that shows info window when app is busy
 * (works exactly like wxBusyCursor)
 */
#define wxUSE_BUSYINFO 1

/*
 * Zip stream for accessing files stored inside .zip archives
 */
#define wxUSE_ZIPSTREAM 1

/*
 * wxPalette class
 */
#define wxUSE_PALETTE 1

/*
 * wxImage support
 */
#define wxUSE_IMAGE 1

/*
 * GIF image format support
 */
#define wxUSE_GIF 1

/*
 * PCX image format support
 */
#define wxUSE_PCX 1

/*
 * IFF image format support
 */
#define wxUSE_IFF 0

/*
 * PNM image format support
 */
#define wxUSE_PNM 1

/*
 * XPM image format support
 */
#define wxUSE_XPM 1

/*
 * MS ICO (and CUR,ANI derivatives) image format support (on any platform)
 */
#define wxUSE_ICO_CUR 1

/*
 * Disable this if your compiler can't cope
 * with omission of prototype parameters.
 */
#define REMOVE_UNUSED_ARG 1
/*
 * The const keyword is being introduced more in wxWindows.
 * You can use this setting to maintain backward compatibility.
 * If 0: will use const wherever possible.
 * If 1: will use const only where necessary
 *       for precompiled headers to work.
 * If 2: will be totally backward compatible, but precompiled
 *       headers may not work and program size will be larger.
 */
#define CONST_COMPATIBILITY 0

/* define with the name of timezone variable */
/* #undef WX_TIMEZONE */

/* The type of 3rd argument to getsockname() - usually size_t or int */
/* #undef SOCKLEN_T */

/* The type of statvfs(2) argument */
/* #undef WX_STATFS_T */

/* The signal handler prototype */
/* #undef wxTYPE_SA_HANDLER */

/* gettimeofday() usually takes 2 arguments, but some really old systems might
 * have only one, in which case define WX_GETTIMEOFDAY_NO_TZ */
/* #undef WX_GETTIMEOFDAY_NO_TZ */

/* struct tm doesn't always have the tm_gmtoff field, define this if it does */
/* #undef WX_GMTOFF_IN_TM */

/* Define if you have poll(2) function */
/* #undef HAVE_POLL */

/* Define if you have pw_gecos field in struct passwd */
/* #undef HAVE_PW_GECOS */

/* Define if you have dlopen() */
/* #undef HAVE_DLOPEN */

/* Define if you have gettimeofday() */
/* #undef HAVE_GETTIMEOFDAY */

/* Define if you have ftime() */
/* #undef HAVE_FTIME */

/* Define if you have support for large (64 bit size) files */
/* #undef HAVE_LARGEFILE_SUPPORT */

/* Define if you have localtime() */
/* #undef HAVE_LOCALTIME */

/* Define if you have nanosleep() */
/* #undef HAVE_NANOSLEEP */

/* Define if you have sched_yield */
/* #undef HAVE_SCHED_YIELD */

/* Define if you have pthread_mutexattr_t and functions to work with it */
/* #undef HAVE_PTHREAD_MUTEXATTR_T */

/* Define if you have PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP */
/* #undef HAVE_PTHREAD_RECURSIVE_MUTEX_INITIALIZER */

/* Define if you have pthread_cancel */
/* #undef HAVE_PTHREAD_CANCEL */

/* Define if you have sigaction() */
/* #undef HAVE_SIGACTION */

/* Define if you have sigemptyset() */
/* #undef HAVE_SIGEMPTYSET */

/* Define if you have shl_load() */
/* #undef HAVE_SHL_LOAD */

/* define if you have statfs function */
/* #undef HAVE_STATFS */

/* define if you have statvfs function */
/* #undef HAVE_STATVFS */

/* Define if you have strptime() */
/* #undef HAVE_STRPTIME */

/* Define if you have all functions to set thread priority */
/* #undef HAVE_THREAD_PRIORITY_FUNCTIONS */

/* Define if you can specify exit functions to a thread */
/* #undef HAVE_THREAD_CLEANUP_FUNCTIONS */

/* Define if you have timegm() function */
/* #undef HAVE_TIMEGM */

/* Define if you have vsnprintf() */
/* #undef HAVE_VSNPRINTF */

/* Define if you have usleep() */
/* #undef HAVE_USLEEP */

/* Define if you have wcslen function  */
/* #undef HAVE_WCSLEN */

/* define if you have vsscanf function */
/* #undef HAVE_VSSCANF */

/* The number of bytes in a char.  */
/* #undef SIZEOF_CHAR */

/* The number of bytes in a wchar_t.  */
/* #undef SIZEOF_WCHAR_T */

/* The number of bytes in a int.  */
/* #undef SIZEOF_INT */

/* The number of bytes in a int *.  */
/* #undef SIZEOF_INT_P */

/* The number of bytes in a long.  */
/* #undef SIZEOF_LONG */

/* The number of bytes in a long long.  */
/* #undef SIZEOF_LONG_LONG */

/* The number of bytes in a short.  */
/* #undef SIZEOF_SHORT */

/* Define if size_t on your machine is the same type as unsigned int. */
/* #undef wxSIZE_T_IS_UINT */

/* Define if size_t on your machine is the same type as unsigned long. */
/* #undef wxSIZE_T_IS_ULONG */

/* Define if you have the dlopen function.  */
/* #undef HAVE_DLOPEN */

/* Define if you have the dlerror function.  */
/* #undef HAVE_DLERROR */

/* Define if you have Posix fnctl() function. */
/* #undef HAVE_FCNTL */

/* Define if you have BSD flock() function. */
/* #undef HAVE_FLOCK */

/* Define if you have the gethostname function.  */
/* #undef HAVE_GETHOSTNAME */

/* Define if you have the inet_addr function.  */
/* #undef HAVE_INET_ADDR */

/* Define if you have the inet_aton function.  */
/* #undef HAVE_INET_ATON */

/* Define if you have the mktemp function.  */
/* #undef HAVE_MKTEMP */

/* Define if you have the mkstemp function.  */
/* #undef HAVE_MKSTEMP */

/* Define if you have the nanosleep function.  */
/* #undef HAVE_NANOSLEEP */

/* Define if you have the putenv function.  */
/* #undef HAVE_PUTENV */

/* Define if you have the setenv function.  */
/* #undef HAVE_SETENV */

/* Define if you have the shl_load function.  */
/* #undef HAVE_SHL_LOAD */

/* Define if you have strtok_r function. */
/* #undef HAVE_STRTOK_R */

/* Define if you have thr_setconcurrency function */
/* #undef HAVE_THR_SETCONCURRENCY */

/* Define if you have the uname function.  */
/* #undef HAVE_UNAME */

/* Define if you have the usleep function.  */
/* #undef HAVE_USLEEP */

/* Define if you have the <X11/XKBlib.h> header file.  */
/* #undef HAVE_X11_XKBLIB_H */

/* Define if you have the fnmatch() function */
/* #undef HAVE_FNMATCH */

/* Define if you have the <fnmatch.h> header file.  */
/* #undef HAVE_FNMATCH_H */

/* Define if you have the <iostream> header file.  */
/* #undef HAVE_IOSTREAM */

/* Define if you have the <linux/joystick.h> header file.  */
/* #undef HAVE_LINUX_JOYSTICK_H */

/* Define if you have the <sched.h> header file.  */
/* #undef HAVE_SCHED_H */

/* Define if you have the <strings.h> header file.  */
/* #undef HAVE_STRINGS_H */

/* Define if you have the <unistd.h> header file.  */
/* #undef HAVE_UNISTD_H */

/* Define if you have the <fcntl.h> header file.  */
/* #undef HAVE_FCNTL_H */

/* Define if you have the <wchar.h> header file.  */
/* #undef HAVE_WCHAR_H */

/* Define if you have the <wcstr.h> header file.  */
/* #undef HAVE_WCSTR_H */

/* Define if you have the <wctype.h> header file.  */
/* #undef HAVE_WCTYPE_H */

/* Define if you have the <iconv.h> header file and iconv() symbol.  */
/* #undef HAVE_ICONV */

/* Define as "const" if the declaration of iconv() needs const.  */
/* #undef ICONV_CONST */

/* Define if you have the <langinfo.h> header file.  */
/* #undef HAVE_LANGINFO_H */

/* Define if you have the <w32api.h> header file (mingw,cygwin).  */
/* #undef HAVE_W32API_H */

/* Define if you have wcsrtombs() function */
/* #undef HAVE_WCSRTOMBS */

/* Define this if you have fputws() and putwc() */
/* #undef HAVE_FPUTWC */

/* Define this if you have wprintf() and related functions */
/* #undef HAVE_WPRINTF */

/* Define this if you have wprintf() and related functions */
/* #undef HAVE_VSWPRINTF */

/* Define this if you have _vsnwprintf */
/* #undef HAVE__VSNWPRINTF */

/* Define this if you are using gtk and gdk contains support for X11R6 XIM */
/* #undef HAVE_XIM */


/* -------------------------------------------------------------------------
   Win32 adjustments section
   ------------------------------------------------------------------------- */

#ifdef __WIN32__

/* we need to define wxUSE_XPM_IN_MSW for MSW compilation for compatibility
   with wx/msw/setup.h */
#define wxUSE_XPM_IN_MSW wxUSE_XPM

#endif /* __WIN32__ */

/* --------------------------------------------------------*
 *  This stuff is static, it doesn't get modified directly
 *  by configure.
*/

#include "wx/chkconf.h"

/*
   define some constants identifying wxWindows version in more details than
   just the version number
 */

/* wxLogChain class available */
#define wxHAS_LOG_CHAIN

/* define this when wxDC::Blit() respects SetDeviceOrigin() in wxGTK */
/* #undef wxHAS_WORKING_GTK_DC_BLIT */


#endif /* __WX_SETUP_H__ */


 	  	 
