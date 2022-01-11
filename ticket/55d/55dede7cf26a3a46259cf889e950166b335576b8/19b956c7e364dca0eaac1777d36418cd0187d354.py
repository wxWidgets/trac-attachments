# -*- coding: utf-8 -*-

import wx

class TestApp(wx.App):
	def OnInit(self):
		frame = MainFrame()
		self.SetTopWindow(frame)
		frame.Show(True)
		return True

class MainFrame(wx.Frame):
	def __init__(self):
		title = "Virtual ListCtrl SetItemCount Bug Test"
		wx.Frame.__init__(self, None, wx.ID_ANY, title, style=wx.DEFAULT_FRAME_STYLE | wx.NO_FULL_REPAINT_ON_RESIZE)
		
		main_panel = wx.Panel(self)
		
		# This is the list of items that will be used by the virtual listctrl
		self.items = [str(i) for i in range(1, 10)]
		
		self.listctrl = TestListCtrl(main_panel, wx.ID_ANY, style=wx.BORDER_SUNKEN | wx.LC_REPORT | wx.LC_VIRTUAL)
		self.listctrl.InsertColumn(1, "A Column")
		self.listctrl.SetItemCount(9)
		
		usage_text = wx.StaticText(main_panel, wx.ID_ANY, "Use number keys 0-9 to SetItemCount to that number")
		
		main_sizer = wx.BoxSizer(wx.VERTICAL)
		main_sizer.Add(usage_text, 0, wx.ALL, border=5)
		main_sizer.Add(self.listctrl, 1, wx.EXPAND | wx.ALL, border=1)
		main_panel.SetSizer(main_sizer)
		
		self.listctrl.Bind(wx.EVT_CHAR, self.OnCharPressed)
	
	def OnCharPressed(self, event):
		# If keypress is a number 0-9 set listctrl item count to that number
		if event.GetKeyCode() in xrange(48, 58):
			self.listctrl.SetItemCount(int(chr(event.GetKeyCode()), 10))
		else:
			event.Skip()

class TestListCtrl(wx.ListCtrl):
	def OnGetItemText(self, n, col):
		return self.GetTopLevelParent().items[n]

if __name__ == "__main__":
	app = TestApp()
	app.MainLoop()
 	  	 
