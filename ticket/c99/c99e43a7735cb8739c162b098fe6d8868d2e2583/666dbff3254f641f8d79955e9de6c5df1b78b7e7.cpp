// Demonstrate race condition with wxSocketBase::m_connected in worker thread
// with wxWidgets 3.1.0 on Windows.

#include "wx/wx.h"
#include "wx/sstream.h"
#include "wx/thread.h"
#include "wx/protocol/ftp.h"

// Download a file larger than 4096 bytes over passive FTP.
const char* host = "127.0.0.1";
const int port = 21;
const char* user = "user";
const char* pass = "pass";
const char* path = "/test.txt";

class MyThread : public wxThread
{
public:
   MyThread() : wxThread(wxTHREAD_DETACHED) {}

   virtual ExitCode Entry()
   {
      wxFTP ftp;
      ftp.SetUser(user);
      ftp.SetPassword(pass);
      if (ftp.Connect(host, port))
      {
         ftp.SetPassive(true);
         int expected = ftp.GetFileSize(path);
         wxInputStream* istream = ftp.GetInputStream(path);
         Sleep(100);  // Remove this to hide the problem.
         if (istream != nullptr && istream->IsOk())
         {
            // Read all data from socket.
            char buffer[4096];
            size_t count = 0;
            do {
               istream->Read(&buffer[0], sizeof(buffer));
               count += istream->LastRead();
            } while (!istream->Eof());
            delete istream;

            wxLogError(wxString::Format("Expected %d bytes.  Got %d bytes.",
               expected, count));
         }
         else
            wxLogError("Couldn't get stream");
      }
      else
         wxLogError("Couldn't connect to %s:%d", host, port);
      return (ExitCode)0;
   }
};


class MyFrame : public wxFrame
{
public:
    MyFrame()
    : wxFrame(nullptr, -1, "Socket Test", wxDefaultPosition, wxSize(400, 300))
    {
        new wxButton(this, wxID_OK, wxString::Format("ftp://%s%s", host, path));
        Bind(wxEVT_BUTTON, &MyFrame::OnButton, this, wxID_OK);
    }

    void OnButton(wxCommandEvent&)
    {
        (new MyThread)->Run();
    }
};


class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        wxSocketBase::Initialize();
        return (new MyFrame)->Show();
    }
};

wxIMPLEMENT_APP(MyApp);
