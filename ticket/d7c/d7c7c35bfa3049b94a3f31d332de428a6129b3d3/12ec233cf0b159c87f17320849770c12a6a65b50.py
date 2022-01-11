import wx


class DisplayOptions(wx.Panel):
    """
    The display options panel displays the name  options.
    """
    def __init__(self, parent, id):
        # note that simple border produces a dark border
        wx.Panel.__init__(self, parent, id)

        lbox = wx.StaticBox(self, -1, "Name")
        self.namesizer = wx.StaticBoxSizer(lbox, wx.VERTICAL)

        self.lblexclusion = wx.StaticText(self, -1,
"Label\n\
 - Must Press <Enter>" )

        self.exclusion = wx.TextCtrl(self, -1, "")
        self.Bind(wx.EVT_TEXT_ENTER,
                      self.OnTextEnter,
                      self.exclusion,
                      )

        # set initial value of ctrl
        self.exclusion.SetValue("1234xxx")

        # set up sizer with label and ctrl
        self.exclusionsizer=wx.BoxSizer(wx.HORIZONTAL)
        self.exclusionsizer.Add(self.lblexclusion,
                      0, wx.ALIGN_LEFT|wx.ALL, 2)
        self.exclusionsizer.Add(self.exclusion,
                      1, wx.ALIGN_LEFT|wx.ALL, 2)

        self.namesizer.Add((40,40), 0) # add a spacer for indentation
        self.namesizer.Add(self.exclusionsizer, 1, wx.EXPAND)

        # put all the sizers under one
        self.mastersizer = wx.BoxSizer(wx.VERTICAL)
        # put all the sizers under one
        self.mastersizer.Add(self.namesizer, 6, wx.EXPAND|wx.NORTH|wx.EAST|wx.WEST,
                             0)
                
        self.SetSizer(self.mastersizer)
        self.mastersizer.Fit(self)

        self.Update()
 
    def OnTextEnter(self, event) :
        print "character pressed"
    
        event.Skip()
 
    

class MainWindow(wx.Frame):
    """ We simply derive a new class of Frame. """
    def __init__(self,parent,id, title):
        wx.Frame.__init__(self,parent,wx.ID_ANY,title,size=(300,300),
                          style=wx.DEFAULT_FRAME_STYLE)
        self.control = DisplayOptions(self,-1)
        self.Show(True)

app = wx.PySimpleApp()

frame=MainWindow(None,-1, 'test window')
frame.Show()
app.MainLoop()

 	  	 
