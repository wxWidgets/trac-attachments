#!/bin/python
# -*- coding: iso-8859-1 -*-

"""
ListCheckBox.py

David Janes
BlogMatrix
2004.06.18

This demonstrates crashing wxListCheckBox with InsertItems
"""

import sys
import os
import os.path
import re
import traceback
import pprint
import time
import threading
import urllib

from wxPython.wx import *

if __name__ == '__main__':
	class TestFrame(wxFrame):
		def __init__(self, parent):
			wxFrame.__init__(self, parent, -1, "Test Frame", size=(100,100),
				style=wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)

			self.sizer = wxBoxSizer(wxVERTICAL)

			self.listCheckBoxID = wxNewId()
			self.listCheckBox = wxCheckListBox(self,
				self.listCheckBoxID, style = wxLB_HSCROLL,
				choices = [],
				size = ( 200, 300 ))
			self.sizer.Add(self.listCheckBox, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5)

			#
			#	Buttons
			#
			self.buttonSizer = wxBoxSizer(wxHORIZONTAL)

			self.buttonSizer.Add(wxStaticText(self, -1, "        "), 1, wxALIGN_CENTER_VERTICAL)

			self.insertNormalButton = wxButton(self, -1, "Insert")
			self.buttonSizer.Add(self.insertNormalButton, 0, wxALIGN_CENTRE|wxRIGHT, 0)
			EVT_BUTTON(self, self.insertNormalButton.GetId(), self.OnInsertNormal)

			self.insertAppendButton = wxButton(self, -1, "Append")
			self.buttonSizer.Add(self.insertAppendButton, 0, wxALIGN_CENTRE|wxRIGHT, 0)
			EVT_BUTTON(self, self.insertAppendButton.GetId(), self.OnInsertAppend)

			self.sizer.AddSizer(self.buttonSizer, 0, wxCENTER|wxALL|wxEXPAND, 5 )

			#
			#	Finish it up
			#
			self.SetSizer(self.sizer)
			self.SetAutoLayout(True)
			self.sizer.Fit(self)

			self.items = [ "A", "B", "C" ]

		def OnInsertNormal(self, event):
			self.listCheckBox.InsertItems(self.items, 0)

		def OnInsertAppend(self, event):
			map(self.listCheckBox.Append, self.items)

	app = wxPySimpleApp()
	frame = TestFrame(None)
	frame.Show(True)
	app.MainLoop()



 	  	 
