import wx
import wx.lib.agw.aui as aui

class Frame(wx.Frame):
    def __init__(self, title):
        wx.Frame.__init__(self, None, title=title, size=(350,200))
        self.nb = aui.AuiNotebook(self)
        self.nb.AddPage(wx.Panel(self.nb),"1")
        self.nb.AddPage(wx.Panel(self.nb),"2")
        sizer = wx.BoxSizer()
        sizer.Add(self.nb, 1, wx.EXPAND)
        self.SetSizer(sizer)

app = wx.App(redirect=True)
top = Frame("Hello World")
top.Show()
app.MainLoop()
