#!/usr/bin/env python2

import wx

app = wx.App()
f = wx.Frame(None)
bs = wx.GridSizer(2, 2)
f.SetSizer(bs)

def ListCtrl():
    lc = wx.ListCtrl(f, style=wx.LC_REPORT)
    lc.InsertColumn(0, 'x')
    lc.SetColumnWidth(0, 1000)

    for i in range(100):
        lc.InsertStringItem(i, str(i) * 100)

    bs.Add(lc, 1, flag=wx.EXPAND)

def ScrolledWindow():
    sw = wx.ScrolledWindow(f)
    sw.SetScrollRate(20, 20)
    swb = wx.BoxSizer(wx.VERTICAL)
    sw.SetSizer(swb)

    for i in range(100):
        swb.Add(wx.StaticText(sw, label='x' * 100))

    bs.Add(sw, 1, flag=wx.EXPAND)

def TextCtrl():
    te = wx.TextCtrl(f, style=wx.TE_MULTILINE | wx.TE_DONTWRAP)

    for i in range(100):
        te.AppendText('x' * 100 + '\n')

    bs.Add(te, 1, flag=wx.EXPAND)

def TreeCtrl():
    tc = wx.TreeCtrl(f, style=wx.TR_HIDE_ROOT)
    tc.AddRoot('')

    for i in range(100):
        tc.AppendItem(tc.GetRootItem(), text='x' * 100)

    bs.Add(tc, 1, flag=wx.EXPAND)

ListCtrl()
ScrolledWindow()
TextCtrl()
TreeCtrl()

f.Show()
app.MainLoop()
