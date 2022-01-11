#!/usr/bin/env python

import wx, time
import wx.gizmos as gizmos
import ScrolledWindow

#----------------------------------------------------------------------
# There are better ways to do IDs, but this demo requires that the window
# IDs be in a specific range. There are better ways to do that, too, but
# this will do for purposes of this demo.

ID_Menu_New         = 5004
ID_Menu_Exit        = 5005

ID_WINDOW_TOP       = 5000
ID_WINDOW_LEFT1     = 5001
ID_WINDOW_LEFT2     = 5002
ID_WINDOW_BOTTOM    = 5003

#----------------------------------------------------------------------

class SimpleView(wx.Panel):
    def __init__(self, parent, ID):
        wx.Panel.__init__(self, parent, ID)
        self.dyn_sash = self
        self.SetBackgroundColour("LIGHT BLUE")
        self.Bind(gizmos.EVT_DYNAMIC_SASH_SPLIT, self.OnSplit)

    def OnSplit(self, evt):
        v = SimpleView(self.dyn_sash, -1)
        
class MyParentFrame(wx.MDIParentFrame):
    def __init__(self):
        wx.MDIParentFrame.__init__(
            self, None, -1, "MDI Parent", size=(600,400),
            style = wx.DEFAULT_FRAME_STYLE | wx.HSCROLL | wx.VSCROLL
            )

        self.winCount = 0
        self.log = ""
        menu = wx.Menu()
        menu.Append(ID_Menu_New, "&New Window")
        menu.AppendSeparator()
        menu.Append(ID_Menu_Exit, "E&xit")

        menubar = wx.MenuBar()
        menubar.Append(menu, "&File")
        self.SetMenuBar(menubar)

        #self.CreateStatusBar()

        self.Bind(wx.EVT_MENU, self.OnNewWindow, id=ID_Menu_New)
        self.Bind(wx.EVT_MENU, self.OnExit, id=ID_Menu_Exit)
        self.Bind(wx.EVT_TIMER, self.OnTimer)

        self.Bind(
            wx.EVT_SASH_DRAGGED_RANGE, self.OnSashDrag, id=ID_WINDOW_TOP, 
            id2=ID_WINDOW_BOTTOM
            )

        self.Bind(wx.EVT_SIZE, self.OnSize)

        # A window to the left of the client window
        win =  wx.SashLayoutWindow(self, ID_WINDOW_LEFT1, style=wx.NO_BORDER|wx.SW_3D)
        win.SetDefaultSize((120, 1000))
        win.SetOrientation(wx.LAYOUT_VERTICAL)
        win.SetAlignment(wx.LAYOUT_LEFT)
        win.SetSashVisible(wx.SASH_RIGHT, True)
        win.SetExtraBorderSize(10)
        win.textWindow = wx.TextCtrl(win, -1, "", style=wx.SUNKEN_BORDER)
        win.textWindow.SetValue("A sub window")

        self.leftWindow1 = win
        self.t = wx.Timer(self)
        self.t.Start(500)

    def OnTimer(self,evt):
        self.leftWindow1.textWindow.SetValue("New Time %s" % time.localtime(time.time()))

    def OnSashDrag(self, event):
        if event.GetDragStatus() == wx.SASH_STATUS_OUT_OF_RANGE:
            return

        eID = event.GetId()
        
        if eID == ID_WINDOW_TOP:
            self.topWindow.SetDefaultSize((1000, event.GetDragRect().height))

        elif eID == ID_WINDOW_LEFT1:
            self.leftWindow1.SetDefaultSize((event.GetDragRect().width, 1000))

        elif eID == ID_WINDOW_LEFT2:
            self.leftWindow2.SetDefaultSize((event.GetDragRect().width, 1000))

        elif eID == ID_WINDOW_BOTTOM:
            self.bottomWindow.SetDefaultSize((1000, event.GetDragRect().height))

        wx.LayoutAlgorithm().LayoutMDIFrame(self)
        self.GetClientWindow().Refresh()

    def OnSize(self, event):
        print self
        wx.LayoutAlgorithm().LayoutMDIFrame(self)

    def OnExit(self, evt):
        self.Close(True)

    def OnNewWindow(self, evt):
        self.winCount = self.winCount + 1
        winId = wx.NewId()
        wx.RegisterId(winId)
        canvasId = wx.NewId()
        wx.RegisterId(canvasId)
        win = wx.MDIChildFrame(self, winId, "Child Window: %d" % self.winCount)
        #canvas = ScrolledWindow.MyCanvas(win)
        #canvas = gizmos.DynamicSashWindow(win,canvasId, style=gizmos.DS_MANAGE_SCROLLBARS)
        canvas = gizmos.DynamicSashWindow(win,canvasId)
        self.Bind(wx.EVT_SIZE, self.OnSize)
        view = SimpleView(canvas, canvasId)
        print self
        win.Show(True)

#----------------------------------------------------------------------

if __name__ == '__main__':
    class MyApp(wx.App):
        def OnInit(self):
            wx.InitAllImageHandlers()
            frame = MyParentFrame()
            frame.Show(True)
            self.SetTopWindow(frame)
            return True

    app = MyApp(False)
    app.MainLoop()
 	  	 
