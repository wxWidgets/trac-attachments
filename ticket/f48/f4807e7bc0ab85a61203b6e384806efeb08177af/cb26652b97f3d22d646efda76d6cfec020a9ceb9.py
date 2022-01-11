import wx
import types
import pprint

print "wx.__version__", wx.__version__


def printobj(event):
    s = str(event.GetEventObject())
    offset = s.index(';')
    return ": " + s[1:offset]


class MyFrame(wx.Frame):
    def __init__(self, parent, id, title, size): 
        wx.Frame.__init__(self, parent, id, title, size=size)

        panel = wx.Panel(self, -1)

        self.text1 = wx.TextCtrl(panel, -1, 'Hello World', pos=(5, 5))
        self.text1.Bind(wx.EVT_LEFT_DOWN, self.on_mouseDown)
        self.text1.Bind(wx.EVT_MOTION, self.on_mouseMove)

        self.btn = wx.Button(panel, -1, "btn", (5, 40))
        self.btn.Bind(wx.EVT_LEFT_DOWN, self.on_mouseDown)
        self.btn.Bind(wx.EVT_MOTION, self.on_mouseMove)

    def on_mouseDown(self, event):
        print "mouseDown", printobj(event), event.GetPosition()
        # it is okay to call Skip on Windows, but if you do it
        # on the Mac you won't get any mouse move (drag) events
        #event.Skip()

    def on_mouseMove(self, event):
        print "mouseMove", printobj(event), event.GetPosition()
        event.Skip()


class MyApp(wx.App):

    def OnInit(self):
        #frame = wx.Frame(None, -1, "minimal", size=(200, 200))
        frame = MyFrame(None, -1, "minimal", size=(200, 200))
        self.frame = frame
        
        frame.Show(1)
        self.SetTopWindow(frame)
        return True


app = MyApp(0)
app.MainLoop()

 	  	 
