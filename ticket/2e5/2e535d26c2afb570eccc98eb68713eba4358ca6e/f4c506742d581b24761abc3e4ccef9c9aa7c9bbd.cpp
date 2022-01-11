#include <wx/defs.h>
#include <wx/string.h>
#include <wx/event.h>
#include <wx/app.h>
#include <wx/utils.h>

// mutex testing

wxMutex *m;

class myThread:public wxThread {
public:
	myThread(wxThreadKind kind):wxThread(kind) {
	}

	void *Entry() {
		m->Lock();
		
		for (int i=0;;i++) {
			if (TestDestroy()) {
				break;
			}
			
			wxPrintf(_T("Thread running\n"));
			wxSleep(1);
			
			if (i%10==0 && i!=0) {
				m->Unlock();
				m->Lock();
			}
		}
		
		m->Unlock();
		wxPrintf(_T("Thread %d done.\n"), GetCurrentId());
	}
	
	void OnExit() {
		wxPrintf(_T("Thread %d exiting!\n"), GetCurrentId());
	}
	
};


class myApp:public wxApp {
public:
	int OnRun() {
		m=new wxMutex();
		
		myThread *t=new myThread(wxTHREAD_JOINABLE);
		t->Create();
		t->Run();
		
		wxSleep(1);
		
		wxPrintf(_T("APP Aquiring mutex\n"));
		m->Lock();
		
		wxPrintf(_T("APP after mutex aquired\n"));
		
		m->Unlock();
		
		wxPrintf(_T("APP Waiting for thread termination\n"));

		t->Delete();
		t->Wait();
		delete m;
		delete t;
		
		return 0;
		
	}
};

IMPLEMENT_APP(myApp);

 	  	 
