import wx
import wx.stc
import os, re, os.path
import random

print wx.VERSION


class drFindReplaceInFilesDialog(wx.Frame):
	def __init__(self, parent, id, title, IsReplace = 0):
		height = 420
		if IsReplace:
			height = 512
		wx.Frame.__init__(self, parent, id, title, wx.Point(50, 50), wx.Size(640, height), wx.DEFAULT_DIALOG_STYLE | wx.MAXIMIZE_BOX | wx.THICK_FRAME | wx.RESIZE_BORDER)
		
		self.parent = parent
		
		self.panel = drFindReplaceInFilesPanel(self, id, title, parent, IsReplace)
		self.panel.closing = 0
		self.SetSizeHints(355, height)

class MyComboBox (wx.ComboBox):
	def __init__(self, parent, id):
		wx.ComboBox.__init__(self, parent, id, "", wx.DefaultPosition, wx.Size(350, -1));
		self.parent = parent
		self.Bind(wx.EVT_KILL_FOCUS,  self.OnFillListBox1)
		self.Bind(wx.EVT_SET_FOCUS,  self.OnFillListBox2)
		
		
	def OnFillListBox1 (self, event):
		if self.parent.allow:
			print "Kill Focus event"
		event.Skip()
	
	def OnFillListBox2 (self, event):
		if self.parent.allow:
			print "Set Focus event"
		event.Skip()
		#pass
		#event.Skip()

