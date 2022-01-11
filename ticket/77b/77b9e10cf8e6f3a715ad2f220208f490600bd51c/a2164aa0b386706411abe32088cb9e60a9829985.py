import wx

class MakeTextCtrl(wx.TextCtrl):
    def __init__(self, parent):
        #Create a TextCtrl
        #style MUST BE SPECIFIED LIKE THIS TO MAKE THE CODE WORK
        wx.TextCtrl.__init__(self, parent, -1, pos = (75, 50), size = wx.Size(200, 100),\
            style = wx.TE_RICH | wx.TE_MULTILINE)
        
        #Set default text colour: blue and default background colour: white
        #THIS ONLY WORKES WHITH wx.TE_MULTILINE (GTK) OR wx.TE_RICH (MSW)
        self.SetDefaultStyle(wx.TextAttr(wx.BLUE, wx.WHITE))
        
        #Write something
        self.WriteText('Some text.................')
        
        #Change text and background colour after writing
        #THIS ONLY WORKES WHITH wx.TE_MULTILINE (GTK) OR wx.TE_RICH (MSW)
        self.SetStyle(5, 9, wx.TextAttr(wx.RED, wx.CYAN))
        
        #Make the text read only
        self.SetEditable(False)
        
        self.Bind(wx.EVT_SET_FOCUS, self.Mark)
        self.Bind(wx.EVT_KILL_FOCUS, self.DelMark)
        
    #Set background colour: grey when the TextCtrl is selected
    def Mark(self, evt):
        self.SetBackgroundColour(wx.LIGHT_GREY)
    
    #Set background colour: white when the TextCtrl no longer selected
    #THIS ONLY WORKES WHITH wx.TE_RICH (MSW)
    def DelMark(self, evt):
        self.SetBackgroundColour(wx.WHITE)

class MainFrame(wx.Frame):
    def __init__(self, parent):
        #Create a Frame
        wx.Frame.__init__(self, None, -1, 'Frame')

        #Initiate the TextCtrl
        p = wx.Panel(self, -1)
        TextCtrl = MakeTextCtrl(p)
        
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)

    #Destroy the Frame when it is closed
    def OnCloseWindow(self, event):
        self.Destroy()

class TestApp(wx.App):
    def OnInit(self):
        frame = MainFrame(self)
        frame.Show(True)
        self.SetTopWindow(frame)
        return True

app = TestApp(False)
app.MainLoop()

        
 	  	 
