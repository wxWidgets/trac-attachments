#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~ Imports 
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

import wxversion
wxversion.select('2.5.3-unicode')

import wx

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~ Definitions 
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def makeLotsOfTimers(evt=None, count=5000):
    for x in xrange(count):
        timer = wx.Timer() 
        del timer

def main():
    app = wx.PySimpleApp()
    frame = wx.Frame(None, -1, 'Testing')
    panel = wx.Panel(frame, -1)

    button = wx.Button(panel, -1, 'Lots of Timers')
    button.Bind(wx.EVT_BUTTON, makeLotsOfTimers)

    frame.Show()
    app.MainLoop()

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#~ Main 
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

if __name__=='__main__':
    main()


 	  	 
