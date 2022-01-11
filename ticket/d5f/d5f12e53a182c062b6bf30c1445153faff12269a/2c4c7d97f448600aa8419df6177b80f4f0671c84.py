import wx

class MainFrame(wx.Frame):
	def __init__(self, parent, id):
		wx.Frame.__init__(self, parent, id, 'SetStatusText Test', size = wx.Size(900,100))
		wx.Frame.CreateStatusBar(self, 1) 

		msg = ''
		for i in xrange(10,200,10):
			msg += '.......' + ('%03d' % i)
		self.SetStatusText(msg, 0)

class MainApp(wx.App):
	def OnInit(self):
		self.frame = MainFrame(None,-1)
		self.frame.Show(True)
		self.SetTopWindow(self.frame)
		return True

if __name__ == '__main__':
	app = MainApp(0)
	app.MainLoop()

 	  	 
