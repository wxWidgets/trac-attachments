import sys

import wx
import wx.lib.agw.ultimatelistctrl as ULC

class MyFrame(wx.Frame):

    def __init__(self, parent):

        wx.Frame.__init__(self, parent, -1, "UltimateListCtrl Demo")

        list = ULC.UltimateListCtrl(self, wx.ID_ANY, agwStyle=wx.LC_REPORT|ULC.ULC_HAS_VARIABLE_ROW_HEIGHT|wx.LC_VRULES|wx.LC_HRULES|ULC.ULC_SINGLE_SEL|ULC.ULC_FOOTER)

        list.InsertColumn(0, "Column 1")
        list.InsertColumn(1, "Column 2")
        list.InsertColumn(2, "Column 3")

        index = list.InsertStringItem(sys.maxint, "Item 1")
        list.SetStringItem(index, 2, "Long Sub-item 1 in column 3")

        index = list.InsertStringItem(sys.maxint, "Item 2")
        list.SetStringItem(index, 2, "Long Sub-item 2 in column 3")

        dc = wx.WindowDC(list)
        font = list.GetItemFont(index)
        dc.SetFont(font)

        w, h, d, l = dc.GetFullTextExtent("Long Sub-item 2 in column 3")
        list.SetColumnWidth(2, w + d + l)
        
        index = list.InsertStringItem(sys.maxint, "")

        def show_width(_):
            scrolled = list.GetScrolledWin()
            width, height = self.GetSize()
            total_width = scrolled.GetTotalWidth()
            list.SetStringItem(index, 1, str(total_width))
            list.SetStringItem(index, 2, str(width))
            self.SetSize((total_width, height))

        button = wx.Button(list, label="width")
        button.Bind(wx.EVT_BUTTON, show_width)
        
        list.SetItemWindow(index, 0, button, expand=True)
        

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(list, 1, wx.EXPAND)
        self.SetSizer(sizer)


# our normal wxApp-derived class, as usual

app = wx.App(0)

frame = MyFrame(None)
app.SetTopWindow(frame)
frame.Show()

app.MainLoop()
