#include "wx/wx.h"
#include <iostream>

class MyApp: public wxApp
{
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:

    MyFrame(const wxString& title);
    virtual ~MyFrame();
    void OnClick(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};
enum
{
    ID_Button = 12345
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(ID_Button, MyFrame::OnClick)
END_EVENT_TABLE()
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame(wxT("Frame"));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, -1, title)
{
    wxButton* button = new wxButton(this, ID_Button, wxT("Click me"));
}

void MyFrame::OnClick(wxCommandEvent& event)
{
    std::wcout << wxT("Before destroy") << std::endl;
    Destroy();
    std::wcout << wxT("After destroy") << std::endl;
    wxMessageBox(wxT("Destroyed."), wxT("Destroyed."), wxOK);
    std::wcout << wxT("After messagebox") << std::endl;
    event.Skip();
}

MyFrame::~MyFrame()
{
    std::wcout << wxT("~MyFrame") << std::endl;
}

