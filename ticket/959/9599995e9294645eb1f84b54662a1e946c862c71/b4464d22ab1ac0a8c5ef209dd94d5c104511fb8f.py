import wx

class TestPanel(wx.Panel):
    def __init__(self, *args, **kw):
        wx.Panel.__init__(self, *args, **kw)

        # Create widgets as children of the box, and use a wx.BoxSizer
        box1 = wx.StaticBox(self, label="Children")
        sizer1 = wx.BoxSizer(wx.VERTICAL)
        box1.SetSizer(sizer1)
        self.makeWidgets(box1, sizer1)

        # Create widgets as siblings of the box and use a wx.StaticBoxSizer
        box2 = wx.StaticBox(self, label="Siblings")
        sizer2 = wx.StaticBoxSizer(box2, wx.VERTICAL)
        self.makeWidgets(self, sizer2)

        # Create widgets as children and use a wx.StaticBoxSizer
        box3 = wx.StaticBox(self, label="Children w/ sbs")
        sizer3 = wx.StaticBoxSizer(box3, wx.VERTICAL)
        self.makeWidgets(box3, sizer3)

        mainSizer = wx.BoxSizer(wx.HORIZONTAL)
        mainSizer.Add(box1, 0, wx.ALL, 15)
        mainSizer.Add(sizer2, 0, wx.ALL, 15)
        mainSizer.Add(sizer3, 0, wx.ALL, 15)
        self.SetSizer(mainSizer)


    def makeWidgets(self, parent, sizer):
        fgs = wx.FlexGridSizer(cols=2, hgap=5, vgap=5)
        fgs.AddGrowableCol(1)
        sizer.Add(fgs, 1, wx.EXPAND)
        for x in range(5):
            lbl = wx.StaticText(parent, -1, 'label %d:' % x)
            txt = wx.TextCtrl(parent, -1, 'textctrl %d' % x)
            fgs.Add(lbl)
            fgs.Add(txt, 0, wx.EXPAND)


app = wx.App()
frm = wx.Frame(None, title="static box tests")
pnl = TestPanel(frm)
frm.Sizer = wx.BoxSizer()
frm.Sizer.Add(pnl, 1, wx.EXPAND)
frm.Fit()
frm.Show()
app.MainLoop()
