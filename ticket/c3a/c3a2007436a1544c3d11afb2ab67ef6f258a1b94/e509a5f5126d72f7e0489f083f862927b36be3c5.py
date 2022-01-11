import wx

class bug(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title='Dud', size=(200,200))
        panel = wx.Panel(self)
        vbox = wx.BoxSizer(wx.VERTICAL)
        b = wx.Button(panel, label='Click')
        vbox.Add(b, proportion=0, flag=wx.ALL, border=5)
        panel.SetSizer(vbox)
        self.Centre()
        self.Show()
        self.Bind(wx.EVT_BUTTON, self.OnClick, id=b.GetId())
        self.dd = DateDialog(self)
    def OnClick(self, event):
        if self.dd.ShowModal() == wx.ID_OK:
            pass

class DateDialog(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, size=(120, 50), title='Date', style=wx.DEFAULT_DIALOG_STYLE)
        date_picker = wx.DatePickerCtrl(self, style=wx.DP_DROPDOWN)
        date_picker.SetValue(wx.DateTimeFromDMY(1,1,2011))

if __name__ == '__main__':
    app = wx.App()
    bug()
    app.MainLoop()
