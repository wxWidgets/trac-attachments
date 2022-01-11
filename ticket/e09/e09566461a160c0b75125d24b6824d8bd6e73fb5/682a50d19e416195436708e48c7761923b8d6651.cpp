#include <wx/app.h>
#include <wx/socket.h>

class App : public wxApp
{
public:
   bool OnInit();
   int  OnExit();

private:
   void OnSocketEvent(wxSocketEvent& evt);

   wxSocketServer* m_listeningSocket;

   wxDECLARE_EVENT_TABLE();
};

class SocketThread : public wxThread
{
public:
   SocketThread(wxSocketBase* socket);
   ~SocketThread();
   ExitCode Entry();

private:
   wxSocketBase* m_socket;
};

wxDECLARE_APP(App);
wxIMPLEMENT_APP(App);

wxBEGIN_EVENT_TABLE(App, wxApp)
   EVT_SOCKET(wxID_ANY, App::OnSocketEvent)
wxEND_EVENT_TABLE()

bool App::OnInit()
{
   if ( !wxApp::OnInit() )
      return false;

   wxIPV4address la;
   la.Service(12345);
   m_listeningSocket = new wxSocketServer(la, wxSOCKET_NOWAIT | wxSOCKET_REUSEADDR);
   m_listeningSocket->SetEventHandler(*this);
   m_listeningSocket->SetNotify(wxSOCKET_CONNECTION_FLAG);
   m_listeningSocket->Notify(true);

   if (!m_listeningSocket->Ok())
   {
      wxLogError("Cannot bind listening socket");
      return false;
   }

   return true;
}

int  App::OnExit()
{

   return wxApp::OnExit();
}

void App::OnSocketEvent(wxSocketEvent& evt)
{
   if ( evt.GetSocketEvent() == wxSOCKET_CONNECTION )
   {
      wxSocketBase* socket = m_listeningSocket->Accept();
      if ( socket )
      {
         SocketThread* thread = new SocketThread(socket);
         if ( thread->Create() == wxTHREAD_NO_ERROR )
         {
            thread->Run();
         }
         else
         {
            delete thread;
            wxLogError("Can't run socket thread");
         }
      }
   }
}

SocketThread::SocketThread(wxSocketBase* socket)
   : wxThread(wxTHREAD_DETACHED)
   , m_socket(socket)
{
   m_socket->Notify(false);
   m_socket->SetFlags(wxSOCKET_BLOCK);
}

SocketThread::~SocketThread()
{
   if ( m_socket )
      m_socket->Destroy();
}

SocketThread::ExitCode SocketThread::Entry()
{
   wxByte buf[1024];
   m_socket->Read(buf, sizeof buf);
   m_socket->Destroy();
   m_socket = NULL;
   
   return NULL;
}
