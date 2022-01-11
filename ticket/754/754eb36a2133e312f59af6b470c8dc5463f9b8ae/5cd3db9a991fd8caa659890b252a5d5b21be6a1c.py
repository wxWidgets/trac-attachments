#!/usr/bin/env python
#----------------------------------------------------------------------------

import wx
import time

#----------------------------------------------------------------------------

#class MyApp(wx.App, wx.lib.mixins.inspection.InspectionMixin) :
class MyApp( wx.App ) :

    #-------------------------------------------------------------------------

    def __init__( self ) :
        wx.App.__init__( self, redirect = False )

    #-------------------------------------------------------------------------

    def OnInit( self ) :

        ###
        ### Initialise Progress Dialog.
        ###

        max = 100

        ### forces a decent width of progress dialog.
        msg = ' ' * 100

        title = 'wx.ProgressDialog'

        ### Set this to 0 to not use the style keyword.
        ### Both MSW and OSX behave identically, though the dialog closes
        ### immediately when the value is set to the maximum.
        useStyle = 1

        if useStyle :
            sty = 0
            sty |= wx.PD_CAN_ABORT
            sty |= wx.PD_APP_MODAL
            dlg = wx.ProgressDialog( title = title, message = msg, maximum = max, style = sty )
        else :
            dlg = wx.ProgressDialog( title = title, message = msg, maximum = max )

        time.sleep( 1 )

        ###
        ### Startup message.
        ###
        val = 0
        msg = 'Starting ... ( value = %d )' % ( val )
        ( keepGoing, skip ) = dlg.Update( val, msg )

        ### 1 second delay.
        time.sleep( 1 )

        ###
        ### 1/2 way.
        ###
        val = max / 2
        msg = 'Processing ... ( value = %d )' % ( val )
        ( keepGoing, skip ) = dlg.Update( val, msg )

        ### 1 second delay.
        time.sleep( 1 )

        ###
        ### 3/4 way.
        ###
        val = max * 3 / 4
        msg = 'Finishing ... ( value = %d )' % ( val )
        ( keepGoing, skip ) = dlg.Update( val, msg )

        ### 1 second delay.
        time.sleep( 1 )

        ###
        ### Finished.
        ###
        ### On OS X, this call to Update() returns immediately.
        ### On MSW and GTK, this call to Update() does NOT return.
        ###
        val = max
        msg = 'Finished ... ( value = %d )' % ( val )
        ( keepGoing, skip ) = dlg.Update( val, msg )

        ### 1 second delay.
        time.sleep( 1 )

        dlg.Destroy()

        return True

    #-------------------------------------------------------------------------

    def AppExit( self, status ):
        sys.exit( status )

    #-------------------------------------------------------------------------

    def OnExitApp( self, evt ):
        self.AppExit( status = True )

    #-------------------------------------------------------------------------

#----------------------------------------------------------------------------

def Main() :

    app = MyApp()
    app.MainLoop()

#----------------------------------------------------------------------------

if __name__ == "__main__" :
    Main()

