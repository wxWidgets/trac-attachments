#include "wx/wx.h"

#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    #include "mondrian.xpm"
#endif
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
            long style = wxDEFAULT_FRAME_STYLE);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

enum
{
    Minimal_Quit = 1,

    Minimal_About = wxID_ABOUT
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(_T("Minimal wxWindows App"),
                                 wxPoint(50, 50), wxSize(450, 340));

    frame->Show(TRUE);

    return TRUE;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
       : wxFrame(NULL, -1, title, pos, size, style)
{
    SetIcon(wxICON(mondrian));

    wxMenu *menuFile = new wxMenu;

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    SetMenuBar(menuBar);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    wxString strings[] = {wxT("choice 1"), wxT("choice 2")};

    wxChoice* choice = new wxChoice(this, -1, wxDefaultPosition,
				    wxDefaultSize, 2, strings);
    wxComboBox* combo = new wxComboBox(this, -1, wxT("standard text"),
				       wxDefaultPosition, wxDefaultSize,
				       2, strings);

    sizer->Add(choice);
    sizer->Add(combo);

    choice->Append(wxT("loooooong choice 3"));
    choice->Append(wxT("choice 4"));
    choice->Append(wxT("choice 5"));

    combo->Append(wxT("loooooong choice 3"));
    combo->Append(wxT("choice 4"));
    combo->Append(wxT("choice 5"));

    wxSize bestSize = choice->GetBestSize();
    choice->SetSize(bestSize);
    sizer->SetItemMinSize(choice, bestSize.GetWidth(), bestSize.GetHeight());

    bestSize = combo->GetBestSize();
    combo->SetSize(bestSize);
    sizer->SetItemMinSize(combo, bestSize.GetWidth(), bestSize.GetHeight());

    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWindows!"));
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the About dialog of the minimal sample.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, _T("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

 	  	 
