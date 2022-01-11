import wx, wx.gizmos

class app(wx.App):
    def OnInit(self):
        f = wx.Frame(None, title='press any key a-z')
        widgetId = wx.NewId()
        self.widget = self.makegizmo(widgetId, f)
        f.Show()        
        return True
    
    def populateTree(self, tree, widgetId):
        root = tree.AddRoot('foo')
        for t in range(10):
            treeId = tree.AppendItem(root, str(t))
            tree.SelectItem(treeId, True)
            
        tree.Expand(root)
        return tree
        
        
    def makegizmo(self, widgetId, parent):
        tree = wx.gizmos.TreeListCtrl(id = widgetId,
            name = 'TreeListCtrl', parent = parent,
            style=wx.TR_MULTIPLE | wx.TR_HAS_BUTTONS)

        tree.AddColumn('TreeListCtrl')
        self.populateTree(tree, widgetId)
        tree.DeleteAllItems()
        print 'selection after DeleteAllItems:', tree.GetSelection()
        return tree
    
        
def main():
    a = app(0)
    a.MainLoop()

if __name__ == '__main__':
    main()

 	  	 
