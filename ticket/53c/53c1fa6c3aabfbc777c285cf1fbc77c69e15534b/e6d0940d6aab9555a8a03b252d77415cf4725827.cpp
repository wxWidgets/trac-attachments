#include <wx/wx.h>

class Thread : public wxThread {
  public:
    Thread() : wxThread(wxTHREAD_JOINABLE) {}

  protected:
    virtual ExitCode Entry() {
        return 0;
    }
    virtual void OnExit() {
        Sleep(200);
        printf("Completing OnExit processing\n");
        CrashMe();
    }
    virtual void CrashMe() { }
};

void main() {
    wxInitializer wx;

    Thread * t = new Thread;
    t->Create();
    t->Run();
    Sleep(100);
    t->Wait();
    delete t;

    printf("Thread has been deleted\n");
    Sleep(200);
}

 	  	 
