#! /usr/local/bin/python

# Python imports...
import random
import sys
import time

# Common 3rd-party imports...
import wx

# Toolbox imports...


# Constants

# If you set this to true, we'll do a delay in the timer (after telling the
# timer to restart!)
_kDelayInTimer = False

# If you set this to true, we'll do a delay in paint...
_kDelayInPaint = True

# If you set this to true, then 1 time out of 100 we won't delay...
_kRandomlyDontDelay = False


##############################################################################
class PsychoWindow(wx.PyControl):
    """A window that constantly changes colors.
    
    ...it also will randomly delay a bit to try to keep any idle events from
    happening...
    """

    ###########################################################
    def __init__(self, parent):
        """The initializer for PsychoWindow. 
                
        @param  parent       The parent Window.
        """
        # Call the base class initializer
        super(PsychoWindow, self).__init__(parent)
        self.SetBackgroundColour((0, 0, 0))
        
        self._colorTimer = wx.Timer(self, -1)
        self.Bind(wx.EVT_TIMER, self.OnColorTimer, self._colorTimer)
        self._colorTimer.Start(1, True)
        
        self.Bind(wx.EVT_PAINT, self.OnPaint)


    ###########################################################
    def OnColorTimer(self, event):
        """Handle our timer event to change colors.
        
        @param  event  The timer event.
        """
        r, g, b = self.GetBackgroundColour()
        r = (r + random.randint(-8, 8) + 256) % 256
        g = (g + random.randint(-8, 8) + 256) % 256
        b = (b + random.randint(-8, 8) + 256) % 256
        
        self.SetBackgroundColour((r, g, b))
        self.Refresh()
        
        self._colorTimer.Start(1, True)
        
        if _kDelayInTimer:
            self._delay()


    ###########################################################
    def OnPaint(self, event):
        """Handle our paint event.
        
        @param  event  The paint event.
        """
        #print list(wx.GetTopLevelWindows())
        dc = wx.PaintDC(self)
        dc.SetBackground(wx.Brush(self.GetBackgroundColour()))
        dc.Clear()
        
        if _kDelayInPaint:
            self._delay()


    ###########################################################
    def _delay(self):
        """Eat up some CPU time, delaying 10ms.
        
        ...if _kRandomlyDontDelay is defined, sometimes we won't delay.
        """
        if _kRandomlyDontDelay:
            if random.randint(0, 100) > 99:
                print "No delay, returning"
                return
        
        startTime = time.time()
        while (time.time() - startTime) < .1:
            pass


##############################################################################
class Dialog2(wx.Dialog):
    """A dumb dialog that has some text and an OK button.
    
    It also has some printouts on various events...
    """
    def __init__(self, parent):
        super(Dialog2, self).__init__(parent, title="Dialog 2")
        
        buttonSizer = self.CreateStdDialogButtonSizer(wx.OK)
        text = wx.StaticText(self, -1, "Text for dialog 2")
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(text, 0, wx.EXPAND)
        sizer.Add(buttonSizer, 1, wx.EXPAND)
        self.SetSizer(sizer)
        
        self.FindWindowById(wx.ID_OK).Bind(wx.EVT_BUTTON, self.OnOK)

    def __del__(self):
        print "Dialog 2 deleted"

    def OnOK(self, event):
        print "OnOK in dialog 2, ending modal"
        self.EndModal(wx.ID_OK)
        print "OnOK in dialog 2 done"


##############################################################################
class Dialog1(wx.Dialog):
    """A dumb dialog that has a button to launch Dialog 2 and an OK button.
    
    It also has some printouts on various events...
    """
    def __init__(self, parent):
        super(Dialog1, self).__init__(parent, title="Dialog 1")
        
        button = wx.Button(self, -1, "Button 1")
        buttonSizer = self.CreateStdDialogButtonSizer(wx.OK)
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(button, 0, wx.EXPAND)
        sizer.Add(buttonSizer, 1, wx.EXPAND)
        self.SetSizer(sizer)
        
        button.Bind(wx.EVT_BUTTON, self.OnButton1)
        self.FindWindowById(wx.ID_OK).Bind(wx.EVT_BUTTON, self.OnOK)

    def __del__(self):
        print "Dialog 1 deleted"

    def OnOK(self, event):
        print "OnOK in dialog 1, ending modal"
        self.EndModal(wx.ID_OK)
        print "OnOK in dialog 1 done"

    def OnButton1(self, event):
        dlg = Dialog2(self)
        print "Showing dialog 2"
        dlg.ShowModal()
        print "Done showing dialog 2"
        dlg.Destroy()
        print "Destroy done for dialog 2"
        #wx.GetApp().SendIdleEvents()


##############################################################################
def test_main():
    """Contains various self-test code."""
    app = wx.PySimpleApp(redirect=False)
    
    frame = wx.Frame(None)
    win = PsychoWindow(frame)
    
    def onLeft(event):
        dlg = Dialog1(frame)
        print "Showing dialog 1"
        dlg.ShowModal()
        print "Done showing dialog 1"
        dlg.Destroy()
        print "Destroy done for dialog 1"
    win.Bind(wx.EVT_LEFT_DOWN, onLeft)
    
    def onIdle(event):
        print "Idle"
        event.Skip()
    frame.Bind(wx.EVT_IDLE, onIdle)
    frame.Show()
    
    # Run the main loop, which will close when the frame does.
    app.MainLoop()


##############################################################################
if __name__ == '__main__':
    test_main()
