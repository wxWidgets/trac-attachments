#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/richmsgdlg.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        wxGenericRichMessageDialog dlg( new wxFrame(NULL, wxID_ANY, "Test"),
            "There is a limited ability to change the lesson font. "
            "Font style (italic, bold, etc) is ignored for most fonts. "
            "If you need an ultrabold font for accessibility, Arial in style "
            "Black may work although like other unsupported style combinations "
            "it may not appear as the selected font in the font picker, even "
            "if it's what you had previously selected."
            "\n\n"
            "After you click OK to this you will be directed to the font picker to pick your font. "
            ,
            "GalaXQL font picker info",
            wxOK | wxCENTRE); 
        
        dlg.ShowModal();
        return false;
    }
};

wxIMPLEMENT_APP(MyApp);
