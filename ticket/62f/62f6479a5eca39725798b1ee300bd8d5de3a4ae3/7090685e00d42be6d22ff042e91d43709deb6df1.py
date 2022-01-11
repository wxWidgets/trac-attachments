from wxPython import wx

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(None, -1, "minimal", size=(600, 200))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        
        frame.Show(1)
        
        self.canvas = wx.wxWindow(panel, -1, pos=(5, 50), size=(500, 100))
        self.fld1 = wx.wxTextCtrl(panel, -1, "one", (5, 5))
        #self.fld2 = wx.wxTextCtrl(panel, -1, "two", (105, 5))        self.fld3 = wx.wxTextCtrl(panel, -1, "three", (205, 5))
        #self.btn1 = wx.wxButton(panel, -1, "Draw", (355, 5))        #self.btn2 = wx.wxButton(panel, -1, "Cancel", (455, 5))
        #self.btn2.Disable()        
        self.SetTopWindow(frame)
        return 1


app = MyApp(0)
app.MainLoop()



 	  	 
