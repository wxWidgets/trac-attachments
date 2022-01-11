import wx, wx.gizmos

class FrameWithTreeListCtrl(wx.Frame):
    def __init__(self, *args, **kwargs):
        super(FrameWithTreeListCtrl, self).__init__(*args, **kwargs)
        tree = wx.gizmos.TreeListCtrl(self)
        tree.AddColumn('Column 0')
        root = tree.AddRoot('Root item')
        tree.AddColumn('Column 1')
        for columnIndex in range(tree.GetColumnCount()):
            print tree.GetItemText(root, columnIndex)


app = wx.App(False)
frame = FrameWithTreeListCtrl(None)
frame.Show()
app.MainLoop()

 	  	 
