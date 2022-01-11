import wx


class MyFrame(wx.Frame):
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, -1, title,
                          pos=(150, 150), size=(350, 200))
        panel = wx.Panel(self)

        self.lb = lb = wx.ListBox(panel, -1, style=wx.LB_EXTENDED)
        lb.Bind(wx.EVT_LISTBOX, self.OnSelection)
        lb.SetMinSize((100, 100))
        lb.AppendItems([str(i) for i in range(1000)])

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(lb, 1, wx.EXPAND)
        panel.SetSizerAndFit(sizer)
        self.Show(True)

    def OnSelection(self, e):
        print "%s items selected" %len(self.lb.GetSelections())


app = wx.App(redirect=False)
MyFrame(None, "sample")
app.MainLoop()

