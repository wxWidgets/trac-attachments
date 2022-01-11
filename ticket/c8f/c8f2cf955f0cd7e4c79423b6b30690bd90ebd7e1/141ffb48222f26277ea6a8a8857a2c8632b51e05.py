#!/usr/bin/env python2

import wx

app = wx.App()
frame = wx.Frame(None, size=(600, 480))
bs = wx.BoxSizer(wx.VERTICAL)
frame.SetSizer(bs)

class ListCtrl(wx.ListCtrl):
    def __init__(self):
        wx.ListCtrl.__init__(self, frame, style=wx.LC_REPORT)
        self.InsertColumn(0, 'x')
        self.SetColumnWidth(0, 1000)

        for i in range(100):
            self.InsertStringItem(i, 'x' * 100)

class TextCtrl(wx.TextCtrl):
    def __init__(self):
        wx.TextCtrl.__init__(self, frame,
                            style=wx.TE_MULTILINE | wx.TE_DONTWRAP)

        for i in range(100):
            self.AppendText('x' * 100 + '\n')

lc = ListCtrl()
tc = TextCtrl()
bs.Add(lc, 1, flag=wx.EXPAND)
bs.Add(tc, 1, flag=wx.EXPAND)
lc.ScrollList(dx=100, dy=100)
# The following even raises an exception
#tc.ScrollWindow(dx=100, dy=100)

frame.Show()
frame.Centre()
app.MainLoop()
