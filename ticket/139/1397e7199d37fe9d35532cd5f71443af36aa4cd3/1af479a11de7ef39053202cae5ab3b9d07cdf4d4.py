#!/usr/bin/env python

import sys
import traceback

import wx
import wx.lib.delayedresult

def wx_exception_handler (type, exception, tb):
    if hasattr(exception, "originalTraceback"):
        wx.MessageBox("An exception occured within a worker thread. The original exception was: \n" + exception.originalTraceback, "Error!", style=wx.ICON_EXCLAMATION)
    else:
        wx.MessageBox("An exception occurred: \n" + ''.join(traceback.format_exception(type, exception, tb)), "Error!", style=wx.ICON_EXCLAMATION)

class DelayedExceptionFrame (wx.Frame):
    def __init__ (self, parent=None, title="DelayedException demonstration", *args, **kwargs):
        super(DelayedExceptionFrame, self).__init__(parent=parent, title=title, *args, **kwargs)

        self.panel = wx.Panel(parent=self)

        self.button = wx.Button(parent=self.panel, label="Start worker thread with exception")
        self.button.Bind(wx.EVT_BUTTON, self.start_worker)

    def start_worker (self, event):
        def producer ():
            raise TypeError

        def consumer (result):
            result = result.get()

            wx.MessageBox("The result was: %s!" % result)

        wx.lib.delayedresult.startWorker(consumer, producer)

def main ():
    app = wx.App(False)

    main_frame = DelayedExceptionFrame()
    main_frame.Show()

    app.MainLoop()

if __name__=="__main__":
    sys.excepthook = wx_exception_handler

    main()
