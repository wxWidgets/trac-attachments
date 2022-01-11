import wx
import wx.lib.inspection

print wx.version()

class TestFrame(wx.Frame):
    def __init__(self, parent=None, id=-1, title="Autobuffered Test", pos=wx.DefaultPosition,
                 size=wx.DefaultSize, style=wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL):
        wx.Frame.__init__(self, parent, id, title, pos, size, style)
        
        p = TestPanel(self, -1)
        
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(p, 1, wx.GROW, 0)
        
        self.SetSizer(sizer)
        self.Layout()
                 
class TestPanel(wx.Panel):
    def __init__(self, parent, id=-1, pos=wx.DefaultPosition, size=wx.DefaultSize, style=0):
        wx.Panel.__init__(self, parent, id, pos, size, style)
        
        self.dw = 100.0
        self.xscale = 1
        self.yscale = 1
        self.Bind(wx.EVT_SIZE, self.OnSize)
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        
        self.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
        
        self.Bind(wx.EVT_ERASE_BACKGROUND, self.OnEraseBackground)
        
    def OnSize(self, evt):
        w, h = evt.GetSize()
        self.xscale = w/self.dw
        self.yscale = h/self.dw
        
        self.Refresh()
    
    def OnPaint(self, evt):
        dc = wx.AutoBufferedPaintDC(self)
        
        dc.SetBrush(wx.LIGHT_GREY_BRUSH)
        size = self.GetSize()
        dc.DrawRectangle(0, 0, size[0], size[1])
        
        dc.SetUserScale(self.xscale, self.yscale)
        dc.DrawLine(self.dw, 0, 0, self.dw)
        dc.DrawLine(0, self.dw, self.dw, self.dw)
        dc.DrawLine(self.dw, self.dw, self.dw, 0)
        dc.DrawLine(0, 0, 0, self.dw)
        dc.DrawLine(0, 0, self.dw, 0)
        dc.DrawLine(0, 0, self.dw, self.dw)
        
        #dc.SetUserScale(1.0, 1.0)
        
    def OnEraseBackground(self, evt):
        pass
        
app = wx.PySimpleApp(0)

frame = TestFrame()
frame.Show()

#wx.lib.inspection.InspectionTool().Show()

app.MainLoop()
