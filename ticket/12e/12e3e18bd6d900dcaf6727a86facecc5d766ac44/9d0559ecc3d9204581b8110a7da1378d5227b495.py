import wx, wx.html

class TestFileSystemHandler(wx.FileSystemHandler):
	def init(self):
		wx.FileSystemHandler.init(self)

	def CanOpen(self, location):
		return True

	def OpenFile(self, fs, location):
		return None

wx.FileSystem_AddHandler(TestFileSystemHandler())

class HTMLWindow(wx.Frame):
	def init(self, parent, id, title, pos=wx.DefaultPosition, size=(120,80), style=wx.DEFAULT_FRAME_STYLE):
		wx.Frame.init(self, parent, -1, title, pos, size, style)
		htmlwin = wx.html.HtmlWindow(self)
		htmlwin.SetPage("HTML<img src='dummyloc:foo'>")

if __name__ == '__main__':
	app = wx.PySimpleApp()
	wnd = HTMLWindow(None, -1, "FileSystemHandler Test")
	wnd.Show(True)
	app.MainLoop()

