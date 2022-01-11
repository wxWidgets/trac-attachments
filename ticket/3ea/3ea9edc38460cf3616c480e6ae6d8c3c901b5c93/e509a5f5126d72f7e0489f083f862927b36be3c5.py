import wx

class Dud(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title='Dud', size=(200,200))
        panel = wx.Panel(self)
        vbox = wx.BoxSizer(wx.VERTICAL)
        my_list = wx.ListBox(panel, -1, choices=['one','two','three','four'])
        font = my_list.GetFont()
        font.SetPointSize(12)
        my_list.SetFont(font)
        vbox.Add(my_list, 1, wx.EXPAND | wx.ALL, 5)
        panel.SetSizer(vbox)
        self.Centre()
        self.Show()

if __name__ == '__main__':
    app = wx.App()
    Dud()
    app.MainLoop()
