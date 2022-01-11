// Program to demonstrate a problem with wxFont::GetFaceName() in wxWidgets 3.0
#include <wx/wx.h>

class MyDialog : public wxDialog
{
public:
    wxFont m_demo_font;

    MyDialog() : wxDialog(NULL, -1, "Font Test")
    {
        m_demo_font = wxFontInfo(18).Italic();
        wxStaticText* label = new wxStaticText(this, -1, "This should be 18-point italic");
        label->SetFont(m_demo_font);

        wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(label);
        sizer->Add(new wxButton(this, -1, "Show problem"));
        SetSizerAndFit(sizer);
    }

    void OnButton(wxCommandEvent& event)
    {
        // Problem is triggered the first time we call GetFaceName()
        // on a font that has been set for a window.
        m_demo_font.GetFaceName();
        Refresh();   // The font is now deleted, so the label is redrawn
                     // using the default System font.
    }

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyDialog, wxDialog)
    EVT_BUTTON(-1, MyDialog::OnButton)
wxEND_EVENT_TABLE();

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        (new MyDialog)->ShowModal();
        return false;
   }
};

wxIMPLEMENT_APP(MyApp);
