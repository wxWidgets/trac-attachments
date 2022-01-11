#include <wx/frame.h>
#include <wx/radiobox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/app.h>

class Frame: public wxFrame {
private:
    wxPanel *mainPanel;
public:
    Frame(): wxFrame(NULL, wxID_ANY, wxT("Frame test")) {
        wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        mainPanel = new wxPanel(this, wxID_ANY);
        sizer->Add(mainPanel, 1, wxEXPAND);
        wxSizer *mainPanelSizer = new wxBoxSizer(wxVERTICAL);
        wxFont font(GetFont());
        wxString choices[2];
        choices[0] = wxT("1l2l3l4l");
        choices[1] = wxT("1i2i3i4i");
        wxPanel *panel;
        wxSizer *panelSizer;
        wxRadioBox *radioBox;
        for (int i = 0; i < 8; i++) {
            panel = new wxPanel(mainPanel);
            panel->SetFont(font);
            panelSizer = new wxBoxSizer(wxVERTICAL);
            radioBox =
                new wxRadioBox(panel, wxID_ANY,
                               wxString::Format(wxT("Font %d"),
                                                font.GetPointSize()),
                                         wxDefaultPosition, wxDefaultSize,
                               2, choices);
            panelSizer->Add(radioBox, 0, wxEXPAND);
            panel->SetSizer(panelSizer);
            mainPanelSizer->Add(panel);
            font.SetPointSize(font.GetPointSize() + 2);
        }
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
