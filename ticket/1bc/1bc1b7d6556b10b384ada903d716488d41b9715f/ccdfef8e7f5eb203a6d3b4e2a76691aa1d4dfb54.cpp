#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>
#include <wx/timer.h>
#include <wx/app.h>

wxPanel *makeLabelPanel(wxWindow *parent) {
    wxPanel *panel = new wxPanel(parent, wxID_ANY);
    wxSizer *sizer= new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Label1")), 0, wxEXPAND);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Label2")), 0, wxEXPAND);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Label3")), 0, wxEXPAND);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Label4")), 0, wxEXPAND);
    panel->SetSizer(sizer);
    return panel;
}

wxPanel *makeTextCtrlPanel(wxWindow *parent) {
    wxPanel *panel = new wxPanel(parent, wxID_ANY);
    wxSizer *sizer= new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxTextCtrl(panel, wxID_ANY, wxT("TextCtrl1")), 0, wxEXPAND);
    sizer->Add(new wxTextCtrl(panel, wxID_ANY, wxT("TextCtrl2")), 0, wxEXPAND);
    sizer->Add(new wxTextCtrl(panel, wxID_ANY, wxT("TextCtrl3")), 0, wxEXPAND);
    sizer->Add(new wxTextCtrl(panel, wxID_ANY, wxT("TextCtrl4")), 0, wxEXPAND);
    panel->SetSizer(sizer);
    return panel;
}

class Frame: public wxFrame {
private:
public:
    Frame(): wxFrame(NULL, wxID_ANY, wxT("Frame test")) {
        int i;
        wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        wxPanel *mainPanel = new wxPanel(this, wxID_ANY);
        sizer->Add(mainPanel, 1, wxEXPAND);
        wxSizer *mainPanelSizer = new wxBoxSizer(wxVERTICAL);
        mainPanelSizer->Add(makeLabelPanel(mainPanel), 0, wxEXPAND);
        mainPanelSizer->Add(makeTextCtrlPanel(mainPanel), 0, wxEXPAND);
        wxNotebook *notebook = new wxNotebook(mainPanel, wxID_ANY);
        // notebook->SetBackgroundColour(wxColour(0, 0xff, 0xff));
        notebook->InsertPage(0, makeLabelPanel(notebook), wxT("wxStaticText"));
        notebook->InsertPage(1, makeTextCtrlPanel(notebook), wxT("wxTextCtrl"));
        notebook->InsertPage(2, new wxPanel(notebook, wxID_ANY), wxT("Empty"));
        mainPanelSizer->Add(notebook, 1, wxEXPAND);
        mainPanel->SetSizer(mainPanelSizer);
        SetSizerAndFit(sizer);
    }
};

class FrameTest: public wxApp {
    bool OnInit(void) {
        if (!wxApp::OnInit()) {
            return false;
        }
        Frame *frame = new Frame();
        frame->Show();
        frame->Raise();
        return true;
    }
};

#ifdef IMPLEMENT_APP
IMPLEMENT_APP(FrameTest);
#else
wxIMPLEMENT_APP(FrameTest);
#endif
