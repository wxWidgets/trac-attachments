#!/usr/bin/env python

import wx

class FixedPyScrolledWindow(wx.PyScrolledWindow):
    """A scrolled window that has a way to set the best size properly."""
    def __init__(self, *args, **kwargs):
        wx.PyScrolledWindow.__init__(self, *args, **kwargs)
        self._bestSize = (-1, -1)
    
    ############################################################
    def SetBestSizeProperly(self, bestSize):
        """A proper implementation of SetBestSize()
        
        Unlike the one in wx.PyScrolledWindow, this one doesn't set the
        minimum size.
        
        @param  bestSize  The best size to use.
        """
        self._bestSize = bestSize
    
    ############################################################
    def DoGetBestSize(self):
        """Implement DoGetBestSize() to properly apply our bestSize.
        
        This is called automatically when someone wants to know our best size.
        We'll return the value that was passed into us, using our superclass
        result whenever we have a -1.
        
        @return bestSize  The actual best size.
        """
        bestWidth, bestHeight = self._bestSize
        if bestWidth != -1 and bestWidth != -1:
            return self._bestSize
        
        superBestWidth, superBestHeight = wx.PyScrolledWindow.DoGetBestSize(self)
        if bestWidth == -1:
            bestWidth = superBestWidth
        if bestHeight == -1:
            bestHeight = superBestHeight
        
        return (bestWidth, bestHeight)


