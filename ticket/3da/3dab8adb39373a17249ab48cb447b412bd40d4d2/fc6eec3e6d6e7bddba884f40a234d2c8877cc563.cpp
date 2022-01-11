// Test DPI change handling

#include "wx/wx.h"

class MyApp: public wxApp
{
public:
    bool OnInit() wxOVERRIDE;
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title);    
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    // Create the main frame window
    MyFrame *frame = new MyFrame("Sizer Border Test");

    frame->Show(true);

    // report success
    return true;
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
        wxDefaultSize, wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU)
{
    const int borderSize = 10;
    const int spacerSize = 10;

    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags sizerFlags(0);
    sizerFlags.Border(wxALL, FromDIP(borderSize));

    wxSizer* horSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(horSizer, sizerFlags);

    wxSizer* col1Sizer = new wxBoxSizer(wxVERTICAL);
    horSizer->Add(col1Sizer, sizerFlags);
	
    wxStaticText* text = new wxStaticText(this, wxID_ANY, "This is text line 1, column 1. It should be completely visible.");
    col1Sizer->Add(text, sizerFlags);
    col1Sizer->AddSpacer(FromDIP(spacerSize));
    col1Sizer->Add(new wxStaticText(this, wxID_ANY, "This is text line 2, column 1. It should be completely visible."), sizerFlags);
    col1Sizer->AddSpacer(FromDIP(spacerSize));
    col1Sizer->Add(new wxStaticText(this, wxID_ANY, "This is text line 3, column 1. It should be completely visible."), sizerFlags);
    col1Sizer->AddSpacer(FromDIP(spacerSize));
    col1Sizer->Add(new wxStaticText(this, wxID_ANY, "This is text line 4, column 1. It should be completely visible."), sizerFlags);

    wxSizer* col2Sizer = new wxBoxSizer(wxVERTICAL);
    horSizer->Add(col2Sizer, sizerFlags);

    col2Sizer->Add(new wxStaticText(this, wxID_ANY, "This is text line 1, column 2. It should be completely visible."), sizerFlags);
    col2Sizer->AddSpacer(FromDIP(spacerSize));
    col2Sizer->Add(new wxStaticText(this, wxID_ANY, "This is text line 2, column 2. It should be completely visible."), sizerFlags);
    col2Sizer->AddSpacer(FromDIP(spacerSize));
    col2Sizer->Add(new wxStaticText(this, wxID_ANY, "This is text line 3, column 2. It should be completely visible."), sizerFlags);
    col2Sizer->AddSpacer(FromDIP(spacerSize));
    col2Sizer->Add(new wxStaticText(this, wxID_ANY, "This is text line 4, column 2. It should be completely visible."), sizerFlags);

    // Test some nested controls
    wxPanel* panel = new wxPanel(this);
    mainSizer->Add(panel, sizerFlags);
    
    wxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panel->SetSizer(panelSizer);
    
    wxSizer* panCol1Sizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(panCol1Sizer, sizerFlags);
  
    panCol1Sizer->Add(new wxStaticText(panel, wxID_ANY, "This is panel text line 1, column 1."), sizerFlags);
    panCol1Sizer->Add(new wxStaticText(panel, wxID_ANY, "This is panel text line 2, column 1."), sizerFlags);
    panCol1Sizer->Add(new wxStaticText(panel, wxID_ANY, "This is panel text line 3, column 1."), sizerFlags);
    panCol1Sizer->Add(new wxStaticText(panel, wxID_ANY, "This is panel text line 4, column 1."), sizerFlags);
    
    wxSizer* panCol2Sizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(panCol2Sizer, sizerFlags);
    
    panCol2Sizer->Add(new wxStaticText(panel, wxID_ANY, "This is panel text line 1, column 2."), sizerFlags);
    panCol2Sizer->Add(new wxStaticText(panel, wxID_ANY, "This is panel text line 2, column 2."), sizerFlags);
    panCol2Sizer->Add(new wxStaticText(panel, wxID_ANY, "This is panel text line 3, column 2."), sizerFlags);
    panCol2Sizer->Add(new wxStaticText(panel, wxID_ANY, "This is panel text line 4, column 2."), sizerFlags);
    
    SetSizerAndFit(mainSizer);
}
