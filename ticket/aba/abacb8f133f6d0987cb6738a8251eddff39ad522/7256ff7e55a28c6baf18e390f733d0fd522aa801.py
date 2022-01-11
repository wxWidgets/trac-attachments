# -*- coding: utf-8 -*-

__author__ = 'waynebell'

import wx

class Dialog(wx.Dialog):

    def __init__(self, parent, id):

        wx.Dialog.__init__(self, None, -1, 'Preferences', size=(100,100), style=wx.STAY_ON_TOP)

        # widgets
        p = wx.Panel(self, -1)
        stat = wx.StaticText(p, -1, 'Prefs')

        #layout
        vs = wx.BoxSizer(wx.VERTICAL)
        vs.Add(stat, wx.ALL, 5)

        p.SetSizer(vs)


if __name__ == '__main__':
    app = wx.App(0)
    dia = Dialog(None, -1)
    app.SetTopWindow(dia)
    dia.Show()
    app.MainLoop()


