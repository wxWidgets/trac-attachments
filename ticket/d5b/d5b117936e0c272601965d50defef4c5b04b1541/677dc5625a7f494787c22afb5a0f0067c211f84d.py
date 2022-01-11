import wx
import wx.lib.agw.aui as aui

class MyFrame(wx.Frame):
    def __init__(self):
        super(MyFrame, self).__init__(None, title="Test Frame")

        nb = aui.AuiNotebook(self)
        il = wx.ImageList(16, 16)
        bmp = wx.ArtProvider.GetBitmap(wx.ART_INFORMATION, wx.ART_MENU, (16,16))
        self._index = il.Add(bmp)
        nb.SetImageList(il)

        p = wx.Panel(nb)
        b = wx.Button(p, label="GetPageImage")
        nb.AddPage(p, "Page 0")
        nb.SetPageImage(0, self._index)

        def printGetPageImage():
            print "Page Image: ", nb.GetPageImage(0), "Actual Index:", self._index
        self.Bind(wx.EVT_BUTTON, lambda evt: printGetPageImage(), b)

app = wx.App(False)
f = MyFrame()
f.Show()
app.MainLoop()
