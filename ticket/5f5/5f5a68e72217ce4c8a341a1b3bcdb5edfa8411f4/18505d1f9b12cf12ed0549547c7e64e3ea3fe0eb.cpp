#include <wx/wx.h>

class App: public wxApp
{
    bool OnInit()
    {
        wxDialog* dlg = new wxDialog(NULL, wxID_ANY, _T("Dialog"), wxDefaultPosition);
        wxBoxSizer* s = new wxBoxSizer(wxVERTICAL);
        s->Add(new wxBitmapButton(dlg, wxID_ANY, wxBitmap(_T("sizingHandle.bmp"), wxBITMAP_TYPE_BMP)),
               0, wxALL, 5);
        dlg->SetSizerAndFit(s);
        dlg->ShowModal();
        return false;
    }
};

IMPLEMENT_APP(App)

 	  	 
