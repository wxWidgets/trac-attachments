__author__ = 'Hose'

#!/usr/bin/python
# -*- coding: utf-8 -*-

# size.py

import wx
from wx.lib import sheet

class Example(wx.Frame):

    def __init__(self, parent, title):
        super(Example, self).__init__(parent, title=title,
            size=(450, 400))

        self.SetLayoutDirection(wx.Layout_RightToLeft)
        a = sheet.CSheet(self)
        a.SetNumberCols(20)
        self.Center()
        self.Show()


if __name__ == '__main__':

    app = wx.App()
    Example(None, title='Size')
    app.MainLoop()
