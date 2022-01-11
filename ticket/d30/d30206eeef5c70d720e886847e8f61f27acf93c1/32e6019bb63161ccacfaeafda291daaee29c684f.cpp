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

#include "xh_sash.h"

#ifndef WX_PRECOMP
    #include "wx/log.h"
#endif

#include "wx/sashwin.h"
#include "wx/laywin.h"

/*
This class supports the following styles:

# wxSW_3D:
Draws a 3D effect sash and border.
# wxSW_3DSASH:
Draws a 3D effect sash.
# wxSW_3DBORDER:
Draws a 3D effect border.
# wxSW_BORDER:
*/

/*
enum wxSashEdgePosition:
wxSASH_TOP
wxSASH_RIGHT
wxSASH_BOTTOM
wxSASH_LEFT
wxSASH_NONE
*/

/* <bitmap stock_id="wxART_QUESTION"/> */

IMPLEMENT_DYNAMIC_CLASS(wxSashWindowXmlHandler, wxXmlResourceHandler)

wxSashWindowXmlHandler::wxSashWindowXmlHandler() : wxXmlResourceHandler()
{
    XRC_ADD_STYLE(wxSW_3D);
    XRC_ADD_STYLE(wxSW_3DSASH);
    XRC_ADD_STYLE(wxSW_3DBORDER);
    XRC_ADD_STYLE(wxSW_BORDER);

    AddWindowStyles();
}

wxObject *wxSashWindowXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(swindow, wxSashWindow);

    swindow->Create(m_parentAsWindow,
                     GetID(),
                     GetPosition(), GetSize(),
                     GetStyle(wxT("style"), wxCLIP_CHILDREN | wxSW_3D),
                     GetName());

    SetupWindow(swindow);
    //swindow->SetSashBorder(wxSashEdgePosition edge, bool hasBorder);
    //swindow->SetSashVisible(wxSashEdgePosition edge, bool visible);

    CreateChildren(swindow);

    return swindow;
}

bool wxSashWindowXmlHandler::CanHandle(wxXmlNode *node)
{
     return IsOfClass(node, wxT("wxSashWindow"));
}


// Sash Layout Window

IMPLEMENT_DYNAMIC_CLASS(wxSashLayoutWindowXmlHandler, wxXmlResourceHandler)

wxSashLayoutWindowXmlHandler::wxSashLayoutWindowXmlHandler() : wxXmlResourceHandler()
{
    XRC_ADD_STYLE(wxSW_3D);
    XRC_ADD_STYLE(wxSW_3DSASH);
    XRC_ADD_STYLE(wxSW_3DBORDER);
    XRC_ADD_STYLE(wxSW_BORDER);

    AddWindowStyles();
}

wxObject *wxSashLayoutWindowXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(swindow, wxSashLayoutWindow);

    swindow->Create(m_parentAsWindow,
                     GetID(),
                     GetPosition(), GetSize(),
                     GetStyle(wxT("style"), wxCLIP_CHILDREN | wxSW_3D),
                     GetName());

    SetupWindow(swindow);
    //swindow->SetSashBorder(wxSashEdgePosition edge, bool hasBorder);
    //swindow->SetSashVisible(wxSashEdgePosition edge, bool visible);

    CreateChildren(swindow);

    return swindow;
}

bool wxSashLayoutWindowXmlHandler::CanHandle(wxXmlNode *node)
{
     return IsOfClass(node, wxT("wxSashLayoutWindow"));
}

//#endif // wxUSE_XRC && wxUSE_SPLITTER