##############################################################################
class Test1Dialog(wx.Dialog):
    """The point of this dialog is for you to read the code.
    
    You can read the code to help you understand what's going on, then run the
    dialog to play with it.
    """
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, -1,
                           style=wx.DEFAULT_DIALOG_STYLE | 
                                 wx.RESIZE_BORDER        |
                                 wx.MAXIMIZE_BOX               )
        # At this point:
        # - Our size is the "default" size, and will stay that way until we
        #   call SetSize() or Fit().  This is (400, 250) in my debugger.
        # - Our client size is slightly smaller--take the title bar out.  On
        #   my machine, that's (400, 228).
        # - Our minSize is (-1, -1)
        # - Calling GetBestSize() is a bad idea right now.
        #   Why?  Doing so will _set_ your minSize to the current size, which
        #   is very confusing (getter functions should never change your state!)
        #       DEBUGGER WARNING: this means stepping through code before
        #       you've got a child or a sizer will change its behavior, since
        #       "BestSize" is a property.  Yuck!
        #
        # TODO: What if we passed in a size to the constructor?  I assume that
        # doesn't tweak the min size?
        
        ms = self.GetMinSize()
        sizer = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(sizer)
        
        # It's now safe to debug, since we've got a sizer set.  Whew!  Now:
        # - bestSize just includes title bar.  (0, 22)
        # - sizer's size and min size are (0, 0)
        # - effectiveMinSize, as everywhere in this example, will match
        #   bestSize.  That's because our minSize is (-1, -1).
        
        sizer.Add(wx.StaticText(self, -1, "First, a wx.PyScrolledWindow with stuff:"))
        
        # We've got one object.  Now:
        # - sizer's minSize is enough to hold the text: (250, 16)
        # - bestSize is is updated to account for the minSize of the sizer
        #   (250, 38)
        
        
        # We'll create a scrolled window with some objects in it...
        sw = FixedPyScrolledWindow(self, -1)
        self._sw = sw
        swSizer = wx.BoxSizer(wx.VERTICAL)
        sw.SetSizer(swSizer)
        
        swSizer.Add(wx.StaticText(sw, -1, "This is the first thing in the scrolled window"))
        swButton1 = wx.Button(sw, -1, "An expanding button")
        swButton1.Bind(wx.EVT_BUTTON, self.OnSwButton)
        swSizer.Add(swButton1, 0, wx.EXPAND)
        swButton2 = wx.Button(sw, -1, "Another button")
        swButton2.Bind(wx.EVT_BUTTON, self.OnSwButton)
        swSizer.Add(swButton2, 0)
        swRedWin = wx.Window(sw)
        swRedWin.SetBackgroundColour("red")
        swSizer.Add(swRedWin, 1, wx.EXPAND)
        swSizer.Add(wx.StaticText(sw, -1, "The above window has prop=1"))
        swSizer.Add(wx.StaticText(sw, -1, "This is the last thing in the scrolled window"))
        
        
        # OK, when we get here, the scrolled window will have some properties:
        # - size: (0, 0)
        # - minSize: (-1, -1)
        # - bestSize: (293, 103)      -- thus effectiveMinSize is (293, 103)
        #   BUG: this appears to be wrong.  Since no scrollbars are showing,
        #        this really should be the same as bestVirtualSize.
        # - virtualSize: (-1, -1)
        # - bestVirtualSize: (278, 88)
        # - swSizer.minSize: (278, 88)
        
        sw.SetScrollRate(1, 1)
        
        
        # What a change after the above line, which enables scrolling in both
        # the horizontal and vertical directions.  Now sw will have:
        # - bestSize: (0, 0)          -- thus effectiveMinSize is (0, 0)
        # - virtualSize: (278, 88)
        # - bestVirtualSize: (278, 88)
        #
        # - SetVirtualSize - no effect here (tried (400, 400), (0, 0), (-1, -1)).
        
        sw.SetSize((400, 400))
        
        # Now, sw will have:
        # - size: (400, 400)
        # - bestSize: (400, 400)      -- thus effectiveMinSize is (400, 400)
        # - virtualSize: (400, 400)
        # - bestVirtualSize: (400, 400)
        #
        # - SetVirtualSize((401, 401)): changes things like this (as does anything greater than (400, 400))
        #   - virtualSize: (400, 385)
        #   - bestVirtualSize: (400, 385)
        # - SetVirtualSize((300, 300)): changes things back:
        #   - virtualSize: (400, 400)
        #   - bestVirtualSize: (400, 400)
        # ...it's like it's somehow deciding on scrollbars (?)
        
        sw.SetSize((0, 0))
        
        sizer.Add(sw, 1, wx.EXPAND)
        
        # Note, the above call didn't do _anything_ around sizes, since
        # the scrolled window has a effectiveMinSize of (0, 0)
        
        # Let's make the scrolled window behave the way it seems like it
        # should have behaved all along.  This will give us a starting size
        # that contains all of our children, but will still allow us to
        # shrink to get smaller.
        # NOTE: SetBestSize() does the wrong thing--it's just an alias for
        #       SetInitialSize() which is just SetSize() + SetMinSize()
        theRightSize = sw.GetSizer().GetMinSize()
        sw.SetBestSizeProperly(theRightSize)
        
        # Make sure that the scrollbars go away...
        sw.SetClientSize(theRightSize)
        sw.SetSize(theRightSize)
        
        
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog2"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog3"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog4"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog5"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog6"))
        
        buttonSizer = wx.StdDialogButtonSizer()
        sizer.Add(buttonSizer, 0,
                  wx.EXPAND | wx.TOP | wx.BOTTOM, 5)
        
        okButton = wx.Button(self, wx.ID_OK, "")
        okButton.Bind(wx.EVT_BUTTON, self.OnButton)
        buttonSizer.AddButton(okButton)
        
        cancelButton = wx.Button(self, wx.ID_CANCEL, "")
        cancelButton.Bind(wx.EVT_BUTTON, self.OnButton)
        buttonSizer.AddButton(cancelButton)
        
        buttonSizer.Realize()
        
        self.Fit()
        
        # The above changes a whole lot:
        # - self.clientSize: (250, 98)  - comes from sizer.minSize
        # - self.bestSize: (250, 120)   - comes from clientSize + title bar
        # - self.size: (250, 120)       - came from bestSize at end of fit
        # - self.effectiveMinSize: (250, 120)
        # - self.bestVirtualSize: (250, 120) - doesn't make sense (BUG?)
        #
        # - sizer.minSize: (250, 98) - came from minSize of child sizers and
        #                              effectiveMinSize of child windows.
        #
        # - sw.size: (250, 0) - 250 came from wx.EXPAND of box sizer (we had
        #                       no constraints ourselves, so we expand to the
        #                       width of everyone else).  0 because that's
        #                       what our effectiveMinSize said.
        # - sw.bestSize: (250, 0) - for a scrolledWindow with scrolling
        #                           enabled, bestSize = size
        # - sw.virtualSize: (278, 88)
        # - sw.bestVirtualSize: (278, 88)
        # - swSizer.minSize: (278, 88)
        self.CenterOnParent()


    def OnSwButton(self, event):
        event.Skip()
        #button = event.GetEventObject()
        #sw = self._sw
        #sizer = self.GetSizer()
        #print "SWButton"
        
    def OnButton(self, event):
        button = event.GetEventObject()
        self.EndModal(button.GetId())


