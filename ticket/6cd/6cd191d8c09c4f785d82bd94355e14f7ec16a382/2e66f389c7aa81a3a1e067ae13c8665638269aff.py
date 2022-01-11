import wx.grid

class MyFrame(wx.Frame):
    def __init__(self):
        super().__init__(None, -1)
        grid = wx.grid.Grid(self, -1)
        grid.CreateGrid(2,2)
        grid.Bind(wx.grid.EVT_GRID_CELL_LEFT_CLICK, self.OnGridCellLeftClick)

    def OnGridCellLeftClick(self, event):
        pass

if __name__=='__main__':
    app = wx.App()
    fr = MyFrame()
    fr.Show(True)
    app.MainLoop()
