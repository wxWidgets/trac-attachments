#!/usr/bin/env python
# -*- coding: iso-8859-15 -*-


import  wx



class MyDC(wx.Window):
    def __init__(self, parent):
        wx.Window.__init__(self, parent)
        self.string = 'This is a Teststring'
        self.nativeFontInfoString = "0;10;0;0;0;400;0;0;0;0;143;0;0;0;MS Shell Dlg 2"
        
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        
    def OnPaint(self, evt):
        dc = wx.PaintDC(self)
        dc.SetBackgroundMode(wx.SOLID)
        dc.SetBrush(wx.Brush(wx.WHITE, wx.SOLID))
        fn = wx.FontFromNativeInfoString(self.nativeFontInfoString)
        fn.SetPointSize(fn.GetPointSize()) # without setting the PointSize again, the font size is false
        dc.SetFont(fn)
        dc.DrawText(self.string, 10,10)
        

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        win = MyDC(self)

#---------------------------------------------------------------------------

if __name__ == '__main__':
    app = wx.App(0)
    wx.InitAllImageHandlers()
    frame = TestFrame( )
    app.SetTopWindow(frame)
    frame.Show()
    app.MainLoop()