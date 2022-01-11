import wx

def ShowDialog():
        
        dialog = wx.Dialog(None, -1, "Connection", size=(200, 240))
        dialog.SetBackgroundColour(wx.Colour(0,51,52)) #some sort of green
        dialog.SetForegroundColour(wx.Colour(255,255,255)) #white text
        
        text = wx.StaticText(dialog, -1, "Connect to:", (10, 10))
        configList = wx.ListBox(dialog, -1, (30, 30), (140, 120))
        configList.SetSelection(0)
        okBtn = wx.Button(dialog, wx.ID_OK, "Connect", (10, 204))
        cancelBtn = wx.Button(dialog, wx.ID_CANCEL, "Quit", (110, 204))

        if dialog.ShowModal() == wx.ID_OK:
            dialog.Destroy()
        else:
            dialog.Destroy()


class MyApp(wx.App):
	def __init__(self):
		wx.App.__init__(self)

	def OnInit(self):
		ShowDialog()
		return True
		
	

def main(argv):
    app = MyApp()    
    app.MainLoop()


if __name__ == '__main__':
    import sys, os
    main(['', os.path.basename(sys.argv[0])] + sys.argv[1:])

 	  	 
