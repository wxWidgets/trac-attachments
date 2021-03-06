
import  string
import  wx
import  images

#---------------------------------------------------------------------------

class MyTreeCtrl(wx.TreeCtrl):
    def __init__(self, parent, id, pos, size, style, log):
        wx.TreeCtrl.__init__(self, parent, id, pos, size, style)
        self.log = log

    def OnCompareItems(self, item1, item2):
        t1 = self.GetItemText(item1)
        t2 = self.GetItemText(item2)
        self.log.WriteText('compare: ' + t1 + ' <> ' + t2 + '\n')
        if t1 < t2: return -1
        if t1 == t2: return 0
        return 1

#---------------------------------------------------------------------------

class TestTreeCtrlPanel(wx.Panel):
    def __init__(self, parent, log):
        # Use the WANTS_CHARS style so the panel doesn't eat the Return key.
        wx.Panel.__init__(self, parent, -1, style=wx.WANTS_CHARS)
        self.Bind(wx.EVT_SIZE, self.OnSize)

        self.log = log
        tID = wx.NewId()

        self.tree = MyTreeCtrl(self, tID, wx.DefaultPosition, wx.DefaultSize,
                               wx.TR_HAS_BUTTONS
                               | wx.TR_EDIT_LABELS
                               #| wx.TR_MULTIPLE
                               #| wx.TR_HIDE_ROOT
                               , self.log)

        isz = (16,16)
        il = wx.ImageList(isz[0], isz[1])
        fldridx     = il.Add(wx.ArtProvider_GetBitmap(wx.ART_FOLDER,      wx.ART_OTHER, isz))
        fldropenidx = il.Add(wx.ArtProvider_GetBitmap(wx.ART_FILE_OPEN,   wx.ART_OTHER, isz))
        fileidx     = il.Add(wx.ArtProvider_GetBitmap(wx.ART_REPORT_VIEW, wx.ART_OTHER, isz))
        smileidx    = il.Add(images.getSmilesBitmap())

        self.tree.SetImageList(il)
        self.il = il

        # NOTE:  For some reason tree items have to have a data object in
        #        order to be sorted.  Since our compare just uses the labels
        #        we don't need any real data, so we'll just use None below for
        #        the item data.

        self.root = self.tree.AddRoot("The Root Item")
        self.tree.SetPyData(self.root, None)
        self.tree.SetItemImage(self.root, fldridx, wx.TreeItemIcon_Normal)
        self.tree.SetItemImage(self.root, fldropenidx, wx.TreeItemIcon_Expanded)


        for x in range(15):
            child = self.tree.AppendItem(self.root, "Item %d" % x)
            self.tree.SetPyData(child, None)
            self.tree.SetItemImage(child, fldridx, wx.TreeItemIcon_Normal)
            self.tree.SetItemImage(child, fldropenidx, wx.TreeItemIcon_Expanded)

            for y in range(5):
                last = self.tree.AppendItem(child, "item %d-%s" % (x, chr(ord("a")+y)))
                self.tree.SetPyData(last, None)
                self.tree.SetItemImage(last, fldridx, wx.TreeItemIcon_Normal)
                self.tree.SetItemImage(last, fldropenidx, wx.TreeItemIcon_Expanded)

                for z in range(5):
                    item = self.tree.AppendItem(last,  "item %d-%s-%d" % (x, chr(ord("a")+y), z))
                    self.tree.SetPyData(item, None)
                    self.tree.SetItemImage(item, fileidx, wx.TreeItemIcon_Normal)
                    self.tree.SetItemImage(item, smileidx, wx.TreeItemIcon_Selected)

        self.tree.Expand(self.root)
        self.Bind(wx.EVT_TREE_ITEM_EXPANDED, self.OnItemExpanded, self.tree)
        self.Bind(wx.EVT_TREE_ITEM_COLLAPSED, self.OnItemCollapsed, self.tree)
        self.Bind(wx.EVT_TREE_SEL_CHANGED, self.OnSelChanged, self.tree)
        self.Bind(wx.EVT_TREE_BEGIN_LABEL_EDIT, self.OnBeginEdit, self.tree)
        self.Bind(wx.EVT_TREE_END_LABEL_EDIT, self.OnEndEdit, self.tree)
        self.Bind(wx.EVT_TREE_ITEM_ACTIVATED, self.OnActivate, self.tree)

        self.tree.Bind(wx.EVT_LEFT_DCLICK, self.OnLeftDClick)
        self.tree.Bind(wx.EVT_RIGHT_DOWN, self.OnRightClick)
        self.tree.Bind(wx.EVT_RIGHT_UP, self.OnRightUp)
        # These go at the end of __init__
        self.tree.Bind(wx.EVT_TREE_BEGIN_DRAG, self.OnBeginDrag)
        self.tree.Bind(wx.EVT_TREE_END_DRAG, self.OnEndDrag)


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



    def OnBeginEdit(self, event):
        self.log.WriteText("OnBeginEdit\n")
        # show how to prevent edit...
        if self.tree.GetItemText(event.GetItem()) == "The Root Item":
            wx.Bell()
            self.log.WriteText("You can't edit this one...\n")

            # Lets just see what's visible of its children
            cookie = 0
            root = event.GetItem()
            (child, cookie) = self.tree.GetFirstChild(root)

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
        if wx.Platform == '__WXMSW__':
            self.log.WriteText("BoundingRect: %s\n" %
                               self.tree.GetBoundingRect(self.item, True))
        #items = self.tree.GetSelections()
        #print map(self.tree.GetItemText, items)
        event.Skip()


    def OnActivate(self, event):
        self.log.WriteText("OnActivate: %s\n" % self.tree.GetItemText(self.item))

    def OnBeginDrag(self, event):
        '''Allow drag-and-drop for leaf nodes.'''
        self.log.WriteText("OnBeginDrag")
        if self.tree.GetChildrenCount(event.GetItem()) == 0:
            event.Allow()
            self.dragItem = event.GetItem()
        else:
            self.log.WriteText("Cant drag a node that has children")

    def OnEndDrag(self, event):
        '''Do the re-organization if possible'''
        #If we dropped somewhere that isn't on top of an item, ignore the event
        self.log.WriteText("OnEndDrag")
        if not event.GetItem().IsOk():
            return

        # Make sure this memeber exists.
        try:
            old = self.dragItem
        except:
            return

        # Get the other IDs that are involved
        new = event.GetItem()
        parent = self.tree.GetItemParent(new)
        if not parent.IsOk():
            return

        # Move 'em
        #text = self.tree.GetItemText(old)
        #self.tree.Delete(old)
        #self.tree.InsertItem(parent, new, text)

        
#---------------------------------------------------------------------------

def runTest(frame, nb, log):
    win = TestTreeCtrlPanel(nb, log)
    return win

#---------------------------------------------------------------------------





overview = """\
A TreeCtrl presents information as a hierarchy, with items that may be 
expanded to show further items. Items in a tree control are referenced by 
wx.TreeItemId handles.

"""



if __name__ == '__main__':
    import sys,os
    import run
    run.main(['', os.path.basename(sys.argv[0])] + sys.argv[1:])


 	  	 
