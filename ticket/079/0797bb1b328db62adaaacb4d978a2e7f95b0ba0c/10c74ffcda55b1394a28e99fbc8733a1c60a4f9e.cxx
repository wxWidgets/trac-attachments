#include <iostream>
#include <wx/wx.h>
#include <wx/valgen.h>

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);

class MyFrame: public wxFrame
{
public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  wxTextCtrl textbox;
  wxTimer timer_1, timer_2;
  DECLARE_EVENT_TABLE()
  void stuff(wxTimerEvent &);
  void freezeThaw(wxTimerEvent &);
};

enum
{
 ID_TEST_TIMER = 10001, ID_TEST_TIMER_2
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_TIMER(ID_TEST_TIMER, MyFrame::stuff)
EVT_TIMER(ID_TEST_TIMER_2, MyFrame::freezeThaw)
END_EVENT_TABLE()

bool MyApp::OnInit()
{
  MyFrame *frame = new MyFrame("Hello world", wxPoint(50, 50), wxSize(450, 340));
  frame->Show(true);
  return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
  :wxFrame(NULL, wxID_ANY, title, pos, size),
   timer_1(this, ID_TEST_TIMER),
   timer_2(this, ID_TEST_TIMER_2),
   textbox(this, -1, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY)
{
  timer_1.Start(100, true);
  timer_2.Start(1000, true);
}

void MyFrame::stuff(wxTimerEvent &) {
  for (int i = 0; i < 100; i++)
    textbox.AppendText(std::to_string(i) + '\n');
}

void MyFrame::freezeThaw(wxTimerEvent &) {
  std::cout << textbox.GetInsertionPoint() << std::endl;
  Freeze();
  Thaw();
  // the insertionPoints are the same after thaw
  // but the actual position in the UI has snapped to the top
  std::cout << textbox.GetInsertionPoint() << std::endl;
}
