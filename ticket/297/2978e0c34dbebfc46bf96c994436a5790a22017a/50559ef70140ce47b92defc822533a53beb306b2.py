"""
This sample application demonstrates a bug found in wxFileDialog.
Run it and in the wxFileDialog that pops enter the name of an existing file
without it's extension (.txt is used here as a wildcard).
This sample ofcourse does not write anything to disk, so no need
to worry about your most precious file :)
"""

import os
from wxPython.wx import *

class Frame(wxFrame):
    def __init__(self, parent, id, title,
                 pos = wxPoint(100,100), size = wxSize(300,300)):
        wxFrame.__init__(self, parent, id, title, pos, size)

        button = wxButton(self, 10, 'press me')

        EVT_BUTTON(self, 10, self.OnClick)

    def OnClick(self, event):
        dlg = wxFileDialog(self, wildcard = "*.txt",
                           style = wxSAVE | wxOVERWRITE_PROMPT)
        dlg.Centre
        res = dlg.ShowModal()
        path = dlg.GetPath()
        dlg.Destroy()

        if res == wxID_OK:
            if os.path.isfile(path): msg = ' exists'
            else: msg = ' does not exist'

            dlg = wxMessageDialog(self, 'File %s and will be saved' % (path + msg),
                                  'Message not from wxFileDialog!',
                                  style = wxOK | wxICON_INFORMATION )
            dlg.Centre(); dlg.ShowModal(); dlg.Destroy()

class MyApp(wxApp):
    def OnInit(self):

        frame = Frame(NULL, -1, 'prox')
        frame.Show(true)
        self.SetTopWindow(frame)
        return true

app = MyApp()
app.MainLoop()

 	  	 
