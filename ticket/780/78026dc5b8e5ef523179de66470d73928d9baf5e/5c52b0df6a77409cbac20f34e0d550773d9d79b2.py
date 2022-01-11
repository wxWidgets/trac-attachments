import wx
import wx.richtext


class Frame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)

        self.Sizer = s = wx.BoxSizer(wx.VERTICAL)
        s.Add(wx.StaticText(self, label="TextCtrl (try cmd-x)"))
        s.Add(wx.TextCtrl(self), 0, wx.BOTTOM, 20)
        s.Add(wx.StaticText(self, label="RichTextCtrl"))
        s.Add(wx.richtext.RichTextCtrl(self), 1, wx.EXPAND)


app = wx.App(False)
app.TopWindow = f = Frame()
f.Show()
app.MainLoop()
