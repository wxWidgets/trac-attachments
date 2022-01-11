#!/usr/bin/env python
"""
EVT_TOOL_ENTER and EVT_TOOL_RCLICKED don't seem to work on WXMAC
"""

import wx

class MainFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, "test")
        self.CreateStatusBar()
        self.ctrl = wx.TextCtrl(self, -1, style=wx.TE_MULTILINE|wx.WANTS_CHARS|wx.TE_RICH2)

        self.setToolbar()
        self.Show()

    def setToolbar(self):
        self.toolbar = self.CreateToolBar(wx.TB_HORIZONTAL)
        tsize = (16, 16)
        self.toolbar.SetToolBitmapSize(tsize)
        
        id = wx.NewId()
        bmp =  wx.ArtProvider.GetBitmap(wx.ART_NEW, wx.ART_TOOLBAR, tsize)
        self.toolbar.AddLabelTool(id, "New", bmp, shortHelp="New", longHelp="Long help for 'New'")
        
        id = wx.NewId()
        bmp =  wx.ArtProvider.GetBitmap(wx.ART_FILE_OPEN, wx.ART_TOOLBAR, tsize)
        self.toolbar.AddLabelTool(id, "Open", bmp, shortHelp="Open", longHelp="Long help for 'Open'")
        
        self.toolbar.Bind(wx.EVT_TOOL, self.OnTool)
        self.toolbar.Bind(wx.EVT_TOOL_ENTER, self.OnToolEnter)
        self.toolbar.Bind(wx.EVT_TOOL_RCLICKED, self.OnToolContext)
        
        self.toolbar.Realize()
        
    def OnTool(self, evt):
        print("in OnTool: id=%s" % evt.GetId())
        
    def OnToolEnter(self, evt):
        print("in OnToolEnter: id=%s" % evt.GetId())
        
    def OnToolContext(self, evt):
        print("in OnToolContext: id=%s" % evt.GetId())
        
app = wx.PySimpleApp(redirect=False)
frame = MainFrame()
app.MainLoop()
