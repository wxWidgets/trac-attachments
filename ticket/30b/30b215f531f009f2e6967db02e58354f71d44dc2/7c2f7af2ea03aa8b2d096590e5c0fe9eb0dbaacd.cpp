
#include <wx/wx.h>

class MyDialog : public wxDialog
{
public:
    MyDialog (wxWindow *parent);
    void OnClose (wxCloseEvent& e);
};

MyDialog::MyDialog (wxWindow *parent)
    : wxDialog (parent, -1, _T("Close event test"),
                wxDefaultPosition, wxDefaultSize,
                wxDIALOG_MODAL | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    wxBoxSizer *topszr = new wxBoxSizer (wxVERTICAL);

    topszr->Add (CreateButtonSizer (wxOK | wxCANCEL), 0, wxALL, 12);

    SetSizer (topszr);
    topszr->Fit (this);
    topszr->SetSizeHints (this);
    SetAutoLayout (true);

    Connect (-1, wxEVT_CLOSE_WINDOW,
             wxCloseEventHandler (MyDialog::OnClose),
             NULL, this);
}

void MyDialog::OnClose (wxCloseEvent& e)
{
    wxMessageBox (_T("Close event triggered!"));
}

class MyApp : public wxApp
{
public:
    bool OnInit ();
};

bool MyApp::OnInit ()
{
    MyDialog dlg (NULL);
    dlg.ShowModal ();
    return false;
}

IMPLEMENT_APP(MyApp);

