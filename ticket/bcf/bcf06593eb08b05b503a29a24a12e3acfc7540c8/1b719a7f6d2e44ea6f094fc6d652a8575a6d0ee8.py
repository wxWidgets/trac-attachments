import wx, sys
#---------------------------------------------------------------------
class TestListCtrl(wx.ListCtrl):

    def __init__(self, parent, ID, pos=wx.DefaultPosition,
                 size=wx.DefaultSize, style=0):
        wx.ListCtrl.__init__(self, parent, ID, pos, size, style)
        self.Populate()
        
    def Populate(self):
        self.InsertColumn(0, "Name")

        for x in range(20):
            index = self.InsertStringItem(sys.maxint, str(x))
            if index != (self.GetItemCount()-1):
                # bug in listCtrl 
                print "Bug?"
            else:
                print 'GOOD'
            self.SetItemData(index, index)
            
        self.SortItems(cmp)
#---------------------------------------------------------------------
class MyFrame(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id,title)
        self.list = TestListCtrl(self, -1, 
            style=wx.LC_REPORT | wx.BORDER_NONE | wx.LC_SORT_ASCENDING)
#---------------------------------------------------------------------
class MyApp(wx.App):
    def OnInit(self):
        self.frame = MyFrame(None, -1,"Tree View of XML")
        self.frame.Show(True)
        self.SetTopWindow(self.frame)
        return True
#---------------------------------------------------------------------
if __name__=="__main__" :
    app = MyApp(0)
    app.MainLoop()



 	  	 
