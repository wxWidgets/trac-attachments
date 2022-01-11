#!/usr/bin/python

import wx

class Test(wx.App):
    def OnInit(self):
        txt =   'Y'
        dc  =   wx.MemoryDC()

        for sz in range(1, 100) :
            f                   =   wx.Font(sz, wx.FONTFAMILY_ROMAN, wx.FONTWEIGHT_NORMAL, wx.FONTSTYLE_NORMAL, False, "")
            width,height,desc,x =   dc.GetFullTextExtent(txt, font = f)
            print "-", sz, width, height
            dc.SetFont(f)
            width,height        =   dc.GetTextExtent(txt)
            print " ", sz, width, height

        return(True)

app=Test(0)
app.MainLoop()


