#!/usr/bin/python

import wx
import wx.grid as grid

class Frame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, "Grid", size=(350, 250))
        self.grid = grid.Grid(self)
        self.grid.CreateGrid(20, 20)


if __name__ == '__main__':
    app = wx.App()
    frame1 = Frame(None)
    frame1.Show()

    app.MainLoop()
