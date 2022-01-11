import wx

class App(wx.App):

    def OnInit(self):
        self.frame = wx.Frame(None)
        self.frame.Show()
        return True

    def MacReopenApp(self):
        print ("reopen")
        self.frame.Raise()

if __name__ == "__main__":
    app = App(False)
    app.MainLoop()


