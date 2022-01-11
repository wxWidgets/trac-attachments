import wx, wx.lib.agw.hypertreelist

class Frame(wx.Frame):
    def __init__(self, *args, **kwargs):
        super(Frame, self).__init__(*args, **kwargs)
        self.tree = wx.lib.agw.hypertreelist.HyperTreeList(self) 
        self.tree.AddColumn("First column")
        root = self.tree.AddRoot("Root", ct_type=1)
        parent = self.tree.AppendItem(root, "First child", ct_type=1)
        child = self.tree.AppendItem(parent, "First Grandchild", ct_type=1)
        self.tree.AppendItem(root, "Second child", ct_type=1)


app = wx.App(False)
f = Frame(None)
f.Show()
app.MainLoop()
