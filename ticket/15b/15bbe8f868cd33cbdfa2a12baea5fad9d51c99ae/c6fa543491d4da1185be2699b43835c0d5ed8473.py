import wx
from wx.lib.agw import ultimatelistctrl as ULC
import sys

class TestPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(wx.StaticText(self, -1, "some text"), 0, wx.EXPAND)
        self.SetAutoLayout(True)
        self.SetSizer(sizer)
        self.Fit()

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, "ULC Test", size=(320, 200))
        
        sizer = wx.BoxSizer(wx.VERTICAL)

        self.list = ULC.UltimateListCtrl(self, -1, agwStyle = wx.LC_REPORT)

        sizer.Add(self.list, 1, wx.EXPAND)
        self.SetSizer(sizer)
        self.SetAutoLayout(True)
        
        width, height = self.GetSize()

        column = ULC.UltimateListItem()
        column.SetText("bla")
        column.SetWidth(width)
        self.list.InsertColumnInfo(0, column)

        for i in range(20):
            self.list.InsertStringItem(sys.maxint, "")
            item = self.list.GetItem(i, 0)
            item.SetWindow(TestPanel(self.list), True) 
            self.list.SetItem(item)

if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = TestFrame()
    frame.Show(True)
    app.MainLoop()
