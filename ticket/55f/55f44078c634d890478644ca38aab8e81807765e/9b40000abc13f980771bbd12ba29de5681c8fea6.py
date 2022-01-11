
import wx

class ProcessDialog (wx.Dialog) :
  def __init__ (self, parent, message, caption, callback=None) :
    wx.Dialog.__init__(self,
      parent=parent,
      title=caption,
      style=wx.RAISED_BORDER|wx.CAPTION)
    self.callback = callback
    self.process = None
    self._error = None
    szr = wx.BoxSizer(wx.VERTICAL)
    self.SetSizer(szr)
    szr2 = wx.BoxSizer(wx.VERTICAL)
    szr.Add(szr2, 1, wx.ALL, 5)
    msg_txt = wx.StaticText(self, -1, message)
    msg_txt.Wrap(400)
    szr2.Add(msg_txt, 0, wx.ALIGN_CENTER_HORIZONTAL|wx.ALL, 5)
    self.gauge = wx.Gauge(parent=self)
    self.gauge.SetRange(100)
    szr2.Add(self.gauge, 1, wx.ALL|wx.EXPAND|wx.ALIGN_CENTER_HORIZONTAL, 5)
    abort_btn = wx.Button(parent=self,
      label="Abort")
    self.Bind(wx.EVT_BUTTON, self.OnAbort, abort_btn)
    szr2.Add(abort_btn, 0, wx.ALL|wx.ALIGN_CENTER_HORIZONTAL, 5)
    szr.Fit(self)
    self.Centre(wx.BOTH)

  def run (self, process) :
    self.Bind(wx.EVT_SHOW, self.OnAbort)
    self.gauge.Pulse()
    return self.ShowModal()

  def OnAbort (self, event) :
    self.EndModal(wx.ID_CANCEL)

if (__name__ == "__main__") :
  app = wx.App(0)
  dlg = ProcessDialog(
    parent=None,
    message="Running test function as separate process...",
    caption="Test dialog")
  print "starting dlg.ShowModal()"
  status = dlg.run(None)#p)
  print "dialog exited"
  wx.CallAfter(dlg.Destroy)
  print "OK"
