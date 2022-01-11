"""
Demo an apparent bug in GraphicsContexts.

Demonstrating another apparent GraphicsContext bug:
Rotating a transform seems to move the origin.


Two graphics are drawn at (0,0), and only differ
by a gc.Rotate call.  Why aren't they superimposed?
"""

import sys, os
import wx

from util import *
from printout import Printable
from math import radians

def test_pattern(gc):
    """
    Make a little test pattern centered on (0, 0):
    """
    size = 4.0
    gc.DrawLines([(-size, -size), (size, size)])
    gc.DrawLines([(size, -size), (-size, size)])
    gc.DrawRectangle(-size/4.0, -size/4.0, size/2.0, size/2.0)

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

        # Scale up a bit, so we can see the effect:
        gc.Scale(10, 10)

        # Make our Origin (0, 0) at screen coords (200, 100)
        gc.Translate(20, 10)

        # Now some axes, to mark the origin:
        gc.SetPen(wx.Pen("#888888", 0.1))
        gc.DrawLines([(-20, 0), (20, 0)])
        gc.DrawLines([(0, -20), (0, 20)])

        # Do one version in red:
        gc.SetPen(wx.Pen("#FF5555", 0.1))
        test_pattern(gc)

        # Report the transform of (0,0)...
        print "(0,0) ==>", gc.GetTransform().TransformPoint(0, 0)

        # Then a 45-degree rotation
        gc.Rotate(radians(45))

        # And another pattern, in blue
        gc.SetPen(wx.Pen("#88AACC", 0.1))
        test_pattern(gc)

        # Report the transform of (0,0)...
        print "NOW (0,0) ==>", gc.GetTransform().TransformPoint(0, 0)

        # Then another 45-degree rotation
        gc.Rotate(radians(45))

        # And a third pattern, in green
        gc.SetPen(wx.Pen("#88DD88", 0.1))
        test_pattern(gc)

        # Report the transform of (0,0)...
        print "and NOW (0,0) ==>", gc.GetTransform().TransformPoint(0, 0)

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
