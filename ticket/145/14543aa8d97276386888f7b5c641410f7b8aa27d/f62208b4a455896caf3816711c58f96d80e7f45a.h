/////////////////////////////////////////////////////////////////////////////
// Name:        datstrm.h
// Purpose:     Data stream classes
// Author:      Guilhem Lavaux
// Modified by: Mickael Gilabert (14/06/03)
// Created:     28/06/1998
// RCS-ID:      $Id: datstrm.h,v 1.26 2003/03/17 10:33:30 JS Exp $
// Copyright:   (c) Guilhem Lavaux
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_DATSTREAM_H_
#define _WX_DATSTREAM_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "datstrm.h"
#endif

#include "wx/stream.h"
#include "wx/longlong.h"
#include "wx/strconv.h"

#if wxUSE_STREAMS

class WXDLLEXPORT wxDataInputStream
{
public:
#if wxUSE_UNICODE
    wxDataInputStream(wxInputStream& s, wxMBConv& conv = wxConvUTF8);
#else
    wxDataInputStream(wxInputStream& s);
#endif
    ~wxDataInputStream();
    
    bool IsOk() { return m_input->IsOk(); }

    wxUint64 Read64();
    wxUint32 Read32();
    wxUint16 Read16();
    wxUint8 Read8();
    float ReadFloat();
    double ReadDouble();

    void Read64(wxUint64 *buffer, int size);
    void Read32(wxUint32 *buffer, int size);
    void Read16(wxUint16 *buffer, int size);
    void Read8(wxUint8 *buffer, int size);
    void ReadFloat(float *buffer, int size);
    void ReadDouble(double *buffer, int size);

    wxString ReadString();

    wxDataInputStream& operator>>(wxString& s);
    wxDataInputStream& operator>>(wxInt8& c);
    wxDataInputStream& operator>>(wxInt16& i);
    wxDataInputStream& operator>>(wxInt32& i);
    wxDataInputStream& operator>>(wxUint8& c);
    wxDataInputStream& operator>>(wxUint16& i);
    wxDataInputStream& operator>>(wxUint32& i);
    wxDataInputStream& operator>>(wxUint64& i);
    wxDataInputStream& operator>>(double& i);
    wxDataInputStream& operator>>(float& f);

    void BigEndianOrdered(bool be_order) { m_be_order = be_order; }

protected:
    wxInputStream *m_input;
    bool m_be_order;
#if wxUSE_UNICODE
    wxMBConv& m_conv;
#endif
};

class WXDLLEXPORT wxDataOutputStream
{
public:
#if wxUSE_UNICODE
    wxDataOutputStream(wxOutputStream& s, wxMBConv& conv = wxConvUTF8);
#else
    wxDataOutputStream(wxOutputStream& s);
#endif
    ~wxDataOutputStream();

    bool IsOk() { return m_output->IsOk(); }

    void Write64(wxUint64 i);
    void Write32(wxUint32 i);
    void Write16(wxUint16 i);
    void Write8(wxUint8 i);
    void WriteFloat(float f);
    void WriteDouble(double d);
    void WriteString(const wxString& string);

    void Write64(const wxUint64 *buffer, int size);
    void Write32(const wxUint32 *buffer, int size);
    void Write16(const wxUint16 *buffer, int size);
    void Write8(const wxUint8 *buffer, int size);
    void WriteFloat(const float *buffer, int size);
    void WriteDouble(const double *buffer, int size);

    wxDataOutputStream& operator<<(const wxChar *string);
    wxDataOutputStream& operator<<(const wxString& string);
    wxDataOutputStream& operator<<(wxInt8 c);
    wxDataOutputStream& operator<<(wxInt16 i);
    wxDataOutputStream& operator<<(wxInt32 i);
    wxDataOutputStream& operator<<(wxUint8 c);
    wxDataOutputStream& operator<<(wxUint16 i);
    wxDataOutputStream& operator<<(wxUint32 i);
    wxDataOutputStream& operator<<(wxUint64 i);
    wxDataOutputStream& operator<<(double f);
    wxDataOutputStream& operator<<(float f);

    void BigEndianOrdered(bool be_order) { m_be_order = be_order; }

protected:
    wxOutputStream *m_output;
    bool m_be_order;
#if wxUSE_UNICODE
    wxMBConv& m_conv;
#endif
};

#endif
  // wxUSE_STREAMS

#endif
    // _WX_DATSTREAM_H_

 	  	 
