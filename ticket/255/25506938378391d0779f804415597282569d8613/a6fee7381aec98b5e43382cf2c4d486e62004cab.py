import wx


class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        panel = wx.Panel(self)

        self.editor1 = wx.TextCtrl(panel, style=wx.TE_MULTILINE, name="editor1")
        self.editor2 = wx.TextCtrl(panel, style=wx.TE_MULTILINE, name="editor2")

        panel.Sizer = wx.BoxSizer(wx.HORIZONTAL)
        panel.Sizer.Add(self.editor1, 1, wx.EXPAND | wx.ALL, 30)
        panel.Sizer.Add(self.editor2, 1, wx.EXPAND | wx.ALL, 30)

        for ctrl in (self.editor1, self.editor2):
            ctrl.Bind(wx.EVT_ENTER_WINDOW, self.OnEnter)
            ctrl.Bind(wx.EVT_LEAVE_WINDOW, self.OnLeave)
            ctrl.Bind(wx.EVT_SET_FOCUS, self.OnFocusSet)
            ctrl.Bind(wx.EVT_KILL_FOCUS, self.OnFocusLost)

    def OnEnter(self, event):
        print event.EventObject.Name, "- Enter window"

    def OnLeave(self, event):
        print event.EventObject.Name, "- Leave window"

    def OnFocusSet(self, event):
        print event.EventObject.Name, "- Set focus"

    def OnFocusLost(self, event):
        print event.EventObject.Name, "- Lost focus"


app = wx.App()
app.TopWindow = f = TestFrame()
f.Show()
app.MainLoop()
