#!/usr/bin/python
# -*- coding: utf-8 -*-

import wx

class FlexGridSizerDemo(wx.Frame):
    def __init__(self, parent, title):
        super(FlexGridSizerDemo, self).__init__(parent, title=title, size=(500, 350))
        
        cols = 3
        rows = 3
        vgap = 5
        hgap = 5

        sizer = wx.FlexGridSizer(rows, cols, hgap, vgap)
        sizer.AddGrowableCol(1, 1)
        sizer.AddGrowableRow(2, 1)

        title1 = wx.StaticText(self, label="Title")
        cb1 = wx.ComboBox(self)
        button1 = wx.Button(self, label='This should define\nwidth of this column\nand height of row...')
        
        title2 = wx.StaticText(self, label="Title")
        cb2 = wx.ComboBox(self)

        title3 = wx.StaticText(self, label="Title")
        cb3 = wx.ComboBox(self)
        button3 = wx.Button(self, label='Fill vertically')
        

        sizer.Add(title1, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(cb1, 0, wx.EXPAND_HORIZONTAL|wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(button1, 0, wx.EXPAND|wx.ALL)

        sizer.Add(title2, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(cb2, 1, wx.EXPAND|wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.AddStretchSpacer()

        sizer.Add(title3, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(cb3, 1, wx.EXPAND|wx.ALL|wx.ALIGN_CENTER_VERTICAL)
        sizer.Add(button3, 0, wx.EXPAND_VERTICAL|wx.EXPAND_HORIZONTAL|wx.ALL)
        
        self.Sizer = wx.BoxSizer()
        self.Sizer.Add(sizer, 1, wx.EXPAND|wx.ALL, border=20)

if __name__ == '__main__':
    app = wx.App()
    demo = FlexGridSizerDemo(None, title='Demo FlexGridSizer')
    demo.Show()
    demo.Centre()
    app.MainLoop()
