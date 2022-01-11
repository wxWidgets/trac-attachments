import wx
import time

id_tree1 = wx.NewId()
id_list1 = wx.NewId()
id_exit = wx.NewId()
id_about = wx.NewId()

class ExampleApp(wx.App):
    def __init__(self):
        wx.App.__init__( self, 0 )

    def OnInit(self):
        self.frame = ExampleAppFrame( None, -1, 'Example App')
        self.frame.Show( True )
        self.SetTopWindow( self.frame )

        return True

class ExampleListPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        wx.EVT_SIZE(self, self.OnSize)

	self.list_ctrl = wx.ListCtrl( self, id_list1,
						wx.DefaultPosition,
						wx.DefaultSize,
						wx.LC_REPORT|wx.NO_BORDER )
	self.list_ctrl.InsertColumn( 0, 'First', wx.LIST_FORMAT_LEFT, 100 )
	self.list_ctrl.InsertColumn( 1, 'Second', wx.LIST_FORMAT_LEFT, 100 )
	self.list_ctrl.InsertColumn( 2, 'Third', wx.LIST_FORMAT_LEFT, 100)

    def OnSize(self, event):
        w,h = self.GetClientSizeTuple()
        print 'ExampleListPanel:OnSize()',w,h
        self.list_ctrl.SetDimensions(10, 100, w-20, h-120)

class ExampleTreeCtrl(wx.TreeCtrl):
    def __init__(self, parent, id, pos, size, style):
        wx.TreeCtrl.__init__(self, parent, id, pos, size, style)

    def OnCompareItems(self, item1, item2):
        print 'OnCompareItems'
        t1 = self.GetItemText(item1)
        t2 = self.GetItemText(item2)
        if t1 < t2: return -1
        if t1 == t2: return 0
        return 1

class ExampleTreePanel(wx.Panel):
    def __init__(self, parent):
        self._id = 0

        wx.Panel.__init__(self, parent, -1)
        wx.EVT_SIZE(self, self.OnSize)

        self.tree_ctrl = ExampleTreeCtrl(self, id_tree1, wx.DefaultPosition, wx.DefaultSize, wx.TR_HAS_BUTTONS )
        self.root = self.tree_ctrl.AddRoot("Example Tree")
        self.tree_ctrl.SetPyData(self.root, self._newId())

        for x in range(15):
            child = self.tree_ctrl.AppendItem(self.root, "Item %d" % x)
            self.tree_ctrl.SetPyData(child, self._newId())
            for y in range(5):
                last = self.tree_ctrl.AppendItem(child, "item %d-%s" % (x, chr(ord("a")+y)))
                self.tree_ctrl.SetPyData(last, self._newId())
                for z in range(5):
                    item = self.tree_ctrl.AppendItem(last, "item %d-%s-%d" % (x, chr(ord("a")+y), z))
                    self.tree_ctrl.SetPyData(item, self._newId())

        self.tree_ctrl.Expand(self.root)
        wx.EVT_TREE_ITEM_EXPANDED( self, id_tree1, self.OnItemExpanded)
        wx.EVT_TREE_ITEM_COLLAPSED( self, id_tree1, self.OnItemCollapsed)
        wx.EVT_TREE_SEL_CHANGED( self, id_tree1, self.OnSelChanged)

        wx.EVT_RIGHT_DOWN(self.tree_ctrl, self.OnRightDown)
        wx.EVT_RIGHT_UP(self.tree_ctrl, self.OnRightUp)

    def _newId(self):
        self._id = self._id + 1
        return self._id

    def OnRightDown( self, event ):
	# move the selection to the clicked on node
	point = event.GetPosition();
	item, flags = self.tree_ctrl.HitTest( point )
        print "OnRightClick: %s, %s" % (self.tree_ctrl.GetItemText(item), type(item))
	self.tree_ctrl.SelectItem( item )

    def OnRightUp( self, event ):
	# move the selection to the clicked on node
	point = event.GetPosition();
	item, flags = self.tree_ctrl.HitTest( point )
        print "OnRightUp: %s " % self.tree_ctrl.GetPyData(item)
	self.tree_ctrl.SelectItem( item )

	menu = wx.Menu()
	menu.Append( id_about, 'About' )
	self.tree_ctrl.PopupMenu( menu, event.GetPosition() )
	menu.Destroy()

    def OnSize(self, event):
        w,h = self.GetClientSizeTuple()
        print 'ExampleTreeCtrl:OnSize()',w,h
        self.tree_ctrl.SetDimensions(10, 100, w-20, h-120)

    def OnItemExpanded(self, event):
        item = event.GetItem()
        print "OnItemExpanded: %s" % self.tree_ctrl.GetItemText(item)

    def OnItemCollapsed(self, event):
        item = event.GetItem()
        print "OnItemCollapsed: %s" % self.tree_ctrl.GetItemText(item)

    def OnSelChanged(self, event):
        self.item = event.GetItem()
        print "OnSelChanged: %s %s" % (self.tree_ctrl.GetPyData(self.item), self.tree_ctrl.GetItemText(self.item))
        print "BoundingRect: %s" % self.tree_ctrl.GetBoundingRect(self.item, True)

