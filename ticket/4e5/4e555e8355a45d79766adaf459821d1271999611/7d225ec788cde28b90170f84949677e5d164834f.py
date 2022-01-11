import wx
import wx.lib.agw.foldpanelbar as fpb

class Panel(wx.Panel):
    def __init__(self, parent):
        super(Panel, self).__init__(parent)
        box = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(box)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

        bar = fpb.FoldPanelBar(self)
        foldpanel = bar.AddFoldPanel("Test")
        button = wx.Button(foldpanel, label="Test")
        bar.AddFoldPanelWindow(foldpanel, button)
        box.Add(bar, 1, wx.EXPAND)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

app = wx.App()
frame = wx.Frame(None)
Panel(frame)
frame.Show()
app.MainLoop()
