
"""
DesktopWindow.py
    MS Window Desktop snapshot grabber

Modified from :
"Taking screenshots"
http://www.python-forum.org/pythonforum/viewtopic.php?f=1&t=3740&start=20

Notes :
    - Requires any platform where [ os.name == 'nt' ].
    - Requies add-on Python Win32 Extensions
    - wxPython for image file save functions

Ray Pasco
pascor(at)verizon(dot)net

REVISIONS:
    2011-06-13  Initial
"""

import sys, os
import time

try :
    import wx
except ImportError :
    print '----  The wxPython GUI package must be installed.\n'
    os.startfile( 'http://www.wxpython.org/download.php' )
    sys.exit(1)
    
try :
    import win32gui
    import win32ui
    import win32con
except ImportError :
    print '----  The "Python Win32 Extensions" package must be installed.\n'
    os.startfile( 'http://python.net/crew/mhammond/win32/Downloads.html' )
    sys.exit(1)

#------------------------------------------------------------------------------

def GetScreenRectList() :
    """
    Find each Desktop screen, storing each in a scrObj within a list.
    Output some of the stored screen metrics for each scrObj.
    """
    
    # Create an app if one hasn't been created yet.
    if not wx.GetApp() :
        dummyApp = wx.App( redirect=False )
    #end try
    
    #-----
    
    # On most systems the Main screen index is 0, but this is not necessarily so.
    # [ scrRectList ] will always have item #0 to be the main screen
    #   regardless of its index value.
    # Screen indices are contiguous starting at 0.
    scrRectList = list()
    for scrIndex in range( wx.Display().GetCount() ) :
        
        # Build the list of scrObj's and sort them so that 
        #  the Main screen is always at list index 0.
        
        scrRect = wx.Display( scrIndex ).GetGeometry()
        
        isPrimary = wx.Display( scrIndex ).IsPrimary()
        
        if isPrimary :           # Force this to be the first element.
            scrRectList.insert( 0, scrRect ) 
        else :                          # Its order in the sequence is unimportant.
            scrRectList.append( scrRect )    
            
    #end for 
    
    return scrRectList
    
#end GetScreenRectList def

#------------------------------------------------------------------------------

def GetDesktopExtent( scrRectList ) :
    
    originXmin, originYmin, sizeXmax, sizeYmax = scrRectList[ 0 ]
    
    if (len( scrRectList ) > 1 ) :
        
        # Start ordinates are relative to the Primary Screen origin (0, 0) !
        for originX, originY, sizeX, sizeY in scrRectList[ 1: ] :
            
            sizeX = originX + sizeX
            sizeY = originY + sizeY
            
            if originX < originXmin:    originXmin = originX
            if originY < originYmin:    originYmin = originY
            
            sizeXmax = max( sizeX, sizeXmax )
            sizeYmax = max( sizeY, sizeYmax )
            
        #end for 
    
    sizeX = sizeXmax - originXmin
    sizeY = sizeYmax - originYmin
    
    return tuple( [originXmin, originYmin, sizeX, sizeY] )
    
#end def

#==============================================================================

