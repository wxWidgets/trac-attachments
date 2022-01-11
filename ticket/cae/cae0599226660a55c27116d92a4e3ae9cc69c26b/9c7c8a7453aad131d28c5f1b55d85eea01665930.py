import wx, wx.grid as gridlib
       
class FailingDialogue(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1,
                           style=wx.DEFAULT_DIALOG_STYLE|wx.WANTS_CHARS)
        panel = wx.Panel(self, -1)
        diasizer = wx.BoxSizer(wx.VERTICAL)
        panelsizer = wx.BoxSizer(wx.VERTICAL)
        grid = gridlib.Grid(panel, -1)
        grid.CreateGrid(2,2)
        panelsizer.Add(grid, 1, wx.EXPAND)
        but = wx.Button(panel, -1, 'Bottom line')
        panelsizer.Add(but, 0, wx.EXPAND)
        panel.SetSizer(panelsizer)
        diasizer.Add(panel, 1, wx.EXPAND)
        self.SetSizer(diasizer)
        grid.Bind(wx.EVT_KEY_DOWN, self.OnGridKey)
        but.Bind(wx.EVT_BUTTON, self.OnButton)
        # but.SetDefault()
    def OnGridKey(self, event):
        print "Hit key:", event.GetKeyCode()
        event.Skip()
    def OnButton(self, event):
        print "Button clicked"

if __name__=='__main__':
    app = wx.PySimpleApp(0)
    fr = FailingDialogue()
    fr.Show(True)
    app.MainLoop()

 	  	 
