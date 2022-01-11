/*
 * wxBgColour - test behaviour of SetBackgroundColour() on Mac/Linux/Windows
 *
 * COMPILE: g++ -o wxBgColour -ggdb -Wall `wx-config --cxxflags` wxBgColour.cpp `wx-config --libs std`
 */

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/button.h>


/**
 * Frame
 */
class Frame : public wxFrame
{
public:
    Frame(wxWindow* parent = 0) : wxFrame(parent, wxID_ANY, _T("Frame")) {

        Create();
    }

    virtual ~Frame() {
    }

private:
    DECLARE_CLASS(Frame);

    void Create() {

        SetBackgroundColour(wxColour(110,0,0));

        // outer panel
        wxPanel* outerPanel = new wxPanel(this, wxID_ANY);
        outerPanel->SetOwnBackgroundColour(wxColour(0,110,0));

        // inner panel
        wxPanel* innerPanel = new wxPanel(outerPanel, wxID_ANY);
        wxButton* innerButton = new wxButton(innerPanel, wxID_ANY, _T("Bar"));

        // outer panel sizer
        wxBoxSizer* outerSizer = new wxBoxSizer(wxVERTICAL);
        outerSizer->Add(new wxButton(outerPanel, wxID_ANY, _T("Foo"), wxDefaultPosition, wxSize(150,-1)), 0, wxEXPAND | wxLEFT | wxRIGHT, 8);
        outerSizer->Add(innerPanel, 0, wxEXPAND | wxLEFT | wxRIGHT, 8);

        outerPanel->SetSizerAndFit(outerSizer);
        outerSizer->SetSizeHints(this);
    }
};

IMPLEMENT_CLASS(Frame, wxFrame)


/**
 * App
 */
class App : public wxApp
{
protected:
    virtual int OnRun() {

        Frame* frame = new Frame;
        SetTopWindow(frame);
        frame->Show();

        return wxApp::OnRun();
    }
};

DECLARE_APP(App)
IMPLEMENT_APP(App)
