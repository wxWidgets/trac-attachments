import wx
from wx.lib.agw.flatnotebook import FlatNotebook


class Notebook(FlatNotebook):
    def __init__(self, parent):
        super(Notebook, self).__init__(parent)
        self.AddPage(Page(self), 'Test1')
        self.AddPage(Page(self), 'Test2')


class Page(wx.SplitterWindow):
    def __init__(self, parent):
        super(Page, self).__init__(parent)
        self.SetMinimumPaneSize(20)
        self.SetSashGravity(1.0)
        self.SplitHorizontally(wx.TextCtrl(self), wx.TextCtrl(self))
        self.SetSashPosition(60)


app = wx.App()
frame = wx.Frame(None)
nb = Notebook(frame)
frame.Centre()
frame.Show()
app.MainLoop()
