
import  wx

class TestPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)

        sampleList = ['one', 'two', 'three', 'four']

        self.lb = wx.CheckListBox(self, -1, wx.DefaultPosition, (200,200), sampleList)

        self.Bind(wx.EVT_CHECKLISTBOX, self.EvtCheckListBox, self.lb)

    def EvtCheckListBox(self, evt):
        print "The current selections are: "+str(self.lb.GetChecked())
        evt.Skip()



# start the app
app = wx.App()
frame = wx.Frame(None)
panel = TestPanel(frame)
frame.Show(True)     
print wx.version()
app.MainLoop()

