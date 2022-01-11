import wx

class myobjects(wx.Window):
    def __init__(self, parent, number):
        wx.Window.__init__(self, parent, -1)
        
        self.SetSize( ( 300,50 ) )
        self.number = number
        
        wx.EVT_PAINT(self, self._onPaint)
        
    
    def _onPaint(self, evt):
        
        paintdc = wx.BufferedPaintDC(self)
        paintdc.SetTextForeground(wx.Colour(255,255,255))
        paintdc.DrawText("TEST NUMBER %s" % self.number, 5, 5)
        paintdc.EndDrawing()
        

class Test(wx.ScrolledWindow):
    def __init__(self, *args, **kwds):
        wx.ScrolledWindow.__init__(self, *args, **kwds)
        self.EnableScrolling(False,True)
        
        hgap, vgap = 5, 5
        class Pos:
            def __init__(self):
                self.x = 0
                self.y = 0
        pos = Pos()
        rows = 1
        for number in range(1000):
            
            obj = myobjects(self, number)
            obj.SetPosition((pos.x+hgap, pos.y+vgap))
            print "OBJ NUMBER %s GETPOSITION %s" % ( number, str(obj.GetPosition()) )
            rows +=1
            pos.x = 0
            pos.y = ( ( obj.GetSize()[1] + vgap ) * ( rows -1 ) )
        
        self.SetScrollbars(0,55,0,rows)
        

if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    f = wx.Frame(None, -1, "TEST")
    t = Test(f, -1)
    f.Show()
    app.MainLoop()
 	  	 
