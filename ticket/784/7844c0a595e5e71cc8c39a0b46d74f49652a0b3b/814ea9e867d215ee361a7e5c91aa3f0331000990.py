#!/usr/bin/env python

import os

import wx
from wx.lib.filebrowsebutton import *

class MyFrame(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, wx.DefaultPosition, wx.DefaultSize)
        panel = wx.Panel(self)
        sizer = wx.BoxSizer(wx.VERTICAL)
        panel.SetSizer(sizer)
        initial = os.getcwd()
        c = FileBrowseButton(self, -1, size=(-1, -1),
                             labelText = 'Non-existent directory:',
                             startDirectory=initial)
        c.SetValue("/this/doesn't/exist")
        sizer.Add(c, 1, wx.EXPAND)
        sizer.Fit(panel)
        panel.Layout()

class MyApp(wx.App):
    def OnInit(self):
        frame = MyFrame(None, -1, 'File Browse Button')
        frame.Show(True)
        frame.Centre()
        return True

if __name__ == '__main__':
    app = MyApp(0)
    app.MainLoop()

 	  	 
