
#include "wx/protocol/http.h"
#include "wx/wx.h"
#include "wx/socket.h"
#include "wx/debugrpt.h"

class TestApp: public wxApp
{
public:
    bool OnInit();
    void OnFatalException();
};

class VideoIP : public wxThread
{
public:
    VideoIP();
    void           *Entry();
};

DECLARE_APP(TestApp)
IMPLEMENT_APP(TestApp)

//===================================================================================
bool TestApp::OnInit()
{
  VideoIP       *m_Video;

  wxHandleFatalExceptions();
  wxSocketBase::Initialize();

  m_Video = new VideoIP;
  m_Video->Create();
  m_Video->Run();

  return true;
}

//===================================================================================
VideoIP::VideoIP() : wxThread(wxTHREAD_JOINABLE){}
//===================================================================================
void *VideoIP::Entry()
{
  wxHTTP          m_Http;
  wxInputStream   *m_is;
  unsigned char   m_Buffer[10];

  m_Http.SetTimeout(10);
  m_Http.Connect("195.24.42.68");
  m_is=m_Http.GetInputStream("/control/faststream.jpg?stream=MxPEG&needlength&fps=25");

  do {
    m_is->Read(m_Buffer,4);
    //    Sleep(0);
  } while ( 1 );

  return NULL;
}

//===================================================================================
void TestApp::OnFatalException()
{
  wxDebugReportCompress *report = new wxDebugReportCompress;
  report->AddAll(wxDebugReport::Context_Exception);
  if (report->Process()) {
    report->Reset();
  }
  delete report;
}
