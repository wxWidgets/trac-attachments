
import wx
import wx.grid

# Window functions

ID_CHOICE = 10000
ID_COMBO = 10001
ID_TREECTRL = 10002

def MyDialogFunc( parent, call_fit = True, set_sizer = True ):
    item0 = wx.FlexGridSizer( 0, 1, 0, 0 )
    item0.AddGrowableCol( 0 )
    item0.AddGrowableRow( 1 )
    
    item1 = wx.FlexGridSizer( 0, 2, 0, 0 )
    item1.AddGrowableCol( 0 )
    item1.AddGrowableCol( 1 )
    item1.AddGrowableRow( 0 )
    
    item2 = wx.Choice( parent, ID_CHOICE, wx.DefaultPosition, [100,-1], 
        ["ChoiceItem","Item","Item","Item","Item","Item","Item","Item","Item","Item","Item","Item","Item"] , 0 )
    item2.SetStringSelection("ChoiceItem")
    item1.Add( item2, 0, wx.GROW|wx.ALIGN_CENTER_HORIZONTAL, 5 )

    item3 = wx.ComboBox( parent, ID_COMBO, "", wx.DefaultPosition, [100,-1], 
        ["ComboItem"] , wx.CB_DROPDOWN )
    item3.SetStringSelection("ComboItem");
    item1.Add( item3, 0, wx.GROW|wx.ALIGN_CENTER_VERTICAL, 5 )

    item0.Add( item1, 0, wx.GROW|wx.ALIGN_CENTER_HORIZONTAL|wx.ALL, 5 )

    item4 = wx.TreeCtrl( parent, ID_TREECTRL, wx.DefaultPosition, [120,160], wx.TR_HAS_BUTTONS|wx.TR_LINES_AT_ROOT|wx.SUNKEN_BORDER )
    item4.SetBackgroundColour( wx.GREEN )
    item0.Add( item4, 0, wx.GROW|wx.ALIGN_CENTER_HORIZONTAL|wx.ALL, 5 )

    root = item4.AddRoot("this is a very very very very very long test of words and also words")
    child = item4.AppendItem(root, "a child with text and more text and you know more text")
    item4.SetFocus()

    item4.EnsureVisible(child)

    if set_sizer == True:
        parent.SetSizer( item0 )
        if call_fit == True:
            item0.SetSizeHints( parent )
    
    return item0


class NApp(wx.App):
    def __init__(self):
        wx.App.__init__(self, 0)

    def OnInit(self):
        parent = wx.Frame(None)
            
        sizer = MyDialogFunc(parent)

        parent.SetSizer(sizer)        

        parent.Show()
        

        return 1        

        
if __name__ == '__main__':

    app = NApp()

    app.MainLoop()

 	  	 
