import wx

class MainFrame (wx.Frame):

    def __init__ (self):
        wx.Frame.__init__(self, None)
        splitter = wx.SplitterWindow(self)
        panel    = wx.Panel(splitter)
        button   = wx.Button(splitter)

app   = wx.App()
frame = MainFrame()
frame.Show(True)
app.MainLoop()
   

 	  	 
