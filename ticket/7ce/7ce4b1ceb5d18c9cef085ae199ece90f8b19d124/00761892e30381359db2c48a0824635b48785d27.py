import wx
import wx.grid

#---------------------------------------------------------------------------

# TODO - figure out how to make the Choice boxes editable.
# It appears that this can only be done when creating the control, so it may
# require that PyGridTableBase be replaced with a normal table.

# FIXME - There are lots of bugs associated with changing the table but keeping
# the grid. It might be better to make a new grid every time. The wxPython wiki
# has conflicting views on this point. If this is the case, the functionality of
# the custom table should be subsumed by a custom grid. This is only a
# prototype, afterall.

class CustomGridDataTable(wx.grid.PyGridTableBase):
    """PyGridTableBase object for dynamically processing and displaying
    GridCellData information.
    """
    def __init__(self, log):
        wx.grid.PyGridTableBase.__init__(self)
        self.log = log

        ## These must be assigned before the data table is used!
        # The possessing grid
        self.grid = None

        # This is a list of column labels for the table
        self.colLabels = []

        # This is a list of row dictionaries. Dictionary keys correspond to
        # column labels. Dictionary items are GridCellData objects.
        self.dataList = []

        return

    def setColLabels(self, colLabels):
        """Use this method to set the column labels."""
        self.colLabels = colLabels
        self.updateDataInfo()
        return

    def setDataList(self, dataList):
        """Use this method to set the data list."""
        self.dataList = dataList
        self.updateDataInfo()
        return

    def updateDataInfo(self):
        """Update the information in the GridCellData objects.

        This assigns the following to each GridCellData in the table:
        table   --  reference to this table
        row     --  the row the data is in
        col     --  the column the data is in

        This should be called whenever the type of GridCellData objects changes.
        """
        if self.colLabels and self.dataList:
            for row in range(self.GetNumberRows()):
                for col in range(self.GetNumberCols()):
                    data = self.getDataObject(row, col)
                    if data:
                        data.table = self
                        data.row = row
                        data.col = col
        return


    # Useful methods!
    def getDataObject(self, row, col):
        """Get the GridCellData assigned to a specific row and column.
        
        If a cell is empty, this will return None
        """
        key = self.GetColLabelValue(col)
        return self.dataList[row].get(key)

    #--------------------------------------------------
    # required methods for the wxPyGridTableBase interface

    def GetNumberRows(self):
        return len(self.dataList)

    def GetNumberCols(self):
        return len(self.colLabels)

    def IsEmptyCell(self, row, col):
        data = self.getDataObject(row, col)
        return data is None

    # Get/Set values in the table.  The Python version of these
    # methods can handle any data-type, (as long as the Editor and
    # Renderer understands the type too,) not just strings as in the
    # C++ version.
    def GetValue(self, row, col):
        data = self.getDataObject(row, col)
        if data:
            return data.GetValue()
        else:
            return ""

    def SetValue(self, row, col, value):
        data = self.getDataObject(row, col)
        if data:
            data.SetValue(value)        
        return

    #--------------------------------------------------
    # Some optional methods

    # Called when the grid needs to display labels
    def GetColLabelValue(self, col):
        if self.colLabels:
            return self.colLabels[col]
        else:
            return None

    # Called to determine the kind of editor/renderer to use by
    # default, doesn't necessarily have to be the same type used
    # natively by the editor/renderer if they know how to convert.
    def GetTypeName(self, row, col):
        data = self.getDataObject(row, col)
        if data:
            return data.GetTypeName()
        else:
            return wx.grid.GRID_VALUE_STRING

    # Called to determine how the data can be fetched and stored by the
    # editor and renderer.  This allows you to enforce some type-safety
    # in the grid.
    def CanGetValueAs(self, row, col, typeName):
        data = self.getDataObject(row, col)
        if data:
            return data.CanGetValueAs(typeName)
        else:
            return False

    def CanSetValueAs(self, row, col, typeName):
        data = self.getDataObject(row, col)
        if data:
            return data.CanSetValueAs(typeName)
        else:
            return False

    # Customized GetAttr that looks at the cell objects for their attributes.
    def GetAttr(self, row, col, *args):
        """Get the attributes for the cell."""
        data = self.getDataObject(row, col)
        attr = None
        if data:
            attr = data.getAttr()
        else:
            # Gray out and make read-only missing cells
            attr = wx.grid.GridCellAttr()
            attr.SetReadOnly( True )
            color = wx.SystemSettings_GetColour(wx.SYS_COLOUR_GRAYTEXT)
            attr.SetBackgroundColour(color)
        return attr

