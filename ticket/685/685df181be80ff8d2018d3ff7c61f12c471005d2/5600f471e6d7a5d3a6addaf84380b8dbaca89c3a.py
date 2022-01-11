from wxPython.wx import *

#To reproduce bug:
# 1) scroll to bottom of window
# 2) maximize window
# 3) scroll back to the top
# 4) note lots of extra space at top

class tpFrame(wxFrame):
  def __init__(self):
    '''Initialize the main UI window'''
    wxFrame.__init__(self, None, -1, 'GUI Test', wxPoint(10,10))

    bouts = 16
    space = 30

    pane = wxScrolledWindow(self)

    for i in range(space, space*bouts*2+1, space):
      wxStaticLine(pane, -1, wxPoint(0, i), wxSize(200, 1))

    for i in range(space, space*bouts*2, space*2):
      wxStaticLine(pane, -1, wxPoint(198, i), wxSize(1, space+1))
      
    pane.SetScrollbars(10, 10, 100, 100)


if __name__ == "__main__":
  #constants
  DOS_WINDOW = 0
  GUI_WINDOW = 1

  #create the application, the user interface, and the atlas
  app = wxPySimpleApp(DOS_WINDOW)
  ui = tpFrame()
  ui.Show(True)
  app.SetTopWindow(ui)

  #start the message loop
  app.MainLoop()

 	  	 
