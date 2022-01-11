#!/bin/python

import sys, os, traceback

import wx, wx.stc


class MainFrame(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, size = (300, 200),
                style=wx.DEFAULT_FRAME_STYLE)

        mainsizer = wx.BoxSizer(wx.HORIZONTAL)
        sctComp = wx.stc.StyledTextCtrl(self, -1,
                style=wx.WANTS_CHARS | wx.TE_PROCESS_ENTER)
                
        sctComp.AddText(u"wxPython version %s.%s.%s" %
                (wx.MAJOR_VERSION, wx.MINOR_VERSION,
                wx.RELEASE_NUMBER))

        mainsizer.Add(sctComp, 1, wx.ALL | wx.EXPAND, 0)
        
        self.SetSizer(mainsizer)
        self.Layout()



class MainApp(wx.App):   
    def OnInit(self):
        mainFrame = MainFrame(None, -1, "Scintilla Test")
        self.SetTopWindow(mainFrame)
        mainFrame.Show()
        return True



app = MainApp(0)
app.MainLoop()

