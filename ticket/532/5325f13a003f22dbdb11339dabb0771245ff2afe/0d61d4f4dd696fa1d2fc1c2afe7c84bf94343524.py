#!/usr/bin/env python

from wx import *
from wx.aui import *
from wx.lib.scrolledpanel import *

demonstrate_goodhack = False # Demonstrate the good Windows hack (Tab/Shift-Tab accelerators)
demonstrate_badhack = False  # Demonstrate the bad Windows hack (AuiNotebook.OnSetFocus handler)
show_where_focus_is = False  # Periodically print where focus is

def app():
	return _app

class PayrollApp(App):
	def GetAppName(self):
		return 'Payroll'
	def GetAppVersion(self):
		return '0.1'
	def warn(self, msg=''):
		'''Emit a warning message.'''
		self.mainframe.SetStatusText(msg)
	def debug(self, msg):
		print msg
	def OnInit(self):
		global _app
		_app = self
		print 'Platform', Platform
		self.mainframe = MainFrame(self)
		self.SetTopWindow(self.mainframe)
		self.mainframe.Show()
		if show_where_focus_is:
			global cl
			def debug_focus():
				w = Window.FindFocus()
				app().debug('FOCUS: ' + repr(w) + ' ' + (w.GetName() if w else ''))
				cl.Restart()
			cl = CallLater(3000, debug_focus)
		return True

import re
def r(pattern, opts=''):
	if type(pattern) == type(u''): pattern = str(pattern)
	if type(pattern) != type(''): return pattern
	flags = 0
	odict = { 'i': re.I, 'l': re.L, 'm': re.M, 's': re.S, 'x': re.X, 'u': re.U }
	for option in opts:
		flags |= odict[option]
	return re.compile(pattern, flags)

def s(pattern, rep, str, count=0, opts=''):
	return r(pattern, opts).sub(rep, str, count)

def debug_event(label, event):
	if isinstance(event, KeyEvent):
		app().debug('%s(%s key=%d%s)' % (label, event.GetEventObject().GetName(), event.GetKeyCode(), ((' [' if event.HasModifiers() else '') + ('s' if event.ShiftDown() else '') + ('c' if event.ControlDown() else '') + ('C' if event.CmdDown() else '') + ('a' if event.AltDown() else '') + ('m' if event.MetaDown() else '') + (']' if event.HasModifiers() else ''))))
	else:
		app().debug('%s(%s)' % (label, event.GetEventObject().GetName()))

class TabEvent():
	def __init__(self, o, m=0): self.o, self.m = o, m
	def GetKeyCode(self): return WXK_TAB
	def GetModifiers(self): return self.m
	def ShiftDown(self): return self.m & MOD_SHIFT
	def GetEventObject(self): return self.o

