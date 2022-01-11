#include "wx/app.h"
#include "wx/frame.h"
#include "wx/socket.h"
#include "wx/timer.h"

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
  public:
    MyFrame();

    ~MyFrame();

    void OnTimer(wxTimerEvent& Event);

    // socket event handler
    void OnSocketEvent(wxSocketEvent& event);

  private:
    wxSocketClient *m_sock;

    wxTimer* mpTimer;

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_SOCKET(wxID_ANY,     MyFrame::OnSocketEvent)
  EVT_TIMER(wxID_ANY, MyFrame::OnTimer)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  if ( !wxApp::OnInit() )
      return false;

  MyFrame *frame = new MyFrame();

  frame->Show(true);

  return true;
}

MyFrame::MyFrame() : wxFrame(
  (wxFrame *)NULL,
  wxID_ANY,
  _("wxSocket demo: Client"),
  wxDefaultPosition,
  wxSize(300, 200))
{
  m_sock = new wxSocketClient();

  m_sock->SetEventHandler(*this);

  m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_LOST_FLAG);

  m_sock->Notify(true);

  wxIPV4address addr;

  addr.Hostname("localhost");

  addr.Service(4040);

  m_sock->Connect(addr, false);

  mpTimer = new wxTimer(this);

  mpTimer->Start(500, false);
}

MyFrame::~MyFrame()
{
  delete m_sock;
}

void MyFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{
  if (m_sock->IsConnected())
  {
    char Buffer[6] = "Hello";

    m_sock->Write(Buffer, 5);

    m_sock->Read(Buffer, 5);
  }
}

void MyFrame::OnSocketEvent(wxSocketEvent& event)
{
  switch ( event.GetSocketEvent() )
  {
    case wxSOCKET_CONNECTION:
      m_sock->Notify(false);
      m_sock->SetFlags(wxSOCKET_NOWAIT);
      break;

    default:
        break;
  }
}
