# -*- coding: utf-8 -*-#
#-----------------------------------------------------------------------------
#!/usr/bin/env python

import wx


class Dialog1(wx.Dialog):
    def __init__(self, *args, **kwds):
        super(Dialog1, self).__init__(*args, **kwds)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sb = self.CreateSB()
        sizer.Add(sb, 1, wx.EXPAND, border=10)
        self.SetSizer(sizer)

    def CreateSB(self):
        sBox = wx.StaticBox(self, -1, "Static box")
        bSizer = wx.BoxSizer()

        tParent = sBox # 2.9 allows that content of SB are children

        aPanel = wx.Panel(tParent, -1)
        txt = wx.TextCtrl(aPanel, -1)
        bSizer.Add(aPanel, 1, wx.EXPAND)

        bPanel = wx.Panel(tParent, -1)
        txt = wx.TextCtrl(bPanel, -1)
        bSizer.Add(bPanel, 1, wx.EXPAND)

        sBox.SetSizer(bSizer)
        return sBox

from wx.lib.mixins.inspection import InspectionMixin

class BaseApp(wx.App, InspectionMixin):
    def OnInit(self):
        self.Init() # InspectionMixin
        return True

if __name__ == '__main__':
    app = BaseApp()
    dlg = Dialog1(None)
    try:
        dlg.ShowModal()
    finally:
        dlg.Destroy()
    app.MainLoop()
