import wx

app = wx.App()
frame = wx.Frame(None)

sw = wx.SplitterWindow(frame)
sw.SetMinimumPaneSize(20)
sw.SetSashGravity(1.0)
sw.SplitHorizontally(wx.TextCtrl(sw), wx.TextCtrl(sw), 60)

frame.Centre()
frame.Show()
app.MainLoop()
