/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_sash.h
// Purpose:     XRC resource handler for wxSashWindow
// Author:      Ilya A Zimnovich
// Created:     2010-06-30
// Copyright:   (c) 2010 Ilya A Zimnovich <webmaster@audice.com>
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_SASH_H
#define _WX_XH_SASH_H

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC && wxUSE_SASH

class WXDLLIMPEXP_XRC wxSashWindowXmlHandler : public wxXmlResourceHandler
{
public:
    wxSashWindowXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);

private:
    wxDECLARE_DYNAMIC_CLASS(wxSashWindowXmlHandler);
};


class WXDLLIMPEXP_XRC wxSashLayoutWindowXmlHandler : public wxXmlResourceHandler
{
public:
    wxSashLayoutWindowXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);

private:
    wxDECLARE_DYNAMIC_CLASS(wxSashLayoutWindowXmlHandler);
};

#endif // wxUSE_XRC && wxUSE_SASH

#endif /* _WX_XH_SASH_H */
