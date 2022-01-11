#!/usr/bin/env python

# This program demonstrates a platform inconsistency concerning
# wx.TextCtrl.SetValue() and wx.TextCtrl.GetInsertionPoint().
#
# On MacOSX, run this program and type: ABC<Left><Left><Left>DEF
#
# The following table shows the keystroke, the insertion point before and
# after the call to SetValue (as printed in the EVT_TEXT handler), and the
# contents of the control after the keystroke (with the visual insertion
# point indicated by a ^).
# 
# keys   pos contents
# ----   --- --------
# A      1/1 A^
# B      2/2 AB^
# C      3/3 ABC^
# <Left>     AB^C
# <Left>     A^BC
# <Left>     ^ABC
# D      1/4 DABC^
# E      5/5 DABCE^
# F      6/6 DABCEF^
#
# Text output is:
# KEY 0 
# pos before SetValue 1
# pos after SetValue 1
# KEY 1 A
# pos before SetValue 2
# pos after SetValue 2
# KEY 2 AB
# pos before SetValue 3
# pos after SetValue 3
# KEY 3 ABC
# KEY 2 ABC
# KEY 1 ABC
# KEY 0 ABC
# pos before SetValue 1
# pos after SetValue 4
# KEY 4 DABC
# pos before SetValue 5
# pos after SetValue 5
# KEY 5 DABCE
# pos before SetValue 6
# pos after SetValue 6
# KEY 6 DABCEF

# So it seems that calling SetValue() moves the insertion point to the end
# of the string rather than leaving it where it was before the call to SetValue.
#
# The same actions on Linux result in the following behaviour.
#
# keys   pos contents
# ----   --- --------
# A      0/0 A^
# B      1/0 AB^
# C      2/0 ABC^
# <Left>     AB^C
# <Left>     A^BC
# <Left>     ^ABC
# D      0/0 D^ABC
# E      1/0 DE^ABC
# F      2/0 DEF^ABC
#
# The text output is:
# KEY 0 
# pos before SetValue 0
# pos after SetValue 0
# KEY 1 A
# pos before SetValue 1
# pos after SetValue 0
# KEY 2 AB
# pos before SetValue 2
# pos after SetValue 0
# KEY 3 ABC
# KEY 2 ABC
# KEY 1 ABC
# KEY 0 ABC
# pos before SetValue 0
# pos after SetValue 0
# KEY 1 DABC
# pos before SetValue 1
# pos after SetValue 0
# KEY 2 DEABC
# pos before SetValue 2
# pos after SetValue 0
#
# Visually, this behaviour is correct (i.e. the insertion point isn't
# modified by a call to SetValue) but there are two odd things about the
# results of GetInsertionPoint.
#
# Firstly, even though the result of GetInsertionPoint in the EVT_KEY_DOWN
# handler is fine, it looks off by one in the EVT_TEXT handler. The
# insertion point reported in the EVT_KEY_DOWN handler is from before the
# keystroke is processed. The insertion point reported in the EVT_TEXT
# handler should be from after the keystroke has been processed and the text
# has been changed but it's not. Before the call to SetValue, the insertion
# point reported is the same as the one reported in the EVT_KEY_DOWN
# handler. So it now looks off-by-one.
#
# Secondly, the insertion point reported after the call to SetValue() in the
# EVT_TEXT handler is always zero even though the visual insertion point is
# somewhere else.
#
# The same actions on Windows result in the following behaviour.
#
# keys   pos contents
# ----   --- --------
# A      1/0 ^A
# B      1/0 ^BA
# C      1/0 ^CBA
# <Left>     ^CBA
# <Left>     ^CBA
# <Left>     ^CBA
# D      1/0 ^DCBA
# E      1/0 ^EDCBA
# F      1/0 ^FEDCBA
#
# The text output is:
# KEY 0 
# pos before SetValue 1
# pos after SetValue 0
# KEY 0 A
# pos before SetValue 1
# pos after SetValue 0
# KEY 0 BA
# pos before SetValue 1
# pos after SetValue 0
# KEY 0 CBA
# KEY 0 CBA
# KEY 0 CBA
# KEY 0 CBA
# pos before SetValue 0
# pos after SetValue 0
# KEY 0 DCBA
# pos before SetValue 1
# pos after SetValue 0
# KEY 0 EDCBA
# pos before SetValue 1
# pos after SetValue 0
#
# So it seems that SetValue moves the insertion point to the beginning
# of the control. This is the opposite of the MacOSX behaviour.
# 
# So, I would think that, in order to preserve the insertion point
# after a call to SetValue on all platforms, the insertion point has to be
# saved in the EVT_KEY_DOWN handler (because this value is wrong by the time
# the EVT_TEXT handler is called) and then reset the insertion point to that
# saved value after the call to SetValue in the EVT_TEXT handler.
#
# However, saving the insertion point just before the call to SetValue in
# the EVT_TEXT handler and restoring it just after the call to SetValue does
# product visually correct behaviour, even on Linux where the position
# values are off-by-one. That doesn't make sense to me.
#
# Uncommenting the call to SetInsertionPoint() produces the following output
# on Windows and MacOSX:
#
# KEY 0 
# pos before SetValue 1
# pos after SetValue 1
# KEY 1 A
# pos before SetValue 2
# pos after SetValue 2
# KEY 2 AB
# pos before SetValue 3
# pos after SetValue 3
# KEY 3 ABC
# KEY 2 ABC
# KEY 1 ABC
# KEY 0 ABC
# pos before SetValue 1
# pos after SetValue 1
# KEY 1 DABC
# pos before SetValue 2
# pos after SetValue 2
# KEY 2 DEABC
# pos before SetValue 3
# pos after SetValue 3
#
# And it produces the following output on Linux:
#
# KEY 0 
# pos before SetValue 0
# pos after SetValue 0
# KEY 1 A
# pos before SetValue 1
# pos after SetValue 1
# KEY 2 AB
# pos before SetValue 2
# pos after SetValue 2
# KEY 3 ABC
# KEY 2 ABC
# KEY 1 ABC
# KEY 0 ABC
# pos before SetValue 0
# pos after SetValue 0
# KEY 1 DABC
# pos before SetValue 1
# pos after SetValue 1
# KEY 2 DEABC
# pos before SetValue 2
# pos after SetValue 2
#
# And yet the insertion points are the same visually on all platforms.
# That makes it seem as though SetInsertionPoint() on Linux is doing the
# right thing when it's being told to do the wrong thing. That's clever.
#
# What am I missing here?
#
# Why does SetValue behave differently on all three platforms:
# moving the insertion point to the right end of the value on MacOSX,
# moving it to the left end of the value on Windows,
# and leaving it unchanged on Linux?
#
# Why does GetInsertionPoint() on Linux return off-by-one values only
# in the EVT_TEXT handler?
#
# Why does SetInsertionPoint() on Linux in the EVT_TEXT handler work
# in spite of that?

