#include <wx/wx.h>
#include <wx/wave.h>

class CrashApp : public wxApp
{
  public:
    CrashApp() { }
    virtual ~CrashApp() { }
    bool OnInit()
    {
      //wxWave ww("/usr/share/sounds/gtk-events/clicked.wav");
      wxWave ww("/usr/share/sounds/shutdown1.wav");
      ww.Play();
      return true;
    }
};

IMPLEMENT_APP(CrashApp)

 	  	 
