#!/usr/bin/env python
# -*- coding: utf-8 -*-

#-Imports.---------------------------------------------------------------------
#--Python Imports.
import os
import sys

#--wxPython Imports.
import wx
import wx.lib.agw.aui as aui
import wx.stc as stc

the_traceback = r"""
# Tested on wxPython 3.0.1.0.b20140104 msw (classic)
# Adding standard border styles to the AuiNotebook style param causes this.

Microsoft Windows XP [Version 5.1.2600]
(C) Copyright 1985-2001 Microsoft Corp.

C:\Documents and Settings\XP\Desktop>testCaretBug.py
Traceback (most recent call last):
  File "C:\Documents and Settings\XP\Desktop\testCaretBug.py", line 79, in <module>
    clearSigInt=True)
  File "C:\Python27\lib\site-packages\wx-3.0-msw\wx\_core.py", line 8631, in __init__
    self._BootstrapApp()
  File "C:\Python27\lib\site-packages\wx-3.0-msw\wx\_core.py", line 8196, in _BootstrapApp
    return _core_.PyApp__BootstrapApp(*args, **kwargs)
  File "C:\Documents and Settings\XP\Desktop\testCaretBug.py", line 69, in OnInit
    gMainWin = MyNameFrame(None)
  File "C:\Documents and Settings\XP\Desktop\testCaretBug.py", line 59, in __init__
    panel = MyNamePanel(self)
  File "C:\Documents and Settings\XP\Desktop\testCaretBug.py", line 43, in __init__
    self.nb = MyAuiNotebook(self)
  File "C:\Documents and Settings\XP\Desktop\testCaretBug.py", line 27, in __init__
    aui.AuiNotebook.__init__(self, parent, id, pos, size, style, agwStyle, name)

  File "C:\Python27\lib\site-packages\wx-3.0-msw\wx\lib\agw\aui\auibook.py", line 2887, in __init__
    wx.PyPanel.__init__(self, parent, id, pos, size, style|wx.BORDER_NONE|wx.TAB_TRAVERSAL, name=name)
  File "C:\Python27\lib\site-packages\wx-3.0-msw\wx\_windows.py", line 4317, in __init__
    _windows_.PyPanel_swiginit(self,_windows_.new_PyPanel(*args, **kwargs))
wx._core.PyAssertionError: C++ assertion "Assert failure" failed at ..\..\src\msw\window.cpp(1472) in wxWindow::MSWGetStyle(): unknown border style

"""

class MyAuiNotebook(aui.AuiNotebook):
    def __init__(self, parent, id=wx.ID_ANY, pos=wx.DefaultPosition,
                 size=wx.DefaultSize,
                 style=0
                       # | wx.BORDER_SUNKEN # <-- The BUG. unknown border style. WTF.
                 ,
                 agwStyle=aui.AUI_NB_DEFAULT_STYLE,
                 name='auinotebook'
                 ):
        aui.AuiNotebook.__init__(self, parent, id, pos, size, style, agwStyle, name)

        for i in range(0, 10):
            s = stc.StyledTextCtrl(self, -1)
            s.SetText('%s' % the_traceback)
            self.AddPage(s, 'page %s' % i)

        self.SetSelection(5)


class MyNamePanel(wx.Panel):
    def __init__(self, parent, id=wx.ID_ANY,
                 pos=wx.DefaultPosition, size=wx.DefaultSize,
                 style=wx.BORDER_SUNKEN, name='panel'):
        wx.Panel.__init__(self, parent, id, pos, size, style, name)

        self.nb = MyAuiNotebook(self)
        self.tc = wx.TextCtrl(self, -1, '01234567890' * 3)

        vbSizer = wx.BoxSizer(wx.VERTICAL)
        vbSizer.Add(self.nb, 1, wx.EXPAND | wx.ALL, 5)
        vbSizer.Add(self.tc, 0, wx.EXPAND | wx.ALL, 5)
        self.SetSizer(vbSizer)


class MyNameFrame(wx.Frame):
    def __init__(self, parent, id=wx.ID_ANY, title=wx.EmptyString,
                 pos=wx.DefaultPosition, size=wx.DefaultSize,
                 style=wx.DEFAULT_FRAME_STYLE, name='frame'):
        wx.Frame.__init__(self, parent, id, title, pos, size, style, name)
        global gMainWin
        gMainWin = self
        panel = MyNamePanel(self)
        self.Bind(wx.EVT_CLOSE, self.OnDestroy)

        self.CreateStatusBar().SetStatusText('wxPython %s' % wx.version())

    def OnDestroy(self, event):
        self.Destroy()

class MyNameApp(wx.App):
    def OnInit(self):
        self.SetClassName('MyNameApp')
        self.SetAppName('MyNameApp')
        gMainWin = MyNameFrame(None)
        gMainWin.SetTitle('MyNameFrame')
        self.SetTopWindow(gMainWin)
        gMainWin.Show()
        return True

if __name__ == '__main__':
    gApp = MyNameApp(redirect=False,
            filename=None,
            useBestVisual=False,
            clearSigInt=True)

    gApp.MainLoop()
