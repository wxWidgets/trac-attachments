#!/usr/bin/env python

from wx import *
from wx.grid import *
from wx.aui import *
from wx.lib.mixins.listctrl import *
from wx.lib.scrolledpanel import *

def app():
	return _app

class TestApp(App):
	def GetAppName(self):
		return 'Payroll'
	def GetAppVersion(self):
		return '0.1'
	def warn(self, msg=''):
		self.mainframe.SetStatusText(msg)
	def OnInit(self):
		self.mainframe = MainFrame(self)
		self.SetTopWindow(self.mainframe)
		global _app
		_app = self
		self.mainframe.Show()
		return True

class NewEmployeeScreen(ScrolledPanel):
	def get_caption(self): return 'NewEmployee'
	def __init__(self, *args, **kwargs):
		ScrolledPanel.__init__(self, *args, **kwargs)
		self.t = StaticText(self, -1, self.get_caption())
		self.SetupScrolling()

def SetTextCtrlWidth(textctrl, length):
	size = textctrl.GetSize()
	size.width = (length + 1) * textctrl.GetCharWidth()
	textctrl.SetInitialSize(size)

class AutoWidthListCtrl(ListCtrl, ListCtrlAutoWidthMixin):
	'''Required by ListCtrlAutoWidthMixin. Seems to do nothing on Mac.'''
	def __init__(self, parent, id=-1, pos=DefaultPosition, size=DefaultSize, style=0):
		ListCtrl.__init__(self, parent, id, pos, size, style)
		ListCtrlAutoWidthMixin.__init__(self)

class TextEntry(TextCtrl):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=0, validator=DefaultValidator, name=TextCtrlNameStr, width=15):
		TextCtrl.__init__(self, parent, id, value, pos, size, style, validator, name)
		SetTextCtrlWidth(self, width)
		# Note: On MacOSX, ComboBox doesn't receive EVT_SET_FOCUS
		# but it does receive EVT_CHILD_FOCUS.
		if Platform == '__WXMAC__':
			self.Bind(EVT_CHILD_FOCUS, self.OnChildFocus)
		else:
			self.Bind(EVT_SET_FOCUS, self.OnSetFocus)

	def OnChildFocus(self, event):
		txt = event.GetWindow()
		if isinstance(txt, TextCtrl):
			self.OnSetFocus(event)

	def OnSetFocus(self, event):
		'''When receiving focus, select all of the text.'''
		CallAfter(self.SetSelection, 0, len(self.GetValue()))
		event.Skip()

	def SetValue(self, val):
		if val is None: val = ''
		TextCtrl.SetValue(self, val)

class PhoneEntry(TextEntry):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=0, validator=DefaultValidator, name=TextCtrlNameStr, width=15):
		TextEntry.__init__(self, parent, id, value, pos, size, style, validator, name, width)

class IntEntry(TextEntry):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=0, validator=DefaultValidator, name=TextCtrlNameStr, width=15):
		TextEntry.__init__(self, parent, id, value, pos, size, style, validator, name, width)

class DateEntry(TextEntry):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=0, validator=DefaultValidator, name=TextCtrlNameStr, width=10):
		TextEntry.__init__(self, parent, id, value, pos, size, style, validator, name, width)

class CodeEntry(ComboBox):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, choices=[], style=CB_DROPDOWN, validator=DefaultValidator, name=TextCtrlNameStr, width=5):
		ComboBox.__init__(self, parent, id, value, pos, size, choices, style, validator, name)
		SetTextCtrlWidth(self, width + 3) # The popup button takes up some room
		self.lastkey = None
		self.Bind(EVT_KEY_DOWN, self.OnKeyDown)
		self.Bind(EVT_TEXT, self.OnText)
		# Note: On MacOSX, ComboBox doesn't receive EVT_SET_FOCUS
		# but it does receive EVT_CHILD_FOCUS.
		if Platform == '__WXMAC__':
			self.Bind(EVT_CHILD_FOCUS, self.OnChildFocus)
		else:
			self.Bind(EVT_SET_FOCUS, self.OnSetFocus)

	def _complete(self):
		if self.lastkey == WXK_BACK:
			return
		txt = self.GetValue().lower()
		l = len(txt)
		if l == 0:
			return
		for item in self.choices:
			if l == len(item) and txt == item[0:l].lower():
				return
			if l < len(item) and txt == item[0:l].lower():
				self.SetValue(item)
				CallAfter(self.SetMark, l, len(item))
				return

	def _nav(self, init, dir):
		txt = self.GetValue()
		if len(txt) == 0:
			self.SetValue(self.choices[init])
		nitems = len(self.choices)
		for i in range(nitems):
			if txt == self.choices[i]:
				self.SetValue(self.choices[dir(i)])
				break

	def OnChildFocus(self, event):
		txt = event.GetWindow()
		if isinstance(txt, TextCtrl):
			self.OnSetFocus(event)

	def OnSetFocus(self, event):
		CallAfter(self.SetMark, 0, len(self.GetValue()))
		event.Skip()

	def OnKeyDown(self, event):
		key, ctrl = event.KeyCode, event.ControlDown()
		self.lastkey = key
		if key == WXK_UP:
			self._nav(-1, lambda i: i - 1)
		elif key == WXK_DOWN:
			self._nav(0, lambda i: i + 1 if i < len(self.items) - 1 else 0)
		else:
			event.Skip()

	def OnText(self, event):
		self._complete()
		event.Skip()

