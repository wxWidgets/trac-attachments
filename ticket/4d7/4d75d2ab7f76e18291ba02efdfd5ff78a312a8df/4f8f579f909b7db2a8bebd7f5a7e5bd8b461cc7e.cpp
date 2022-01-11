// Example code for reproducing changed behavior in navigation key
// handling for the wxAuiNotebook between r72662 and 72664
//
// Issue #14821
// http://trac.wxwidgets.org/attachment/ticket/14821
#include "wx/wx.h"
#include "wx/aui/auibook.h"

/* A panel that should get keypresses (wxWANTS_CHARS), without having
them intercepted by a tab-control containing the panel.

In wxWidgets r72662, wxWANTS_CHARS makes panels like this receive
Ctrl+PgDn, Ctrl+Tab and so on (as separate key-presses, Ctrl, then PgDn).
Without wxWANTS_CHARS, the second key turns into a navigation event
for the wxAuiNotebook (all OK).

In wxWidgets r72664, Ctrl+PgDn/Ctrl+Tab always go to the
wxAuiNotebook, ignoring wxWANTS_CHARS on the panel. The panels
receive only the initial "Ctrl". */
class TestPanel : public wxPanel {
public:
  TestPanel( wxWindow* parent )
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS)
  {}
  void OnKeyDown( wxKeyEvent& ){
    wxLogMessage("TestPanel::OnKeyDown");
  }
private:
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(TestPanel, wxPanel)
EVT_KEY_DOWN(TestPanel::OnKeyDown)
END_EVENT_TABLE()

/* Irrelevant class, just housing the log window */
class TestFrame : public wxFrame {
public:
  TestFrame::TestFrame()
    : wxFrame(0, wxID_ANY, "Test Application"),
      m_logWindow(0)
  {
    m_logWindow = new wxLogWindow(0, "Log");
    m_logWindow->GetFrame()->SetPosition(wxPoint(400,0));
  }
  void OnClose( wxCloseEvent& event ){
    delete m_logWindow;
    event.Skip();
  }
  DECLARE_EVENT_TABLE()
private:
  wxLogWindow* m_logWindow;
};

BEGIN_EVENT_TABLE(TestFrame, wxFrame)
EVT_CLOSE(TestFrame::OnClose)
END_EVENT_TABLE()

class Application : public wxApp {
public:
  Application()
  {}
  bool OnInit() {
    if ( !wxApp::OnInit() ){
      return false;
    }
    wxFrame* frame = new TestFrame();
    wxAuiNotebook* book = new wxAuiNotebook(frame);
    book->AddPage( new TestPanel(book), "P1", false );
    book->AddPage( new TestPanel(book), "P2", false );
    frame->Show(true);
    frame->SetPosition(wxPoint(0,0));
    SetTopWindow(frame);
    return true;
  }
private:
};

IMPLEMENT_APP( Application )
