import wx
import wx.lib.agw.aui as aui

class MyFrame(wx.Frame):
    def __init__(self, parent):
        super(MyFrame, self).__init__(parent, title="Test AuiNotebook.SetFont")

        self.panel = MyPanel(self)

class MyPanel(wx.Panel):
    def __init__(self, parent):
        super(MyPanel, self).__init__(parent)

        self.nb = aui.AuiNotebook(self)
        self.fbtn = wx.Button(self, label="Change Font")
        self.pgbtn = wx.Button(self, label="Add Page")

        # Add some pages to start with
        for x in range(3):
            self.NewPage()
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.nb, 1, wx.EXPAND)
        hsizer = wx.BoxSizer(wx.HORIZONTAL)
        hsizer.AddMany([(self.fbtn, 0), (self.pgbtn, 0)])
        sizer.Add(hsizer, 0, wx.ALL, 5)
        self.SetSizer(sizer)

        # Events
        self._newfont = wx.Font(20, wx.FONTFAMILY_MODERN,
                                wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL)
        self.Bind(wx.EVT_BUTTON, lambda evt: self.nb.SetFont(self._newfont))
        self.Bind(wx.EVT_BUTTON, lambda evt: self.NewPage(), self.pgbtn)

    def NewPage(self):
        pcount = self.nb.GetPageCount()
        panel = wx.Panel(self.nb)
        self.nb.AddPage(panel, "Page %d" % pcount)

app = wx.App(False)
f = MyFrame(None)
f.Show()
app.MainLoop()
