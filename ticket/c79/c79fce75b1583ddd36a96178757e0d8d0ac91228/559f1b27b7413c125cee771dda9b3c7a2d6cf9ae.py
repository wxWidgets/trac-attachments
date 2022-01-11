import wx

class Tester(wx.Window):
    def __init__(self, parent, id):
        wx.Window.__init__(self, parent, id)
        # We need to know when to draw ourselves...
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        
    ###########################################################
    def OnPaint(self, event):
        # Get a paint context and new-style graphics context.  Right now, we
        # will fail if graphics context doesn't work...
        dc = wx.PaintDC(self)
        gc = wx.GraphicsContext.Create(dc)
        
        extra = .5        # Terrible lines on mac, good for even-width on PC
        #extra = 0         # Good on mac, good for odd-width on PC
        
        len = 5
        spacing = 5
        
        
        # Horizotal lines...
        xOrig = 3 + extra
        yOrig = 3 + extra
        
        x = xOrig
        y = yOrig
        
        for i in xrange (1, 6):
            pen = wx.Pen("black", i)
            gc.SetPen(pen)
            gc.StrokeLine (x, y, x+len, y)
            x += len+spacing
        
        x = xOrig
        y += 10
        
        for i in xrange (1, 6):
            pen = wx.Pen("black", i)
            pen.SetCap(wx.CAP_PROJECTING)
            gc.SetPen(pen)
            gc.StrokeLine (x, y, x+len, y)
            x += len+spacing

        x = xOrig
        y += 10
        
        for i in xrange (1, 6):
            pen = wx.Pen("black", i)
            pen.SetCap(wx.CAP_BUTT)
            gc.SetPen(pen)
            gc.StrokeLine (x, y, x+len, y)
            x += len+spacing
            
        # Vertical lines...
        xOrig = 3 + extra
        yOrig = 30 + extra
        
        x = xOrig
        y = yOrig
        
        for i in xrange (1, 6):
            pen = wx.Pen("black", i)
            gc.SetPen(pen)
            gc.StrokeLine (x, y, x, y+len)
            y += len+spacing
        
        x += 10
        y  = yOrig
        
        for i in xrange (1, 6):
            pen = wx.Pen("black", i)
            pen.SetCap(wx.CAP_PROJECTING)
            gc.SetPen(pen)
            gc.StrokeLine (x, y, x, y+len)
            y += len+spacing
        
        x += 10
        y  = yOrig
        
        for i in xrange (1, 6):
            pen = wx.Pen("black", i)
            pen.SetCap(wx.CAP_BUTT)
            gc.SetPen(pen)
            gc.StrokeLine (x, y, x, y+len)
            y += len+spacing

def main():
    # Create a simple test app to see how things worked!
    app = wx.PySimpleApp()
    frame = wx.Frame(None, -1, "graphicsContextTests", size=(200,200))
    tester = Tester(frame, -1)
    
    # Go!
    frame.Show(1)
    app.MainLoop()

if __name__ == '__main__':
    main()

 	  	 
