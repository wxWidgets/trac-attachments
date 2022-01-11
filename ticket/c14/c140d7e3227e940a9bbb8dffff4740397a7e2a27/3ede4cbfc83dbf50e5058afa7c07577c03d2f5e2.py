
import  wx

import wx.stc as stc

demotext = """wxPython %s

Show a Bug with the MouseWheel stopping
working after a undetermined amount of time.
Sometimes it occurs 5 min, 1 hour, variable, etc. 
Just leave the app open and do something else for a while.
Checking up on it every x amount of mins, testing the mousewheel.

Comfirmed on wxPython 2.9.4.0 msw (classic)
Windows XP Pro SP3

The Test:
The top ctrl is PlainSTC1(regular).
The bottom ctrl is PlainSTC2(wx.EVT_MOUSEWHEEL hack to bypass).

The top ctrl's MouseWheel scrolling functionallity will eventually stop working,
while the bottom ctrl will still work correctly
with the wx.EVT_MOUSEWHEEL hack def.

Please Fix This Bug. 
It is very annoying to have to restart an app because of this bug 
I'm not sure if this is scintilla or wxwidgets bug, but I am guessing wxwidgets.

%s%s
""" %(wx.version(), '='*78, ('Test '*100 + '\n' + 'StyledTextCtrl'*25 + '\n ')*100)

#---------------------------------------------------------------------------

class PlainSTC1(stc.StyledTextCtrl):
    def __init__(self, parent, id=wx.ID_ANY):
        stc.StyledTextCtrl.__init__(self, parent, id)
        self.SetText(demotext)


class PlainSTC2(stc.StyledTextCtrl):
    def __init__(self, parent, id=wx.ID_ANY):
        stc.StyledTextCtrl.__init__(self, parent, id)
        self.SetText(demotext)
        self.Bind(wx.EVT_MOUSEWHEEL, self.OnMouseWheel)

    def OnMouseWheel(self, event):
        """
        wx.EVT_MOUSEWHEEL
        Allow Shift + MouseWheel Horizontal Scrolling
        """
        print('OnMouseWheel')
        evtobj = event.GetEventObject() #In this case it's a StyledTextCtrl
        xoffset = evtobj.GetXOffset()
        # print('GetWheelRotation: ', event.GetWheelRotation())
        # print('GetWheelDelta: ', event.GetWheelDelta())
        # print('GetXOffset: ', xoffset)
        if xoffset < 0:#Dont scroll back past zero position
            evtobj.SetXOffset(0)
            evtobj.Refresh()
            return
        #-- Shift + MouseWheel = Scroll Horizontally
        if event.ShiftDown() and event.GetWheelRotation() < 0:#negative/down Ex: -120
            # print('Shift + WheelDown')
            evtobj.SetXOffset(xoffset + 30)
            return
        elif event.ShiftDown() and event.GetWheelRotation() > 0:#positive/up Ex: 120
            # print('Shift + WheelUp')
            if not xoffset <= 0:
                evtobj.SetXOffset(xoffset - 30)
                return
            else:
                return

        #-- MouseWheel = Scroll Vertically
        # Duplicate Default behavior to try to bypass
        # (MouseWheel not working after a undetermined amount of time)BUG
        elif event.GetWheelRotation() < 0:#negative/down Ex: -120
            self.LineScroll(0, 3)
            # print('WheelDown')
            return
        elif event.GetWheelRotation() > 0:#positive/up Ex: 120
            self.LineScroll(0, -3)
            # print('WheelUp')
            return
        # event.Skip()



class MyFrame(wx.Frame):
    def __init__(
            self, parent, id=wx.ID_ANY, title='Test STC MouseWheel Bug', pos=wx.DefaultPosition,
            size=wx.DefaultSize, style=wx.DEFAULT_FRAME_STYLE
            ):

        wx.Frame.__init__(self, parent, id, title, pos, size, style)
        panel = wx.Panel(self, -1)
        self.control1 = PlainSTC1(panel, wx.ID_ANY)
        self.control2 = PlainSTC2(panel, wx.ID_ANY)

        vsizer = wx.BoxSizer(wx.VERTICAL)
        vsizer.Add(self.control1, 1, wx.EXPAND | wx.ALL, 5)
        vsizer.Add(self.control2, 1, wx.EXPAND | wx.ALL, 5)
        panel.SetSizerAndFit(vsizer)

        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)

        self.Centre()
        self.Show()

    def OnCloseWindow(self, event):
        self.Destroy()


if __name__ == '__main__':
    app = wx.App(0)
    frame = MyFrame(None)
    app.MainLoop()