def GetDesktopBmap() :
    
    dtHwnd = win32gui.GetDesktopWindow()
    
    scrRectList = GetScreenRectList()
    print '----  scrRectList = (startX, startY, sizeX, sizeY) ='
    for aRect in scrRectList :
        print '\t', aRect
    print
    
    dtRect = GetDesktopExtent( scrRectList )
    print '----  Desktop Extent = (minX, minY, sizeX, sizeY) ='
    print '\t', dtRect;  print
    
    originX, originY, sizeX, sizeY = dtRect
    
    dtHandleDC = win32gui.GetWindowDC( dtHwnd )     # Same as win32gui.GetDC( dtHwnd ) ?
    dtSourceDC  = win32ui.CreateDCFromHandle( dtHandleDC )
    dtDestDC = dtSourceDC.CreateCompatibleDC()
    destBmap = win32ui.CreateBitmap()
    destBmap.CreateCompatibleBitmap( dtSourceDC, sizeX, sizeY )
    dtDestDC.SelectObject( destBmap )
    
    bltWriteToStartCoord = (0, 0)
    bltSize = (sizeX, sizeY)
    bltReadFromStartCoord = (originX, originY)
    dtDestDC.BitBlt( bltWriteToStartCoord, bltSize,                         # Destination args
                     dtSourceDC, bltReadFromStartCoord, win32con.SRCCOPY )  # Source args.
    
    filename = 'GetDesktopBmap_MSC.BMP'      # No PNG of JPG save is available.
    print 'MSW Bitmap Save to BMP\n'
    print '----  Writing File [ %s ]' % (filename)
    startTime = time.time()
    destBmap.SaveBitmapFile( dtDestDC, filename )
    endTime = time.time()
    sizeKB = os.path.getsize( filename ) / 1024
    secs = repr( endTime-startTime )[ :5 ]
    speedKBs = repr( int( float( sizeKB ) / ( endTime-startTime ) ) )[ :5 ]
    print '\t[ %d ] KB written in [ %s ] sec =\t[ %s KB/sec ] \n' % (sizeKB, secs, speedKBs)
    
    #-----
    
    print 'WxPython Coversions to PNG and JPG:\n'
    
    # Allow use of wx.Bitmap.SaveFile()
    dummyApp = wx.App( redirect=False )
    wxBmap = wx.Bitmap( filename, wx.BITMAP_TYPE_BMP )   # Read in the .BMP file.
    
    filename = 'GetDesktopBmap_WX.PNG'
    print '----  Writing File [ %s ]' % (filename)
    startTime = time.time()
    wxBmap.SaveFile( filename, wx.BITMAP_TYPE_PNG )
    endTime = time.time()
    sizeKB = os.path.getsize( filename ) / 1024
    secs = repr( endTime-startTime )[ :5 ]
    speedKBs = repr( int( float( sizeKB ) / ( endTime-startTime ) ) )[ :5 ]
    print '\t[ %d ] KB written in [ %s ] sec =\t[ %s KB/sec ] \n' % (sizeKB, secs, speedKBs)
    
    filename = 'GetDesktopBmap_WX.JPG'
    print '----  Writing File [ %s ]  at ~75/100 quality' % (filename)
    startTime = time.time()
    wxBmap.SaveFile( filename, wx.BITMAP_TYPE_JPEG )    # quality = 75/100
    endTime = time.time()
    sizeKB = os.path.getsize( filename ) / 1024
    secs = repr( endTime-startTime )[ :5 ]
    speedKBs = repr( int( float( sizeKB ) / ( endTime-startTime ) ) )[ :5 ]
    print '\t[ %d ] KB written in [ %s ] sec =\t[ %s KB/sec ] \n' % (sizeKB, secs, speedKBs)
    
    #-----
    
    try :
        import Image
        
        print 'PIL Coversions to PNG and JPG:\n'
        
        pilImg = Image.open( 'GetDesktopBmap_WX.PNG' )   # Uses lossless compression
        
        filename = 'GetDesktopBmap_PIL.PNG'
        print '----  Writing File [ %s ]' % (filename)
        startTime = time.time()
        pilImg.save( filename )
        endTime = time.time()
        sizeKB = os.path.getsize( filename ) / 1024
        secs = repr( endTime-startTime )[ :5 ]
        speedKBs = repr( int( float( sizeKB ) / ( endTime-startTime ) ) )[ :5 ]
        print '\t[ %d ] KB written in [ %s ] sec =\t[ %s KB/sec ] \n' % (sizeKB, secs, speedKBs)
        
        filename = 'GetDesktopBmap_PIL.JPG'
        print '----  Writing File [ %s ]  at 90/100 quality' % (filename)
        startTime = time.time()
        pilImg.save( filename, quality=90 )
        endTime = time.time()
        sizeKB = os.path.getsize( filename ) / 1024
        secs = repr( endTime-startTime )[ :5 ]
        speedKBs = repr( int( float( sizeKB ) / ( endTime-startTime ) ) )[ :5 ]
        print '\t[ %d ] KB written in [ %s ] sec =\t[ %s KB/sec ] \n' % (sizeKB, secs, speedKBs)
        
    except ImportError :
        pass            # PIL isn't installed.
    
    #-----
    
    del dtSourceDC
    del destBmap
    del dtDestDC        # Just in case ...
    
    return wxBmap
    
#end GetDesktopBmap def

#------------------------------------------------------------------------------

if __name__ == '__main__' :
    
    dtBmap = GetDesktopBmap()
    
#end if