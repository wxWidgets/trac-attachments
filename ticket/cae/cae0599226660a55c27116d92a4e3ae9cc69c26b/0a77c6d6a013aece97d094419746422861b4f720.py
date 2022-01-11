import wx, wx.grid as gridlib
       
class FailingDialogue(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1)
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        grid = gridlib.Grid(self, -1)
        grid.CreateGrid(2,2)
        sizer.Add(grid, 1, wx.EXPAND)
        self.SetSizer(sizer)

if __name__=='__main__':
    app = wx.PySimpleApp(0)
    fr = FailingDialogue()
    fr.Show(True)
    app.MainLoop()

 	  	 
