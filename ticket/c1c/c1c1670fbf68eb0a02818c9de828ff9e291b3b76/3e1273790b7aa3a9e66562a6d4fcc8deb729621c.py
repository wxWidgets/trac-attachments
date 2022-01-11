# -*- encoding: iso-8859-1 -*-
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

"""
I noticed an oddity which I'd like to track down.  I'm not sure that
it is a bug in the binding instead of in my programming, which is why
I'd like to talk to an expert first before opening a bug report
officially.

I'm working with Python 2.3 and wxWidgets 2.4.2.4 under Debian sid and
discovered that after creating the colour dialog, pre-setting the
colour doesn't seem to take the effects I expected.  Instead, the
dialog always displays black as selected colour, regardless of my
pre-setting.

In the example below I set the colour to red (#FF0000) after the
dialog is created but before it is drawn on the screen.  However, on
my system it still displays black as selection instead of red.

This bug has been confirmed by Robin Dunn <robin@alldunn.com>, who is
responsible for the Python bindings of wxWidgets.  However, he
discovered that this problem can be bypassed by using a different
constructor and supplying the color data at the __init__ stage.

Comment out one of the following runTest functions to find out what
the bug feels like.
"""

import wx

#---------------------------------------------------------------------------

# Using the set data method, pre-selection doesn't work.
#
def runTest(frame, nb, log):
    dlg = wx.ColourDialog(frame)
    dlg.GetColourData().SetColour("#FF0000")
    log.WriteText('Pre-selected color: %s\n' % str(dlg.GetColourData().GetColour().Get()))
    dlg.GetColourData().SetChooseFull(True)
    if dlg.ShowModal() == wx.ID_OK:
        log.WriteText('You selected: %s\n' % str(dlg.GetColourData().GetColour().Get()))
    dlg.Destroy()
"""
# From Robin Dunn: Using a different constructor pre-selection works
#
def runTest(frame, nb, log):
    data = wx.ColourData()
    data.SetColour("#FF0000")
    dlg = wx.ColourDialog(frame, data)
    log.WriteText('Pre-selected color: %s\n' % str(dlg.GetColourData().GetColour().Get()))
    dlg.GetColourData().SetChooseFull(True)
    if dlg.ShowModal() == wx.ID_OK:
        log.WriteText('You selected: %s\n' % str(dlg.GetColourData().GetColour().Get()))
    dlg.Destroy()
"""
#---------------------------------------------------------------------------

if __name__ == '__main__':
    from sys import path
    path.insert (0, "/usr/share/doc/wx2.8-examples/examples/wxPython/")
    import sys,os
    import run
    run.main(['', os.path.basename(sys.argv[0])])

