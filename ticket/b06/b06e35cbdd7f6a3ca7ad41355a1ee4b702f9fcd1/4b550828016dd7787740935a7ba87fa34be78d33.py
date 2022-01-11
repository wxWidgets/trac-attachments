import wx
import sys
from time import sleep

USE_MANUAL_LOOP=1

def one(evt):
    print('one')

def two(evt):
    print('two')

def create():
    win = wx.Frame(None, -1, 'Menu Demo', pos=(50,50), style=wx.DEFAULT_FRAME_STYLE)
    p = wx.Panel(win)
    m = wx.MenuBar()

    menu = wx.Menu()
    item = menu.Append(-1, 'One')
    win.Bind(wx.EVT_MENU, one, item)
    item = menu.Append(-1, 'Two')
    win.Bind(wx.EVT_MENU, two, item)
    m.Append(menu, 'Options')
    win.SetMenuBar(m)

    win.SetSize((300,150))
    win.Show(True)
 
def Interact():
    global evtloop
    while not evtloop.Pending() and evtloop.ProcessIdle(): pass
    if wx.GetApp(): wx.GetApp().ProcessPendingEvents()
    if not evtloop.Dispatch(): return
    # Currently on wxOSX Pending always returns true, so the
    # ProcessIdle above is not ever called. Call it here instead.
    evtloop.ProcessIdle()
    
    while True:
        checkAgain = False
        if wx.GetApp() and wx.GetApp().HasPendingEvents():
            wx.GetApp().ProcessPendingEvents()
            checkAgain = True
        if not checkAgain:
            break


def main():
    if USE_MANUAL_LOOP:
        global evtloop
        App = wx.App()
        create()
        evtloop = wx.GUIEventLoop()
        wx.EventLoop.SetActive(evtloop)

        while True:
            Interact()
            sleep(0.03)

    else:
        App = wx.App()
        create()
        App.MainLoop()

if __name__=='__main__':
    if '-manual' in sys.argv:
        USE_MANUAL_LOOP=1
    elif '-mainloop' in sys.argv:
        USE_MANUAL_LOOP=0
    main()
