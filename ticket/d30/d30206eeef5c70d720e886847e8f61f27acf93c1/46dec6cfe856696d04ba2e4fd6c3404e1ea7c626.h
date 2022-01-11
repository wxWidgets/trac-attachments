/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_toolbook.h
// Purpose:     XRC resource for wxSashWindow
// Author:      webmaster@audice.com, Ilya A Zimnovich
// Created:     2010/07/01
// Copyright:   (c) 2010 webmaster@audice.com, Ilya A Zimnovich
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _XH_TOOLBOOK_H
#define	_XH_TOOLBOOK_H

#include "wx/xrc/xmlres.h"

//#if wxUSE_XRC && wxUSE_SPLITTER

class WXDLLIMPEXP_XRC wxToolbookXmlHandler : public wxXmlResourceHandler
{
    DECLARE_DYNAMIC_CLASS(wxToolbookXmlHandler)

public:
    wxToolbookXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};

#endif	/* _XH_TOOLBOOK_H */
