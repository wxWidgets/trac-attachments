/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

const int  ID_PANEL1    = 1000;
const int  ID_PANEL3    = 1001;
const int  ID_BUTTON2    = 1002;
const int  ID_BUTTON3    = 1003;
const int  ID_BUTTON4    = 1004;
const int  ID_BUTTON5    = 1005;




// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};
class Frame1 : public wxFrame
{
public:
    // ctor(s)
    Frame1(const wxString& title);

};

Frame1::Frame1(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
	
		 Frame1* itemFrame1 = this;
		wxPanel* itemPanel2 = new wxPanel( itemFrame1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

		wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
		itemPanel2->SetSizer(itemBoxSizer3);

		wxButton* itemButton4 = new wxButton( itemPanel2, ID_BUTTON2, _("Button1"), wxDefaultPosition, wxSize(60, 25), 0 );
		itemBoxSizer3->Add(itemButton4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

		wxButton* itemButton5 = new wxButton( itemPanel2, ID_BUTTON3, _("Button2"), wxDefaultPosition, wxSize(60, 25), 0 );
		itemBoxSizer3->Add(itemButton5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

		wxButton* itemButton6 = new wxButton( itemPanel2, ID_BUTTON4, _("Button3"), wxDefaultPosition, wxSize(60, 25), 0 );
		itemBoxSizer3->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

		wxButton* itemButton7 = new wxButton( itemPanel2, ID_BUTTON5, _("Button4"), wxDefaultPosition, wxSize(60, 25), 0 );
		itemButton7->SetDefault();
		itemBoxSizer3->Add(itemButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

}
class Dialog1 : public wxDialog
{
public:
    // ctor(s)
    Dialog1(const wxString& title);

};

Dialog1::Dialog1(const wxString& title)
       : wxDialog(NULL, wxID_ANY, title)
{
	
		 Dialog1* itemDialog1 = this;
		wxPanel* itemPanel2 = new wxPanel( itemDialog1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

		wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
		itemPanel2->SetSizer(itemBoxSizer3);

		wxButton* itemButton4 = new wxButton( itemPanel2, ID_BUTTON2, _("Button1"), wxDefaultPosition, wxSize(60, 25), 0 );
		itemBoxSizer3->Add(itemButton4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

		wxButton* itemButton5 = new wxButton( itemPanel2, ID_BUTTON3, _("Button2"), wxDefaultPosition, wxSize(60, 25), 0 );
		itemBoxSizer3->Add(itemButton5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

		wxButton* itemButton6 = new wxButton( itemPanel2, ID_BUTTON4, _("Button3"), wxDefaultPosition, wxSize(60, 25), 0 );
		itemBoxSizer3->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

		wxButton* itemButton7 = new wxButton( itemPanel2, ID_BUTTON5, _("Button4"), wxDefaultPosition, wxSize(60, 25), 0 );
		itemButton7->SetDefault();
		itemBoxSizer3->Add(itemButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

}

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnDialog(wxCommandEvent& event);
    void OnFrame(wxCommandEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT,
    Minimal_Dialog = 10000,
    Minimal_Frame = 10001
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_MENU(Minimal_Dialog, MyFrame::OnDialog)
    EVT_MENU(Minimal_Frame, MyFrame::OnFrame)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame("Minimal wxWidgets App");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

    fileMenu->Append(Minimal_Dialog, "Open wxDialog", "Open Dialog");
    fileMenu->Append(Minimal_Frame, "Open wxFrame", "Open Frame");
    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);


#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
#endif // wxUSE_STATUSBAR


}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "Welcome to %s!\n"
                    "\n"
                    "This is the minimal wxWidgets sample\n"
                    "running under %s.",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}
void MyFrame::OnDialog(wxCommandEvent& WXUNUSED(event))
{	
	Dialog1 *dialog1 = new Dialog1("Minimal wxWidgets App");

	dialog1->Show(true);

    
}
void MyFrame::OnFrame(wxCommandEvent& WXUNUSED(event))
{
	Frame1 *frame1 = new Frame1("Minimal wxWidgets App");

	frame1->Show(true);
    
}
