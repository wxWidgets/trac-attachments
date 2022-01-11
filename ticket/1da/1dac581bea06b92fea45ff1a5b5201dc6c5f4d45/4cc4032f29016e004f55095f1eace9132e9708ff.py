
import wx

ID_EXIT=wx.ID_EXIT

ID_PASTE=wx.ID_PASTE

#ID_HELP=wx.ID_HELP
ID_ABOUT=wx.ID_ABOUT


class MainWindow(wx.Frame):
    """The main window of the application"""
    
    _img = None
    
    def __initMenu__(self):
        # set up the menu
        fileMenu= wx.Menu()
        fileMenu.AppendSeparator()
        fileMenu.Append(ID_EXIT,"E&xit"," Terminate the application")
        
        self._fileMenu = fileMenu

        editMenu= wx.Menu()
        editMenu.Append(ID_PASTE, "&Paste\tCtrl+V"," Paste image contained in clipboard")
        
        self._editMenu = editMenu

        helpMenu= wx.Menu()
        helpMenu.AppendSeparator()
        helpMenu.Append(ID_ABOUT, "&About"," Info about this application")
        
        self._helpMenu = helpMenu
        
        # create the menubar
        menuBar = wx.MenuBar()
        menuBar.Append(fileMenu,"&File") # Adding the "filemenu" to the MenuBar
        menuBar.Append(editMenu,"&Edit") # Adding the "filemenu" to the MenuBar
        menuBar.Append(helpMenu,"&Help") # Adding the "filemenu" to the MenuBar
        self.SetMenuBar(menuBar)  # Adding the MenuBar to the Frame content.

        wx.EVT_MENU(self, ID_EXIT, self.OnExit)
        wx.EVT_MENU(self, ID_PASTE, self.PasteClipboard)
        wx.EVT_MENU(self, ID_ABOUT, self.OnAbout)
        

    def __init__(self,parent,id, title):
        wx.Frame.__init__(self,parent,wx.ID_ANY,title,size=(100,100) )
        
        self.__initMenu__()
        
        self.Bind( wx.EVT_KEY_DOWN, self.KeyPressed, self )
        
        self.Show(True)
        
    def OnAbout(self,e):
        d= wx.MessageDialog( self, 
                            " A program.. ",
                            "About Bugger", wx.OK)
        d.ShowModal() 
        d.Destroy() 

    def KeyPressed(self, evt):
        keycode = evt.GetKeyCode()
        
        if evt.ControlDown():
            if keycode == 86: #'v'
                self.PasteClipboard()
        
        level = evt.StopPropagation()
        evt.ResumePropagation(level)
        #pass the event in case anyone needs it
        evt.Skip()

        
    def PasteClipboard(self, event=None):
        do = wx.BitmapDataObject()
        if wx.TheClipboard.Open():
            success = wx.TheClipboard.GetData( do )
        
        print str( success )
        
        wx.TheClipboard.Close()

    def OnExit(self,e):
        self.Close(True)

class BugTestApp(wx.PySimpleApp):
    def OnInit(self):
        self._frame=MainWindow(None,-1,'Bugger')
        return True
        

app = BugTestApp()
app.MainLoop()


 	  	 
