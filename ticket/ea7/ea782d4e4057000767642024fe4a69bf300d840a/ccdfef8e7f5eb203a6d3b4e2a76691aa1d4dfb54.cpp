#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>
#include <wx/timer.h>
#include <wx/app.h>

class Dialog: public wxDialog {
private:
    wxStaticText *label1;
    wxStaticText *label2;
    wxTimer timer;
public:
    Dialog(wxWindow *parent): wxDialog(parent, wxID_ANY, wxT("Test")),
                              timer(this) {
        wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        label1 = new wxStaticText(this, wxID_ANY,
                                  wxT("Parent->IsEnabled(): unknown"));
        sizer->Add(label1, 0, wxEXPAND | wxALL, 5);
        label2 = new wxStaticText(this, wxID_ANY,
                                  wxT("Parent->IsThisEnabled(): unknown"));
        sizer->Add(label2, 0, wxEXPAND | wxALL, 5);
        SetSizerAndFit(sizer);
        Connect(wxEVT_TIMER, wxTimerEventHandler(Dialog::updateLabels));
        timer.Start(1000, wxTIMER_ONE_SHOT);
    }

    void updateLabels(wxTimerEvent &event) {
        wxWindow *parent = GetParent();
        label1->SetLabel(wxString::Format(wxT("Parent->IsEnabled(): %d"),
                                          parent->IsEnabled()));
        label2->SetLabel(wxString::Format(wxT("Parent->IsThisEnabled(): %d"),
                                          parent->IsThisEnabled()));
        event.Skip();
    }
};

class Frame: public wxFrame {
private:
    wxPanel *mainPanel;
    wxRadioBox *radioBox;
    wxButton *button1;
    wxButton *button2;
    wxButton *problematicButton, *problematicChildButton;
    wxPanel *problematicPanel;
    wxTextCtrl *textCtrl;
    wxToggleButton *toggleButton;
    wxColor disabledColor, enabledColor;
public:
    Frame(): wxFrame(NULL, wxID_ANY, wxT("Frame test")),
             enabledColor(0, 255, 0) {
        wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        mainPanel = new wxPanel(this, wxID_ANY);
        sizer->Add(mainPanel, 1, wxEXPAND);
        wxSizer *mainPanelSizer = new wxBoxSizer(wxVERTICAL);
        // radioBox
        wxString choices[3];
        choices[0] = wxT("wxDialog");
        choices[1] = wxT("wxMessageDialog");
        choices[2] = wxT("Nothing");
        radioBox = new wxRadioBox(mainPanel, wxID_ANY, wxT("Display"),
                                  wxDefaultPosition, wxDefaultSize,
                                  3, choices, 1, wxRA_SPECIFY_COLS);
        mainPanelSizer->Add(radioBox, 0, wxALL, 5);
        // Button 1
        button1 = new wxButton(mainPanel, wxID_ANY, wxT("Change state"));
        Connect(button1->GetId(), wxEVT_BUTTON,
                wxCommandEventHandler(Frame::button1Clicked), NULL, this);
        mainPanelSizer->Add(button1, 0, wxALL, 5);
        disabledColor = button1->GetBackgroundColour();
        // Button 2
        button2 = new wxButton(mainPanel, wxID_ANY, wxT("Focus problematic 1\n"
                                                        "Do not change state"));
        Connect(button2->GetId(), wxEVT_BUTTON,
                wxCommandEventHandler(Frame::button2Clicked), NULL, this);
        mainPanelSizer->Add(button2, 0, wxALL, 5);
        mainPanel->SetSizer(mainPanelSizer);
        // problematicButton
        problematicButton =
            new wxButton(mainPanel, wxID_ANY, wxT("Problematic 1"));
        problematicButton->Disable();
        Connect(problematicButton->GetId(), wxEVT_BUTTON,
                wxCommandEventHandler(Frame::problematicButtonClicked),
                NULL, this);
        mainPanelSizer->Add(problematicButton, 0, wxALL, 10);
        // toggleButton (problematic 2)
        toggleButton = new wxToggleButton(mainPanel, wxID_ANY,
                                          wxT("Problematic 2"));
        toggleButton->Disable();
        Connect(toggleButton->GetId(), wxEVT_TOGGLEBUTTON,
                wxCommandEventHandler(Frame::toggleButtonClicked), NULL, this);
        mainPanelSizer->Add(toggleButton, 0, wxALL, 10);
        // problematicPanel
        problematicPanel = new wxPanel(mainPanel, wxID_ANY);
        problematicChildButton = new wxButton(problematicPanel, wxID_ANY,
                                              wxT("Problematic child"));
        wxSizer *tempSizer = new wxBoxSizer(wxVERTICAL);
        tempSizer->Add(problematicChildButton, 0);
        problematicPanel->SetSizer(tempSizer);
        problematicPanel->Disable();
        mainPanelSizer->Add(problematicPanel, 0, wxALL, 10);
        // textCtrl
        textCtrl = new wxTextCtrl(mainPanel, wxID_ANY);
        textCtrl->SetValue(wxT("This is Ok"));
        textCtrl->SetBackgroundColour(disabledColor);
        textCtrl->Disable();
        mainPanelSizer->Add(textCtrl, 0, wxALL, 10);
        SetSizerAndFit(sizer);
    }

    void showRequestedDialog(void) {
        switch (radioBox->GetSelection()) {
        case 0: // Dialog
            do {
                Dialog(this).ShowModal();
            } while (0);
            break;
        case 1: // wxMessageDialog
            do {
                wxMessageDialog(this, wxT("Test")).ShowModal();
            } while (0);
            break;
        }
    }
    
    void button1Clicked(wxCommandEvent &event) {
        bool mustEnable = !problematicButton->IsEnabled();
        wxColour color;
        if (mustEnable) {
            color = enabledColor;
        } else {
            color = disabledColor;
        }
        problematicButton->Enable(mustEnable);
        problematicButton->SetBackgroundColour(color);
        problematicButton->Refresh();
        toggleButton->Enable(mustEnable);
        toggleButton->SetBackgroundColour(color);
        toggleButton->Refresh();
        textCtrl->Enable(mustEnable);
        textCtrl->SetBackgroundColour(color);
        textCtrl->Refresh();
        problematicPanel->Enable(mustEnable);
        problematicChildButton->SetBackgroundColour(color);
        problematicPanel->Refresh();
        showRequestedDialog();
        event.Skip();
    }

    void problematicButtonClicked(wxCommandEvent &event) {
        wxMessageBox(wxString::Format("Button enable status: %d",
                                      problematicButton->IsEnabled()));
        event.Skip();
    }

    void toggleButtonClicked(wxCommandEvent &event) {
        wxMessageBox(wxString::Format("ToggleButton enable status: %d",
                                      toggleButton->IsEnabled()));
        event.Skip();
    }

    void button2Clicked(wxCommandEvent &event) {
        problematicButton->SetFocus();
        showRequestedDialog();
        event.Skip();
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
