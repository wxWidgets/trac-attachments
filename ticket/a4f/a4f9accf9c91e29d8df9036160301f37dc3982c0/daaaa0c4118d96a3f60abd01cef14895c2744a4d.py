import wx
import wx.gizmos as gizmos

class TestPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        self.DragItem = None
        self.Bind(wx.EVT_SIZE, self.OnSize)
        self.tree = gizmos.TreeListCtrl(self, -1, style = wx.TR_DEFAULT_STYLE
                                        | wx.TR_FULL_ROW_HIGHLIGHT)
        isz = (16,16)
        il = wx.ImageList(isz[0], isz[1])
        fldridx = il.Add(wx.ArtProvider_GetBitmap(wx.ART_FOLDER, wx.ART_OTHER, isz))
        fldropenidx = il.Add(wx.ArtProvider_GetBitmap(wx.ART_FILE_OPEN, wx.ART_OTHER, isz))
        self.fileidx = il.Add(wx.ArtProvider_GetBitmap(wx.ART_NORMAL_FILE, wx.ART_OTHER, isz))
        self.tree.SetImageList(il)
        self.il = il
        self.tree.AddColumn("Main column")
        self.tree.SetMainColumn(0)
        self.tree.SetColumnWidth(0, 175)
        self.root = self.tree.AddRoot("The Root Item")
        self.tree.SetItemImage(self.root, fldridx, which = wx.TreeItemIcon_Normal)
        self.tree.SetItemImage(self.root, fldropenidx, which = wx.TreeItemIcon_Expanded)
        for x in range(15):
            txt = "Item %d" % x
            child = self.tree.AppendItem(self.root, txt)
            self.tree.SetItemImage(child, fldridx, which = wx.TreeItemIcon_Normal)
            self.tree.SetItemImage(child, fldropenidx, which = wx.TreeItemIcon_Expanded)
            for y in range(5):
                txt = "item %d-%s" % (x, chr(ord("a")+y))
                item = self.tree.AppendItem(child,  txt)
                self.tree.SetItemImage(item, self.fileidx, which = wx.TreeItemIcon_Normal)
                self.tree.SetItemImage(item, self.fileidx, which = wx.TreeItemIcon_Selected)
        self.tree.Expand(self.root)
        self.tree.Bind(wx.EVT_TREE_BEGIN_DRAG, self.OnBeginDrag)
        self.tree.Bind(wx.EVT_TREE_END_DRAG, self.OnEndDrag)

    def OnBeginDrag(self, evt):
        if not self.tree.ItemHasChildren(evt.GetItem()):
            evt.Allow()
            self.DragItem = evt.GetItem()
            print self.tree.GetItemText(self.DragItem)

    def OnEndDrag(self, evt):
        old = self.DragItem
        if old is None:
            return
        new_ = evt.GetItem()
        if not new_.IsOk() or new_ == old:
            return
        parent = self.tree.GetItemParent(new_)
        OldParent = self.tree.GetItemParent(old)
        if new_ != OldParent and parent != OldParent:
            self.tree.UnselectAll()
            self.tree.SelectItem(old)
            return
        text = self.tree.GetItemText(old, 0)
        self.tree.Delete(old)
        if new_ == OldParent:
            child = self.tree.InsertItemBefore(new_, 0, text)
        else:
            child = self.tree.InsertItem(parent, new_, text)
        self.tree.SetItemImage(child, self.fileidx,
                               which = wx.TreeItemIcon_Normal)
        self.tree.SetItemImage(child, self.fileidx,
                               which = wx.TreeItemIcon_Expanded)
        self.tree.SelectItem(child)
        self.DragItem = None

    def OnSize(self, evt):
        self.tree.SetSize(self.GetSize())

def main():
    app = wx.PySimpleApp()
    frame = wx.Frame(None, -1, 'TreeListCtrl', size=(200, 400))
    panel = TestPanel(frame)
    frame.Show()
    app.MainLoop()

if __name__ == '__main__':
    main()

 	  	 
