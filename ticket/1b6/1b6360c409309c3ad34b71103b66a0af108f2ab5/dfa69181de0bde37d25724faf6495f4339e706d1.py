import wx
import wx.grid


class MyFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, -1, title="Grid Sample")
        panel = wx.Panel(self, -1)
        grid = wx.grid.Grid(panel, -1)
        grid.CreateGrid(4, 2)
        grid.SetSize((200, 200))
        grid.SetDefaultEditor(wx.grid.GridCellFloatEditor())


if __name__ == "__main__":
    app = wx.PySimpleApp()
    frame = MyFrame()
    frame.Show(True)
    app.MainLoop() 
 	  	 