from wx import *

class TestApp(App):
	def OnInit(self):
		self.mainframe = MainFrame(self)
		self.SetTopWindow(self.mainframe)
		return True

class MainFrame(Frame):
	def __init__(self, app):
		Frame.__init__(self, None, title='Test')
		sz = BoxSizer(VERTICAL)
		self.ctrl = UpperTextCtrl(self)
		sz.Add(self.ctrl)
		self.SetSizerAndFit(sz)
		self.Centre()
		self.Show()

class UpperTextCtrl(TextCtrl):
	def __init__(self, parent, id=-1, value='', pos=DefaultPosition, size=DefaultSize, style=WANTS_CHARS|TE_PROCESS_TAB, validator=DefaultValidator, name=TextCtrlNameStr, width=15):
		TextCtrl.__init__(self, parent, id, value, pos, size, style, validator, name)
		self.Bind(EVT_TEXT, self.OnText)
		self.Bind(EVT_KEY_DOWN, self.OnKeyDown)
	def OnKeyDown(self, event):
		val = self.GetValue()
		pos = self.GetInsertionPoint()
		print 'KEY %d %s' % (pos, val)
		event.Skip()
	def OnText(self, event):
		val = self.GetValue()
		uval = val.upper()
		if val != uval:
			pos = self.GetInsertionPoint()
			print 'pos before SetValue %d' % pos
			self.SetValue(uval) # Same behaviour with ChangeValue()
			#self.SetInsertionPoint(pos)
			pos = self.GetInsertionPoint()
			print 'pos after SetValue %d' % pos
		event.Skip()

def main(redirect=False):
	TestApp(redirect=redirect).MainLoop()

if __name__ == '__main__':
	main()

# vi:set ts=4 sw=4:
