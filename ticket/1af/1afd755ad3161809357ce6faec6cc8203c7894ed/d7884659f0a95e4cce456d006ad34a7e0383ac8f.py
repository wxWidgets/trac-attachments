import wx, wx.grid as gridlib
       
class GridFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1)
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.grid = grid = gridlib.Grid(self, -1)
        grid.CreateGrid(2,2)
        grid.SetCellRenderer(0,0, gridlib.GridCellNumberRenderer())
        grid.SetCellEditor(0,0, gridlib.GridCellNumberEditor())
        sizer.Add(grid, 1, wx.EXPAND)
        self.SetSizer(sizer)
        self.Bind(wx.grid.EVT_GRID_CELL_CHANGE, self.OnGridCellChange)

    def OnGridCellChange(self, event):
        row,col = event.GetRow(), event.GetCol()
        value = self.grid.GetCellValue(row, col)
        print "at (%d,%d): %r" % (row,col,value)

if __name__=='__main__':
    app = wx.PySimpleApp(0)
    fr = GridFrame()
    fr.Show(True)
    app.MainLoop()

 	  	 
