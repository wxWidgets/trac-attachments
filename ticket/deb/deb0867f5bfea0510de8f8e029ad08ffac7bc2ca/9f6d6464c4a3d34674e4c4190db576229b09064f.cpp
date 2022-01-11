#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#define ID_TESTDIALOG 10000
#define ID_TEXT 10001

class TestDialog: public wxDialog
{    
  DECLARE_DYNAMIC_CLASS( TestDialog )
  DECLARE_EVENT_TABLE()

public:
  TestDialog() {}
  ~TestDialog() {}
    
  TestDialog( wxWindow* parent, wxWindowID id = ID_TESTDIALOG, const wxString& caption = "TestDialog", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 300), long style = wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL )
  {
    Create(parent, id, caption, pos, size, style);
  }

  bool Create( wxWindow* parent, wxWindowID id = ID_TESTDIALOG, const wxString& caption = "TestDialog", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 300), long style = wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL )
  {
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );
    CreateControls();
    if (GetSizer())
    {
      GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
  }

  void CreateControls()
  {
    TestDialog* dlg = this;

    wxBoxSizer* boxSizer2 = new wxBoxSizer(wxVERTICAL);
    dlg->SetSizer(boxSizer2);
    wxBoxSizer* boxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    boxSizer2->Add(boxSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3);
    m_textCtrl = new wxTextCtrl( dlg, ID_TEXT, _("Some text"), wxDefaultPosition, wxDefaultSize, 0 );
    boxSizer1->Add(m_textCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
    wxBoxSizer* boxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    boxSizer2->Add(boxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3);
    wxButton* button = new wxButton( dlg, wxID_OK, "OK", wxDefaultPosition, wxDefaultSize, 0 );
    boxSizer3->Add(button, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);
  }

  void OnTextUpdated( wxCommandEvent& event )
  {
    wxLogMessage(wxString("TextCtrl IsModified returned ") + (m_textCtrl->IsModified() ? wxString("true") : wxString("false")));
    event.Skip();
  }

  void OnOkClick( wxCommandEvent& )
  {
    EndModal(wxID_OK);
  }
  
  wxTextCtrl* m_textCtrl;
};

IMPLEMENT_DYNAMIC_CLASS( TestDialog, wxDialog )

BEGIN_EVENT_TABLE( TestDialog, wxDialog )
  EVT_TEXT( ID_TEXT, TestDialog::OnTextUpdated )
  EVT_BUTTON( wxID_OK, TestDialog::OnOkClick )
END_EVENT_TABLE()


class MacosTest1App : public wxApp
{    
  DECLARE_CLASS( MacosTest1App )
public:
  MacosTest1App() {};

  virtual bool OnInit()
  {
    TestDialog* mainWindow = new TestDialog(NULL);
    mainWindow->ShowModal();
    mainWindow->Destroy();
    return false;
  }

  virtual int OnExit()
  {
    return wxApp::OnExit();
  }
};

DECLARE_APP(MacosTest1App)
IMPLEMENT_APP( MacosTest1App )
IMPLEMENT_CLASS( MacosTest1App, wxApp )
