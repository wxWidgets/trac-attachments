

"""
A WX cross-platform method to capture any arbitrary portion 
of the extended Desktop screen.

Ray Pasco
pascor(at)verizon(dot)net

Adapted from "How to Take a Screenshot of Your wxPython App and Print it" @
http://www.blog.pythonlibrary.org/2010/04/16/how-to-take-a-screenshot-of-your-wxpython-app-and-print-it/

Revision History :

2011-07-05
    Incorporated function CreateTextBmap. ScreenShotWX is now a single file.

2011-06-24
    Modifications for the access to an extended desktop (multiple screens). 
    This is hampered by the lack of built-in function which returns the size and 
    the origin of the entire  extended desktop.
    
    wx.ScreenDC.GetSize() improperly returns the size of only the primary 
    desktop screen, not the entire extended desktop. Functions GetScreenRects() and 
    GetDesktopRect() were added to provide this capability.

2011-06-10
    Added option to create error text message bitmap when the given bmapSize is illegal. 
    The associated flag arg is [ errorMsgBmap=True/False ].
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

def GetScreenRects() :
    """
    Find all individual Desktop screens. These consist of a mandatory primary screen
    whose origin is always (0, 0) and any number of extension screens whose origins are
    defined by their configured position relative to the primary screen.
    """
    
    # Create an app if one hasn't been created yet.
    if not wx.GetApp() :
        dummyApp = wx.App( redirect=False )
    #end try
    
    #-----
    
    # The primary screen's index is not necessarily 0.
    # [ scrList ] will always have the main screen be positioned first 
    #   in the list regardless of its index value. This is just for convenience.
    # Screen indices are contiguous starting at 0.
    scrList = list()
    for scrIndex in range( wx.Display().GetCount() ) :
        
        scrRect = wx.Display( scrIndex ).GetGeometry()              # a rect object to ...
        scrRect = (scrRect[0], scrRect[1], scrRect[2], scrRect[3])  # ... a 4-tuple
        scrOriginX, scrOriginY = (scrRect[0], scrRect[1])
        scrIsPrimary = (scrOriginX == 0)  and  (scrOriginY == 0)
        
        if scrIsPrimary :               # Make this to be the first element.
            scrList.insert( 0, scrRect ) 
        else :                          # Its order in the sequence is unimportant.
            scrList.append( scrRect )    
            
    #end for 
    
    return scrList
    
#end GetScreenRects def

#------------------------------------------------------------------------------

def GetDesktopRect() :
    """
    NOTE:   
        The upper-left coord of the primary desktop screen
        is always defined as (0, 0). The U-L coord
        of any extended screen may have negative ordinate values.
            
    The returned origin coordinate of the desktop rect is relative
    to the primary screen origin of (0, 0).
    """
    
    scrList = GetScreenRects()   # The will create a wx.App if there isn't one.
    
    # Initialize the screen sides' ordinates
    scrRect = scrList[0]
    left, top    = (scrRect[0], scrRect[1])
    sizeX, sizeY = (scrRect[2], scrRect[3])
    right  = left + sizeX
    bottom = top  + sizeY
    
    # Adjust the desktop boundary ordinates by each extended screen, if any.
    # Some resulting ordinates may be negative valued if any extended screen 
    #   is located above and/or to the left of the primary screen.
    
    numScreens = len( scrList )
    if numScreens >= 2 :
        
        for extRect in scrList[ 1:numScreens ] :
            
            extLeft,  extTop   = (extRect[0], extRect[1])
            extSizeX, extSizeY = (extRect[2], extRect[3]) # No use for this.
            extRight  = extLeft + extSizeX
            extBottom = extTop  + extSizeY
            
            left   = min( left, extLeft )
            top    = min( top,  extTop )
            
            right  = max( right, extRight )
            bottom = max( bottom, extBottom )
            
        #end for
        
    #end def
    
    # Left, right, top and bottom are now adjusted for any extended screens.
    desktopSizeX, desktopSizeY = (right - left, bottom - top)
    scrRect = wx.Rect(left, top, desktopSizeX, desktopSizeY)
    
    return scrRect
    
#end GetDesktopRect def

#------------------------------------------------------------------------------

def ScreenCapture( grabRect, errorMsgBmap=True, debug=False ) :
    """
    General desktop bitmap capture of any portion of the possibly extended desktop.
    
    Any particular Desktop screen size is :
        screenRect = wx.Display( n ).GetGeometry()
        
    Different wx.Display's in a single system may have different dimensions.        
    """
    
    # Create an app if one hasn't been created yet.
    if not wx.GetApp() :
        dummyApp = wx.App( redirect=False )
    #end try
    
    #-----
    
    scrList = GetScreenRects()   # The will create a wx.App if there isn't one.
    numScreens = len( scrList )
    if debug :
        print '----  numScreens    = ', numScreens
        print '----  scrList       = ', scrList
    #end if
    
    desktopRect = GetDesktopRect()
    
    desktopOriginX, desktopOriginY = desktopRect[ 0 ], desktopRect[ 1 ]
    desktopSizeX,   desktopSizeY   = desktopRect[ 2 ], desktopRect[ 3 ]
    desktopOrigin = (desktopOriginX, desktopOriginY)
    desktopSize   = (desktopSizeX, desktopSizeY)
    if debug :
        print '----  desktopOrigin = ', desktopOrigin
        print '----  desktopSize   = ', desktopSize
        print
    #end if
    
    #-----
    
    # A wx.ScreenDC provides access to the entire (extended desktop) SCREEN.
    #   portion of the Desktop. Any exteded Desktop creen portions are excluded.
    # This includes any extended Desktop monitor screens that are enabled in the OS.
    desktopDC   = wx.ScreenDC()     # CORRECT: RETURNS THE EXTENDED DESKTOP
    #desktopSize = desktopDC.Size    # BUG:     REPORTS THE WRONG SIZE !
    
    desktopSizeX, desktopSizeY = desktopSize
    
    # Cross-platform adaptations :
    desktopDCBmap  = desktopDC.GetAsBitmap()
    scrBmapSize    = desktopDCBmap.GetSize()
    
    #print '----  scrBmapSize ', scrBmapSize;  print
    
    # Check if desktopDC.GetAsBitmap() method has been implemented on this platform.
    if desktopDCBmap.IsOk() :   # Use desktopDC as it is.
        
        if debug :
            print '----  Using desktopDC.GetAsBitmap()\n'
        
    else :
        
        if debug :
            print '----  Using memDC.Blit() since desktopDC.GetAsBitmap() is nonfunctional.\n'
        
        # Create a new empty (black) destination bitmap the size of the desktopDC. 
        # Overwrire the invalid original "desktopDCBmap".
        desktopDCBmap = wx.EmptyBitmap( *desktopSize )
        
        # Create a DC tool that is associated to desktopDCBmap.
        memDC = wx.MemoryDC( desktopDCBmap )
        
        # Copy (blit, "Block Level Transfer") a portion of the screen bitmap 
        #   into the returned capture bitmap.
        # The bitmap associated with memDC (desktopDCBmap) is the blit destination.
        
        desktopBmapOriginX, desktopBmapOriginY  = (0, 0)
        desktopSizeX, desktopSizeY      = desktopSize
        
        #######################################################################
        # Blit the entire desktop.
        memDC.Blit( desktopBmapOriginX, desktopBmapOriginY, # Destination start coordinate
                    desktopSizeX, desktopSizeY,             # Blit size
                    desktopDC,                              # Source bitmap DC
                    *desktopOrigin )                        # Source start coordinate
        
        memDC.SelectObject( wx.NullBitmap ) # Finish using this wx.MemoryDC
                                            # Release desktopDCBmap for other uses
        #######################################################################
    #end if
    
    #-----
    
    if debug :
        print '----  grabRect ', grabRect
    
    # The grab origin given in the desktop coordinate system (possible negative ordinates) 
    #   has to be translated (literally) to the bitmap coordinate system 
    #   with its origin of (0, 0), 
    # Subtract the grab origin ordinates from the desktop origin ordinates.
    grabStartX, grabStartY = (grabRect[ 0 ], grabRect[ 1 ])
    
    subBmapStart = (grabStartX - desktopOriginX, grabStartY - desktopOriginY)
    
    grabSize = (grabRect[ 2 ], grabRect[ 3 ])
    if debug :
        print '----  grabStartX, grabStartY ', grabStartX, grabStartY
        print '----  subBmapStart ', subBmapStart, '(grab start coord translated to bitmap origin)'
        print '----  grabSize ', grabSize;  print
    #end if
    
    try :
        grabBmap = desktopDCBmap.GetSubBitmap( wx.RectPS( subBmapStart, grabSize ) )
        
    except :    # Given bmapSize tuple arg is illegal
        
        errMsg = '####  ScreenCapture:  Invalid Parameter Given:  %s  or  %s'  \
                 % ('startPos='+repr(subBmapStart), 'bmapSize'+repr(grabSize))
                 
        if errorMsgBmap :
            # Create a error message text bitmap in place of the screen grab.
            grabBmap = ctb.CreateTextBmap( errMsg, color='Navy', bgColor='Red' )
        else :
            if debug :
                print errMsg
            grabBmap = None
        #end if

    #end try
    
    return grabBmap
        
#end ScreenCapture def

#------------------------------------------------------------------------------

if __name__ == '__main__' :
    """
    Demo.test App
    """
    
    DEBUG = False
    DEBUG = True
    
    desktopRect = GetDesktopRect()
    
    #-----
    
    """ """
    # Grab and save the entire possibly extended desktop.
    grabOriginX, grabOriginY = desktopRect.GetPosition()
    grabSizeX,   grabSizeY   = desktopRect.GetSize()
    grabRect = (grabOriginX, grabOriginY, grabSizeX,  grabSizeY)
    
    shotBmap = ScreenCapture( grabRect, debug=DEBUG )
    filename = 'ScreenShotWX_Entire.PNG'
    shotBmap.SaveFile( filename, wx.BITMAP_TYPE_PNG )
    """ """
    
    #-----
    
    """ """
    desktopOriginX, desktopOriginY = desktopRect.GetPosition()
    
    desktopSizeX, desktopSizeY = desktopRect.GetSize()
    
    # Capture the central part of the possibly extended desktop.
    grabOriginX, grabOriginY = (desktopOriginX + desktopSizeX/4, desktopOriginY + desktopSizeY/4)
    grabSizeX,   grabSizeY   = (desktopSizeX/2, desktopSizeY/2)
    grabRect = (grabOriginX, grabOriginY, grabSizeX, grabSizeY)
    
    shotBmap = ScreenCapture( grabRect, debug=DEBUG )
    filename = 'ScreenShotWX_Central.PNG'
    shotBmap.SaveFile( filename, wx.BITMAP_TYPE_PNG )
    """ """
    
#end if

#------------------------------------------------------------------------------

def CreateTextBmap( text, size=None, font=None, 
                    color=None, bgColor=None, transparent=False ) :
    """ 
    Returns a minimally-sized bitmap.
    
    Colors may be defined in the usual ways: A 3-tuple or a text string.
    If a given text background color is invalid 
      it will be set to the DC's background color.
    
    Ray Pasco
    pascor(at)verizon(dot)net
    
    2011-06-09
    """
    
    # Create an app if one hasn't been created yet.
    if not wx.GetApp() :
        dummyApp = wx.App( redirect=False )
    #end try
    
    #-----
    
    # The text font.
    if font :
        useFont = font
    else :
        useFont = wx.SystemSettings_GetFont( wx.SYS_DEFAULT_GUI_FONT )
    #end if
    useSize = useFont.GetPointSize()
    
    if size :   # Set the font's size in pixels (not points !)
        useFont.SetPointSize( size )  # Function name is a misnomer.
    #end if
    useSize = useFont.GetPointSize()
    
    #-----
    
    # Create a bitmap larger that the expected written text bounding box.
    textLen = len( text )
    bmapSizeX = (useSize * textLen) * 2     # Use a bitmap bigger than expected.
    bmapSizeY = useSize * 2                 # Some font "aspect ratios" are very unusual.
    bmapSize = (bmapSizeX, bmapSizeY)          
    bmap = wx.EmptyBitmap( *bmapSize )
    dc = wx.MemoryDC()
    dc.SelectObject( bmap )
    
    dc.SetFont( useFont )
    
    #-----
    
    # Text FG and BG colors.
    useColor = 'BLACK'     # Already the DC's default.
    if color :
        useColor = color
    dc.SetTextForeground( useColor )
    
    useBgColor = 'WHITE'   # Already the DC's default.
    if bgColor :
        useBgColor = bgColor
    dc.SetTextBackground( useBgColor )  # Has no effect if BG mode is wx.TRANSPARENT
    
    dc.SetBackgroundMode( wx.SOLID )    # MUST first set SOLID !  (Bug or feature ?)
    if transparent :
        dc.SetBackgroundMode( wx.TRANSPARENT )  # DC default is wx.SOLID
    
    #-----
    
    # Paint the bitmap background.
    useDcColor = wx.NamedColor( 'WHITE' )   # The DC default
    if not transparent :
        useDcColor = useBgColor
        
    dc.SetBackground( wx.Brush( useDcColor ) )
    dc.Clear()
    
    #-----
    
    textPosn = (1, 0)               # 1-pixel left-side border
    dc.DrawText( text, *textPosn )
    
    dc.SelectObject( wx.NullBitmap )
    
    # Crop the oversized bitmap to the needed minimum.
    origin = (0, 0)
    textSize = dc.GetTextExtent( text )
    
    # Adjust for a 1-pixel left and bottom margin.
    bmap = bmap.GetSubBitmap( wx.RectPS( origin, SequenceAdd( textSize, (1, 1) ) ) )
    
    return bmap
    
#end CreateTextBmap def

#------------------------------------------------------------------------------

def SequenceAdd( x, y, error=True ) :
    """
    Add numerical elements in lists and/or tuples.
    The returned sequence type is set by the type of the first given sequence.
    """
    
    legalTypes = [type( [1, 2] ), type( (1, 2) )]
    if (type( x ) not in legalTypes)  or  (type( y ) not in legalTypes)  :
        errMsg = '\n####  A given sequence argument is not a list or a tuple: [ %s ]  [%s ]' %  \
                 (repr( x ), repr( y ))
        print errMsg
        return None
    #end if
    
    #-----
    
    returnType = type( x )      # First given seq defines the returned sequence type.
    
    if len(x) != len(y) :
        raise ValueError, 'Given Sequences Must Have the Same Length.'
    
    sumList = list()
    for index in range( len( x ) ) :
        
        try :
            float( x[ index ] );  float( y[ index ] )
        except :
            errMsg = '\n####  Sequence Elements Must Be Numerical:  [%s], [%s]'  \
                      % (repr(x[ index ]), repr(y[ index ]))
            
            if error :
                raise ValueError, errMsg
            else :
                print errMsg
                return None
        #end try
        
        sumList.append( x[ index ] + y[ index ] )
    #end for
    
    if   returnType == type( (1, 2, 3) ) :
        return tuple( sumList )
    
    elif returnType == type( [1, 2, 3] ) :
        return sumList 
    
#end def
    
#------------------------------------------------------------------------------
