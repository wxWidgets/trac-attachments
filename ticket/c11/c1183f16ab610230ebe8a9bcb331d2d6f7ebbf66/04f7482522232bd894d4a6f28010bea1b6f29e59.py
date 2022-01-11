from wxPython import wx

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(None, -1, "minimal", size=(300, 400))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        
        frame.Show(1)
        
        btn = wx.wxButton(panel, -1, "Draw")        self.Bind(wx.EVT_BUTTON, self.OnDraw, btn)
        
        self.SetTopWindow(frame)
        return 1

    def OnDraw(self, event):
        dc = wx.wxClientDC(self.panel)
        dc.DrawText('Hello World', 10, 40)
        dc.DrawRotatedText('Rotated', 10, 200, 90)
        for i in range(9):
            y = 200
            angle = i * 40            dc.DrawRotatedText('Rotated World', 100, y, angle)


app = MyApp(0)
app.MainLoop()



 	  	 
