import wx
class frame(wx.Frame):
    def __init__(self,p=None):
        wx.Frame.__init__(self,p)
        self.box = wx.ListBox(self)
        self.box.AppendItems( ['Zero', 'One', 'Two', 'Three', 'Four', \
                               'Five', 'Six', 'Seven', 'Eight', 'Nine', \
                               'Ten', 'Eleven', 'Twelve', 'Thirteen'] )
        self.box.Bind(wx.EVT_MOUSE_EVENTS,self.onMouse)
    def onMouse(self,evt):
        pos = evt.GetPosition()
        print self.box.HitTest(pos)
        evt.Skip()
class guiApp(wx.App):
    def __init__(self,redirect=False):
        wx.App.__init__(self,redirect)
    def OnInit(self):
        f = frame()
        f.Show()
        self.SetTopWindow(f)
        return True
if __name__=="__main__":
    app = guiApp()
    app.MainLoop()
