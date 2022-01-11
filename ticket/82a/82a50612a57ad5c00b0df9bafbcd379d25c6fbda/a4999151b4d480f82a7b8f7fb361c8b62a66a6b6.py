from wxPython import wx
import string

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(wx.NULL, -1, "drag test", size=(600, 200))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        self.frame = frame
        
        frame.Show(1)
        self.SetTopWindow(frame)
        #frame.Raise()

        self.static = wx.wxStaticText(panel, -1, 'hello world', (100, 5))

        self.btn = wx.wxButton(panel, -1, "set text", name='btn')
        wx.EVT_BUTTON(panel, self.btn.GetId(), self.OnMouseClick)

        frame.CreateStatusBar()
        frame.SetStatusText("jyqp")
        return 1

    def OnMouseClick(self, evt):
        print "mouseClick:", evt.GetEventObject().GetName()
        self.frame.SetStatusText(string.letters + " | / % $ # ` ' ")


app = MyApp(0)
app.MainLoop()



 	  	 
