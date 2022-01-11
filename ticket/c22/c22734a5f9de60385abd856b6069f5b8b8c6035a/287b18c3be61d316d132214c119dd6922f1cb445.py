import wx
from wx.lib.agw import aui

class TestPanel(wx.Panel):
    def __init__(self, *args, **keys):
        wx.Panel.__init__(self, *args, **keys)
        self.textCtrl = wx.StaticText( self, wx.ID_ANY, 'AGW is a very nice library!' )

class TestFrame(wx.Frame):
    def __init__(self, *args, **keys):
        wx.Frame.__init__(self, *args, **keys)
        self.mgr = mgr = aui.AuiManager()
        mgr.SetManagedWindow( self )        
        mgr.AddPane( TestPanel(self), aui.AuiPaneInfo().Name('p1').Caption('p1').Right().BestSize((100,100)) )
        mgr.AddPane( TestPanel(self), aui.AuiPaneInfo().Name('p2').Caption('p2').Bottom().BestSize((100,100)) )
        mgr.Update()


if __name__ == '__main__':
    app = wx.App( redirect = False )
    frame = TestFrame( None, title = 'AUI test', size = (300, 400) )
    frame.Show()
    app.MainLoop()