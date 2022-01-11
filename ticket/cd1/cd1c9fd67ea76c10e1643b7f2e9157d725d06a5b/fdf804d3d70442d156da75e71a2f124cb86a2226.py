import wx

class Panel(wx.Panel):
    def __init__(self, parent):
        super(Panel, self).__init__(parent)
        box = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(box)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

        il = wx.ImageList(32, 32)
        il.Add(self._make_bitmap(wx.RED))
        il.Add(self._make_bitmap(wx.GREEN))

        book = wx.Toolbook(self, -1)
        book.AssignImageList(il)
        book.AddPage(wx.Button(book, label="Test1"), "Test", imageId=0)
        book.AddPage(wx.Button(book, label="Test2"), "Test", imageId=1)
        box.Add(book, wx.EXPAND)

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
