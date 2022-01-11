import wx
#
class MyApp(wx.App):
	def OnInit(self):
		myframe=wx.Frame(None,-1,'test')
		logButton1 = wx.Button(myframe,-1,'Show Log')
		logButton2 = wx.Button(myframe,-1,'Show Log with Gui')
		s=wx.BoxSizer(wx.VERTICAL)
		s.Add(logButton1,0,0)
		s.Add(logButton2,0,0)
		myframe.SetSizer(s)
		myframe.Layout()
		wx.EVT_BUTTON(logButton1,logButton1.GetId(),self.button1)
		wx.EVT_BUTTON(logButton2,logButton2.GetId(),self.button2)
		myframe.Show()
		return True
		
	def button1(self,evt):
		# text of wxLog
		wx.LogMessage("test")		
		
	def button2(self,evt):
		# text of wxLog
		wx.Log.SetActiveTarget(wx.LogGui())
		wx.LogMessage("test")

myapp = MyApp()
myapp.MainLoop()

 	  	 
