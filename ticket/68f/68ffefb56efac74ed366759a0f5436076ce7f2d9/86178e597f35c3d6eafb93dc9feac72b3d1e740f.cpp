#include "wx/wx.h"

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
  public:
    MyFrame(const wxString& title);

    void OnQuit(wxCommandEvent& event);
    void OnAddRadio(wxCommandEvent& event);

  private:
    bool added;
    wxMenu *radioMenu;
  
    DECLARE_EVENT_TABLE()
};

enum
{
  Minimal_AddRadio = 5000,
  Minimal_Quit = wxID_EXIT,
  Minimal_Radio1 = 5001,
  Minimal_Radio2 = 5002,
  Minimal_Radio3 = 5003,
  Minimal_Radio4 = 5004,
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_AddRadio,  MyFrame::OnAddRadio)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));

  frame->Show(true);

  return true;
}

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
  SetIcon(wxICON(sample));

  wxMenu *fileMenu = new wxMenu;
  radioMenu = new wxMenu;

  fileMenu->Append(Minimal_AddRadio, _T("Add Radio"));
  fileMenu->Append(Minimal_Quit, _T("E&xit\tAlt-X"));

  radioMenu->Append(Minimal_Radio1, _T("Radio1"), _T(""), wxITEM_RADIO);
  radioMenu->Append(Minimal_Radio2, _T("Radio2"), _T(""), wxITEM_RADIO);

  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, _T("&File"));
  menuBar->Append(radioMenu, _T("&Radio"));

  SetMenuBar(menuBar);
  added = false;
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

void MyFrame::OnAddRadio(wxCommandEvent& WXUNUSED(event))
{
  //if (!added)
  //{  
  added = true;
  radioMenu->Append(Minimal_Radio3, _T("Radio3"), _T(""), wxITEM_RADIO);
  radioMenu->Append(Minimal_Radio4, _T("Radio4"), _T(""), wxITEM_RADIO);
}

 	  	 
