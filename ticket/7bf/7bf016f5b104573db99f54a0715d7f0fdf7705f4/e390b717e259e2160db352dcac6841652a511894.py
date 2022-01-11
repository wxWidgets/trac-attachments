from wxPython import wx
import time

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(None, -1, "timers", size=(200, 100))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        self.frame = frame
        
        menuBar = wx.wxMenuBar()        menu = wx.wxMenu()        menu.Append(-1, "Useless Filler")        # for some reason the following menu item doesn't even show up        # unless I change the id to something other than wx.ID_EXIT        #self.menuid = wx.ID_EXIT        self.menuid = wx.wxNewId()        menu.Append(self.menuid, "E&xit\tAlt-X", "Exit this simple sample")        self.frame.Bind(wx.EVT_MENU, self.OnTimeToClose, id=self.menuid)        menuBar.Append(menu, "&File")        self.frame.SetMenuBar(menuBar)
        
        self.frame.Show(1)
        
        self.fld1 = wx.wxStaticText(panel, -1, '', (5, 5))
        self.fld2 = wx.wxStaticText(panel, -1, '', (5, 35))
        
        self.timer1 = wx.wxTimer(self.fld1, -1)
        self.timer2 = wx.wxTimer(self.fld2, -1)
        
        wx.EVT_TIMER(self.fld1, -1, self.OnTimer1)
        wx.EVT_TIMER(self.fld2, -1, self.OnTimer2)
                self.timer1.Start(1000)
        self.timer2.Start(20 * 1000)
        
        wx.EVT_CLOSE(frame, self.OnClose)
        
        self.SetTopWindow(frame)
        return 1

    def OnTimeToClose(self, evt):        self.frame.Close()

    def OnTimer1(self, event):
        t = time.localtime(time.time())
        st = time.strftime("%I:%M:%S", t)
        self.fld1.SetLabel(st)

    def OnTimer2(self, event):        t = time.localtime(time.time())        st = time.strftime("%I:%M", t)        self.fld2.SetLabel(st)

    def OnClose(self, event):
        self.timer1 = None
        self.timer2 = None
        event.Skip()

app = MyApp(0)
app.MainLoop()



 	  	 
