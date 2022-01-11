#include <stdio.h>
#include <wx/wx.h>


  #define APP_TYPE wxAppConsole
//#define APP_TYPE wxApp



class MyApp;
// ====================================
class MyThread : public wxThread
{
public:
                      MyThread ( MyApp* app ) : mApp(app) {}
  wxThread::ExitCode  Entry ();
               MyApp* mApp;
};
// ====================================
class MyApp : public APP_TYPE
{
MyThread* mThread;
public:
bool  OnInit ()
{
  MyThread* t = new MyThread ( this );
  t->Create();
  t->Run();
  printf ( "MyApp quits OnInit()\n" );
}
void  OnEvent ( wxCommandEvent& event )
{
  printf ( "MyApp receives an event.\n" );
}
void  OnEventLoopEnter ( wxEventLoopBase* loop )
{
  printf ( "MyApp OnEventLoopEnter()\n" );
}
DECLARE_EVENT_TABLE()
};
// ------------------------------------
DECLARE_APP   ( MyApp )
IMPLEMENT_APP ( MyApp )
BEGIN_EVENT_TABLE ( MyApp, APP_TYPE )
  EVT_BUTTON  ( wxID_ANY, MyApp::OnEvent )
END_EVENT_TABLE()

// ------------------------------------
wxThread::ExitCode MyThread::Entry ()
{
  printf ( "MyThread started.\n" );
  for ( ;; ) {
    wxMilliSleep ( 500 );
    wxCommandEvent* event = new wxCommandEvent ( wxEVT_BUTTON, wxID_ANY );
    // why wxEVT_BUTTON ? why not ! just to test
    printf ( "MyThread sends an event.\n" );
    wxQueueEvent ( mApp, event );
  }
}
