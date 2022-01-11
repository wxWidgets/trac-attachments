import wx

#----------------------------------------------------------------------

class TestPanel(wx.Panel):
    def __init__(self, parent, log):
        self.log = log
        wx.Panel.__init__(self, parent, -1)

        self.Bind(wx.EVT_PAINT, self.OnPaint)

    def OnPaint(self, evt):
        dc = wx.PaintDC(self)
        try:
            gc = wx.GraphicsContext.Create(dc)
        except NotImplementedError:
            dc.DrawText("This build of wxPython does not support the wx.GraphicsContext "
                        "family of classes.",
                        25, 25)
            return

        self.log('XXX')
        # comment the next line to prevent the crash/hang
        # or move it below gc.SetFont
        self.log( gc.GetTextExtent('test') )
        self.log('YYY')
        font = wx.SystemSettings.GetFont(wx.SYS_DEFAULT_GUI_FONT)
        font.SetWeight(wx.BOLD)
        gc.SetFont(font)

#----------------------------------------------------------------------

if __name__ == '__main__':
    app = wx.App( redirect = False )
    frame = wx.Frame( None, wx.ID_ANY, 'gc crash' )
    def log(msg):
        print msg
    pnl = TestPanel( frame, log )
    frame.Show()
    app.MainLoop()

