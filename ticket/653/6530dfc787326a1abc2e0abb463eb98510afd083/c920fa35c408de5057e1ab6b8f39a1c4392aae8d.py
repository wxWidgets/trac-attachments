import wx
import wx.lib.agw.aui as aui

class TestApp(wx.App):
    def OnInit(self):
        self.SetAppName("PyAuiNotebookTestApp")
        self.f = MyFrame()
        self.f.Show()
        return True

class MyFrame(wx.Frame):
    def __init__(self):
        super(MyFrame, self).__init__(None, title="Notebook Perspective Test")

        # Attributes
        self._nb = aui.AuiNotebook(self)

        cfg = wx.Config(wx.GetApp().GetAppName())
        perspect = cfg.Read("Perspective", u"")

        if perspect:
            # Only load two of the panels that were saved before
            p1 = Panel1(self._nb)
            self._nb.AddPage(p1, "Panel1")
            p3 = Panel3(self._nb)
            self._nb.AddPage(p3, "Panel3")
            self._nb.LoadPerspective(perspect)
        else:
            p1 = Panel1(self._nb)
            self._nb.AddPage(p1, "Panel1")
            p2 = Panel2(self._nb)
            self._nb.AddPage(p2, "Panel2")
            p3 = Panel3(self._nb)
            self._nb.AddPage(p3, "Panel3")

        self.Bind(wx.EVT_CLOSE, self.OnClose)

    def OnClose(self, event):
        perspect = self._nb.SavePerspective()
        cfg = wx.Config(wx.GetApp().GetAppName())
        cfg.Write("Perspective", perspect)
        event.Skip()

class Panel1(wx.Panel):
    def __init__(self, parent):
        super(Panel1, self).__init__(parent)

        self.SetBackgroundColour(wx.BLUE)

class Panel2(wx.Panel):
    def __init__(self, parent):
        super(Panel2, self).__init__(parent)

        self.SetBackgroundColour(wx.RED)

class Panel3(wx.Panel):
    def __init__(self, parent):
        super(Panel3, self).__init__(parent)

        self.SetBackgroundColour(wx.GREEN)

if __name__ == '__main__':
    app = TestApp(False)
    app.MainLoop()
