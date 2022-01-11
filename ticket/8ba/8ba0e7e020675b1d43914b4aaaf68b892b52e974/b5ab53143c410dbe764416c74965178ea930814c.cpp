#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/msw/dirdlg.h"   // same results with "wx/dirdlg.h" or with "wx/msw/dirdlg.h"

class TestDirDialogApp: public wxApp
{    
    DECLARE_CLASS( TestDirDialogApp )
    DECLARE_EVENT_TABLE()

public:
    TestDirDialogApp();
    virtual bool OnInit();
    virtual int OnExit();
};

DECLARE_APP(TestDirDialogApp)

class TestDirDialog: public wxFrame
{    
    DECLARE_CLASS( TestDirDialog )
    DECLARE_EVENT_TABLE()

  public:
    TestDirDialog( wxWindow* parent, wxWindowID id = 10000, const wxString& caption = _(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 300), long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX);

    bool Create( wxWindow* parent, wxWindowID id = 10000, const wxString& caption = _(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 300), long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX);

    ~TestDirDialog();
};

IMPLEMENT_APP( TestDirDialogApp )
IMPLEMENT_CLASS( TestDirDialogApp, wxApp )

BEGIN_EVENT_TABLE( TestDirDialogApp, wxApp )
END_EVENT_TABLE()

TestDirDialogApp::TestDirDialogApp()
{
}

bool TestDirDialogApp::OnInit()
{    
	TestDirDialog* mainWindow = new TestDirDialog( NULL );
	mainWindow->Show(true);
  return true;
}

int TestDirDialogApp::OnExit()
{    
	return wxApp::OnExit();
}

IMPLEMENT_CLASS( TestDirDialog, wxFrame )

BEGIN_EVENT_TABLE( TestDirDialog, wxFrame )
END_EVENT_TABLE()

TestDirDialog::TestDirDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
  Create( parent, id, caption, pos, size, style );
}

TestDirDialog::~TestDirDialog()
{
}

bool TestDirDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
  wxFrame::Create( parent, id, caption, pos, size, style );

  wxDirDialog* dir1 = new wxDirDialog(this,"Default style" ,"",wxDD_DEFAULT_STYLE);
  wxDirDialog* dir2 = new wxDirDialog(this,"Dir must exist","",wxDD_DIR_MUST_EXIST);
  
  dir1->ShowModal();
  dir2->ShowModal();
  
  return true;
}
