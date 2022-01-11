

import wx

class MyFrame(wx.Frame):
    def __init__(
            self, parent, ID, title, pos=wx.DefaultPosition,
            size=wx.DefaultSize, style=wx.DEFAULT_FRAME_STYLE
            ):

        wx.Frame.__init__(self, parent, ID, title, pos, size, style)
        panel = wx.Panel(self, -1)

        button1 = wx.Button(panel, -1, "Close Me")
        button1.SetPosition((15, 15))
        button2 = wx.Button(panel, -1, "Set it")
        button2.SetPosition((140, 15))
        button3 = wx.Button(panel, -1, "Show it")
        button3.SetPosition((265, 15))
        self.spin = wx.SpinCtrl(panel,-1,pos=(15,80),\
           size=(50,-1),min=0,initial=0)
        self.set_it = wx.TextCtrl(panel, -1, pos=(140,80))
        self.show_it = wx.TextCtrl(panel, -1, pos=(265,80))
        self.Bind(wx.EVT_BUTTON, self.OnCloseMe, button1)
        self.Bind(wx.EVT_BUTTON,self.OnSetIt, button2)
        self.Bind(wx.EVT_BUTTON, self.OnShowIt, button3)
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)


    def OnCloseMe(self, event):
        self.Close(True)

    def OnCloseWindow(self, event):
        self.Destroy()

    def OnSetIt(self, event):
       val = self.set_it.GetValue()
       self.spin.SetValue(int(val))

    def OnShowIt(self, event):
       val = self.spin.GetValue()
       self.show_it.SetValue(str(val))

class MyApp(wx.App):
   def OnInit(self):
      self.main = MyFrame(None,-1,'Test')
      self.main.Show()
      self.SetTopWindow(self.main)
      return True

def main():
   application = MyApp(0)
   application.MainLoop()

main()

 	  	 
