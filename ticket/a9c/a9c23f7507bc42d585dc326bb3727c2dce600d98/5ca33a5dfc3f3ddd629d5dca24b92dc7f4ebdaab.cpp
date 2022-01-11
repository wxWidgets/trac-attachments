#include <wx/wx.h>

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame
{
    public:
        MyFrame(const wxString& title);

        void OnQuit(wxCommandEvent& event);
        void OnStart(wxCommandEvent& event);

    private:
        DECLARE_EVENT_TABLE()
};

enum
{
    MY_ID_CLOSE = wxID_HIGHEST
};

class MyDialog : public wxDialog
{
    public:
        MyDialog(wxWindow* parent);

    protected:
        void OnCloseClick(wxCommandEvent& evt);

    private:
        DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(MyApp)

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// App
// ----------------------------------------------------------------------------

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;
    MyFrame *frame = new MyFrame("ShowModal Test");
    frame->Show(true);
    return true;
}

// ----------------------------------------------------------------------------
// MyFrame 
// ----------------------------------------------------------------------------

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    wxLogWindow* log = new wxLogWindow(this, "Logger");
    wxButton* startBut = new wxButton(this, wxID_ANY, "Start");
    startBut->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnStart));

    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(startBut, 1, wxEXPAND);
    this->SetSizer(sizer);
}

void MyFrame::OnStart(wxCommandEvent& WXUNUSED(event))
{
    MyDialog dlg(this);
    wxLogMessage("going modal");
    dlg.ShowModal();
    wxLogMessage("do work");
}

// ----------------------------------------------------------------------------
// MyDialog 
// ----------------------------------------------------------------------------

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

BEGIN_EVENT_TABLE(MyDialog, wxDialog)
    EVT_BUTTON(MY_ID_CLOSE,  MyDialog::OnCloseClick)
END_EVENT_TABLE()

MyDialog::MyDialog(wxWindow* parent) :
    wxDialog(parent, wxID_ANY, wxString("MyDialog"))
{
    wxButton* stopBut = new wxButton(this, MY_ID_CLOSE, "Close");
    Fit();
    Center();
}


void MyDialog::OnCloseClick(wxCommandEvent& evt)
{
    wxSleep(1);
    EndModal(MY_ID_CLOSE);
}
