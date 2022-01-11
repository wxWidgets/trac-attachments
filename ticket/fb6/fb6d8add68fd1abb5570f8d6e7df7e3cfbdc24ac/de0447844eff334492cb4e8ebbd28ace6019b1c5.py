import wx

class Frame(wx.Frame):
    def __init__(self, *args, **kwargs):
        super(Frame, self).__init__(*args, **kwargs)
        self.listCtrl = wx.ListCtrl(self)
        self.listCtrl.InsertStringItem(0, 
            'ThisIsALongLabel')
        self.listCtrl.InsertStringItem(1, 
            'ThisIsALongLabel')

app = wx.App()
frame = Frame(None)
frame.Show()
app.MainLoop()
