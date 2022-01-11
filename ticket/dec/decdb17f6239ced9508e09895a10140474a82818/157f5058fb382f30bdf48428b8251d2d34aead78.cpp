#include "wx/wx.h"
#include "wx/xrc/xmlres.h"          // XRC XML resources

class MyApp : public wxApp
{
public:
    MyApp(void) {}
    bool OnInit(void);
};

// The main window: jsut somthing with a button in it.
// Clicking on the button will open the dialog which shows the behaviour
class MyFrame : public wxMDIParentFrame
{
public:
    MyFrame(wxWindow* parent, const wxWindowID id, const wxString& title) : wxMDIParentFrame(parent, id, title) {}

    void OnClick(wxCommandEvent&);

    // Callback for EVT_SHOW event.
    // Doesn't work because the event is thrown during creation of the panel, not when the dialog is shown.
    void OnShow(wxShowEvent &);
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->LoadAllFiles(".");

    MyFrame* frame = new MyFrame(NULL, wxID_ANY, "Test Frame");
    frame->SetMenuBar(new wxMenuBar());

    wxMDIChildFrame *child = new wxMDIChildFrame(frame, wxID_ANY, "Child");
    wxPanel *panel = new wxPanel(child, wxID_ANY);
    wxButton *button = new wxButton(panel, wxID_ANY, "Click Me");

    button->Connect(wxEVT_BUTTON, wxCommandEventHandler(MyFrame::OnClick), NULL, frame);

    frame->Show();

    child->Show();

    return true;
}


void MyFrame::OnClick(wxCommandEvent&)
{
    // The top level window
    wxMDIChildFrame * dlg = new wxMDIChildFrame(this, wxID_ANY, "Test Dialog");

    // Load a wxPanel from a xrc file:
    // Panel with RadioButtons
    wxPanel* panel = wxXmlResource::Get()->LoadPanel(dlg, "FocusTestDlgRB");
    // Panel with CheckBoxes
    // wxPanel* panel = wxXmlResource::Get()->LoadPanel(dlg, "FocusTestDlgCB");

    // EVT_SHOW doesn't work because a panel is visible by default when created
    // panel->Connect(wxEVT_SHOW, wxShowEventHandler(MyFrame::OnShow), NULL, this);

    // Just resize
    dlg->Layout();

    // Set focus on 3rd TextBox
    panel->FindWindow("Table")->SetFocus();
    // Alternate way to set focus on 3rd TextBox
    // panel->WXSetPendingFocus(panel->FindWindow("Table"));

    dlg->Show();
}

void MyFrame::OnShow(wxShowEvent& evt)
{

}


