from wxPython.wx import *

class MyTreeCtrl(wxTreeCtrl):
    def __init__(self, parent, ID):
        wxTreeCtrl.__init__(self, parent, ID, style = wxTR_HIDE_ROOT)
        
        self.root = self.AddRoot("Everything")
        first = self.AppendItem(self.root,"1")
        self.AppendItem(self.root,"2")
        self.AppendItem(self.root,"3")
        self.AppendItem(self.root,"4")
        
        self.SelectItem(first)
        
        EVT_TREE_SEL_CHANGED(self,self.GetId(),self.OnTermSelect)
        EVT_TREE_DELETE_ITEM(self,self.GetId(),self.OnTermDelete)
        
        print "About to DeleteAllItems()"
        self.DeleteAllItems()
        print "Done DeleteAllItems()"

    def OnTermSelect(self, event):
        print "OnTermSelect"
        
    def OnTermDelete(self, event):
        print "OnTermDelete"

class MyApp(wxApp):
    def OnInit(self):
        frame = wxFrame(NULL, -1, "wxTreeCtrl.DeleteAllItems() Bug")
        tree = MyTreeCtrl(frame,-1)
        frame.Show(true)
        self.SetTopWindow(frame)
        return true

app = MyApp(0)
app.MainLoop()

    

 	  	 
