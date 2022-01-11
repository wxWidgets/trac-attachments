#!/usr/bin/env python
# -*- coding: utf-8 -*-

import wx

class MyFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        self.TTT = wx.TextCtrl(self, -1,
        "------------------------------------------------------------------------------\n\n\
        ---------------------------------------\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
        \n\n\n\n---------------------------------------", style=wx.TE_MULTILINE|wx.HSCROLL)

        self.TTT.Bind (wx.EVT_MOUSE_EVENTS, self.__xgMouseEvents)
        self.SetTitle("frame")
        self.SetSize((100, 100))
        sizer_1 = wx.BoxSizer(wx.VERTICAL)
        sizer_1.Add(self.TTT, 1, wx.EXPAND, 0)
        self.SetSizer(sizer_1)
        self.Layout()

    def __xgMouseEvents (self,event) :
        self.TTT.SetScrollPos (wx.HORIZONTAL, 100)
        self.TTT.SetScrollPos (wx.VERTICAL,   100)


if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()
    frame_1 = MyFrame(None, -1, "")
    app.SetTopWindow(frame_1)
    frame_1.Show()
    app.MainLoop()
