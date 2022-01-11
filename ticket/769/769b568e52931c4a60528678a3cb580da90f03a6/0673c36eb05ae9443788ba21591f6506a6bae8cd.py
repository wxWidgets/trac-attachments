import  wx.lib.mixins.listctrl  as  listmix
import  wx

musicdata = {
0 : ('test00', 'test00', 'test00', 'mine intresting data: 0'),
1 : ('test01', 'test02', 'test03', 'mine intresting data: 1'),
2 : ('test02', 'test04', 'test06', 'mine intresting data: 2'),
3 : ('test03', 'test06', 'test09', 'mine intresting data: 3'),
4 : ('test04', 'test08', 'test12', 'mine intresting data: 4'),
5 : ('test05', 'test10', 'test15', 'mine intresting data: 5'),
6 : ('test06', 'test12', 'test18', 'mine intresting data: 6'),
7 : ('test07', 'test14', 'test21', 'mine intresting data: 7'),
8 : ('test08', 'test16', 'test24', 'mine intresting data: 8'),
9 : ('test09', 'test18', 'test27', 'mine intresting data: 9'),
10 : ('test10', 'test20', 'test30', 'mine intresting data: 10'),
11 : ('test11', 'test22', 'test33', 'mine intresting data: 11'),
12 : ('test12', 'test24', 'test36', 'mine intresting data: 12')
}

class TestListCtrl(wx.ListCtrl, listmix.ListCtrlAutoWidthMixin):
    def __init__(self, parent, ID, pos=wx.DefaultPosition,
                 size=wx.DefaultSize, style=0):
        wx.ListCtrl.__init__(self, parent, ID, pos, size, style)
        listmix.ListCtrlAutoWidthMixin.__init__(self)

class TestListCtrlPanel(wx.Panel, listmix.ColumnSorterMixin):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1, style=wx.WANTS_CHARS)
        tID = wx.NewId()
        self.list = TestListCtrl(self, tID,
                                 style=wx.LC_REPORT
                                 | wx.BORDER_NONE
                                 | wx.LC_SORT_DESCENDING
                                 | wx.LC_VRULES
                                 | wx.LC_HRULES
                                 | wx.LC_SINGLE_SEL
                                 )
        self.PopulateList()
        self.itemDataMap = musicdata
        listmix.ColumnSorterMixin.__init__(self, 3)
        self.Bind(wx.EVT_SIZE, self.OnSize)
        self.Bind(wx.EVT_LIST_ITEM_SELECTED, self.OnItemSelected, self.list)

    def PopulateList(self):
        self.list.InsertColumn(0, "col 1")
        self.list.InsertColumn(1, "col 2")
        self.list.InsertColumn(2, "col 3")

        for key, data in musicdata.items():
            index = self.list.InsertStringItem(key, data[0])
            self.list.SetStringItem(index, 1, data[1])
            self.list.SetStringItem(index, 2, data[2])
            self.list.SetItemData(index, key)
######################## fot testing ########################
            print key, data, index                          #
######################## fot testing ########################
        self.list.SetColumnWidth(0, 200)
        self.list.SetColumnWidth(1, 200)
        self.list.SetColumnWidth(2, 200)
        self.currentItem = 0

    def GetListCtrl(self):
        return self.list

    def OnItemSelected(self, event):
######################## fot testing ########################
	msg =  str(event.m_itemIndex) + ' ' + str(musicdata[event.m_itemIndex])
	msg += '\n' + 'mine index: ' + musicdata[event.m_itemIndex][3]
	dlg = wx.MessageDialog(None, msg)
        dlg.ShowModal()
        dlg.Destroy()
######################## fot testing ########################

    def OnSize(self, event):
        w,h = self.GetClientSizeTuple()
        self.list.SetDimensions(0, 0, w, h)

class Frame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, size = (650,250))
        list_ctrl = TestListCtrlPanel(self)

class App(wx.App):
    def OnInit(self):
        frame = Frame()
        frame.Show(True)
        self.SetTopWindow(frame)
        return True

if __name__ == '__main__':
    App().MainLoop()
	

 	  	 
