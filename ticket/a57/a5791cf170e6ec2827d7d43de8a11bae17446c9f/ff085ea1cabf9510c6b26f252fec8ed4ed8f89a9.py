import wx
 
class TestFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, "Test", size=(400,300))
	p = wx.Panel(self)

        happyButton = wx.Button(p, -1, "!", size=(300,300), pos = (1000000, 1000000))

        sadButton = wx.Button(p, -1, "!", size=(300,300))
	sadButton.SetPosition((1000000,1000000))

        deprivedButton = wx.Button(p, -1, "!", size=(300,300), pos = (1000000, 1000000))
	deprivedButton.SetPosition((1000000,1000000))

 	wx.MessageBox("happyButton's position:\t" + str(happyButton.GetPosition()) + "\nsadButton's position:\t"+ str(sadButton.GetPosition()) + "\ndeprivedButton's position:\t" + str(deprivedButton.GetPosition()))

app = wx.PySimpleApp()
frame = TestFrame(None)
frame.Show(True)
app.MainLoop()

 	  	 
