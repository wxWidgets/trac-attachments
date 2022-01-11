/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_sash.h
// Purpose:     XRC resource for wxSashWindow
// Author:      webmaster@audice.com, Ilya A Zimnovich
// Created:     2010/06/30
// Copyright:   (c) 2010 webmaster@audice.com, Ilya A Zimnovich
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _XH_SASH_H
#define	_XH_SASH_H

#include "wx/xrc/xmlres.h"

//#if wxUSE_XRC && wxUSE_SPLITTER

class WXDLLIMPEXP_XRC wxSashWindowXmlHandler : public wxXmlResourceHandler
{
    DECLARE_DYNAMIC_CLASS(wxSashWindowXmlHandler)

public:
    wxSashWindowXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};


class WXDLLIMPEXP_XRC wxSashLayoutWindowXmlHandler : public wxXmlResourceHandler
{
    DECLARE_DYNAMIC_CLASS(wxSashLayoutWindowXmlHandler)

public:
    wxSashLayoutWindowXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};

//#endif // wxUSE_XRC && wxUSE_SPLITTER


#endif	/* _XH_SASH_H */
