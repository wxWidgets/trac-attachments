import wx

class TestDialog(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, wx.ID_ANY, "Test",
            style=wx.CAPTION|wx.CLOSE_BOX|wx.SYSTEM_MENU|wx.RESIZE_BORDER)
        okBut = wx.Button(self, wx.ID_OK)
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(okBut)
        self.SetSizer(sizer)

class MainPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.ID_ANY, style=wx.TAB_TRAVERSAL|wx.BORDER_THEME)

        button = wx.Button(self, wx.ID_ANY, "Show Dialog")
        self.Bind(wx.EVT_BUTTON, self._showDialog, button)

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(button)
        self.SetSizer(sizer)

    def _showDialog(self, event):
        progDlg = wx.ProgressDialog("Long task", "Starting...", parent=self)
        # progDlg = wx.GenericProgressDialog("Long task", "Starting...", parent=self)
        with progDlg:
            progDlg.Pulse("One.")
            wx.Sleep(1)
            progDlg.Pulse("Two.")
            wx.Sleep(1)
            progDlg.Pulse("Three.")

        with TestDialog(self) as dlg:
            dlg.ShowModal()

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title="Progress Dialog Modal Issue")

        mainPanel = MainPanel(self)
        selfSizer = wx.BoxSizer(wx.VERTICAL)
        selfSizer.Add(mainPanel, 1, wx.EXPAND)
        self.SetSizer(selfSizer)


app = wx.PySimpleApp()
frame = TestFrame()
frame.Show()
app.MainLoop()
