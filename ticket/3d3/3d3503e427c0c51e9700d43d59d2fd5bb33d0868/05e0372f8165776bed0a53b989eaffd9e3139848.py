#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
import wx

class Onglet(wx.Panel):
    def __init__(self, parent, page):
        panel = wx.Panel.__init__(self, parent, style = wx.TAB_TRAVERSAL)
        self.Bind(wx.EVT_PAINT, self.OnPaint)


    def OnPaint(self, event):
        self.dc = wx.PaintDC(self)
        self.dc.Clear()

        self.dc.SetDeviceOrigin(100, 100)

        #---------------------------------------------------------------
        # The problem :
        
        # self.dc.SetAxisOrientation(True, True)        # Wrong display : X direction OK but line too short in Y direction (almost 20 times storter than the X line)
        # self.dc.SetAxisOrientation(False, True)       # Wrong display : Lines are too short (both X and Y)
        self.dc.SetAxisOrientation(True, False)         # Display ok : Lines have the same length
        # self.dc.SetAxisOrientation(False, False)      # Wrong display : Y direction OK but line too short in X direction (almost 20 times storter than the Y line)
        #---------------------------------------------------------------

        self.dc.DrawLine(1, 1, 100, 1)   # set X line
        self.dc.DrawLine(1, 1, 1, 100)   # set Y line



class MainFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title="1", size=(400,400), pos=(100,100))
        p = wx.Panel(self)
        nb = wx.Notebook(p)
        page1 = Onglet(nb, 2)
        nb.AddPage(page1, "o")
        sizer = wx.BoxSizer()
        sizer.Add(nb, 1, wx.EXPAND)
        p.SetSizer(sizer)

if __name__ == "__main__":
    app = wx.App()
    MainFrame().Show()
    app.MainLoop()
