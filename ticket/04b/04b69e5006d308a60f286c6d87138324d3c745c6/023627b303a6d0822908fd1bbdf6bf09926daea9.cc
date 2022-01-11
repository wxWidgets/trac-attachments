
#include "wx/wx.h"

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
  public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
    void CheckEditable(wxCommandEvent& event);

  private:
    wxTextCtrl* text_ctrl;
    DECLARE_EVENT_TABLE();
};

enum
{
    ID_Quit = 1,
    ID_Test,
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit,  MyFrame::OnQuit)
    EVT_MENU(ID_Test, MyFrame::CheckEditable)
    END_EVENT_TABLE();

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Minimal wxWindows App",
                                 wxPoint(50, 50), wxSize(450, 340));
    frame->Show(TRUE);
    return TRUE;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu("", wxMENU_TEAROFF);

    menuFile->Append(ID_Quit, "E&xit\tAlt-X");
    menuFile->Append(ID_Test, "Check Editable");

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);

    this->text_ctrl = new wxTextCtrl(
	this, -1, "", wxDefaultPosition, wxSize(100, 75),
	wxTE_MULTILINE);
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::CheckEditable(wxCommandEvent& WXUNUSED(event))
{
    // TRUE is to force the frame to close
    this->text_ctrl->IsEditable();
}

 	  	 
