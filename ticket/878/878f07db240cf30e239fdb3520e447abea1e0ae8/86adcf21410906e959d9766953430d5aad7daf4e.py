"""
A tiny test application for GraphicsContext

Cool!  It seems to supply most of the features i've been
missing in wxPython!

NOT WORKING: printing.
 - We seem to get an inscrutible error on GraphicsContext.Create(dc),
   when dc is a printer DC.
 - Print 

"""

import sys, os
import wx

from util import *
from printout import Printable

################################################################################
# 
################################################################################

def ORBody(gc):
    """
    Returns a path for an OR-gate body, centered on (0, 0) and scaled
    to extend from -50 < x < 50 and -20 < y < 20.
    """
    path = gc.CreatePath()

    #x1, x2, x3 = 25, 10, 25
    #xcback = 10
    #y1, y2 = 20, 20

    x1, x2, x3 = 50, 30, 50
    xcback = 20
    y1, y2 = 40, 45

    
    path.MoveToPoint(-x1, y1)                         # lower left corner
    path.AddQuadCurveToPoint(-x1+xcback, 0, -x1, -y1)    # back curve to UL

    path.AddQuadCurveToPoint(x2, -y2, x3, 0)           # top curve

    path.MoveToPoint(-x1, y1)
    path.AddQuadCurveToPoint(x2, y2, x3, 0)


    return path

def ANDBody(gc):
    """
    Returns a path for an AND-gate body, centered on (0, 0) and scaled
    to extend from -50 < x < 50 and -20 < y < 20.
    """
    path = gc.CreatePath()
    x1, x2, x3 = 50, 0, 50
    xcback = 20
    y1, y2 = 40, 40

    path.MoveToPoint(-x1, y1)                         # lower left corner
    path.AddLineToPoint(-x1, -y1)
    path.AddLineToPoint(x2, -y1)
    path.AddCurveToPoint(x2+50, -y1, x3, 0, x3, 0)
    path.AddCurveToPoint(x3, 0, x2+50, y1, x2, y1)
    path.AddLineToPoint(-x1, y1)
    
    return path


    path.AddQuadCurveToPoint(-x1+xcback, 0, -x1, -y1)    # back curve to UL

    path.AddQuadCurveToPoint(x2, -y2, x3, 0)           # top curve

    path.MoveToPoint(-x1, y1)
    path.AddQuadCurveToPoint(x2, y2, x3, 0)

    return path


BASE  = 80.0    # sizes used in shapes drawn below
BASE2 = BASE/2
BASE4 = BASE/4
BASE8 = BASE/8

