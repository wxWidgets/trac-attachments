/*
 *  combobox.cpp
 *  ComboBox
 *
 *  Created by Per Johansson on Fri Nov 21 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */
// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif



//--------------------------------------------------------------

//Test combobox..

#define ID_TESTCOMBO 10001

//ComboBox
class MyComboBox : public wxComboBox
{
public:
	MyComboBox(wxWindow *parent, wxWindowID id, const wxString &value,
               const wxPoint &pos, const wxSize &size, int n = 0, const wxString choices[] = NULL, int style = 0, const wxValidator &validator=wxDefaultValidator,const wxString &name=wxTextCtrlNameStr)
        : wxComboBox(parent, id, value, pos, size, n, choices, style, validator, name)
    {
    }
	void OnClose(wxCommandEvent &event);
    void OnChar(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
	void OnKeyDown(wxKeyEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyComboBox, wxComboBox)
	EVT_COMBOBOX(ID_TESTCOMBO,MyComboBox::OnClose)
	EVT_TEXT(ID_TESTCOMBO,MyComboBox::OnChar)
	EVT_KEY_UP(MyComboBox::OnKeyUp)
	EVT_KEY_DOWN(MyComboBox::OnKeyDown)
END_EVENT_TABLE()

void MyComboBox::OnClose(wxCommandEvent &event)
{
	fprintf(stderr,"Catched a Close ComboBox event\n");
}

void MyComboBox::OnChar(wxKeyEvent &event)
{
	fprintf(stderr,"Catched a OnChar event\n");
}

void MyComboBox::OnKeyUp(wxKeyEvent& event)
{
	fprintf(stderr,"Catched a KeyUp event\n");
}

void MyComboBox::OnKeyDown(wxKeyEvent& event)
{
	fprintf(stderr,"Catched a KeyDown event\n");
}

//--------------------------------------------------------------










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

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
private:
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
END_EVENT_TABLE()



// Create a new application object: this macro will allow wxWindows to create
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
    // create the main application window
    MyFrame *frame = new MyFrame(_T("ComboBox test"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(TRUE);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned FALSE here, the
    // application would exit immediately.
    return TRUE;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, -1, title)
{

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *menuFile = new wxMenu;

    // the "About" item should be in the help menu
    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));


    wxString TestStrings[3];
	TestStrings[0].Printf("Test 1");
	TestStrings[1].Printf("Test 2");
	TestStrings[2].Printf("Test 3");

	wxComboBox *testcombo = new MyComboBox(this, ID_TESTCOMBO, _("0.00"), wxDefaultPosition, wxDefaultSize, 3, TestStrings, wxCB_DROPDOWN );

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR && !defined(__WXWINCE__)
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWindows!"));
#endif // wxUSE_STATUSBAR
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // TRUE is to force the frame to close
    Close(TRUE);
}

 	  	 
