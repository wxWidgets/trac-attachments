import wx

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        self.button = wx.Button(self, label="Crash Me")
        self.Bind(wx.EVT_BUTTON, self.OnCrashMe, self.button)

    def OnCrashMe(self, evt):
        dlg = wx.FileDialog(self.button)
        try:
            dlg.ShowModal()
        finally:
            dlg.Destroy()
        self.button.Destroy()

app = wx.PySimpleApp()
frame = TestFrame()
frame.Show()
app.MainLoop()
