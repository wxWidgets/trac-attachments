import wx

class App(wx.App):
    """accelerator table test"""

    def OnInit(self):
        import sys
        self.frame = MyFrame('accelerator test')

        self.frame.Show()
        self.SetTopWindow(self.frame)

        wx.Bell()
        return True

class MyFrame(wx.Frame):

    def __init__(self, title, parent=None, id=wx.ID_ANY):
        wx.Frame.__init__(self, parent, id, title)
        at = wx.AcceleratorTable([
            (wx.ACCEL_NORMAL, wx.WXK_NUMPAD_MULTIPLY, wx.ID_ABOUT),
            ])
        self.SetAcceleratorTable(at)
        
        wx.EVT_MENU(self, wx.ID_ABOUT, self.OnAbout)

    def OnAbout(self, ev):
        wx.MessageBox("got it", "test", wx.OK, self)
        

if __name__ == '__main__':
    app = App()
    app.MainLoop()
