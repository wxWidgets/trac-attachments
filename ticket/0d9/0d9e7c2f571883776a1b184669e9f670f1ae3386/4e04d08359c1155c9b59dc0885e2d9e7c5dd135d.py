from time import sleep
import wx

class Main(wx.Frame):
    def __init__(self):
        super(Main, self).__init__(parent=None, id=-1, title="wx.Yield test")

        sizer = wx.BoxSizer(wx.VERTICAL)

        self.SetSizer(sizer)
        button = wx.Button(self, -1, "Test wx.Yield()")
        self.Bind(wx.EVT_BUTTON, self.test_guage, button)
        sizer.Add(button, 1, wx.EXPAND|wx.ALL)

        self.gauge = wx.Gauge(self, id=-1, range=100, style=wx.GA_SMOOTH)
        sizer.Add(self.gauge, 1, wx.EXPAND|wx.ALL)

        self.text = wx.TextCtrl(self, id=-1)
        sizer.Add(self.text, 1, wx.EXPAND|wx.ALL)


    def test_guage(self, event):
        wx.CallAfter(self.gauge.SetValue, 100)
        sleep(1.0)
        wx.Yield()
        self.text.SetValue("yield")
        wx.Yield()
        sleep(1.0)
        self.text.SetValue(unicode(self.gauge.GetValue()))


app = wx.App(False)
frame = Main()
frame.Show(True)
app.MainLoop()
