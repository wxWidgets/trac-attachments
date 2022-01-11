
import wx

from wx.lib.agw import ultimatelistctrl as ULC



class TestUltimateListCtrl(ULC.UltimateListCtrl):
    def __init__(self, parent, id=wx.ID_ANY, pos=wx.DefaultPosition, size=wx.DefaultSize, style=0, agwStyle=0):
        ULC.UltimateListCtrl.__init__(self, parent, id, pos, size, style, agwStyle)

########################################################################
class TestPanel(wx.Panel):
    """"""
 
    #----------------------------------------------------------------------
    def __init__(self, parent):
        """Constructor"""
        wx.Panel.__init__(self, parent)
 
        font = wx.SystemSettings_GetFont(wx.SYS_DEFAULT_GUI_FONT)
        boldfont = wx.SystemSettings_GetFont(wx.SYS_DEFAULT_GUI_FONT)
        boldfont.SetWeight(wx.BOLD)
        boldfont.SetPointSize(12)
 
        self.ultimateList = TestUltimateListCtrl(self, agwStyle = wx.LC_REPORT 
                                         | wx.LC_VRULES
                                         | wx.LC_HRULES |ULC.ULC_BORDER_SELECT)#|ULC.ULC_EDIT_LABELS)
        #self.ultimateList.EnableSelectionGradient()

        self.ultimateList.EnableSelectionGradient(True)
        self.ultimateList.SetGradientStyle(1)
        #self.ultimateList.SetSelectedTextColour()
        self.ultimateList.SetFirstGradientColour(wx.BLUE)
        self.ultimateList.SetSecondGradientColour(wx.YELLOW)

        info = ULC.UltimateListItem()
        info._mask = wx.LIST_MASK_TEXT | wx.LIST_MASK_IMAGE | wx.LIST_MASK_FORMAT |ULC.ULC_MASK_FONTCOLOUR#| ULC.ULC_MASK_CHECK# |ULC.ULC_EDIT_LABELS
        #info._image = []
        info._format = 0
        #info._kind = 1
        info._mask = wx.LIST_MASK_TEXT | wx.LIST_MASK_IMAGE | wx.LIST_MASK_FORMAT | ULC.ULC_MASK_BACKCOLOUR

        info._font = font
        info.SetMask(ULC.ULC_MASK_FONTCOLOUR| wx.LIST_MASK_WIDTH | wx.LIST_MASK_TEXT| wx.LIST_MASK_FORMAT )
        info.SetTextColour(wx.Colour(255,0,0))
        info._text = "Artist Name"
        self.ultimateList.InsertColumnInfo(0, info)
 
        info = ULC.UltimateListItem()
        info._format = wx.LIST_FORMAT_RIGHT
        info._mask = wx.LIST_MASK_TEXT | wx.LIST_MASK_IMAGE | wx.LIST_MASK_FORMAT | ULC.ULC_MASK_FONTCOLOUR#|ULC.ULC_EDIT_LABELS
        #info._image = []
        info._text = "Title"
        #info._font = boldfont
        self.ultimateList.InsertColumnInfo(1, info)
 
        info = ULC.UltimateListItem()
        info._mask = wx.LIST_MASK_TEXT | wx.LIST_MASK_IMAGE | wx.LIST_MASK_FORMAT | ULC.ULC_MASK_FONTCOLOUR#|ULC.ULC_EDIT_LABELS
        info._format = 0
        info._text = "Genre"
        #info._font = font
        #info._image = []
        self.ultimateList.InsertColumnInfo(2, info)
 
        for i in range(0,150,3):
            self.ultimateList.InsertStringItem(i, "Puffy")
            self.ultimateList.SetStringItem(i, 1, "Bring It!")
            self.ultimateList.SetStringItem(i, 2, str(i))
            item2 = self.ultimateList.GetItem(i, 1)
            item3 = self.ultimateList.GetItem(i, 2)
            item2.SetMask(ULC.ULC_MASK_FONTCOLOUR| wx.LIST_MASK_WIDTH)
            item3.SetMask(ULC.ULC_MASK_FONTCOLOUR| wx.LIST_MASK_WIDTH)
            item2.SetTextColour(wx.Colour(255,0,0))
            item3.SetTextColour(wx.Colour(255,0,0))
            self.ultimateList.SetItem(item2)
            self.ultimateList.SetItem(item3)

            if i==3:
                print 'hiding'
                item = self.ultimateList.GetItem(i)
                item.SetShown(False)
                #set color to green in case hiding fails
                item.SetTextColour(wx.Colour(90,255,111))
                self.ultimateList.SetItem(item)

            self.ultimateList.InsertStringItem(i+1, "Newsboys")
            self.ultimateList.SetStringItem(i+1, 1, "Go")
            self.ultimateList.SetStringItem(i+1, 2, str(i+1))
            item1 = self.ultimateList.GetItem(i+1, 0)
            item2 = self.ultimateList.GetItem(i+1, 1)
            item3 = self.ultimateList.GetItem(i+1, 2)
            item1.SetMask(ULC.ULC_MASK_BACKCOLOUR| wx.LIST_MASK_WIDTH)
            item2.SetMask(ULC.ULC_MASK_BACKCOLOUR| wx.LIST_MASK_WIDTH)
            item3.SetMask(ULC.ULC_MASK_BACKCOLOUR| wx.LIST_MASK_WIDTH)
            item1.SetBackgroundColour(wx.Colour(242,242,242))
            item2.SetBackgroundColour(wx.Colour(242,242,242))
            item3.SetBackgroundColour(wx.Colour(242,242,242))
            self.ultimateList.SetItem(item1)
            self.ultimateList.SetItem(item2)
            self.ultimateList.SetItem(item3)


            self.ultimateList.InsertStringItem(i+2, "Family Force 5")
            self.ultimateList.SetStringItem(i+2, 1, "III")
            self.ultimateList.SetStringItem(i+2, 2, str(i+2))        
            item2 = self.ultimateList.GetItem(i+2, 1)
            item3 = self.ultimateList.GetItem(i+2, 2)
            item2.SetMask(ULC.ULC_MASK_FONTCOLOUR| wx.LIST_MASK_WIDTH)
            item3.SetMask(ULC.ULC_MASK_FONTCOLOUR| wx.LIST_MASK_WIDTH)        
            item2.SetTextColour(wx.Colour(111,158,219))
            item3.SetTextColour(wx.Colour(111,158,219))
            self.ultimateList.SetItem(item2)
            self.ultimateList.SetItem(item3)


        self.ultimateList.SetColumnWidth(0, wx.LIST_AUTOSIZE_USEHEADER)
        self.ultimateList.SetColumnWidth(1, wx.LIST_AUTOSIZE_USEHEADER)
        self.ultimateList.SetColumnWidth(2, -3)
        self.ultimateList.SetColumnWidth(0, wx.LIST_AUTOSIZE)#150)
        self.ultimateList.SetColumnWidth(1, wx.LIST_AUTOSIZE)#200)
        self.ultimateList.SetColumnWidth(2, -3)#100)

        
        
        self.ultimateList.SetItemState(2, wx.LIST_STATE_SELECTED|wx.LIST_STATE_FOCUSED, wx.LIST_STATE_SELECTED|wx.LIST_STATE_FOCUSED)




        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.ultimateList, 1, wx.EXPAND)
        self.SetSizer(sizer)
 
########################################################################
class TestFrame(wx.Frame):
    """"""
 
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        wx.Frame.__init__(self, None, title="MvP UltimateListCtrl Demo")
        panel = TestPanel(self)
        self.Show()
 
#----------------------------------------------------------------------
if __name__ == "__main__":
    app = wx.App(False)
    frame = TestFrame()
    app.MainLoop()