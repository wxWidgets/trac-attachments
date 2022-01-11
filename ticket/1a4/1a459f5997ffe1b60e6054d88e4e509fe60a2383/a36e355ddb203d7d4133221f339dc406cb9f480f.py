#!/usr/bin/env python
# vim: tabstop=4 shiftwidth=4

import wx


class App(wx.App):
	"""Application class."""

	def OnInit(self):
		self.frame = wx.Frame(None)
		self.SetTopWindow(self.frame)
		panel = wx.Panel(self.frame)

		sizer = wx.BoxSizer(wx.VERTICAL)
		sizer.AddStretchSpacer()
		sizer.Add(wx.StaticText(panel, label = "This looks good"),
			1, wx.ALL, border = 5)

		image = wx.StaticBitmap(panel)
		image.SetBitmap(wx.Bitmap("test.png"))
		sizer.Add(image, 1, wx.ALL, border = 5)

		sizer.Add(wx.StaticText(panel, label = "This looks bad"),
			0, wx.ALL, border = 5)

		image = wx.StaticBitmap(panel, style = wx.SUNKEN_BORDER)
		image.SetBitmap(wx.Bitmap("test.png"))
		sizer.Add(image, 0, wx.ALL, border = 5)

		sizer.Add(wx.StaticText(panel, label = "This looks half bad"),
			1, wx.ALL, border = 5)

		image = wx.StaticBitmap(panel, style = wx.SUNKEN_BORDER)
		image.SetBitmap(wx.Bitmap("test.png"))
		sizer.Add(image, 1, wx.ALL, border = 5)

		sizer.AddStretchSpacer()
		panel.SetSizer(sizer)
		self.frame.Show()
		return True


def main():
	"""Main entry point."""
	app = App(redirect = False)
	app.MainLoop()
	print "main() finished running."


if __name__ == "__main__":
	main()


 	  	 
