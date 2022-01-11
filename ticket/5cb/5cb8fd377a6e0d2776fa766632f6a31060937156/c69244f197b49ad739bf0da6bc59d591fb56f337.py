
import  wx
import  wx.grid as gridlib

#---------------------------------------------------------------------------

class CustomDataTable(gridlib.PyGridTableBase):
    def __init__(self, log):
        gridlib.PyGridTableBase.__init__(self)
        self.log = log

        self.colLabels = ['ID']

        self.dataTypes = [gridlib.GRID_VALUE_NUMBER]

        self.data = []
        for i in range(5):
            self.data.append([i])

    def GetNumberRows(self):
        return len(self.data)

    def GetNumberCols(self):
        return len(self.data[0])

    def IsEmptyCell(self, row, col):
        return not self.data[row][col]

    def GetValue(self, row, col):
        return self.data[row][col]

    def SetValue(self, row, col, value):
        self.data[row][col] = value

    def GetColLabelValue(self, col):
        return self.colLabels[col]

    def GetTypeName(self, row, col):
        return self.dataTypes[col]

    def CanGetValueAs(self, row, col, typeName):
        colType = self.dataTypes[col].split(':')[0]
        if typeName == colType:
            return True
        else:
            return False

    def CanSetValueAs(self, row, col, typeName):
        return self.CanGetValueAs(row, col, typeName)

    def InsertRows(self, pos=0, numRows=1, updateLabels=True):
        """Insert a row at the desired position"""
        for i in range(numRows):
            self.data.insert(pos+1, [''] * self.GetNumberCols())

            # XXX inserted and deleted are switched
            # Though I'm saying inserted, the grid will remove a row!
            msg = gridlib.GridTableMessage(self, 
                    gridlib.GRIDTABLE_NOTIFY_ROWS_INSERTED,
                    1
                    )

            self.GetView().ProcessTableMessage(msg)
        
    def DeleteRows(self, pos=0, numRows=1):
        """Delete a row at the desired position"""
        try:
            for i in range(numRows):
                del self.data[pos]

                # tell the grid we've deleted a row 
                # (for some reason the grid adds a row)
                msg = gridlib.GridTableMessage(self,  
                        gridlib.GRIDTABLE_NOTIFY_ROWS_DELETED, 
                        1                                       
                        )

                self.GetView().ProcessTableMessage(msg)
        except IndexError:
            # There's really not much we can do...
            pass



#---------------------------------------------------------------------------



class CustTableGrid(gridlib.Grid):
    def __init__(self, parent, log):
        gridlib.Grid.__init__(self, parent, -1)

        table = CustomDataTable(log)

        self.SetTable(table, True)
        
        gridlib.EVT_GRID_CELL_RIGHT_CLICK(self, self.OnRightClick)
        
    # Show "Context Menu" to insert/delete rows
    def OnRightClick(self, evt):
        # select the row that was clicked
        self.SelectRow(evt.GetRow())
        
        if not hasattr(self, "rcDeleteRowID"):
            self.rcDeleteRowID = wx.NewId()
            self.rcInsertRowID = wx.NewId() 

            self.Bind(wx.EVT_MENU, self.OnRemoveRow, id=self.rcDeleteRowID)
            self.Bind(wx.EVT_MENU, self.OnInsertRow, id=self.rcInsertRowID)

        # make a menu
        menu = wx.Menu()
        item = wx.MenuItem(menu, self.rcDeleteRowID,"Delete Row")
        menu.AppendItem(item)
        menu.Append(self.rcInsertRowID, "Insert Row")

        self.PopupMenu(menu)
        menu.Destroy()
        
    def OnRemoveRow(self, event):
        if len(self.GetSelectedRows()) > 0:
            self.DeleteRows(self.GetSelectedRows()[0])

    def OnInsertRow(self, event):
        if len(self.GetSelectedRows()) > 0:
            self.InsertRows(self.GetSelectedRows()[0])

#---------------------------------------------------------------------------

class TestFrame(wx.Frame):
    def __init__(self, parent, log):

        wx.Frame.__init__(
            self, parent, -1, "Delete message to delete, Insert to insert", size=(640,480)
            )

        p = wx.Panel(self, -1, style=0)
        grid = CustTableGrid(p, log)
        bs = wx.BoxSizer(wx.VERTICAL)
        bs.Add(grid, 1, wx.GROW|wx.ALL, 5)
        p.SetSizer(bs)

    def OnButton(self, evt):
        print "button selected"

    def OnButtonFocus(self, evt):
        print "button focus"


#---------------------------------------------------------------------------

if __name__ == '__main__':
    import sys
    app = wx.PySimpleApp()
    frame = TestFrame(None, sys.stdout)
    frame.Show(True)
    app.MainLoop()


#---------------------------------------------------------------------------

 	  	 
