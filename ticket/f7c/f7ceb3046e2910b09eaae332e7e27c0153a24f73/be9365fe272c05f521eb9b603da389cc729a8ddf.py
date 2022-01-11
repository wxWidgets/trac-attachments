import wx

app = wx.PySimpleApp()
frame = wx.Frame(None, size=(400, 400))

myScrolledWin = wx.ScrolledWindow(frame)
myScrolledWin.SetScrollbars(1, 1, 1000, 1000, 300, 300)
label = wx.StaticText(myScrolledWin, label="This should be scrolled...")

def onScrollWin(event):
    print "caught wx.EVT_SCROLLWIN: position=%d, orientation=%d" % (event.Position, event.Orientation)
    event.Skip()

myScrolledWin.Bind(wx.EVT_SCROLLWIN, onScrollWin)

frame.Show()
app.MainLoop()
