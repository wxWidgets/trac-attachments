import wx

class AScrolledWindow(wx.ScrolledWindow):
    def __init__(self, parent):
        wx.ScrolledWindow.__init__(self, parent, -1)
        gb = wx.GridBagSizer()
        for y in [1,2]:
            lb = wx.ListBox(self, -1,style=wx.LB_EXTENDED,
                            choices=map(str, xrange(100,130)))
            gb.Add(lb, (y,0), (1,1))
        self.SetSizer(gb)
        self.SetScrollRate(20,20)
        self.EnableScrolling(True,True)

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, 'Selection computation problem')
        sz = wx.BoxSizer(wx.VERTICAL)
        pa = AScrolledWindow(self)
        sz.Add(pa, 1, wx.EXPAND)
        self.SetSizer(sz)

def main():
    wxapp = wx.App()
    fr = TestFrame()
    fr.Show(True)
    wxapp.MainLoop()

if __name__=='__main__':
    main()
