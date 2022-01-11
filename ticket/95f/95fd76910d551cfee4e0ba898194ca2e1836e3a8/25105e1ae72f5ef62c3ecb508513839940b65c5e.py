import sys
import wx

class Test(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self, parent=None, title="Testing List Controls with LC_LIST and Item Properties", size=(800,400))
		
		panel = wx.Panel(self)
		
		LC_LIST_label = wx.StaticText(panel, label="wx.ListCtrl (LC_LIST)")
		LC_LIST_list = TestList(panel, style=wx.LC_LIST)
		
		LC_REPORT_label = wx.StaticText(panel, label="wx.ListCtrl (LC_REPORT)")
		LC_REPORT_list = TestList(panel, style=wx.LC_REPORT)
		
		LC_LIST_sizer = wx.BoxSizer(wx.VERTICAL)
		LC_LIST_sizer.Add(LC_LIST_label)
		LC_LIST_sizer.Add(LC_LIST_list, proportion=1, flag=wx.EXPAND)
		
		LC_REPORT_sizer = wx.BoxSizer(wx.VERTICAL)
		LC_REPORT_sizer.Add(LC_REPORT_label)
		LC_REPORT_sizer.Add(LC_REPORT_list, proportion=1, flag=wx.EXPAND)
		
		sizer = wx.BoxSizer(wx.HORIZONTAL)
		sizer.Add(LC_LIST_sizer, proportion=1, flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.BOTTOM, border=5)
		sizer.Add(LC_REPORT_sizer, proportion=1, flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.BOTTOM, border=5)
		panel.SetSizer(sizer)
		
		self.Center()
		self.Show()
		
class TestList(wx.ListCtrl):
	def __init__(self, parent, style):
		wx.ListCtrl.__init__(self, parent, style=style)
		
		if style == wx.LC_REPORT:
			self.InsertColumn(0, "Column")
			
		font = wx.SystemSettings_GetFont(wx.SYS_DEFAULT_GUI_FONT)
		font.SetPointSize(16)
		
		for x in range(1,51):
			label = "Item %i" % x
			
			idx = self.InsertStringItem(sys.maxint, label)
			
			self.SetItemTextColour(idx, wx.RED)
			self.SetItemBackgroundColour(idx, wx.BLUE)
			self.SetItemFont(idx, font)
			
		self.Refresh()
		
app = wx.App(0)
Test()
app.MainLoop()