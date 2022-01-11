"""Restore bug demo

To demonstrate the bug:
1. Run python restore_bug.py
2. Click on the Taskbar icon to minimize the window
3. Right-click on the Task Bar icon and choose 'Restore'
4. Now click the Task Bar icon repeatedly.  The window will gain and lose
   focus but will fail to minimize.

The bug is appears with Python 2.5.1 and wxPython 2.8.7.1 on Windows XP SP2
"""
import wx

class App(wx.App):
    def OnInit(self):
        frame = wx.Frame(None, title="Restore bug demo", size=(400,400))
        frame.Show()
        self.SetTopWindow(frame)
        return True

if __name__ == '__main__':
    app = App(redirect=False)
    app.MainLoop()

 	  	 
