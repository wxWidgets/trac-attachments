#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import os
import wx

''' 
This script shows the wxWidgets bug when Ctrl^C is used in the controlling terminal.

When no wx.Notebook have been created, things go smoothly.

Otherwise, the Ctrl^C handler shuts down the app, which tries to unregister window classes,
"_wx_SysTabCtl32" being one of them, fails, tries to log a message, which triggers a WakeUpIdle
action, which itself fails miserably since the app is shutting down ... and logs a message!
Boom, stack overflow.
'''


class OKPanel(wx.Panel):
	def __init__(self, parent):
		wx.Panel.__init__(self, parent)
		wx.StaticText(self, label='I am clean')
		
class BuggyPanel(wx.Panel):
	def __init__(self, parent):
		wx.Panel.__init__(self, parent)
		wx.StaticText(self, label='I am buggy')
		nb = wx.Notebook(self)
		
class MainFrame(wx.Frame):
	def __init__(self):
		wx.Frame.__init__(self, None, title='wxWidgets Ctrl^C crash demo')
		panel = BuggyPanel(self)
		
class App(wx.App):
	def OnInit(self):
		frame = MainFrame()
		frame.Show(True)
		self.SetTopWindow(frame)
		return True
		
if __name__ == '__main__':
	print "Press Ctrl^C in this terminal window to crash the python interpreter"
	app = App()
	app.MainLoop()
		