import wx, wx.gizmos
import gc

class app(wx.App):
    def OnInit(self):
        f = wx.Frame(None)
        widgetId = wx.NewId()
        self.widget = self.makegizmo(widgetId,f)
        #self.widget = self.maketree(widgetId,f)
        f.Show()
        
        return True

    def maketree(self,widgetId, parent):
        tree = wx.TreeCtrl(id = widgetId, name = 'TreeCtrl',
                           parent = parent,
            style=wx.TR_MULTIPLE)
        return self.populateTree(tree, widgetId)

    
    def populateTree(self,tree, widgetId, select = True):
        tree.Bind(wx.EVT_TREE_KEY_DOWN, self.doLeak,id = widgetId)
        root = tree.AddRoot('foo')
        for t in range(120):
            treeId = tree.AppendItem(root,str(t))
            tree.SelectItem(treeId, select)
            
        tree.Expand(root)
        return tree
        
        
    def makegizmo(self,widgetId, parent):
        tree = wx.gizmos.TreeListCtrl(id = widgetId,
            name = 'TreeListCtrl', parent = parent,
            style=wx.TR_MULTIPLE | wx.TR_HAS_BUTTONS)

        tree.AddColumn('TreeListCtrl')
        return self.populateTree(tree, widgetId, False)

    
    def doLeak(self,event):
        gc.collect()
        print len(self.widget.GetSelections()),
        gc.collect()
        
        
def main():
    a = app(0)
    a.MainLoop()

if __name__ == '__main__':
    main()

 	  	 