class ExampleAppFrame(wx.Frame):
    def __init__(self, parent, id, title ):
        wx.Frame.__init__(self, parent, -1, title,
                         wx.DefaultPosition, wx.Size(700, 550), wx.DEFAULT_FRAME_STYLE )

        self.size_init = 0

        self.menu_bar = wx.MenuBar()
        self.SetMenuBar( self.menu_bar )
        self.menu_file = wx.Menu()
        self.menu_file.Append( id_exit, "Exit", "Exit the application" )

        self.menu_help = wx.Menu()
        self.menu_help.Append( id_about, "About", "About Application" )

        self.menu_bar.Append( self.menu_file, "File" )
        self.menu_bar.Append( self.menu_help, "Help" )

        self.splitter = wx.SplitterWindow( self, -1 )

        self.panel1 = ExampleTreePanel( self.splitter )
        self.panel2 = ExampleListPanel( self.splitter )

        self.splitter.SetMinimumPaneSize( 100 )
        self.splitter.SplitVertically( self.panel1, self.panel2 )

        wx.EVT_MENU( self, id_about, self.OnCmdAbout )
        wx.EVT_MENU( self, id_exit, self.OnCmdExit )
        wx.EVT_SIZE( self, self.OnSize )

        wx.EVT_MENU_CLOSE( self, self.OnMenuClose )
        #wx.EVT_MENU_HIGHLIGHT( self, self.OnMenuHighlight )
        wx.EVT_MENU_HIGHLIGHT_ALL( self, self.OnMenuHighlightAll )
        wx.EVT_MENU_OPEN( self, self.OnMenuOpen )

    def OnMenuClose( self, event ):
        print 'OnMenuClose',event.GetMenuId(),event.IsPopup()
	print repr(event)
	print event.GetMenu()

    def OnMenuHighlight( self, event ):
        print 'OnMenuHighlight',event.GetMenuId(),event.IsPopup()
	print repr(event)
	print event.GetMenu()

    def OnMenuHighlightAll( self, event ):
        print 'OnMenuHighlightAll',event.GetMenuId(),event.IsPopup()
	print repr(event)
	print event.GetMenu()

    def OnMenuOpen( self, event ):
        print 'OnMenuOpen',event.GetMenuId(),event.IsPopup()
	print repr(event)
	print event.GetMenu()
        if event.GetMenu() == self.menu_file:
            print 'Open: File'
        elif  event.GetMenu() == self.menu_help:
            print 'Open: Help'
            time.sleep( .500 )
            self.menu_help.Enable( id_about, not self.menu_help.IsEnabled( id_about ) )
        else:
            print 'Open: -unknown-'

    def OnSize(self, x):
        print 'OnSize',x.GetSize()
        size = self.GetClientSize()
        self.splitter.SetSize( size )
        if not self.size_init:
            self.splitter.SetSashPosition( size.width / 2 )
            self.size_init = 1
        
    def OnClick(self,x):
        print 'Button click',x.GetId()

    def OnCmdExit(self,x):
        print 'Exit command',x.GetId()
        self.Close()

    def OnCmdAbout(self,x):
        print 'About command',x.GetId()

def main():
    global app
    app = ExampleApp()

    app.frame.Show(1)
    app.MainLoop()

if __name__ == '__main__':
    main()

 	  	 