class MainFrame(Frame):
	def __init__(self, app):
		self.app = app
		self.app.debug('mainframe.__init__')
		Frame.__init__(self, None, title=app.GetAppName(), pos=(50, 50), size=(1000, 700))
		self.Bind(EVT_CLOSE, self.OnClose)

		# The following data is a tuple of the menu name and a list of its items.
		# Each item is either a dictionary, or a tuple of submenu name and a list of its items.
		# Each dictionary can have the following entries and the corresponding effects:
		#  id - The WX id to be used for menu items and toolbar items (mandatory)
		#  menu - Text appearing in menu (including accelerator details) (mandatory)
		#  help - Short help text for tooltips or the status bar
		#  cmd - Callable to be called when the item is chosen
		#  tool - Text appearing the in toolbar
		#  icon - Image appearing in the toolbar
		#  tree - Text to appear in the TreeCtrl widget (e.g. 'New')
		#  title - Text to appear as the page caption (e.g. 'New Employee')
		#  cls - Panel class to instantiate in notebook when the item is chosen
		#  able - Callable that tests whether or not this item should be enabled
		#
		# Note: When building the TreeCtrl, only the 4th element of this
		# list is examined (i.e. The Action menu).

		# Hacklet: Normally, we'd want Ctrl-Tab and Ctrl-Shift-Tab for cycling
		# through pages because on Windows (and hence Linux) Alt-Tab is used
		# for cycling through applications. However, on MacOSX, Ctrl-Tab is
		# automatically converted into Command-Tab which is what is used on
		# MacOSX for cycling through applications. So, on MacOSX, we use Alt
		# there instead.
		tabmod = 'Alt' if Platform == '__WXMAC__' else 'Ctrl'
		self.cmd_data = [
			('&File', [
				dict(id=NewId(), menu='&Quit\tCtrl-Q', help='Quit this application', cmd=self.OnFileQuitCmd, tool='Quit', icon=ART_QUIT)
			]),
			('&Edit', [
				dict(id=NewId(), menu='C&ut\tCtrl-X', help='Cut selected text into the clipboard', cmd=self.OnXXXCmd, tool='Cut', icon=ART_CUT),
				dict(id=NewId(), menu='&Copy\tCtrl-C', help='Copy selected text into the clipboard', cmd=self.OnXXXCmd, tool='Copy', icon=ART_COPY),
				dict(id=NewId(), menu='&Paste\tCtrl-V', help='Paste the text in the clipboard', cmd=self.OnXXXCmd, tool='Paste', icon=ART_PASTE)
			]),
			('&Page', [
				dict(id=NewId(), menu='&Close\tCtrl-W', help='Close the currently selected page', cmd=self.OnPageCloseCmd, tool='Close', icon=ART_DELETE, able=lambda:self._has_page(0)),
				dict(id=NewId(), menu='&Tree\tCtrl-T', help='Move focus to the tree panel', cmd=self.OnPageTreeCmd),
				dict(id=NewId(), menu='&Previous Page\t%s-Shift-Tab' % tabmod, help='Move focus to the previous page', cmd=self.OnPagePrevCmd, tool='Prev', icon=ART_GO_BACK, able=lambda:self._has_page(1)),
				dict(id=NewId(), menu='&Next Page\t%s-Tab' % tabmod, help='Move focus to the next page', cmd=self.OnPageNextCmd, tool='Next', icon=ART_GO_FORWARD, able=lambda:self._has_page(1)),
				dict(id=NewId(), menu='Page &0\tCtrl-0', help='Move focus to page 0', cmd=self.OnPagePage0Cmd, able=lambda:self._has_page(0)),
				dict(id=NewId(), menu='Page &1\tCtrl-1', help='Move focus to page 1', cmd=self.OnPagePage1Cmd, able=lambda:self._has_page(1)),
				dict(id=NewId(), menu='Page &2\tCtrl-2', help='Move focus to page 2', cmd=self.OnPagePage2Cmd, able=lambda:self._has_page(2)),
				dict(id=NewId(), menu='Page &3\tCtrl-3', help='Move focus to page 3', cmd=self.OnPagePage3Cmd, able=lambda:self._has_page(3)),
				dict(id=NewId(), menu='Page &4\tCtrl-4', help='Move focus to page 4', cmd=self.OnPagePage4Cmd, able=lambda:self._has_page(4)),
				dict(id=NewId(), menu='Page &5\tCtrl-5', help='Move focus to page 5', cmd=self.OnPagePage5Cmd, able=lambda:self._has_page(5)),
				dict(id=NewId(), menu='Page &6\tCtrl-6', help='Move focus to page 6', cmd=self.OnPagePage6Cmd, able=lambda:self._has_page(6)),
				dict(id=NewId(), menu='Page &7\tCtrl-7', help='Move focus to page 7', cmd=self.OnPagePage7Cmd, able=lambda:self._has_page(7)),
				dict(id=NewId(), menu='Page &8\tCtrl-8', help='Move focus to page 8', cmd=self.OnPagePage8Cmd, able=lambda:self._has_page(8)),
				dict(id=NewId(), menu='Page &9\tCtrl-9', help='Move focus to page 9', cmd=self.OnPagePage9Cmd, able=lambda:self._has_page(9))
			]),
			('&Action', [
				('&Employee', [
					dict(id=NewId(), menu='&Edit\tCtrl-E', help='Edit an existing employee', tree='Edit', title='Edit Employee', cls=EditEmployeeScreen, tool='EditEmp', icon=ART_NEW)
				])
			])
		]

		# Hack: On Windows, to take complete control of tab order inside an
		# AuiNotebook, it is not sufficient (as it is on other platforms)
		# to avoid TAB_TRAVERSAL in panels, use WANTS_CHARS in controls, and
		# handle tab keys yourself in the EVT_CHAR handlers of all controls.
		#
		# This is because tabbing and shift-tabbing when a ComboBox or Button
		# has focus does not produce an EVT_CHAR event as it would for other
		# controls. Instead, keyboard focus just moves to the AuiNotebook
		# named 'control'.
		#
		# A failed attempt at a workaround was to use the AuiNotebook's
		# EVT_SET_FOCUS handler to send focus to the appropriate widget.
		# This also required the ComboBoxes and Buttons to save themselves
		# in their EVT_SET_FOCUS handlers for use in the AuiNotebook's
		# EVT_SET_FOCUS handler.
		#
		# However, since any knowledge of the tab key is lost, it can't tell
		# if the keystroke was a Tab or a Shift-Tab key. Assuming the most
		# useful case, it's assumed to be a Tab key. But this means that it
		# is only half of a solution. So Tab could be made to work but not
		# Shift-Tab.
		#
		# So, instead, make Tab and Shift-Tab accelerators on Windows. This
		# could have been done with an explicit AcceleratorTable to keep it
		# out of the menu, but that would probably require replicating all
		# of the accelerator information already contained in the menu items
		# above. That seems absurd. Can AcceleratorTables be pushed rather
		# than just set? That would be useful here. Maybe get, append, set?

		if Platform == '__WXMSW__' and demonstrate_goodhack:
			self.cmd_data[2][1].append(dict(id=NewId(), menu='Previous Field\tShift-Tab', help='Move focus to the previous field', cmd=self.OnShiftTabCmd, able=lambda:self._has_page(0)))
			self.cmd_data[2][1].append(dict(id=NewId(), menu='Next Field\tTab', help='Move focus to the next field', cmd=self.OnTabCmd, able=lambda:self._has_page(0)))

		self._build_menus()
		self._build_tools()
		self._build_panel()
		self._enable_cmds()
		self.CreateStatusBar()
		# Hacklet: On Linux, the app starts with nothing having keyboard
		# focus. On other platforms, the TreeCtrl starts with focus. The
		# following statement makes Linux behave like the other platforms.
		if Platform == '__WXGTK__':
			self.tree.SetFocus()

	def _has_page(self, n):
		return self.book and self.book.GetPageCount() > n

	def _add_page(self, paneclass, label):
		if paneclass and self.book:
			pane = paneclass(self.book)
			self.book.AddPage(pane, pane.get_caption(), True)
			self._enable_cmds()

	def _enable_cmds(self):
		for menu_item, cmd_items in self.cmd_data:
			self._enable_cmd(cmd_items)

	def _enable_cmd(self, cmd_items):
		for cmd_item in cmd_items:
			self._enable_cmd_item(cmd_item)

	def _enable_cmd_item(self, item):
		if type(item) == dict:
			if 'able' in item:
				able = item['able']()
				item['_parent'].Enable(item['id'], able)
				if 'tool' in item and 'icon' in item and ('cmd' in item or 'cls' in item):
					self.tool_bar.EnableTool(item['id'], able)
		elif type(item) == tuple:
			subname, subitems = item
			self._enable_cmd(subitems)
		else:
			raise Exception('Unexpected cmd data: %s' % repr(item))

	def _build_menus(self):
		self.menu_bar = MenuBar()
		for menu_name, menu_items in self.cmd_data:
			self.menu_bar.Append(menu=self._build_menu(menu_items), title=menu_name)
		self.SetMenuBar(self.menu_bar)

	def _build_menu(self, menu_items):
		menu = Menu()
		for menu_item in menu_items:
			self._add_menu_item(menu, menu_item)
		return menu

	def _add_menu_item(self, menu, item):
		if type(item) == dict:
			menuitem = menu.Append(id=item['id'], text=item['menu'], help=item['help'])
			item['_parent'] = menu
			if 'cmd' in item:
				self.Bind(EVT_MENU, item['cmd'], menuitem)
			if 'cls' in item:
				def addpage(event): self._add_page(item['cls'], item['title'])
				self.Bind(EVT_MENU, addpage, menuitem)
		elif type(item) == tuple:
			subname, subitems = item
			menu.AppendMenu(-1, text=subname, submenu=self._build_menu(subitems))
		else:
			raise Exception('Unexpected cmd data: %s' % repr(item))

	def _build_tools(self):
		style = 0
		style |= TB_FLAT
		style |= TB_DOCKABLE
		style |= TB_HORIZONTAL
		self.tool_bar = self.CreateToolBar(style=style)
		self.tool_bar_icon_size = (16, 16)
		self.tool_bar.SetToolBitmapSize(self.tool_bar_icon_size)
		for menu_name, cmd_items in self.cmd_data:
			self._build_tool_palette(cmd_items)
		self.tool_bar.Realize()

	def _build_tool_palette(self, cmd_items):
		for cmd in cmd_items:
			self._add_tool(cmd)

	def _add_tool(self, item):
		if type(item) == dict:
			if 'tool' in item and 'icon' in item and ('cmd' in item or 'cls' in item):
				image = item['icon']
				if type(image) in [unicode, str]: # e.g. Standard icon wx.ART_NEW == u'wxART_NEW'
					image = ArtProvider.GetBitmap(image, ART_TOOLBAR, self.tool_bar_icon_size)
				tool = self.tool_bar.AddLabelTool(id=item['id'], label=item['tool'], bitmap=image, shortHelp=item['help'], longHelp=item['help'])
				if 'cmd' in item:
					cmd = item['cmd']
				else:
					def addpage(event): self._add_page(item['cls'], item['title'])
					cmd = addpage
				self.Bind(EVT_TOOL, cmd, tool)
		elif type(item) == tuple:
			subname, subitems = item
			self._build_tool_palette(subitems)
		else:
			raise Exception('Unexpected cmd data: %s' % repr(item))

	def _build_panel(self):
		'''Build the main window's contents.'''
		splitter_flags = SP_LIVE_UPDATE | SP_3D
		# Split nav+info to the left, notebook to the right
		self.vsplit = SplitterWindow(self, style=splitter_flags)
		# Disallow complete removal of a pane or user won't be able to retrieve it
		self.vsplit.SetMinimumPaneSize(1)
		# When growing, only grow the right (main) pane
		self.vsplit.SetSashGravity(0.0)

		# Split nav to the top and info to the bottom
		self.hsplit = SplitterWindow(self.vsplit, style=splitter_flags)
		# Disallow complete removal of a pane or user won't be able to retrieve it
		self.hsplit.SetMinimumPaneSize(1)
		# When growing, only grow the top (tree) pane
		self.hsplit.SetSashGravity(1.0)

		# Create the top-left panel to contain the tree widget
		p1 = Panel(self.hsplit, style=BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_tree(p1), 1, EXPAND | ALL, 3)
		p1.SetSizer(sz)
		# Create the bottom-left panel to contain random info
		p2 = Panel(self.hsplit, style=BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_info(p2), 1, EXPAND | ALL, 3)
		p2.SetSizer(sz)
		# Create the right panel to contain the AuiNotebook
		p3 = Panel(self.vsplit, style=BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_book(p3), 1, EXPAND | ALL, 3)
		p3.SetSizer(sz)

		# Set splitter sash positions
		self.hsplit.SplitHorizontally(p1, p2, 400)
		# Initial sash position for a nested SplitterWindow doesn't work so...
		CallAfter(self.hsplit.SetSashPosition, 400)
		self.vsplit.SplitVertically(self.hsplit, p3, 300)

	def create_tree(self, panel):
		style = TR_DEFAULT_STYLE | TR_HIDE_ROOT
		self.tree = TreeCtrl(panel, style=style)
		self.build_tree()
		self.Bind(EVT_TREE_ITEM_ACTIVATED, self.OnTreeItemActivated, self.tree)
		self.tree.ExpandAll()
		return self.tree

	def build_tree(self):
		self._build_tree_cmds()

	def _build_tree_cmds(self):
		self.tree_root = self.tree.AddRoot(self.app.GetAppName())
		self.tree_first = None
		for menu_item, cmd_items in self.cmd_data[3][1]: # The 'Action' menu
			label = s('&', '', menu_item)
			parent = self.tree.AppendItem(self.tree_root, label)
			self._build_tree_cmd(parent, label, cmd_items)

	def _build_tree_cmd(self, parent, label, cmd_items):
		for cmd_item in cmd_items:
			self._build_tree_cmd_item(parent, label, cmd_item)

	def _build_tree_cmd_item(self, parent, label, item):
		if type(item) == dict:
			if 'tree' in item and 'cls' in item:
				# Add the item and save a pane class with each item
				tree_item = self.tree.AppendItem(parent, item['tree'])
				id = label + '/' + item['title']
				self.tree.SetPyData(tree_item, (item['cls'], id))
				# Select the first top-level child in the tree (by default)
				if self.tree_first == None:
					self.tree_first = tree_item
					self.tree.SelectItem(self.tree_first)
		elif type(item) == tuple:
			subname, subitems = item
			sublabel = subname
			parent = self.tree.AppendItem(parent, sublabel)
			self._build_tree_cmd(parent, label + '/' + sublabel , subitems)
		else:
			raise Exception('Unexpected cmd data: %s' % repr(item))

	def create_info(self, panel):
		self.info_panel = Panel(panel, style=0) # Disable TAB_TRAVERSAL
		return self.info_panel

	def create_book(self, panel):
		self.book = AuiNotebook(panel, style=AUI_NB_DEFAULT_STYLE | AUI_NB_CLOSE_ON_ALL_TABS | AUI_NB_WINDOWLIST_BUTTON)
		self.book.Bind(EVT_AUINOTEBOOK_PAGE_CLOSE, self.OnAuiNotebookPageClose)
		self.book.Bind(EVT_AUINOTEBOOK_PAGE_CHANGED, self.OnAuiNotebookPageChanged)
		# BadHack: On Windows, catch focus lost to Auinotebook and pass it on to the correct control.
		if Platform == '__WXMSW__' and demonstrate_badhack:
			self.book.Bind(EVT_SET_FOCUS, self.OnBookSetFocus)
		return self.book

	# Hack: We make Tab and Shift-Tab accelerators on Windows
	def OnTabCmd(self, event):
		self.app.debug('MainFrame.OnTabCmd()')
		self.app.debug("HACK: Tab accelerator needed because Tab in ComboBox/Button doesn't produce an EVT_CHAR event")
		if hasattr(self, 'current_page') and hasattr(self, 'current_ctrl'):
			handle_tab(TabEvent(self.current_ctrl), self.current_page.tab_order)

	# Hack: We make Tab and Shift-Tab accelerators on Windows
	def OnShiftTabCmd(self, event):
		self.app.debug('MainFrame.OnShiftTabCmd()')
		self.app.debug("HACK: Shift-Tab accelerator needed because Shift-Tab in ComboBox/Button doesn't produce an EVT_CHAR event")
		if hasattr(self, 'current_page') and hasattr(self, 'current_ctrl'):
			handle_tab(TabEvent(self.current_ctrl, MOD_SHIFT), self.current_page.tab_order)

	# BadHack: On Windows, catch the focus that is 'lost' to the AuiNotebook
	# when Tab is pressed in a ComboBox or Button. But Shift-Tab isn't
	# solved by this, hence the Tab and Shift-Tab accelerator hack.
	def OnBookSetFocus(self, event):
		app().debug('BADHACK: Tab in ComboBox/Button sends focus here rather than to next control')
		debug_event('MainFrame.OnBookSetFocus()', event)
		if hasattr(self, 'current_ctrl'):
			# Note: We have no way of knowing if the Tab key that
			# got us here was a Shift-Tab or not.
			handle_tab(TabEvent(self.current_ctrl), self.current_page.tab_order)

	def OnAuiNotebookPageClose(self, event):
		debug_event('MainFrame.OnAuiNotebookPageClose', event)
		self._enable_cmds()

	def OnAuiNotebookPageChanged(self, event):
		debug_event('MainFrame.OnAuiNotebookPageChanged', event)
		self._enable_cmds()

	def OnClose(self, event):
		self.app.debug('MainFrame.OnClose()')
		event.Skip()

	def OnTreeItemActivated(self, event):
		debug_event('MainFrame.OnTreeItemActivated', event)
		item = event.GetItem()
		if item:
			data = self.tree.GetPyData(item)
			if data: self._add_page(*data)
		event.Skip()

	def OnFileQuitCmd(self, event):
		self.app.debug('MainFrame.OnQuitCmd()')
		self.Close()

	def OnPageCloseCmd(self, event):
		debug_event('MainFrame.OnPageCloseCmd', event)
		if self.book:
			page = self.book.GetSelection()
			if page >= 0 and page < self.book.GetPageCount():
				self.book.DeletePage(page)

	def OnPageTreeCmd(self, event):
		app().debug('MainFrame.OnPageTreeCmd()')
		if self.tree:
			self.tree.SetFocus()

	def OnPageNextCmd(self, event):
		app().debug('MainFrame.OnPageNextCmd()')
		if self.book:
			pages = self.book.GetPageCount()
			if pages > 0:
				page = self.book.GetSelection()
				self.book.SetSelection(page + 1 if page >= 0 and page < self.book.GetPageCount() - 1 else 0)

	def OnPagePrevCmd(self, event):
		app().debug('MainFrame.OnPagePrevCmd()')
		if self.book:
			pages = self.book.GetPageCount()
			if pages > 0:
				page = self.book.GetSelection()
				self.book.SetSelection(page - 1 if page > 0 and page < self.book.GetPageCount() else pages - 1)

	def OnPageNCmd(self, n):
		'''Move focus to page n of the AuiNotebook.'''
		self.app.debug('MainFrame.OnPagePage%dCmd()' % n)
		if self.book:
			pages = self.book.GetPageCount()
			if pages > n:
				self.book.SetSelection(n)

	def OnPagePage0Cmd(self, event): self.OnPageNCmd(0)
	def OnPagePage1Cmd(self, event): self.OnPageNCmd(1)
	def OnPagePage2Cmd(self, event): self.OnPageNCmd(2)
	def OnPagePage3Cmd(self, event): self.OnPageNCmd(3)
	def OnPagePage4Cmd(self, event): self.OnPageNCmd(4)
	def OnPagePage5Cmd(self, event): self.OnPageNCmd(5)
	def OnPagePage6Cmd(self, event): self.OnPageNCmd(6)
	def OnPagePage7Cmd(self, event): self.OnPageNCmd(7)
	def OnPagePage8Cmd(self, event): self.OnPageNCmd(8)
	def OnPagePage9Cmd(self, event): self.OnPageNCmd(9)
	def OnXXXCmd(self, event): pass

