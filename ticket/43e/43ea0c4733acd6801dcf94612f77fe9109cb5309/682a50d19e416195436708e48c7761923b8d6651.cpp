
#include "wx/wx.h"

class HelloWorldApp : public wxApp
{
public:
    virtual bool OnInit();
};

DECLARE_APP(HelloWorldApp)

IMPLEMENT_APP(HelloWorldApp)

// This is executed upon startup, like 'main()' in non-wxWidgets programs.
bool HelloWorldApp::OnInit()
{
    wxFrame *frame = new wxFrame((wxFrame*) NULL, -1, _T("Hello wxWidgets World"));
    frame->CreateStatusBar();
    frame->SetStatusText(_T("Hello World"));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxCheckBox* cb1 = new wxCheckBox(frame, wxID_ANY, "Label 1");
    wxCheckBox* cb2 = new wxCheckBox(frame, wxID_ANY, "Label 2");

    sizer->Add(cb1);
    sizer->Add(cb2);

    frame->SetSizer(sizer);

    frame->Show(true);
    SetTopWindow(frame);
    return true;
}