#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/sysopt.h>
#include <wx/image.h>

template<typename T1, typename T2>
class Button: public wxButton
{
public:
    Button(wxWindow* parent): wxButton(parent, wxID_ANY, _T("Press Me")) {}

private:
    T1 t1;
    T2 t2;

    void OnClick(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE_TEMPLATE2(Button, wxButton, T1, T2)
    EVT_BUTTON(wxID_ANY, Button::OnClick)
END_EVENT_TABLE()

template<typename T1, typename T2>
void Button<T1, T2>::OnClick(wxCommandEvent& /* event */)
{
    SetLabel(wxString::Format(_T("sizeof T1, T2: %lu, %lu"), sizeof(t1), sizeof(t2)));
}


class App: public wxApp
{
    bool OnInit()
    {
        wxDialog* dlg = new wxDialog(NULL, wxID_ANY, _T("Dialog"), wxDefaultPosition);
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(new Button<char, short>(dlg), 0, wxALL, 5);
        sizer->Add(new Button<float, double>(dlg), 0, wxALL, 5);
        dlg->SetSizerAndFit(sizer);
        dlg->ShowModal();
        return false;
    }
};

IMPLEMENT_APP(App)

 	  	 
