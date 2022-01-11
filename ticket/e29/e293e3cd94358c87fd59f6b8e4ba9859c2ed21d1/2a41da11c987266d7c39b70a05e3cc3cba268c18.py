
import wx

class TopFrame(wx.Frame):
  def __init__(self, parent, id):
    wx.Frame.__init__(self, parent, id, "Address Book", size = (300,200))

    label = wx.StaticText(self, -1, "Does cursor show?", (20, 20))
    self.field = wx.TextCtrl(self, -1, '', (20, 60), validator=MyValidator())
    self.field.Bind(wx.EVT_SET_FOCUS, self.onFocus)
    self.field2 = wx.TextCtrl(self, -1, '', (20, 100))

  def onFocus(self, event):
    self.field.SetInsertionPoint(0)

class MyValidator(wx.PyValidator):
  def __init__(self):
    wx.PyValidator.__init__(self)

  def Clone(self):
    " Every validator must implement the Clone() method. "
    return MyValidator()


class App(wx.App):
  def OnInit(self):
    self.frame = TopFrame(None, -1)
    self.frame.Show()
#    self.SetTopWindow(self.frame)
    return True

if __name__ == '__main__':
  app = App(redirect=False)
  app.MainLoop()

