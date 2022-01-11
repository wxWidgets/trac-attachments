/*
 * sample.cpp
 */

#include "wx/wx.h"
#include "wx/combo.h"
#include "wx/odcombo.h"
#include "wx/config.h"
#include "wx/collpane.h"

class MyApp: public wxApp
{
    virtual bool OnInit();
};

class Login_panel: public wxPanel
{
public:
	Login_panel(wxFrame *frame);

	wxCollapsiblePane *pane() { return m_pane; }

private:
	wxCollapsiblePane    *m_pane;
	wxButton             *m_sendLogin;
        wxTextCtrl           *m_serverUrl;

	bool m_connected;
};

class Desktop_panel: public wxPanel
{
public:
	Desktop_panel(wxFrame *frame);

	wxCollapsiblePane *pane() { return m_pane; }
        wxCheckBox *cbox() { return m_cbox; }
        wxOwnerDrawnComboBox *dt_list() { return m_dtList; }

private:
	void dropdown_list_enable() {
		if (m_dropdown_list_size > 1) {
			m_dtList->Enable();
		} else {
			m_dtList->Disable();
		}
	}
	wxCollapsiblePane    *m_pane;
	wxCheckBox           *m_cbox;
	wxOwnerDrawnComboBox *m_dtList;

	bool m_displaying;
	int m_dropdown_list_size;
};

class MyFrame: public wxFrame
{
public:

    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnLogin(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()

private:
    Login_panel *m_login_panel;
    Desktop_panel *m_dt_panel;
};

enum
{
	USER_CONSOLE_QUIT           = wxID_EXIT,
	USER_CONSOLE_ABOUT          = wxID_ABOUT,
	USER_CONSOLE_LOGIN,
	USER_CONSOLE_LOGIN_PANEL,
	USER_CONSOLE_DESKTOP_PANEL,
        USER_CONSOLE_SELECT_DESKTOP
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(USER_CONSOLE_QUIT, MyFrame::OnQuit)
    EVT_MENU(USER_CONSOLE_ABOUT, MyFrame::OnAbout)
    EVT_BUTTON(USER_CONSOLE_LOGIN, MyFrame::OnLogin)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    /*MyFrame *frame = new MyFrame( _("Hello World"), wxPoint(50, 50),
                                  wxSize(450,340) );*/
    MyFrame *frame = new MyFrame( _("Sample Program"), wxPoint(wxDefaultCoord, wxDefaultCoord),
                                  wxSize(wxDefaultCoord, wxDefaultCoord) );
    
    wxMenu *menuFile = new wxMenu;

