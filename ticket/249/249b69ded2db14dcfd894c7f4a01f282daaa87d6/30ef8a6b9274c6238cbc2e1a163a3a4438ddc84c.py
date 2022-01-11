#!/usr/bin/env python
# -*- coding: utf-8 -*-

#-Imports.--------------------------------------------------------------------
#--Python Imports.
import os
import sys

#--wxPython Imports.
import wx
import wx.lib.agw.aui as aui
import wx.stc as stc

# Confirmed on MSW XP Pro SP3, so far.
# Need to recheck on linux also, as it probably is there also...

TextCtrl_JitterBug_Cause = r"""

s.SetSTCFocus(True)

^ see this line in the code. ^

Notice the all textctrl carets positions go wacky
until each STC has gained focus.

http://trac.wxwidgets.org/ticket/16217

"""

class MyAuiNotebook(aui.AuiNotebook):
    def __init__(self, parent, id=wx.ID_ANY, pos=wx.DefaultPosition,
                 size=wx.DefaultSize,
                 style=0
                       # | wx.BORDER_SUNKEN # <--- Another BUG. unknown border style. WTF.
                       # http://trac.wxwidgets.org/ticket/16248
                 ,
                 agwStyle=aui.AUI_NB_DEFAULT_STYLE,
                 name='auinotebook'
                 ):
        aui.AuiNotebook.__init__(self, parent, id, pos, size, style, agwStyle, name)

        for i in range(0, 10):
            s = stc.StyledTextCtrl(self, -1)
            s.SetText('%s' % TextCtrl_JitterBug_Cause)
            s.SetSTCFocus(True) # <--- This is what causes it.
            self.AddPage(s, 'page %s' % i)

        self.SetSelection(5)


class MyPanel(wx.Panel):
    def __init__(self, parent, id=wx.ID_ANY,
                 pos=wx.DefaultPosition, size=wx.DefaultSize,
                 style=wx.BORDER_SUNKEN, name='panel'):
        wx.Panel.__init__(self, parent, id, pos, size, style, name)

        self.nb = MyAuiNotebook(self)
        self.tc = wx.TextCtrl(self, -1, '01234567890TextCtrl_' * 3)

        vbSizer = wx.BoxSizer(wx.VERTICAL)
        vbSizer.Add(self.nb, 1, wx.EXPAND | wx.ALL, 5)
        vbSizer.Add(self.tc, 0, wx.EXPAND | wx.ALL, 5)
        self.SetSizer(vbSizer)


class MyFrame(wx.Frame):
    def __init__(self, parent, id=wx.ID_ANY, title=wx.EmptyString,
                 pos=wx.DefaultPosition, size=wx.DefaultSize,
                 style=wx.DEFAULT_FRAME_STYLE, name='frame'):
        wx.Frame.__init__(self, parent, id, title, pos, size, style, name)
        global gMainWin
        gMainWin = self
        panel = MyPanel(self)
        self.Bind(wx.EVT_CLOSE, self.OnDestroy)

        self.CreateStatusBar().SetStatusText('wxPython %s' % wx.version())

    def OnDestroy(self, event):
        self.Destroy()

class MyNameApp(wx.App):
    def OnInit(self):
        gMainWin = MyFrame(None)
        gMainWin.SetTitle('http://trac.wxwidgets.org/ticket/16248')
        self.SetTopWindow(gMainWin)
        gMainWin.Show()
        return True

if __name__ == '__main__':
    gApp = MyNameApp(redirect=False,
            filename=None,
            useBestVisual=False,
            clearSigInt=True)

    gApp.MainLoop()