def SetTextWidth(textctrl, length):
	size = textctrl.GetSize()
	size.width = (length + 1) * textctrl.GetCharWidth()
	textctrl.SetInitialSize(size)

class TextEntry(TextCtrl):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=WANTS_CHARS|TE_PROCESS_TAB, validator=DefaultValidator, name=TextCtrlNameStr, width=15):
		TextCtrl.__init__(self, parent, id, value, pos, size, style, validator, name)
		SetTextWidth(self, width)
		self.Bind(EVT_SET_FOCUS, self.OnSetFocus)

	def OnSetFocus(self, event=None):
		'''When receiving focus, select all of the text.'''
		if event: debug_event('TextEntry.OnSetFocus', event)
		CallAfter(self.SetSelection, 0, len(self.GetValue()))
		if event: event.Skip()

	def SetValue(self, val):
		if val is None: val = ''
		TextCtrl.SetValue(self, val)

class PhoneEntry(TextEntry):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=WANTS_CHARS|TE_PROCESS_TAB, validator=DefaultValidator, name=TextCtrlNameStr, width=15):
		TextEntry.__init__(self, parent, id, value, pos, size, style, validator, name, width)

class IntEntry(TextEntry):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=WANTS_CHARS|TE_PROCESS_TAB, validator=DefaultValidator, name=TextCtrlNameStr, width=15):
		TextEntry.__init__(self, parent, id, value, pos, size, style, validator, name, width)

