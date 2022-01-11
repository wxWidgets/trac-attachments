#include "wx/wx.h"
#include <iostream>

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
  void OnStart(wxCommandEvent& event);

private:
  DECLARE_EVENT_TABLE()
  void takeScreenshot();
  int screenshots;
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
  EVT_BUTTON(wxID_ANY, MyFrame::OnStart)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  if ( !wxApp::OnInit() )
    return false;

  MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));
  frame->Show(true);
  return true;
}

MyFrame::MyFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
{
  wxButton *button = new wxButton(this, wxID_OK, wxT("Start taking screenshots"));
  screenshots = 0;
}


void MyFrame::OnStart(wxCommandEvent& event) {

  for (int i=0; i < 100; i++) {
    takeScreenshot();
    std::cout <<  "screenshots taken: " << ++screenshots << std::endl;
    wxThread::Sleep(100);
  }
  std::cout << "finished" << std::endl;
}

void MyFrame::takeScreenshot() {

  wxScreenDC dcScreen;
  wxCoord screenWidth, screenHeight;
  dcScreen.GetSize(&screenWidth, &screenHeight);
  wxBitmap screenshot(screenWidth, screenHeight,-1);
  wxMemoryDC memDC;
  memDC.SelectObject(screenshot);
  memDC.Blit( 0, 0, screenWidth, screenHeight, &dcScreen, 0, 0);
  memDC.SelectObject(wxNullBitmap);


}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}
