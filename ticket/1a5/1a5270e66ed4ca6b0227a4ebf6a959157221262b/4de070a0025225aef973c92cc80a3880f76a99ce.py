#This Program demonstrates a bug in wxPython(or wxWindows?) which causes 
#the edit control to appear in the wrong wxNotebook page if you define a 
#wxGrid with a custom data table and custom data types.
from wxPython.wx import *
from wxPython.grid import *

#-------------------------

class MyTextType:
        Editor=wxGridCellTextEditor()
        Renderer=wxGridCellStringRenderer()
class MyNumberType:
        Editor=wxGridCellNumberEditor()
        Renderer=wxGridCellNumberRenderer()
class MyFloatType:
        Editor=wxGridCellTextEditor()
        Renderer=wxGridCellFloatRenderer()
#---------------------------------------------------------------------------
class CustTableGrid(wxGrid):
        
    def __init__(self, parent):
        wxGrid.__init__(self, parent, -1)
        #a list of tuples containing the typename, a typeclass reference, and some sample data for each custom type
        TestTypes=[("MyTextType",MyTextType,"Strange behaviour in this column"),("MyNumberType",MyNumberType,1234),("MyFloatType",MyFloatType,3.25)]
        #register the datatype for each custom type
        for (TypeName,TypeClass,Value) in TestTypes:
                self.RegisterDataType(TypeName, TypeClass.Renderer, TypeClass.Editor)
                   
        #append some non custom types to the list for comparison to the custom ones in the grid 
        TestTypes.append((wxGRID_VALUE_STRING,None,"Expected behaviour in this column"))
        table = CustomDataTable(TestTypes)
        self.SetTable(table, true)
        self.AutoSizeColumns(True)
        
class CustomDataTable(wxPyGridTableBase):

    def __init__(self,TestTypes):
        wxPyGridTableBase.__init__(self)
        self.colLabels=[]
        self.dataTypes=[]
        self.data=[[] for i in range(5)]
        for (name,type,value) in TestTypes:
                self.colLabels.append(name)
                self.dataTypes.append(name)
                for row in self.data:
                        row.append(value)
                
    #--------------------------------------------------
    # required methods for the wxPyGridTableBase interface
    def GetNumberRows(self):
        return len(self.data) + 1

    def GetNumberCols(self):
        return len(self.colLabels)

    def IsEmptyCell(self, row, col):
        try:
            return not self.data[row][col]
        except IndexError:
            return true
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
    def GetColLabelValue(self, col):
        return self.colLabels[col]
    def GetTypeName(self, row, col):
        return self.dataTypes[col]
#----------------------------------------------------------------
class TestNB(wxNotebook):
    def __init__(self, parent, id):
        wxNotebook.__init__(self, parent, id, style=
                            wxNB_TOP
                            #wxNB_BOTTOM
                            #wxNB_LEFT
                            #wxNB_RIGHT
                            )
        win = CustTableGrid(self)
        self.AddPage(win, "Grid 1")
        win=CustTableGrid(self)
        self.AddPage(win, "Grid 2")
#---------------------------------------------------------------------------
class TestFrame(wxFrame):
    def __init__(self, parent):
        wxFrame.__init__(self, parent, -1, "Custom Grid Cell Editor Test",
                         size=(640,480))
        nb=TestNB(self,-1)

#---------------------------------------------------------------------------
if __name__ == '__main__':
    import sys
    app = wxPySimpleApp()
    frame = TestFrame(None)
    frame.Show(True)
    app.MainLoop()

 	  	 
