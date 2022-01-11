# -*- coding: utf-8 -*-
# Chapter 1: wxPython starting points
# Recipe 3: Using Bitmaps
#
import wx

class ImagePanel(wx.Panel):
    def __init__(self, parent):
        super().__init__(parent)
        
        # Load the image data into a Bitmap
        theBitmap = wx.Bitmap("usingBitmaps.png")
        
        # Create a control that can display the bitmap
        # on the screen.
        # Add following line to put the bitmaps in a sizer. Idea is to have 2 bitmaps (originating from identical bitmap)
        # next to each other.
        #self.Sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.bitmap = wx.StaticBitmap(self).SetBitmap(theBitmap)
        #self.bitmap2 = wx.StaticBitmap(self).SetBitmap(theBitmap)
        #self.Sizer.Add(self.bitmap, 0, wx.EXPAND|wx.ALL, 3)
        #self.Sizer.Add(self.bitmap2, 0, wx.EXPAND | wx.ALL, 3)


class MyFrame(wx.Frame):
    def __init__(self, parent, title=""):
        super().__init__(parent, title=title)
        
        # Set the panel
        self.panel = ImagePanel(self)

class MyApp(wx.App):
    def OnInit(self):
        self.frame = MyFrame(None, title="Using Bitmaps")
        self.frame.Show()
        return True

if __name__ == "__main__":
    app = MyApp(False)
    app.MainLoop()