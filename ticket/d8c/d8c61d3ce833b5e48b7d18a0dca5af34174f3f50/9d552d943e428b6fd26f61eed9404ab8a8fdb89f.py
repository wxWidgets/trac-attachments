#!/usr/bin/env python

import wx
import sys
sys.stderr.write( "OSversion %s\n" % str(wx.GetOsVersion()))
sys.stderr.write( "Wx Version %s\n" % wx.__version__)

app = wx.PySimpleApp()

i1 = wx.MenuItem(None, 101, "T0", "", wx.ITEM_NORMAL, None)
i2 = wx.MenuItem(None, 102, "T1", "", wx.ITEM_NORMAL, None)

i3 = wx.MenuItem(None, 103, "T2", "", wx.ITEM_NORMAL, None)
i4 = wx.MenuItem(None, 104, "T3", "", wx.ITEM_NORMAL, None)

menu = wx.Menu()
menu.AppendItem(i1)
menu.AppendItem(i2)

me = wx.Menu()
me.AppendItem(i3)
me.AppendItem(i4)

i1.SetSubMenu(me)

# Remove these two lines and the subsequent code appears to work
menu.RemoveItem(i1)
menu.InsertItem(0, i1)

menu.RemoveItem(i1)
sys.stderr.write( "One\n" )
me.RemoveItem (i3)
sys.stderr.write( "Two\n" )
me.RemoveItem (i4)
sys.stderr.write( "Three\n" )
me.InsertItem (0, i4)
sys.stderr.write( "Four\n" )
menu.InsertItem(0, i1)
sys.stderr.write( "Five\n" )

frame = wx.Frame(None, title="Test")
bar = wx.MenuBar()
frame.SetMenuBar(bar)
bar.Append(menu, "Title")
frame.Show()

# Pick the cascade from the menu and get a segmentation fault
app.MainLoop()

 	  	 
