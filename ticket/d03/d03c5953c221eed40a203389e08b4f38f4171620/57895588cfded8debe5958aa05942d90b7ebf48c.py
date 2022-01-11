import wx
from wx.lib.embeddedimage import PyEmbeddedImage

red_square = PyEmbeddedImage(
    "iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzOAAAAGXRFWHRTb2Z0d2FyZQBBZG9i"
    "ZSBJbWFnZVJlYWR5ccllPAAAAL1JREFUeNrclj0OwjAMhZ9TU7pxAlY6sHH/E/QMsHEAEBtS"
    "4roVRRb784ClSMniT89/sUyX8wPAHjwrft4qfX84jicexgz3622nAoG1BhHhcNy3O4duVKai"
    "xTRSaYo2EIggRFCaImv1H0IXi6ESFaVVXQSBqOinj7JCV1tmjpCQoyV0abOOywl9xAJ9/j6N"
    "g49mUkJ5MxV1mpCjFYSk0KVUXQRRd4YvSDs860DsI0OpTcQvL38PRDHrAjkLMACuhXkXo0Sv"
    "EAAAAABJRU5ErkJggg==")

def draw_me_a_bitmap(width,text,bitmap_on_top):
    brand_bmp= red_square.GetBitmap()
    padding= 18
    height= brand_bmp.GetHeight() + padding
    dc= wx.MemoryDC()
    banner_bmp= wx.EmptyBitmap(width,height)
    dc.SelectObject(banner_bmp)
    dc.GradientFillLinear(wx.Rect(0,0,width,height),(223,232,238),(181,211,234),wx.SOUTH)
    dc.SetPen(wx.Pen(wx.Colour(150,183,212)))
    dc.DrawLine(0,height-1,width,height-1)
    if bitmap_on_top:
        dc.DrawBitmap(brand_bmp,18,padding/2)
    f= dc.GetFont()
    f.SetPointSize(12)
    dc.SetFont(f)
    w,h= dc.GetTextExtent(text)
    dc.SetTextForeground((255,255,255,128))
    dc.DrawText(text,width-25-w,height/2 - h/2 +1)
    dc.SetTextForeground((98,115,136))
    dc.DrawText(text,width-25-w,height/2 - h/2)
    dc.SelectObject(wx.NullBitmap)
    return banner_bmp

class Frame(wx.Frame):
    def __init__(self,*args,**kwargs):
        wx.Frame.__init__(self,*args,**kwargs)
        panel= wx.Panel(self)

	sizer= wx.BoxSizer(wx.VERTICAL)
	bmp= wx.StaticBitmap(panel,bitmap=draw_me_a_bitmap(500,"without bitmap",False))
        sizer.Add(bmp,0,wx.ALL,5)
        bmp= wx.StaticBitmap(panel,bitmap=draw_me_a_bitmap(500,"with bitmap",True))
	sizer.Add(bmp,0,wx.ALL,5)
	panel.SetSizer(sizer)
        self.Show()

if __name__ == "__main__":
    app= wx.App(False)
    Frame(None,size=(600,200))
    app.MainLoop()
