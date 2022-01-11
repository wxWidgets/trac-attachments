from wxPython.wx import *
from wxPython.grid import *

class MyTable(wxPyGridTableBase):

    def __init__(self, items = ()):
        wxPyGridTableBase.__init__(self)
        self.items = items
        self.num_rows = len(self.items)
        self.num_cols = 1

    def set_values(self, values):
        msg = wxGridTableMessage(self, wxGRIDTABLE_REQUEST_VIEW_GET_VALUES)
        self.items = values
        self.num_rows = len(values)
        self.GetView().ProcessTableMessage(msg)

    def GetNumberRows(self):
        return len(self.items)

    def GetNumberCols(self):
        return self.num_cols

    def IsEmptyCell(self, row, col):
        return row >= self.num_rows or col >= self.num_cols

    def GetValue(self, row, col):
        if row < self.num_rows:
            return self.items[row]
        return ""

    def GetColLabelValue(self, col):
        return "Value"

    def GetRowLabelValue(self, row):
        return str(row)


class MyGrid(wxGrid):

    def __init__(self, parent):
        wxGrid.__init__(self, parent, -1)

        self.table = MyTable(["a", "b", "c"])
        self.SetTable(self.table, true)

class MyFrame(wxFrame):

    def __init__(self, parent):
        wxFrame.__init__(self, parent, -1, "GridBug demo", size = (200, 200))
        panel = wxPanel(self, -1)
        box = wxBoxSizer(wxVERTICAL)
        self.grid = MyGrid(panel)
        box.Add(self.grid, 1, wxALL|wxEXPAND, 4)

        box.Add(wxButton(panel, 3000, "New Values"), 0, wxALL, 4)

        EVT_BUTTON(self, 3000, self.OnNewValues)

        panel.SetAutoLayout(true)
        panel.SetSizer(box)
        box.Fit(panel)
        box.SetSizeHints(panel)

    def OnNewValues(self, *rest):
        if self.grid.table.GetValue(0, 0) == "a":
            values = [1, 2, 3]
        else:
            values = ["a", "b", "c"]
        self.grid.table.set_values(values)

app = wxPySimpleApp()
frame = MyFrame(None)
frame.Show(true)
app.MainLoop()

 	  	 
