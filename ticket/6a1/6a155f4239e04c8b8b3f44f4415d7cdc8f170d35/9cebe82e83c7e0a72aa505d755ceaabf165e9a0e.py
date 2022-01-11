import wx

class Frame(wx.Frame):
    def __init__(self,*args,**kwargs):
        wx.Frame.__init__(self,*args,**kwargs)
        self.control = wx.TextCtrl(self, style=wx.TE_MULTILINE | wx.ST_NO_AUTORESIZE,value="",size=self.Size)
        def configure():
                import threading
                self.activeTimer = threading.Timer(0.1,_step)
                self.activeTimer.start()
        def _step():
            self.control.SetValue(self.control.GetValue()+"crash me\n")
            configure()
        configure()

app = wx.App(False)
app.SetAppName("StaticTextCrash")


frame = Frame(None)
frame.Show()
app.MainLoop()