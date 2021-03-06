#!/usr/bin/env python
# -*- coding: ANSI_X3.4-1968 -*-
# generated by wxGlade 0.3.5.1 on Thu Jun  9 15:21:05 2005

import wxversion

wxversion.select("2.6")

import wx
import wx.grid

class MyFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        # begin wxGlade: MyFrame.__init__
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        self.grid_1 = wx.grid.Grid(self, -1, size=(1, 1))

        self.__set_properties()
        self.__do_layout()
        # end wxGlade

	wx.grid.EVT_GRID_CELL_RIGHT_CLICK(self.grid_1, self.Selection )
        self.myTimer = wx.Timer(self, 2) # create a timer
        wx.EVT_TIMER(self,2,self.OnUpdate)
        self.myTimer.Start(5000) # launch timer, to fire every 5000ms (5 seconds)


    def __set_properties(self):
        # begin wxGlade: MyFrame.__set_properties
        self.SetTitle("frame_1")
        self.SetSize((400, 300))
        self.grid_1.CreateGrid(10, 3)
        #self.grid_1.EnableEditing(0)
        #self.grid_1.EnableDragColSize(0)
        #self.grid_1.EnableDragRowSize(0)
        #self.grid_1.EnableDragGridSize(0)
        #self.grid_2.SetSelectionMode(wx.grid.Grid.wxGridSelectRows)
        # end wxGlade

    def __do_layout(self):
        # begin wxGlade: MyFrame.__do_layout
        sizer_1 = wx.BoxSizer(wx.HORIZONTAL)
        sizer_1.Add(self.grid_1, 1, wx.ALL|wx.EXPAND, 0)
        self.SetAutoLayout(True)
        self.SetSizer(sizer_1)
        self.Layout()
        # end wxGlade

    def Selection(self, event):
	print "event object =",event.GetEventObject()
	print "event type =",event.GetEventType()
    	print "Number of rows selected =",len(self.grid_1.GetSelectedRows())
    	print "Number of cols selected =",len(self.grid_1.GetSelectedCols())
    	print "Number of cells selected =",len(self.grid_1.GetSelectedCells())

    def OnUpdate(self, event):
    	print "Number of rows selected =",len(self.grid_1.GetSelectedRows())
    	print "Number of cols selected =",len(self.grid_1.GetSelectedCols())
    	print "Number of cells selected =",len(self.grid_1.GetSelectedCells())


# end of class MyFrame


class GridSelectBug(wx.App):
    def OnInit(self):
        wx.InitAllImageHandlers()
        frame_1 = MyFrame(None, -1, "")
        self.SetTopWindow(frame_1)
        frame_1.Show()
        return 1

# end of class GridSelectBug

if __name__ == "__main__":
    GridSelectBug = GridSelectBug(0)
    GridSelectBug.MainLoop()

 	  	 
