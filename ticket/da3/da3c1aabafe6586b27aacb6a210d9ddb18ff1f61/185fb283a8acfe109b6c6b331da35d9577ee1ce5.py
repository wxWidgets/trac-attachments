#!/usr/bin/env python

import wx

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title="Test Frame")

        sizer = wx.BoxSizer(wx.VERTICAL)
        button = wx.Button(self, label='Remove')
        sizer.Add(button, flag=wx.EXPAND)
        self.Bind(wx.EVT_BUTTON, self.on_remove, button)
        self.SetSizer(sizer)
        self.removed = False
    def on_remove(self, event):
        sizer = self.GetSizer()
        assert self.removed or len(sizer.GetChildren()) == 1
        sizer.Remove(0)
        assert len(sizer.GetChildren()) == 0
        self.removed = True

app = wx.PySimpleApp()
frm = TestFrame()
frm.Show()
app.MainLoop()
