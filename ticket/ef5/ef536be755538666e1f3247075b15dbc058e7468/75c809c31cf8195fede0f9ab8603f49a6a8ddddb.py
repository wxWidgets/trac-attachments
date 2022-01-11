import wx

class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        self.Panel = wx.Panel(self)
        self.Panel.Sizer = sizer = wx.BoxSizer()

        a = wx.TextCtrl(self.Panel)
        b = wx.TextCtrl(self.Panel)
        c = wx.DatePickerCtrl(self.Panel)
        d = wx.TextCtrl(self.Panel)
        e = wx.TextCtrl(self.Panel)

        sizer.Add(a)
        sizer.Add(b)
        sizer.Add(c)
        sizer.Add(d)
        sizer.Add(e)

        a.SetFocus()
        self.Show(True)

if __name__ == "__main__":
    app = wx.App(False)
    f = MyFrame()
    app.MainLoop()
