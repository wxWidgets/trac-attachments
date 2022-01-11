
import sys
from wxPython import wx

print "Python", sys.version
print "wxPython", wx.__version__

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(wx.NULL, -1, "wxTE_RICH2 2.4.1.2 SetValue bug", size=(450, 350))
        panel = wx.wxPanel(frame, -1)

        txt = "The quick brown fox jumped over the lazy dog."
        
        borderStyle = 0 # wx.wxNO_BORDER
        
        # THIS BUG APPEARS TO BE LIMITED TO THE wxTE_RICH2 style
        richText = wx.wxTE_RICH2

        clipStyle = wx.wxCLIP_SIBLINGS
        multilineStyle = richText | \
                         wx.wxTE_PROCESS_TAB | \
                         wx.wxTE_MULTILINE | \
                         borderStyle | \
                         clipStyle | \
                         wx.wxNO_FULL_REPAINT_ON_RESIZE

        self.notes = wx.wxTextCtrl(panel, -1, '', (7,64), (278, 200), style=multilineStyle)
        self.notes.Show(False)
        print "self.notes.IsShown()", self.notes.IsShown()

        self.toggleNotes = wx.wxButton(panel, -1, 'Toggle Notes', (100, 0))
        wx.EVT_BUTTON(panel, self.toggleNotes.GetId(), self.OnToggle)

        self.street = wx.wxTextCtrl(panel, -1, '', (100,72), (183, -1), style=clipStyle)
        self.city = wx.wxTextCtrl(panel, -1, '', (100,94), (250, -1), style=clipStyle)
        #self.city.Show(False)

        wx.wxStaticText(panel, -1, 'Street', (8,79), (68, -1), \
            style = wx.wxALIGN_RIGHT | wx.wxST_NO_AUTORESIZE | wx.wxCLIP_SIBLINGS)

        wx.wxStaticText(panel, -1, 'City', (8,101), (68, -1), \
            style = wx.wxALIGN_RIGHT | wx.wxST_NO_AUTORESIZE | wx.wxCLIP_SIBLINGS)

        self.notes.SetValue(txt)
        self.city.SetValue(txt)
        
        frame.Show(1)
        self.SetTopWindow(frame)

        return 1

    def OnToggle(self, evt):
        self.notes.Show(not self.notes.IsShown())


app = MyApp(0)
app.MainLoop()

 	  	 
