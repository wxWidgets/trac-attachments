import wx
import wx.animate


BUSY_GIF = 'Ajax-loader.gif'


class MainFrame(wx.Frame):
    def __init__(self, parent=None):
        wx.Frame.__init__(self, parent)
        self.toolbar = self.CreateToolBar()
        self.busy_animation = wx.animate.Animation(BUSY_GIF)
        self.busy_ctrl = wx.animate.AnimationCtrl(self.toolbar, -1, self.busy_animation)
        self.toolbar.AddControl(self.busy_ctrl)
        self.busy_ctrl.Play()
        self.toolbar.Realize()


class Test(wx.App):

    def __init__(self):
        self.frame = None
        wx.App.__init__(self, 0)

    def OnInit(self):
        self.frame = MainFrame()
        self.SetTopWindow(self.frame)
        self.frame.Show()
        return True


if __name__ == '__main__':
    app = Test()
    app.MainLoop()

