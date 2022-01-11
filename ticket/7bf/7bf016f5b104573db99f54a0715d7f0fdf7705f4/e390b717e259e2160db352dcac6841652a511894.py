from wxPython import wx
import time

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(None, -1, "timers", size=(200, 100))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        self.frame = frame
        
        menuBar = wx.wxMenuBar()
        
        self.frame.Show(1)
        
        self.fld1 = wx.wxStaticText(panel, -1, '', (5, 5))
        self.fld2 = wx.wxStaticText(panel, -1, '', (5, 35))
        
        self.timer1 = wx.wxTimer(self.fld1, -1)
        self.timer2 = wx.wxTimer(self.fld2, -1)
        
        wx.EVT_TIMER(self.fld1, -1, self.OnTimer1)
        wx.EVT_TIMER(self.fld2, -1, self.OnTimer2)
        
        self.timer2.Start(20 * 1000)
        
        wx.EVT_CLOSE(frame, self.OnClose)
        
        self.SetTopWindow(frame)
        return 1

    def OnTimeToClose(self, evt):

    def OnTimer1(self, event):
        t = time.localtime(time.time())
        st = time.strftime("%I:%M:%S", t)
        self.fld1.SetLabel(st)

    def OnTimer2(self, event):

    def OnClose(self, event):
        self.timer1 = None
        self.timer2 = None
        event.Skip()

app = MyApp(0)
app.MainLoop()



 	  	 