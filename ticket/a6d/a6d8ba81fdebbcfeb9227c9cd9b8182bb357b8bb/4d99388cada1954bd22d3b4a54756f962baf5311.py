import wx
from wx.lib.agw.hypertreelist import HyperTreeList, TR_NO_HEADER
print wx.lib.agw.hypertreelist.__file__
import os

app = wx.PySimpleApp()
frame = wx.Frame(None)

scrollwin = wx.PyScrolledWindow(frame, style=wx.HSCROLL|wx.VSCROLL)
scrollwin.SetScrollbars(100, 100, 30, 30, 0, 0)

for n in range(50):
    offset = n * 10
    wnd = wx.CheckBox(scrollwin, pos=(offset,offset))

wx.CallLater(5000, scrollwin.SetScrollbars, 100, 100, 30, 30, 0, 3)


frame.Show()
app.MainLoop()


