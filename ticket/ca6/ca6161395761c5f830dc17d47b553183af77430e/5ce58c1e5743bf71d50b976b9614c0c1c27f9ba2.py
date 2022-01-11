#! /usr/bin/python

import wxversion
wxversion.select("3.0")
#wxversion.select("2.9.4")
import wx

class Dialog(wx.Dialog):
  def __init__(self, frame):
    wx.Dialog.__init__(self, frame, title="TestDialog", pos=frame.GetPosition()+(50,50))
    msg=wx.Button(self, 1001, "MsgBox", pos=(20,20))
    txt=wx.Button(self, 1002, "TxtBox", pos=(20, 100))
    msg.Bind(wx.EVT_BUTTON, self.OnPressMsg)
    txt.Bind(wx.EVT_BUTTON, self.OnPressTxt)
    self.Show()
    
  def OnPressMsg(self, _evt):
    dlg=wx.MessageDialog(self, "The Message Box")
    dlg.ShowModal()
  
  def OnPressTxt(self, _evt):
    dlg=wx.TextEntryDialog(self, "ignore", "Some Text")
    dlg.ShowModal()
    
class Frame(wx.Frame):
  def __init__(self):
    wx.Frame.__init__(self, None, title="TestFrame")
    wx.StaticText(self, -1, "Just some static text\nto fill the space\nrunning %s" % wx.version())
    self.Show()

app=wx.App()

frame=Frame()
Dialog(frame)
app.SetTopWindow(frame)
app.MainLoop()
