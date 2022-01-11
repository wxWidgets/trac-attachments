import wx
print wx.version()

class Frame(wx.Frame):
    def __init__(self, parent=None):
        wx.Frame.__init__(self, parent)

        self.panel = wx.Panel(self)
        self.combo = wx.ComboBox(self.panel, choices=["1","2","3","1"])

        self.Show()


if __name__ == "__main__":
    app = wx.App(None)
    frame = Frame()
    app.MainLoop()