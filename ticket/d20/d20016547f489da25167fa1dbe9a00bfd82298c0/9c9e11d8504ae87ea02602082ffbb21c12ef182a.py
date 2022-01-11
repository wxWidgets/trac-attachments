from wxPython.wx import *

class ResourceTree( wxTreeCtrl):
    def __init__( self, parent):
        wxTreeCtrl.__init__( self, parent, -1, style= wxTR_MULTIPLE |wxTR_EXTENDED |wxTR_HAS_BUTTONS  )
        EVT_TREE_BEGIN_DRAG(self, self.GetId(), self.OnBeginDrag)
        self.BuildItems()
    def BuildItems( self ):
        """Create the tree items from the application's resource table"""
        self.DeleteAllItems()
        self.rootID = self.AddRoot( "Resources")
        for rootItem in ['a','b','c']:
            ID = self.AppendItem( self.rootID, rootItem )
        self.Expand( self.rootID )
    def OnBeginDrag( self, event ):
        """Handle the start of a drag to the list"""
        print 'OnBeginDrag', self.GetSelections()

if __name__ == "__main__":
    class TestApplication (wxPySimpleApp):
        def OnInit(self):
            wxInitAllImageHandlers()
            frame =wxFrame (NULL, -1, "test", size = (600,300))
            panel = ResourceTree(frame)
            frame.Show (1)
            self.SetTopWindow(frame)
            return 1
    
    app = TestApplication ()
    app.MainLoop()


 	  	 
