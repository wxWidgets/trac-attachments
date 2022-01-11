#include <wx/wx.h>
#include <wx/spinctrl.h>

//
// Declaration
//

class MainApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MainFrame: public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

DECLARE_APP(MainApp)

//
// Implementation
//

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
    MainFrame* frame = new MainFrame(wxT("wxSpinCtrl sample"), wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(panelSizer);

    // No scrolling
    panelSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("No scrolling")), wxSizerFlags().Border(wxALL & ~wxBOTTOM));
    wxSpinCtrl* spinCtrlNoScroll = new wxSpinCtrl(
        panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
        // Control size
        wxSize(50, wxDefaultSize.GetHeight()),
        // Style
        wxSP_ARROW_KEYS | wxALIGN_RIGHT,
        0, 100000);
    panelSizer->Add(spinCtrlNoScroll, wxSizerFlags().Border());

    // Scrolling
    panelSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Scrolling")), wxSizerFlags().Border(wxALL & ~wxBOTTOM));
    wxSpinCtrl* spinCtrlScroll = new wxSpinCtrl(
        panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
        // Control size
        wxSize(50, wxDefaultSize.GetHeight()),
        // Style
        wxSP_ARROW_KEYS | wxALIGN_RIGHT | wxSP_AUTO_SCROLL,
        0, 100000);
    panelSizer->Add(spinCtrlScroll, wxSizerFlags().Border());

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, wxSizerFlags(1).Expand());
    SetSizer(sizer);
    Fit();
}