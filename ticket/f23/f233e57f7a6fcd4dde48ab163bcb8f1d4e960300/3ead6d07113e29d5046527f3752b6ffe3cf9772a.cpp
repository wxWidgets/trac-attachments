/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: minimal.cpp,v 1.66 2004/05/25 11:18:01 JS Exp $
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
#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "../sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

#include "wx/notebook.h"

// CFileControl header
class CFileControl : public wxPanel
{
public:
	CFileControl(wxPanel *tab,
		const wxPoint& point,
		const wxSize& size);

	virtual ~CFileControl();

	void OnComboChoice(wxCommandEvent& event);
	void Import(wxCommandEvent& event);
	void Remove(wxCommandEvent& event);

protected:
	wxStaticBox *m_pGroupBox;
	wxComboBox *m_pFileList;
	wxStaticText *m_pSndName;
	wxButton *m_pPlayBn, *m_pImportBn, *m_pRemoveBn;

	// Update file and file files list
	void UpdateFile(void) throw ();

	//DECLARE_EVENT_TABLE()
};
//////////////////////////////////////////////////

// CTab header
class CTab: public wxPanel
{
public:
	wxPanel *glass;
	CTab(wxWindow *frame);
	virtual ~CTab();

	//void OnSize(wxSizeEvent& event);

	CFileControl *m_pFileControl;

private:
	inline int GetControlWidth(void);

	//DECLARE_EVENT_TABLE()
};
//////////////////////////////////////////////////

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
	wxPanel *m_pPanel;
	wxNotebook *m_pNotebook;

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

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
	Minimal_Notebook = 100,
	Minimal_Cmbbox = 101,
	Minimal_Remove = 102,
	Minimal_Import = 103
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
	EVT_COMBOBOX(Minimal_Cmbbox, CFileControl::OnComboChoice)
	EVT_BUTTON(Minimal_Remove, CFileControl::Remove)
	EVT_BUTTON(Minimal_Import, CFileControl::Import)
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
    // create the main application window
    MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));

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
    wxMenu *menuFile = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWidgets!"));
#endif // wxUSE_STATUSBAR

	m_pPanel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(400, 200));
	m_pNotebook = new wxNotebook(m_pPanel, Minimal_Notebook, wxPoint(-1, -1), wxSize(400, 200));
	CTab *tab;
	for (int i = 0; i < 4; i ++)
	{
		tab = new CTab(m_pNotebook);
		m_pNotebook->AddPage(tab, wxString::Format(wxT("Tab %i"), i).GetData());
	}
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the About dialog of the minimal sample.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, _T("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

// CTab source
CTab::CTab(wxWindow *frame)
	   : wxPanel(frame, -1, wxPoint(-1, -1), wxSize(400, 200))
{
	m_pFileControl = new CFileControl(this, wxPoint(-1, -1), wxSize(GetControlWidth(), 100));
}

CTab::~CTab(void)
{
}

int
CTab::GetControlWidth(void)
{
	return 428 - 2 * 10 - wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
}


// CFileControl source
CFileControl::CFileControl(wxPanel *tab,
							 const wxPoint& point,
							 const wxSize& size)
	   : wxPanel(tab, -1, point, size)
{
	m_pGroupBox = new wxStaticBox(tab, -1, wxEmptyString, point, size);

	wxString *choices = new wxString[3];
	choices[0] = wxT("First File");
	choices[1] = wxT("Second File");
	choices[2] = wxT("Third File");

	m_pFileList = new wxComboBox(this, Minimal_Cmbbox, wxEmptyString, wxPoint(10, 10), wxSize(-1, -1), 3, choices, wxCB_READONLY);
	m_pFileList->SetSelection(0);

	m_pSndName = new wxStaticText(this, -1, wxEmptyString);

	// This should go in the name and size label changing methods
	m_pSndName->SetLabel(wxT("Loaded file"));

	m_pSndName->Move(GetClientSize().x - m_pSndName->GetClientSize().x - 10, 10);
	// End of things that should not be here later on

	// Create buttons
	m_pImportBn = new wxButton(this, Minimal_Import, _("Import"));
	m_pRemoveBn = new wxButton(this, Minimal_Remove, _("Remove"));

	// Position buttons
	m_pRemoveBn->Move(GetClientSize().x - m_pRemoveBn->GetClientSize().x - 4,
						GetClientSize().y - m_pRemoveBn->GetClientSize().y - 4);
	m_pImportBn->Move(m_pRemoveBn->GetPosition().x - m_pImportBn->GetClientSize().x - 4,
						m_pRemoveBn->GetPosition().y);
}

CFileControl::~CFileControl(void)
{
}

void
CFileControl::OnComboChoice(wxCommandEvent& event)
{
	wxLogMessage(wxT("OnComboChoice detected!"));

	wxCommandEvent xx = event;
}

void
CFileControl::Import(wxCommandEvent& event)
{
	wxString path;
	int nResult;

	wxFileDialog dlg
	(
		this,
		wxT(""),
		wxT(""),
		wxT(""),
		wxT("GIF Files (*.gif)|*.gif|"),
		wxOPEN | wxHIDE_READONLY | wxCHANGE_DIR,
		wxPoint()
	);

	nResult = dlg.ShowModal();

	wxLogMessage(wxT("Import (obviously) detected!"));

	wxCommandEvent xx = event;
	
}

void
CFileControl::Remove(wxCommandEvent& event)
{
	wxLogMessage(wxT("Remove detected!"));

	wxCommandEvent xx = event;
}

 	  	 
