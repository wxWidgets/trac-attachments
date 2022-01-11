import wx
import sys
""" A Class for reproducing a bug when using a non-empty wx.CheckListBox
    - All Radio check items are damaged, the icon for the selected item disappears.
    Tested under win32 (Windows XP)"""
class TestCheckListBox(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        colSizer = wx.BoxSizer(wx.VERTICAL)
        # The list Box
        self.listbox1 = wx.CheckListBox( self, -1, choices=[], style=wx.LB_HSCROLL )
        colSizer.Add(self.listbox1, 0)

        # This is the line that causes the problems,
        # Either that, or setting the choices parameter in the wx.CheckListBox not to [].
        # Both cause the same problem
        # Comment this line and see how everything works well
        self.listbox1.Set( ["test1", "test2"] )

        
        # A Simple right click menu for reproducing the disappearance of Radio-tool item bitmaps (the balck circle)
        # The bug also affects radio tools in Application menu.
        # It seems like all the menues that have been created after using self.listbox1.Set got damaged
        txt = wx.StaticText(self, -1, "Right Click Here!")
        colSizer.Add(txt, 0)
        txt.Bind(wx.EVT_RIGHT_UP, self.showMenu)
        self.SetSizer(colSizer)
        self.SetAutoLayout(True)
        
        self.chosen = 0
        self.popupmenu = False
        
    def makePopupMenu(self):
        self.popupmenu = wx.Menu()        
        self.popupmenu.Append(666, "Option1", "Option1", wx.ITEM_RADIO)
        self.popupmenu.Append(667, "Option2", "Option2", wx.ITEM_RADIO)
        self.popupmenu.Append(668, "Option3", "Option3", wx.ITEM_RADIO)
        self.Bind(wx.EVT_MENU, self.onChangeOption, id = 666, id2 = 668)
        
    def showMenu(self, event):
        if not self.popupmenu:
            self.makePopupMenu()
        self.popupmenu.Check(self.chosen + 666, True)
        self.PopupMenuXY(self.popupmenu, -1, -1)

    def onChangeOption(self, event):
        self.chosen = event.GetId() - 666
        print "Chosen: ", self.chosen
        event.Skip()
        
        
class TestFrame(wx.Frame):

    def __init__(self, parent, id, title, size, style = wx.DEFAULT_FRAME_STYLE ):

        wx.Frame.__init__(self, parent, id, title, size=size, style=style)

        self.win = TestCheckListBox(self)

def main(argv=None):
    if argv is None:
        argv = sys.argv

    app = wx.PySimpleApp()
    f = TestFrame(None, -1, "CheckListBox Bug Test",wx.Size(500,300))
    f.Show()
    app.MainLoop()

if __name__ == '__main__':
    main()

 	  	 
