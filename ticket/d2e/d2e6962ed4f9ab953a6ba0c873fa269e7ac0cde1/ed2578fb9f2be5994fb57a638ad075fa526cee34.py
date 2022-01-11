import sys
import wx

class Test(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self, parent=None, title="wxListCtrl with LC_LIST and Invisible Fonts", size=(800,400))
		
		panel = wx.Panel(self)
		
		list_no_column_label = wx.StaticText(panel, label="wx.ListCtrl (No Column)")
		list_no_column = TestList(panel, insert_column=False)
		
		list_with_column_label = wx.StaticText(panel, label="wx.ListCtrl (With Column)")
		list_with_column = TestList(panel, insert_column=True)
		
		list_no_column_sizer = wx.BoxSizer(wx.VERTICAL)
		list_no_column_sizer.Add(list_no_column_label)
		list_no_column_sizer.Add(list_no_column, proportion=1, flag=wx.EXPAND)
		
		list_with_column_sizer = wx.BoxSizer(wx.VERTICAL)
		list_with_column_sizer.Add(list_with_column_label)
		list_with_column_sizer.Add(list_with_column, proportion=1, flag=wx.EXPAND)
		
		sizer = wx.BoxSizer(wx.HORIZONTAL)
		sizer.Add(list_no_column_sizer, proportion=1, flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.BOTTOM, border=5)
		sizer.Add(list_with_column_sizer, proportion=1, flag=wx.EXPAND|wx.TOP|wx.LEFT|wx.BOTTOM, border=5)
		panel.SetSizer(sizer)
		
		self.Center()
		self.Show()
		
class TestList(wx.ListCtrl):
	def __init__(self, parent, insert_column):
		wx.ListCtrl.__init__(self, parent, style=wx.LC_LIST)
		
		if insert_column:
			self.InsertColumn(0, "")
		
		self.Populate()
		
	def Populate(self):
		for x in range(1,51):
			label = "Item %i" % x
			
			if x % 2:
				font = wx.SystemSettings_GetFont(wx.SYS_DEFAULT_GUI_FONT)
			else:
				font = wx.Font(pointSize=8, family=wx.FONTFAMILY_DEFAULT, style=wx.FONTSTYLE_NORMAL, weight=wx.FONTWEIGHT_NORMAL)
			
			idx = self.InsertStringItem(sys.maxint, label)
			self.SetItemFont(idx, font)
			
		self.Refresh()
		
app = wx.App(0)
Test()
app.MainLoop()