import wx

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        panel = wx.Panel(self)
        combo = wx.ComboBox(panel)
        combo.Append("hello")
        combo.Append("world")

        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.OnTimer, self.timer)
        self.timer.Start(1000)

    def OnTimer(self, evt):
        wx.CallAfter(self.DoNothing)

    def DoNothing(self):
        pass

app = wx.PySimpleApp()
frame = TestFrame()
frame.Show()
app.MainLoop()
