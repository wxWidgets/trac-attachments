#!/usr/bin/env python
# coding: UTF8

import wx
import wx.grid

ID_MENU = wx.NewId()

class Absolute(wx.Frame):
    def __init__(self, title):
        wx.Frame.__init__(self, None, -1, title, wx.DefaultPosition, wx.Size(200, 150))

        menubar = wx.MenuBar()
        file = wx.Menu()
        file.Append(wx.ID_EXIT, '&Quit')
        edit = wx.Menu()
        edit.Append(ID_MENU, text=u'&Menu')
        menubar.Append(file, '&File')
        menubar.Append(edit, '&Edit')
        self.SetMenuBar(menubar)

        self.Bind(wx.EVT_MENU, self.OnQuit, id=wx.ID_EXIT)
        self.Bind(wx.EVT_MENU, self.OnMenu, id=ID_MENU)

        self.grid = wx.grid.Grid(self)
        self.grid.Bind(wx.EVT_KEY_DOWN, self.OnKey)

        self.SetAcceleratorTable(wx.AcceleratorTable([
             (wx.ACCEL_NORMAL,  wx.WXK_ESCAPE,     wx.ID_EXIT),
             (wx.ACCEL_CTRL,    ord('X'),          wx.ID_EXIT),
             (wx.ACCEL_NORMAL,  wx.WXK_NUMPAD_ADD, ID_MENU),
             ]))

        self.grid.SetFocus()

    def OnKey(self, event):
        print event.GetKeyCode()
        event.Skip()

    def OnQuit(self, event):
        print "QUIT"
        self.Close()

    def OnMenu(self, event):
        print "MENU"


def main():
    app = wx.App()

    absolute = Absolute("Absolute")
    absolute.Show(True)
    app.MainLoop()


if __name__ == '__main__':
    main()
