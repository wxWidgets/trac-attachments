#!/usr/bin/env pythonw
#
# photoblog.py -- a script for posting images to a MovableType blog.
#
# Copyright (C) Robert Kaye 2003
# 
# photoblog.py is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# photoblog.py is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with photoblog.py; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

# NOTE: This program requires mtsend.py:
#       http://scott.yang.id.au/archives/000092.php

# TODO: The app needs a menu, and options for loading a new file

import wx, sys, re, os

class PhotoDetailsFrame(wx.Frame):

    descTextId = 6

    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, 
                          style = wx.SYSTEM_MENU | wx.CAPTION | wx.CLOSE_BOX | wx.TAB_TRAVERSAL |
                                  wx.RESIZE_BORDER | wx.MINIMIZE_BOX | wx.MAXIMIZE_BOX)

        wx.EVT_TEXT(self, self.descTextId, self.OnText)

        self.descTextCtrl = wx.TextCtrl(self, self.descTextId, "", style = wx.TE_MULTILINE)
        mainSizer = wx.BoxSizer(wx.VERTICAL)
        mainSizer.Add(self.descTextCtrl, 1, wx.EXPAND | wx.ALL, 10)

        self.SetSizer(mainSizer)

    def OnText(self, event):
        for i in xrange(self.descTextCtrl.GetNumberOfLines()):
           print "%d: %s" % (i, self.descTextCtrl.GetLineText(i))


#---------------------------------------------------------------------------

class PhotoDetails(wx.App):
  
    def __init__(self):
        wx.App.__init__(self, 0)

    def OnInit(self):

        frame = PhotoDetailsFrame(None, -1, "Text control test")
        frame.Show(True)

        self.SetTopWindow(frame)

        # Return a success flag
        return True

    def MacOpenFile(self, filename): 
        print filename, "was dropped"

#---------------------------------------------------------------------------

app = PhotoDetails()
app.MainLoop()

#----------------------------------------------------------------------------

 	  	 
