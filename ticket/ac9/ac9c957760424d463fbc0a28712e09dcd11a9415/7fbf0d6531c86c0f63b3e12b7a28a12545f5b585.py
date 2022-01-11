from wxPython.wx import *

[wxID_MYEDITFRAME, wxID_MYEDITFRAMENEWIMAGEURL] = map(lambda _init_ctrls: wxNewId(), range(2))

class MyURLDropTarget(wxPyDropTarget):
    def __init__(self, window):
        wxPyDropTarget.__init__(self)
        self.window = window

        self.data = wxURLDataObject()
        self.SetDataObject(self.data)

    def OnDragOver(self, x, y, d):
        return wxDragLink

    def OnDrop(self, x, y):
        print "OnDrop"
        return true
    
    def OnData(self, x, y, d):
        print "OnData"
        self.GetData()
        return d

class MyEditFrame(wxFrame):
    def _init_utils(self):
        pass

    def _init_ctrls(self, prnt):
        wxFrame.__init__(self, id = wxID_MYEDITFRAME, name = 'MyEditFrame', parent = prnt, pos = wxPoint(288, 191), size = wxSize(768, 509), style = wxDEFAULT_FRAME_STYLE, title = 'Edit')
        self._init_utils()
        self.SetClientSize(wxSize(768, 509))

        self.newImageURL = wxTextCtrl(id = wxID_MYEDITFRAMENEWIMAGEURL, name = 'newImageURL', parent = self, pos = wxPoint(48, 32), size = wxSize(456, 40), style = 0, value = 'Drop new image URL here')

    def __init__(self, parent):
        self._init_ctrls(parent)
        self.newImageURL.SetDropTarget(MyURLDropTarget(self.newImageURL))
        
app = wxPySimpleApp(0)
frm = MyEditFrame(None)
frm.Show(1)
app.MainLoop()

 	  	 
