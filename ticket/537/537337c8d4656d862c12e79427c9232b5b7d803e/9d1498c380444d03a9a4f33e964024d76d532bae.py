from wxPython import wx

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(None, -1, "slider test", size=(200, 200))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        
        frame.Show(1)
        
        slider1 = wx.wxSlider(panel, -1, 10, 0, 100, (30, 30))
        
        slider2 = wx.wxSlider(panel, -1, 10, 0, 100, (30, 80), style=wx.wxSL_HORIZONTAL | wx.wxSL_AUTOTICKS | wx.wxSL_LABELS)
        
        self.SetTopWindow(frame)
        return 1



app = MyApp(0)
app.MainLoop()



 	  	 
