import wx

class ProblemApp(wx.App):
    optionsCount = 5
    
    def OnInit(self):
        # Create main frame
        self.mainFrame = wx.Frame(parent = None, title = "Problem - Main")
        self.mainSizer = wx.BoxSizer(orient = wx.VERTICAL)
        
        self.radios = []
        for index in range(0, self.optionsCount):
            if index == 0:
                style = wx.RB_GROUP
            else:
                style = 0
            radio = wx.RadioButton(parent = self.mainFrame,
                                   label = "Choice %d" % (index + 1),
                                   style = style)
            self.mainSizer.Add(radio)
            self.radios.append(radio)
        
        self.mainFrame.Bind(wx.EVT_RADIOBUTTON, self.OnRadio)
        self.mainFrame.SetSizer(self.mainSizer)
        self.mainFrame.Show()


        # Create remote frame
        self.remoteFrame = wx.Frame(parent = None, title = "Problem - Remote")
        self.remoteSizer = wx.BoxSizer(orient = wx.VERTICAL)
        
        self.buttons = []
        for index in range(0, self.optionsCount):
            button = wx.Button(parent = self.remoteFrame,
                               label = "Select Choice %d" % (index + 1))
            self.remoteSizer.Add(button)
            self.buttons.append(button)
        
        self.remoteFrame.Bind(wx.EVT_BUTTON, self.OnButton)
        self.remoteFrame.SetSizer(self.remoteSizer)
        self.remoteFrame.Show()


        return True
    
    def OnRadio(self, event):
        print "OnRadio: '%s' clicked" % event.GetEventObject().GetLabel()
    
    def OnButton(self, event):
        print "OnButton: '%s' pressed" % event.GetEventObject().GetLabel()
        index = self.buttons.index(event.GetEventObject())
        self.radios[index].SetValue(True)
    
if __name__ == "__main__":
    app = ProblemApp(redirect = False)
    app.MainLoop()