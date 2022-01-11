import wx

def draw_me_a_bitmap(drawBmp):
    dc = wx.MemoryDC()
    banner_bmp = wx.EmptyBitmap(250, 50)
    dc.SelectObject(banner_bmp)
    dc.SetBackground(wx.Brush(wx.Colour(181,211,234)))
    dc.Clear()
    if drawBmp:
        brand_bmp = wx.Bitmap('day_on.png')
        dc.DrawBitmap(brand_bmp,18,9)
    dc.SelectObject(wx.NullBitmap)
    return banner_bmp

class Frame(wx.Frame):
    def __init__(self,parent):
        wx.Frame.__init__(self,parent)
        panel = wx.Panel(self)
	sizer = wx.BoxSizer(wx.VERTICAL)
	bmp = wx.StaticBitmap(panel,-1, draw_me_a_bitmap(False))
        sizer.Add(bmp, 0, wx.ALL, 5)
        bmp = wx.StaticBitmap(panel, -1, draw_me_a_bitmap(True))
	sizer.Add(bmp, 0, wx.ALL, 5)
	panel.SetSizer(sizer)
        self.Show()

if __name__ == "__main__":
    app= wx.App(False)
    Frame(None)
    app.MainLoop()
