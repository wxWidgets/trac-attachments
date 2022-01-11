import wx

class Panel(wx.Panel):
    def __init__(self, parent):
        super(Panel, self).__init__(parent)
        box = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(box)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

        tree = wx.TreeCtrl(self, style=wx.TR_DEFAULT_STYLE | wx.TR_MULTIPLE)
        root = tree.AddRoot(text="Test")
        #tree.SelectItem(root)
        #tree.UnselectAll()
        tree.AppendItem(root, text="Test")
        tree.AppendItem(root, text="Test")
        box.Add(tree, 1, wx.EXPAND)

        box.Add(wx.Button(self, label="Test"))
        box.Add(wx.Button(self, label="Test"))

app = wx.App()
frame = wx.Frame(None)
Panel(frame)
frame.Show()
app.MainLoop()
