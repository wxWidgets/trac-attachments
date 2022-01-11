
import wx

class Panel(wx.Panel):
    
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        self.Bind(wx.EVT_PAINT, self.onPaint)
    
    
    def onPaint(self, evt):
        
        dc = wx.PaintDC(self)
        self.draw(dc)
    
    
    def draw(self, dc):
        
        gc = wx.GCDC(dc)
        
        gc.SetBackground(wx.Brush(wx.WHITE, wx.SOLID))
        gc.Clear()
        
        gc.SetPen(wx.Pen((100,100,255)))
        gc.SetBrush(wx.Brush((100,255,100)))
        
        gc.DrawRectangle(10, 10, 70, 70) # this will be transparent in exported png
        gc.DrawRectangle(100, 10, 50, 50)
        
        gc.DrawRoundedRectangle(10, 100, 70, 70, 5)
        gc.DrawRoundedRectangle(100, 100, 50, 50, 5)
    
    
    def get_bitmap(self):
        
        width, height = self.GetClientSize()
        bitmap = wx.EmptyBitmap(width, height)
        dc = wx.MemoryDC()
        dc.SelectObject(bitmap)
        dc.Clear()
        
        self.draw(dc)
        dc.SelectObject(wx.NullBitmap)
        
        return bitmap
    


class MyApp(wx.App):
    
    def OnInit(self):
        
        frame = wx.Frame(None, title="Transparent Rectangle Test", size=(180,220))
        panel = Panel(frame)
        frame.Show(True)
        
        # export as png
        bitmap = panel.get_bitmap()
        image = bitmap.ConvertToImage()
        image.SaveFile('test.png', wx.BITMAP_TYPE_PNG)
        
        # paste to clipboard
        obj = wx.BitmapDataObject(bitmap)
        if wx.TheClipboard.Open():
            wx.TheClipboard.SetData(obj)
            wx.TheClipboard.Flush()
            wx.TheClipboard.Close()
        
        return True


if __name__ == '__main__':
    app = MyApp(0)
    app.MainLoop() 