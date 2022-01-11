#!/usr/bin/env python
#----------------------------------------------------------------------------

import wx
import time

message = \
'''
This message has newline characters in it
to produce multiline messages in the
ProgressDialog.

As you can see the width is far too large !!!
'''

#----------------------------------------------------------------------------

#class MyApp(wx.App, wx.lib.mixins.inspection.InspectionMixin) :
class MyApp( wx.App ) :

    #-------------------------------------------------------------------------

    def __init__( self ) :
        wx.App.__init__( self, redirect = False )

    #-------------------------------------------------------------------------

    def OnInit( self ) :

        title = 'wx.ProgressDialog'

        sty = 0
        sty |= wx.PD_CAN_ABORT
        sty |= wx.PD_APP_MODAL

        ###
        ### Progress Dialog with excessively large width.
        ###

        msg = message

        dlg = wx.ProgressDialog( title = title, message = msg, style = sty )

        cont = True
        while cont :
            ( cont, skip ) = dlg.Update( value = 50 )
            wx.MilliSleep( 100 )

        ### Destroy the dialog.
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

