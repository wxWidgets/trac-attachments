/////////////////////////////////////////////////////////////////////////////
// Name:        unix/dlunix.cpp
// Purpose:     Unix-specific part of wxDynamicLibrary and related classes
// Author:      Vadim Zeitlin, modified by Bernard Krummenacher
// Modified by:
// Created:     2005-01-16 (extracted from common/dynlib.cpp)
// RCS-ID:      $Id: dlunix.cpp,v 1.11 2005/04/19 12:38:24 SC Exp $
// Copyright:   (c) 2000-2005 Vadim Zeitlin <vadim@wxwindows.org>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include  "wx/wxprec.h"

#ifdef __BORLANDC__
  #pragma hdrstop
#endif

#if wxUSE_DYNLIB_CLASS

#include "wx/dynlib.h"
#include "wx/ffile.h"

#ifndef WX_PRECOMP
    #include "wx/intl.h"
    #include "wx/log.h"
#endif

// only Mac OS X 10.3+ has dlfcn.h, and it is simpler to always provide our own
// wrappers using the native functions instead of doing checks for OS version
#ifndef __DARWIN__
    #include <dlfcn.h>
#endif

// if some flags are not supported, just ignore them
#ifndef RTLD_LAZY
    #define RTLD_LAZY 0
#endif

#ifndef RTLD_NOW
    #define RTLD_NOW 0
#endif

#ifndef RTLD_GLOBAL
    #define RTLD_GLOBAL 0
#endif


#if defined(HAVE_DLOPEN) || defined(__DARWIN__)
    #define USE_POSIX_DL_FUNCS
#elif !defined(HAVE_SHL_LOAD)
    #error "Don't know how to load dynamic libraries on this platform!"
#endif

//#include <Carbon.h>

#ifdef __APPLE_CC__
#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFPlugInCOM.h>
#else
#include <CFPlugIn.h>
#include <CFPlugInCOM.h>
#endif

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// standard shared libraries extensions for different Unix versions
#if defined(__HPUX__)
    const wxChar *wxDynamicLibrary::ms_dllext = _T(".sl");
#elif defined(__DARWIN__)
    const wxChar *wxDynamicLibrary::ms_dllext = _T(".bundle");
#else
    const wxChar *wxDynamicLibrary::ms_dllext = _T(".so");
#endif

// ============================================================================
// wxDynamicLibrary implementation
// ============================================================================

// ----------------------------------------------------------------------------
// dlxxx() emulation for Darwin
// ----------------------------------------------------------------------------

#if defined(__DARWIN__)
// ---------------------------------------------------------------------------
// For Darwin/Mac OS X
//   supply the sun style dlopen functions in terms of Darwin NS*
// ---------------------------------------------------------------------------

/* Porting notes:
 *   The dlopen port is a port from dl_next.xs by Anno Siegel.
 *   dl_next.xs is itself a port from dl_dlopen.xs by Paul Marquess.
 *   The method used here is just to supply the sun style dlopen etc.
 *   functions in terms of Darwin NS*.
 */

#include <stdio.h>
#include <mach-o/dyld.h>

static char dl_last_error[1024];

static
void TranslateError(const char *path, int number)
{
  sprintf(dl_last_error, "%s(%d): %s\n", path, number,wxSysErrorMsg(number));
}

const char *dlerror()
{
    return dl_last_error;
}

void *dlopen(const char *path, int WXUNUSED(mode) /* mode is ignored */)
{
  CFURLRef bundleURL;
  CFBundleRef bundle;
  
  // Make a CFURLRef from the CFString representation of the 
  // bundleÕs path.
  bundleURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, 
                                            CFStringCreateWithCString(NULL,
                                            path,kCFStringEncodingUTF8),
                                            kCFURLPOSIXPathStyle,
                                            true);
    
  // Make a bundle instance using the URLRef.
  bundle = CFBundleCreate( kCFAllocatorDefault, bundleURL );
  if ( !bundle )
  {
    TranslateError(path, errno);
  }
  // Any CF objects returned from functions with "create" or 
  // "copy" in their names must be released by us!
  CFRelease( bundleURL );
  return bundle;
}

int dlclose(void *handle)
{
    CFBundleUnloadExecutable((CFBundleRef)handle);
    return 0;
}

void* dlsym(void* handle, const char* symbol)
{
  void* func_symbol = CFBundleGetFunctionPointerForName(CFBundleRef(handle),
                        CFStringCreateWithCString(NULL,symbol,
                                                  kCFStringEncodingUTF8));
  return func_symbol;
}

#endif // defined(__DARWIN__)

// ----------------------------------------------------------------------------
// loading/unloading DLLs
// ----------------------------------------------------------------------------

wxDllType wxDynamicLibrary::GetProgramHandle()
{
#ifdef USE_POSIX_DL_FUNCS
   return dlopen(0, RTLD_LAZY);
#else
   return PROG_HANDLE;
#endif
}

/* static */
wxDllType wxDynamicLibrary::RawLoad(const wxString& libname, int flags)
{
    wxASSERT_MSG( !(flags & wxDL_NOW) || !(flags & wxDL_LAZY),
                  _T("wxDL_LAZY and wxDL_NOW are mutually exclusive.") );

#ifdef USE_POSIX_DL_FUNCS
    // we need to use either RTLD_NOW or RTLD_LAZY because if we call dlopen()
    // with flags == 0 recent versions of glibc just fail the call, so use
    // RTLD_NOW even if wxDL_NOW was not specified
    int rtldFlags = flags & wxDL_LAZY ? RTLD_LAZY : RTLD_NOW;

    if ( flags & wxDL_GLOBAL )
        rtldFlags |= RTLD_GLOBAL;

    wxDllType result = dlopen(libname.fn_str(), rtldFlags);
    if (result == NULL)
    {
      const char* xx = dlerror();
      printf("%s\n",xx);
    }
    return result;
#else // !USE_POSIX_DL_FUNCS
    int shlFlags = 0;

    if ( flags & wxDL_LAZY )
    {
        shlFlags |= BIND_DEFERRED;
    }
    else if ( flags & wxDL_NOW )
    {
        shlFlags |= BIND_IMMEDIATE;
    }

    return shl_load(libname.fn_str(), shlFlags, 0);
#endif // USE_POSIX_DL_FUNCS/!USE_POSIX_DL_FUNCS
}