##############################################################################
class Test2Dialog(wx.Dialog):
    """This dialog is to show how PyScrolledWindow's SetBestSize is broken.
    
    This is very similar to Test1, but without the comments / extra playing
    around code--just straight to the poit of showing how SetBestSize() is
    weird.
    """
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, -1,
                           style=wx.DEFAULT_DIALOG_STYLE | 
                                 wx.RESIZE_BORDER        |
                                 wx.MAXIMIZE_BOX               )
        sizer = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(sizer)
        
        sizer.Add(wx.StaticText(self, -1, "First, a wx.PyScrolledWindow with stuff:"))
        
        # We'll create a scrolled window with some objects in it...
        sw = wx.PyScrolledWindow(self, -1)
        swSizer = wx.BoxSizer(wx.VERTICAL)
        sw.SetSizer(swSizer)
        
        swSizer.Add(wx.StaticText(sw, -1, "This is the first thing in the scrolled window"))
        swButton1 = wx.Button(sw, -1, "An expanding button")
        swSizer.Add(swButton1, 0, wx.EXPAND)
        swButton2 = wx.Button(sw, -1, "Another button")
        swSizer.Add(swButton2, 0)
        swRedWin = wx.Window(sw)
        swRedWin.SetBackgroundColour("red")
        swSizer.Add(swRedWin, 1, wx.EXPAND)
        swSizer.Add(wx.StaticText(sw, -1, "The above window has prop=1"))
        swSizer.Add(wx.StaticText(sw, -1, "This is the last thing in the scrolled window"))
        
        sw.SetScrollRate(1, 1)
        
        sizer.Add(sw, 1, wx.EXPAND)
        
        # Get the minSize before calling SetBestSize()
        oldMinSize = sw.GetMinSize()
        theRightSize = sw.GetSizer().GetMinSize()
        sw.SetBestSize(theRightSize)
        newMinSize = sw.GetMinSize()
        
        if tuple(oldMinSize) != tuple(newMinSize):
            wx.MessageBox("Min size changed!\n"
                          "That seems wrong...\n"
                          "That means you can't shrink scrolled window on Mac.")
        
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog2"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog3"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog4"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog5"))
        sizer.Add(wx.StaticText(self, -1, "Just more text in the dialog6"))
        
        buttonSizer = wx.StdDialogButtonSizer()
        sizer.Add(buttonSizer, 0,
                  wx.EXPAND | wx.TOP | wx.BOTTOM, 5)
        
        okButton = wx.Button(self, wx.ID_OK, "")
        okButton.Bind(wx.EVT_BUTTON, self.OnButton)
        buttonSizer.AddButton(okButton)
        
        cancelButton = wx.Button(self, wx.ID_CANCEL, "")
        cancelButton.Bind(wx.EVT_BUTTON, self.OnButton)
        buttonSizer.AddButton(cancelButton)
        
        buttonSizer.Realize()
        
        self.Fit()
        
        self.CenterOnParent()


    def OnButton(self, event):
        button = event.GetEventObject()
        self.EndModal(button.GetId())


##############################################################################
class MainFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1)
        
        sizer = wx.BoxSizer(wx.VERTICAL)
        
        sizer.Add(wx.StaticText(self, -1, "Choose a test:"), 0, wx.ALL, 10)
        
        sizer.Add(wx.StaticText(self, -1, "Test1--read the comments:"), 0, wx.ALL, 10)
        test1Button = wx.Button(self, -1, "Test1")
        test1Button.Bind(wx.EVT_BUTTON, self.OnTest1)
        sizer.Add(test1Button, 0, wx.ALL, 10)
        
        sizer.Add(wx.StaticText(self, -1, "Test2--show BestSize issue:"), 0, wx.ALL, 10)
        test2Button = wx.Button(self, -1, "Test2")
        test2Button.Bind(wx.EVT_BUTTON, self.OnTest2)
        sizer.Add(test2Button, 0, wx.ALL, 10)
        
        self.SetSizer(sizer)
        self.Fit()
        self.CenterOnParent()
        self.Show()


    def OnTest1(self, event):
        dialog = Test1Dialog(self)
        dialog.ShowModal()
        dialog.Destroy()


    def OnTest2(self, event):
        dialog = Test2Dialog(self)
        dialog.ShowModal()
        dialog.Destroy()



##############################################################################
def main():
    app = wx.PySimpleApp()
    frame = MainFrame()
    app.MainLoop()



##############################################################################
if __name__ == '__main__':
    main()


 	  	 
