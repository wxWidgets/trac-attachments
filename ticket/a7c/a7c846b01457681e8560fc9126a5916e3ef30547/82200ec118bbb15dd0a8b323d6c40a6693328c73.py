import sys

import numpy

import wx
import wx.lib.printout as printout
    
class MainWindow(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        data = numpy.array(xrange(100)).reshape(10,10)
        prt = printout.PrintTable(self)
        prt.data = data
        prt.Preview()

def main():
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()
    
    main_window = MainWindow()
    
    app.SetTopWindow(main_window)
    main_window.Show()
    app.MainLoop()


if __name__ == "__main__":
    main()
