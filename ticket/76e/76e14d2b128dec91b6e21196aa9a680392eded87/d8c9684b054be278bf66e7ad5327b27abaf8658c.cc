#include <wx/app.h>
#include <wx/menu.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>

enum {
  ID_Modal
};

// Main Frame
class PbFrame : public wxFrame
{
  public:
    PbFrame();
    virtual ~PbFrame();
    void showModalWindow(wxCommandEvent& event);

  private:
    wxMenuBar *menuBar_;

    DECLARE_EVENT_TABLE();
};

// Dialog whose destruction entails segmentation fault
class ChmodDialog : public wxDialog
{
  public:
    ChmodDialog(wxWindow* parent);
    virtual ~ChmodDialog();

    DECLARE_EVENT_TABLE();
};

class DerivedApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(DerivedApp);

BEGIN_EVENT_TABLE(ChmodDialog, wxDialog)
END_EVENT_TABLE();

BEGIN_EVENT_TABLE(PbFrame, wxFrame)
  EVT_MENU(ID_Modal, PbFrame::showModalWindow)
END_EVENT_TABLE();

bool
DerivedApp::OnInit()
{
  PbFrame *the_frame = new PbFrame();

  the_frame->Show(true);
  SetTopWindow(the_frame);

  return true;
}

ChmodDialog::ChmodDialog(wxWindow* parent)
  : wxDialog(parent, -1, "Modifier les permissions")
{
  wxSizer *btnSizer = CreateButtonSizer(wxCANCEL | wxOK);

  wxPanel* panel = new wxPanel(this, wxID_ANY);

  wxCheckBox *checkBoxLecUsr = new wxCheckBox(panel, wxID_ANY, "Lecture", wxDefaultPosition, wxDefaultSize);

  wxStaticBox *usrBox = new wxStaticBox(panel, wxID_ANY, "Proprietaire:");
  wxStaticBoxSizer *usrSizer = new wxStaticBoxSizer(usrBox, wxVERTICAL);
  usrSizer->Add(checkBoxLecUsr, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  wxBoxSizer *panelSizer = new wxBoxSizer(wxHORIZONTAL);
  panelSizer->Add(usrSizer, 0, wxGROW | wxALL, 0);

  panel->SetSizer(panelSizer);
  panelSizer->Fit(panel);
  panelSizer->SetSizeHints(panel);
  
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  topSizer->Add(panelSizer, 0, wxGROW | wxALIGN_CENTRE | wxALL, 5);
  topSizer->Add(btnSizer);

  SetSizer(topSizer);
  topSizer->Fit(this);
  topSizer->SetSizeHints(this);
}

ChmodDialog::~ChmodDialog()
{}

PbFrame::PbFrame()
  : wxFrame((wxFrame *) NULL, -1, "Bug", wxDefaultPosition, wxDefaultSize,
            wxDEFAULT_FRAME_STYLE)
{
  menuBar_ = new wxMenuBar;
  SetMenuBar(menuBar_);
  
  wxMenu *menuModal = new wxMenu;
  wxMenuItem *itemModal = new wxMenuItem(menuModal, ID_Modal, "Modal Window");
  menuModal->Append(itemModal);

  menuBar_->Append(menuModal, "File");
}

void
PbFrame::showModalWindow(wxCommandEvent& event)
{
  ChmodDialog dialog(this);
  dialog.ShowModal();
}

PbFrame::~PbFrame()
{}

 	  	 
