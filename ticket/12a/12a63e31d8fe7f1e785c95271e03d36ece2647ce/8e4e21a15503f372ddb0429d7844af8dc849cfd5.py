#!/usr/bin/env python
# -*- coding: utf-8 -*-
""" This code reproduces the Clear() function not working with a
    wxSimpleHTMLListBox. Since wxSimpleHTMLListBox implements wxControlWithItems
    Clear() should work.
"""

import wx

app = wx.PySimpleApp(0)
frame = wx.Frame(None, 0)
app.SetTopWindow(frame)
HTMLLB = wx.SimpleHtmlListBox(frame,100)
HTMLLB.Append('hello1')
HTMLLB.Append('hello2')
HTMLLB.Append('hello3')
HTMLLB.Clear()
if HTMLLB.IsEmpty():
    print 'Success'
else:
    print 'Failed -> Clear() not working'
 	  	 
