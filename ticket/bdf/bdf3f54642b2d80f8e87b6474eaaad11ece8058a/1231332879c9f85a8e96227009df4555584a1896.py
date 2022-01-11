#!/usr/bin/env python

import wx

class MyDialog(wx.Dialog):
    def __init__(self,parent):
        wx.Dialog.__init__(self, parent, -1,"Demonstration of multiline wxTextEdit bug")
        
        entry = wx.TextCtrl(self,-1,"Enter text here", style=wx.TE_MULTILINE)
            
        mainSizer = wx.GridSizer(1, 1)
        mainSizer.Add(entry, 0, wx.ALL, 12)
        
        self.SetSizerAndFit(mainSizer)


if __name__ == "__main__":
        app = wx.PySimpleApp()
        frame = wx.Frame(None, -1, "Demonstration of multiline wxTextEdit bug")
        dlg = MyDialog(frame)
        dlg.ShowModal()

 	  	 
