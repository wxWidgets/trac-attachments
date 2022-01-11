#include <wx/wx.h>
#include <wx/spinctrl.h>

class MainApp : public wxApp { public: virtual bool OnInit(); };
IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
    wxFrame* win = new wxFrame((wxFrame*)0, -1, _T("Test"), wxDefaultPosition);
    win->Show(true);
    SetTopWindow(win);
    wxDialog* dlg = new wxDialog(win, -1, _T("Test"), wxDefaultPosition);
    wxFlexGridSizer* sizer = new wxFlexGridSizer(3, 2, 4, 12);
    sizer->Add(new wxStaticText(dlg, -1, _T("&Test")));
    sizer->Add(new wxSpinCtrl(dlg, -1, _T("1")));
    sizer->Add(new wxStaticText(dlg, -1, _T("T&est")));
    sizer->Add(new wxSpinCtrl(dlg, -1, _T("2")));
    sizer->Add(new wxStaticText(dlg, -1, _T("Te&st")));
    sizer->Add(new wxSpinCtrl(dlg, -1, _T("3")));
    dlg->SetSizerAndFit(sizer);
    dlg->SetAutoLayout(true);
    dlg->Layout();
    dlg->Show(true);
    return true;
}


 	  	 
