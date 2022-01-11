import wx

class Test(wx.ScrolledWindow):
    def __init__(self, *args, **kwds):
        wx.ScrolledWindow.__init__(self, *args, **kwds)

        x = 0
        y = 0
        maxX = 500
        maxY = 50000

        self.SetScrollRate(0, 50)
        self.SetVirtualSize((maxX, maxY))
        
        while y < maxY:
            if x > maxX: x = 0
            b = wx.Button(self, -1, str( (x,y) ), (x,y))
            b.Bind(wx.EVT_BUTTON, self.OnShowPos)
            x += 25
            y += 150
            self.lastB = b

    def OnShowPos(self, evt):
        print self.CalcUnscrolledPosition(evt.GetEventObject().GetPosition())
        self.lastB.Move((0, 49950))

        
if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    f = wx.Frame(None, -1, "TEST")
    t = Test(f, -1)
    f.Show()
    app.MainLoop()

 	  	 