#---------------------------------------------------------------------------

class GridCellData(object):
    """Base class for holding cell data to be used with a CustomGridDataTable."""

    def __init__(self):
        # These are set by the CustomGridDataTable
        self.table = None
        self.row = 0
        self.col = 0

        # Not yet used
        self.tags = []

        # Current and default values
        self.value = None
        self.default = None

        # Other stuff
        self._datatype = None
        self.isReadOnly = False
        return

    # These can replaced in a derived class

    def startupHandler(self):
        """Handler that is called when the grid is instantiated.

        Note that the grid only takes care of whether a cell is read only.  All
        other cell modifications (fonts, etc.) must be placed here.

        This method must be overloaded in a derived class for anything
        interesting to happen.
        """
        return

    def handler(self):
        """Handler for this cell object.

        Note that the grid only takes care of whether a cell is read only or
        not.  All other cell modifications (fonts, etc.) must be placed here.

        This method must be overloaded in a derived class for anything
        interesting to happen. It is called whenever the cell's data changes. 
        """
        return

    def getEditorParametersString(self):
        """Get the cell format string needed by CustomGridDataTable."""
        raise NotImplementedError("Overload in derived class.")

    def getAttr(self):
        """Get the attributes of the cell.

        This only tells if the cell is read-only. Other attributes must be
        applied by the derived class.
        """
        attr = wx.grid.GridCellAttr()
        if self.isReadOnly:
            color = wx.SystemSettings_GetColour(wx.SYS_COLOUR_GRAYTEXT)
        else:
            color = wx.NullColour
        attr.SetReadOnly(self.isReadOnly)
        attr.SetBackgroundColour(color)
        return attr

    ########################################################
    # Needed by CustomGridDataTable. Don't mess with these #
    ########################################################

    def GetValue(self):
        """Get the current value."""
        return self.value

    def SetValue(self, value):
        """Set the current value."""
        # Note that the handler is not called here, but by the grid when an
        # EVT_GRID_CELL_CHANGE event is thrown.
        self.value = value
        return

    def GetTypeName(self):
        """Get the data type, including the cell format."""
        type = self._datatype
        type += self.getEditorParametersString()
        return type

    def CanGetValueAs(self, typeName):
        return typeName == self._datatype

    def CanSetValueAs(self, typeName):
        return typeName == self._datatype

# End class GridCellData

class StringGridCell(GridCellData):
    """Class for holding information about string cells."""

    def __init__(self):
        GridCellData.__init__(self)
        self._datatype = wx.grid.GRID_VALUE_STRING

        # Editor parameters
        self.maxWidth = 12

        # Formatting parameters
        self.fontFamily = wx.FONTFAMILY_DEFAULT
        self.fontStyle = wx.FONTSTYLE_NORMAL
        self.fontWeight = wx.FONTWEIGHT_NORMAL
        self.isUnderlined = False
        return

    def getEditorParametersString(self):
        """Get the cell format string needed by CustomGridDataTable."""
        return ":%i" % self.maxWidth

    def getAttr(self):
        """Get the attributes of the cell."""
        attr = GridCellData.getAttr(self)
        font = wx.Font(10, self.fontFamily, self.fontStyle,
                self.fontWeight, underline = self.isUnderlined)
        self.table.grid.SetCellFont(self.row, self.col, font)
        attr.SetFont(font)
        return attr

class HeaderGridCell(StringGridCell):
    """Class for holding a header. Just a specific StringGridCell."""

    def __init__(self):
        StringGridCell.__init__(self)
        self.isReadOnly = True

        # Specifically for headers
        self.fontFamily = wx.FONTFAMILY_DEFAULT
        self.fontStyle = wx.FONTSTYLE_NORMAL
        self.fontWeight = wx.FONTWEIGHT_BOLD
        self.isUnderlined = True
        return

    def startupHandler(self):
        """Make cell extend across the grid."""
        StringGridCell.startupHandler(self)

        # Make the cell span the remaining columns
        ncols = self.table.GetNumberCols()
        self.table.grid.SetCellSize(self.row, self.col, 1, ncols-self.col)
        return

