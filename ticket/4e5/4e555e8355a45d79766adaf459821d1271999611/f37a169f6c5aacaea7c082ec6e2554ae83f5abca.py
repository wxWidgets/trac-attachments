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

        # Is there a better way to get the CaptionBar?
        foldpanel._captionBar.Bind(wx.EVT_SET_FOCUS, self._on_focus)
        foldpanel._captionBar.Bind(wx.EVT_KEY_DOWN, self._on_key)

    def _on_focus(self, event):
        print("Focus!")
        event.Skip()

    def _on_key(self, event):
        print("Key!")
        event.Skip()

app = wx.App()
frame = wx.Frame(None)
Panel(frame)
frame.Show()
app.MainLoop()
