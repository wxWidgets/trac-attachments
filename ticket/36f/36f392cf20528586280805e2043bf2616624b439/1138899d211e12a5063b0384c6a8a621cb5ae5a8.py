import wx

class TestKeyBindDialog(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, style=wx.DEFAULT_DIALOG_STYLE|wx.WANTS_CHARS)
        button = wx.Button(self, label="Press a Key", style=wx.WANTS_CHARS)
        button.SetFocus()
        button.Bind(wx.EVT_KEY_DOWN, self.OnKeyDown)

    def OnKeyDown(self, evt):
        print "OnKeyDown", evt.GetKeyCode()

app = wx.PySimpleApp()
dlg = TestKeyBindDialog(None)
dlg.ShowModal()
