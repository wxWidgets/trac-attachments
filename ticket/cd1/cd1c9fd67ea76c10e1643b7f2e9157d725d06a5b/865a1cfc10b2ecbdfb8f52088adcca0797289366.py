import wx

class Panel(wx.Panel):
    def __init__(self, parent):
        super(Panel, self).__init__(parent)
        box = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(box)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

        bar = wx.ToolBar(self)
        bar.AddLabelTool(0, "Test", self._make_bitmap(wx.RED))
        bar.AddLabelTool(1, "Test", self._make_bitmap(wx.GREEN))
        bar.Realize()
        box.Add(bar, wx.EXPAND)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

    def _make_bitmap(self, color):
        dc = wx.MemoryDC()
        bitmap = wx.EmptyBitmap(32, 32)
        dc.SelectObject(bitmap)
        dc.SetBackground(wx.Brush(color))
        dc.Clear()
        return bitmap

app = wx.App()
frame = wx.Frame(None)
Panel(frame)
frame.Show()
app.MainLoop()
