import wx

class MyFrame(wx.Frame):

	def __init__(self, parent, ID, title):
		wx.Frame.__init__(self, parent, ID, title, size=(300, 250))

		self.slider = wx.Slider ( self, -1, 1, 1, 1, style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|~wx.SL_LABELS )

		self.SetAutoLayout(True)
		self.Layout()


app = wx.PySimpleApp()
frame = MyFrame(None, -1, "Slider Test")
frame.Show()
app.MainLoop()
 	  	 
