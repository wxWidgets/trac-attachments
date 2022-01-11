import wx

class TaskBarIcon(wx.TaskBarIcon):
	def __init__(self):
		wx.TaskBarIcon.__init__(self)
		
		bmp = wx.EmptyImage(16,16).ConvertToBitmap()
		icon = wx.EmptyIcon()
		icon.CopyFromBitmap(bmp)
		
		self.SetIcon(icon, "Test Menu")
		self.Bind(wx.EVT_TASKBAR_RIGHT_UP, self.OnRightClick)
		
	def OnRightClick(self, event):
		menu = wx.Menu()
		
		item = wx.MenuItem(menu, 0, "Some Item")
		item.Enable(False)
		menu.AppendItem(item)
		
		item = wx.MenuItem(menu, 0, "Some Item")
		menu.AppendItem(item)
		item.Enable(False)
		
		item = wx.MenuItem(menu, 2, "Exit")
		menu.AppendItem(item)
		
		wx.EVT_MENU(menu, 0, self.DoSomething)
		wx.EVT_MENU(menu, 1, self.DoSomething)
		wx.EVT_MENU(menu, 2, self.OnExit)
		self.PopupMenu(menu)
		
	def DoSomething(self, event):
		print "This should not be printed"
	
	def OnExit(self, event):
		self.RemoveIcon()
		self.Destroy()

if __name__ == "__main__":		
	app = wx.App(0)
	frame = TaskBarIcon()
	app.MainLoop()
 	  	 
