import sys

import wx
import wx.grid

class MainGrid(wx.grid.Grid):
    def __init__(self, parent):
        wx.grid.Grid.__init__(self, parent, -1)
        
        self.CreateGrid(5,5)
        
        self.InsertRows(2, 1, updateLabels=False)
        self.InsertCols(2, 1, updateLabels=False)
        
    
class MainWindow(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        self.grid = MainGrid(self)

def main():
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()
    
    main_window = MainWindow()
    
    app.SetTopWindow(main_window)
    main_window.Show()
    app.MainLoop()


if __name__ == "__main__":
    main()
