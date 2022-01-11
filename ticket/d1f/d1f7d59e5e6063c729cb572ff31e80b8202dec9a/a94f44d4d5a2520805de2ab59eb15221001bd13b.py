import wx
from wx.lib.agw import ultimatelistctrl as ULC
import  wx.lib.mixins.listctrl  as  list_mix


class TimerFrame(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self, None, -1, size=(400,300), title='Time Out!')
		#This is the toolbar section, nothing else goes here
		self.panel=TimerPanel(self)
		TB_FLAGS = ( wx.TB_HORIZONTAL
					)
		icon_size = (32,32)
		self.toolbar=self.CreateToolBar(TB_FLAGS)
		
		
		
		new_bmp =  wx.ArtProvider.GetBitmap(wx.ART_NEW, wx.ART_TOOLBAR, icon_size)
		
		del_bmp=wx.ArtProvider.GetBitmap(wx.ART_DELETE, wx.ART_TOOLBAR, icon_size)
		
		self.toolbar.SetToolBitmapSize(icon_size)
		
		self.toolbar.AddSimpleTool(10, new_bmp, "New Timer", "Long help for 'New'")
		
		self.Bind(wx.EVT_TOOL, self.OnClickNew, id=10)
		
		self.toolbar.AddSimpleTool(20, del_bmp, "Delete Timer", "Delete the selected timer")
		
		self.Bind(wx.EVT_TOOL, self.OnClickDel, id=20)
		
		self.Centre()
		
		self.Show()
		
		self.toolbar.Realize()
	def OnClickNew(self, evt):
		self.AddTimer()
	
	
	def OnClickDel(self, evt):
		self.RemoveTimer()
	
	
	def AddTimer(self):
		timer_list=self.panel.GetTimerList()
		timer_list.AddTimer()
		
	def RemoveTimer(self):
		timer_element=self.panel.GetTimerList()
		timer=timer_element.GetSelectedItem()
		if timer is not None:
			timer_element.OnItemDeselected(None, timer)
			timer_element.DeleteItem(timer)
		
		
class TimerPanel(wx.Panel):
	def __init__(self,parent):
		wx.Panel.__init__(self, parent, -1, style=wx.WANTS_CHARS)
		self.timer_list=TimerElement(self)
		sizer = wx.BoxSizer(wx.VERTICAL)
		sizer.Add(self.timer_list, 1, wx.EXPAND)
		self.SetSizer(sizer)
	
		self.SetAutoLayout(True)
	def GetTimerList(self):
		return self.timer_list

class TimerElement(ULC.UltimateListCtrl, list_mix.ListCtrlAutoWidthMixin):
	def __init__(self, parent):
		ULC.UltimateListCtrl.__init__(self, parent, -1, 
		agwStyle=wx.LC_REPORT |wx.LC_NO_HEADER)
		list_mix.ListCtrlAutoWidthMixin.__init__(self)
		self.InsertColumn(0, "timername")
		self.SetColumnWidth(0, 175)
		
		self.length=0
		self.item=None
		
		self.attribute=wx.ListItemAttr()
		self.Bind(ULC.EVT_LIST_ITEM_SELECTED, self.OnItemSelected)
		self.Bind(ULC.EVT_LIST_ITEM_DESELECTED, self.OnItemDeselected)
	def AddTimer(self):
		self.Freeze()	
		new_timer='timer'+ `self.length`
		self.InsertStringItem(self.length, new_timer)
		timer=self.GetItem(self.length, 0)
		textctrl = wx.TextCtrl(self, -1, "00:00:00")
		timer.SetWindow(textctrl)
		self.SetItem(timer)
		
		self.length+=1
		self.Thaw()
		self.Update()
	
	def OnItemSelected(self, event):
		
		current_item = event.m_itemIndex
		self.item=current_item
		print self.item
		event.Skip()
		
	def OnItemDeselected(self, evt, index=None):
		if index is not None:
			current_index=index
			if current_index:
				self.item=current_index-1
				self.SetItemState(self.item, wx.LIST_STATE_SELECTED, wx.LIST_STATE_SELECTED)
			else:
				self.item=None
		else:	
			self.item=None
	def GetSelectedItem(self):
		return self.item
	
	

app=wx.App(redirect=False)
timer_frame=TimerFrame()
app.MainLoop()