/////////////////////////////////////////////////////////////////////////////
// Name:        scroll.cpp
// Purpose:     wxScrolledWindow sample
// Author:      Robert Roebling
// Modified by:
// Created:
// RCS-ID:      $Id: scroll.cpp,v 1.45 2006/10/02 05:36:26 PC Exp $
// Copyright:   (C) 1998 Robert Roebling, 2002 Ron Lee, 2003 Matt Gregory
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/image.h"
#include "wx/listctrl.h"
#include "wx/SpinCtrl.h"
#include "wx/sizer.h"
#include "wx/log.h"

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/toolbar.h>
#include <wx/tglbtn.h>

const int ID_MY_LIST = 10060;

// ----------------------------------------------------------------------
// a trivial example
// ----------------------------------------------------------------------

class MySimpleFrame;
class MySimpleCanvas;

// MySimpleCanvas

class MySimpleCanvas: public wxScrolledWindow
{
public:
    MySimpleCanvas() { }
    MySimpleCanvas( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size );
    
private:
    DECLARE_DYNAMIC_CLASS(MyCanvas)
    
};

IMPLEMENT_DYNAMIC_CLASS(MySimpleCanvas, wxScrolledWindow)

MySimpleCanvas::MySimpleCanvas( wxWindow *parent, wxWindowID id,const wxPoint &pos, const wxSize &size )
    : wxScrolledWindow( parent, id, pos, size, wxSUNKEN_BORDER, _T("test") )
{
    SetScrollRate( 10, 10 );
    SetVirtualSize( 92, 97 );
    SetBackgroundColour( *wxWHITE );

    wxBoxSizer *sizer = new wxBoxSizer( wxVERTICAL );
    wxListCtrl *pList= new wxListCtrl( this, ID_MY_LIST, wxDefaultPosition, wxSize(190,110), wxLC_LIST|wxLC_NO_HEADER|wxSUNKEN_BORDER );
    for (int i=0;i<20;i++)
      pList->InsertItem(0,wxT("test")); 
    sizer->Add( pList, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
     SetSizer(sizer);
  
  // This next line fixes the problem for this case, but does not work for more complex sizer trees.
  // For more complex cases, I call a wxWindow::Refresh for each EVT_SCROLLWIN event.
  // SetScrollbars(1, 1, sizer->CalcMin().x, sizer->CalcMin().y);  

    
 }



class MySimpleFrame: public wxFrame
{
public:
    MySimpleFrame();
    MySimpleCanvas         *m_canvas;
private:
    DECLARE_DYNAMIC_CLASS(MySimpleFrame)
};


IMPLEMENT_DYNAMIC_CLASS( MySimpleFrame, wxFrame )
MySimpleFrame::MySimpleFrame() : wxFrame( (wxFrame *)NULL, wxID_ANY, _T("wxScrolledWindow sample"),wxPoint(120,120), wxSize(150,150) )
{
    m_canvas = new MySimpleCanvas( this, wxID_ANY, wxPoint(0,0), wxSize(200,200) );
    m_canvas->EnableScrolling(true,true);
}


class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MySimpleFrame* frame = new MySimpleFrame();
    frame->Show();
    return true;
}

