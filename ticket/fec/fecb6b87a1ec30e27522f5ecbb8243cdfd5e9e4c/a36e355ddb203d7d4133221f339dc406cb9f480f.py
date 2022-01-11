import wxversion
wxversion.select(["2.7"])
import wx
import wx.aui as AUI

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, "Left Right Bugs", size=(640,480))
        self._mgr = AUI.FrameManager(self)

        test = wx.TextCtrl(self, wx.ID_ANY, style=wx.TE_MULTILINE)
        wndinfo = AUI.PaneInfo()
        wndinfo.DestroyOnClose(False)
        wndinfo.Name("Test Wnd1")
        wndinfo.Caption("Test Wnd1")
        wndinfo.Right()
        wndinfo.BestSize((200,200))
        wndinfo.Show()
        self._mgr.AddPane(test, wndinfo)

        test = wx.TextCtrl(self, wx.ID_ANY, style=wx.TE_MULTILINE)
        wndinfo = AUI.PaneInfo()
        wndinfo.DestroyOnClose(False)
        wndinfo.Name("Test Wnd2")
        wndinfo.Caption("Test Wnd2")
        wndinfo.Left()
        wndinfo.BestSize((200,200))
        wndinfo.Show()
        self._mgr.AddPane(test, wndinfo)

        self._mgr.Update()

class TestFrame1(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, "Top Bottom Bugs", size=(640,480))
        self._mgr = AUI.FrameManager(self)

        test = wx.TextCtrl(self, wx.ID_ANY, style=wx.TE_MULTILINE)
        wndinfo = AUI.PaneInfo()
        wndinfo.DestroyOnClose(False)
        wndinfo.Name("Test Wnd1")
        wndinfo.Caption("Test Wnd1")
        wndinfo.Top()
        wndinfo.BestSize((300,200))
        wndinfo.Layer(1)
        wndinfo.Show()
        self._mgr.AddPane(test, wndinfo)

        test = wx.TextCtrl(self, wx.ID_ANY, style=wx.TE_MULTILINE)
        wndinfo = AUI.PaneInfo()
        wndinfo.DestroyOnClose(False)
        wndinfo.Name("Test Wnd2")
        wndinfo.Caption("Test Wnd2")
        wndinfo.Bottom()
        wndinfo.Layer(1)
        wndinfo.BestSize((300,200))
        wndinfo.Show()
        self._mgr.AddPane(test, wndinfo)

        self._mgr.Update()


class TestApp(wx.App):
    def OnInit(self):
        frame = TestFrame()
        frame.Raise()
        frame.Show()
        self.SetTopWindow(frame)
        frame1 = TestFrame1()
        frame1.Raise()
        frame1.Show()
        self.SetTopWindow(frame1)
        return True

if __name__ == "__main__":
    app = TestApp(0)
    app.MainLoop()

 	  	 
