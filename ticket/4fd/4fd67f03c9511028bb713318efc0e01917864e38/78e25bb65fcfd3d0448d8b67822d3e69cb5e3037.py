#! /usr/bin/env python

import wx

class Frame(wx.Frame):

    def __init__(self, image, parent=None, id=-1, pos=wx.DefaultPosition, title="Splash Demo"):
        bmp = image.ConvertToBitmap()
        size = bmp.GetWidth(), bmp.GetHeight()
        wx.Frame.__init__(self, parent, id, title, pos, size)
        self.bitmap = wx.StaticBitmap(parent=self, bitmap=bmp)


class App (wx.App):

    def OnInit(self):
        image = wx.Image('wxPython.jpg', wx.BITMAP_TYPE_JPEG)
        self.ShowSplashScreen(image)
        self.frame = Frame(image)
        self.frame.Show(True)
        self.SetTopWindow(self.frame)
        return True
    
    def ShowSplashScreen(self, image):
        bmp = image.ConvertToBitmap()
        wx.SplashScreen(bmp, wx.SPLASH_CENTRE_ON_SCREEN | wx.SPLASH_TIMEOUT, 1000, None, -1)
        wx.Yield()
        

if __name__ == '__main__':
    app = App()
    app.MainLoop()

 	  	 