class drFindReplaceInFilesPanel(wx.Panel):
	def __init__(self, parent, id, title, grandparent, IsReplace = 0):
		wx.Panel.__init__(self, parent, id)
		self.allow = False
		
		self.parent = parent
		self.grandparent = grandparent
		
		self.ID_BROWSE = 1001
		self.ID_SELECT = 1002
		self.ID_TEXT = 1003

		self.ID_CHK_REGEX = 1010
		self.ID_CREATERE = 1011
		
		self.ID_POPUP_FIND = 1020
		self.ID_RESULTS = 1030

		self.IsReplace = IsReplace		
		
		
		self.txtSearchFor = MyComboBox(self, self.ID_TEXT)

		if (IsReplace):
			self.ID_POPUP_REPLACE = 1021
			
			self.ID_UNDO_REPLACE = 1040
		
			self.txtReplaceWith = wx.ComboBox(self, -1, "", wx.DefaultPosition, wx.Size(350, -1))		

		self.txtPattern = wx.ComboBox(self, -1, "", wx.DefaultPosition, wx.DefaultSize)
		self.txtDirectory = wx.ComboBox(self, -1, "", wx.DefaultPosition, wx.Size(350, -1))

		self.boxresults = wx.ListBox(self, self.ID_RESULTS, wx.DefaultPosition, wx.Size(200, -1))

		self.btnPopUpFind = wx.Button(self, self.ID_POPUP_FIND, "Edit")		
		if (IsReplace):
			self.btnPopUpReplace = wx.Button(self, self.ID_POPUP_REPLACE, "Edit")
		self.btnBrowse = wx.Button(self, self.ID_BROWSE, "Browse")
		self.btnFind = wx.Button(self, wx.ID_OK, "&Search")
		self.btnCreateRE = wx.Button(self, self.ID_CREATERE, " &Create ")
		self.chkRegularExpression = wx.CheckBox(self, self.ID_CHK_REGEX, "RegularExpression")
		self.chkMatchCase = wx.CheckBox(self, -1, "Match Case")
		self.chkSubDirectories = wx.CheckBox(self, -1, "Subdirectories")
		if (IsReplace):
			self.chkPromptOnReplace  = wx.CheckBox(self, -1, "Prompt on Replace")
			self.chkPromptOnReplace.SetValue(1)
		self.btnSelect = wx.Button(self, self.ID_SELECT, "S&elect")
		if (IsReplace):
			self.btnUndo = wx.Button(self, self.ID_UNDO_REPLACE, "Undo Replace")
		self.btnCancel = wx.Button(self, wx.ID_CANCEL, "&Close")

		
				
		self.chkRegularExpression.SetValue(1)
		self.btnCreateRE.Enable(True)
		self.chkMatchCase.SetValue(1)
		self.chkSubDirectories.SetValue(1)				

		self.statusBar = wx.StatusBar(self, -1)		
		self.statusBar.SetFieldsCount(3)
		self.statusBar.SetStatusWidths ([-3, -12, -3])
		self.txtDirectory.SetValue("test1")
		self.txtDirectory.Append("test")
		self.txtDirectory.Append("test1")
		
		self.txtPattern.SetValue("test")
		self.txtPattern.Append("test")
		self.txtPattern.Append("test1")

		self.txtSearchFor.Append("test")
		self.txtSearchFor.Append("test1")
		self.txtSearchFor.SetValue("test")


		if (IsReplace):
			self.SetHistory(self.txtReplaceWith, ["test, test1"])
			self.txtReplaceWith.Append("test")
			self.txtReplaceWith.Append("test1")
			self.txtReplaceWith.SetValue("test")
		


		commandSizer = wx.BoxSizer(wx.VERTICAL)
		commandSizer.Add((0, 5), 0, wx.ALL, 0)
		commandSizer.Add(self.btnPopUpFind, 0, wx.ALL, 0)
		if (IsReplace):
			commandSizer.Add((0, 3), 0, wx.ALL, 0)
			commandSizer.Add(self.btnPopUpReplace, 0, wx.ALL, 0)
		commandSizer.Add((0, 29), 0, wx.ALL, 0)
		commandSizer.Add(self.btnBrowse, 0, wx.ALL, 0)
		commandSizer.Add((0, 20), 0, wx.ALL, 0)
		commandSizer.Add(self.btnFind, 0, wx.ALL, 0)

		commandSizer.Add((0, 25), 0, wx.ALL, 0)
		commandSizer.Add(self.btnCreateRE, 0, wx.ALL, 0)
		commandSizer.Add((0, 5), 0, wx.ALL, 0)

		commandSizer.Add(self.chkRegularExpression, 0, wx.ALL, 0)
		commandSizer.Add((0, 25), 0, wx.ALL, 0)
		commandSizer.Add(self.chkMatchCase, 0, wx.ALL, 0)
		commandSizer.Add((0, 5), 0, wx.ALL, 0)
		commandSizer.Add(self.chkSubDirectories, 0, wx.ALL, 0)
		if IsReplace:
			commandSizer.Add((0, 5), 0, wx.ALL, 0)
			commandSizer.Add(self.chkPromptOnReplace, 0, wx.ALL, 0)
		commandSizer.Add((0, 25), 0, wx.ALL, 0)
		commandSizer.Add(self.btnSelect, 0, wx.ALL, 0)
		if IsReplace:
			commandSizer.Add((0, 25), 0, wx.ALL, 0)
			commandSizer.Add(self.btnUndo, 0, wx.SHAPED)
		commandSizer.Add((0, 15), 0, wx.ALL, 0)
		commandSizer.Add(self.btnCancel, 0, wx.ALL, 0)

		
		topSizer = wx.FlexGridSizer(3, 2, 5, 5)
		topSizer.AddGrowableCol(1)
		topSizer.Add(wx.StaticText(self, -1, "Search For: "), 0)
		topSizer.Add(self.txtSearchFor, 1, wx.GROW)
		if (IsReplace):
			topSizer.Add(wx.StaticText(self, -1, "Replace With: "), 0)
			topSizer.Add(self.txtReplaceWith, 1, wx.GROW)
		topSizer.Add(wx.StaticText(self, -1, "File Pattern:"), 0)
		topSizer.Add(self.txtPattern, 1, wx.GROW)
		topSizer.Add(wx.StaticText(self, -1, "Directory:"), 0)
		topSizer.Add(self.txtDirectory, 1, wx.GROW)
		
		
		leftSizer = wx.BoxSizer(wx.VERTICAL)
		leftSizer.Add(topSizer, 0, wx.EXPAND | wx.ALL, 5)
		leftSizer.Add(self.boxresults, 1, wx.EXPAND | wx.ALL, 5)

		newSizer = wx.BoxSizer(wx.HORIZONTAL)
		newSizer.Add(leftSizer,1, wx.EXPAND | wx.ALL, 10)
		newSizer.Add(commandSizer,0, wx.ALIGN_TOP | wx.ALL, 10)
		lastSizer = wx.BoxSizer(wx.VERTICAL)
		lastSizer.Add(newSizer,1, wx.EXPAND | wx.ALL, 0)
		lastSizer.Add(self.statusBar, 0, wx.EXPAND | wx.ALL, 0)
		self.SetSizer(lastSizer)

		self.txtSearchFor.SetFocus()
		
		self.Bind(wx.EVT_BUTTON,  self.OnSearch, id=wx.ID_OK)
		self.Bind(wx.EVT_BUTTON,  self.OnSelect, id=self.ID_SELECT)
		self.Bind(wx.EVT_COMBOBOX,  self.OnFillListBox2, id=self.ID_TEXT)
		#self.Bind(wx.EVT_KILL_FOCUS,  self.OnFillListBox1, id=self.ID_TEXT)
		self.allow = True

	def OnFillListBox1(self, event):
			print "FillListBox1"
			self.OnFillListBox(event)
	
	def OnFillListBox2(self, event):
			print "FillListBox2"
			self.OnFillListBox(event)

	def OnFillListBox(self, event):
			e = random.randint (3,7)
			t = []
			for i in range (e):
				t.append('Test%d' % i)
			self.boxresults.Set(t)

	def OnSelect(self, event):
			print "Select"
				
	def OnSearch(self, event):
			print "Search"

class DrApp(wx.App):

	def OnInit(self):
		
		frame = drFindReplaceInFilesDialog(None, 101, "DrFindReplaceInFiles")	
		
		frame.Show(True)

		self.SetTopWindow(frame)
		return True
	
	
if __name__ == '__main__':
	app = DrApp(0)
	app.MainLoop()

        

 	  	 