class DateEntry(TextEntry):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=WANTS_CHARS|TE_PROCESS_TAB, validator=DefaultValidator, name=DatePickerCtrlNameStr, width=10):
		TextEntry.__init__(self, parent, id, value, pos, size, style, validator, name, width)

class FlagEntry(CheckBox):
	def __init__(self, parent, id=-1, label=EmptyString, pos=DefaultPosition, size=DefaultSize, style=WANTS_CHARS, validator=DefaultValidator, name=CheckBoxNameStr):
		CheckBox.__init__(self, parent, id, label, pos, size, style, validator, name)

class Table:
	@classmethod
	def load(cls, data):
		cls._loaded = [cls(r) for r in data]
		cls._by_name = dict([(r.name, r) for r in cls._loaded])
		cls._by_code = dict([(r.code, r) for r in cls._loaded])
		cls._by_id = dict([(r.id, r) for r in cls._loaded])
	@classmethod
	def get(cls, key):
		if hasattr(key, 'upper') and cls._by_code.has_key(key.upper()):
			return cls._by_code[key.upper()]
		if cls._by_name.has_key(key):
			return cls._by_name[key]
		if cls._by_id.has_key(key):
			return cls._by_id[key]
		return None
	@classmethod
	def get_all(cls):
		return cls._loaded

