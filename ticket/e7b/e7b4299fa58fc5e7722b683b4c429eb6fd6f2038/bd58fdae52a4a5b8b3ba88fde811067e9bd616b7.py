#!/bin/env python

import wx
import wx.lib.agw.ultimatelistctrl as ULC # Downloaded from SVN on 30 March 2010

class myFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, size=(330,200), title='ULC Test')

        self.ulc = ULC.UltimateListCtrl(self, -1, style=wx.LC_REPORT,
                                        extraStyle = ULC.ULC_HAS_VARIABLE_ROW_HEIGHT)

        self.ulc.InsertColumn(0,'TextCtrls')
        self.ulc.SetColumnWidth(0, 300)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.ulc, 1, wx.GROW, 0)
        self.SetSizer(sizer)

        for itemCount in range(10):
            # This works, until the controls are supposed to be drawn off the
            # screen. Then those off-screen controls are placed in the upper-
            # left corner UNTIL the control is scrolled to the place where
            # they should appear, and then it's all drawn correctly.

            item = ULC.UltimateListItem()
            item.SetColumn(0)
            item.SetId(itemCount)

            newWin = wx.TextCtrl(self.ulc, -1, value='TextCtrl %d' % itemCount)

            # Need to mess with the _enabled flag, b/c exception gets thrown
            # when trying to do item.SetWindow
            # item.Enable(True)
            # BUT item.Enable doesn't set item._enabled!?
            item._enabled = True

            item.SetWindow(newWin)
            self.ulc.InsertItem(item)

            # None of these solve the problem
            #self.ulc.Layout()
            #self.ulc._mainWin.ResetVisibleLinesRange()
            #self.ulc._mainWin.RecalculatePositions()
            #self.ulc._mainWin.RefreshAll()

if __name__ == '__main__':
    app = wx.App(False)
    frame = myFrame(None)
    frame.Show(True)
    app.MainLoop()




