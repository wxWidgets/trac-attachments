
import  wx

#---------------------------------------------------------------------------

class TestPanel(wx.Panel):
    def __init__(self, parent, log):
        self.log = log
        wx.Panel.__init__(self, parent, -1)

        b = wx.Button(self, -1, "Create and Show a MCDialog", (50,50))
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)


    def OnButton(self, evt):
        lst = [ 'apple', 'pear', 'banana', 'coconut', 'orange', 'grape', 'pineapple',
                'blueberry', 'raspberry', 'blackberry', 'snozzleberry',
                'etc', 'etc..', 'etc...' ]



        dlg = MCDialog( self, 
                                   "Pick some fruit from\nthis list",
                                   "MCDialog", lst)

        if (dlg.ShowModal() == wx.ID_OK):
            selections = dlg.GetValue()
            strings = dlg.GetValueString()
            self.log.write("Selections: %s -> %s\n" % (selections, strings))


        dlg.Destroy()



#---------------------------------------------------------------------------

def runTest(frame, nb, log):
    win = TestPanel(nb, log)
    return win

#---------------------------------------------------------------------------
import  wx.lib.mixins.listctrl  as  listmix

class AutoWidthListCtrl(wx.ListCtrl, listmix.ListCtrlAutoWidthMixin,
        listmix.ColumnSorterMixin):
    def __init__(self, parent, ID, pos=wx.DefaultPosition,
                 size=wx.DefaultSize, style=0, *args, **kwargs):
        wx.ListCtrl.__init__(self, parent, ID, pos, size, style, *args, **kwargs)
        listmix.ListCtrlAutoWidthMixin.__init__(self)

    def GetListCtrl(self):
        #required by sorter mixin
        return self

    def initializeSorter(self, numcol):
        """Initialize the column sorter mixin after the list is filled."""
        listmix.ColumnSorterMixin.__init__(self, numcol)
        return

    def clearSelections(self):
        """Clear all selections in the list."""
        for item in range( self.GetItemCount() ):
            #self.SetItemState(item, 0, wx.LIST_STATE_SELECTED)
            self.Select(item, on=0)
            #self.SetItemState(item, 0, wx.LIST_STATE_FOCUSED)
        return

    def setSelection(self, name = None):
        """Set the selection to a given name and unselects everything else.

        This does not check to see if the list is empty!

        Arguments:
        name      -   Name of the pc to get focus (default None). If name is
                        None, then none get focus.
        """
        # Clear all selections
        self.clearSelections()
            
        # Set the selected item
        item = 0
        if name:
            item = self.FindItem(-1, name)
            #self.SetItemState(item,
            #        wx.LIST_STATE_SELECTED, wx.LIST_STATE_SELECTED)
            self.Select(item)
            self.Focus(item)
        return item

# end AutoWidthListCtrl
 

class KeyEventsListCtrl(AutoWidthListCtrl):
    def __init__(self, parent, id, pos=wx.DefaultPosition, size=wx.DefaultSize,
            style=0, *args, **kwargs):
        AutoWidthListCtrl.__init__(self, parent, id, pos, size, style, *args,
                **kwargs)
        self.typedText = ''
        self.Bind(wx.EVT_KEY_DOWN, self.OnKey)


    def FindPrefix(self, prefix):
        if prefix:
            prefix = prefix.lower()
            length = len(prefix)

            for x in range(self.GetItemCount()):
                text = self.GetItemText(x)
                text = text.lower()

                if text[:length] == prefix:
                    return x

        return -1


    def OnKey(self, evt):
        key = evt.GetKeyCode()

        # Select All - Ctrl+A
        if evt.ControlDown() and key == 65:
            for item in range(self.GetItemCount()):
                self.Select(item)
            return

        # Search for name
        if key >= 32 and key <= 127:
            self.typedText = self.typedText + chr(key)
            item = self.FindPrefix(self.typedText)

            if item != -1:
                pcName = self.GetItemText(item)
                self.setSelection(pcName)

        elif key == wx.WXK_BACK:
            self.typedText = self.typedText[:-1]

            if not self.typedText:
                pcName = self.GetItemText(0)
                self.setSelection(pcName)
            else:
                item = self.FindPrefix(self.typedText)

                if item != -1:
                    pcName = self.GetItemText(item)
                    self.setSelection(pcName)

        else:
            self.typedText = ''
            evt.Skip()

    def OnKeyDown(self, evt):
        pass

# end KeyEventsListCtrl

class MCDialog(wx.Dialog):
    def __init__(self, parent, msg, title, lst, pos = wx.DefaultPosition,
                 size = (200,200), style = wx.DEFAULT_DIALOG_STYLE):
        wx.Dialog.__init__(self, parent, -1, title, pos, size, style)
        
        x, y = pos
        if x == -1 and y == -1:
            self.CenterOnScreen(wx.BOTH)

        stat = wx.StaticText(self, -1, msg)
        self.lbox = KeyEventsListCtrl(self, -1, wx.DefaultPosition,
                wx.DefaultSize, wx.LC_REPORT|wx.LC_NO_HEADER)
        self.lbox.InsertColumn(0, "")
        import sys
        for name in lst:
            self.lbox.InsertStringItem(sys.maxint, name)

        ok = wx.Button(self, wx.ID_OK, "OK")
        ok.SetDefault()
        cancel = wx.Button(self, wx.ID_CANCEL, "Cancel")
        
        dlgsizer = wx.BoxSizer(wx.VERTICAL)
        dlgsizer.Add(stat, 0, wx.ALL, 4)
        dlgsizer.Add(self.lbox, 1, wx.EXPAND|wx.ALL, 4)
        
        btnsizer = wx.StdDialogButtonSizer()
        btnsizer.AddButton(ok)
        btnsizer.AddButton(cancel)
        btnsizer.Realize()
        dlgsizer.Add(btnsizer, 0, wx.ALL|wx.ALIGN_RIGHT, 4)
        self.SetSizer(dlgsizer)
        self.lst = lst
        self.Layout()
        self.Bind(wx.EVT_LIST_ITEM_ACTIVATED, self.Quit, self.lbox)
        

    def Quit(self, event = None):
        self.EndModal(wx.ID_OK)
        return

    def GetValue(self):
        selections = []
        item = self.lbox.GetFirstSelected()
        while item != -1:
            selections.append(item)
            item = self.lbox.GetNextSelected(item)
        return selections

    def GetValueString(self):
        selections = self.GetValue()
        val = [ self.lst[i] for i in selections ]
        return tuple(val)
#---------------------------------------------------------------------------


if __name__ == '__main__':
    import sys,os
    import run
    run.main(['', os.path.basename(sys.argv[0])] + sys.argv[1:])

 	  	 
