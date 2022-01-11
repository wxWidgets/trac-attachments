#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/app.h>
#include <wx/apptrait.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/platinfo.h>

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame();
private:
    void OnExit(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show( true );
    return true;
}

MyFrame::MyFrame()
        : wxFrame(NULL, wxID_ANY, "tab")
{
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *label = NULL;
    wxTextCtrl *ctrl = NULL;
    for (int i=0; i<3; i++)
    {
        label = new wxStaticText(this, wxID_ANY, wxString::Format("%i", i));
        ctrl = new wxTextCtrl(this, wxID_ANY);
        sizer->Add(label);
        sizer->Add(ctrl);
    }

    SetSizer(sizer);
    CreateStatusBar();

    wxAppTraits *traits = wxTheApp->GetTraits();
    const wxPlatformInfo *info = &wxPlatformInfo::Get();

    wxString str = wxString::Format("PortID=%d major=%d minor=%d on %s",
                                        info->GetPortId(),
                                        info->GetToolkitMajorVersion(),
                                        info->GetToolkitMinorVersion(),
                                        info->GetOperatingSystemDescription());
    SetStatusText(str);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