/* static */
void wxDynamicLibrary::Unload(wxDllType handle)
{
#ifdef wxHAVE_DYNLIB_ERROR
    int rc =
#endif

#ifdef USE_POSIX_DL_FUNCS
    dlclose(handle);
#else // !USE_POSIX_DL_FUNCS
    shl_unload(handle);
#endif // USE_POSIX_DL_FUNCS/!USE_POSIX_DL_FUNCS

#if defined(USE_POSIX_DL_FUNCS) && defined(wxHAVE_DYNLIB_ERROR)
    if ( rc != 0 )
        Error();
#endif
}

/* static */
void *wxDynamicLibrary::RawGetSymbol(wxDllType handle, const wxString& name)
{
    void *symbol;

#ifdef USE_POSIX_DL_FUNCS
    symbol = dlsym(handle, name.fn_str());
#else // !USE_POSIX_DL_FUNCS
    // note that shl_findsym modifies the handle argument to indicate where the
    // symbol was found, but it's ok to modify the local handle copy here
    if ( shl_findsym(&handle, name.fn_str(), TYPE_UNDEFINED, &symbol) != 0 )
        symbol = 0;
#endif // USE_POSIX_DL_FUNCS/!USE_POSIX_DL_FUNCS

    return symbol;
}

// ----------------------------------------------------------------------------
// error handling
// ----------------------------------------------------------------------------

#ifdef wxHAVE_DYNLIB_ERROR

/* static */
void wxDynamicLibrary::Error()
{
#if wxUSE_UNICODE
    wxWCharBuffer buffer = wxConvLocal.cMB2WC( dlerror() );
    const wxChar *err = buffer;
#else
    const wxChar *err = dlerror();
#endif

    wxLogError(wxT("%s"), err ? err : _("Unknown dynamic library error"));
}

#endif // wxHAVE_DYNLIB_ERROR

// ----------------------------------------------------------------------------
// listing loaded modules
// ----------------------------------------------------------------------------

// wxDynamicLibraryDetails declares this class as its friend, so put the code
// initializing new details objects here
class wxDynamicLibraryDetailsCreator
{
public:
    // create a new wxDynamicLibraryDetails from the given data
    static wxDynamicLibraryDetails *
    New(unsigned long start, unsigned long end, const wxString& path)
    {
        wxDynamicLibraryDetails *details = new wxDynamicLibraryDetails;
        details->m_path = path;
        details->m_name = path.AfterLast(_T('/'));
        details->m_address = wx_reinterpret_cast(void *, start);
        details->m_length = end - start;

        // try to extract the library version from its name
        const size_t posExt = path.rfind(_T(".so"));
        if ( posExt != wxString::npos )
        {
            if ( path.c_str()[posExt + 3] == _T('.') )
            {
                // assume "libfoo.so.x.y.z" case
                details->m_version.assign(path, posExt + 4, wxString::npos);
            }
            else
            {
                size_t posDash = path.find_last_of(_T('-'), posExt);
                if ( posDash != wxString::npos )
                {
                    // assume "libbar-x.y.z.so" case
                    posDash++;
                    details->m_version.assign(path, posDash, posExt - posDash);
                }
            }
        }

        return details;
    }
};

/* static */
wxDynamicLibraryDetailsArray wxDynamicLibrary::ListLoaded()
{
    wxDynamicLibraryDetailsArray dlls;

#ifdef __LINUX__
    // examine /proc/self/maps to find out what is loaded in our address space
    wxFFile file(_T("/proc/self/maps"));
    if ( file.IsOpened() )
    {
        // details of the module currently being parsed
        wxString pathCur;
        unsigned long startCur = 0,
                      endCur = 0;

        char path[1024];
        char buf[1024];
        while ( fgets(buf, WXSIZEOF(buf), file.fp()) )
        {
            // format is: start-end perm something? maj:min inode path
            unsigned long start, end;
            switch ( sscanf(buf,
                            "%08lx-%08lx %*4s %*08x %*02d:%*02d %*d %1024s\n",
                            &start, &end, path) )
            {
                case 2:
                    // there may be no path column
                    path[0] = '\0';
                    break;

                case 3:
                    // nothing to do, read everything we wanted
                    break;

                default:
                    // chop '\n'
                    buf[strlen(buf) - 1] = '\0';
                    wxLogDebug(_T(
                      "Failed to parse line \"%s\" in /proc/self/maps."),buf);
                    continue;
            }

            wxString pathNew = wxString::FromAscii(path);
            if ( pathCur.empty() )
            {
                // new module start
                pathCur = pathNew;
                startCur = start;
                endCur = end;
            }
            else if ( pathCur == pathNew )
            {
                // continuation of the same module
                wxASSERT_MSG(start == endCur, _T("hole in /proc/self/maps?"));
                endCur = end;
            }
            else // end of the current module
            {
                dlls.Add(wxDynamicLibraryDetailsCreator::New(startCur,
                                                             endCur,
                                                             pathCur));
                pathCur.clear();
            }
        }
    }
#endif // __LINUX__

    return dlls;
}

#endif // wxUSE_DYNLIB_CLASS


 	  	 
