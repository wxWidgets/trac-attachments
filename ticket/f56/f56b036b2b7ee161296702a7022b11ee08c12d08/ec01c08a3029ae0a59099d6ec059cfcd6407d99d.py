import wx

class TestDlg(wx.Dialog):
    def __init__(self, *args, **kwargs):
        kwargs["title"] = "Test dialog"
        wx.Dialog.__init__(self, *args, **kwargs)
        
        #put normal content on dialog
        txton = wx.TextCtrl(self, -1, pos=(20,20), size=(100,20))
        txtoff = wx.TextCtrl(self, -1, pos=(20,60), size=(100,20))
        hint = wx.StaticText(self, -1, pos=(20,100), size=(100,40))
        hint.SetLabel("""Popup appears focusing on first TextCtrl """\
                      """and disappears when leaving it""")
        #create popup and put a textcontrol and a button on it
        self.popup = wx.PopupWindow(self, wx.RAISED_BORDER)
        test = wx.TextCtrl(self.popup, -1, pos=(10,10), size=(80,20))
        test.SetValue("Try to edit here...")
        self.popup.SetPosition((100,120))
        self.popup.SetSize((100,200))
        button = wx.Button(self.popup, -1, "Hide me!", pos=(10,40))
        
        #show popup when focusing on first textcontrol, hide when leaving
        #or pressing the button
        txton.Bind(wx.EVT_SET_FOCUS, self.OnPopupDisplay)
        txton.Bind(wx.EVT_KILL_FOCUS, self.OnPopupHide)
        self.Bind(wx.EVT_BUTTON, self.OnPopupHide, button)

    def OnPopupDisplay(self, evt):
        self.popup.Show(True)
        evt.Skip()

    def OnPopupHide(self, evt):
        self.popup.Show(False)
        evt.Skip()

app = wx.PySimpleApp(True)
app.MainLoop()

dlg = TestDlg(None, -1)
dlg.ShowModal()

 	  	 
