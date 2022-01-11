import wx
import wx.grid

class ChoiceRenderer(wx.grid.PyGridCellRenderer):
    def __init__(self, table):
        """
        Image Renderer Test.
        
        The renderer shall mimic a choice widget
        
        """
        
        wx.grid.PyGridCellRenderer.__init__(self)
        self.table = table
        
        self.iconwidth = 32

    def Draw(self, grid, attr, dc, rect, row, col, isSelected):
        render = wx.RendererNative.Get()

        # clear the background
        dc.SetBackgroundMode(wx.SOLID)
        
        if isSelected:
            dc.SetBrush(wx.Brush(wx.BLUE, wx.SOLID))
            dc.SetPen(wx.Pen(wx.BLUE, 1, wx.SOLID))
        else:
            dc.SetBrush(wx.Brush(wx.WHITE, wx.SOLID))
            dc.SetPen(wx.Pen(wx.WHITE, 1, wx.SOLID))
        dc.DrawRectangleRect(rect)
        
        button_x = rect.x + rect.width - self.iconwidth
        button_y = rect.y
        button_width = self.iconwidth
        button_height = rect.height
        
        render.DrawComboBoxDropButton(grid, dc, \
            (button_x, button_y, button_width, button_height), \
            wx.CONTROL_CURRENT)


class MainGrid(wx.grid.Grid):
    """Keep this scrolled"""
    
    def __init__(self, parent):
        wx.grid.Grid.__init__(self, parent, -1)
        
        self.CreateGrid(5, 5)

        self.Bind(wx.grid.EVT_GRID_CELL_LEFT_CLICK, self.OnMouse)

    def OnMouse (self, event):
        """Get rid of the double-click"""
        self.SetGridCursor(event.Row, event.Col)
        self.EnableCellEditControl(True)
        event.Skip()


class MainWindow(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        self.grid = MainGrid(self)
        
        choice_renderer = ChoiceRenderer(self.grid)
        choice_editor = wx.grid.GridCellChoiceEditor( \
                ['one', 'two', 'three', 'four'], False)
        self.grid.SetCellRenderer(1, 1, choice_renderer)
        self.grid.SetCellEditor(1, 1, choice_editor)
        


def main():
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()
    
    main_window = MainWindow()
    
    app.SetTopWindow(main_window)
    main_window.Show()
    app.MainLoop()


if __name__ == "__main__":
    main()
