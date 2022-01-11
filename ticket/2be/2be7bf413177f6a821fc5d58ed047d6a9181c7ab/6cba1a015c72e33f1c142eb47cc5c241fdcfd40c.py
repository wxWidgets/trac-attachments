import wx                                                                                                                         
                                                                                                                                  
class MyFrame(wx.Frame):                                                                                                          
    def __init__(self, parent, id, title):                                                                                    
        wx.Frame.__init__(self, parent, id, title)                                                                        
                                                                                                                          
        self.SetMenuBar(self.createMenuBar())                                                                             
        self.Bind(wx.EVT_MENU_HIGHLIGHT, self.OnMenuHighlight)                                                            
                                                                                                                          
        self.SetStatusBar(self.createStatusBar())                                                                         
                                                                                                                              
    def createMenuBar(self):                                                                                                  
        menuBar = wx.MenuBar()                                                                                            
        menu = wx.Menu()                                                                                                  
        menu.Append(-1, "Stomp", "Stomp!")                                                                                
        menuBar.Append(menu, "Test")                                                                                      
        return menuBar                                                                                                    
                                                                                                                              
    def createStatusBar(self):                                                                                                
        statusBar = wx.StatusBar(self)                                                                                    
        statusBar.SetStatusText("This is my status text")                                                                 
        return statusBar                                                                                                  
                                                                                                                              
    def OnMenuHighlight(self, evt):                                                                                           
        print "Don't stomp on my statusbar"                                                                               
                                                                                                                                  
if __name__ == "__main__":                                                                                                        
    app = wx.PySimpleApp()                                                                                                    
    frame = MyFrame(None, -1, "Statusbar Stompage")                                                                           
    frame.Show()                                                                                                              
    app.MainLoop()                                                                                                            
