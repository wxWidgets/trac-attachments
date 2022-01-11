# Demonstrate notebook behaviour with pre-close message box.
# Issue present in wx.aui.Notebook too.
import time
import wx

class Apanel(wx.Panel):
    def __init__(self, parent):
        self.notebook = parent
        wx.Panel.__init__(self, parent )
        b = wx.Button(self,wx.ID_ANY, "Press me to close page", (50, 50))
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)

    def OnButton(self, evt):
        md_parent = self                    # crashes Python
        # md_parent = self.GetParent()        # OK
        # md_parent = self.GetGrandParent()   # OK
        # md_parent = None                    # OK
        message = ('Closing this notebook page. ' +
                  'Parent of message dialog is %s' % repr(md_parent) )
        dlg = wx.MessageDialog(md_parent, message, 'Message box' , wx.OK )
        dlg.ShowModal()
        dlg.Destroy()
        n = 0
        # this wait loop has no effect and reports n = 0
        #while hasattr(self, 'dlg'):
        #    n += 1
        #    time.sleep(0.001)
        #print n 

        self.notebook.DeletePage(0)                   # crashes
        # wx.CallAfter(self.notebook.DeletePage, 0)     # still crashes
        # wx.CallLater(50, self.notebook.DeletePage, 0)  # OK - even with t=0 !

class Aframe(wx.Frame):
    def __init__(self, parent, id=wx.ID_ANY, title="",
                   pos=wx.DefaultPosition, size=(800, 600),
                   style=wx.DEFAULT_FRAME_STYLE):

        wx.Frame.__init__(self, parent, id, title, pos, size, style)
        nb = wx.Notebook(self, wx.ID_ANY)
        nb.AddPage(Apanel(parent=nb),'Page 1', True)

if __name__ == '__main__':
    print wx.version() 
    app = wx.PySimpleApp()
    frame = Aframe(None, title="Notebook with a pre-close message")
    frame.Show()
    app.MainLoop()
