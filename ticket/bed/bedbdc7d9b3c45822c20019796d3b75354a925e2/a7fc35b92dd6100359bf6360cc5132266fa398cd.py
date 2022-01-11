import sys
import wx
from wx.lib.agw import ultimatelistctrl as ULC

class Test(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self, parent=None, title="Testing UltimateListCtrl with LC_LIST and Fonts", size=(800,600))
		
		panel = wx.Panel(self)
		
		ulc_label = wx.StaticText(panel, label="ULC.UltimateListCtrl")
		self.ulc = ULC.UltimateListCtrl(panel, style=0, agwStyle=wx.LC_LIST)
		
		sizer = wx.BoxSizer(wx.VERTICAL)
		sizer.Add(ulc_label, flag=wx.TOP|wx.LEFT, border=5)
		sizer.Add(self.ulc, proportion=1, flag=wx.EXPAND|wx.TOP|wx.LEFT, border=5)
		panel.SetSizer(sizer)
		
		self.Center()
		self.Show()
		
		self.Populate()
		
	def Populate(self):
		font = wx.SystemSettings_GetFont(wx.SYS_DEFAULT_GUI_FONT)
		font.SetPointSize(16)
		
		for x in range(1,11):
			idx = self.ulc.InsertStringItem(sys.maxint, "Item %ia" % x)
			self.ulc.SetItemTextColour(idx, wx.RED)
			self.ulc.SetItemFont(idx, font)
			self.ulc.SetItemBackgroundColour(idx, wx.YELLOW) # Only this gets set
			
			idx = self.ulc.InsertStringItem(sys.maxint, "Item %ib" % x)
			self.ulc.SetItemBackgroundColour(idx, wx.YELLOW)
			self.ulc.SetItemTextColour(idx, wx.RED)
			self.ulc.SetItemFont(idx, font) # Only this gets set
			
			idx = self.ulc.InsertStringItem(sys.maxint, "Item %ic" % x)
			self.ulc.SetItemFont(idx, font)
			self.ulc.SetItemBackgroundColour(idx, wx.YELLOW)
			self.ulc.SetItemTextColour(idx, wx.RED) # Only this gets set
			
		self.Refresh()
		
app = wx.App(0)
Test()
app.MainLoop()