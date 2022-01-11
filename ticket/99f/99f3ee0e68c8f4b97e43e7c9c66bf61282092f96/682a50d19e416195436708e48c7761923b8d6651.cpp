#include <wx/wx.h>

class MyApp : public wxApp
{
    public:
        virtual bool MyApp::OnInit();
};

class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString& title);
	private:
        DECLARE_EVENT_TABLE()
};

class MainPanel : public wxPanel
{
    public:

        MainPanel(wxWindow* parent);
        void OnShowDialog(wxCommandEvent& event);

    private:
        wxPanel* contentPanel_;
        DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(MyApp)
   
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(MainPanel, wxPanel)
END_EVENT_TABLE()

MainPanel::MainPanel(wxWindow* parent) : wxPanel(parent)
{
    contentPanel_ = new wxPanel(this);
    auto label = new wxStaticText(contentPanel_, wxID_ANY, "Blah Blah");
    auto button = new wxButton(this, wxID_ANY, "Show Dialog");
    Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainPanel::OnShowDialog));
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(button);
    sizer->Add(contentPanel_, 1, wxEXPAND);
    SetSizer(sizer);
}

void MainPanel::OnShowDialog(wxCommandEvent& WXUNUSED(event))
{
    auto dlg = new wxMessageDialog(contentPanel_, "Wait a little after this dialog is closed to witness the crash.");
    dlg->ShowModal();
    dlg->Destroy();
    if (contentPanel_ != NULL)
    {
        GetSizer()->Detach(contentPanel_);
        contentPanel_->Destroy();
        contentPanel_ = NULL;
    }
}

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
{
    auto mainPanel = new MainPanel(this);
    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(mainPanel, 1, wxEXPAND);
    SetSizer(sizer);
}

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;
    MainFrame *frame = new MainFrame("Dialog causes crash sample");
    frame->Show(true);
    return true;
}


