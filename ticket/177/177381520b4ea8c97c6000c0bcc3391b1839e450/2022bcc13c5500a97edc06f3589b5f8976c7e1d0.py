import wx

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title="Frame")
        dlg = wx.Dialog(self, title="Dialog", style=wx.DEFAULT_DIALOG_STYLE | wx.FRAME_FLOAT_ON_PARENT)
        self.Show()
        dlg.Show()

app = wx.PySimpleApp()
frame = TestFrame()
app.MainLoop()
