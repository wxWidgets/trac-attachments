#! /usr/bin/env python

'''Short script to illustrate Help menu problem on Mac OS X'''

# contact Dan Koch <kochdb@ornl.gov> for questions


import wx


class MyFrame(wx.Frame):

	def __init__(self):
		
		wx.Frame.__init__(self, None, size=(300,300))
		
		self.menubar = wx.MenuBar()
		menu = wx.Menu()
		item = wx.MenuItem(menu, -1, 'Menu Item')
		
		menu.AppendItem(item)
		self.menubar.Append(menu, 'Help') # change 'Help' to 'File' to see difference
		self.SetMenuBar(self.menubar)

		item.Enable(False) # disable the menu item

		self.Bind(wx.EVT_MENU_OPEN, self.OnMenu)
		
		
	def OnMenu(self, event):
	
		item_id = self.menubar.FindMenuItem('Help', 'Menu Item') # change 'Help' to 'File' here too
		item = self.menubar.FindItemById(item_id)
		print item.IsEnabled() # run from command line to see status
		

if __name__ == '__main__':
	app = wx.PySimpleApp()
	frame = MyFrame()
	frame.Show()
	app.MainLoop()

