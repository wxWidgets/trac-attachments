/////////////////////////////////////////////////////////////////////////////
// Name:        display.h
// Purpose:     wxDisplay class
// Author:      Brian Victor
// Modified by: 
// Created:     12/05/02
// RCS-ID:      $Id: display.h,v 1.2 2002/08/31 11:29:10 GD Exp $
// Copyright:   (c) wxWindows team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GTK_DISPLAY_H_
#define _WX_GTK_DISPLAY_H_

#if wxUSE_DISPLAY

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "display.h"
#endif

class wxRect;
class wxString;
class wxDisplayUnixPriv;

class WXDLLEXPORT wxDisplay : public wxDisplayBase
{

  public:
    wxDisplay ( size_t index = 0 );

    virtual wxRect GetGeometry() const;
    virtual int GetDepth() const;
    virtual wxString GetName() const;

    ~wxDisplay();

  private:
    wxDisplayUnixPriv *m_priv;

    DECLARE_NO_COPY_CLASS(wxDisplay);
};

#endif // wxUSE_DISPLAY

#endif // _WX_GTK_DISPLAY_H_

 	  	 