    menuFile->Append( USER_CONSOLE_ABOUT, _("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( USER_CONSOLE_QUIT, _("E&xit") );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, _("&File") );

    frame->SetMenuBar( menuBar );
    frame->Show(true);
    SetTopWindow(frame);
    frame->Center();
    return true;
} 

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame( NULL, -1, title, pos, size, wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxMAXIMIZE_BOX) )
{
    CreateStatusBar(1);
    wxBoxSizer *vert_sz = new wxBoxSizer(wxVERTICAL);

    m_login_panel = new Login_panel(this);
    m_dt_panel = new Desktop_panel(this);

    vert_sz->Add(m_login_panel, 0, wxALL | wxEXPAND, 2);
    vert_sz->Add(m_dt_panel, 0, wxALL | wxEXPAND, 2);

    SetSizer(vert_sz);
    vert_sz->Fit(this);

    SetStatusText( _("Welcome to wxWidgets!") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _("This is Sample Program for wxWidgets Issues"),
                  _("About Sample"),
                  wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnLogin(wxCommandEvent& WXUNUSED(event))
{
    m_login_panel->pane()->Collapse();
    m_login_panel->pane()->Disable();
    
    m_dt_panel->pane()->Enable();
    m_dt_panel->pane()->Expand();
    m_dt_panel->dt_list()->Append("test1");
    m_dt_panel->dt_list()->Append("test2");
    m_dt_panel->dt_list()->Enable();
    m_dt_panel->cbox()->Enable();
    m_dt_panel->dt_list()->SetSelection(0);
    m_dt_panel->dt_list()->SetFocus();
}

Login_panel::Login_panel(wxFrame *frame) :
			wxPanel(frame, wxID_ANY, 
				wxPoint(wxDefaultCoord, wxDefaultCoord),
				wxSize(wxDefaultCoord, wxDefaultCoord))
			, m_connected(false)
{
	wxFont font = GetFont();
	font.SetPointSize(10);
	SetFont(font);

	const int border = 4;

	wxBoxSizer * col_sz = new wxBoxSizer(wxVERTICAL);
	m_pane = new wxCollapsiblePane(this, USER_CONSOLE_LOGIN_PANEL, _("Login"));
	col_sz->Add(m_pane, 0, wxGROW|wxALL, 5);

	wxWindow *win = m_pane->GetPane();
	wxSizer *panel_sz = new wxBoxSizer(wxVERTICAL);
	panel_sz->Add(new wxStaticText(win,wxID_ANY,_("Server:")), 0,
			wxRIGHT | wxLEFT |wxEXPAND, border); 
	m_serverUrl = new wxTextCtrl(win, wxID_ANY, wxT(""), wxDefaultPosition, 
					wxSize(230,25) , wxTE_PROCESS_ENTER);

	m_serverUrl->SetMaxLength(200);
	panel_sz->Add(m_serverUrl, 0, wxRIGHT | wxLEFT, border);
	win->SetSizer(panel_sz);
	panel_sz->SetSizeHints(win);
	m_pane->Expand();
	m_sendLogin = new wxButton(this, USER_CONSOLE_LOGIN, 
					_("&Connect"), 
					wxDefaultPosition, wxDefaultSize);
	m_sendLogin->SetDefault();
	col_sz->Add(m_sendLogin, 0, wxRIGHT | wxLEFT | wxDOWN | wxALIGN_CENTER_HORIZONTAL, border);

	SetSizer(col_sz);
}

Desktop_panel::Desktop_panel(wxFrame *frame) : 
				wxPanel(frame, wxID_ANY, 
					wxPoint(wxDefaultCoord, wxDefaultCoord),
					wxSize(wxDefaultCoord, wxDefaultCoord))
				, m_displaying(false)
				, m_dropdown_list_size(0)
{
	wxFont font = GetFont();
	font.SetPointSize(10);
	SetFont(font);

	const int border = 4;

	wxBoxSizer * col_sz = new wxBoxSizer(wxVERTICAL);
	m_pane = new wxCollapsiblePane(this, USER_CONSOLE_DESKTOP_PANEL, _("Desktop:"));
	col_sz->Add(m_pane, 0, wxGROW|wxALL, 5);

	wxWindow *win = m_pane->GetPane();
	wxSizer *panel_sz = new wxBoxSizer(wxVERTICAL);

	wxStaticText *dt_text = new wxStaticText(win,wxID_ANY,_("Select Item:"));
	panel_sz->Add(dt_text, 0, wxRIGHT | wxLEFT | wxDOWN | wxALIGN_CENTER_HORIZONTAL, border);
	m_dtList = new wxOwnerDrawnComboBox(win
						  , USER_CONSOLE_SELECT_DESKTOP
						  , wxEmptyString
						  , wxDefaultPosition
						  , wxSize(200,25)
						  , 0
						  , NULL
						  , wxCB_SIMPLE);
	m_dtList->Disable();
	panel_sz->Add(m_dtList, 0, wxRIGHT | wxLEFT | wxDOWN | wxALIGN_CENTER_HORIZONTAL, border);
	m_cbox = new wxCheckBox(win, wxID_ANY, _("&CheckBox "), wxPoint(20,170));
	m_cbox->SetValue(true);
	m_cbox->Disable();
	panel_sz->Add(m_cbox, 0, wxRIGHT | wxLEFT | wxDOWN | wxALIGN_LEFT, border);
	win->SetSizer(panel_sz);
	panel_sz->SetSizeHints(win);
	m_pane->Collapse();
	m_pane->Disable();
	col_sz->Add(new wxStaticText(this,wxID_ANY,wxT("")));

	SetSizer(col_sz);
}
