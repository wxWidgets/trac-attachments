#include "wx/wx.h"
#include "wx/datetime.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxLocale l(wxLANGUAGE_GERMAN);
    wxDateTime t(3, (wxDateTime::Month)2, 2005, 0, 0, 0);
    wxMessageBox(t.Format());
    return false;
}


 	  	 
