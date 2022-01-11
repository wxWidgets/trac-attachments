/////////////////////////////////////////////////////////////////////////////
// Name:        sizertest.h
// Purpose:     
// Author:      Alex Bligh
// Modified by: 
// Created:     Sat 17 Jun 2006 11:12:08 BST
// RCS-ID:      
// Copyright:   (c) 2006 Alex Bligh, wxWidgets Licence
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// COMPILATION INSTRUCTIONS
//
// export WXCONFIG=/usr/lib/wx/config/gtk2-unicode-debug-2.6
// gcc `$WXCONFIG --cxxflags --libs` sizer.cpp -o sizer

#include <wx/wx.h>

class SizertestApp: public wxApp
{    
    DECLARE_CLASS( SizertestApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    SizertestApp();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();
};


#define ID_DIALOG 10000
#define SYMBOL_SIZERDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxDIALOG_MODAL
#define SYMBOL_SIZERDLG_TITLE _("SizerDlg")
#define SYMBOL_SIZERDLG_IDNAME ID_DIALOG
#define SYMBOL_SIZERDLG_SIZE wxSize(400, 300)
#define SYMBOL_SIZERDLG_POSITION wxDefaultPosition
#define ID_TOPBUTTON 10001
#define ID_SHOWHIDE 10002
#define ID_ROW2BUTTON 10006
#define ID_STRETCHY 10003
#define ID_PANEL 10004
#define ID_BOTTOMBUTTON1 10007
#define ID_BOTTOMBUTTON2 10008
#define ID_BOTTONBUTTON3 10009
#define ID_BUTTONBUTTON4 10005

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
* SizerDlg class declaration
*/

class SizerDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( SizerDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SizerDlg( );
    SizerDlg( wxWindow* parent, wxWindowID id = SYMBOL_SIZERDLG_IDNAME, const wxString& caption = SYMBOL_SIZERDLG_TITLE, const wxPoint& pos = SYMBOL_SIZERDLG_POSITION, const wxSize& size = SYMBOL_SIZERDLG_SIZE, long style = SYMBOL_SIZERDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SIZERDLG_IDNAME, const wxString& caption = SYMBOL_SIZERDLG_TITLE, const wxPoint& pos = SYMBOL_SIZERDLG_POSITION, const wxSize& size = SYMBOL_SIZERDLG_SIZE, long style = SYMBOL_SIZERDLG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

    /// wxEVT_SIZE event handler for ID_DIALOG
    void OnSize( wxSizeEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SHOWHIDE
    void OnShowhideClick( wxCommandEvent& event );

    wxButton* m_pStretchy;
    wxPanel* m_pPanel;
};

IMPLEMENT_DYNAMIC_CLASS( SizerDlg, wxDialog )
BEGIN_EVENT_TABLE( SizerDlg, wxDialog )
//    EVT_SIZE( SizerDlg::OnSize ) // Not used for now
    EVT_BUTTON( ID_SHOWHIDE, SizerDlg::OnShowhideClick )
END_EVENT_TABLE()

SizerDlg::SizerDlg( )
{
}

SizerDlg::SizerDlg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

bool SizerDlg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    m_pStretchy = NULL;
    m_pPanel = NULL;

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}

void SizerDlg::CreateControls()
{    
    SizerDlg* itemDialog1 = this;
    
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);
    
    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);
    
    wxButton* itemButton4 = new wxButton( itemDialog1, ID_TOPBUTTON, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemButton4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    wxButton* itemButton5 = new wxButton( itemDialog1, ID_SHOWHIDE, _("Stretch (showhide)"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemButton5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer6, 0, wxGROW|wxALL, 5);
    
    itemBoxSizer6->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    wxButton* itemButton8 = new wxButton( itemDialog1, ID_ROW2BUTTON, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButton8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer9, 1, wxGROW|wxALL, 5);
    
    m_pStretchy = new wxButton( itemDialog1, ID_STRETCHY, _("Expand & Stretch"), wxDefaultPosition, wxSize(100, 100), 0 );
    itemBoxSizer9->Add(m_pStretchy, 1, wxGROW|wxALL, 5);
    // Use an opening size which for m_pStretchy is larger than the minimum
    m_pStretchy->SetSize(wxSize(200,200));
    
    m_pPanel = new wxPanel( itemDialog1, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    m_pPanel->Show(false);
    itemBoxSizer2->Add(m_pPanel, 0, wxGROW|wxALL, 5);
    
    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    m_pPanel->SetSizer(itemBoxSizer12);
    
    wxBoxSizer* itemBoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer12->Add(itemBoxSizer13, 0, wxGROW|wxALL, 5);
    
    itemBoxSizer13->Add(550, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer12->Add(itemBoxSizer15, 0, wxGROW|wxALL, 5);
    
    wxButton* itemButton16 = new wxButton( m_pPanel, ID_BOTTOMBUTTON1, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    wxButton* itemButton17 = new wxButton( m_pPanel, ID_BOTTOMBUTTON2, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    wxButton* itemButton18 = new wxButton( m_pPanel, ID_BOTTONBUTTON3, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton18, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    itemBoxSizer15->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    wxButton* itemButton20 = new wxButton( m_pPanel, ID_BUTTONBUTTON4, _("Stretch"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton20, 1, wxGROW|wxALL, 5);
    
    // Do an extra layout and fit to ensure we have the new size in
    Layout();
    Fit();
}

void SizerDlg::OnSize( wxSizeEvent& event )
{
    // Not used for now
    event.Skip();
}

void SizerDlg::OnShowhideClick( wxCommandEvent& event )
{
    // Return the stretchy control to a minimum size, so
    // the subsequent layout() and Fit() will bring it
    // back to the minimum size
    m_pStretchy->SetSize(1,1);
    
    m_pPanel->Show(!m_pPanel->IsShown());
    if (GetSizer())
    {
        Layout();
        Fit();
        GetSizer()->SetSizeHints(this);
    }
}


bool SizertestApp::OnInit()
{
    SizerDlg* mainWindow = new SizerDlg(NULL, ID_DIALOG, _("SizerDlg"));
    mainWindow->ShowModal();
    mainWindow->Destroy();
    return false;
}

DECLARE_APP(SizertestApp)

IMPLEMENT_APP( SizertestApp )
IMPLEMENT_CLASS( SizertestApp, wxApp )
BEGIN_EVENT_TABLE( SizertestApp, wxApp )
END_EVENT_TABLE()

SizertestApp::SizertestApp()
{
}

int SizertestApp::OnExit()
{
    return wxApp::OnExit();
}

 	  	 
