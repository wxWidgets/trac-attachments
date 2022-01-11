
"""
A WX cross-platform method to capture any arbitrary portion 
of the Desktop screen.

ON MSW PLATFORMs THE EXTENDED PORTION OF THE DESKTOP IS NOT INCLUDED.

Ray Pasco
pascor(at)verizon(dot)net
2011-04-20-Wed__PM-04-52-36__April

Adapted from "How to Take a Screenshot of Your wxPython App and Print it" @
http://www.blog.pythonlibrary.org/2010/04/16/how-to-take-a-screenshot-of-your-wxpython-app-and-print-it/

Revision History :

2011-06-10
    Added option to create error text message bitmap when the given bmapSize
      is illegal. Associated flag arg [ errorMsgBmap=True ].
    Added a simple main test app.
    
2011-04-20
    Using wx.Bitmap.IsOk() as the validity check for the call to wx.ScreenDC.GetAsBitmap().

Platform  Linux
Python    2.6.6 (r266:84292, Sep 15 2010, 15:52:39) 
[GCC 4.4.5]
Wx Version 2.8.11.0
Wx Platform ('__WXGTK__', 'wxGTK', 'unicode', 'gtk2', 'wx-assertions-off', 'SWIG-1.3.29')

2011-04-18  Debug Rev v1.2.1
    Added statements specifically for debugging. Enable by calling with "(... , debug=True)"

2011-04-15  Rev 1.2  RDP:
    screenDC.GetAsBitmap() isn't implemented on MSW :(  Reversion to original Desktop bitmap 
    aquisition code only if scrDC.GetAsBitmap() isn't implemented. 

2011-03-25  Rev. 1.1   OS-X 10.6 tested:
Adapted for Mac by:
Chris Barker
Chris.Barker (at) noaa (dot) gov

Wx Version 2.8.11.0
Wx Pltform ('__WXMAC__', 'wxMac', 'unicode', 'wx-assertions-on', 'SWIG-1.3.29', 'mac-cg', 'mac-native-tb')


2011-03-25  Rev. 1.0    MS Win7 tested.
Ray Pasco
pascor(at)verizon(dot)net

Windows   6.1.7600
Python    2.6.5 (r265:79096, Mar 19 2010, 21:48:26) [MSC v.1500 32 bit (Intel)]
Wx Version 2.8.11.0
Wx Pltform ('__WXMSW__', 'wxMSW', 'unicode', 'wx-assertions-on', 'SWIG-1.3.29')

"""
import sys
import wx

#------------------------------------------------------------------------------

def ScreenCapture( startPos, bmapSize, 
                   errorMsgBmap=True, debug=False ) :
    """
    General Desktop screen portion capture - partial or entire Desktop.
    
    My particular screen hardware configuration: 
        wx.Display( 0 ) refers to the extended Desktop display monitor screen.
        wx.Display( 1 ) refers to the primary  Desktop display monitor screen.
    
    Any particular Desktop screen size is :
        screenRect = wx.Display( n ).GetGeometry()
        
    Different wx.Display's in a single system may have different dimensions.        
    """

    # Create an app if one hasn't been created yet.
    if not wx.GetApp() :
        dummyApp = wx.App( redirect=False )
    #end try
    
    #-----
    
    # A wx.ScreenDC provides access to the entire PRIMARY SCREEN, ONLY 
    #   portion of the Desktop. Any exteded Desktop creen portions are excluded.
    # This includes any extended Desktop monitor screens that are enabled in the OS.
    scrDC     = wx.ScreenDC()
    scrDcSize = scrDC.Size
    scrDcSizeX, scrDcSizeY = scrDcSize
    
    if debug :
        print 'DEBUG:  scrDcSize ', scrDcSize
    
    # Cross-platform adaptations :
    scrDcBmap   = scrDC.GetAsBitmap()
    scrBmapSize = scrDcBmap.GetSize()
    
    # Check if scrDC.GetAsBitmap() method has been implemented on this platform.
    if scrDcBmap.IsOk() :   # Not implemented :  Get the screen bitmap the long way.
        
        if debug :
            print 'DEBUG:  Using scrDC.GetAsBitmap()'
            
        # This platform has scrDC.GetAsBitmap() implemented.
        scrDcBmap = scrDC.GetAsBitmap()     # So easy !  The main Desktop bitmap.
        
    else :
        
        if debug :
            print 'DEBUG:  Using memDC.Blit() since scrDC.GetAsBitmap() is nonfunctional.\n'
            
        # Create a new empty (black) destination bitmap the size of the scrDC. 
        # Overwrire the invalid original "scrDcBmap".
        scrDcSizeX, scrDcSizeY = scrDcSize
        scrDcBmap = wx.EmptyBitmap( *scrDcSize )
        
        # Create a DC tool that is associated with scrDcBmap.
        memDC = wx.MemoryDC( scrDcBmap )
        
        # Copy (blit, "Block Level Transfer") a portion of the screen bitmap 
        #   into the returned capture bitmap.
        # The bitmap associated with memDC (scrDcBmap) is the blit destination.
        
        memDC.Blit( 0, 0,                       # Copy to this start coordinate.
                    scrDcSizeX, scrDcSizeY, # Copy an area this size.
                    scrDC,                      # Copy from this DC's bitmap.
                    0, 0,                    )  # Copy from this start coordinate.

        memDC.SelectObject( wx.NullBitmap )     # Finish using this wx.MemoryDC.
                                                # Release scrDcBmap for other uses.        
    #end if
    
    #-----
    
    try :
        grabBmap = scrDcBmap.GetSubBitmap( wx.RectPS( startPos, bmapSize ) )
        
    except :    # Given bmapSize tuple arg is illegal
        
        grabBmap = None
        errMsg = 'ScreenCapture:  Invalid Param:  %s  or  %s'  \
                 % ('startPos='+repr(startPos), 'bmapSize'+repr(bmapSize))
                 
        print errMsg
        
    #end try
    
    return grabBmap
        
#end ScreenCapture def

#------------------------------------------------------------------------------

if __name__ == '__main__' :
    
    dummyApp = wx.App( redirect=False )
    
    ########################################################
    # NOTE: My extended monitor is ditely above the promary.
    #       It's resolution is the same as the primary's.
    #       Change the following coordinates and screen sizes for your setup.
    ########################################################
    originList  = [ (0, 0), (0, 800), (0, -800), (0, 1600), (0, -1600) ]
    
    scrSizeX, scrSizeY = wx.GetDisplaySize()
    winSizeList = [ (scrSizeX, scrSizeY), (scrSizeX, 2*scrSizeY) ]
    
    for origin in originList :

        for winSize in winSizeList :

            shotBmap = ScreenCapture( origin, winSize )

            if shotBmap :

                yOrd = origin[1]
                yOrdStr = '+' + str( yOrd )
                if yOrd < 0 :
                    yOrdStr = '.-' + str( yOrd )
                
                ySize = winSize[1]
                ySizeStr = '+' + str( ySize )
                if ySize < 0 :
                    ySizeStr = '.-' + str( ySize )
                
                
                filename = 'ScreenShotWX_TRAC' + ySizeStr + yOrdStr + '.png'
                print '----  Writing file [ %s ]' % (filename)
                print '        for Size = %s  and  Origin = %s'  \
                      % (repr(winSize), repr(origin))

                shotBmap.SaveFile( filename, wx.BITMAP_TYPE_PNG )
                
            #end if
        
        #end for
        
    #end for
    
#end if __name__
