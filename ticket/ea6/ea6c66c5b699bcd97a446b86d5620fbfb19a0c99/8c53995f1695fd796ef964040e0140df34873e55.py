import wx

class Frame(wx.Frame):
    def __init__(self):
        super(Frame, self).__init__(None)
        self.datePicker = wx.DatePickerCtrl(self)
        

app = wx.App()
languageInfo = wx.Locale.FindLanguageInfo('nn_NO')
locale = wx.Locale(languageInfo.Language)
frame = Frame()
frame.Show()
app.MainLoop()
