import wx, os, sys
class MainFrame(wx.Frame):
  def __init__(self, parent, title):
    wx.Frame.__init__(self, parent, -1, title)
    self.buttonsPanel = wx.Panel(self)
    self.butSink = wx.Button(self.buttonsPanel, label="Click me to sink ESC key")
    self.butOK = wx.Button(self.buttonsPanel, label="You can click me and still hit ESC", pos=(0,50))
    self.accel = wx.AcceleratorTable([(wx.ACCEL_NORMAL, wx.WXK_ESCAPE, ID_ESC)])
    self.SetAcceleratorTable(self.accel)
    self.Bind(wx.EVT_MENU, self.OnCloseWindow, id=ID_ESC)
    self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)
    self.butSink.Bind(wx.EVT_LEFT_UP, self.NavClick)
    self.buttonsPanel.SetFocus()

  def NavClick(self, event):
    self.butSink.Enable(False) # Kills the ESC key
    #self.buttonsPanel.SetFocus() #This has no effect
    #Toggle the remark below to toggle the effect
    self.butOK.SetFocus() #If do this, it works again

  def OnCloseWindow(self,event):
    self.Destroy()

class App(wx.App):
  def OnInit(self):
    frame = MainFrame(None, "click sink")
    self.SetTopWindow(frame)
    frame.Show(True)
    return True

ID_ESC = wx.NewId()

if __name__ == "__main__":
  app = App(0)
  app.MainLoop()
