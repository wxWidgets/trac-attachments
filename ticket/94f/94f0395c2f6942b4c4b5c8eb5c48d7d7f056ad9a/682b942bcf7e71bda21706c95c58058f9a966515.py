import wx


class TestFrame(wx.Frame):
    def __init__(self, *args, **kwargs):
        wx.Frame.__init__(self, *args, **kwargs)

        self.tree = wx.TreeCtrl(self, wx.ID_ANY,
                                style=(wx.TR_EDIT_LABELS | wx.TR_DEFAULT_STYLE))
        self.tree.AddRoot('root')

        menubar = wx.MenuBar()
        test = wx.Menu()
        buggyadd = test.Append(wx.ID_ANY, '&Buggy Add\tCtrl-B')
        self.Bind(wx.EVT_MENU, self.OnBuggyAdd, buggyadd)
        hackfixedadd = test.Append(wx.ID_ANY, 'Hack &Fixed Add\tCtrl-F')
        self.Bind(wx.EVT_MENU, self.OnHackFixedAdd, hackfixedadd)
        menubar.Append(test, '&Test')

        self.SetMenuBar(menubar)

    def OnBuggyAdd(self, event):
        parent = self.tree.GetSelection()
        item = self.tree.AppendItem(parent, 'New')
        self.tree.Expand(parent)
        self.tree.EditLabel(item)

    def OnHackFixedAdd(self, event):
        parent = self.tree.GetSelection()
        item = self.tree.AppendItem(parent, 'New')
        self.tree.Collapse(parent) # This line fixes the problem
        self.tree.Expand(parent)
        self.tree.EditLabel(item)


app = wx.App(redirect=False)
frame = TestFrame(parent=None, id=wx.ID_ANY)
frame.Show(True)
app.MainLoop()
