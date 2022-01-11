import wx

class Frame1(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title='Set Tansparent test')
        
        bSizer1 = wx.BoxSizer( wx.VERTICAL )
        self.btnSetTransparent = wx.Button( self, wx.ID_ANY, u"SetTransparent", wx.DefaultPosition, wx.DefaultSize, 0 )
        bSizer1.Add( self.btnSetTransparent, 0, wx.ALL, 5 )
        self.SetSizer( bSizer1 )
        self.Layout()
        
        self.Centre( wx.BOTH )
        
        self.btnSetTransparent.Bind( wx.EVT_BUTTON, self._SetTransparent )

        self.Show(True)
        self.SetTransparent(200) #This works
    
    def _SetTransparent( self, event ):
        self.SetTransparent(255) #This doesn't work
    

if __name__ == '__main__':
    app = wx.PySimpleApp()
    frm1 = Frame1()
    app.MainLoop()
