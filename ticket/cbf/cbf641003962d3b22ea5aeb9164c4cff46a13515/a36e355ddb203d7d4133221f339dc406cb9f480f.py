from wxPython import wx
f=wx.wxFrame(None,-1,'test')
s1=wx.wxBoxSizer()
s2=wx.wxBoxSizer()
s1.Add(s2)
f.SetSizer(s1)
#
s1.Add(wx.wxButton(f,-1,'button sizer1'),0,0)
s2.Add(wx.wxButton(f,-1,'button sizer2'),0,0)
#
def hideS2():
    s1.Show(s2,False)
    f.Layout()
def showS2():
    s1.Show(s2,True)
    f.Layout()
#
f.Show(True)

 	  	 
