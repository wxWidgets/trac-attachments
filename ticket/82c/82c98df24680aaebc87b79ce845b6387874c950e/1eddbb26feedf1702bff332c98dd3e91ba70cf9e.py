#
# ListCtrlGrid.py:
#   A simulated list control with word-wrapping multicolor renderer
#     that demonstrates problems with
#     wx.Grid's MakeCellVisible method
#

import  wx
import  wx.grid as gridlib

class TestRenderer(gridlib.PyGridCellRenderer):

    def __init__(self):
        gridlib.PyGridCellRenderer.__init__(self)

    def Draw(self, grid, attr, dc, rect, row, col, isSelected):

        dc.SetBrush(wx.Brush(wx.WHITE, wx.SOLID))
        dc.SetPen  (wx.TRANSPARENT_PEN)

        dc.DrawRectangleRect(rect)

        dc.SetBackgroundMode(wx.TRANSPARENT) # the background of drawn text
        dc.SetFont(attr.GetFont())

        x = rect.x + 1
        y = rect.y + 1

        rowval = grid.GetCellValue(row, col)
        rownum = rowval[:3]
        text   = rowval[3:]

        dc.SetTextForeground('BLACK')

        for ch in rownum:
            dc.DrawText(ch,x,y)
            x += 6

        for word in text.split():
            word += ' '
            w, h = dc.GetTextExtent(word)

            if (x + w > rect.right - 8) and (x != rect.x+1):
                x = rect.x + 18
                y += h

            dc.SetTextForeground('RED GREEN BLUE'.split()[len(word)%3])

            dc.DrawText(word, x, y)

            x += w

        if x == rect.x + 18: height = y    -rect.y +1
        else:                height = y +h -rect.y +1

        row_size = grid.GetRowSize(row)
        if row_size != height:
            grid.SetRowSize(row, height)
            grid.ForceRefresh()

    def GetBestSize(self, grid, attr, dc, row, col):

        text = grid.GetCellValue(row, col)
        dc.SetFont(attr.GetFont())

        h  = dc.GetTextExtent(text)[1]

        # Try to account for the vertical scrollbar
        w = grid.GetParent().GetClientSize()[0] - 27

        return wx.Size(w, h)

    def Clone(self):
        return TestRenderer()

#-----------------------------------------------------------------------------

class TestGrid(gridlib.Grid):
    def __init__(self, parent, log):
        gridlib.Grid.__init__(self, parent, -1)
        self.log = log
        self.initialized = False
        self.Bind(wx.EVT_SIZE, self.OnSize)

        self.dc = wx.MemoryDC()
        bitmap  = wx.EmptyBitmap(1024,768)
        self.dc.SelectObject(bitmap)

        testrecs = load_text()

        self.CreateGrid( len(testrecs), 1)

        self.EnableGridLines(False)
        self.SetDefaultRenderer( TestRenderer())
        self.EnableEditing(False)
        self.DisableDragRowSize()

        # No row or column labels
        self.SetRowLabelSize(0)
        self.SetColLabelSize(0)

        # Eliminate the right and bottom margins (so
        # that scroll bars don't appear prematurely)
        self.SetMargins(-10,-10) # extra width, extra height

        self.SetCellHighlightColour('BLUE')

        self.AutoSizeRows   (True)
        self.AutoSizeColumns(True)

        row = 0
        for rec in testrecs:
            self.SetCellValue(row,0, rec)
            row += 1

        self.initialized = True

    def OnSize(self,evt):
        if self.initialized:
            w = self.GetParent().GetClientSize()[0] - 17
            if  self.GetColSize(0) != w:
                self.SetColSize(0   , w)
        evt.Skip()

#-------------------------------------------------------------------------------------

class TestFrame(wx.Frame):
    def __init__(self, parent, log):
#       wx.Frame.__init__(self, parent, -1, "Test Grid", size=(100,400))  ##### <=====
        wx.Frame.__init__(self, parent, -1, "Test Grid", size=(224,400))  ##### <=====
#       wx.Frame.__init__(self, parent, -1, "Test Grid", size=(225,400))  ##### <=====
#       wx.Frame.__init__(self, parent, -1, "Test Grid", size=(340,400))  ##### <=====
        grid = TestGrid(self, log)

        self.Show(True)

        wx.CallAfter(self.DoLater, grid)

    def DoLater(self, grid):
        for row in range(grid.GetNumberRows()):
            rect = grid.CellToRect(row,0)
#           print row, rect, grid.GetCellValue(row,0)

        cursorRow = 30
        grid.SetGridCursor  (cursorRow,0)
        grid.MakeCellVisible(cursorRow,0)

        print 'VISIBLE:',
        for row in range(grid.GetNumberRows()):
            if grid.IsVisible(row,0): print row,
        print

        # RESULT: Rows 9 through 17 are visible; row 30 is not.   ##### <=====

        print 'ROW SIZES:',
        for row in range(grid.GetNumberRows()):
            print grid.GetRowSize(row),

        # CONCLUSION: wx.Grid's .MakeCellVisible() does not       ##### <=====
        #             properly account for variable row sizes     ##### <=====

#-------------------------------------------------------------------------------------

def load_text():
    digits = 'zero one two three four five six seven eight nine'.split()
    lines = []
    for i in range(50):
        line = '%2d  '%i
        for j in range((i%10)+1):
            line += digits[j] + ' '
        if (i%10)%2: line = line.upper()
        lines.append(line)
    return lines

#-------------------------------------------------------------------------------------

if __name__ == '__main__':
    import sys

    app = wx.PySimpleApp()
    frame = TestFrame(None, sys.stdout)
    frame.Show(True)
    app.MainLoop()

#-------------------------------------------------------------------------------------


 	  	 
