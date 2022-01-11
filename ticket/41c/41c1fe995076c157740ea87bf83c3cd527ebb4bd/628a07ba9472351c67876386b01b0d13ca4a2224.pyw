#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
from __future__ import division # 1/2 == .5 (par defaut, 1/2 == 0)

##--------------------------------------##
#              WxGeometrie               #
#              main program              #
##--------------------------------------##
#    WxGeometrie
#    Dynamic geometry, graph plotter, and more for french mathematic teachers.
#    Copyright (C) 2005-2007  Nicolas Pourcelot
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

VERSION = "2.8"

import wxversion
if wxversion.checkInstalled(VERSION):
    wxversion.select(VERSION) # version a utiliser de preference
else:
    print "Version %s was not found." %VERSION
import wx

class Panel_simple(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1,style = wx.TAB_TRAVERSAL|wx.WANTS_CHARS)
        self.Bind(wx.EVT_CHAR, self.test_evt_char)
        self.Bind(wx.EVT_MOTION, self.test_evt_motion)
        
    def test_evt_char(self, event):
        print "test_evt_char"

    def test_evt_motion(self, event):
        print "test_evt_motion"


class WxGeometrie(wx.Frame):
    def __init__(self, app):
        wx.Frame.__init__(self, parent = None, size=wx.Size(500,400))
        self.panel = Panel_simple(self)

app = wx.PySimpleApp()
frame = WxGeometrie(app)
frame.Show(True)
app.MainLoop()