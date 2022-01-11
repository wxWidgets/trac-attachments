import wx

PARENT = wx.ScrolledWindow
#PARENT = wx.Panel # uncomment this to "fix" problem
class DragWindow(PARENT):
    def __init__(self, parent):
        PARENT.__init__(self, parent, size=(300,200))
        self.Bind(wx.EVT_LEFT_DOWN, self.OnLeftDown)
        self.Bind(wx.EVT_MOTION, self.OnMotion)
        self.Bind(wx.EVT_LEFT_UP, self.OnLeftUp)
        self.SetBackgroundColour("YELLOW")

    def OnMotion(self, evt):
        if self.HasCapture():
            print 'drag at',evt.GetPosition()

    def OnLeftDown(self, evt):
        self.CaptureMouse()

    def OnLeftUp(self, evt):
        if self.HasCapture():
            self.ReleaseMouse()

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, 'CLICK AND DRAG FROM YELLOW TO GREEN')
        sizer = wx.BoxSizer(wx.HORIZONTAL)

        wnd = wx.Panel(self, size=(100,-1))
        sizer.Add(wnd)
        wnd = DragWindow(self)
        sizer.Add(wnd, 1, wx.EXPAND|wx.ALL, 0)

        self.SetSizer(sizer)
        self.SetBackgroundColour("GREEN")
        self.Fit()

if __name__=="__main__":
    print wx.version()
    app = wx.App(0)
    win = TestFrame()
    win.Show(True)
    app.MainLoop()
