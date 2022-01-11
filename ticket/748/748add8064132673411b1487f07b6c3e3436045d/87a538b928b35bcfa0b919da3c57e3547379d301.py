"""
Minimum code that is the cause of an "Unhandled Exception"
when trying to use Notebook with sizers.

Windows "Unhandled Exception" Message Box :
    An unhandled exception occured.
    'Abort' will terminate theprogram,
    'Retry' will close the current dialog.
    'Ignore' will try to continue.

The Exception occurs when closing the frame (and the application)

versions:
    wxPythonWIN32-2.5.1.5-Py23.exe
    Python-2.3.4.exe
    Windows XP Home Edition, Service Pack 1,

started by:
    C:\Python23\Python.exe notebooksizer_bug.py

the application creates a Notebook with one page and use the sizers
"""
import wx

class MyApp(wx.App):
    def OnInit(self):
        frame = wx.Frame(None,-1,"wxWindow Editor")
        
        # add Notebook with 1 page containg 1 TextCtrl
        nb = wx.Notebook(frame,-1)
        pan = wx.Panel(nb,-1)
        edtCtrl = wx.TextCtrl(pan, -1 , size=wx.Size(100,40))
        nb.AddPage(pan,'Editor')
        
        # create sizers
        panSizer = wx.BoxSizer(wx.VERTICAL)
        pan.SetSizer(panSizer)
        panSizer.Add(edtCtrl)
        
        nbSizer = wx.NotebookSizer(nb)
        nb.SetSizer(nbSizer) # if that line is commented, no crash, and no sizer :)
        
        frameSizer=wx.BoxSizer(wx.VERTICAL)
        frame.SetSizer(frameSizer)
        frameSizer.Add(nbSizer)
        
        frame.SetAutoLayout(1)
        frameSizer.Fit(frame)
        
        # show        
        frame.Show(True)
        self.SetTopWindow(frame)
        return True

if __name__ == '__main__':
    app = MyApp()
    app.MainLoop()

 	  	 
