/////////////////////////////////////////////////////////////////////////////
// Name:        ListBookBug.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      The Code Lurker, with code from wxWidget sample, "minimal".
// Created:     04/18/02
// Copyright:   Public Domain
/////////////////////////////////////////////////////////////////////////////


#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "../sample.xpm"
#endif

#include <wx/listbook.h>
#include <wx/listctrl.h>

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

class MyApp : public wxApp
{
public:
     virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    wxListbook* m_listbook1;
    wxPanel* m_panel1;
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyFrame *frame = new MyFrame(_T("ListBookBug"));

    frame->Show(true);

    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
  SetSize(700,200);

    m_listbook1 = new wxListbook( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxLB_DEFAULT );

    m_panel1 = new wxPanel( m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_listbook1->AddPage( m_panel1, wxT("Some really ."), true );
}


 	  	 
