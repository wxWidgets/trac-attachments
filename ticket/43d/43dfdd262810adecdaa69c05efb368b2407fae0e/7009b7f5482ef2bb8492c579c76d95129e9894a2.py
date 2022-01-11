#!/usr/bin/env python

import wx

class MyPanel(wx.Panel):
    def __init__(self, parent, offset):
        wx.Panel.__init__(self, parent)
        self.offset = offset
        self.Bind(wx.EVT_PAINT, self.OnPaint)

    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        gc = wx.GraphicsContext.Create(dc)
        w, h = self.GetSize()
        gc.SetPen(wx.Pen('black', 1))
        gc.StrokeLine(0, h/2 + self.offset, w, h/2 + self.offset)
        gc.StrokeLine(w/2 + self.offset, 0, w/2 + self.offset, h)

class MainWindow(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, wx.ID_ANY, 'Layout Test')
        sizer = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(sizer)
        panel1 = MyPanel(self, 0.0)
        sizer.Add(panel1)
        panel2 = MyPanel(self, 0.5)
        sizer.Add(panel2)
        self.Show(True)

app = wx.PySimpleApp()
frame = MainWindow()
app.MainLoop()
