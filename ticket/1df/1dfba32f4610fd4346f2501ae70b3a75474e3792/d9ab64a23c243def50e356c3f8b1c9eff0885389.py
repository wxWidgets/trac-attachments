import wx
try:
    from ctypes import *
    from Carbon import Windows
    carbonLoc = '/System/Library/Carbon.framework/Carbon'
    carbon = CDLL(carbonLoc)  
    OnMac = True
except :
    OnMac =False
    
class App(wx.PySimpleApp):
    def OnInit(self):
        if OnMac:
            # - - - - - - Frame 1
            frame1 = wx.Frame(None , -1, "This window is in a group", (200,150), (300,100) )
            
            self.WindowGroup = c_void_p()           
            print "Create window group result is ", carbon.CreateWindowGroup( 0, byref(self.WindowGroup) )
            print "Add to windowgroup result is ", carbon.SetWindowGroup( frame1.MacGetTopLevelWindowRef(), self.WindowGroup )
            
            self.caretDemo(frame1, "Please move this window with the mouse. Observe that the blinking insertion point caret remains stationary relative to the screen.") 
            
            # - - - - - - Frame 2
            frame2 = wx.Frame(None , -1, "This window is not in a group", (200,300), (300,100) )    
            self.caretDemo(frame2,"Please move this window with the mouse. Observe that the blinking insertion point caret remains stationary relative to this window.")
            
        else:
            frame1 = wx.Frame(None , -1, "We don't appear to be on a Mac", (200,150), (300,100) )
            wx.StaticText(frame1, -1, label= "This test is for OS X, so there's no point in running it on another OS.", style = 0 )
            frame1.Show()
        return True
    
    def caretDemo( self, parent, aLabel ):
        """ The demo works the same way regardless of which control you Set the caret in -
            I have set it in the frame here because the frame is what is explicitly assigned
            to the Window Group. But you can Set the caret in any child control or window  
            of the frame, and it will exhibit the same behavior.
        """
        aControl = wx.StaticText(parent, label = aLabel )
        parent.Show()
        CaretTarget = parent
        CaretTarget.SetCaret(wx.Caret(CaretTarget, (2, 20)))            
        CaretTarget.GetCaret().Move((50, 30))
        CaretTarget.GetCaret().Show()
        
#---------------------------------------------------------------------------
def run():
    app = App()
    app.MainLoop()

if __name__ == '__main__':
    run()
