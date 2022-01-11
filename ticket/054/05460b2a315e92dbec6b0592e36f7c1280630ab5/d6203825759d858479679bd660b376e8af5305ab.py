import wx

class BlittingFrame(wx.Frame):

    def __init__(self, parent, wxId, bitmap=None, **options):
        wx.Frame.__init__(self, parent, wxId, 'Blitting Test Frame', **options)
        if bitmap is None:
            oBitmap = wx.EmptyBitmap(200,200)
        else:
            oBitmap = wx.Image(bitmap).ConvertToBitmap()
        self.__oMemDc = wx.MemoryDC()
        self.__oMemDc.SelectObject(oBitmap)
        iBmpWidth = oBitmap.GetWidth()
        iBmpHeight = oBitmap.GetHeight()
        self.SetClientSize(wx.Size(iBmpWidth, iBmpHeight))
        self.CentreOnScreen()
        oButton = wx.Button(self, -1, 'Close')
        wx.EVT_PAINT(self, self.OnPaint)
        wx.EVT_BUTTON(oButton, oButton.GetId(), self.OnButtonClose)

    def OnPaint(self, ev):
        oDc = wx.PaintDC(self)
        iWidth, iHeight = self.GetSizeTuple()
        oDc.Blit(0, 0, iWidth, iHeight, self.__oMemDc, 0, 0, wx.COPY)

    def OnButtonClose(self, ev):
        self.Close(True)

if __name__ == "__main__":
    app = wx.PySimpleApp()
    frame = BlittingFrame(None, -1)
    frame.Show(True)
    app.MainLoop()


 	  	 
