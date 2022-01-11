import wx
print(wx.version())

class TestPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)

        self.lc = wx.ListCtrl(
            self, style=wx.LC_REPORT | wx.BORDER_NONE | wx.LC_EDIT_LABELS)
        self.lc.SetToolTip("This is the ToolTip")
        self.populateList()

        box = wx.BoxSizer()
        box.Add(self.lc, 1, wx.EXPAND)
        self.SetSizer(box)

    def populateList(self):
        self.lc.InsertColumn(0, "AAA")
        self.lc.InsertColumn(1, "BBB")
        self.lc.InsertColumn(2, "CCC")

        for row in range(100):
            self.lc.InsertItem(row, 'A'+str(row))
            self.lc.SetItem(row, 1, 'B'+str(row))
            self.lc.SetItem(row, 2, 'C'+str(row))


class App(wx.App):
    def OnInit(self):
        frm = wx.Frame(None, -1, "ListCtrl with a ToolTip",
                       size=(200,100),
                       style=wx.DEFAULT_FRAME_STYLE)
        frm.Show()
        pnl = TestPanel(frm)
        frm.SetSize((600,400))
        return True


app = App()
app.MainLoop()