class T_title(Table):
	def __init__(self, r): self.id, self.code, self.name = r
class T_gender(Table):
	def __init__(self, r): self.id, self.code, self.name = r
class T_marital_status(Table):
	def __init__(self, r): self.id, self.code, self.name = r
class T_state(Table):
	def __init__(self, r): self.id, self.code, self.name = r
class T_country(Table):
	def __init__(self, r): self.id, self.code, self.name = r
class T_language(Table):
	def __init__(self, r): self.id, self.code, self.name = r
class T_period(Table):
	def __init__(self, r): self.id, self.code, self.name = r
class T_leaving_reason(Table):
	def __init__(self, r): self.id, self.code, self.name = r

T_title.load([(1, 'M', 'Mr'), (2, 'S', 'MS'), (3, 'I', 'Miss'), (4, 'R', 'Mrs')])
T_gender.load([(1, 'M', 'Male'), (2, 'F', 'Female'), (3, 'O', 'Other')])
T_marital_status.load([(1, 'M', 'Married'), (2, 'S', 'Single'), (3, 'O', 'Other')])
T_state.load([(1, 'NSW', 'NSW'), (2, 'VIC', 'VIC'), (3, 'TAS', 'TAS')])
T_country.load([(1, 'AU', 'Australia'), (2, 'NZ', 'New Zealand')])
T_language.load([(1, 'EN', 'English'), (2, 'ZH', 'Mandarin')])
T_period.load([(1, 'D', 'Days'), (2, 'W', 'Weeks'), (3, 'M', 'Months')])
T_leaving_reason.load([(1, 'R', 'Resigned'), (2, 'T', 'Retired'), (3, 'D', 'Dismissed')])

# Hack: On Windows, this function must be called in the EVT_SET_FOCUS
# handlers of all controls to keep track of focus so that when it gets
# lost in the AuiNotebook, we can get it back on track.
def save_focus(frame, page, ctrl):
	frame.current_page = page
	frame.current_ctrl = ctrl
	app().debug('HACK SAVE: ' + repr(page) + ' ' + repr(ctrl))

class CodeEntry(ComboBox):
	def __init__(self, parent, tableclass, id=-1, value='', pos=DefaultPosition, size=DefaultSize, choices=[], style=CB_DROPDOWN|WANTS_CHARS|TE_PROCESS_TAB, validator=DefaultValidator, name=TextCtrlNameStr, width=5):
		if choices == []:
			self.tableclass = tableclass
			#self.tableclass.load(app().db)
			self.items = self.tableclass.get_all()
			choices = [i.name for i in self.items]
			self.choices = choices
		ComboBox.__init__(self, parent, id, value, pos, size, choices, style, validator, name)
		SetTextWidth(self, width + 3) # The popup button takes up some room
		self.lastkey = None
		self.Bind(EVT_KEY_DOWN, self.OnKeyDown)
		self.Bind(EVT_CHAR, self.OnChar)
		self.Bind(EVT_TEXT, self.OnText)
		# Hacklet: On MacOSX, ComboBox doesn't receive EVT_SET_FOCUS
		# but it does receive EVT_CHILD_FOCUS (wxpython-2.8.8.1).
		if Platform == '__WXMAC__':
			self.Bind(EVT_CHILD_FOCUS, self.OnChildFocus)
		self.Bind(EVT_SET_FOCUS, self.OnSetFocus)

	def OnChildFocus(self, event):
		debug_event('CodeEntry.OnChildFocus', event)
		txt = event.GetWindow()
		if isinstance(txt, TextCtrl):
			self.OnSetFocus()
		event.Skip()

	def OnSetFocus(self, event=None):
		'''When receiving focus, select all of the text.'''
		if event: debug_event('CodeEntry.OnSetFocus', event)
		CallAfter(self.SetMark, 0, len(self.GetValue()))
		if event: event.Skip()

	def SetID(self, id):
		if id is None:
			self.SetValue('')
			return
		item = self.tableclass.get(id)
		if item:
			self.SetValue(item.name)

	def GetID(self):
		txt = self.GetValue().lower()
		if len(txt) == 0:
			return None
		for item in self.items:
			if txt == item.name.lower():
				return item.id
		raise Exception('No such id: ' + self.GetValue())

	def _complete(self):
		if self.lastkey == WXK_BACK: return
		txt = self.GetValue().lower()
		l = len(txt)
		if l == 0:
			return
		for item in self.items:
			if l == len(item.name) and txt == item.name[0:l].lower():
				return
			if l < len(item.name) and txt == item.name[0:l].lower():
				self.SetValue(item.name)
				CallAfter(self.SetMark, l, len(item.name))
				return
		for item in self.items:
			if l <= len(item.code) and txt == item.code[0:l].lower():
				self.SetValue(item.name)
				CallAfter(self.SetMark, l, len(item.name))
				return

	def _nav(self, init, dir):
		txt = self.GetValue()
		if len(txt) == 0:
			self.SetValue(self.items[init].name)
		nitems = len(self.items)
		for i in range(nitems):
			if txt == self.items[i].name:
				self.SetValue(self.items[dir(i)].name)
				break

	def OnKeyDown(self, event):
		debug_event('CodeEntry.OnKeyDown', event)
		event.Skip()

	def OnChar(self, event):
		debug_event('CodeEntry.OnChar', event)
		key = event.GetKeyCode()
		self.lastkey = key
		if key == WXK_UP:
			self._nav(-1, lambda i: i - 1)
		elif key == WXK_DOWN:
			self._nav(0, lambda i: i + 1 if i < len(self.items) - 1 else 0)
		else:
			event.Skip()

	def OnText(self, event):
		app().debug('CodeEntry.OnText(%s)' % self.GetValue())
		# Not working on Linux yet because Linux has extra EVT_TEXT events
		# whenever selected text is replaced by the user's keystroke.
		# MacOSX and Windows platforms do this in a single EVT_TEXT event.
		self._complete()
		event.Skip()

