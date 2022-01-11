#!/usr/bin/env python

import wx, decimal

class TestObject (object):
    def __init__ (self, value):
        self.value = value

    def __str__ (self):
        return str(self.value)

class VirtualListCtrl (wx.ListCtrl):
    def __init__ (self, parent, types):
        wx.ListCtrl.__init__(self, parent, style=wx.LC_REPORT|wx.LC_SINGLE_SEL|wx.LC_VIRTUAL)

        self.SetItemCount(1)

        self.types = types

        for col, type in enumerate(types):
            self.InsertColumn(col, type.__name__)

    def OnGetItemText (self, item, col):
        if item == 0:
            return self.types[col](10)

    def OnGetItemAttr (self, item):
        return None

    def OnGetItemImage (self, item):
        return -1

class TestFrame (wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, parent=None, id=-1, title="VirtualListCtrl test")

        # Works:
        #VirtualListCtrl(self, types=[str, unicode])

        # Segfaults:
        VirtualListCtrl(self, types=[TestObject, int, long, float, decimal.Decimal])

        self.Show()

if __name__ == "__main__":
    app = wx.App(0)
    frame = TestFrame()
    app.MainLoop()
