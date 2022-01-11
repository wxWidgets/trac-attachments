# -*- coding: utf-8 -*-#
#-----------------------------------------------------------------------------
#!/usr/bin/env python

import wx


class Dialog1(wx.Dialog):
    def __init__(self, *args, **kwds):
        super(Dialog1, self).__init__(*args, **kwds)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sb = self.CreateSB()
        sizer.Add(sb)
        self.SetSizer(sizer)

    def CreateSB(self):
        # without the panel the SB doesn't size nicely
        panel = wx.Panel(self, -1)
        sBox = wx.StaticBox(self, -1, "Static box")
        bSizer = wx.StaticBoxSizer(sBox, wx.VERTICAL)

#        tParent = self # previous to 2.9
        tParent = sBox # the 2.9 way = no tab traversal

        aPanel = wx.Panel(tParent, -1)
        txt = wx.TextCtrl(aPanel, -1)
        bSizer.Add(aPanel, 1, wx.EXPAND)

        bPanel = wx.Panel(tParent, -1)
        txt = wx.TextCtrl(bPanel, -1)
        bSizer.Add(bPanel, 1, wx.EXPAND)

        panel.SetSizer(bSizer)
        return panel

if __name__ == '__main__':
    app = wx.PySimpleApp()
    dlg = Dialog1(None)
    try:
        dlg.ShowModal()
    finally:
        dlg.Destroy()
    app.MainLoop()
