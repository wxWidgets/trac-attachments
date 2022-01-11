// mailcapbug.cc
//
// This small wxwindows program provokes a freeze in
// wxMimeTypesManagerImpl::ReadMailcap which is solved only by pressing
// control-C.  The control-C seems to unfreeze the ReadMailcap and then the
// file dialog pops up fine.
//
// My setup:
// - wxwindows 2.3.2
// - redhat linux 6.2
// - egcs 2.91.66 from 19990314
// - glibc 2.1.3
// - libpthread 0.8
//
// Compile with:
//   g++ -Wall `wx-config --cxxflags --libs` mailcapbug.cc -o mailcapbug
// 
// To reproduce the bug:
// - run mailcapbug
// - choose File:Start Thread.  Now you should get debug messages on stderr
//   like "thread count: 12"
// - choose File:Show Dialog.  Since I turned on MIME tracing with
//   wxLog::AddTraceMask (_T("mime")), you should see some mime log 
//   messages.  "In Add to Mime data 'audio/mod' with...." etc.
//   However on my machine after a few log messages it freezes.  A backtrace
//   shows that it has stopped in a system() call within
//   wxMimeTypesManagerImpl::ReadMailcap which tries to execute the
//   command "test %{encapsulation}=entity".  This is part of an /etc/mailcap
//   entry that reads:
//   > application/pgp; pgp -f < %s | metamail; needsterminal; 
//   >      test=test %{encapsulation}=entity
// - the freeze seems to last forever.  But if I press control-C, it 
//   unfreezes, I get hundreds more mime log messages and the dialog shows 
//   up.
// - if I do the same steps WITHOUT starting a separate thread, there is 
//   no freeze and the dialog shows up fine.
// - in addition, if I show the dialog first, choose something, and then
//   start the thread, I never see any thread count messages.
//   
// I'm starting to wonder if my libpthreads is a piece of junk.
//

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class MyApp: public wxApp
{
virtual bool OnInit();
};

class MyThread : public wxThread
{
  public:
  virtual ExitCode Entry ();
};

class MyFrame: public wxFrame
{
public:
MyFrame(const wxString& title, const wxPoint& pos, const wxSize&
size);
void OnQuit(wxCommandEvent& event);
void OnShow(wxCommandEvent& event);
void OnStartThread(wxCommandEvent& event);
private:
wxMenu *menuConfiguration;

DECLARE_EVENT_TABLE()
};

enum
{
ID_Quit = 1,
ID_ShowDialog,
ID_StartThread
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Quit, MyFrame::OnQuit)
EVT_MENU(ID_StartThread, MyFrame::OnStartThread)
EVT_MENU(ID_ShowDialog, MyFrame::OnShow)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  wxLog::AddTraceMask (_T("mime"));
  MyFrame *frame = new MyFrame( "Bochs Control Panel", wxPoint(50,50),
  wxSize(450,340) );
  frame->Show( TRUE );
  SetTopWindow( frame );
  return TRUE;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const
wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  // set up the gui
  menuConfiguration = new wxMenu;
  menuConfiguration->Append( ID_StartThread, "Start &Thread" );
  menuConfiguration->Append( ID_ShowDialog, "&Show Dialog" );
  menuConfiguration->Append (ID_Quit, "&Quit");

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append( menuConfiguration, "&File" );
  SetMenuBar( menuBar );
  CreateStatusBar();
  SetStatusText( "Welcome to wxWindows!" );
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
  Close( TRUE );
}

void MyFrame::OnShow(wxCommandEvent& WXUNUSED(event))
{
  wxFileDialog fdialog (this, "Choose a file", "", "", "*.*", 0);
  if (fdialog.ShowModal() == wxID_OK) {
    wxLogMessage ("you chose %s", fdialog.GetPath().c_str());
  }
}

void MyFrame::OnStartThread(wxCommandEvent& WXUNUSED(event))
{
  MyThread *thread = new MyThread ();
  thread->Create();
  thread->Run();
}

void *
MyThread::Entry ()
{
  int i = 0;
  while (1)
  {
    wxLogDebug ("thread count: %d", i++);
    Sleep (500);
  }
}

 	  	 
