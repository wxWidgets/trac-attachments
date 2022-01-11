import wx
from wx.lib.agw.hypertreelist import HyperTreeList
from wx import gizmos as gizmos

class apanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, id=wx.ID_ANY)
        #add a vertical sizer to this panel
        sizer = wx.BoxSizer(orient=wx.VERTICAL)

        agwStyle = (
            wx.TR_DEFAULT_STYLE | wx.TR_HAS_BUTTONS | 
            wx.TR_HIDE_ROOT | 
            wx.TR_MULTIPLE | 
            wx.TR_HAS_VARIABLE_ROW_HEIGHT 

        )

        self.tree_list = HyperTreeList(self, size=(-1, 800), agwStyle=agwStyle)

        #tree_list.EnableSelectionVista(True)
        column = self.tree_list.AddColumn("RMA", width=200)
        column = self.tree_list.AddColumn("labels", width=200)
        column = self.tree_list.AddColumn("labels", width=200)

        self.tree_list.SetColumnEditable(1, True)
        
        sizer.AddF(self.tree_list, wx.SizerFlags(1).Expand().Border(wx.ALL, 5))
        self.SetSizer(sizer)

class MainFrame(wx.Frame):

    def __init__(self, parent):
        
        wx.Frame.__init__(self, parent, -1, "Subclassing HyperTreeList", size=(400, 400))
        self.panel = apanel(self)
        menu_bar = wx.MenuBar()
        menu = wx.Menu()
        item = wx.MenuItem(menu, wx.NewId(), "DeleteAllItems")
        menu.AppendItem(item)
        menu_bar.Append(menu, "Functions")
        self.Bind(wx.EVT_MENU, self.menuClicked, item)
        self.SetMenuBar(menu_bar)

        self.createTreeListItems()

        self.panel.tree_list.SetItemBackgroundColour(self.panel.tree_list.GetFirstChild(self.first)[0], wx.RED)
        self.panel.tree_list.Bind(wx.EVT_TREE_SEL_CHANGED, self.OnTreeClick)


    def menuClicked(self, event):
        self.panel.tree_list.DeleteAllItems()
        self.createTreeListItems()

    def createTreeListItems(self):
        root = self.panel.tree_list.AddRoot("Root")

        # create 2 nodes
        self.first = self.panel.tree_list.AppendItem(root, "First Node")
        second = self.panel.tree_list.AppendItem(root, "Second Node")
        
        # create sub nodes
        for i in xrange(0, 5) :
            itemIndex = self.panel.tree_list.AppendItem(self.first, "SubNode 1.%s" % (i + 1))
            self.panel.tree_list.SetItemText(itemIndex, "blahZany!!!", 1)
            self.panel.tree_list.AppendItem(second, "SubNode 2.%s" % (i + 1))

    def OnTreeClick(self, event):
        print type(event.GetEventObject())
        print event.GetEventObject()

if __name__ == "__main__" :
    app = wx.App()
    frame = MainFrame(None)
    app.SetTopWindow(frame)
    frame.Show()
    app.MainLoop()
