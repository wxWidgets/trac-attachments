#!/usr/bin/env python

from wxPython.wx import *

class wxFrame1(wxFrame):
    def __init__(self, parent):
        wxFrame.__init__(self, parent, -1, title = 'testFrame', 
                         style = wxDEFAULT_FRAME_STYLE)
        exitID = wxNewId()
        aTable = wxAcceleratorTable([(wxACCEL_CTRL, ord('Q'), exitID),
                                     (wxACCEL_ALT, ord('X'), exitID)])
        self.SetAcceleratorTable(aTable)

        EVT_MENU(self, exitID, self.OnExit)

    def OnExit(self, evt):
        self.Close()

class BoaApp(wxApp):
    def OnInit(self):
        self.main = wxFrame1(None)
        self.main.Show(true)
        self.SetTopWindow(self.main)
        return true

def main():
    application = BoaApp(0)
    application.MainLoop()

if __name__ == '__main__':
    main()


 	  	 
