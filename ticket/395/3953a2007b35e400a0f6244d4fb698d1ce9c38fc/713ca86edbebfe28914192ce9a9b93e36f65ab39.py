#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import wx
import UITest
import os
import string
from ctypes import windll
#from Utilities import *
import wx.grid as  gridlib

class RequestTable(gridlib.PyGridTableBase):
    def __init__(self, char, occurs):

        gridlib.PyGridTableBase.__init__(self)

        self.odd = gridlib.GridCellAttr()
        self.odd.SetBackgroundColour("white")
        self.even = gridlib.GridCellAttr()
        self.even.SetBackgroundColour((240, 240, 240))

        self.data = {}

        self.labels = ["NAME", "LEN", "VALUE"]
        self.columnsType = ["text", "integer", "text"]

        try:
            maxLength = int(occurs)
        except:
            maxLength = 2979
        string_to_expand = char
        if len(string_to_expand) == 0:
            string_to_expand = "m"

        i = 0
        for currentLength in range(maxLength - 1, maxLength + 1):
            self.data[i] = (str(i), currentLength, (string_to_expand * ((currentLength / len(string_to_expand)) + 1))[:currentLength])
            i += 1

    def GetAttr(self, row, col, kind):
        attr = [self.even, self.odd][row % 2]
        attr.IncRef()
        return attr

    def GetColLabelValue(self, col):
        return self.labels[col]

    def GetNumberRows(self):
        return len(self.data)

    def GetNumberCols(self):
        return len(self.labels)

    def IsEmptyCell(self, row, col):
        return False

    def GetValue(self, row, col):
        value = self.data[row][col]
        return value

class TestFrame(UITest.TestFrame):
    # constructor
    def __init__(self, parent):
        # initialize parent class
        UITest.TestFrame.__init__(self, parent)
        self.SetAutoLayout(True)

    def write(self,message):
        self.PBReportText.AppendText(message)
        wx.Yield()


    def CMDButtonOnButtonClick(self, event):
        self.PBReportText.Clear()

        self.recordSetGrid.SetTable(RequestTable(self.CharacterText.GetValue(), self.OccursText.GetValue()), True)
        self.recordSetGrid.AutoSizeColumns()
        self.recordSetGrid.Refresh()
        self.recordSetGrid.Update()


class TestManagerApp(wx.App):
    def OnInit(self):
        self.frame = TestFrame(None)
        self.SetTopWindow(self.frame)
        self.frame.Show(True)
        return True

if __name__ == '__main__':
    app = TestManagerApp(False)
    app.MainLoop()
    del app




