///////////////////////////////////////////////////////////////////////////////
// Name:        wx/platinfo.h
// Purpose:     declaration of the wxPlatformInfo class
// Author:      Francesco Montorsi
// Modified by:
// Created:     7.07.2006 (based over wxToolkitInfo)
// RCS-ID:      $Id$
// Copyright:   (c) 2006 Francesco Montorsi
// License:     wxWindows license
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_PLATINFO_H_
#define _WX_PLATINFO_H_

#include "wx/defs.h"


// ----------------------------------------------------------------------------
// wxPlatformInfo
// ----------------------------------------------------------------------------

// VERY IMPORTANT: when changing these enum values, also change the relative
//                 string tables in src/common/platinfo.cpp


// families & sub-families of operating systems
enum wxOperatingSystemId
{
    wxOS_UNKNOWN = 0,                 // returned on error

    wxOS_MAC_OS = 1,                  // Apple Mac OS 8/9/X with Mac paths
    wxOS_MAC_OSX_DARWIN = 2,          // Apple Mac OS X with Unix paths

    // the mac family
    wxOS_MAC = wxOS_MAC_OS|wxOS_MAC_OSX_DARWIN,

    wxOS_WINDOWS_9X = 4,              // Windows 9X family (95, 96, ME)
    wxOS_WINDOWS_NT = 8,              // Windows NT family (2000 included)
    wxOS_WINDOWS_MICRO = 16,          // MicroWindows
    wxOS_WINDOWS_CE = 32,             // Windows CE (Window Mobile)

    // the windows family
    wxOS_WINDOWS = wxOS_WINDOWS_9X|wxOS_WINDOWS_NT|wxOS_WINDOWS_MICRO|
                   wxOS_WINDOWS_CE,

    wxOS_UNIX_LINUX = 64,             // Linux (with or without GNU suite)
    wxOS_UNIX_FREEBSD = 128,          // FreeBSD
    wxOS_UNIX_OPENBSD = 256,          // OpenBSD
    wxOS_UNIX_NETBSD = 512,           // NetBSD
    wxOS_UNIX_SOLARIS = 1024,         // SunOS
    wxOS_UNIX_AIX = 2048,             // AIX
    wxOS_UNIX_HPUX = 4096,            // HP/UX

    // the unix family
    wxOS_UNIX = wxOS_UNIX_LINUX|wxOS_UNIX_FREEBSD|wxOS_UNIX_OPENBSD|
                wxOS_UNIX_NETBSD|wxOS_UNIX_SOLARIS|wxOS_UNIX_AIX|
                wxOS_UNIX_HPUX,

    wxOS_DOS = 8192,                  // Microsoft DOS
    wxOS_OS2 = 16384,                 // OS/2

    wxOS_MAX = 15                     // the number of members of this enum
};

// list of wxWidgets ports - some of them can be used with more than
// a single toolkit.
enum wxPortId
{
    wxPORT_UNKNOWN = -1,    // returned on error

    wxPORT_BASE = 1,            // wxBase, no native toolkit used

    wxPORT_MSW = 2,             // wxMSW, native toolkit is Windows API
    wxPORT_MOTIF = 4,           // wxMotif, toolkit is one of OpenMotif, Lesstif
                                //          and all others Motif-compatible toolkits
    wxPORT_GTK = 8,             // wxGTK, toolkit is GTK+ 1.x, GTK+ 2.x, GPE or MAEMO
    wxPORT_MGL = 16,            // wxMGL, toolkit is wxUniversal
    wxPORT_X11 = 32,            // wxX11, toolkit is wxUniversal
    wxPORT_OS2 = 64,            // wxOS2, toolkit is the OS/2 Presentation Manager
    wxPORT_MAC = 128,           // wxMac, toolkit is one of Cocoa, Carbon or Classic Mac API set
    wxPORT_WINCE = 256,         // wxWinCE, toolkit is WinCE SDK API
    wxPORT_PALMOS = 512,        // wxPalmOS, toolkit is PalmOS API

    wxPORT_MAX = 10
};

// architecture of the operating system
// (regardless of the build environment of wxWidgets library - see wxIsPlatform64bit
//  documentation for more info)
enum wxArchitecture
{
    wxARCH_INVALID = -1,        // returned on error

    wxARCH_32,                  // 32 bit
    wxARCH_64,

    wxARCH_MAX
};


// endian-ness of the machine
enum wxEndianness
{
    wxENDIAN_INVALID = -1,      // returned on error

    wxENDIAN_BIG,               // 4321
    wxENDIAN_LITTLE,            // 1234
    wxENDIAN_PDP,               // 3412

    wxENDIAN_MAX
};

// the tableb of names of the enum values above
extern WXDLLIMPEXP_DATA_BASE(wxString) wxOperatingSystemFamilyName[];
extern WXDLLIMPEXP_DATA_BASE(wxString) wxOperatingSystemIdName[];
extern WXDLLIMPEXP_DATA_BASE(wxString) wxToolkitIdName[];
extern WXDLLIMPEXP_DATA_BASE(wxString) wxPortIdName[];
extern WXDLLIMPEXP_DATA_BASE(wxString) wxArchitectureName[];
extern WXDLLIMPEXP_DATA_BASE(wxString) wxEndiannessName[];

// Information about the toolkit that the app is running under and some basic
// platform and architecture info
class WXDLLIMPEXP_BASE wxPlatformInfo : public wxObject
{

public:
    wxPlatformInfo();
    wxPlatformInfo(wxPortId pid,
                   int tkMajor = -1, int tkMinor = -1,
                   wxOperatingSystemId id = wxOS_UNKNOWN,
                   int osMajor = -1, int osMinor = -1,
                   wxArchitecture arch = wxARCH_INVALID,
                   wxEndianness endian = wxENDIAN_INVALID);
    virtual ~wxPlatformInfo() {}



