
import wx
import wx.lib.buttons

class TopFrame(wx.Frame):
  def __init__(self, parent, id):
    wx.Frame.__init__(self, parent, id, "Address Book", size = (300,200))

    self.nextbutton = wx.lib.buttons.GenButton( self, -1, "Next",
                     (50,40), (50, -1) )
    self.nextbutton.Bind(wx.EVT_BUTTON, self.OnNext)
    self.prevbutton = wx.lib.buttons.GenButton( self, -1, "Prev",
                     (200,40), (50, -1) )
    self.prevbutton.Bind(wx.EVT_BUTTON, self.OnPrev)

    self.status = wx.StaticText( self, -1, "Last button pressed: None ",
                                 (1, 80))

  def OnNext(self, event):
    self.nextbutton.SetBackgroundColour("gray")
    self.prevbutton.SetBackgroundColour("red")
    self.nextbutton.Refresh()
    self.prevbutton.Refresh()
    self.status.SetLabel("Last button pressed: Next ")

  def OnPrev(self, event):
    self.prevbutton.SetBackgroundColour("gray")
    self.nextbutton.SetBackgroundColour("red")
    self.nextbutton.Refresh()
    self.prevbutton.Refresh()
    self.status.SetLabel("Last button pressed: Prev ")


class App(wx.App):
  def OnInit(self):
    self.frame = TopFrame(None, -1)
    self.frame.Show()
    self.SetTopWindow(self.frame)
    return True

if __name__ == '__main__':
  app = App(redirect=False)
  app.MainLoop()

