/////////////////////////////////////////////////////////////////////////////
// Name:        xh_grd.h
// Purpose:     XML resource handler for the grid control
// Author:      Agron Selimaj
// Created:     2005/08/11
// RCS-ID:      $Id: xh_grd.h,v 0.1 2005/08/11 09:17:06 VS Exp $
// Copyright:   (c) 2005 Agron Selimaj, Freepour Controls Inc.
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "xh_grd.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_XRC

#include "wx/xrc/xh_grd.h"
#include <wx/grid.h>

IMPLEMENT_DYNAMIC_CLASS(wxGridXmlHandler, wxXmlResourceHandler)

wxGridXmlHandler::wxGridXmlHandler()
: wxXmlResourceHandler()
{
    XRC_ADD_STYLE(wxBU_AUTODRAW);
    XRC_ADD_STYLE(wxBU_LEFT);
    XRC_ADD_STYLE(wxBU_RIGHT);
    XRC_ADD_STYLE(wxBU_TOP);
    XRC_ADD_STYLE(wxBU_BOTTOM);
    XRC_ADD_STYLE(wxBU_EXACTFIT);
    AddWindowStyles();
}

wxObject *wxGridXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(grid, wxGrid)

    grid->Create(m_parentAsWindow,
                   GetID(),
                   GetPosition(), GetSize(),
                   GetStyle(wxT("style"), wxBU_AUTODRAW),
                   GetName());

    SetupWindow( grid);

    return grid;
}

bool wxGridXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("wxGrid"));
}

#endif // wxUSE_XRC

 	  	 
