from   wxPython.wx import *

class Testfields(wxDialog):
     def __init__(self, parent, id=-1, title = "Textfield Dialog", 
pos=wxDefaultPosition,
                  size=wxDefaultSize, style = wxDEFAULT_DIALOG_STYLE):
         wxDialog.__init__(self, parent, id, title, pos, wxSize(640, 
550), style)
         self.Centre(wxBOTH)
         self.a1 = wxTextCtrl(self, 101, '', wxPoint(20, 10), 
                              wxSize(600, 60),  style = wxTE_MULTILINE)
         self.a2 = wxTextCtrl(self, 102, '', wxPoint(20, 80), 
                              wxSize(600, 60), style = wxTE_MULTILINE)
         self.a3 = wxTextCtrl(self, 103, '', wxPoint(20, 150), 
                              wxSize(600, 60))#, style = wxTE_MULTILINE)
         self.a4 = wxTextCtrl(self, 104, '', wxPoint(20, 220), 
                              wxSize(600, 60))#, style = wxTE_MULTILINE)
         self.a5 = wxTextCtrl(self, 105, '', wxPoint(20, 290), 
                              wxSize(600, 60))#, style = wxTE_MULTILINE)
         self.a6 = wxTextCtrl(self, 106, '', wxPoint(20, 360), 
                              wxSize(600, 60), style = wxTE_MULTILINE)
         self.a7 = wxTextCtrl(self, 107, '', wxPoint(20, 430), 
                              wxSize(600, 60), style = wxTE_MULTILINE)
         self.btnOK = wxButton(self, wxID_OK, '&OK', wxPoint(20, 500), 
                               wxSize(-1, -1))
         self.btnCancel = wxButton(self, wxID_CANCEL,'&Cancel', 
                               wxPoint(120, 500), wxSize(-1, -1))

         self.a1.SetFocus()


class MyApp(wxApp):
     def OnInit(self):
         frame = Testfields(None, -1)
         frame.Show(true)
         self.SetTopWindow(frame)
         return true

#---------------------------------------------------------------------------
def main():
     app = MyApp(0)
     app.MainLoop()
#----------------------------------------------------------------------------
if __name__ == '__main__':
     main()


 	  	 
