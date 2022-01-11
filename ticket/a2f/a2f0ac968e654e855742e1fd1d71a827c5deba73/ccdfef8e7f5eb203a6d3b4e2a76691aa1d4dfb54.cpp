#include <wx/wx.h>

class Frame: public wxFrame {
public:
    Frame(wxWindow *parent): wxFrame(parent, wxID_ANY,
                                     wxT("Frame created by hand")) {
        wxSizer *mainSizer, *panelSizer;
        wxStaticBoxSizer *staticBoxSizer;
        wxStaticBox *staticBox;
        mainSizer = new wxBoxSizer(wxVERTICAL);
        wxPanel *panel_1 = new wxPanel(this, wxID_ANY);
        panel_1->SetBackgroundColour(wxColour(0xff, 0xff, 0));
        panelSizer = new wxBoxSizer(wxVERTICAL);
        panelSizer->Add(new wxStaticText(panel_1, wxID_ANY,
                                         wxT("This is a child of the main panel")),
                        0, wxALL, 10);
        // First wxStaticBoxSizer: widgets are children of its wxStaticBox,
        // red background
        staticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, panel_1,
                                              wxT("Children of wxStaticBox, "
                                                  "red"));
        staticBox = staticBoxSizer->GetStaticBox();
        staticBox->SetBackgroundColour(wxColour(0xff, 0, 0));
        staticBoxSizer->Add(new wxStaticText(staticBox, wxID_ANY,
                                             wxT("This is a label")),
                            0);
        staticBoxSizer->Add(new wxButton(staticBox, wxID_ANY, wxT("Clickable")),
                            0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 10);
        panelSizer->Add(staticBoxSizer, 1, wxALL | wxEXPAND, 10);
        // First wxStaticBoxSizer: widgets are children of its wxStaticBox,
        // background color not set
        staticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, panel_1,
                                              wxT("Children of wxStaticBox, "
                                                  "default bg"));
        staticBox = staticBoxSizer->GetStaticBox();
        staticBoxSizer->Add(new wxStaticText(staticBox, wxID_ANY,
                                             wxT("This is a label")),
                            0);
        staticBoxSizer->Add(new wxButton(staticBox, wxID_ANY, wxT("Clickable")),
                            0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 10);
        panelSizer->Add(staticBoxSizer, 1, wxALL | wxEXPAND, 10);
        // Third wxStaticBoxSizer: widgets are its siblings, red background
        staticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, panel_1,
                                              wxT("Siblings of wxStaticBox, "
                                                  "red"));
        staticBox = staticBoxSizer->GetStaticBox();
        staticBox->SetBackgroundColour(wxColour(0xff, 0, 0));
        staticBoxSizer->Add(new wxStaticText(panel_1, wxID_ANY,
                                             wxT("This is a label")),
                            0);
        staticBoxSizer->Add(new wxButton(panel_1, wxID_ANY, wxT("Clickable")),
                            0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 10);
        panelSizer->Add(staticBoxSizer, 1, wxALL | wxEXPAND, 10);
        // Fourth wxStaticBoxSizer: widgets are its siblings, background
        // color not set
        staticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, panel_1,
                                              wxT("Siblings of wxStaticBox, "
                                                  "default bg"));
        staticBox = staticBoxSizer->GetStaticBox();
        staticBoxSizer->Add(new wxStaticText(panel_1, wxID_ANY,
                                             wxT("This is a label")),
                            0);
        staticBoxSizer->Add(new wxButton(panel_1, wxID_ANY, wxT("Clickable")),
                            0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 10);
        panelSizer->Add(staticBoxSizer, 1, wxALL | wxEXPAND, 10);
        panel_1->SetSizer(panelSizer);
        mainSizer->Add(panel_1, 1, wxEXPAND);
        SetSizerAndFit(mainSizer);
    }
};

class Test: public wxApp {
    bool OnInit(void) {
        if (!wxApp::OnInit()) {
            return false;
        }
        (new Frame(NULL))->Show();
        return true;
    }
};

#ifdef IMPLEMENT_APP
IMPLEMENT_APP(Test);
#else
wxIMPLEMENT_APP(Test);
#endif
