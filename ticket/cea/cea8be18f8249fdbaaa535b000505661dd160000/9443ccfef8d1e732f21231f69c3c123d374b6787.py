#!/bin/env python

# ---------------------------------------------------------------------------
#
# Test code to demo bug where wxConfig.read() can return a tuple rather than
# a string.
#
# ---------------------------------------------------------------------------

import os
from wxPython.wx import *

appTitle   = "wxConfig 'tuple' bug"
appName    = "wxConfig Tuple Bug"
vendorName = "wxWindows"

class BCFrame(wxFrame):
    def __init__(self, parent, id, title,
            pos = wxPyDefaultPosition, size = wxPyDefaultSize,
            style = wxDEFAULT_FRAME_STYLE):
        wxFrame.__init__(self, parent, id, title, pos, size, style)

        self.cfg=wxConfigBase_Get(True)

        path = os.getcwd()
        lastDrv, lastDir = os.path.splitdrive(path)
        lastFil = ''

        print '-'*80
        print "Set up some variables to use as defaults for wxConfig.Read()"
        print "1: lastDrv=", lastDrv
        print "1: type(lastDrv)=", type(lastDrv)
        print "1: lastDir=", lastDir
        print "1: type(lastDir)=", type(lastDir)
        print '-'*80

        # Wierdness here. If we supply a default, cfg.Read returns a tuple!
        lastFil = self.cfg.Read("/Prefs/DataFile", lastFil)
        lastDrv = self.cfg.Read("/Prefs/LastDataDrive", lastDrv),
        lastDir = self.cfg.Read("/Prefs/LastDataDirectory", lastDir),

        print "If we supply these defaults, cfg.Read() returns a tuple!"
        print "2: lastDrv=", lastDrv
        print "2: type(lastDrv)=", type(lastDrv)
        print "2: lastDir=", lastDir
        print "2: type(lastDir)=", type(lastDir)
        print '-'*80

        # With no default, cfg.Read returns a string, as expected.
        lastFil = self.cfg.Read("/Prefs/DataFile")
        lastDrv = self.cfg.Read("/Prefs/LastDataDrive")
        lastDir = self.cfg.Read("/Prefs/LastDataDirectory")

        print "With no defaults, cfg.Read() returns a string, as expected"
        print "3: lastDrv=", lastDrv
        print "3: type(lastDrv)=", type(lastDrv)
        print "3: lastDir=", lastDir
        print "3: type(lastDir)=", type(lastDir)
        print '-'*80

        # With no default, cfg.Read returns a string, as expected.
        lastFil = self.cfg.Read("/Prefs/DataFile", "")
        lastDrv = self.cfg.Read("/Prefs/LastDataDrive", "")
        lastDir = self.cfg.Read("/Prefs/LastDataDirectory", "")

        print "With empty defaults, cfg.Read() returns a string, as expected"
        print "4: lastDrv=", lastDrv
        print "4: type(lastDrv)=", type(lastDrv)
        print "4: lastDir=", lastDir
        print "4: type(lastDir)=", type(lastDir)
        print '-'*80

        EVT_CLOSE(self, self.OnCloseWindow)

    def OnCloseWindow(self, event):
        self.Destroy()

# -------------------------------------------------------------------------

class BCApp(wxApp):
    def __init__(self):
        wxApp.__init__(self)

    def OnInit(self):
        wxInitAllImageHandlers()
        self.SetAppName(appName)
        self.SetVendorName(vendorName)

        frame = BCFrame(None, -1, appTitle, wxPoint(20,20), wxSize(500,340))
        frame.Show(True)
        return True

# -------------------------------------------------------------------------
      
app = BCApp()
app.MainLoop()

 	  	 
