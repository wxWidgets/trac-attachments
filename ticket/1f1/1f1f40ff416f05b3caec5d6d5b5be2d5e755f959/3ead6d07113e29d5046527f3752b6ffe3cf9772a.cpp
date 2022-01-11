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

#ifdef ORIGINAL_MINIMAL
// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};
#endif

///////////////////
// patch code

////@begin control identifiers
#define ID_START 10000
#define ID_TEXTCTRL 10001
#define ID_RADIOBUTTON 10002
#define ID_RADIOBUTTON1 10003
#define ID_RADIOBUTTON2 10004
#define SYMBOL_START_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_START_TITLE _("start")
#define SYMBOL_START_IDNAME ID_START
#define SYMBOL_START_SIZE wxSize(400, 300)
#define SYMBOL_START_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CStartDlg class declaration
 */

class CStartDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CStartDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CStartDlg();
    CStartDlg( wxWindow* parent, wxWindowID id = SYMBOL_START_IDNAME, const wxString& caption = SYMBOL_START_TITLE, const wxPoint& pos = SYMBOL_START_POSITION, const wxSize& size = SYMBOL_START_SIZE, long style = SYMBOL_START_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_START_IDNAME, const wxString& caption = SYMBOL_START_TITLE, const wxPoint& pos = SYMBOL_START_POSITION, const wxSize& size = SYMBOL_START_SIZE, long style = SYMBOL_START_STYLE );

    /// Destructor
    ~CStartDlg();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CStartDlg event handler declarations

////@end CStartDlg event handler declarations

////@begin CStartDlg member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CStartDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CStartDlg member variables
////@end CStartDlg member variables
};



/*
 * CStartDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS(CStartDlg, wxDialog)


/*
 * start event table definition
 */

	BEGIN_EVENT_TABLE(CStartDlg, wxDialog)

	////@begin start event table entries
	////@end start event table entries

	END_EVENT_TABLE()


	/*
	 * start constructors
	 */

	CStartDlg::CStartDlg()
{
	Init();
}

CStartDlg::CStartDlg(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
	Init();
	Create(parent, id, caption, pos, size, style);
}


/*
 * CStartDlg creator
 */

bool CStartDlg::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
	////@begin CStartDlg creation
	SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS);
	wxDialog::Create(parent, id, caption, pos, size, style);

	CreateControls();
	if (GetSizer())
	{
		GetSizer()->SetSizeHints(this);
	}
	Centre();
	////@end CStartDlg creation
	return true;
}


/*
 * CStartDlg destructor
 */

CStartDlg::~CStartDlg()
{
	////@begin CStartDlg destruction
	////@end CStartDlg destruction
}


/*
 * Member initialisation
 */

void CStartDlg::Init()
{
	////@begin CStartDlg member initialisation
	////@end CStartDlg member initialisation
}


/*
 * Control creation for CStartDlg
 */
//#define NO_PROBLEM
void CStartDlg::CreateControls()
{
	////@begin CStartDlg content construction
	CStartDlg* itemDialog1 = this;

	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxStaticText* itemStaticText1 = new wxStaticText(itemDialog1, wxID_STATIC, _("top of window"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer2->Add(itemStaticText1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, wxDLG_UNIT(itemDialog1, wxSize(3, -1)).x);

#ifdef NO_PROBLEM
	wxTextCtrl* itemTextCtrl2 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
#else
// got a problem
	wxTextCtrl* itemTextCtrl2 = new wxTextCtrl(itemDialog1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
#endif
	itemBoxSizer2->Add(itemTextCtrl2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, wxDLG_UNIT(itemDialog1, wxSize(3, -1)).x);

	wxRadioButton * itemRadioButton3 = new wxRadioButton(itemDialog1, ID_RADIOBUTTON, _("Radiobutton"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	itemRadioButton3->SetValue(true);
	itemBoxSizer2->Add(itemRadioButton3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, wxDLG_UNIT(itemDialog1, wxSize(3, -1)).x);

	wxRadioButton * itemRadioButton4 = new wxRadioButton(itemDialog1, ID_RADIOBUTTON1, _("Radiobutton"), wxDefaultPosition, wxDefaultSize, 0);
	itemRadioButton4->SetValue(false);
	itemBoxSizer2->Add(itemRadioButton4, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, wxDLG_UNIT(itemDialog1, wxSize(3, -1)).x);

	wxRadioButton * itemRadioButton5 = new wxRadioButton(itemDialog1, ID_RADIOBUTTON2, _("Radiobutton"), wxDefaultPosition, wxDefaultSize, 0);
	itemRadioButton5->SetValue(false);
	itemBoxSizer2->Add(itemRadioButton5, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, wxDLG_UNIT(itemDialog1, wxSize(3, -1)).x);

	wxStaticText * itemStaticText6 = new wxStaticText(itemDialog1, wxID_STATIC, _("bottom"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer2->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, wxDLG_UNIT(itemDialog1, wxSize(3, -1)).x);

	////@end CStartDlg content construction
}


/*
 * Should we show tooltips?
 */

bool CStartDlg::ShowToolTips()
{
	return true;
}

/*
 * Get bitmap resources
 */

wxBitmap CStartDlg::GetBitmapResource(const wxString & name)
{
	// Bitmap retrieval
////@begin CStartDlg bitmap retrieval
	wxUnusedVar(name);
	return wxNullBitmap;
	////@end CStartDlg bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon CStartDlg::GetIconResource(const wxString & name)
{
	// Icon retrieval
////@begin CStartDlg icon retrieval
	wxUnusedVar(name);
	return wxNullIcon;
	////@end CStartDlg icon retrieval
}







// end patch code
//////////////////////////////////////

#ifdef ORIGINAL_MINIMAL

////////////////
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
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

#endif
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

/////////////////
// patch code
	CStartDlg* mainWindow = new CStartDlg(NULL);
	mainWindow->ShowModal();
	mainWindow->Destroy();
	// A modal dialog application should return false to terminate the app.
	return false;
// end patch code
//////////////////////

#ifdef ORIGINAL_MINIMAL
    // create the main application window
    MyFrame *frame = new MyFrame("Minimal wxWidgets App");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
#endif
    return true;
}

#ifdef ORIGINAL_MINIMAL
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
#endif
