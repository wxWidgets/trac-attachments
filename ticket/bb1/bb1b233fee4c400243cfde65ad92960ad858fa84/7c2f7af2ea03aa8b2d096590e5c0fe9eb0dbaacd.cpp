#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/evtloop.h>
#include <wx/process.h>

class Proc: public wxEvtHandler {
private:
   wxProcess* proc;
   long pid;
public:
   Proc()
      : wxEvtHandler(),
        proc(NULL),
        pid(0) {
      Connect(wxEVT_END_PROCESS, wxProcessEventHandler(Proc::OnTerm));
   }
   void Run(void) {
      proc = new wxProcess(this);
      proc->Redirect();
      if ((pid = wxExecute("sort", wxEXEC_ASYNC, proc)) == 0) {
         wxLogMessage("Can't execute.");
         //wxLog::FlushActive();
         delete proc;
         proc = NULL;
         return;
      }
      wxLogMessage("Process started.");
      //wxLog::FlushActive();
   }
   void Stop(void) {
      if (!proc)
         return;
      proc->CloseOutput();
      while (pid) {
         wxLogMessage("Waiting for %ld.", pid);
         //wxLog::FlushActive();
         wxSafeYield();
      }
      delete proc;
      proc = NULL;
      wxLogMessage("Process stopped.");
      //wxLog::FlushActive();
   }
private:
   void OnTerm(wxProcessEvent& e) {
      wxLogMessage("Process %d terminated.", e.GetPid());
      //wxLog::FlushActive();
      pid = 0;
   }
};

class Test: public wxApp {
public:
   bool OnInit() {
      wxLogMessage("Event loop = %p", wxEventLoopBase::GetActive());
      //wxLog::FlushActive();
      Proc p;
      p.Run();
      p.Stop();
      return false;
   }
};
IMPLEMENT_APP(Test)
