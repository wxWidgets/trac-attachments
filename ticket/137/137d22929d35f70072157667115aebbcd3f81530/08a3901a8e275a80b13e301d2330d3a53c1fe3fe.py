#!/usr/bin/env python

# Test blitting of a MemoryDC with maskcolor set.


import wx


WIDTH   = 400
HEIGHT  = 400

class BlitMaskTestWindow(wx.Window):
    def __init__(self, *args, **kwargs):
        wx.Window.__init__(self, *args, **kwargs)

        self.Bind(wx.EVT_PAINT, self.OnPaint)


    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        mask_color = "#00FF00"

        # Red Background
        dc.SetBackground(wx.Brush("#FF0000"))
        dc.Clear()

        dc.SetPen(wx.Pen("#000000", 2, wx.SOLID))
        dc.DrawLine(0, 0, WIDTH, HEIGHT)

        # Setup the memory DC
        # The mdc has green as a mask color
        buffer = wx.EmptyBitmap(WIDTH, HEIGHT)
        buffer.SetMaskColour(mask_color)

        mdc = wx.MemoryDC()
        mdc.SelectObject(buffer)

        mdc.SetBackground(wx.Brush(mask_color))
        mdc.Clear()

        mdc.DrawCircle(WIDTH/2, HEIGHT/2, 50)

        dc.Blit(0, 0, WIDTH, HEIGHT, mdc, 0, 0, useMask=True)


class BlitMaskTestFrame(wx.Frame):
    def __init__(self, *args, **kwargs):
        wx.Frame.__init__(self, *args, **kwargs)

        # A window where we will draw the base canvas
        self.win = BlitMaskTestWindow(self, size=(WIDTH, HEIGHT))

        vsizer = wx.BoxSizer(orient=wx.VERTICAL)
        vsizer.Add(self.win, 0, wx.SHAPED)
        self.SetSizer(vsizer)

        self.GetSizer().Fit(self)

        self.Center(wx.BOTH|wx.CENTER_ON_SCREEN)


class BlitMaskTestApp(wx.PySimpleApp):

    def OnInit(self):
        # We do not want a resizeable frame!
        framestyle = wx.DEFAULT_FRAME_STYLE & ~ (wx.RESIZE_BORDER | wx.MAXIMIZE_BOX)
        frametitle = "Blit Mask Test"
        frame = BlitMaskTestFrame(None, title=frametitle, style=framestyle)
        frame.Show()
        return True


if __name__ == "__main__":
    app = BlitMaskTestApp()
    app.MainLoop()

 	  	 
