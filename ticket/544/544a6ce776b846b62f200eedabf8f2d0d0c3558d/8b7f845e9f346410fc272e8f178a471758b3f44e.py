import wx

def main():
    # Create a simple test app to see how things worked!
    app = wx.PySimpleApp(redirect=bool("__WXMAC__" not in wx.PlatformInfo))
    frame = wx.Frame(None, -1, "macVertScrollBugt", size=(200,200))
    
    # Creating this, or a horizontal scrollbar, fixes graphics glitch.
    #frame.CreateStatusBar()
    
    # Create the scrolled window.
    scrolledWindow = wx.ScrolledWindow(frame, -1)
    scrolledWindow.SetScrollRate(2, 2)
    
    # Create our sizer, and the first 20 static texts...
    sizer = wx.BoxSizer(wx.VERTICAL)
    scrolledWindow.SetSizer(sizer)
    for i in xrange(0, 20):
        text = wx.StaticText(scrolledWindow, -1, "--- %d ---" % i)
        sizer.Add(text)
    
    # Go!
    frame.Show(1)
    app.MainLoop()

if __name__ == '__main__':
    main()

 	  	 
