import wx

class MainFrame(wx.Frame):
    def __init__(self, *args, **kw):
        wx.Frame.__init__(self, *args, **kw)
        self.infoBar = wx.InfoBar(self)
        self.Sizer = wx.BoxSizer(wx.VERTICAL)
        self.Sizer.Add(self.infoBar, 0, wx.EXPAND)
        self.infoBar.ShowMessage("Test Message 1 2 3 4 5 6", wx.ICON_WARNING)

if __name__ == "__main__":
    app = wx.App()
    MainFrame(None).Show()
    app.MainLoop()
