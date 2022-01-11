/*
Just click on the tab and you will never go out of the function call
::IsDialogMessage(GetHwnd(), msg) in wxWindowMSW::MSWProcessMessage (msw/window.cpp l.2487)
*/

#include "wx/wx.h"
#include "wx/aui/tabmdi.h"


class Test : public wxApp {
public:
  bool OnInit() {
    wxApp::OnInit();

    wxAuiMDIParentFrame *parent = new wxAuiMDIParentFrame(0, wxID_ANY, "Parent");
    wxAuiMDIChildFrame *child = new wxAuiMDIChildFrame(parent, wxID_ANY, "Child");
    child->SetSizer(new wxBoxSizer(wxVERTICAL));
    child->GetSizer()->Add(new wxTextCtrl(child, wxID_ANY));
    parent->Show();
    SetTopWindow(parent);

    return true;
  }
};

IMPLEMENT_APP( Test )
