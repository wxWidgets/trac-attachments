
import wx

class MyFrame(wx.Frame):
    def __init__(self):
        super(MyFrame, self).__init__(None)
        self.panel = wx.Panel(self)

        top_level = wx.Frame(None)
        top_level.Reparent(self)

        self.panel.Destroy()

if __name__ == '__main__':
    app = wx.App()
    red_frame = MyFrame()
    red_frame.Show()
    app.MainLoop()