def set_tab_order(widgets): # XXX tab order - make this work...
	for i in xrange(len(widgets) - 1):
		widgets[i + 1].MoveAfterInTabOrder(widgets[i])

class EditEmployeeScreen(ScrolledPanel):
	def get_caption(self): return 'EditEmployee'
	def __init__(self, *args, **kwargs):
		ScrolledPanel.__init__(self, *args, **kwargs)
		self.employee = None

		# Create widgets
		self.employee_search_label = StaticText(self, -1, 'Employee:')
		self.employee_search_ctrl = TextEntry(self, 10)
		self.employee_search_result_label = StaticText(self, -1, '')
		self.name_label = StaticText(self, -1, 'Name:')
		self.title_ctrl = CodeEntry(self, choices='Mr Ms Miss Mrs Dr Sir'.split(), width=4)
		self.first_names_ctrl = TextEntry(self, width=15)
		self.family_name_ctrl = TextEntry(self, width=20)
		self.birth_date_label = StaticText(self, -1, 'Birth:')
		self.birth_date_ctrl = DateEntry(self, width=10)
		self.gender_label = StaticText(self, -1, 'Gender:')
		self.gender_ctrl = CodeEntry(self, choices='Male Female Other'.split(), width=6)
		self.marital_status_label = StaticText(self, -1, 'Marital:')
		self.marital_status_ctrl = CodeEntry(self, choices='Married Single Blah', width=9)
		self.preferred_name_label = StaticText(self, -1, 'Alias:')
		self.preferred_name_ctrl = TextEntry(self, width=15)
		self.maiden_name_label = StaticText(self, -1, 'Maiden:')
		self.maiden_name_ctrl = TextEntry(self, width=20)

		self.address_label = StaticText(self, -1, 'Address:')
		self.address_1_ctrl = TextEntry(self, -1, width=15)
		self.address_2_ctrl = TextEntry(self, -1, width=15)
		self.address_3_ctrl = TextEntry(self, -1, width=15)
		self.state_label = StaticText(self, -1, 'State:')
		self.state_ctrl = CodeEntry(self, choices='NSW VIC BLAH'.split(), width=3)
		self.post_code_label = StaticText(self, -1, 'Postcode:')
		self.post_code_ctrl = TextEntry(self, -1, width=4)
		self.country_label = StaticText(self, -1, 'Country:')
		self.country_ctrl = CodeEntry(self, choices='Australia NewZealand'.split(), width=10)
		self.telephone_label = StaticText(self, -1, 'Phone:')
		self.telephone_ctrl = PhoneEntry(self, -1, width=10)
		self.office_telephone_label = StaticText(self, -1, 'W:')
		self.office_telephone_ctrl = PhoneEntry(self, -1, width=10)
		self.mobile_telephone_label = StaticText(self, -1, 'M:')
		self.mobile_telephone_ctrl = PhoneEntry(self, -1, width=10)
		self.fax_label = StaticText(self, -1, 'F:')
		self.fax_ctrl = PhoneEntry(self, -1, width=10)
		self.email_label = StaticText(self, -1, 'Email:')
		self.email_ctrl = TextEntry(self, -1, width=30)
		self.emergency_contact_label = StaticText(self, -1, 'Emergency:')
		self.emergency_contact_ctrl = TextEntry(self, -1, width=15)
		self.emergency_contact_telephone_label = StaticText(self, -1, 'Phone:')
		self.emergency_contact_telephone_ctrl = PhoneEntry(self, -1, width=15)

		self.start_date_label = StaticText(self, -1, 'Joined:')
		self.start_date_ctrl = DateEntry(self, width=10)
		self.leaving_date_label = StaticText(self, -1, 'Left:')
		self.leaving_date_ctrl = DateEntry(self, width=10)

		self.nationality_country_label = StaticText(self, -1, 'Nationality:')
		self.nationality_country_ctrl = CodeEntry(self, choices='Australia NewZealand'.split(), width=10)
		self.birth_country_label = StaticText(self, -1, 'Birth:')
		self.birth_country_ctrl = CodeEntry(self, choices='Australia NewZealand'.split(), width=10)
		self.place_of_birth_label = StaticText(self, -1, 'Place:')
		self.place_of_birth_ctrl = TextEntry(self, width=10)

		self.first_language_label = StaticText(self, -1, 'First Language:')
		self.first_language_ctrl = CodeEntry(self, choices='English Blah'.split(), width=10)
		self.atsi_flag_ctrl = CheckBox(self, -1, 'ATSI', style=ALIGN_RIGHT)

		self.health_general_label = StaticText(self, -1, 'Health')
		self.health_general_ctrl = TextEntry(self, width=15)
		self.health_specific_label = StaticText(self, -1, '(Specific)')
		self.health_specific_ctrl = TextEntry(self, width=15)
		self.disabled_flag_ctrl = CheckBox(self, -1, 'Disabled', style=ALIGN_RIGHT)

		self.retirement_age_label = StaticText(self, -1, 'Ret. Age:')
		self.retirement_age_ctrl = IntEntry(self, width=3)
		self.probation_label = StaticText(self, -1, 'Probation:')
		self.probation_ctrl = IntEntry(self, width=3)
		self.probation_period_ctrl = CodeEntry(self, choices='Days Weeks Months'.split(), width=6)

		self.notice_label = StaticText(self, -1, 'Notice:')
		self.notice_ctrl = IntEntry(self, width=3)
		self.notice_period_ctrl = CodeEntry(self, choices='Days Weeks Months'.split(), width=6)
		self.notice_given_label = StaticText(self, -1, 'Notice:')
		self.notice_given_ctrl = IntEntry(self, width=3)
		self.notice_given_period_ctrl = CodeEntry(self, choices='Days Weeks Months'.split(), width=6)
		self.rehire_flag_ctrl = CheckBox(self, -1, 'Rehire', style=ALIGN_RIGHT)
		self.continuous_service_flag_ctrl = CheckBox(self, -1, 'Continuous', style=ALIGN_RIGHT)

		self.type_of_licence_label = StaticText(self, -1, 'Licence:')
		self.type_of_licence_ctrl = TextEntry(self, width=3)
		self.endorsements_label = StaticText(self, -1, 'Endorsement:')
		self.endorsements_ctrl = TextEntry(self, width=10)
		self.hobbies_label = StaticText(self, -1, 'Hobbies:')
		self.hobbies_ctrl = TextEntry(self, width=20)

		self.previous_start_date_label = StaticText(self, -1, 'Prior Start:')
		self.previous_start_date_ctrl = DateEntry(self, width=10)
		self.previous_leaving_date_label = StaticText(self, -1, 'Left:')
		self.previous_leaving_date_ctrl = DateEntry(self, width=10)
		self.previous_employee_number_label = StaticText(self, -1, 'Employee:')
		self.previous_employee_number_ctrl = TextEntry(self, width=6)
		self.leaving_reason_label = StaticText(self, -1, 'Reason:')
		self.leaving_reason_ctrl = CodeEntry(self, choices='Whatever Something'.split(), width=25)

		self.save_button = Button(self, -1, 'Save')

		# Bind events
		self.employee_search_ctrl.Bind(EVT_KEY_DOWN, self.OnSearchKeyDown)
		self.title_ctrl.Bind(EVT_KEY_DOWN, self.OnEntryKeyDown)
		self.first_names_ctrl.Bind(EVT_KEY_DOWN, self.OnEntryKeyDown)
		self.family_name_ctrl.Bind(EVT_KEY_DOWN, self.OnEntryKeyDown)
		self.preferred_name_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.maiden_name_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.birth_date_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.gender_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.marital_status_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.address_1_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.address_2_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.address_3_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.post_code_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.state_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.country_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.telephone_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.office_telephone_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.mobile_telephone_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.fax_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.email_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.emergency_contact_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.emergency_contact_telephone_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.start_date_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.leaving_date_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.nationality_country_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.birth_country_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.place_of_birth_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.first_language_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.atsi_flag_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.health_general_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.health_specific_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.disabled_flag_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.retirement_age_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.probation_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.probation_period_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.notice_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.notice_period_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.notice_given_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.notice_given_period_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.rehire_flag_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.continuous_service_flag_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.type_of_licence_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.endorsements_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.hobbies_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.previous_start_date_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.previous_leaving_date_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.previous_employee_number_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.leaving_reason_ctrl.Bind(EVT_BUTTON, self.OnEntryKeyDown)
		self.save_button.Bind(EVT_BUTTON, self.OnSave)

		# Set up tab order
		set_tab_order([
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
			self.telephone_ctrl,
			self.office_telephone_ctrl,
			self.mobile_telephone_ctrl,
			self.fax_ctrl,
			self.email_ctrl,
			self.emergency_contact_ctrl,
			self.emergency_contact_telephone_ctrl,
			self.start_date_ctrl,
			self.leaving_date_ctrl,
			self.nationality_country_ctrl,
			self.birth_country_ctrl,
			self.place_of_birth_ctrl,
			self.first_language_ctrl,
			self.atsi_flag_ctrl,
			self.health_general_ctrl,
			self.health_specific_ctrl,
			self.disabled_flag_ctrl,
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
		])

		# Layout the widgets
		vsz = BoxSizer(VERTICAL)

		# The search part is visually separated in its own box
		hsz = StaticBoxSizer(StaticBox(self), HORIZONTAL)
		hsz.Add(self.employee_search_label, 0, ALL, 3)
		hsz.AddSpacer(5)
		hsz.Add(self.employee_search_ctrl, 0, ALL, 3)
		hsz.AddSpacer(5)
		hsz.Add(self.employee_search_result_label, 1, ALL, 3)
		vsz.Add(hsz, 0, EXPAND | ALL, 3)

		# Put the employee fields in a grid
		gsz = FlexGridSizer(cols=2, vgap=3, hgap=3)

		def row(lhs, rhs):
			gsz.Add(lhs, 0, ALL, 2)
			hsz = BoxSizer(HORIZONTAL)
			for w in rhs:
				hsz.Add(w, 0, ALL, 2)
				#hsz.AddSpacer(2)
			gsz.Add(hsz, 0, 0, 0)

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

		# Phone: telephone_ctrl, office_telephone_ctrl, mobile_telephone_ctrl, fax_ctrl
		row(self.telephone_label, [self.telephone_ctrl,
			self.office_telephone_label, self.office_telephone_ctrl,
			self.mobile_telephone_label, self.mobile_telephone_ctrl,
			self.fax_label, self.fax_ctrl])

		# Email: email_ctrl
		row(self.email_label, [self.email_ctrl])

		# Next of kin: emergency_contact_ctrl, emergency_contact_telephone_ctrl
		row(self.emergency_contact_label, [self.emergency_contact_ctrl,
			self.emergency_contact_telephone_label, self.emergency_contact_telephone_ctrl])

		# Start: start_date_ctrl, leaving_date_ctrl
		row(self.start_date_label, [self.start_date_ctrl,
			self.leaving_date_label, self.leaving_date_ctrl])

		# Nationality: nationality_country_ctrl, birth_country_ctrl, place_of_birth_ctrl
		row(self.nationality_country_label, [self.nationality_country_ctrl,
			self.birth_country_label, self.birth_country_ctrl,
			self.place_of_birth_label, self.place_of_birth_ctrl])

		# Language: first_language_ctrl, atsi_flag_ctrl
		row(self.first_language_label, [self.first_language_ctrl, self.atsi_flag_ctrl])

		# Health: health_general_ctrl, health_specific_ctrl, disabled_flag_ctrl
		row(self.health_general_label, [self.health_general_ctrl,
			self.health_specific_label, self.health_specific_ctrl, self.disabled_flag_ctrl])

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
			self.previous_employee_number_label, self.previous_employee_number_ctrl,
			self.leaving_reason_label, self.leaving_reason_ctrl])

		vsz.Add(gsz, 1, EXPAND | ALL, 2)
		vsz.Add(self.save_button, 0, ALL, 2)

		self.SetSizer(vsz)
		self.SetupScrolling()

	def OnSave(self, event=None):
		app().warn('Removed as not relevant to gui problem')

	def OnSearchKeyDown(self, event):
		key, ctrl = event.KeyCode, event.ControlDown()
		if key >= 256: event.Skip(); return
		if chr(key) in '\r\n':
			self.do_employee_search(self.employee_search_ctrl.GetValue())
		event.Skip()

	def OnEntryKeyDown(self, event):
		key, ctrl = event.KeyCode, event.ControlDown()
		if key >= 256: event.Skip(); return
		if chr(key) in '\r\n':
			self.OnSave()
		event.Skip()

	def do_employee_search(self, term):
		app().warn('Removed as not relevant to gui problem')

