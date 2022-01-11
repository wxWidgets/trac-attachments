
import wx

class MyFrame(wx.Frame):
    def __init__(
            self, parent, ID, title, pos=wx.DefaultPosition,
            size=wx.DefaultSize, style=wx.DEFAULT_FRAME_STYLE
            ):

        wx.Frame.__init__(self, parent, ID, title, pos, size, style)
        panel = wx.Panel(self, -1)

        button1 = wx.Button(panel, 1003, "Close Me")
        button1.SetPosition((15, 15))
        button1.Bind(wx.EVT_BUTTON, self.OnCloseMe)
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)

        self.spin = wx.SpinCtrl(panel,wx.ID_ANY,pos=(15,70))
        self.spin.SetRange(1,10)
        
        button2 = wx.Button(panel, 1003, "Show SpinCtrl Value")
        button2.SetPosition((15, 125))
        button2.Bind(wx.EVT_BUTTON, self.OnShowSpin)

        self.show_place = wx.TextCtrl(panel,wx.ID_ANY,pos=(15,180))

    def OnCloseMe(self, event):
        self.Close(True)

    def OnCloseWindow(self, event):
        self.Destroy()

    def OnShowSpin(self,evt):
        x = self.spin.GetValue()
        self.show_place.SetValue(str(x))
        
#---------------------------------------------------------------------------

class MyApp(wx.App):
    def OnInit(self):
        frame = MyFrame(None,-1,'SpinCtrl Error')
        self.SetTopWindow(frame)
        frame.Show(True)
        return True

appl = MyApp()
appl.MainLoop()

 	  	 
