import wx

class TestFrame(wx.Frame):
	def __init__(self, parent, id):
		super(TestFrame, self).__init__(parent=parent, id=id)
		self.SetSize((300,400))
		pal = wx.Panel(self)
		self.slider = wx.Slider(pal)
		self.slider.SetPosition((50, 50))
		self.slider.Bind(wx.EVT_LEFT_DOWN, self.onSliderLeftDown)
		self.slider.Bind(wx.EVT_SCROLL_THUMBRELEASE, self.onSliderLeftUp)

	def onSliderLeftDown(self, evt):
		print "Slider left down"
		evt.Skip()

	def onSliderLeftUp(self, evt):
		print "Slider left up"
		evt.Skip()

if __name__ == '__main__':
	app = wx.App()
	frm = TestFrame(None, -1)
	frm.Show()
	app.MainLoop()
