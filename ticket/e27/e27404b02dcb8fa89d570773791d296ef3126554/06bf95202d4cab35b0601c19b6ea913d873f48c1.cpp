#include <wx/wx.h>
#include <ApplicationServices/ApplicationServices.h>
 
class MyApp : public wxApp
{
  virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame
{
public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  void OnQuit(wxCommandEvent& event);
};

enum
  {
    ID_Quit=1
  };


bool MyApp::OnInit()
{
  ProcessSerialNumber PSN;
  GetCurrentProcess(&PSN);
  TransformProcessType(&PSN,kProcessTransformToForegroundApplication);
  
  MyFrame *frame = new MyFrame( _("Hello World"), wxPoint(50, 50),
                                wxSize(450, 350));

  frame->Connect( ID_Quit, wxEVT_COMMAND_MENU_SELECTED,
                  (wxObjectEventFunction) &MyFrame::OnQuit );

  frame->Show(true);
  SetTopWindow(frame);
  return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
  : wxFrame( NULL, -1, title, pos, size )
{
  wxMenuBar *menuBar = new wxMenuBar;
  wxMenu *menuFile = new wxMenu;

  menuFile->Append( ID_Quit, _("E&xit") );
  menuBar->Append(menuFile, _("&File") );
  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText( _("Welcome to wxWidgets!") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}
