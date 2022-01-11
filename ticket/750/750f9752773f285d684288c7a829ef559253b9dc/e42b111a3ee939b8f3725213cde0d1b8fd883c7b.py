
import wx
from wx.gizmos import TreeListCtrl


class A(TreeListCtrl):
    def __init__(self,*args,**kwds):
        kwds["style"] = \
            wx.TR_FULL_ROW_HIGHLIGHT|\
            wx.TR_HIDE_ROOT|\
            wx.TR_NO_BUTTONS|\
            wx.TR_NO_LINES#|\
##            wx.TR_HAS_BUTTONS

        TreeListCtrl.__init__( self, args[0], -1, **kwds )

        self.AddColumn('col1')
        self.AddColumn('col2')
        self.AddColumn('col3')
        
        self.root = self.AddRoot('root')
        self.root = self.AppendItem( self.root, 'Birds')
        for i in range(12000):
            item = self.AppendItem( self.root, 'item %d'%i )
            self.SetItemText( item, 'col1', 1 )
            self.SetItemText( item, 'col2', 2 )



app=wx.PySimpleApp(0)
frm=wx.Frame(None,-1,'Frame',size=(400, 800))
tree = A(frm)
app.SetTopWindow(frm)
frm.Show(1)
app.MainLoop()
 	  	 
