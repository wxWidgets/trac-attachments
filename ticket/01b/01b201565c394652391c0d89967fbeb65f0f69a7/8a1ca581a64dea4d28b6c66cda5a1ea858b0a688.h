/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_simplehtmllbox.h
// Purpose:     XML resource handler for wxSimpleHtmlListBox
// Author:      Francesco Montorsi
// Created:     2006/10/21
// RCS-ID:      $Id$
// Copyright:   (c) 2006 Francesco Montorsi
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_SIMPLEHTMLLISTBOX_H_
#define _WX_XH_SIMPLEHTMLLISTBOX_H_

#include "wx/xrc/xmlres.h"
#include "wx/xrc/xh_listb.h"

#if wxUSE_XRC && wxUSE_HTML

class WXDLLIMPEXP_XRC wxSimpleHtmlListBoxXmlHandler : public wxXmlResourceHandler
{
    DECLARE_DYNAMIC_CLASS(wxSimpleHtmlListBoxXmlHandler)

public:
    wxSimpleHtmlListBoxXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);

private:
    bool m_insideBox;
    wxArrayString strList;
};

#endif // wxUSE_XRC && wxUSE_HTML

#endif // _WX_XH_SIMPLEHTMLLISTBOX_H_

 	  	 
