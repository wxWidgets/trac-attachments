import wx


class Frame(wx.Frame):
    def __init__(self, *args, **kwargs):
        super(Frame, self).__init__(*args, **kwargs)
        self.tree = wx.TreeCtrl(self, style=wx.TR_HIDE_ROOT)
        root = self.tree.AddRoot('Hidden root')
        self.tree.AppendItem(root, 'First visible item')
        print self.tree.GetItemText(self.tree.GetFirstVisibleItem())

app = wx.App(False)
frame = Frame(None)
frame.Show()
app.MainLoop()

 	  	 
