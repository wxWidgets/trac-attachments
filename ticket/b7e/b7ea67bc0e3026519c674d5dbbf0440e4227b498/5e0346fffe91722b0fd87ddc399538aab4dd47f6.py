import wx

def rotateBitmap(bitmap,angle_radians):
    img= bitmap.ConvertToImage()
    img_centre= (img.GetWidth()/2,img.GetHeight()/2)
    img= img.Rotate(angle_radians,img_centre)
    return img.ConvertToBitmap()

def getSomeBitmap(rotate,set_mask_before_rotate):
    bitmap= wx.EmptyBitmap(50,50)
    dc=wx.MemoryDC(bitmap)
    dc.SetBackground(wx.Brush(wx.WHITE))
    dc.Clear()
    dc.DrawText("TEST",10,15)
    dc.Destroy()
    if set_mask_before_rotate:
        bitmap.SetMaskColour(wx.WHITE)
    if rotate:
        bitmap= rotateBitmap(bitmap,6)
    if not set_mask_before_rotate:
        bitmap.SetMaskColour(wx.WHITE)
    return bitmap

class Frame(wx.Frame):
    def __init__(self,*args,**kwargs):
        wx.Frame.__init__(self,*args,**kwargs)
        panel= wx.Panel(self)
        sizer=wx.BoxSizer()
        sizer.Add(wx.StaticBitmap(panel,bitmap=getSomeBitmap(False,False)))
        sizer.Add(wx.StaticBitmap(panel,bitmap=getSomeBitmap(True,True)))
        sizer.Add(wx.StaticBitmap(panel,bitmap=getSomeBitmap(True,False)))
        panel.SetSizer(sizer)
        self.Show()


class App(wx.App):
    def OnInit(self):
        Frame(None)
        return True

if __name__ == "__main__":
    app=App(False)
    app.MainLoop()
