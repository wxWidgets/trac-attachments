#! /usr/local/bin/python

# Python imports...
import sys
import time

# Common 3rd-party imports...
import wx

# Toolbox imports...


# Constants
_kDefaultStartColor = (172, 0, 0)
_kDefaultEndColor = (235, 249, 253)


# We only see the bug if we use graphics context to draw...
kUseGc = True

# We can workaround the bug by blitting to a memory DC, then copying it over.
kUseWorkaround = False


##############################################################################
class GradientPanel(wx.Panel):
    """A panel with a linear gradient background."""

    ###########################################################
    def __init__(self, parent, id=wx.ID_ANY,
                 startColor=None, endColor=None,
                 pos=wx.DefaultPosition, size=wx.DefaultSize,
                 style=wx.TAB_TRAVERSAL | wx.BORDER_NONE |
                 wx.FULL_REPAINT_ON_RESIZE, name="panel"):
        """The initializer for GradientPanel. 
                
        @param  parent       The parent Window.
        @param  id           The ID
        @param  startColor   The start color; if None, will be auto-assigned.
        @param  endColor     The end color; if None, will be auto-assigned.
        @param  pos          UI pos.
        @param  size         UI size.
        @param  style        UI style.
        """
        # Call the base class initializer
        super(GradientPanel, self).__init__(parent, id, pos, size, style, name)
        
        # Tell the window that we have a custom background style.  This keeps
        # wx from erasing our background for us and avoids flicker.
        self.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
        
        # Avoid flicker when translucent children are drawn...
        self.SetDoubleBuffered(True)
        
        # Adjust params...
        if startColor is None: startColor = _kDefaultStartColor
        if endColor is None: endColor = _kDefaultEndColor
        
        # Save params...
        self._startColor = wx.Color(*startColor)
        self._endColor = wx.Color(*endColor)
        
        # Bind to paint events
        self.Bind(wx.EVT_PAINT, self.OnPaint)


    ###########################################################
    def OnPaint(self, event):
        """Draw ourselves...
        
        @param  event  The paint event.
        """
        if kUseGc:
            # If we are doing our workaround, we will point our GraphicsContext
            # at a MemoryDC and will blit to the PaintDC later.  Otherwise, we'll
            # point our GraphicsContext to the PaintDC directly.
            if kUseWorkaround:
                paintDc = wx.PaintDC(self)
                bitmap = wx.EmptyBitmapRGBA(*paintDc.GetSize())
                dc = wx.MemoryDC()
                dc.SelectObject(bitmap)
            else:
                dc = wx.PaintDC(self)
            
            gc = wx.GraphicsContext.Create(dc)
            
            width, height = self.GetClientSize()
            
            # Draw the rectangle with the gradient...
            gradientBrush = gc.CreateLinearGradientBrush(
                0, height, 0, 0, self._startColor, self._endColor
            )
            gc.SetPen(wx.TRANSPARENT_PEN)
            gc.SetBrush(gradientBrush)
            gc.DrawRectangle(0, 0, width, height)
            
            # Need to finish blitting if we used the workaround...
            if kUseWorkaround:
                dc.SelectObject(wx.NullBitmap)
                paintDc.DrawBitmap(bitmap, 0, 0, True)
        else:
            dc = wx.PaintDC(self)
            width, height = self.GetClientSize()
            dc.GradientFillLinear((0, 0, width, height), self._startColor,
                                  self._endColor, wx.NORTH)
            


##############################################################################
def test_main():
    """Contains various self-test code."""
    app = wx.PySimpleApp(redirect=False)
    
    frame = wx.Frame(None)
    panel = GradientPanel(frame)
    
    frame.Show()
    
    # Run the main loop, which will close when the frame does.
    app.MainLoop()


##############################################################################
if __name__ == '__main__':
    test_main()
