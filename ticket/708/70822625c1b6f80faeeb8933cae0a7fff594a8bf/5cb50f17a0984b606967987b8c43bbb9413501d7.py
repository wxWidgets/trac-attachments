import wx

class MyFrame(wx.Frame):
    def __init__(self):
        super(MyFrame, self).__init__(None, title="TreeCtrl Focus")

        self.p = MyPanel(self)

class MyPanel(wx.Panel):
    def __init__(self, parent):
        super(MyPanel, self).__init__(parent)

        self.tree = wx.TreeCtrl(self)
        self.tree.AddRoot("The Root")

        # Setup
        bsizer = wx.BoxSizer(wx.HORIZONTAL)
        for x in range(4):
            label = "Branch %d" % x
            i = self.tree.AppendItem(self.tree.RootItem, label)
            for n in range(5):
                self.tree.AppendItem(i, "Child %d" % n)
            self.tree.Expand(i)
            btn = wx.Button(self, label="Delete '%s'" % label)
            bsizer.Add(btn, 0, wx.ALL, 5)
            btn.Bind(wx.EVT_BUTTON, lambda evt, item=i, label=label: self.DoDelete(item, label))

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.tree, 1, wx.EXPAND)
        sizer.Add(bsizer, 0, wx.EXPAND)
        self.SetSizer(sizer)
        self.tree.Expand(self.tree.RootItem)

    def DoDelete(self, item, label):
        print "Delete:", label
#        self.tree.Unselect()
        self.tree.Delete(item)

a = wx.App(False)
f = MyFrame()
f.Show()
a.MainLoop()
