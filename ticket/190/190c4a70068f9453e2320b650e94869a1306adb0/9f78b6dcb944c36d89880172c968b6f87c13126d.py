# TreeTest.py

# Trying to get the right selection behaviour with a tree

from wxPython.wx import *

class MyTree(wxTreeCtrl):

    def __init__(self, parent, id, style):
        wxTreeCtrl.__init__(self, parent, id, style = style)

        self.eventCount = 0
        self.selectedItems = []
        self.possibleDrag = false
        
        # Some tests
        EVT_LEFT_DOWN(self, self.onLeftDown)
        EVT_LEFT_UP(self, self.onLeftUp)
        EVT_TREE_SEL_CHANGING(self, self.GetId(), self.onSelectionChanging)
        EVT_TREE_SEL_CHANGED(self, self.GetId(), self.onSelectionChanged)
        
    def onLeftDown(self, event):
        self.printEvent("LEFT_DOWN")
        event.Skip()

    def onLeftUp(self, event):
        self.printEvent("LEFT_UP")
        event.Skip()

    def onSelectionChanging(self, event):
        item = event.GetItem()
        oldItem = event.GetOldItem()

        self.printEvent("SEL_CHANGING (itemOK:%d oldItemOK:%d)" % (item.IsOk(), oldItem.IsOk()))

        event.Skip()

    def onSelectionChanged(self, event):
        item = event.GetItem()
        oldItem = event.GetOldItem()

        self.printEvent("SEL_CHANGED (itemOK:%d oldItemOK:%d)" % (item.IsOk(), oldItem.IsOk()))

        event.Skip()

    def printEvent(self, text):
        print "%d: %s (%d items selected)" % (self.eventCount, text,
                                              len(self.GetSelections()))
        self.eventCount = self.eventCount + 1
        
class MyApp(wxApp):

    def OnInit(self):
        frame = wxFrame(NULL, 1, "Tree Test")
        tree = MyTree(frame,
                      -1,
                      style = (wxTR_HAS_BUTTONS |
                               wxTR_NO_LINES |
                               wxTR_MULTIPLE |
                               wxNO_BORDER))
        frame.Show(true)
        self.SetTopWindow(frame)
        self.doTest(tree)
        
        return true

    def doTest(self, tree):
        root = tree.AddRoot("Root")
        
        for i in range(10):
            item = tree.AppendItem(root, "Item %d" % i)
            
            for j in range(5):
                tree.AppendItem(item, "Child %d" % j)
                
        tree.Expand(root)

if __name__ == "__main__":
    app = MyApp(0)
    app.MainLoop()

 	  	 