def handle_tab(event, widgets):
	debug_event('handle_tab', event)
	if event.GetKeyCode() != WXK_TAB:
		return False
	# Hack: On Linux, Tab (with or without modifiers) does not work
	# as accelerators. Instead, they end up here so we redirect them
	# to the appropriate accelerator handlers.
	if Platform == '__WXGTK__':
		if event.ControlDown():
			if event.ShiftDown():
				app().debug("HACK: Ctrl-Shift-Tab accelerator didn't work. Redirecting to OnPagePrevCmd()")
				app().mainframe.OnPagePrevCmd(None)
			else:
				app().debug("HACK: Ctrl-Tab accelerator didn't work. Redirecting to OnPageNextCmd()")
				app().mainframe.OnPageNextCmd(None)
			return
	if not (event.GetModifiers() in [0, MOD_SHIFT]):
		return False
	shift = event.ShiftDown()
	# Move between widgets
	src = event.GetEventObject()
	nwidgets = len(widgets)
	for i in range(nwidgets):
		if src == widgets[i]:
			widgets[i - 1 if shift else (i + 1) % nwidgets].SetFocus()
			return True
	return False

class EditEmployeeScreen(ScrolledPanel):
	def get_caption(self): return 'EditEmployee'
	def __init__(self, parent, id=-1, pos=DefaultPosition, size=DefaultSize, style=0, name='scrolledpanel'):
		ScrolledPanel.__init__(self, parent, id, pos, size, style, name)
		self.employee = None

		# Create widgets
		self.employee_search_label = StaticText(self, label='Employee')
		self.employee_search_ctrl = TextEntry(self, width=10, name='employee_search')
		self.employee_search_result_label = StaticText(self, label='')

		self.name_label = StaticText(self, label='Name')
		self.title_ctrl = CodeEntry(self, T_title, width=4, name='title')
		self.first_names_ctrl = TextEntry(self, name='first_names')
		self.family_name_ctrl = TextEntry(self, name='family_name')

		self.birth_date_label = StaticText(self, label='Birth')
		self.birth_date_ctrl = DateEntry(self, width=10, name='birth_date')
		self.gender_label = StaticText(self, label='Gender')
		self.gender_ctrl = CodeEntry(self, T_gender, width=6, name='gender')
		self.marital_status_label = StaticText(self, label='Marital')
		self.marital_status_ctrl = CodeEntry(self, T_marital_status, width=9, name='marital_status')

		self.preferred_name_label = StaticText(self, label='Alias')
		self.preferred_name_ctrl = TextEntry(self, name='preferred_name')
		self.maiden_name_label = StaticText(self, label='Maiden')
		self.maiden_name_ctrl = TextEntry(self, name='maiden_name')

		self.address_label = StaticText(self, label='Address')
		self.address_1_ctrl = TextEntry(self, name='address_1')
		self.address_2_ctrl = TextEntry(self, name='address_2')
		self.address_3_ctrl = TextEntry(self, name='address_3')

		self.post_code_label = StaticText(self, label='Postcode')
		self.post_code_ctrl = TextEntry(self, width=4, name='post_code')
		self.state_label = StaticText(self, label='State')
		self.state_ctrl = CodeEntry(self, T_state, width=3, name='state')
		self.country_label = StaticText(self, label='Country')
		self.country_ctrl = CodeEntry(self, T_country, width=10, name='country')

		self.home_telephone_label = StaticText(self, label='Phone')
		self.home_telephone_ctrl = TextEntry(self, width=10, name='home_telephone')
		self.office_telephone_label = StaticText(self, label='W')
		self.office_telephone_ctrl = TextEntry(self, width=10, name='office_telephone')
		self.mobile_telephone_label = StaticText(self, label='M')
		self.mobile_telephone_ctrl = TextEntry(self, width=10, name='mobile_telephone')
		self.fax_telephone_label = StaticText(self, label='F')
		self.fax_telephone_ctrl = TextEntry(self, width=10, name='fax_telephone')

		self.email_address_label = StaticText(self, label='Email')
		self.email_address_ctrl = TextEntry(self, width=30, name='email_address')

		self.emergency_contact_label = StaticText(self, label='Emergency')
		self.emergency_contact_ctrl = TextEntry(self, name='emergency_contact')
		self.emergency_contact_telephone_label = StaticText(self, label='Phone')
		self.emergency_contact_telephone_ctrl = TextEntry(self, width=15, name='emergency_contact_telephone')

		self.start_date_label = StaticText(self, label='Joined')
		self.start_date_ctrl = DateEntry(self, width=10, name='start_date')
		self.leaving_date_label = StaticText(self, label='Left')
		self.leaving_date_ctrl = DateEntry(self, width=10, name='leaving_date')

		self.nationality_country_label = StaticText(self, label='Nationality')
		self.nationality_country_ctrl = CodeEntry(self, T_country, width=10, name='nationality_country')
		self.birth_country_label = StaticText(self, label='Birth')
		self.birth_country_ctrl = CodeEntry(self, T_country, width=10, name='birth_country')
		self.birth_place_label = StaticText(self, label='Place')
		self.birth_place_ctrl = TextEntry(self, name='birth_place')

		self.first_language_label = StaticText(self, label='Language')
		self.first_language_ctrl = CodeEntry(self, T_language, width=10, name='first_language')

		self.health_general_label = StaticText(self, label='Health')
		self.health_general_ctrl = TextEntry(self, name='health_general')
		self.health_specific_label = StaticText(self, label='(Specific)')
		self.health_specific_ctrl = TextEntry(self, name='health_specific')

		self.retirement_age_label = StaticText(self, label='Ret. Age')
		self.retirement_age_ctrl = IntEntry(self, width=3, name='retirement_age')
		self.probation_label = StaticText(self, label='Probation')
		self.probation_ctrl = IntEntry(self, width=3, name='probation')
		self.probation_period_ctrl = CodeEntry(self, T_period, width=6, name='probation_period')

		self.notice_label = StaticText(self, label='Notice')
		self.notice_ctrl = IntEntry(self, width=3, name='notice')
		self.notice_period_ctrl = CodeEntry(self, T_period, width=6, name='notice_period')
		self.notice_given_label = StaticText(self, label='Notice\nGiven')
		self.notice_given_ctrl = IntEntry(self, width=3, name='notice_given')
		self.notice_given_period_ctrl = CodeEntry(self, T_period, width=6, name='notice_given_period')
		self.rehire_flag_ctrl = FlagEntry(self, label='Rehire', name='rehire_flag')
		self.continuous_service_flag_ctrl = FlagEntry(self, label='Continuous', name='continuous_service_flag')

		self.type_of_licence_label = StaticText(self, label='Licence')
		self.type_of_licence_ctrl = TextEntry(self, width=3, name='type_of_licence')
		self.endorsements_label = StaticText(self, label='Endorsement')
		self.endorsements_ctrl = TextEntry(self, name='endorsements')
		self.hobbies_label = StaticText(self, label='Hobbies')
		self.hobbies_ctrl = TextEntry(self, name='hobbies')

		self.previous_start_date_label = StaticText(self, label='Prior Start')
		self.previous_start_date_ctrl = DateEntry(self, width=10, name='previous_start_date')
		self.previous_leaving_date_label = StaticText(self, label='Left')
		self.previous_leaving_date_ctrl = DateEntry(self, width=10, name='previous_leaving_date')
		self.previous_employee_number_label = StaticText(self, label='Employee')
		self.previous_employee_number_ctrl = TextEntry(self, width=6, name='previous_employee_number')
		self.leaving_reason_label = StaticText(self, label='Reason')
		self.leaving_reason_ctrl = CodeEntry(self, T_leaving_reason, width=25, name='leaving_reason')

		self.save_button = Button(self, label='Save', name='save_button')

		self.tab_order = [
			self.employee_search_ctrl,
			self.title_ctrl,
			self.first_names_ctrl,
			self.family_name_ctrl,
			self.birth_date_ctrl,
			self.gender_ctrl,
			self.marital_status_ctrl,
			self.preferred_name_ctrl,
			self.maiden_name_ctrl,
			self.address_1_ctrl,
			self.address_2_ctrl,
			self.address_3_ctrl,
			self.post_code_ctrl,
			self.state_ctrl,
			self.country_ctrl,
			self.home_telephone_ctrl,
			self.office_telephone_ctrl,
			self.mobile_telephone_ctrl,
			self.fax_telephone_ctrl,
			self.email_address_ctrl,
			self.emergency_contact_ctrl,
			self.emergency_contact_telephone_ctrl,
			self.start_date_ctrl,
			self.leaving_date_ctrl,
			self.nationality_country_ctrl,
			self.birth_country_ctrl,
			self.birth_place_ctrl,
			self.first_language_ctrl,
			self.health_general_ctrl,
			self.health_specific_ctrl,
			self.retirement_age_ctrl,
			self.probation_ctrl,
			self.probation_period_ctrl,
			self.notice_ctrl,
			self.notice_period_ctrl,
			self.notice_given_ctrl,
			self.notice_given_period_ctrl,
			self.rehire_flag_ctrl,
			self.continuous_service_flag_ctrl,
			self.type_of_licence_ctrl,
			self.endorsements_ctrl,
			self.hobbies_ctrl,
			self.previous_start_date_ctrl,
			self.previous_leaving_date_ctrl,
			self.previous_employee_number_ctrl,
			self.leaving_reason_ctrl,
			self.save_button
		]

		for w in self.tab_order:
			w.Bind(EVT_CHAR, self.OnChar)
			w.Bind(EVT_KEY_DOWN, self.OnKeyDown)
			# Hack/BadHack: On Windows we need to keep track of focus ourselves.
			if Platform == '__WXMSW__' and (demonstrate_goodhack or demonstrate_badhack):
				w.Bind(EVT_SET_FOCUS, self.OnCtrlSetFocus)
		self.save_button.Bind(EVT_BUTTON, self.OnSave)

		vsz = BoxSizer(VERTICAL)

		gsz = FlexGridSizer(cols=2, vgap=3, hgap=3)

		def row(lhs, rhs):
			gsz.Add(lhs, 0, ALL, 2)
			hsz = BoxSizer(HORIZONTAL)
			# Hacklet: On MacOSX, there is extra border around compound widgets
			# like ComboBox and CheckBox. To compensate, add a border around
			# TextCtrl widgets. It isn't needed on Linux or Windows.
			needsit = Platform == '__WXMAC__'
			for w in rhs:
				hsz.Add(w, 0, ALL, 3 if needsit and isinstance(w, TextEntry) else 0)
				hsz.AddSpacer(2)
			gsz.Add(hsz, 0, 0, 0)

		row(self.employee_search_label,
			[self.employee_search_ctrl, self.employee_search_result_label])

		# Name: title_ctrl, first_names_ctrl, family_name_ctrl
		row(self.name_label, [self.title_ctrl, self.first_names_ctrl, self.family_name_ctrl])

		# Birth: birth_date_ctrl, Gender: gender_ctrl, Marital: marital_status_ctrl
		row(self.birth_date_label, [self.birth_date_ctrl, self.gender_label, self.gender_ctrl,
			self.marital_status_label, self.marital_status_ctrl])

		# Alias: preferred_name_ctrl, Maiden: maiden_name_ctrl
		row(self.preferred_name_label, [self.preferred_name_ctrl,
			self.maiden_name_label, self.maiden_name_ctrl])

		# Address: address_[123]_ctrl
		row(self.address_label, [self.address_1_ctrl, self.address_2_ctrl, self.address_3_ctrl])

		# Postcode: post_code_ctrl, state_ctrl, country_ctrl
		row(self.post_code_label, [self.post_code_ctrl, self.state_label, self.state_ctrl,
			self.country_label, self.country_ctrl])

		# Phone: home_telephone_ctrl, office_telephone_ctrl, mobile_telephone_ctrl, fax_telephone_ctrl
		row(self.home_telephone_label, [self.home_telephone_ctrl,
			self.office_telephone_label, self.office_telephone_ctrl,
			self.mobile_telephone_label, self.mobile_telephone_ctrl,
			self.fax_telephone_label, self.fax_telephone_ctrl])

		# Email: email_address_ctrl
		row(self.email_address_label, [self.email_address_ctrl])

		# Next of kin: emergency_contact_ctrl, emergency_contact_telephone_ctrl
		row(self.emergency_contact_label, [self.emergency_contact_ctrl,
			self.emergency_contact_telephone_label, self.emergency_contact_telephone_ctrl])

		# Start: start_date_ctrl, leaving_date_ctrl
		row(self.start_date_label, [self.start_date_ctrl,
			self.leaving_date_label, self.leaving_date_ctrl])

		# Nationality: nationality_country_ctrl, birth_country_ctrl, birth_place_ctrl
		row(self.nationality_country_label, [self.nationality_country_ctrl,
			self.birth_country_label, self.birth_country_ctrl,
			self.birth_place_label, self.birth_place_ctrl])

		# Language: first_language_ctrl
		row(self.first_language_label, [self.first_language_ctrl])

		# Health: health_general_ctrl, health_specific_ctrl
		row(self.health_general_label, [self.health_general_ctrl,
			self.health_specific_label, self.health_specific_ctrl])

		# Retirement/Probation: retirement_age_ctrl, probation_ctrl, probation_period_ctrl
		row(self.retirement_age_label, [self.retirement_age_ctrl,
			self.probation_label, self.probation_ctrl, self.probation_period_ctrl])

		# Notice: notice_ctrl, notice_period_ctrl, notice_given_ctrl,
		# notice_given_period_ctrl, rehire_flag_ctrl,
		# continuous_service_flag_ctrl
		row(self.notice_label, [self.notice_ctrl, self.notice_period_ctrl,
			self.notice_given_label, self.notice_given_ctrl, self.notice_given_period_ctrl,
			self.rehire_flag_ctrl, self.continuous_service_flag_ctrl])

		# Licence: type_of_licence_ctrl, endorsements_ctrl, hobbies_ctrl
		row(self.type_of_licence_label, [self.type_of_licence_ctrl,
			self.endorsements_label, self.endorsements_ctrl,
			self.hobbies_label, self.hobbies_ctrl])

		# Previous: previous_start_date_ctrl, previous_leaving_date_ctrl,
		# previous_employee_number_ctrl, leaving_reason_ctrl
		row(self.previous_start_date_label, [self.previous_start_date_ctrl,
			self.previous_leaving_date_label, self.previous_leaving_date_ctrl,
			self.previous_employee_number_label, self.previous_employee_number_ctrl])

		row(self.leaving_reason_label, [self.leaving_reason_ctrl])

		vsz.Add(gsz, 1, EXPAND | ALL, 2)
		vsz.Add(self.save_button, 0, ALL, 5)

		self.SetSizer(vsz)
		self.SetupScrolling()

	# Hack/BadHack: On Windows we need to keep track of focus ourselves.
	def OnCtrlSetFocus(self, event):
		save_focus(app().mainframe, self, event.GetEventObject())
		event.Skip()

	def OnSave(self, event=None):
		app().debug('EditEmployeeScreen.OnSave()')

	def OnKeyDown(self, event):
		debug_event('EditEmployeeScreen.OnKeyDown', event)
		# Hacklet: On MacOSX, ComboBox doesn't get EVT_CHAR events for
		# TAB characters but it does get EVT_KEY_DOWN events.
		event.Skip()
		return
		#if Platform == '__WXMAC__' and event.GetKeyCode() == WXK_TAB:
		#	if not handle_tab(event, self.tab_order):
		#		event.Skip()
		#else:
		#	event.Skip()

	def OnChar(self, event):
		debug_event('EditEmployeeScreen.OnChar', event)
		key = event.GetKeyCode()
		src = event.GetEventObject()
		if key == WXK_TAB:
			if not handle_tab(event, self.tab_order):
				event.Skip()
		elif key == WXK_RETURN:
			if src == self.employee_search_ctrl:
				self.do_employee_search(self.employee_search_ctrl.GetValue())
			else:
				self.OnSave()
		else:
			event.Skip()

	def do_employee_search(self, term):
		app().debug('EditEmployeeScreen.do_employee_search(%s)' % term)

def main(redirect=False):
	PayrollApp(redirect=redirect).MainLoop()

if __name__ == '__main__':
	main()

