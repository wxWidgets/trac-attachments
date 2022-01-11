#!/usr/bin/env python

# A test for the semantic of wx.DC.Blit()
# On different platforms the Blit operation behaves in different ways when the
# source and destination DCs have different coordinate systems.


# Another question:
# Is the wx.DC.SetAxisOrientation documentation right? I read the following:
#
# SetAxisOrientation(self, xLeftRight, yBottomUp)
#
#   Sets the x and y axis orientation (i.e., the direction from lowest to
#   highest values on the axis). The default orientation is the natural
#   orientation, e.g. x axis from left to right and y axis from bottom up.
#
#    Parameters:
#       xLeftRight
#           (type=bool)
#
#       yBottomUp
#           (type=bool)
#
# --
# Hemm, but it seems that the default orientation is with y from top down...
# Well, this clarification is on the TODO list, as seen on:
# http://www.wxwidgets.org/wiki/index.php/Development:_Todo_List#Documentation


import wx


BASE_CANVAS_WIDTH   = 400
BASE_CANVAS_HEIGHT  = 400

SUBCANVAS_ORIGX = 100
SUBCANVAS_ORIGY = 100

SUBCANVAS_WIDTH  = 200 
SUBCANVAS_HEIGHT = 200


class SubCanvasDC(wx.MemoryDC):
    def __init__(self, size):
        wx.MemoryDC.__init__(self)

        width,height = size
        self.buffer = wx.EmptyBitmap(width, height)
        self.SelectObject(self.buffer)

        # We change the coordinate system, should I change the Device Origin
        # explicitly if I want 0,0 to be in the lower-left corner?
        self.SetDeviceOrigin(0, height-1)
        self.SetAxisOrientation(True, True)

        self.SetBackground(wx.Brush("#FF0000"))
        self.Clear()


class BaseCanvasWindow(wx.Window):
    def __init__(self, *args, **kwargs):
        wx.Window.__init__(self, *args, **kwargs)

        self.width, self.height = self.GetSize()

        self.contentwidth = SUBCANVAS_WIDTH
        self.contentheight = SUBCANVAS_HEIGHT

        self.contentorigx = SUBCANVAS_ORIGX
        self.contentorigy = SUBCANVAS_ORIGY

        self.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
        self.SetBackgroundColour("#FFFFFF")
        self.black_pen = wx.Pen("#000000", 1, wx.SOLID)

        self.position = 0,0

        self.content_dc = SubCanvasDC( (self.contentwidth, self.contentheight) )

        self.Bind(wx.EVT_PAINT, self.OnPaint)


    def OnPaint(self, event):
        dc = wx.BufferedPaintDC(self)
        self.DrawCanvas(dc)


    def DrawCanvas(self, dc):
        dc.SetBackground(wx.Brush(self.GetBackgroundColour()))
        dc.Clear()

        # I would expect the line drawn accordingly to the coordinate
        # system of self.content_dc
        self.content_dc.DrawLine(10, 10, 50, 100)

        # The first call is how I think the blit should be invoked, the second
        # is how I managed to make it work on only wxGTK (hence in a non
        # portable way).  Does wx.DC.Blit() take into account that the source
        # and destination DC can have different coordinate systems?
        # How is the semantic defined in this case?

        # On wxMSW _this_ call blits the correct region to the base canvas,
        # BUT it completely ignores the Axis Orientation of the subcanvas...
        # (the latter gets drawn following the Base Canvas orientation...)
        #dc.Blit(self.contentorigx, self.contentorigy, self.contentwidth, self.contentheight,
        #        self.content_dc, 0, 0)

        # On wxGTK with _this_ call I get the region and the orietation blitted as
        # desired, BUT the call, _is_ weird, look at the last argument, used
        # to compensate the hack in the SubCanvasDC class.
        dc.Blit(self.contentorigx, self.contentorigy, self.contentwidth, self.contentheight,
                self.content_dc, 0, self.contentheight-1)

        dc.DrawLine(10, 10, 50, 100)

        x,y = self.position
        x,y = self.SubCanvasToWinCoord(x,y)
        dc.CrossHair(x, y)


    def WinToSubCanvasCoord(self, x, y):
        x -= SUBCANVAS_ORIGX
        y += SUBCANVAS_ORIGY
        return x, y

    def SubCanvasToWinCoord(self, x, y):
        x += SUBCANVAS_ORIGX
        y -= SUBCANVAS_ORIGY + SUBCANVAS_HEIGHT - 1
        y *= -1
        return x, y


class BlitTestFrame(wx.Frame):
    def __init__(self, *args, **kwargs):
        wx.Frame.__init__(self, *args, **kwargs)

        # A window where we will draw the base canvas
        self.win = BaseCanvasWindow(self, size=(BASE_CANVAS_WIDTH, BASE_CANVAS_HEIGHT))
        self.win.SetFocus()

        self.win.Bind(wx.EVT_MOTION, self.OnMotion)

        vsizer = wx.BoxSizer(orient=wx.VERTICAL)
        vsizer.Add(self.win, 0, wx.SHAPED)
        self.SetSizer(vsizer)

        sb = self.CreateStatusBar(style=0)
        sb.SetFieldsCount(2)

        self.GetSizer().Fit(self)

        self.Center(wx.BOTH|wx.CENTER_ON_SCREEN)


    def OnMotion(self, event):
        x,y = event.GetLogicalPosition(self.win.content_dc)

        x,y = self.win.WinToSubCanvasCoord(x, y)
        self.win.position = x,y
        self.win.Refresh()

        self.SetStatusText("Mouse Position %3d,%3d" % (x,y), 1)


class BlitTestApp(wx.PySimpleApp):

    def OnInit(self):
        # We do not want a resizeable frame!
        framestyle = wx.DEFAULT_FRAME_STYLE & ~ (wx.RESIZE_BORDER | wx.MAXIMIZE_BOX)
        frametitle = "Blit Test"
        frame = BlitTestFrame(None, title=frametitle, style=framestyle)
        frame.Show()
        return 1


if __name__ == "__main__":
    app = BlitTestApp()
    app.MainLoop()

 	  	 
