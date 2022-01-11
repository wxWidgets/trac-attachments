#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    wxTextCtrl log;

    void OnReset(wxCommandEvent& event);
    void OnFirst(wxCommandEvent& event);
    void OnSecond(wxCommandEvent& event);
    void OnThird(wxCommandEvent& event);

private:
    wxDECLARE_EVENT_TABLE();
};

enum
{
    MENU_Reset = 20000,
    MENU_First,
    MENU_Second,
    MENU_Third
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(MENU_Reset, MyFrame::OnReset)
    EVT_MENU(MENU_First, MyFrame::OnFirst)
    EVT_MENU(MENU_Second, MyFrame::OnSecond)
    EVT_MENU(MENU_Third, MyFrame::OnThird)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if(!wxApp::OnInit())
        return false;

    MyFrame *frame = new MyFrame("Test Radio Menu - Reset fails on Linux");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title),
    log(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxTE_MULTILINE | wxTE_READONLY)
{
    wxMenu *testMenu = new wxMenu();
    testMenu->Append(MENU_Reset, "Reset to default");
    testMenu->AppendSeparator();
    testMenu->Append(MENU_First, "First radio (default)", "", wxITEM_RADIO);
    testMenu->Check(MENU_First, true);
    testMenu->Append(MENU_Second, "Second radio", "", wxITEM_RADIO);
    testMenu->Append(MENU_Third, "Third radio", "", wxITEM_RADIO);

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(testMenu, "&Test");
    SetMenuBar(menuBar);
}

void MyFrame::OnReset(wxCommandEvent& WXUNUSED(event))
{
    log.AppendText("MyFrame::OnReset\n");
    GetMenuBar()->Check(MENU_First, 1);
    log.AppendText("~MyFrame::OnReset\n");
}

void MyFrame::OnFirst(wxCommandEvent& WXUNUSED(event))
{
    log.AppendText("MyFrame::OnFirst\n");
    log.AppendText("~MyFrame::OnFirst\n");
}

void MyFrame::OnSecond(wxCommandEvent& WXUNUSED(event))
{
    log.AppendText("MyFrame::OnSecond\n");
    log.AppendText("~MyFrame::OnSecond\n");
}

void MyFrame::OnThird(wxCommandEvent& WXUNUSED(event))
{
    log.AppendText("MyFrame::OnThird\n");
    log.AppendText("~MyFrame::OnThird\n");
}
