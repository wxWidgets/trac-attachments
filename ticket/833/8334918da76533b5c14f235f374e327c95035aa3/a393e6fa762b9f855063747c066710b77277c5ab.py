from wxPython import wx

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(None, -1, "font bug", size=(200, 200))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        
        frame.Show(1)


        self.btn = wx.wxButton(panel, -1, "Button")

        borderStyle = 0 #wx.wxNO_BORDER
        tstyle = wx.wxTE_RICH2 | wx.wxTE_PROCESS_TAB | wx.wxTE_MULTILINE | borderStyle | \
                wx.wxNO_FULL_REPAINT_ON_RESIZE | wx.wxCLIP_SIBLINGS

        self.text = wx.wxTextCtrl(panel, -1, 'Hello World', (0, 50), style=tstyle)
        
        font = wx.wxFont(18, wx.wxSWISS, wx.wxNORMAL, wx.wxNORMAL)
        self.btn.SetFont(font)
        self.text.SetFont(font)

        self.SetTopWindow(frame)

        return 1


app = MyApp(0)
app.MainLoop()



 	  	 
