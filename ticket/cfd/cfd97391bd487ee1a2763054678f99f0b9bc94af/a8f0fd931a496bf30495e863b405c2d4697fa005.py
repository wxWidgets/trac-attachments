from wxPython.wx import *

class MyFrame(wxFrame):
    def __init__(self):
        wxFrame.__init__(self, NULL, -1, "Hello, world!")
        sizer = wxBoxSizer(wxHORIZONTAL)
        st = wxStaticText(self, -1, "asdf")
        sizer.Add(st, 1, wxEXPAND)
        st2 = wxStaticText(self, -1, "asdf")
        sizer.Add(st2, 1, wxEXPAND)
        self.SetSizer(sizer)

class MyApp(wxApp):
    def OnInit(self):
        frame = MyFrame()
        frame.Show()
        return true

app = MyApp(0)
app.MainLoop()

 	  	 
