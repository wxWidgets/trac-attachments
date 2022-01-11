"""
Demo an apparent bug in GraphicsContexts.

My understanding is that GraphicsContext.Scale(sx, sy)
should apply scale factors to the transform, leaving
the mapping of (0, 0) the same.  This little program
demonstrates that, at least under OSX, a call to Scale
seems to move the origin.

Two graphics are drawn at (0,0), and only differ
by a gc.Scale call.  Why aren't they superimposed?
"""

import sys, os
import wx

from util import *
from printout import Printable
from math import radians

class MyWindow(wx.Window):

    def __init__(self, parent):
        wx.Window.__init__(self, parent)
        self.SetBackgroundColour("#CCCCDD")

        # Setup painting:
        self.Bind(wx.EVT_PAINT, self.OnPaint)

    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        self.PrepareDC(dc)
        gc = wx.GraphicsContext.Create(dc)

        # Make our Origin (0, 0) at screen coords (200, 100)
        gc.Translate(200, 100)

        # Now some axes, to mark the origin:
        gc.SetPen(wx.Pen("#888888", 1))
        gc.DrawLines([(-200, 0), (200, 0)])
        gc.DrawLines([(0, -200), (0, 200)])

        # A little red X at the origin:
        gc.SetPen(wx.Pen("#FF5555", 1))
        gc.DrawLines([(-40, -40), (40, 40)])
        gc.DrawLines([(40, -40), (-40, 40)])
        gc.DrawEllipse(-10, -10, 20, 20)       # add a circle...

        # Report the transform of (0,0)...
        print "(0,0) ==>", gc.GetTransform().TransformPoint(0, 0)

        # Now scale up our dimensions... presumably holding (0, 0) stationary:
        gc.Scale(10, 10)

        # And a bigger blue X at the origin:
        gc.SetPen(wx.Pen("#88AACC", 0.11))
        gc.DrawLines([(-5, -5), (5, 5)])
        gc.DrawLines([(5, -5), (-5, 5)])

        gc.DrawEllipse(-1, -1, 2, 2)    # and a circle ... should line up.

        # Report the transform of (0,0)...
        print "NOW (0,0) ==>", gc.GetTransform().TransformPoint(0, 0)


class AppWindow(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None)
        self.gw = MyWindow(self)
        self.Show()

if __name__ == "__main__":
    app = wx.PySimpleApp()
    frame = AppWindow()
    app.MainLoop()
    app.Destroy()
