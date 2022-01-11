from wxPython.wx import *
from wxPython.stc import *

crash_on_start=0

class app(wxApp):
    def OnInit(self):
        frame = wxFrame(NULL, -1, "STC Killer", wxDefaultPosition, wxSize(600-(crash_on_start*400), 300))
        stc = wxStyledTextCtrl(frame, -1)
        stc.SetWrapMode(wxSTC_WRAP_WORD)
        stc.SetMarginWidth(1, 0)
        text="""\
I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.  I am a REALLY long line of text that gets repeated.

Horizontally resize me until I am around an inch wide.  Watch me crash."""
        stc.SetText(text)
        frame.Show(True)
        self.SetTopWindow(frame)
        return True

app = app()
app.MainLoop()

 	  	 
