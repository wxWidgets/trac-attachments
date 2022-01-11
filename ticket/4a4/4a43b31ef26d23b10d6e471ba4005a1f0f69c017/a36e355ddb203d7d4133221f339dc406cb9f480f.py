import wxversion
wxversion.select('3.0')
import wx

class TestDialog(wx.Dialog):
    def __init__(self, *args, **kwds):
        wx.Dialog.__init__(self, *args, **kwds)
        sizer = wx.BoxSizer(wx.VERTICAL)
        control = wx.TextCtrl(self, wx.ID_ANY, '')
        sizer.Add(control, 0)
        self.SetSizer(sizer)
        sizer.Fit(self)
        self.Layout()

if __name__ == "__main__":
    app = wx.App(False)
    dialog = TestDialog(None)
    try:
        dialog.ShowModal()
    finally:
        dialog.Destroy()
