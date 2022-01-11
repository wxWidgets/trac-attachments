#include "wx/wx.h"   
#include <wx/progdlg.h>
class MyApp : public wxApp {
public:   
    bool OnInit()
    {
     wxGenericProgressDialog *progress_bar = new wxGenericProgressDialog ("Title", "Very very very long string. It is not centered properly within this dialog. I think that this is a bug",100, NULL);
        return true;
    }
};

IMPLEMENT_APP(MyApp)