class BoolGridCell(GridCellData):
    """Class for holding information about boolean cells."""

    def __init__(self):
        GridCellData.__init__(self)

        self._datatype = wx.grid.GRID_VALUE_BOOL
        return

    def getEditorParametersString(self):
        """Get the cell format string needed by CustomGridDataTable."""
        return ""

class RowToggleGridCell(BoolGridCell):
    """A BoolGridCell that enables/disables its entire row.
    
    If the box is checked, the row is enabled. If the box is not checked, the
    row is disabled.
    """

    def handler(self):
        """Set cells in row as editable or not based on toggle state."""
        ncols = self.table.GetNumberCols()
        for col in range(ncols):
            if col != self.col:
                data = self.table.getDataObject(self.row, col)
                if data:
                    data.isReadOnly = not self.value
        return

    def startupHandler(self):
        """Set cells in row as editable or not based on toggle state."""
        return self.handler()


class NumberGridCell(GridCellData):
    """Class for holding information about integer cells."""

    def __init__(self):
        GridCellData.__init__(self)

        self._datatype = wx.grid.GRID_VALUE_NUMBER

        # Editor parameters. Default to no parameter checking.
        self.min = -1
        self.max = -1
        return

    def getEditorParametersString(self):
        """Get the cell format string needed by CustomGridDataTable."""
        return ":%i,%i" % (self.min, self.max)

class FloatGridCell(GridCellData):
    """Class for holding information about float cells."""

    def __init__(self):
        GridCellData.__init__(self)

        self._datatype = wx.grid.GRID_VALUE_FLOAT

        # These integer formatting options. Default to unrestricted.
        self.width = -1
        self.precision = -1
        return

    def getEditorParametersString(self):
        """Get the cell format string needed by CustomGridDataTable."""
        return ":%i,%i" % (self.width, self.precision)

class ChoiceGridCell(GridCellData):
    """Class for holding information about choice cells."""

    def __init__(self):
        GridCellData.__init__(self)

        self._datatype = wx.grid.GRID_VALUE_CHOICE

        # Editor parameters.
        self.choices = []
        return

    def getEditorParametersString(self):
        """Get the cell format string needed by CustomGridDataTable."""
        if self.choices:
            return ":%s" % ",".join(self.choices)
        else:
            return ""

#---------------------------------------------------------------------------

class CustomTableGrid(wx.grid.Grid):
    def __init__(self, parent, log):
        wx.grid.Grid.__init__(self, parent, -1)
        self.log = log

        # The second parameter means that the grid is to take ownership of the
        # table and will destroy it when done.  Otherwise you would need to keep
        # a reference to it and call it's Destroy method later.
        self.SetRowLabelSize(0)
        self.SetMargins(0,0)
        self.AutoSizeColumns(True)

        # EVENT BINDING
        wx.grid.EVT_GRID_CELL_LEFT_DCLICK(self, self.onLeftDClick)
        wx.grid.EVT_GRID_CELL_CHANGE(self, self.onCellChange)
        #wx.grid.EVT_GRID_EDITOR_HIDDEN(self, self.onEditorHidden)
        return

    # EVENT HANDLERS
    def onLeftDClick(self, evt):
        """Process double click as two clicks."""
        if self.CanEnableCellControl():
            self.EnableCellEditControl()
        return

    def onCellChange(self, evt):
        """Call the cell's handler function on a cell change."""
        return
        row = evt.GetRow()
        col = evt.GetCol()
        table = self.GetTable()
        data = table.getDataObject(row, col)
        # Batch this just in case it makes lots of modifications to the grid
        self.BeginBatch()
        if data:
            data.handler()
        self.EndBatch()
        evt.Skip()
        return

    def onEditorHidden(self, evt):
        """Call the update the cell size."""
        # FIXME - AutoSize seems to be broken in this context
        self.AutoSize()
        return

    # UTILITY METHODS

    def setData(self, colLabels, dataList):
        """Change the grid's table.

        colLabels   --  List of column labels
        dataList    --  List of row dictionaries. Dictionary keys correspond to
                        column labels. Dictionary items are GridCellData objects.
        """
        # FIXME - AutoSize seems to be broken

        # This hides all shown editors. Seems to somehow cause a segmentation
        # fault.
        nrows = self.GetNumberRows()
        ncols = self.GetNumberCols()
        for row in range(nrows):
            for col in range(ncols):
                editor = self.GetCellEditor(row, col)
                if editor.IsCreated():
                    editor.EndEdit(row, col, self)
                    editor.Show(False)

        # Make the new table
        table = CustomGridDataTable(self.log)
        table.grid = self
        table.setColLabels(colLabels)
        table.setDataList(dataList)
        self.SetTable(table, True)
        self.callStartupHandlers()
        return

    def callStartupHandlers(self):
        """Call the startup handlers of the cells."""
        table = self.GetTable()
        nrows = table.GetNumberRows()
        ncols = table.GetNumberCols()

        # Batch this just in case it makes lots of modifications to the grid
        self.BeginBatch()
        for row in range(nrows):
            for col in range(ncols):
                data = table.getDataObject(row, col)
                if data:
                    data.startupHandler()
        self.EndBatch()
        return