class MainFrame(Frame):

	def __init__(self, app):
		self.app = app
		Frame.__init__(self, None, -1, app.GetAppName(), size=(800, 600))
		self.Bind(EVT_CLOSE, self.OnClose)
		self.build_panel()
		self.CreateStatusBar()

	def build_panel(self):
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

		p1 = Panel(self.hsplit, style=TAB_TRAVERSAL|BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_tree(p1), 1, EXPAND | ALL, 3)
		p1.SetSizer(sz)

		p2 = Panel(self.hsplit, style=TAB_TRAVERSAL|BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_info(p2), 1, EXPAND | ALL, 3)
		p2.SetSizer(sz)

		p3 = Panel(self.vsplit, style=TAB_TRAVERSAL|BORDER_SUNKEN)
		sz = BoxSizer(VERTICAL)
		sz.Add(self.create_book(p3), 1, EXPAND | ALL, 3)
		p3.SetSizer(sz)

		self.hsplit.SplitHorizontally(p1, p2, 400)
		# Initial sash position for a nested SplitterWindow doesn't work so...
		CallAfter(self.hsplit.SetSashPosition, 400)

		self.vsplit.SplitVertically(self.hsplit, p3, 300)

	def create_tree(self, panel):
		'''Create the tree control (top left) for navigating around data entry screens.'''
		tree_style = TR_DEFAULT_STYLE | TR_HIDE_ROOT
		self.tree = TreeCtrl(panel, style=tree_style)
		self.build_tree_items()
		self.Bind(EVT_TREE_ITEM_ACTIVATED, self.OnTreeItemActivated, self.tree)
		self.tree.ExpandAll()
		return self.tree

	def build_tree_items(self):
		'''Build the contents of the navigation tree.'''
		self.screen_data = [
			['Employee', [
				('Edit', EditEmployeeScreen)
			]]
		]

		self.tree_root = self.tree.AddRoot(self.app.GetAppName())
		first = None
		for data in self.screen_data:
			node, children = data
			parent = self.tree.AppendItem(self.tree_root, node)
			for child in children:
				label, paneclass = child
				id = node + '/' + label
				# Add the item and save a pane class with each item
				item = self.tree.AppendItem(parent, label)
				self.tree.SetPyData(item, (paneclass, id))
				# Select the first top-level child in the tree (by default)
				if first == None:
					first = item
					self.tree.SelectItem(first)

	def create_info(self, panel):
		'''Create the informational panel (bottom left).'''
		self.info_panel = Panel(panel)
		return self.info_panel

	def create_book(self, panel):
		'''Create the 'notebook' panel (right) that will contain data entry screens activated via the navigation tree.'''
		self.book = AuiNotebook(panel, style=AUI_NB_DEFAULT_STYLE|AUI_NB_CLOSE_ON_ALL_TABS|TAB_TRAVERSAL)
		return self.book

	def OnClose(self, event):
		event.Skip()

	def OnTreeItemActivated(self, event):
		item = event.GetItem()
		if item:
			paneclass, label = self.tree.GetPyData(item)
			if paneclass:
				pane = paneclass(self.book)
				self.book.AddPage(pane, pane.get_caption(), True)
		event.Skip()

	def OnQuitCmd(self, event):
		'''Quit the application.'''
		self.Close()

def main(redirect=False):
	TestApp(redirect=redirect).MainLoop()

if __name__ == '__main__':
	main()

# vi:set ts=4 sw=4:
