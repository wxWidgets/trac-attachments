import wx

class TestApp(wx.Frame):
 
    #----------------------------------------------------------------------
    def __init__(self):
        wx.Frame.__init__(self, None, wx.ID_ANY, "Test")
 
        wx.SafeYield()
        scrDC = wx.ScreenDC() 
        scrDcSize = scrDC.Size
        width, height = scrDcSize
        
        bmp = wx.EmptyBitmap(width, height)

        memDC = wx.MemoryDC()

        memDC.SelectObject(bmp)
 
        wx.SafeYield()
        memDC.Blit( 0, 0, width, height, scrDC, 0,0)
        memDC.SelectObject(wx.NullBitmap)
        bmp.SaveFile("test.png", wx.BITMAP_TYPE_PNG)

# Run the program
if __name__ == "__main__":
    app = wx.App(False)
    wx.InitAllImageHandlers()
    frame = TestApp()
    frame.Show()
    app.MainLoop()