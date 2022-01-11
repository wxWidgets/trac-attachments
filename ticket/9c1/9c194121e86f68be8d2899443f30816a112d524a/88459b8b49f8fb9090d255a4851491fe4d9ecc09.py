# -*- coding: utf-8 -*-
# File: test-DC-drawBitmap.py
# Author: Vladiuz7

import os
import sys
import wx
from wx import ImageFromStream, BitmapFromImage, EmptyIcon
import cStringIO, zlib

RC_SCALE = 24

def getData():
    return zlib.decompress(
"x\xda\xeb\x0c\xf0s\xe7\xe5\x92\xe2b``\xe0\xf5\xf4p\t\x02\xd2\x1c \xcc\xc1\
\x04$\xbds5\xef\x00)\xe6b'\xcf\x10\x0e\x0e\x8e\xdb\x0f\xfd\x1f\x00\xb9Q\x9e.\
\x8e!\x1c3}\xfb\x0e\n\xb28r01\xaa\xf7\x9d\xb4\xd7\x11\x16|\x97x\xf5\xce\xb7\
\xe9l\xa9B\x0c\x0c9\xe5\xdf\xcfL\x98R\xf2\xe1\xe0\xb6\xdcI\x0c\xff\x18O\xaaX\
Oxr\xa3\xae*t\xad\xe2\xcb\x92\xedoUBK\xdfO\xddro\xe6L^\x86\x90\xabr\x0c\nu\
\x15\xf2L\x16\xb7}?\xb9M\x93W]`\xb1Md\xdd\x047\xa0-\x0c\x9e\xae~.\xeb\x9c\
\x12\x9a\x00\xc5\x816\xbc" )

def getBitmap():
    return BitmapFromImage(getImage())

def getImage():
    stream = cStringIO.StringIO(getData())
    return ImageFromStream(stream)

class rcMainFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, wx.NewId(), "test", pos = wx.DefaultPosition, size = (700,500))
        self.Bind(wx.EVT_PAINT, self.onPaint)
        self.Bind(wx.EVT_ERASE_BACKGROUND, self.onEraseBG)
        self.bmp = getBitmap()
    def onPaint(self, evt):
        self.DoDraw(wx.BufferedPaintDC(self))
    def onEraseBG(self, evt):
        dc = wx.ClientDC(self)
        self.DoDraw(wx.BufferedDC(dc))
    def DoDraw(self, dc):
        dc.Clear()
        dc.SetPen(wx.Pen("black", 1))
        dc.DrawRectangle(RC_SCALE-1,RC_SCALE-1,RC_SCALE*8+2,RC_SCALE*8+2)
        dc.SetUserScale(RC_SCALE, RC_SCALE)
        dc.DrawBitmap(self.bmp,1,1)
        dc.SetUserScale(1, 1)
class rcApp(wx.App):
    def __init__(self):
        wx.App.__init__(self)
        self.frame = rcMainFrame(None)
        self.frame.Show(True)
        self.SetTopWindow(self.frame)

if __name__ == '__main__':
    app = rcApp()
    app.MainLoop()

