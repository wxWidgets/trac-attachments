#!/usr/bin/python

import wxversion
wxversion.select('2.8')
    
import  wx
import  wx.gizmos   as  gizmos

#----------------------------------------------------------------------

class TestFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1)

        self.tree = gizmos.TreeListCtrl(self, -1, style =wx.TR_DEFAULT_STYLE | wx.TR_FULL_ROW_HIGHLIGHT)

        isz = (16,16)
        il = wx.ImageList(isz[0], isz[1])
        fldridx     = il.Add(wx.ArtProvider_GetBitmap(wx.ART_FOLDER,      wx.ART_OTHER, isz))
        fldropenidx = il.Add(wx.ArtProvider_GetBitmap(wx.ART_FILE_OPEN,   wx.ART_OTHER, isz))
        fileidx     = il.Add(wx.ArtProvider_GetBitmap(wx.ART_NORMAL_FILE, wx.ART_OTHER, isz))

        self.tree.SetImageList(il)
        self.il = il

        # create some columns
        self.tree.AddColumn("Main column")
        self.tree.AddColumn("Column 1")
        self.tree.AddColumn("Column 2")
        self.tree.SetMainColumn(0) # the one with the tree in it...
        self.tree.SetColumnWidth(0, 175)

        self.root = self.tree.AddRoot("The Root Item")
        self.tree.SetItemText(self.root, "col 1 root", 1)
        self.tree.SetItemText(self.root, "col 2 root", 2)
        self.tree.SetItemImage(self.root, fldridx, which = wx.TreeItemIcon_Normal)
        self.tree.SetItemImage(self.root, fldropenidx, which = wx.TreeItemIcon_Expanded)

        for x in range(5):
            txt = "Item %d" % x
            child = self.tree.AppendItem(self.root, txt)
            self.tree.SetItemText(child, txt + "(c1)", 1)
            self.tree.SetItemText(child, txt + "(c2)", 2)
            self.tree.SetItemImage(child, fldridx, which = wx.TreeItemIcon_Normal)
            self.tree.SetItemImage(child, fldropenidx, which = wx.TreeItemIcon_Expanded)

        self.tree.Expand(self.root)

        wx.EVT_TREE_BEGIN_DRAG(self, self.tree.GetId(), self.DirCtrlDragInit)
	wx.EVT_TREE_END_DRAG(self, self.tree.GetId(), self.DirCtrlDragEnd)

    def DirCtrlDragInit(self, event):
        event.Allow()
	print("Init drag")
	    
	    
    def DirCtrlDragEnd(self, event):
        print("End drag")

#----------------------------------------------------------------------

if __name__ == '__main__':
    application = wx.App(redirect=False,clearSigInt=False)
    gui = TestFrame(None)
    application.SetTopWindow(gui)
    gui.Show()
    application.MainLoop()
