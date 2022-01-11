#!/usr/bin/env python
import wx

class MemoryDcDraw(wx.Panel):

    def __init__(self, parent):
        wx.Panel.__init__(self, parent)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(self.sizer)
        self.img_path = 'img.png'

        self.create_ui()
        self.make_transparent_and_draw_circle()

    def create_ui(self):
        self.scroll = wx.ScrolledWindow(self, style=wx.HSCROLL | wx.VSCROLL | wx.BORDER_SIMPLE)
        self.sizer.Add(self.scroll, 1, flag=wx.EXPAND)

        self.img = wx.Image(self.img_path, wx.BITMAP_TYPE_PNG)
        self.bitmap = wx.BitmapFromImage(self.img)
        self.staticbitmap = wx.StaticBitmap(self.scroll, wx.ID_ANY, self.bitmap)
        self.scroll.SetScrollbars(1, 1, self.bitmap.GetWidth(), self.bitmap.GetHeight())

    def make_transparent_and_draw_circle(self):
        self.bitmap.SaveFile("bitmap_in_make_func.png", wx.BITMAP_TYPE_PNG)
        dc = wx.MemoryDC(self.bitmap)
        dc.DrawCircle(100, 100, 50)
        dc.SelectObject(wx.NullBitmap)
        self.staticbitmap.SetBitmap(self.bitmap)


if __name__ == '__main__':
    app = wx.App(False)
    frame = wx.Frame(parent=None)
    MemoryDcDraw(frame)
    frame.Show()
    app.MainLoop()