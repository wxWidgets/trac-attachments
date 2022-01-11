import wx
print wx.version()

class MyFrame(wx.Frame):
    def __init__(self, *args, **kw):
        wx.Frame.__init__(self, *args, **kw)

        pnl = wx.Panel(self)
        txt1 = wx.TextCtrl(pnl)

        pnl2 = wx.Panel(pnl)
        dp = wx.DatePickerCtrl(pnl2)
        pnl2.Sizer = wx.BoxSizer()
        pnl2.Sizer.Add(dp, 0, wx.ALL, 5)

        pnl.Sizer = wx.BoxSizer(wx.VERTICAL)
        pnl.Sizer.Add(txt1, 0, wx.ALL, 5)
        pnl.Sizer.Add(pnl2, 0, wx.ALL, 5)

        self.Bind(wx.EVT_CHILD_FOCUS, self.OnChildFocus)


    def OnChildFocus(self, evt):
        print 'focus:', evt.GetWindow()


app = wx.App(False)
frm = MyFrame(None, title="child focus events")
frm.Show()
app.MainLoop()


