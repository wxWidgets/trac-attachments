#!/usr/bin/env python
# -*- coding: utf-8 -*-#

import wx
print wx.VERSION_STRING
import wx.lib.sized_controls as sc
        
       
########################################################################
class MainFrame(sc.SizedFrame):
    #----------------------------------------------------------------------
    def __init__(self, parent, **kwds):
        super(MainFrame, self).__init__(parent, wx.ID_ANY, **kwds)
        
        self.SetTitle("combobox background")
        
        self.createControls()

    def createControls(self):
        paneContent = self.GetContentsPane()
        
        cb1 = wx.ComboBox(paneContent, -1)

        cb2 = wx.ComboBox(paneContent, -1, style=wx.CB_READONLY)
        cb2.SetBackgroundColour("yellow")

        cb3 = wx.ComboBox(paneContent, -1)
        cb3.SetBackgroundColour("red")

if __name__ == '__main__':
    # we use the WIT for the app, it is a very powerfull tool to help debug
    # layout issues and many other things, run it and try ctrl-alt-i
    # for more detail check out the wiki:
    # http://wiki.wxpython.org/Widget%20Inspection%20Tool
    import wx.lib.mixins.inspection as WIT
    app = WIT.InspectableApp(redirect=False)

    frame = MainFrame(None)
    frame.Show()
    app.MainLoop()
        
        
    
    