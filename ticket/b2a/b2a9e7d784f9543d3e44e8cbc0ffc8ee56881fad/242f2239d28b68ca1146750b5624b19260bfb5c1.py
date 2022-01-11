
import wx
print wx.version()
import wx.lib.agw.aui as aui

class Pane(wx.Panel):

    def __init__(self, parent):
        super(Pane, self).__init__(parent)

        self._sizer = wx.BoxSizer(wx.VERTICAL)
        self._txt = wx.TextCtrl(self, -1, "text")
        #self._txt = wx.StaticText(self, -1, "text")
        self._sizer.Add(self._txt, 1, wx.EXPAND, 5)
        self.SetSizer(self._sizer)

        self.SetMinSize((300, 300))

    def GetBestSize(self):
        return (300, 300)

class Frame(wx.Frame):

    def __init__(self):
        super(Frame, self).__init__(None)

        flags = (aui.AUI_MGR_DEFAULT | aui.AUI_MGR_ALLOW_ACTIVE_PANE
                 | aui.AUI_MGR_USE_NATIVE_MINIFRAMES)
        self._mgr = aui.AuiManager(self, flags)
	
        self._mgr.AddPane(Pane(self), aui.AuiPaneInfo().Left().MinSize(300, 300))
        self._mgr.AddPane(Pane(self), aui.AuiPaneInfo().Right().MinSize(200, 200))
        self._mgr.Update()


app = wx.App(False)
frame = Frame()
frame.Show()
app.MainLoop()
