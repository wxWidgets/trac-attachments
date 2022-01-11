from wxPython import wx
import string

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(wx.NULL, -1, "crash password field", size=(200, 200))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        self.frame = frame
        
        frame.Show(1)
        self.SetTopWindow(frame)

        self.btn = wx.wxButton(panel, -1, "Toggle", name='btn')
        wx.EVT_BUTTON(panel, self.btn.GetId(), self.OnMouseClick)

        self.text1 = wx.wxTextCtrl(panel, -1, pos=(0, 30), style=wx.wxTE_PASSWORD)


        return 1

    def OnMouseClick(self, evt):
        print "mouseClick:", evt.GetEventObject().GetName()
        self.text1.Show(not self.text1.IsShown())


app = MyApp(0)
app.MainLoop()



 	  	 
