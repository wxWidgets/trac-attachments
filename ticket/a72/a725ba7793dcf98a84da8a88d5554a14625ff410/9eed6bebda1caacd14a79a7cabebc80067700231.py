''' drawingOnGridColumnLabel.py
    2003-12-03

    This example shows a wxGrid with some sample columns, where the column
    headers draw sort indicators when clicked. The example does not actually
    do the sorting of the data, as it is intended to show how to draw on the
    grid's column headers.

    by Paul McNett (p@ulmcnett.com) and whoever wrote the GridCustTable.py demo,
    from which I pulled the CustomDataTable() class.

    I didn't know what to do until Robin pointed out an undocumented method in
    wxGrid: GetGridColLabelWindow(), which returns a reference to the wxWindow
    that makes up the column header for the grid. From there, I could trap that
    window's Paint event, and draw the column labels myself, including graphical
    sort indicators.
'''

from wxPython.wx import *
from wxPython.grid import *

class CustomDataTable(wxPyGridTableBase):
    """ From the wxPython demo
    """

    def __init__(self):
        wxPyGridTableBase.__init__(self)

        self.colLabels = ['ID', 'Description', 'Severity', 'Priority', 'Platform',
                          'Opened?', 'Fixed?', 'Tested?', 'TestFloat']

        self.dataTypes = [wxGRID_VALUE_NUMBER,
                          wxGRID_VALUE_STRING,
                          wxGRID_VALUE_CHOICE + ':only in a million years!,wish list,minor,normal,major,critical',
                          wxGRID_VALUE_NUMBER + ':1,5',
                          wxGRID_VALUE_CHOICE + ':all,MSW,GTK,other',
                          wxGRID_VALUE_BOOL,
                          wxGRID_VALUE_BOOL,
                          wxGRID_VALUE_BOOL,
                          wxGRID_VALUE_FLOAT + ':6,2',
                          ]

        self.data = [
            [1010, "The foo doesn't bar", "major", 1, 'MSW', 1, 1, 1, 1.12],
            [1011, "I've got a wicket in my wocket", "wish list", 2, 'other', 0, 0, 0, 1.50],
            [1012, "Rectangle() returns a triangle", "critical", 5, 'all', 0, 0, 0, 1.56]

            ]


    #--------------------------------------------------
    # required methods for the wxPyGridTableBase interface

    def GetNumberRows(self):
        return len(self.data) + 1

    def GetNumberCols(self):
        return len(self.data[0])

    def IsEmptyCell(self, row, col):
        try:
            return not self.data[row][col]
        except IndexError:
            return true

    # Get/Set values in the table.  The Python version of these
    # methods can handle any data-type, (as long as the Editor and
    # Renderer understands the type too,) not just strings as in the
    # C++ version.
    def GetValue(self, row, col):
        try:
            return self.data[row][col]
        except IndexError:
            return ''

    def SetValue(self, row, col, value):
        try:
            self.data[row][col] = value
        except IndexError:
            # add a new row
            self.data.append([''] * self.GetNumberCols())
            self.SetValue(row, col, value)

            # tell the grid we've added a row
            msg = wxGridTableMessage(self,                             # The table
                                     wxGRIDTABLE_NOTIFY_ROWS_APPENDED, # what we did to it
                                     1)                                # how many

            self.GetView().ProcessTableMessage(msg)

class MyGrid(wxGrid):
    def __init__(self, parent):

        wxGrid.__init__(self, parent, -1)
        table = CustomDataTable()
        self.SetTable(table, true)

        self.SetRowLabelSize(0)
        self.SetMargins(0,0)
        self.AutoSizeColumns(False)

        # A click in the column header will set these:
        self.sortedColumn = -1
        self.sortedColumnDescending = False

        # trap the column label's paint event:
        columnLabelWindow = self.GetGridColLabelWindow()
        EVT_PAINT(columnLabelWindow, self.OnColumnHeaderPaint)

        # trap the grid label's left click:
        EVT_GRID_LABEL_LEFT_CLICK(self, self.OnGridLabelLeftClick)
        
        wx.grid.Grid.SetCellHighlightPenWidth(self, 1)

    def OnColumnHeaderPaint(self, evt):
        w = self.GetGridColLabelWindow()
        dc = wxPaintDC(w)
        clientRect = w.GetClientRect()
        font = dc.GetFont()

        # For each column, draw it's rectangle, it's column name,
        # and it's sort indicator, if appropriate:
        #totColSize = 0
        totColSize = -self.GetViewStart()[0]*self.GetScrollPixelsPerUnit()[0] # Thanks Roger Binns
        for col in range(self.GetNumberCols()):
            dc.SetBrush(wxBrush("WHEAT", wxTRANSPARENT))
            dc.SetTextForeground(wxBLACK)
            colSize = self.GetColSize(col)
            rect = (totColSize,0,colSize,32)
            dc.DrawRectangle(rect[0] - (col<>0 and 1 or 0), rect[1],
                             rect[2] + (col<>0 and 1 or 0), rect[3])
            totColSize += colSize

            if col == self.sortedColumn:
                font.SetWeight(wxBOLD)
                # draw a triangle, pointed up or down, at the
                # top left of the column.
                left = rect[0] + 3
                top = rect[1] + 3

                dc.SetBrush(wxBrush("WHEAT", wxSOLID))
                if self.sortedColumnDescending:
                    dc.DrawPolygon([(left,top), (left+6,top), (left+3,top+4)])
                else:
                    dc.DrawPolygon([(left+3,top), (left+6, top+4), (left, top+4)])
            else:
                font.SetWeight(wxNORMAL)

            dc.SetFont(font)
            dc.DrawLabel("%s" % self.GetTable().colLabels[col],
                     rect, wxALIGN_CENTER | wxALIGN_TOP)


    def OnGridLabelLeftClick(self, evt):
        self.processSort(evt.GetCol())

    def processSort(self, gridCol=None):
        if gridCol == None:
            gridCol = self.GetGridCursorCol()

        descending = False
        if gridCol == self.sortedColumn:
            if self.sortedColumnDescending == False:
                descending = True

        self.sortedColumn = gridCol
        self.sortedColumnDescending = descending
        self.Refresh()

if __name__ == "__main__":
        # instantiate a simple app object:
        app = wxPySimpleApp()
        frame = wxFrame(None, -1, "Click on any column header")
        frame.SetSize((400,200))
        object = MyGrid(frame)
        object.SetFocus()
        frame.Show(1)
        app.MainLoop()
 	  	 
