#!/usr/bin/env python2

import wx

app = wx.App()
f = wx.Frame(None, size=(600, 480))
bs = wx.GridSizer(4, 2)
f.SetSizer(bs)

def ListCtrl():
    lc = wx.ListCtrl(f, style=wx.LC_REPORT)
    lc.InsertColumn(0, 'x')
    lc.SetColumnWidth(0, 1000)

    for i in range(100):
        lc.InsertStringItem(i, 'x' * 100)

    lc.Bind(wx.EVT_MOUSEWHEEL, handle_mousewheel)

    bs.Add(lc, 1, flag=wx.EXPAND)

def ScrolledWindow():
    sw = wx.ScrolledWindow(f)
    sw.SetScrollRate(20, 20)
    swb = wx.BoxSizer(wx.VERTICAL)
    sw.SetSizer(swb)

    for i in range(100):
        swb.Add(wx.StaticText(sw, label='x' * 100))

    sw.Bind(wx.EVT_MOUSEWHEEL, handle_mousewheel)

    bs.Add(sw, 1, flag=wx.EXPAND)

def TextCtrl():
    te = wx.TextCtrl(f, style=wx.TE_MULTILINE | wx.TE_DONTWRAP)

    for i in range(100):
        te.AppendText('x' * 100 + '\n')

    te.Bind(wx.EVT_MOUSEWHEEL, handle_mousewheel)

    bs.Add(te, 1, flag=wx.EXPAND)

def TreeCtrl():
    tc = wx.TreeCtrl(f, style=wx.TR_HIDE_ROOT)
    tc.AddRoot('')

    for i in range(100):
        tc.AppendItem(tc.GetRootItem(), text='x' * 100)

    tc.Bind(wx.EVT_MOUSEWHEEL, handle_mousewheel)

    bs.Add(tc, 1, flag=wx.EXPAND)

def Choice():
    cc = wx.Choice(f, choices=("A", "B", "C", "D", "E", "F"))
    cc.SetSelection(0)

    cc.Bind(wx.EVT_MOUSEWHEEL, handle_mousewheel)

    bs.Add(cc)

def ComboBox():
    cb = wx.ComboBox(f, choices=("A", "B", "C", "D", "E", "F"))
    cb.SetSelection(0)

    cb.Bind(wx.EVT_MOUSEWHEEL, handle_mousewheel)

    bs.Add(cb)

def SpinCtrl():
    sc = wx.SpinCtrl(f)

    sc.Bind(wx.EVT_MOUSEWHEEL, handle_mousewheel)

    bs.Add(sc)

def handle_mousewheel(event):
    print('++++++GetTimestamp++++++', event.GetTimestamp())
    print('GetLinesPerAction', event.GetLinesPerAction())
    print('GetWheelAxis', event.GetWheelAxis())
    print('GetWheelDelta', event.GetWheelDelta())
    print('GetWheelRotation', event.GetWheelRotation())
    event.Skip()

ListCtrl()
ScrolledWindow()
TextCtrl()
TreeCtrl()
Choice()
ComboBox()
SpinCtrl()

f.Show()
app.MainLoop()
