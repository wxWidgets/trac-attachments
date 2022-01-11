import wx

class PseudoDcPanel(wx.Panel):
    def __init__(self, parent, pseudoDC):
        wx.Panel.__init__(self, parent)
        self.pseudoDC = pseudoDC
        self.Bind(wx.EVT_PAINT, self.OnPaint)
    def OnPaint(self, evt):
        dc = wx.PaintDC(self)
        self.pseudoDC.DrawToDC(dc)

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)

        self.pseudoDC = pdc = wx.PseudoDC()

        pdc.SetId(0)
        pdc.SetBrush(wx.TRANSPARENT_BRUSH)
        pdc.DrawLines(((50, 50), (100, 50), (100,100)))
        pdc.DrawRectangle(60, 60, 30, 30)
        pdc.DrawEllipse(60, 60, 30, 30)
        pdc.DrawSpline(((50, 50), (100, 50), (100,100)))
        pdc.SetIdBounds(0, wx.Rect(0,0,200, 200))

        moveBtn = wx.Button(self, label="Move")
        self.Bind(wx.EVT_BUTTON, self.OnMoveBtn, moveBtn)
        self.pseudoDcPanel = PseudoDcPanel(self, self.pseudoDC)

        sizer = wx.BoxSizer()
        sizer.Add(moveBtn, 0)
        sizer.Add(self.pseudoDcPanel, 1, wx.EXPAND)
        self.SetSizerAndFit(sizer)

    def OnMoveBtn(self, evt):
        self.pseudoDC.TranslateId(0, 10, 10)
        self.pseudoDcPanel.Refresh()

app = wx.App(False)
testFrame = TestFrame()
testFrame.Size = 300, 200
testFrame.Show()
app.MainLoop()
