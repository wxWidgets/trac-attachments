#include <wx/defs.h>
#include <wx/string.h>
#include <wx/log.h>
#include <wx/event.h>
#include <wx/app.h>
#include <wx/utils.h>
#include <wx/init.h>		// for wxBase-2.5.2

wxSemaphore *s;

class myThread:public wxThread {
public:
	myThread(wxThreadKind kind):wxThread(kind) {
	}

	void *Entry() {
		for (int i=0;;i++) {
			if (TestDestroy())
				break;
		
			wxPrintf(_T("Thread #2 running i=%d\n"),i);
			wxSleep(1);
			
			if (i%10==0 && i!=0) {
				wxPrintf(_T("Thread releasing semaphore!\n"));
				s->Post();
				// wxSleep(1);
				s->Wait();
			}
		}
	}
	
	void OnExit() {
		wxPrintf(_T("Thread %d exiting!\n"), GetCurrentId());
	}
	
};


int main() {
		wxInitialize();
	
		s=new wxSemaphore();
		
		myThread *t=new myThread(wxTHREAD_JOINABLE);
		t->Create();
		t->Run();
		
		wxSleep(1);
		
		wxPrintf(_T("APP aquiring semaphore\n"));
		s->Wait();
		
		wxPrintf(_T("APP after semaphore quired\n"));
		
		s->Post();
		
		/*
		for (;;) {
			wxPrintf(_T("Waiting crash\n"));
			wxSleep(1);
		}
		*/
		
		t->Delete();
		t->Wait();
		delete t;
		
		return 0;
		
		delete s;
}

 	  	 
