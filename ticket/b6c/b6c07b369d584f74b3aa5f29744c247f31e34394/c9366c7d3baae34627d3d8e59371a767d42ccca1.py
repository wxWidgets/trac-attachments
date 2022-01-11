#!/usr/bin/python2

import wx

# Select different test modes
# 1: draw buffered pattern in background
#      - works fine on GTK
#      - unexpected black background on MSW
# 2: draw buffered pattern in foreground
#      - works fine on GTK & MSW
# 3: draw pattern directly in background
#      - works fine on GTK
#      - unexpected black background on MSW
# 4: draw pattern directly in foreground
#      - works fine on GTK & MSW
mode = 1


class DrawBackground(wx.Frame):

    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, size=(400, 100))

        self.reInitBuffer = True
        self.InitBuffer()

        if mode == 3 or mode == 4:
            self.Bind(wx.EVT_PAINT, self.OnPaintDirect)
        else:
            self.Bind(wx.EVT_PAINT, self.OnPaintBuffered)
            self.Bind(wx.EVT_SIZE, self.OnSize)
            self.Bind(wx.EVT_IDLE, self.OnIdle)

        self.Centre()
        self.Show(True)

    def OnPaintBuffered(self, event):
        wx.BufferedPaintDC(self, self.buffer)

    def OnPaintDirect(self, event):
        dc = wx.PaintDC(self)
        brush = wx.Brush(wx.BLACK, wx.FDIAGONAL_HATCH)

        # fill background first
        dc.SetBackground(wx.Brush(wx.LIGHT_GREY))
        dc.Clear()

        if mode == 3:
            # draw hatched lines in background
            dc.SetBackground(brush)
            dc.Clear()
        elif mode == 4:
            # draw hatched lines in foreground
            dc.BeginDrawing()
            dc.SetBrush(brush)
            w, h = self.GetClientSize()
            dc.DrawRectangle(0, 0, w, h)
            dc.EndDrawing()

    def OnSize(self, event):
        self.reInitBuffer = True

    def OnIdle(self, event):
        if self.reInitBuffer:
            self.InitBuffer()
            self.Refresh(False)

    def InitBuffer(self):
        size = self.GetClientSize()
        self.buffer = wx.EmptyBitmap(size.width, size.height)
        brush = wx.Brush(wx.BLACK, wx.FDIAGONAL_HATCH)

        dc = wx.BufferedDC(None, self.buffer)

        # fill background first
        dc.SetBackground(wx.Brush(wx.LIGHT_GREY))
        dc.Clear()

        if mode == 1:
            # draw hatched lines in background
            dc.SetBackground(brush)
            dc.Clear()

        elif mode == 2:
            # draw hatched lines in foreground
            dc.SetBrush(brush)
            dc.DrawRectangle(0, 0, size.width, size.height)

        self.reInitBuffer = False

app = wx.App()
title = 'Bug on %s' % wx.Platform
if mode == 1:
    title += ' - buffer bg'
elif mode == 2:
    title += ' - buffer fg'
elif mode == 3:
    title += ' - direct bg'
else:
    title += ' - direct fg'

DrawBackground(None, -1, title)
app.MainLoop()