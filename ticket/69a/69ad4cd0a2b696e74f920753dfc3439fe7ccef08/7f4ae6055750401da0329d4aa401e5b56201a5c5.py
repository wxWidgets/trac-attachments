import wx

#----------------------------------------------------------------------

class TestPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.ID_ANY)
        
        self.box = wx.BoxSizer(wx.VERTICAL)
        
        self.btn = wx.Button(self, wx.ID_ANY, "Created Before StaticBox")
        
        lb = wx.StaticBox(self, wx.ID_ANY, "wx.StaticBox")
        lbs = wx.StaticBoxSizer(lb, wx.VERTICAL)

        self.btn2 = wx.Button(self, wx.ID_ANY, "Created After StaticBox")
        
        self.Bind(wx.EVT_BUTTON, self.on_btn1, self.btn)
        self.Bind(wx.EVT_BUTTON, self.on_btn2, self.btn2)
            
        lbs.Add(self.btn)
        lbs.Add(self.btn2)
        self.box.Add(lbs)
        
        self.SetSizer(self.box)
    
    
    def on_btn1(self, event):
        print "This event doesn't occur in wxMac"
    
    
    def on_btn2(self, event):
        print "This event will occur in wxMac"


#----------------------------------------------------------------------

if __name__ == '__main__':
    import sys
    app = wx.PySimpleApp()
    frame = wx.Frame(None, wx.ID_ANY, "title")
    TestPanel(frame)
    frame.Show(True)
    app.MainLoop()
 	  	 
