import wx


myEVT_MY_ERROR = wx.NewEventType()
EVT_MY_ERROR = wx.PyEventBinder(myEVT_MY_ERROR, 1)
MY_ERROR_ID = wx.NewId()

class ErrorEvent(wx.PyCommandEvent):
    def __init__(self, evtType, id):
        wx.PyCommandEvent.__init__(self, evtType, id)

    
    
class MainWindow(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, -1, 'Test')

        self.file_list = FileList(self)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.file_list, 1, wx.EXPAND, 0)
        self.SetSizer(sizer)
        self.Fit()

        self.Bind(EVT_MY_ERROR, self.on_error, id=MY_ERROR_ID)
    
    def on_error(self, event=None):
        dlg = ErrorDialog(parent=self)
        dlg.ShowModal()
        dlg.Destroy()



class FileList(wx.ListCtrl):
    def __init__(self, parent):
        wx.ListCtrl.__init__(
            self, parent, -1, 
            style=wx.LC_REPORT|wx.LC_SINGLE_SEL 
            )

        self.InsertColumn(0, '')

        self.InsertStringItem(0, '0')
        self.InsertStringItem(1, '1')
        self.InsertStringItem(2, '2')

        self.Bind(wx.EVT_CONTEXT_MENU, self.on_context_menu)
        self.Bind(wx.EVT_LIST_ITEM_SELECTED, self.on_item_selected)

    def on_item_selected(self, event):
        if event.GetIndex() == 2:
            def fn():
                evt = ErrorEvent(myEVT_MY_ERROR, MY_ERROR_ID)
                self.GetEventHandler().ProcessEvent(evt)
            wx.CallAfter(fn)
        event.Skip()
            
    def on_context_menu(self, event):
        menu = wx.Menu()
        for i in xrange(3):
            menu.Append(-1, 'Test %d' % i)
        self.PopupMenu(menu)
        menu.Destroy()




class ErrorDialog(wx.Dialog):
    def __init__(self, *args, **kwds):
        kwds["style"] = wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER|wx.THICK_FRAME
        wx.Dialog.__init__(self, *args, **kwds)

        self.ok_btn = wx.Button(self, wx.ID_OK, ("&OK"))

        main_sizer = wx.BoxSizer(wx.VERTICAL)
        main_sizer.Add(self.ok_btn, 0, wx.ALL, 10)
        self.SetSizer(main_sizer)
        main_sizer.Fit(self)
        self.Layout()

        self.Bind(wx.EVT_BUTTON, self.on_ok_click, self.ok_btn)

    def on_ok_click(self, event):
        self.EndModal(1)



if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = MainWindow()
    frame.Show()
    app.MainLoop()
