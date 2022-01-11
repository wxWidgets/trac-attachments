from wxPython.wx import *
from wxPython.grid import *

class Huge(wxPyGridTableBase):
   def GetNumberCols(self): return 100
   def GetNumberRows(self): return 20000000
   def GetColLabelValue(self, col): return str(col)
   def GetRowLabelValue(self, row): return str(row)
   def GetValue(self, row, col): return "wait..."

class T(wxGrid):
   def __init__(self, parent, **kw):
       apply(wxGrid.__init__, (self, parent, -1), kw)
       self.table = Huge()
       self.SetTable(self.table, true)
app = wxPySimpleApp()
foo = wxFrame(None, -1, "Bad Grid")
grid = T(foo)
foo.Show()
app.MainLoop() 

 	  	 
