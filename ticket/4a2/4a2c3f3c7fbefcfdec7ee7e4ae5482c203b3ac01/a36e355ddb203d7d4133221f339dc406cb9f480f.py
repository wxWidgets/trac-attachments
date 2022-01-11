#!/usr/bin/env python
#-*- coding: ISO-8859-1 -*-

#****h* /test.py
#  NAME
#    test -- 
#  COPYRIGHT
#
#  Copyright (C) 2006 Jérôme Laheurte <fraca7@free.fr>
#
# This library  is free software; you can  redistribute it and/or
# modify  it under  the terms  of the  GNU Lesser  General Public
# License as  published by  the Free Software  Foundation; either
# version  2.1 of  the License,  or  (at your  option) any  later
# version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY;  without even the implied warranty of
# MERCHANTABILITY or  FITNESS FOR A PARTICULAR  PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You  should have  received a  copy  of the  GNU Lesser  General
# Public License  along with this  library; if not, write  to the
# Free  Software Foundation,  Inc., 59  Temple Place,  Suite 330,
# Boston, MA 02111-1307 USA
#
#  CREATION DATE
#    28 Sep 2006
#***

__rcsid__ = '$Id$'

import wx

class MyDropTarget(wx.PyDropTarget):
    def __init__(self):
        wx.PyDropTarget.__init__(self)

        self.data = wx.CustomDataObject('text/x-moz-message')
        self.SetDataObject(self.data)

    def OnEnter(self, x, y, d):
        return d

    def OnLeave(self):
        pass

    def OnDrop(self, x, y):
        return True

    def OnDragOver(self, x, y, d):
        return d

    def OnData(self, x, y, d):
        print 'DATA', x, y

        if self.GetData():
            print 'OK', self.data.GetData()

        return d

class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, 'test')

        target = MyDropTarget()
        self.SetDropTarget(target)

        self.Show()

class MyApp(wx.App):
    def OnInit(self):
        frm = MyFrame()
        return True

if __name__ == '__main__':
    app = MyApp(0)
    app.MainLoop()

 	  	 
