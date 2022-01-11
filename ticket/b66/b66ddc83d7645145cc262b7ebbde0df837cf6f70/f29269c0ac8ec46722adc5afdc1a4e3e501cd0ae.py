import wx

class MyFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, title="Text Align Test", size=(400, 200))

        self.panel = wx.Panel(self)
        sizer = wx.BoxSizer()
        self.txt = wx.TextCtrl(self.panel, value="hello", style=wx.TE_CENTER)
        sizer.AddMany([((5, 5), 0), (self.txt, 1, wx.ALIGN_CENTER), ((5, 5), 0)])
        self.panel.SetSizer(sizer)
        msizer = wx.BoxSizer(wx.VERTICAL)
        msizer.Add(self.panel, 1, wx.EXPAND)
        self.SetSizer(msizer)

if __name__ == '__main__':
    app = wx.App(False)
    frame = MyFrame(None)
    frame.Show()
    app.MainLoop()
