# -*- coding: iso-8859-1 -*-

import wx, random, time, wx.lib.newevent
import wx.gizmos
import threading, thread
from wx.lib.mixins import treemixin

(OnNewTest, EVT_NEW_TEST) = wx.lib.newevent.NewEvent()


#################################
######  TEST RULES BROWSER  #####
#################################

class DragAndDrop(treemixin.DragAndDrop):
    def OnDrop(self, *args): pass
class Tree(DragAndDrop, wx.gizmos.TreeListCtrl):
    def __init__(self, *args, **kargs):
        super(Tree, self).__init__(*args, **kargs)

ID_GIZMOSTREECTRL = 2003

class TestFrame(wx.Frame) :
    def __init__(self, parent) :
        wx.Frame.__init__(self, parent, -1, "Test RulesBrowser")
        
        # Taille de la fenetre
        self.SetSize((800,600))
        
        item0 = wx.FlexGridSizer( 2, 0, 0, 0 )
        self.SetSizer(item0)
        item0.AddGrowableCol( 0 )
        item0.AddGrowableRow( 1 )
        
        item1 = wx.BoxSizer( wx.HORIZONTAL )
        
        item4 = wx.Button( self, ID_GIZMOSTREECTRL, "Launch test", wx.DefaultPosition, wx.DefaultSize, 0 )
        item1.Add( item4, 0, wx.ALIGN_CENTER|wx.ALL, 5 )

        item0.Add( item1, 0, wx.ALIGN_CENTER|wx.ALL, 5 )
        
        self._treeListCtrl =  Tree(self, ID_GIZMOSTREECTRL, style=wx.TR_NO_BUTTONS  | wx.TR_ROW_LINES | wx.TR_MULTIPLE | wx.TR_HIDE_ROOT | wx.TR_EDIT_LABELS | wx.TR_NO_LINES  | wx.TR_FULL_ROW_HIGHLIGHT)
        isz = 16, 16
        il = wx.ImageList(isz[0], isz[1])
        self.fldridx     = il.Add(wx.ArtProvider_GetBitmap(wx.ART_FOLDER,      wx.ART_OTHER, isz))
        self.fldropenidx = il.Add(wx.ArtProvider_GetBitmap(wx.ART_FILE_OPEN,   wx.ART_OTHER, isz))
        self.fileidx     = il.Add(wx.ArtProvider_GetBitmap(wx.ART_NORMAL_FILE, wx.ART_OTHER, isz))

        self._treeListCtrl.SetImageList(il)
        self.il = il

        
        item0.Add( self._treeListCtrl, 0, wx.GROW|wx.ALIGN_CENTER_VERTICAL|wx.ALL, 5 )
        
        self.initGizmosTree()
        
        item4.Bind(wx.EVT_BUTTON, self.onLaunchTest)
        self._treeListCtrl.Bind(wx.EVT_TREE_KEY_DOWN,                         self.onKeyDown)

        
        self.Bind(EVT_NEW_TEST, self.updateTree)
        
        
        
    def initGizmosTree(self) :
        for i in range(8) :
            label = "Column " + str(i)
            self._treeListCtrl.AddColumn(label)
            self._treeListCtrl.SetColumnWidth(i, 100)
        self._treeListCtrl.SetMainColumn(0)
        
        
    
    def updateTree(self, event) :
        #print "updateTree"
        
        self._treeListCtrl.DeleteAllItems()
        rootItem = self._treeListCtrl.AddRoot('')   
        
        length = random.randint(0, 100)

        for i in range(length) :
            col = 0
            item = self._treeListCtrl.AppendItem(rootItem, "Line " + str(i) + "/" + str(col))

            for j in range(7) :
                col = j + 1
                self._treeListCtrl.SetItemText(item, "Line " + str(i) + "/" + str(col), col)
                self._treeListCtrl.SetItemImage(item, self.fldridx)
            for aa in range(2):
                newitem = self._treeListCtrl.AppendItem(item, "Child " + str(j) + "/" + str(col))
                for j in range(7) :
                    col = j + 1
                    self._treeListCtrl.SetItemText(newitem, "Child " + str(j) + "/" + str(col), col)
                    self._treeListCtrl.SetItemImage(newitem, self.fileidx)
        
        
    def onLaunchTest(self, event) :
        #endJob = threading.Event()
        
        
        #thread.start_new_thread(self.launchTest,(endJob, ))
        #thread.start_new_thread(self._waitLaunchTest,(endJob, ))
        self.launchTest(None)
        
    def _waitLaunchTest(self, endJob) :
        endJob.wait()
        
        
    def launchTest(self, endJob) :
        print "Test"
        
        for j in range(1) :
            #self.updateTree(None)
            self.GetEventHandler().ProcessEvent(OnNewTest())
            
        if endJob :
            endJob.set()
    def onKeyDown(self, evt):
        keyEvt = evt.GetKeyEvent()

        # Actions
        if evt.GetKeyCode() == wx.WXK_SPACE and keyEvt.GetModifiers() == wx.MOD_NONE:
            item    = self._treeListCtrl.GetSelection()
            if item.IsOk(): self._treeListCtrl.EditLabel(item)
        else: evt.Skip()

class TestApp(wx.App):
    def __init__(self) :
        wx.App.__init__(self, 0)
        
    def OnInit(self):
        wx.InitAllImageHandlers()
        self._frame = TestFrame(None)
        self._frame.Show(True)
        self.SetTopWindow(self._frame)
        return True

        
class Test :
    def __init__(self) :
        app = TestApp()
        app.MainLoop()
        
    
def main() :
    # Il est normal d'avoir un message "ERREUR..."
    # qui correspond à l'absence de réponse du serveur
    Test()

if __name__ == '__main__':
    main()

 	  	 
