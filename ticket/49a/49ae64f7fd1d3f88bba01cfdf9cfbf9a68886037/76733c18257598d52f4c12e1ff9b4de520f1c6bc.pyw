###!/Library/Frameworks/Python.framework/Versions/2.3/Resources/Python.app/Contents/MacOS/python

#import os, sys, time, shutil, threading
from wxPython.wx import *
from wxPython.grid import *

class EVBTableBase(wxPyGridTableBase):
    def __init__(self, colNames, colTypes, values):
        wxPyGridTableBase.__init__(self)
        self.colNames = colNames
        self.colTypes = colTypes
        self.values = values
    def GetNumberRows(self):
        return len(self.values)
    def GetNumberCols(self):
        return len(self.values[0])
    def GetValue(self,row,col):
        return self.values[row][col]
    def SetValue(self,row,col, value):
        self.values[row][col] =value
    def GetColLabelValue(self,col):
        return self.colNames[col]
    def GetRowLabelValue(self, row):
        return self.values[row][0] #label is column 0
    def GetTypeName(self,row,col):
        typeMap = { "B": wxGRID_VALUE_BOOL, "D":wxGRID_VALUE_FLOAT, "I":wxGRID_VALUE_NUMBER, "S":wxGRID_VALUE_STRING}
        return typeMap[self.colTypes[col]]
    def isEditable(self, row, col):
        if col == 0:
            return False
        else:
            return True
    def IsEmptyCell(self, row, col):
        try:
            return not self.values[row][col]
        except IndexError:
            return true

     
class EVBTable(wxGrid):
    def __init__(self, dataModel, parent = None, name = None):
        self._dataModel = dataModel
        wxGrid.__init__(self, parent, -1)
        self.SetTable(dataModel, True)
        self.BeginBatch()
        self.SetMargins(20,20)
        self.AutoSize()
        #add a bit of space between each row
        rs = self.GetDefaultRowSize()
        self.SetDefaultRowSize(rs + 5, True)
        if dataModel.isEditable(0,0):
            self.SetRowLabelSize(0) #No row labels
        else:
            labelSize = self.GetColSize(0)
            self.SetRowLabelSize(labelSize)
            self.SetColSize(0,0) #Hide col 0, as it now is the row label
        self.EndBatch()
   

class ControlFiles(wxFrame):
    """Edit control files"""
    def __init__(self, parent = None, caption = None):
        wxFrame.__init__(self, parent, -1, caption, size= (640,480), style=wxDEFAULT_FRAME_STYLE|wxNO_FULL_REPAINT_ON_RESIZE)

        #events
        #EVT_CLOSE(self, self.OnCloseWindow)
        self.Centre(wxBOTH)
        self.CreateStatusBar(1, wxST_SIZEGRIP)
        split = wxSplitterWindow(self, -1, style=wxNO_3D|wxSP_3D)
        def EmptyHandler(evt): pass
        EVT_ERASE_BACKGROUND(split, EmptyHandler)

        tID = wxNewId()
        list = wxTreeCtrl(split, tID, style=wxTR_HAS_BUTTONS |
                               wxTR_HAS_VARIABLE_ROW_HEIGHT)
        self.list = list 
        root = list.AddRoot("System Control")
        da = list.AppendItem(root, "Data Acquisition")
        self.nb = wxNotebook(split, -1)
        tbl = EVBTable(EVBTableBase(("Desc", "Value"), ("S", "B"), [["Test 1", 0], ["Test 2", 1]]), self.nb)
        tbl2 = EVBTable(EVBTableBase(("Desc", "Value"), ("S", "D"), [["Test 1", 0], ["Test 2", 1]]), self.nb)
        tbl3 = EVBTable(EVBTableBase(("Desc", "Value", "Value2"), ("S", "I", "I"), \
                                     [["1 Write retention time on top of sheet:", 1, ""]] * 11 + [["Test 12", 0, 5],\
                                    ["test 13", 0, 2], ["Test 14", 0, 4]] +\
                                     [["Testing", 0, ""]] *2 + \
                                     [["Buggyy", -1,"2"], ["Hmm", 5, ""],["Why", 0,""]]), self.nb)
        self.nb.AddPage(tbl, "Boolean")
        self.nb.AddPage(tbl2, "Float")
        self.nb.AddPage(tbl3, "Int")
        self.nb.SetSelection(0)

        split.SplitVertically(self.list, self.nb, 180)
        split.SetMinimumPaneSize(20)

        return
            
def main():
    app = wxPySimpleApp()
    cf = ControlFiles(None, "Control Files")
    cf.Show(true)
    cf.Raise()
    app.SetTopWindow(cf)
    app.MainLoop()

if __name__ == '__main__':
    main()
    #
    #

 	  	 
