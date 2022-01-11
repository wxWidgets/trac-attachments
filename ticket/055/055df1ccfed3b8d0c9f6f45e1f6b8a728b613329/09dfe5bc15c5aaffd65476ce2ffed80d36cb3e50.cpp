// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

class TextDialog : public wxDialog 
{
public:
		TextDialog(wxWindow* parent); 
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

wxTextCtrl* CreateScrollingTextCtrl(wxWindow* parent) {
	  wxTextCtrl* textCtrl = new wxTextCtrl(parent,
	                                        wxID_ANY,
	                                        wxEmptyString,
	                                        wxDefaultPosition,
	                                        wxSize(-1, -1),
	                                        wxTE_MULTILINE | wxTE_READONLY);
    wxString msg;
    for (int i = 0; i < 200; i++) {
        msg += wxString::Format("Line number %d\n", i);
    }
    textCtrl->SetValue(msg);
    return textCtrl;
}

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );

	  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl* textCtrl = CreateScrollingTextCtrl(this);
	  sizer->Add(textCtrl, 1, wxALL|wxEXPAND, 10);
	  SetSizer(sizer);
	  Layout();
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    TextDialog dlg(this);
    dlg.CenterOnParent();
    dlg.ShowModal();
}

TextDialog::TextDialog(wxWindow* parent) : wxDialog(parent,
                                                    wxID_ANY,
                                                    "Dialog",
                                                    wxDefaultPosition,
                                                    wxSize(371, 262),
                                                    wxDEFAULT_DIALOG_STYLE)
{
	  SetSizeHints(wxDefaultSize, wxDefaultSize);

	  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxTextCtrl* textCtrl = CreateScrollingTextCtrl(this);
	  sizer->Add(textCtrl, 1, wxALL|wxEXPAND, 10);

	  wxButton* button = new wxButton(this, wxID_OK);
	  sizer->Add(button, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5);

	  SetSizer(sizer);
	  Layout();
}