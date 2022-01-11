//
/////////////////////////////////////////////////////////////////////////////
// Stripped from layout sample to show problem with FlexGridSizer.
/////////////////////////////////////////////////////////////////////////////
// Name:        layout.cpp
// Purpose:     Layout sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: layout.cpp,v 1.41 2005/01/18 21:21:57 RD Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/sizer.h"
#include "wx/gbsizer.h"
#include "wx/statline.h"



// Define a new application
class MyApp: public wxApp
{
public:
    MyApp(){};
    bool OnInit();
};

// the main frame class
class MyFrame : public wxFrame
{
public:
    MyFrame();

    void OnQuit(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};


// controls and menu constants
enum
{
    LAYOUT_QUIT = 100,
    LAYOUT_ABOUT 
};


// #include "layout.h"

// ----------------------------------------------------------------------------
// MyApp
// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
  // Create the main frame window
  MyFrame *frame = new MyFrame;

  frame->Show(true);

  return true;
}

// ----------------------------------------------------------------------------
// MyFrame
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(LAYOUT_QUIT, MyFrame::OnQuit)

END_EVENT_TABLE()

// Define my frame constructor
MyFrame::MyFrame()
       : wxFrame(NULL, wxID_ANY, _T("wxWidgets Layout Demo"),
                 wxDefaultPosition, wxDefaultSize,
                 wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
{
  // Make a menubar
  wxMenu *file_menu = new wxMenu;


  file_menu->AppendSeparator();
  file_menu->Append(LAYOUT_QUIT, _T("E&xit"), _T("Quit program"));

  wxMenu *help_menu = new wxMenu;
  help_menu->Append(LAYOUT_ABOUT, _T("&About"), _T("About layout demo"));

  wxMenuBar *menu_bar = new wxMenuBar;

  menu_bar->Append(file_menu, _T("&File"));
  menu_bar->Append(help_menu, _T("&Help"));

  // Associate the menu bar with the frame
  SetMenuBar(menu_bar);

#if wxUSE_STATUSBAR
  CreateStatusBar(2);
  SetStatusText(_T("wxWidgets layout demo"));
#endif // wxUSE_STATUSBAR

  wxPanel* p = new wxPanel(this, -1);
  
  // we want to get a dialog that is stretchable because it
  // has a text ctrl in the middle. at the bottom, we have
  // two buttons which.

  wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );


  wxFlexGridSizer *sizerFlex;

    // consttuct the first column
    wxSizer *sizerCol1 = new wxBoxSizer(wxVERTICAL);
    sizerFlex = new wxFlexGridSizer(2, 2);
    for ( int i = 0; i < 2; i++ )
    {
        for ( int j = 0; j < 2; j++ )
        {
           if ( i==0 && j== 0 ){
		wxWindow *ww;
		ww = new wxWindow( 
				p, 
				wxID_ANY,
                            	wxDefaultPosition,
                            	wxDefaultSize
				);

// Explicitly setting MinSize will hide the problem.
//              ww->SetMinSize( wxSize(1,1) );

                sizerFlex->Add( ww,
                                0, 
                                wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALL, 
                                3);
				
           } else {
                sizerFlex->Add(new wxStaticText
                           (
                            p,
                            wxID_ANY,
                            wxString::Format(_T("(%d, %d)"), i + 1, j + 1),
                            wxDefaultPosition,
                            wxDefaultSize,
                            wxALIGN_CENTER
                           ),
                       0, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALL, 3);
	    }
        }
    }
  sizerFlex->AddGrowableCol(0);
  sizerFlex->AddGrowableRow(0);

  sizerCol1->Add(sizerFlex, 1, wxALL | wxEXPAND, 10);

  topsizer->Add(sizerCol1, 1, wxALL | wxEXPAND, 1 );

  p->SetSizer( topsizer );
  
  // don't allow frame to get smaller than what the sizers tell it and also set
  // the initial size as calculated by the sizers
  topsizer->SetSizeHints( this );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
    Close(true);
}




 	  	 