#---------------------------------------------------------------------------

colLabels = ["name", "uno", "dos", "tres"]

# Set up Row 1
row1 = {}
row1["name"] = StringGridCell()
row1["name"].SetValue("Row 1")
row1["name"].tag = "name"
row1["uno"] = RowToggleGridCell()
row1["uno"].SetValue(True)
row1["uno"].tag = "uno"
row1["dos"] = ChoiceGridCell()
row1["dos"].SetValue("reallylongword")
row1["dos"].choices = ["1.0", "pie", "ham", "reallylongword"]
row1["dos"].tag = "dos"
row1["tres"] =  StringGridCell()
row1["tres"].SetValue("Three")
row1["tres"].tag = "tres"

# Set up Row 2
row2 = {}
row2["name"] = StringGridCell()
row2["name"].SetValue("Row 2")
row2["name"].tag = "name"
row2["uno"] = NumberGridCell()
row2["uno"].SetValue(2)
row2["uno"].min = 1
row2["uno"].max = 9
row2["uno"].tag = "uno"
row2["dos"] = FloatGridCell()
row2["dos"].SetValue(2.0)
row2["dos"].width = 6
row2["dos"].precision = 4
row2["dos"].tag = "dos"

row3 = {}
row3["name"] = HeaderGridCell()
row3["name"].SetValue("Header cells span the columns")
row3["name"].tag = "name"

row4 = {}
row4["name"] = StringGridCell()
row4["name"].SetValue("Row 4")
row4["name"].tag = "name"

dataList = [ row1, row2 ]

class TestFrame(wx.Frame):
    def __init__(self, parent, log):

        wx.Frame.__init__(
            self, parent, -1, "Custom Table, data driven Grid  Demo", size=(640,480)
            )

        self.log = log
        self.p = wx.Panel(self, -1, style=0)
        self.grid = CustomTableGrid(self.p, self.log)
        self.grid.setData(colLabels, dataList)
        b = wx.Button(self.p, -1, "Toggle Data Table")
        b.SetDefault()
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)
        bs = wx.BoxSizer(wx.VERTICAL)
        bs.Add(self.grid, 1, wx.GROW|wx.ALL, 5)
        bs.Add(b)
        self.p.SetSizer(bs)
        self.toggle = 0
        return

    def OnButton(self, evt):
        if self.toggle == 0:
            self.toggle = 1
            cL = ["name", "dos", "tres"]
            dL = [row1, row3]
        elif self.toggle == 1:
            self.toggle = 2
            cL = ["name", "uno", "tres"]
            dL = [row1, row2, row3, row4]
        else:
            self.toggle = 0
            cL = ["name", "uno", "dos", "tres", "quatro"]
            dL = [row1, row2, {}]
        self.grid.setData(cL, dL)
        return


#---------------------------------------------------------------------------

if __name__ == '__main__':
    import sys
    app = wx.PySimpleApp()
    frame = TestFrame(None, sys.stdout)
    frame.Show(True)
    app.MainLoop()


#---------------------------------------------------------------------------

 	  	 
