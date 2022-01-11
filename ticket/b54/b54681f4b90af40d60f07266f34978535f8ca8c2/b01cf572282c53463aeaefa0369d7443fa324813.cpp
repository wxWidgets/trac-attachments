#include <wx/wx.h>

class Thread : public wxThread {
  public:
    Thread() : wxThread(wxTHREAD_JOINABLE) {}
  protected:
    virtual ExitCode Entry() {
        Sleep(100);
        return 0;
    }
};

void main() {
    wxInitializer wx;

    for(;;) {
        Sleep(100);
        Thread * t = new Thread;
        t->Create(); t->Run();
        t->Wait();
        delete t;
    };
}

 	  	 
