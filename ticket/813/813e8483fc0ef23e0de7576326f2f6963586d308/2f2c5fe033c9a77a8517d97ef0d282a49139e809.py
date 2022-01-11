#!/usr/bin/env python

from wx import *
from wx.aui import *

class TestApp(App):
	def GetAppName(self):
		return 'Test'
	def GetAppVersion(self):
		return '0.1'
	def OnInit(self):
		self.mainframe = MainFrame(self)
		self.SetTopWindow(self.mainframe)
		return True

class MainFrame(Frame):
	def __init__(self, app):
		self.app = app
		Frame.__init__(self, None, -1, app.GetAppName(), size=(800, 600), pos=(100, 100))
		self.build_panel()
		self.Show()
	def build_panel(self):
		self.vsplit = SplitterWindow(self, style=SP_LIVE_UPDATE)
		self.hsplit = SplitterWindow(self.vsplit, style=SP_LIVE_UPDATE)
		p1 = Panel(self.hsplit, style=BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_tree(p1), 1, EXPAND, 3)
		p1.SetSizer(sz)
		p2 = Panel(self.hsplit, style=BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_info(p2), 1, EXPAND, 3)
		p2.SetSizer(sz)
		self.hsplit.SplitHorizontally(p1, p2, 500) # The sash position is ignored here
		self.hsplit.SetSashPosition(500)           # The sash position is ignored here too
		#CallAfter(self.hsplit.SetSashPosition, 500) # But this does work
		p3 = Panel(self.vsplit, style=BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_book(p3), 1, EXPAND, 3)
		p3.SetSizer(sz)
		self.vsplit.SplitVertically(self.hsplit, p3, 300)
	def create_tree(self, panel):
		self.tree = TreeCtrl(panel)
		self.root = self.tree.AddRoot('Blah')
		self.tree.AppendItem(self.root, 'Blah1')
		self.tree.AppendItem(self.root, 'Blah2')
		return self.tree
	def create_info(self, panel):
		self.info = Panel(panel)
		return self.info
	def create_book(self, panel):
		self.book = AuiNotebook(panel)
		return self.book

if __name__ == '__main__':
	TestApp(redirect=False).MainLoop()
