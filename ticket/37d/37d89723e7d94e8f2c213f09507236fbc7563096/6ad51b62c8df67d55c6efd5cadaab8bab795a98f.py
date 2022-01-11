# this code illustrates two errors:

# 1. SetDropTarget()
#    custom drag and drop does not work with wxTE_RICH and wxTE_RICH2 
#    TextCtrl. Just change the commented line below to see the effect
# 2. button-up-event not caught in this case

# start script from the commandline to see messages



from wxPython.wx import * 
 
MENU_FILE_EXIT = 101 
DRAG_SOURCE    = 201 
 
class TextDropTarget(wxTextDropTarget): 
    def __init__(self, obj): 
        wxTextDropTarget.__init__(self) 
        self.obj = obj 
 
    def OnDropText(self, x, y, data): 
        self.obj.WriteText(data) 
        print 'custom drag and drop working' 
 
class MainWindow(wxFrame): 
    def __init__(self,parent,id,title): 
        wxFrame.__init__(self,parent,-4, title, size = (-1,-1), style=wxDEFAULT_FRAME_STYLE|wxNO_FULL_REPAINT_ON_RESIZE) 
        self.SetBackgroundColour(wxWHITE) 
 
        menuBar = wxMenuBar() 
        menu1 = wxMenu() 
        menu1.Append(MENU_FILE_EXIT, "E&xit", "Quit Application") 
        menuBar.Append(menu1, "&File") 
        self.SetMenuBar(menuBar) 
        EVT_MENU(self, MENU_FILE_EXIT, self.CloseWindow) 
        
# remove wxTE_RICH to see drag and drop working !!!
# drag data from other window/application

#        self.text = wxTextCtrl(self, -1, "", size=(410,235), style = wxTE_MULTILINE) 
        self.text = wxTextCtrl(self, -1, "", size=(410,235), style = wxTE_MULTILINE|wxTE_RICH) 

        dt1 = TextDropTarget(self.text) 
        self.text.SetDropTarget(dt1) 
        EVT_RIGHT_DOWN(self.text, self.OnDragInit) 
        EVT_RIGHT_UP(self.text, self.OnRightUp)
        EVT_LEFT_UP(self.text, self.OnLeftUp)
        self.Show(true) 
 
    def OnRightUp(self, evt):
        print "Right Up "
        evt.Skip()
 
    def OnLeftUp(self, evt):
        print "Left Up "
        evt.Skip()
        
    def CloseWindow(self, event): 
        self.Close() 
 
    def OnDragInit(self, event): 
        tdo = wxPyTextDataObject(self.text.GetStringSelection()) 
        tds = wxDropSource(self.text) 
        tds.SetData(tdo) 
        tds.DoDragDrop(wx.true) 
 
class MyApp(wxApp): 
    def OnInit(self): 
        frame = MainWindow(None, -1, "Drag and Drop Example") 
        self.SetTopWindow(frame) 
        return true 
       
 
# Declare the Application and start the Main Loop 
app = MyApp(0) 
app.MainLoop() 

 	  	 
