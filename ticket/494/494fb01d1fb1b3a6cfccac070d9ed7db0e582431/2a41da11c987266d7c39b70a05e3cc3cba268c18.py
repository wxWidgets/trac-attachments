#!/usr/bin/env python

import wx, wx.grid

class IntEditor(wx.grid.PyGridCellEditor):
    def __init__ (self):
        self._control = None

        wx.grid.PyGridCellEditor.__init__(self)

    def Create (self, parent, id, evtHandler):
        self._control = wx.TextCtrl(parent, id)

        self.SetControl(self._control)

    def SetSize (self, rect):
        if self._control is None:
            return

        self._control.SetDimensions(rect.x, rect.y, rect.width+2, rect.height+2, wx.SIZE_ALLOW_MINUS_ONE)

    def BeginEdit (self, row, col, grid):
        self._control.SetFocus()

    def Reset (self):
        self._control.SetValue("")

    def Destroy (self):
        self._control.Destroy()
        self.base_Destroy()

    def EndEdit(self, row, col, grid, oldval=""):
        result = int(self._control.GetValue())

        if (oldval.isdigit() and result != int(oldval)) or not oldval.isdigit():
            return float(result)
        else:
            return None

    def ApplyEdit (self, row, col, grid):
        result = self._control.GetValue()

        grid.GetTable().SetValue(row, col, result)
        self.Reset()

    def Clone(self):
        return IntEditor()

class TestFrame (wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, parent=None, id=-1, title="Grid Editor test")

        grid = wx.grid.Grid(self)
        grid.CreateGrid(1, 5)

        attr = wx.grid.GridCellAttr()
        #attr.SetEditor(wx.grid.GridCellNumberEditor())
        attr.SetEditor(IntEditor())
        grid.SetRowAttr(0, attr)

        self.Show()

if __name__ == "__main__":
    app = wx.App(0)
    frame = TestFrame()
    app.MainLoop()
