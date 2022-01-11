import wx

print "wx.__version__", wx.__version__


def printobj(event):
    s = str(event.GetEventObject())
    offset = s.index(';')
    return ": " + s[1:offset]


class MyFrame(wx.Frame):
    def __init__(self, parent, id, title, size): 
        wx.Frame.__init__(self, parent, id, title, size=size)

        self.numIdles = 0
        
        wx.EVT_WINDOW_CREATE(self, self.on_initialize)
        wx.EVT_ACTIVATE(self, self.on_activate)
        wx.EVT_MOVE(self, self.on_move)
        wx.EVT_SIZE(self, self.on_size)
        wx.EVT_IDLE(self, self.on_idle)
        wx.EVT_ICONIZE(self, self.on_minimize)
        wx.EVT_MAXIMIZE(self, self.on_maximize)
        wx.EVT_CLOSE(self, self.on_close)

        panel = wx.Panel(self, -1)
        #print "frame:", frame, frame.__class__

        self.text1 = wx.TextCtrl(panel, -1, 'Hello World', pos=(5, 5))
        wx.EVT_SET_FOCUS(self.text1, self.on_gainFocus)
        wx.EVT_KILL_FOCUS(self.text1, self.on_loseFocus)

        self.btn = wx.Button(panel, -1, "btn", (5, 40))
        wx.EVT_BUTTON(panel, self.btn.GetId(), self.on_mouseClick)

    def on_initialize(self, event):
        print "initialize", printobj(event)
        event.Skip()

    def on_activate(self, event):
        print "activate", event.GetActive(), printobj(event)
        event.Skip()

    def on_move(self, event):
        print "move", printobj(event), event.GetPosition()
        event.Skip()

    def on_size(self, event):
        print "size", printobj(event), event.GetSize()
        event.Skip()

    def on_idle(self, event):
        # prevent idle message flood
        if self.numIdles < 5:
            self.numIdles += 1
            print "idle", printobj(event)
        event.Skip()

    def on_minimize(self, event):
        print "minimize", printobj(event)
        event.Skip()

    def on_maximize(self, event):
        print "maximize", printobj(event)
        event.Skip()

    def on_close(self, event):
        print "close", printobj(event)
        event.Skip()

    # control events
    
    def on_gainFocus(self, event):
        print "gainFocus", printobj(event)
        event.Skip()

    def on_loseFocus(self, event):
        print "loseFocus", printobj(event)
        event.Skip()

    def on_mouseClick(self, event):
        print "mouseClick", printobj(event)
        event.Skip()


class MyApp(wx.App):

    def OnInit(self):
        #frame = wx.wxFrame(None, -1, "minimal", size=(200, 200))
        frame = MyFrame(None, -1, "minimal", size=(200, 200))
        self.frame = frame
        
        frame.Show(1)
        self.SetTopWindow(frame)
        return True


app = MyApp(0)
app.MainLoop()

 	  	 
