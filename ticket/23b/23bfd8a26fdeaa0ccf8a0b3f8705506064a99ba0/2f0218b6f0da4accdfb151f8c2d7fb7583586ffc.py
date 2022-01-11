import wx

ID_LIST_TEST = 1001

class frame_Main(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self,None,-1,"Test")
        self.list_Test = wx.ListView(self, ID_LIST_TEST, style=wx.LC_REPORT|wx.LC_SINGLE_SEL|wx.SUNKEN_BORDER)
        self.list_Test.InsertColumn(0, "Test")
        self.list_Test.SetColumnWidth(0, 240)
        self.FillList()
        
        self.currentIndex = -1
        self.ignoreSelection = False
        
        #wx.EVT_LIST_ITEM_FOCUSED(self, ID_LIST_TEST,self.ListSelectionChanged)
        wx.EVT_LIST_ITEM_SELECTED(self, ID_LIST_TEST,self.ListSelectionChanged)
    
    def FillList(self):
        self.list_Test.InsertStringItem(0,"Use the arrow keys to change selection")
        self.list_Test.InsertStringItem(1,"Then try clicking to change selection")
    
    def ClearSelection(self):
        item = self.list_Test.GetFirstSelected()
        while (item >= 0):
            self.list_Test.Select(item,False)
            item = self.list_Test.GetNextSelected(item)
    
    def SelectItem(self,index):
        self.ClearSelection()
        self.list_Test.Select(index,True)
        self.list_Test.Focus(index)
    
    def ListSelectionChanged(self,event):
        newindex = event.GetIndex()
        print "Selection changed from",self.currentIndex,"to",newindex,"Ignore =",self.ignoreSelection
        if(self.ignoreSelection):
            return
        if(self.currentIndex >= 0):
            result = wx.MessageBox("Sure you want to change selection?","Question", wx.YES_NO | wx.ICON_QUESTION)
            if(result == wx.NO):
                self.ignoreSelection = True
                self.SelectItem(self.currentIndex)
                self.ignoreSelection = False
                print "This should be the end of this selection change"
                return
        self.currentIndex = newindex

class testApp(wx.App):
    def OnInit(self):
        self.frame = frame_Main()
        self.frame.Show(True)
        self.SetTopWindow(self.frame)
        return True

app = testApp(0)
app.MainLoop()


 	  	 
