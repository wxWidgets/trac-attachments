#include <wx/app.h>
#include <wx/panel.h>
#include <wx/sizer.h>

class Dialog: public wxDialog
{
public:
    Dialog(): wxDialog(NULL, wxID_ANY, _T("Dialog"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        // show/hide button
        const int ID_BUTTON = wxID_HIGHEST + 1;
        wxButton* button = new wxButton(this, ID_BUTTON, _T("Show/Hide"));
        sizer->Add(button, 1, wxGROW | wxALL, 5);
        button->SetFocus();
        Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Dialog::OnClick));

        // expander window
        m_expander = new wxWindow(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200), wxSUNKEN_BORDER);
        sizer->Add(m_expander, 0, wxALL, 5);
        m_expander->Show(false);

        SetSizerAndFit(sizer);
    }

private:
    wxWindow* m_expander;

    void OnClick(wxCommandEvent& /* event */)
    {
        m_expander->Show(!m_expander->IsShown());

        SetBestFittingSize();
#ifdef __WXGTK__
        ::wxYieldIfNeeded();
#endif

        GetSizer()->SetSizeHints(this);
    }
};


class App: public wxApp
{
    bool OnInit()
    {
        (new Dialog())->ShowModal();
        return false;
    }
};

IMPLEMENT_APP(App)

// vi: shiftwidth=4 tabstop=4 expandtab smarttab

 	  	 
