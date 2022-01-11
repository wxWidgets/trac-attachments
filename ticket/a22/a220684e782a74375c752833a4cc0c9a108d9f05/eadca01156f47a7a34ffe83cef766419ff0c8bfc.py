
from wx.lib.agw import flatnotebook
import wx.aui
import wx

class Notebook (wx.aui.AuiNotebook) :
  def DeletePage (self, page) :
    print 12345
    wx.aui.AuiNotebook.DeletePage(self, page)

class MyFrame (wx.Frame) :
  def __init__ (self, *args, **kwds) :
    wx.Frame.__init__(self, *args, **kwds)
    szr = wx.BoxSizer(wx.VERTICAL)
    self.SetSizer(szr)
    nb = flatnotebook.FlatNotebook(parent=self,
      agwStyle=flatnotebook.FNB_NODRAG)
    szr.Add(nb, 1, wx.EXPAND)
    page1 = ContentPanel(nb, size=(600,400))
    nb.AddPage(page1, "Page 1")
    for n in range(2) :
      nb2 = flatnotebook.FlatNotebook(parent=nb,
        agwStyle=flatnotebook.FNB_NODRAG)
      nb.AddPage(nb2, "Page %d" % (n+2))
      for m in range(2) :
        p2 = ContentPanel(nb2, size=(600,400))
        nb2.AddPage(p2, "Page %d" % (m+1))

class ContentPanel (wx.Panel) :
  def __init__ (self, *args, **kwds) :
    wx.Panel.__init__(self, *args, **kwds)
    szr = wx.BoxSizer(wx.VERTICAL)
    self.SetSizer(szr)
    txt = wx.StaticText(self, -1, "This is a text label.")
    szr.Add(txt, 0, wx.ALL, 10)
    ctrl1 = wx.TextCtrl(self, -1, value="This is text input.", size=(400,-1))
    szr.Add(ctrl1, 0, wx.ALL, 10)
    szr2 = wx.BoxSizer(wx.VERTICAL)
    szr.Add(szr2, 0, wx.ALL)
    txt2 = wx.StaticText(self, -1, "Choices:")
    ctrl2 = wx.Choice(self, -1, choices=["Value 1", "Value 2"])
    szr2.Add(txt2, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 10)
    szr2.Add(ctrl2, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 10)

if (__name__ == "__main__") :
  app = wx.App(0)
  frame = MyFrame(None, -1, "Test frame")
  frame.Show()
  app.MainLoop()
