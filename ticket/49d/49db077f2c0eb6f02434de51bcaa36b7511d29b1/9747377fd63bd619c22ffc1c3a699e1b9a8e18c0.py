#!/usr/bin/env python
import wx
import wx.lib.dialogs

class MyFrame(wx.Frame):
	def __init__(self, parent, id, title):
		wx.Frame.__init__(self, parent, id, title, size=(300,200))
		self.panel = wx.Panel(self, -1)
		
		box = wx.BoxSizer()
		for i in (1,2):
			text = wx.TextCtrl(self.panel, 1, style=wx.TE_MULTILINE|
				wx.TE_RICH|wx.TE_READONLY|wx.NO_BORDER)
			text.AppendText(u'test \u65e5\u672c')
			box.Add(text,1,flag=wx.EXPAND)
			setattr(self, "text%d" % i, text)

		self.button = wx.Button(self.panel, -1, "Choose Font...")
		self.Bind(wx.EVT_BUTTON, self.setFont, self.button)
		
		grid = wx.FlexGridSizer(2,1,10,10)
		grid.AddGrowableRow(1)
		grid.AddGrowableCol(0)
		grid.Add(self.button,border=4,flag=wx.ALL)
		grid.Add(box,flag=wx.EXPAND)
		
		self.panel.SetSizer(grid)
		self.panel.SetAutoLayout(True)
		self.Layout()
		self.CreateStatusBar()

	def setFont(self, event):
		res = wx.lib.dialogs.fontDialog(self)
		if res.accepted:
			self.text1.SetStyle(0, 1000, wx.TextAttr(font=res.font))
			ur = res.font.GetNativeFontInfoUserDesc()
			self.SetStatusText(ur)
			n = wx.NativeFontInfo()
			n.FromUserString(ur)
			self.text2.SetStyle(0, 1000, wx.TextAttr(font=wx.FontFromNativeInfo(n)))
			self.text1.Update()
			self.text2.Update()

app = wx.PySimpleApp()
frame = MyFrame(None, -1, "Test")
frame.Show(True)
app.MainLoop()

 	  	 
