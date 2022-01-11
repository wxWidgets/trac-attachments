import wx
app = wx.App(0)
d = wx.Dialog(None, size=(200, -1))
s = wx.BoxSizer(wx.VERTICAL)
d.SetSizer(s)

# Add a few textareas
for i in xrange(10):
	t = wx.TextCtrl(d, -1, str(i))
	s.Add(t, flag=wx.EXPAND)

b = wx.Button(d, -1, "Test")
s.Add(b, flag=wx.EXPAND)
s.SetSizeHints(d)
s.Layout()
d.ShowModal()
d.Destroy()