    bool operator ==(const wxPlatformInfo &t) const;

    bool operator !=(const wxPlatformInfo &t) const
        { return !(*this == t); }


    // string -> enum conversions
    // ---------------------------------

    static wxOperatingSystemId GetOperatingSystemId(const wxString &name);
    static wxPortId GetPortId(const wxString &portname);

    static wxArchitecture GetArch(const wxString &arch);
    static wxEndianness GetEndianness(const wxString &end);

    // enum -> string conversions
    // ---------------------------------

    static wxString GetOperatingSystemFamilyName(wxOperatingSystemId os);
    static wxString GetOperatingSystemIdName(wxOperatingSystemId os);
    static wxString GetPortIdName(wxPortId port);
    static wxString GetPortIdShortName(wxPortId port);

    static wxString GetArchName(wxArchitecture arch);
    static wxString GetEndiannessName(wxEndianness end);

    // getters
    // -----------------

    int GetOSMajorVersion() const
        { return m_osVersionMajor; }
    int GetOSMinorVersion() const
        { return m_osVersionMinor; }

    int GetToolkitMajorVersion() const
        { return m_tkVersionMajor; }
    int GetToolkitMinorVersion() const
        { return m_tkVersionMinor; }

    wxOperatingSystemId GetOperatingSystemId() const
        { return m_os; }
    wxPortId GetPortId() const
        { return m_port; }
    wxArchitecture GetArchitecture() const
        { return m_arch; }
    wxEndianness GetEndianness() const
        { return m_endian; }


    // string getters
    // -----------------

    wxString GetOperatingSystemFamilyName() const
        { return GetOperatingSystemFamilyName(m_os); }
    wxString GetOperatingSystemIdName() const
        { return GetOperatingSystemIdName(m_os); }
    wxString GetPortIdName() const
        { return GetPortIdName(m_port); }
    wxString GetPortIdShortName() const
        { return GetPortIdShortName(m_port); }
    wxString GetArchName() const
        { return GetArchName(m_arch); }
    wxString GetEndiannessName() const
        { return GetEndiannessName(m_endian); }

    // setters
    // -----------------

    void SetOSVersion(int major, int minor)
        { m_osVersionMajor=major; m_osVersionMinor=minor; }
    void SetToolkitVersion(int major, int minor)
        { m_tkVersionMajor=major; m_tkVersionMinor=minor; }

    void SetOperatingSystemId(wxOperatingSystemId n)
        { m_os=n; }
    void SetPortId(wxPortId n)
        { m_port=n; }
    void SetArchitecture(wxArchitecture n)
        { m_arch=n; }
    void SetEndianness(wxEndianness n)
        { m_endian=n; }

    // miscellaneous
    // -----------------

    bool IsOk() const
    {
        return m_osVersionMajor != -1 && m_osVersionMinor != -1 &&
               m_os != wxOS_UNKNOWN &&
               m_tkVersionMajor != -1 && m_tkVersionMinor != -1 &&
               m_port != wxPORT_UNKNOWN &&
               m_arch != wxARCH_INVALID && m_endian != wxENDIAN_INVALID;
    }

    static bool IsUsingUniversalWidgets()
    {
    #ifdef __WXUNIVERSAL__
        return true;
    #else
        return false;
    #endif
    }


    // platform-specific functions
    // ----------------------------

#if 0       // TODO

#ifdef __LINUX__
    static wxString GetGNULibcVersion();
#endif

    // returns true if currently running platform is a mobile device
    static bool IsMobile();

#endif

protected:

    // OS stuff
    // -----------------

    // Version of the OS; valid if m_os != wxOS_UNKNOWN
    // (-1 means not initialized yet).
    int m_osVersionMajor, m_osVersionMinor;

    // Operating system ID.
    wxOperatingSystemId m_os;


    // toolkit
    // -----------------

    // Version of the underlying toolkit
    // (-1 means not initialized yet; zero means no toolkit).
    int m_tkVersionMajor, m_tkVersionMinor;

    // name of the wxWidgets port
    wxPortId m_port;


    // others
    // -----------------

    // architecture of the OS
    wxArchitecture m_arch;

    // endianness of the machine
    wxEndianness m_endian;

private:
    DECLARE_CLASS(wxPlatformInfo)
};


#if WXWIN_COMPATIBILITY_2_6
    #define wxUNKNOWN_PLATFORM      wxOS_UNKNOWN
    #define wxUnix                  wxOS_UNIX
    //#define wxWinPocketPC           wxOS_WINDOWS_POCKETPC
    //#define wxWinSmartPhone         wxOS_WINDOWS_SMARTPHONE
    #define wxWin95                 wxOS_WINDOWS_9X
    #define wxWIN95                 wxOS_WINDOWS_9X
    #define wxWINDOWS_NT            wxOS_WINDOWS_NT
    #define wxMSW                   wxOS_WINDOWS
    #define wxWinCE                 wxOS_WINDOWS_CE
    #define wxWIN32S                wxOS_WINDOWS_9X

    #define wxPalmOS                wxPORT_PALMOS
    #define wxOS2                   wxPORT_OS2
    #define wxMGL                   wxPORT_MGL
    #define wxCocoa                 wxPORT_MAC
    #define wxMac                   wxPORT_MAC
    #define wxMotif                 wxPORT_MOTIF
    #define wxGTK                   wxPORT_GTK
#endif

#endif // _WX_PLATINFO_H_

 	  	 
