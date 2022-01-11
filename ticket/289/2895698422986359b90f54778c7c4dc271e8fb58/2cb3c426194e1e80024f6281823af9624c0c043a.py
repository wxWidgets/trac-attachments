import wx

class StupidApp(wx.App):
    def OnInit(self):
        dlg = wx.Frame(None, -1, "wxListBox bug")
        self.listbox = wx.CheckListBox(dlg, -1, choices=['a', 'b', 'c'])
        wx.EVT_LISTBOX_DCLICK(self, self.listbox.GetId(), self.err)
        self.SetTopWindow(dlg)
        dlg.Show()
        return True

    def err(self, event=None):
        self.listbox.Select(1)
        self.listbox.SetString(1, 'assertion error')

app = StupidApp()
app.MainLoop()

 	  	 
