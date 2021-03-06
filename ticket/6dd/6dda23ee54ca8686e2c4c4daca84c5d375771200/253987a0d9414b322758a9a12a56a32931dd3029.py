import wx

class TheFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1)
        pa1 = wx.Panel(self, -1, size=(200, -1))
        pa1.SetBackgroundColour(wx.YELLOW)
        sz1 = wx.BoxSizer(wx.HORIZONTAL)
        a = wx.RadioButton(pa1, -1, "A")
        b = wx.RadioButton(pa1, -1, "B")
        for rb in [a,b]: rb.SetBackgroundColour('GREY')
        sz1.Add(a)
        sz1.Add(b)
        pa1.SetSizer(sz1)
        pa2 = wx.Panel(self, -1)
        sz2 = wx.BoxSizer(wx.HORIZONTAL)
        but = wx.Button(pa2, -1, "Set B")
        but.Bind(wx.EVT_BUTTON, lambda event:b.SetValue(True))
        sz2.Add(but)
        pa2.SetSizer(sz2)
        sz = wx.BoxSizer(wx.VERTICAL)
        sz.Add(pa1)
        sz.Add(pa2)
        self.SetSizer(sz)
        self.Layout()

app = wx.App()
fr = TheFrame()
fr.Show()
app.MainLoop()
