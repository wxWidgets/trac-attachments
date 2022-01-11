import wx

class MyApp(wx.App):
    def OnInit(self):
        frame = wx.Frame(None, -1, "TreeCtrl Tooltips")

        self.tree = wx.TreeCtrl(frame, -1)#, style = wx.TR_HAS_BUTTONS | wx.TR_DEFAULT_STYLE | wx.TR_HIDE_ROOT | wx.TR_SINGLE | wx.SUNKEN_BORDER)

        root = self.tree.AddRoot("r00t")

        c1 = self.tree.AppendItem(root, "Topic 1")
        c1a = self.tree.AppendItem(c1, "Item 1")
        c2 = self.tree.AppendItem(root, "Topic 2")
        c3 = self.tree.AppendItem(root, "Topic 3")
        c3a = self.tree.AppendItem(c3, "Item 1")
        c3b = self.tree.AppendItem(c3, "Item 2")
        c3c = self.tree.AppendItem(c3, "Item 3")
        c3d = self.tree.AppendItem(c3, "Item 4")
    
        self.tree.Expand(c1)
        self.tree.Expand(c3)
        self.tree.SelectItem(c1)

        frame.Show(True)
        self.SetTopWindow(frame)
        
#        wx.EVT_MOTION(self.tree, self.OnMouseMotion)
        wx.EVT_TREE_ITEM_GETTOOLTIP(self, -1, self.OnTreeTooltip)

        return True

    #workarond from Robin
    def OnMouseMotion(self, event):
        item, flags = self.tree.HitTest(event.GetPosition())
        if not flags & wx.TREE_HITTEST_ONITEMLABEL:
            self.tree.SetToolTipString("")
        event.Skip()

    def OnTreeTooltip(self, event):
	print "Tool tip!" #debug
        itemtext = self.tree.GetItemText(event.GetItem())
	event.SetToolTip("This is a ToolTip for %s!" % itemtext)
        event.Skip()

app = MyApp(0)
app.MainLoop()



 	  	 
