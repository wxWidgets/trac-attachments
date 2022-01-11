from wxPython.wx import *

class MainWindow(wxPanel):
    def __init__(self, parent):
        wxPanel.__init__(self, parent, -1)

        self.a = wxListCtrl(self, wxNewId())
        self.b = wxButton(None, -1, "")   # having no parent segfaults
        box = wxBoxSizer(wxVERTICAL)
        box.Add(self.a, 1, wxEXPAND)

        # If next line commented out, doesn't SIGSEGV
        box.Add(self.b, 1, wxEXPAND)

        self.SetSizer(box)
        self.Layout()

class App(wx.wxApp):
    def __init__(self):
        wxApp.__init__(self, 0)

    def OnInit(self):
        wxInitAllImageHandlers()

        self.frame = wxFrame(None, -1, "")
        self.window = MainWindow(self.frame)

        return True

def main(argv):
    app = App()
    app.MainLoop()

if __name__ == "__main__":
    main(sys.argv)



 	  	 
