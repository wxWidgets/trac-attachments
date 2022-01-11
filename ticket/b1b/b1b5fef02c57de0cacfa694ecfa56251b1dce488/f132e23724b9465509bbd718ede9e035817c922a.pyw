#! /usr/bin/env python

'''Short script to illustrate Windows menu bitmap problem after SetItemLabel'''

# contact Dan Koch <kochdb@ornl.gov> for questions


import wx


class MyFrame(wx.Frame):

	def __init__(self):
		
		wx.Frame.__init__(self, None, size=(300,300))
		
		self.menubar = wx.MenuBar()
		menu = wx.Menu()

		self.label = 'Label 1'
		item = wx.MenuItem(menu, -1, self.label)
		
		self.bmp = wx.Bitmap('/Users/ko5/Desktop/folder.png', wx.BITMAP_TYPE_PNG) # change filepath as needed
		item.SetBitmap(self.bmp)
				
		menu.AppendItem(item)
		self.menubar.Append(menu, 'File')
		self.SetMenuBar(self.menubar)

		self.Bind(wx.EVT_MENU, self.OnFile, item)
		
		
	def OnFile(self, event):

		item_id = self.menubar.FindMenuItem('File', self.label)
		item = self.menubar.FindItemById(item_id)

		if self.label == 'Label 1':
			self.label = 'Label 2'

		else:
			self.label = 'Label 1'
			
		item.SetItemLabel(self.label)
		
		item.SetBitmap(self.bmp) # uncomment this line to see workaround, must invoke twice


if __name__ == '__main__':
	app = wx.PySimpleApp()
	frame = MyFrame()
	frame.Show()
	app.MainLoop()

