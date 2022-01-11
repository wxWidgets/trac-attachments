///////////////////////////////////////////////////////////////////////////////
// Name:        src/common/platinfo.cpp
// Purpose:     implements wxPlatformInfo class
// Author:      Francesco Montorsi
// Modified by:
// Created:     7.07.2006 (based over wxToolkitInfo)
// RCS-ID:      $Id$
// Copyright:   (c) 2006 Francesco Montorsi
// License:     wxWindows license
///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// for compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/utils.h"
#endif //WX_PRECOMP

#include "wx/platinfo.h"
#include "wx/apptrait.h"

#include "wx/math.h"        // for wxRound

// used by wxPlatformInfo::GetOperatingSystemIdName
extern double log(double);

// a little trick to get the index of the string for this wxOperatingSystemId
// (whose values are not linear but exponential with base 2)
#define wxGET_INDEX_FROM_ENUMVALUE(value)   \
    ((size_t)wxRound(log((double)value)/log((double)2.0)))



// ----------------------------------------------------------------------------
// wxPlatformInfo
// ----------------------------------------------------------------------------

IMPLEMENT_CLASS(wxPlatformInfo, wxObject)

wxString wxOperatingSystemIdName[] =
{
    _T("Apple Mac OS"),
    _T("Apple Mac OS X"),

    _T("Microsoft Windows 9X"),
    _T("Microsoft Windows NT"),
    _T("Microsoft Windows Micro"),
    _T("Microsoft Windows CE"),

    _T("Linux"),
    _T("FreeBSD"),
    _T("OpenBSD"),
    _T("NetBSD"),

    _T("SunOS"),
    _T("AIX"),
    _T("HPUX"),

    _T("DOS"),
    _T("OS/2")
};

wxString wxPortIdName[] =
{
    _T("wxBase"),
    _T("wxMSW"),
    _T("wxMotif"),
    _T("wxGTK"),
    _T("wxMGL"),
    _T("wxX11"),
    _T("wxOS2"),
    _T("wxMac"),
    _T("wxWinCE"),
    _T("wxPalmOS")
};

wxString wxArchitectureName[] =
{
    _T("32 bit"),
    _T("64 bit")
};

wxString wxEndiannessName[] =
{
    _T("Big endian"),
    _T("Little endian"),
    _T("PDP endian")
};

wxPlatformInfo::wxPlatformInfo()
{
    // autodetect all informations

    m_port = wxTheApp->GetTraits()->GetToolkitVersion(&m_tkVersionMajor, &m_tkVersionMinor);
    m_os = wxGetOsVersion(&m_osVersionMajor, &m_osVersionMinor);
    m_endian = wxIsPlatformLittleEndian() ? wxENDIAN_LITTLE : wxENDIAN_BIG;
    m_arch = wxIsPlatform64Bit() ? wxARCH_64 : wxARCH_32;
}

wxPlatformInfo::wxPlatformInfo(wxPortId pid, int tkMajor, int tkMinor,
                               wxOperatingSystemId id, int osMajor, int osMinor,
                               wxArchitecture arch, wxEndianness endian)
{
    m_tkVersionMajor = tkMajor;
    m_tkVersionMinor = tkMinor;
    m_port = pid;

    m_os = id;
    m_osVersionMajor = osMajor;
    m_osVersionMinor = osMinor;

    m_endian = endian;
    m_arch = arch;
}

bool wxPlatformInfo::operator ==(const wxPlatformInfo &t) const
{
    return m_tkVersionMajor == t.m_tkVersionMajor &&
           m_tkVersionMinor == t.m_tkVersionMinor &&
           m_osVersionMajor == t.m_osVersionMajor &&
           m_osVersionMinor == t.m_osVersionMinor &&
           m_os == t.m_os &&
           m_port == t.m_port &&
           m_arch == t.m_arch &&
           m_endian == t.m_endian;
}



// ----------------------------------------------------------------------------
// wxPlatformInfo - enum -> string conversions
// ----------------------------------------------------------------------------

wxString wxPlatformInfo::GetOperatingSystemFamilyName(wxOperatingSystemId os)
{
    if (os & wxOS_MAC)
        return _T("Macintosh");
    else if (os & wxOS_WINDOWS)
        return _T("Windows");
    else if (os & wxOS_UNIX)
        return _T("Unix");
    else if (os == wxOS_DOS)
        return _T("DOS");
    else if (os == wxOS_OS2)
        return _T("OS/2");

    return _T("Unknown");
}

wxString wxPlatformInfo::GetOperatingSystemIdName(wxOperatingSystemId os)
{
    wxASSERT(os > wxOS_UNKNOWN && os <= (1 << (wxOS_MAX-1)));
    return wxOperatingSystemIdName[wxGET_INDEX_FROM_ENUMVALUE(os)];
}

wxString wxPlatformInfo::GetPortIdName(wxPortId port)
{
    wxASSERT(port > wxPORT_UNKNOWN && port <= (1 << (wxPORT_MAX-1)));
    wxString ret = wxPortIdName[wxGET_INDEX_FROM_ENUMVALUE(port)];

    if (IsUsingUniversalWidgets())
        ret += wxT("/wxUniversal");
    return ret;
}

wxString wxPlatformInfo::GetPortIdShortName(wxPortId port)
{
    wxASSERT(port > wxPORT_UNKNOWN && port <= (1 << (wxPORT_MAX-1)));
    wxString ret = wxPortIdName[wxGET_INDEX_FROM_ENUMVALUE(port)];
    ret = ret.Mid(2).Lower();       // remove 'wx' prefix

    if (IsUsingUniversalWidgets())
        ret += wxT("univ");
    return ret;
}

wxString wxPlatformInfo::GetArchName(wxArchitecture arch)
{
    return wxArchitectureName[arch];
}

wxString wxPlatformInfo::GetEndiannessName(wxEndianness end)
{
    return wxEndiannessName[end];
}


// ----------------------------------------------------------------------------
// wxPlatformInfo - string -> enum conversions
// ----------------------------------------------------------------------------

wxOperatingSystemId wxPlatformInfo::GetOperatingSystemId(const wxString &str)
{
    for (size_t i=0; i < wxOS_MAX; i++)
        if (wxOperatingSystemIdName[i].CmpNoCase(str) == 0)
            return (wxOperatingSystemId)(1 << i);

    return wxOS_UNKNOWN;
}

wxPortId wxPlatformInfo::GetPortId(const wxString &str)
{
    // recognize both short and long port names

    for (size_t i=0; i < wxPORT_MAX; i++)
    {
        wxPortId current = (wxPortId)(1 << i);

        if (wxPortIdName[i].CmpNoCase(str) == 0)
            return current;
        if (GetPortIdShortName(current).CmpNoCase(str) == 0)
            return current;
    }

    return wxPORT_UNKNOWN;
}

wxArchitecture wxPlatformInfo::GetArch(const wxString &arch)
{
    wxArchitecture ret = wxARCH_INVALID;
    if (arch.Contains(wxT("32"))) ret = wxARCH_32;
    if (arch.Contains(wxT("64"))) ret = wxARCH_64;
    return ret;
}

wxEndianness wxPlatformInfo::GetEndianness(const wxString &end)
{
    wxEndianness ret = wxENDIAN_INVALID;

    // FIXME: here we would need a StartsWith which is case insensitive
    if (end.Lower().StartsWith(wxT("little"))) ret = wxENDIAN_LITTLE;
    if (end.Lower().StartsWith(wxT("big"))) ret = wxENDIAN_BIG;
    return ret;
}


 	  	 
