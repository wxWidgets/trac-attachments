#!/bin/python

import sys, os, traceback

import wx


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
        metaDC = wx.MetaFileDC()
        
        metaDC.DrawCircle(10, 10, 5)

        metaFile = metaDC.Close()

        metaFile.SetClipboard(metaDC.MaxX(), metaDC.MaxY());
        
        print "Freeing metafile from MetaFileDC"       
        metaFile = None   # No problem
        print "Done"

        cb = wx.TheClipboard
        cb.Open()
        try:
            dataob = wx.MetafileDataObject()
    
            if cb.GetData(dataob):
                metaFile = dataob.GetMetafile()
        finally:
            cb.Close()

        print "\nFreeing metafile from clipboard"
        metaFile = None   # Memory leak error
        print "Done"

        return True



app = MainApp(0)
app.MainLoop()

