#!/usr/bin/python
# -*- coding: utf-8 -*-

# review.py

import wx

def set_width(control, width):
    control.MinSize = width, control.Size[1]
    control.MaxSize = width, control.Size[1]
    #control.Size = width, control.Size[1]

def set_height(control, height):
    control.Size = control.Size[0], height

class FindInFiles(wx.Frame):
  
    def __init__(self, parent, title):
        super(FindInFiles, self).__init__(parent, title=title, size=(500, 350))
        self.InitUI()
        
    def InitUI(self):
        cols = 3
        rows = 3
        vgap = 5
        hgap = 5

        sizer = wx.FlexGridSizer(rows, cols, vgap, hgap)
        sizer.AddGrowableCol(1)

        title1 = wx.StaticText(self, label="Find Text")
        cb1 = wx.ComboBox(self)
        button1 = wx.Button(self, label='>')
        
        title2 = wx.StaticText(self, label="Location")
        cb2 = wx.ComboBox(self)
        button2 = wx.Button(self, label='...')

        title3 = wx.StaticText(self, label="File Types")
        cb3 = wx.ComboBox(self)
        
        set_width(button1, button1.Size[1])
        set_width(button2, button2.Size[1])

        sizer.Add(title1, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(cb1, 1, wx.EXPAND|wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(button1, 0, wx.ALL)

        sizer.Add(title2, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(cb2, 1, wx.EXPAND|wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(button2, 0, wx.ALL)

        sizer.Add(title3, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(cb3, 1, wx.EXPAND|wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        
        self.Sizer = wx.BoxSizer()
        self.Sizer.Add(sizer, 1, wx.EXPAND|wx.ALL, border=20)


if __name__ == '__main__':
    app = wx.App()
    find_in_files = FindInFiles(None, title='Find In Files...')
    find_in_files.Show()     
    find_in_files.Centre()
    app.MainLoop()
