import wx

class MyFrame(wx.Frame):

	def __init__(self, parent, ID, title):
		wx.Frame.__init__(self, parent, ID, title, size=(300, 250))

		self.t1 = wx.TextCtrl ( self, -1, "", (-1,-1) )
		self.t1.Bind ( wx.EVT_TEXT, self.on_text )

		self.SetAutoLayout(True)
		self.Layout()

	def on_text ( self, event ):

		entry = self.t1.GetValue()
		self.t1.Unbind ( wx.EVT_TEXT )
		self.t1.SetValue ( "%d" %( int(entry) + 1 ) )
		self.t1.Bind ( wx.EVT_TEXT, self.on_text )
		event.Skip()


app = wx.PySimpleApp()
frame = MyFrame(None, -1, "Bind Test")
frame.Show()
app.MainLoop()
 	  	 