class GridWindow(wx.ScrolledWindow):

    def __init__(self, parent,
                 msg = None,
                 vsize = (1000, 1000),
                 pos = wx.DefaultPosition,
                 size = wx.DefaultSize):

        self.parent = parent
        self.msg_handler = msg
        self.vsize = vsize

        wx.ScrolledWindow.__init__(self,
                                   parent,                 # parent
                                   id=-1,                  # id
                                   size = size,
                                   style = wx.BORDER+wx.HSCROLL+wx.VSCROLL,
                                   name = "GridWindow")

        self.SetScrollbars(1, 1,                   # pixels per unit
                           vsize[0], vsize[1],      # size in units
                           xPos=0, yPos=0,          # initial position
                           noRefresh = False)
        self.SetVirtualSize(vsize)
        self.SetScrollRate(1, 1)
        self.Scroll(100, 0)

        self.SetBackgroundColour("#CCCCDD")

        # Setup painting:
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_SIZE, self.OnSize)
        self.Bind(wx.EVT_SCROLL, self.OnScroll)

    def msg(self, m):
        if self.msg_handler: self.msg_handler(m)

    def OnScroll(self, event):
        #print "OnScroll called..."
        #self.OnPaint(event)
        pass

    def PaintGrid(self, dc):
        grid_size = 10
        xmax, ymax = self.vsize

        pen = wx.Pen("#DDDDDD", 1)
        dc.SetPen(pen)

        for x in range(0, self.vsize[0], grid_size):
            dc.DrawLine(x, 0, x, ymax)

        for y in range(0, self.vsize[1], grid_size):
            dc.DrawLine(0, y, xmax, y)

    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        self.DoPrepareDC(dc)
        self.DoDrawing(dc)
        return

        self.PaintGrid(dc)
        
        try:
            gc = wx.GraphicsContext.Create(dc)
        except NotImplementedError:
            dc.DrawText("This build of wxPython does not support the wx.GraphicsContext "
                        "family of classes.",
                        25, 25)
            return

        # Must set up a font:
        font = wx.SystemSettings.GetFont(wx.SYS_DEFAULT_GUI_FONT)
        font.SetWeight(wx.BOLD)
        gc.SetFont(font)

        self.ReDraw(gc)

    def DoDrawing(self, dc):
        """
        Draw the contents of this frame in the supplied DeviceContext.

        Directly draws the Grid in the DC; then creates a GraphicsContext
        and calls self.ReDraw(gc) to paint all the other stuff.
        """

        self.PaintGrid(dc)
        self.DoPrepareDC(dc)
        print "DC =", dc

        try:
            gc = wx.GraphicsContext.Create(dc)
        except NotImplementedError:
            dc.DrawText("This build of wxPython does not support the wx.GraphicsContext "
                        "family of classes.",
                        25, 25)
            return
        return

        # Must set up a font:
        font = wx.SystemSettings.GetFont(wx.SYS_DEFAULT_GUI_FONT)
        font.SetWeight(wx.BOLD)
        gc.SetFont(font)

        self.ReDraw(gc)


    def OnSize(self, dc):
        pass

    def MyCrosshair(self, dc, x, y):
        dc.DrawLines([(x,0), (x, self.vsize[0])])
        dc.DrawLines([(0, y), (self.vsize[1], y)])

    def ReDraw(self, gc):
        """
        Draws all the "serious stuff" in the supplied GraphicsContext, gc.
        """

        # make a path that contains a circle and some lines, centered at 0,0
        path = gc.CreatePath()
        path.AddCircle(0, 0, BASE2)
        path.MoveToPoint(0, -BASE2)
        path.AddLineToPoint(0, BASE2)
        path.MoveToPoint(-BASE2, 0)
        path.AddLineToPoint(BASE2, 0)
        path.CloseSubpath()

        path.MoveToPoint(BASE4, BASE4)
        path.AddLineToPoint(-BASE4, BASE4)
        path.AddLineToPoint(-BASE4 + BASE8, BASE4 - BASE8)
        
        path.AddRectangle(-BASE4, -BASE4/2, BASE2, BASE4)

        # Now use that path to demonstrate various capbilites of the grpahics context
        gc.PushState()             # save current translation/scale/other state 
        gc.Translate(60, 75)       # reposition the context origin

        gc.SetPen(wx.Pen("navy", 1))
        gc.SetBrush(wx.Brush(wx.Color(220, 220, 250, 128)))

        # show the difference between stroking, filling and drawing
        for label, PathFunc in [("StrokePath", gc.StrokePath),
                                ("FillPath",   gc.FillPath),
                                ("DrawPath",   gc.DrawPath)]:
            w, h = gc.GetTextExtent(label)
            
            gc.DrawText(label, -w/2, -BASE2-h-4)
            PathFunc(path)
            gc.Translate(2*BASE, 0)

        gc.PopState()
        gc.PushState()
        gc.Translate(380, 200)       # reposition the context origin

        # Try flipping:
        gc.Scale(-1.0, 1.0)

        for label, PathFunc in [("StrokePath", gc.StrokePath),
                                ("FillPath",   gc.FillPath),
                                ("DrawPath",   gc.DrawPath)]:
            w, h = gc.GetTextExtent(label)
            
            gc.DrawText(label, -w/2, -BASE2-h-4)
            PathFunc(path)
            gc.Translate(2*BASE, 0)
        gc.PopState()

        # Next, try some Gate bodies.  First, an OR body:
        gc.PushState()
        gc.Translate(100, 350)       # reposition the context origin

        gc.DrawLines(((-100, 0), (100, 0)))
        gc.DrawLines(((0, -100), (0, 100)))

        orbody = ORBody(gc)
        gc.DrawPath(orbody)
        gc.PopState()

        # Then, an AND body:
        gc.PushState()
        gc.Translate(350, 350)       # reposition the context origin

        gc.DrawLines(((-100, 0), (100, 0)))
        gc.DrawLines(((0, -100), (0, 100)))

        andbody = ANDBody(gc)
        gc.DrawPath(andbody)
        gc.PopState()

class AppWindow(wx.Frame, Printable):
    """
    Try making ScrolledWindows work.
    """

    def __init__(self):

        wx.Frame.__init__(self,
                          None,                 # parent
                          -1,                    # id
                          title="AppWindow",
                          pos=(700, 200),
                          size=(500, 500))

        self.toolbar = self.CreateToolBar()

        b = wx.Button(self.toolbar, -1, 'Page Setup')
        self.toolbar.AddControl(b)
        self.Bind(wx.EVT_BUTTON, self.PageSetup, b)
        b.SetDefault()

        b = wx.Button(self.toolbar, -1, 'Preview')
        self.toolbar.AddControl(b)
        self.Bind(wx.EVT_BUTTON, self.PrintPreview, b)
        b.SetDefault()

        b = wx.Button(self.toolbar, -1, 'Print')
        self.toolbar.AddControl(b)
        self.Bind(wx.EVT_BUTTON, self.PrintButton, b)
        b.SetDefault()

        self.toolbar.Realize()

        self.CreateStatusBar()
        self.msg('Hello.')

        self.gw = GridWindow(self,
                             msg = self.msg,
                             vsize = (1000, 1000),
                             pos=wx.DefaultPosition,
                             size = wx.DefaultSize)

        self.gw.SetScrollbars(1, 1, 1000, 1000)

        self.Refresh()
        self.Show()

        # setup printing:
        Printable.__init__(self, self.gw, (1000, 1000))


    def msg(self, m):
        self.SetStatusText(m)
        

if __name__ == "__main__":

    app = wx.PySimpleApp()
    frame = AppWindow()
    app.MainLoop()
    app.Destroy()
