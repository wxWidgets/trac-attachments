#! Python
# -*- coding: utf-8 -*-

import wx

words = "x xxxxxxxxxx xxxxxxxxxxxxxxxxxxxx".split()
indx = 0

def OnMenuOpen(evt):
    global indx
    global words
    undo_menu_item.SetText(u"&Undo %s\tCtrl+Z" % (words[indx%3]))
    indx += 1

def OnUndo(evt):
    txt_field.SetValue(undo_menu_item.GetText())

app = wx.App()
frm = wx.Frame(None, -1, u"test menu label")
txt_field = wx.TextCtrl(frm, 1, style=wx.TE_MULTILINE)
frm.CreateStatusBar()



test_menu= wx.Menu()
#undo_menu_item = test_menu.Append(-1, "&Undo\tCtrl+Z"," Undo last item")
#dummy_menu_item = test_menu.Append(-1, "&Dummy\tCtrl+Z"," Dummy menu item 1")

undo_menu_item  = wx.MenuItem(test_menu,-1,"&Undo\tCtrl+Z"," Undo last item")
dummy_menu_item = wx.MenuItem(test_menu,-1,"&Dummy\tCtrl+Z"," Dummy menu item 1")

undo_menu_item.SetBitmap(wx.Bitmap("edit-undo.png",wx.BITMAP_TYPE_PNG))

test_menu.AppendItem(undo_menu_item)
test_menu.AppendItem(dummy_menu_item)

menu_bar = wx.MenuBar()
menu_bar.Append(test_menu,"&Testmenu") 
frm.SetMenuBar(menu_bar) 

frm.Bind(wx.EVT_MENU_OPEN, OnMenuOpen)
frm.Bind(wx.EVT_MENU, OnUndo, undo_menu_item)

frm.Show(True)
app.MainLoop()
