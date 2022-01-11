#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

import wx.gizmos


class Toto(wx.gizmos.TreeListCtrl):
    def __init__(self, parent, id, columnsInfos) :
        wx.gizmos.TreeListCtrl.__init__(self, parent, id, style=wx.LC_REPORT | wx.SUNKEN_BORDER | wx.LC_VRULES | wx.LC_HRULES)
        
        self._columnsInfos = columnsInfos
        
        # Construction des colonnes
        for i in range(len(self._columnsInfos)) :
            column = self._columnsInfos[i]
            self.AddColumn(column["TEXT"])
            self.SetColumnWidth(i, column["MINSIZE"])
        
        self.AddRoot("toto")

    def onMotion(self,  event):
        print "Motion"
        self.SetToolTip(wx.ToolTip("toto"))




COLUMNS = [
    {"TEXT" : "",
     "MINSIZE" : 22,
     "ALIGNMENT" : wx.LIST_FORMAT_CENTER},
    {"TEXT" : "One",
     "MINSIZE" : 65,
     "ALIGNMENT" : wx.LIST_FORMAT_CENTER},
    {"TEXT" : "Two",
     "MINSIZE" : 70,
     "ALIGNMENT" : wx.LIST_FORMAT_CENTER},
    {"TEXT" : "Three",
     "MINSIZE" : 95,
     "ALIGNMENT" : wx.LIST_FORMAT_CENTER},
    {"TEXT" : "Four",
     "MINSIZE" : 110,
     "ALIGNMENT" : wx.LIST_FORMAT_LEFT}
    ]


class MyFrame(wx.Frame) :
    def __init__(self, parent) :
        wx.Frame.__init__(self, parent, -1, "Test")
        
        item0 = wx.FlexGridSizer( 0, 1, 0, 0 )
        item0.AddGrowableCol( 0 )
        item0.AddGrowableRow( 0 )
        self.SetSizer( item0 )
        item0.SetSizeHints( self )
        
        ID = 2003
        
        list = Toto(self, ID, COLUMNS)
        
        list.Bind(wx.EVT_MOTION, list.onMotion)
        
        item0.Add(list, 1, wx.GROW|wx.ALIGN_CENTER_VERTICAL, 5 )
        
        # Taille de la fenetre
        self.SetSize((500,400))
        


class MainApp(wx.App):
    def __init__(self) :
        wx.App.__init__(self, 0)
        
    def OnInit(self):
        wx.InitAllImageHandlers()
        self._frame = MyFrame(None)
        self._frame.Show(True)
        self.SetTopWindow(self._frame)
        return True

def main() :
    app = MainApp()
    app.MainLoop()
    
    
    
if __name__ == '__main__':
    main()

 	  	 
