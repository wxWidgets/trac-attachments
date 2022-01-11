#include <wx/wx.h>
wxWindow * creator(wxWindow * fdlgParent)
{
#if 1
        return new wxCheckBox(fdlgParent, wxID_ANY, wxT("Open as read-only")); // SIGSEGV in wxMSW; Works fine in wxGTK.
#elif 0
        return new wxTextCtrl(fdlgParent, wxID_ANY, wxEmptyString); // All good.
#elif 0
        // No extra control will be shown on the file dialog.
        wxPanel * panel = new wxPanel(fdlgParent);
        new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(200, 0));
        new wxCheckBox(panel, wxID_ANY, wxT("Open as read-only"), wxPoint(400, 0));
        return panel;
#else
        // It seems that we have to use sizer so as to obtain the expected result. This is also how the sample `dialogs` does when it displays the file dialog.
        wxPanel * panel = new wxPanel(fdlgParent);
        wxBoxSizer * sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(new wxTextCtrl(panel, wxID_ANY), 0, wxALL | wxALIGN_CENTER_VERTICAL, 10); // The text control will be missing if link with wxGTK.
        sizer->Add(new wxCheckBox(panel, wxID_ANY, wxT("Open as read-only")), 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
        panel->SetSizerAndFit(sizer);
        panel->Layout();
        return panel;
#endif
}
struct CApp : public wxApp
{
    bool OnInit() {
        wxFileDialog dlg(NULL);
        dlg.SetExtraControlCreator(creator);
        dlg.ShowModal();
        return false;
    }
};
DECLARE_APP(CApp)
IMPLEMENT_APP(CApp)
