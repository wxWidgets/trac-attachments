import wx
TRY_BUG = 1
class Frame(wx.MDIParentFrame):
	def __init__(self):
		wx.MDIParentFrame.__init__(self, None, -1)
		self.SetSize(wx.Size(800,600))
		self._tbH = 0
		if TRY_BUG:
			tb = self.CreateToolBar( wx.TB_HORIZONTAL )
			tsize = (22,22)
			tb.SetToolBitmapSize(tsize)
			new_bmp = wx.ArtProvider.GetBitmap(wx.ART_NEW, wx.ART_TOOLBAR, tsize)
			tb.AddSimpleTool(wx.ID_NEW, new_bmp, "New","Long help for 'New'")
			tb.Bind(wx.EVT_MENU, self.onNew, id=wx.ID_NEW)
			tb.Realize()
		if not TRY_BUG:
			self._tbH = tb.GetSizeTuple()[1]

	def onNew(self, evt):
		f = wx.MDIChildFrame(self, pos=wx.Point(0,0))
		f.Show()
		f.SetDimensions(0,-self._tbH,100,100)

if __name__ == '__main__':
	class MyApp(wx.App):
		def OnInit(self):
			wx.InitAllImageHandlers()
			frame = Frame()
			frame.Show( True )
			self.SetTopWindow( frame )
			return True

app = MyApp( False )
app.MainLoop()
