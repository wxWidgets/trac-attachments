import wx

class Panel(wx.Panel):
    def __init__(self, parent):
        super(Panel, self).__init__(parent)
        box = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(box)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

        list_ = wx.ListView(self)
        list_.InsertColumn(0, 'Test')
        list_.InsertStringItem(0, "Test")
        #list_.InsertStringItem(0, "Test")
        box.Add(list_, 1, wx.EXPAND)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

app = wx.App()
frame = wx.Frame(None)
Panel(frame)
frame.Show()
app.MainLoop()
