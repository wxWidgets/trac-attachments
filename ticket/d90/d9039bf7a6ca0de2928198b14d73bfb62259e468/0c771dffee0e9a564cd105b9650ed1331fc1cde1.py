use_saved_color = False # change to True and voila, no leak!

import wx

from win32api     import GetCurrentProcess
from win32con     import GR_GDIOBJECTS
from win32process import GetGuiResources
from wx.lib.floatcanvas import NavCanvas, FloatCanvas, Resources

def GdiReport(desc):
    numGdi = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS)
    print "%s: %d" % (desc, numGdi)

saved_color = wx.Colour(255, 100, 100)

class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, "Hello")
        
        canvas = FloatCanvas.FloatCanvas(self)
        canvas.Bind(wx.EVT_LEFT_UP, self.OnClick)
        self.arrow = canvas.AddArrow((0,0), 0.02, 90)
    
    def OnClick(self, event):
        GdiReport("MyWin before creating 100 wx.Colour")
        for x in xrange(100):
            # if you just keep a single instance of wx.Colour, no leak
            color = wx.Colour(255, 100, 100)
            if use_saved_color: color = saved_color
            self.arrow.SetColor(color)
        GdiReport("MyWin  after creating 100 wx.Colour")
        event.Skip()

##############################################################################
def _simpleTest():
    """Create a simple test app to see how things worked!
    """
    app = wx.PySimpleApp()
    
    frame = MyFrame()
    frame.Show(1)
    
    app.MainLoop()
    
if __name__ == '__main__':
    _simpleTest()


