#include "wx/wx.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() ) return false;

    wxDialog dlg1(NULL, -1, wxT("Dialog 1"));
    dlg1.ShowModal();

    // On 10.5 we never get here:
    wxDialog dlg2(NULL, -1, wxT("Dialog 2"));
    dlg2.ShowModal();
    return false;
}
