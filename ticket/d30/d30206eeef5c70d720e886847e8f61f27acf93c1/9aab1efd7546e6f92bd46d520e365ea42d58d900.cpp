/////////////////////////////////////////////////////////////////////////////
// Name:        src/xrc/xh_sash.cpp
// Purpose:     XRC resource for wxSashWindow
// Author:      webmaster@audice.com, Ilya A Zimnovich
// Created:     2010/06/30
// Copyright:   (c) 2010 webmaster@audice.com, Ilya A Zimnovich
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

//#if wxUSE_XRC && wxUSE_SPLITTER

#include "xh_toolbook.h"

#ifndef WX_PRECOMP
    #include "wx/log.h"
#endif

#include "wx/toolbook.h"

IMPLEMENT_DYNAMIC_CLASS(wxToolbookXmlHandler, wxXmlResourceHandler)

wxToolbookXmlHandler::wxToolbookXmlHandler() : wxXmlResourceHandler()
{

    XRC_ADD_STYLE(wxBK_TOP); // controller above pages
    XRC_ADD_STYLE(wxBK_BOTTOM); // controller below pages
    XRC_ADD_STYLE(wxBK_LEFT); // controller on the left
    XRC_ADD_STYLE(wxBK_RIGHT); // controller on the right
    XRC_ADD_STYLE(wxBK_DEFAULT); // native controller placement

    XRC_ADD_STYLE(wxTBK_BUTTONBAR);
    XRC_ADD_STYLE(wxTBK_HORZ_LAYOUT);

    AddWindowStyles();
}

wxObject *wxToolbookXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(swindow, wxToolbook);

    swindow->Create(m_parentAsWindow,
                     GetID(),
                     GetPosition(), GetSize(),
                     GetStyle(wxT("style"), 0),
                     GetName());

    SetupWindow(swindow);
    CreateChildren(swindow);

    return swindow;
}

bool wxToolbookXmlHandler::CanHandle(wxXmlNode *node)
{
     return IsOfClass(node, wxT("wxToolbook"));
}
