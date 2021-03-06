
from wxPython.wx import *

import string

#---------------------------------------------------------------------------

class MyTreeCtrl(wxTreeCtrl):
    def __init__(self, parent, id, pos, size, style, log):
        wxTreeCtrl.__init__(self, parent, id, pos, size, style)
        self.log = log

    def OnCompareItems(self, item1, item2):
        t1 = self.GetItemText(item1)
        t2 = self.GetItemText(item2)
        self.log.WriteText('compare: ' + t1 + ' <> ' + t2 + '\n')
        if t1 < t2: return -1
        if t1 == t2: return 0
        return 1

#---------------------------------------------------------------------------

class TestTreeCtrlPanel(wxPanel):
    def __init__(self, parent, log):
        # Use the WANTS_CHARS style so the panel doesn't eat the Return key.
        wxPanel.__init__(self, parent, -1, style=wxWANTS_CHARS)
        EVT_SIZE(self, self.OnSize)

        self.log = log
        tID = NewId()

        self.tree = MyTreeCtrl(self, tID, wxDefaultPosition, wxDefaultSize,
                               wxTR_HAS_BUTTONS
                               | wxTR_EDIT_LABELS
                               | wxTR_MULTIPLE, self.log)


        ##import images
        ##il = wxImageList(16, 16)
        ##idx1 = il.Add(images.getSmilesBitmap())
        ##idx2 = il.Add(images.getOpenBitmap())
        ##idx3 = il.Add(images.getNewBitmap())
        ##idx4 = il.Add(images.getCopyBitmap())
        ##idx5 = il.Add(images.getPasteBitmap())

        ##self.tree.SetImageList(il)
        ##self.il = il

        # NOTE:  For some reason tree items have to have a data object in
        #        order to be sorted.  Since our compare just uses the labels
        #        we don't need any real data, so we'll just use None.

        self.root = self.tree.AddRoot("The Root Item")
        self.tree.SetPyData(self.root, None)
        ##self.tree.SetItemImage(self.root, idx1)

        for x in range(15):
            child = self.tree.AppendItem(self.root, "Item %d" % x)
            self.tree.SetPyData(child, None)
            ##self.tree.SetItemImage(child, idx2, wxTreeItemIcon_Expanded)
            ##self.tree.SetItemSelectedImage(child, idx3)
            for y in range(5):
                last = self.tree.AppendItem(child, "item %d-%s" % (x, chr(ord("a")+y)))
                self.tree.SetPyData(last, None)
                ##self.tree.SetItemImage(last, idx4)
                ##self.tree.SetItemSelectedImage(last, idx5)
                for z in range(5):
                    item = self.tree.AppendItem(last,  "item %d-%s-%d" % (x, chr(ord("a")+y), z))
                    self.tree.SetPyData(item, None)

        self.tree.Expand(self.root)
        EVT_TREE_ITEM_EXPANDED  (self, tID, self.OnItemExpanded)
        EVT_TREE_ITEM_COLLAPSED (self, tID, self.OnItemCollapsed)
        EVT_TREE_SEL_CHANGED    (self, tID, self.OnSelChanged)
        EVT_TREE_BEGIN_LABEL_EDIT(self, tID, self.OnBeginEdit)
        EVT_TREE_END_LABEL_EDIT (self, tID, self.OnEndEdit)
        EVT_TREE_ITEM_ACTIVATED (self, tID, self.OnActivate)

        EVT_LEFT_DCLICK(self.tree, self.OnLeftDClick)
        EVT_RIGHT_DOWN(self.tree, self.OnRightClick)
        EVT_RIGHT_UP(self.tree, self.OnRightUp)
        EVT_LEFT_DOWN(self.tree, self.OnLeftDown)



    def OnRightClick(self, event):
        pt = event.GetPosition();
        item, flags = self.tree.HitTest(pt)
        self.log.WriteText("OnRightClick: %s, %s, %s\n" %
                           (self.tree.GetItemText(item), type(item), item.__class__))
        self.tree.SelectItem(item)


    def OnRightUp(self, event):
        pt = event.GetPosition();
        item, flags = self.tree.HitTest(pt)
        self.log.WriteText("OnRightUp: %s (manually starting label edit)\n"
                           % self.tree.GetItemText(item))
        self.tree.EditLabel(item)

    # prg added
    def OnLeftDown(self, event):
      self.log.WriteText("OnLeftDown")  # prg debug
      self.itemGrabbed = False  # reset
      self.currentViewer = event.GetEventObject()
      pt = event.GetPosition();
      item, flags = self.currentViewer.HitTest(pt)
      self.itemGrabbed = (flags == 16 or flags == 64)
      if item.IsOk():  # need this to prevent sys crash when tree has no items
        itemText = self.currentViewer.GetItemText(item)
        self.entityObj = self.currentViewer.GetPyData(item)
      event.Skip()


    def OnBeginEdit(self, event):
        self.log.WriteText("OnBeginEdit\n")
        # show how to prevent edit...
        if self.tree.GetItemText(event.GetItem()) == "The Root Item":
            wxBell()
            self.log.WriteText("You can't edit this one...\n")

            # Lets just see what's visible of its children
            cookie = 0
            root = event.GetItem()
            (child, cookie) = self.tree.GetFirstChild(root, cookie)
            while child.IsOk():
                self.log.WriteText("Child [%s] visible = %d" %
                                   (self.tree.GetItemText(child),
                                    self.tree.IsVisible(child)))
                (child, cookie) = self.tree.GetNextChild(root, cookie)

            event.Veto()


    def OnEndEdit(self, event):
        self.log.WriteText("OnEndEdit\n")
        # show how to reject edit, we'll not allow any digits
        for x in event.GetLabel():
            if x in string.digits:
                self.log.WriteText("You can't enter digits...\n")
                event.Veto()
                return


    def OnLeftDClick(self, event):
        pt = event.GetPosition();
        item, flags = self.tree.HitTest(pt)
        self.log.WriteText("OnLeftDClick: %s\n" % self.tree.GetItemText(item))
        parent = self.tree.GetItemParent(item)
        self.tree.SortChildren(parent)
        event.Skip()


    def OnSize(self, event):
        w,h = self.GetClientSizeTuple()
        self.tree.SetDimensions(0, 0, w, h)


    def OnItemExpanded(self, event):
        item = event.GetItem()
        self.log.WriteText("OnItemExpanded: %s\n" % self.tree.GetItemText(item))

    def OnItemCollapsed(self, event):
        item = event.GetItem()
        self.log.WriteText("OnItemCollapsed: %s\n" % self.tree.GetItemText(item))

    def OnSelChanged(self, event):
        self.item = event.GetItem()
        self.log.WriteText("OnSelChanged: %s\n" % self.tree.GetItemText(self.item))
        if wxPlatform == '__WXMSW__':
            self.log.WriteText("BoundingRect: %s\n" %
                               self.tree.GetBoundingRect(self.item, true))
        #items = self.tree.GetSelections()
        #print map(self.tree.GetItemText, items)
        self.tree.SetItemText(self.item, "Selected")
        event.Skip()


    def OnActivate(self, evt):
        self.log.WriteText("OnActivate: %s\n" % self.tree.GetItemText(self.item))


#---------------------------------------------------------------------------

def runTest(frame, nb, log):
    win = TestTreeCtrlPanel(nb, log)
    return win

#---------------------------------------------------------------------------





overview = """\
A tree control presents information as a hierarchy, with items that may be expanded to show further items. Items in a tree control are referenced by wxTreeItemId handles.

"""



if __name__ == '__main__':
    import sys,os
    import run
    run.main(['', os.path.basename(sys.argv[0])])


 	  	 
