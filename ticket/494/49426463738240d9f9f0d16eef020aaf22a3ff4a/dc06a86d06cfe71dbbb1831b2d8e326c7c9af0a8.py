#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import wx
import wx.lib.scrolledpanel


class MyPanel(wx.Panel):
    def __init__(self, parent):
        super(wx.Panel, self).__init__(parent)
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(wx.Choice(self, choices=['a', 'b']))
        sizer.Add(wx.TextCtrl(self, value=str(id(self))))
        self.SetSizer(sizer)


class MyFrame(wx.Frame):
    def __init__(self):
        super(wx.Frame, self).__init__(None)
        sizer = wx.BoxSizer(wx.VERTICAL)

        bt = wx.Button(self, label='Test Add')
        bt.Bind(wx.EVT_BUTTON, self._OnAdd)
        sizer.Add(bt)

        self.panel = wx.lib.scrolledpanel.ScrolledPanel(self, style=wx.TAB_TRAVERSAL)
        self.panelsizer = wx.BoxSizer(wx.VERTICAL)

        i = 0
        while i < 20:
            self.panelsizer.Add(MyPanel(self.panel))
            i += 1

        self.panel.SetSizer(self.panelsizer)
        self.panel.SetupScrolling()

        sizer.Add(self.panel, proportion=1, flag=wx.EXPAND)
        self.SetSizer(sizer)

    def _OnAdd(self, event):
        focus = MyPanel(self.panel)
        self.panelsizer.Add(focus)

        self.Layout()
        # this alone doesn't work
        focus.SetFocus()
        # !!!!!!!!!!!!!!!!!!!!!!
        # this is the WORKAROUND
        #self.panel.ScrollChildIntoView(focus)


if __name__ == '__main__':
    app = wx.App()
    win = MyFrame()
    win.Show()
    app.MainLoop()
