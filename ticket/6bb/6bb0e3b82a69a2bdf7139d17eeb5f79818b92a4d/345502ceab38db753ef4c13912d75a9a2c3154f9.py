import sys
from wxPython import wx


frame = wx.wxFrame(None, -1, 'SetSizer crash')
sizer = wx.wxBoxSizer(wx.wxVERTICAL)
sizer.Add(wx.wxButton(frame, -1, 'SetSizer crash'))
frame.SetSizer(sizer)

if len(sys.argv) < 2:
    # segfault!
    frame.SetSizerAndFit(sizer)
else:
    # error message!
    frame.SetSizer(sizer)

sizer.Fit(frame)
frame.Show()


app = wx.wxPySimpleApp()
app.SetTopWindow(frame)
app.MainLoop()

 	  	 
