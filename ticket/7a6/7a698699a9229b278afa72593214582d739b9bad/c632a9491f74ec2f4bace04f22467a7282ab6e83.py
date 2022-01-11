from wxPython.wx import *
from wxPython import calendar

class MyApp(wxApp):

    def OnInit(self):
        frame = wxFrame(NULL, -1, "Calendar SetPosition bug", size=(300, 200))
        panel = wxPanel(frame, -1)
        frame.Show(true)
        self.SetTopWindow(frame)

        # init pos is not the top of the compound calendar, but
        # just the main month part of the calendar display
        self.cal = calendar.wxCalendarCtrl(panel, -1, pos=(0, 30))
        # init pos is different than SetPosition
        # SetPosition uses top of the compound control
        # uncomment to see the problem
        #self.cal.SetPosition((0, 30))

        return true

app = MyApp(0)
app.MainLoop()

 	  	 
