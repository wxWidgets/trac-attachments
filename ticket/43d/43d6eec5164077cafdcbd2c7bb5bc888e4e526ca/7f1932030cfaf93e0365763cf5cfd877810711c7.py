# CLB.py

# Demonstrating a problem with wxCheckListBox

from wxPython.wx import *
        
class MyApp(wxApp):

    def OnInit(self):
        frame = wxFrame(NULL, 1, "CLB Test")
        clb = wxCheckListBox(frame, -1)

        clb.Append("Foo")

        frame.Show(true)
        self.SetTopWindow(frame)
        return true

if __name__ == "__main__":
    app = MyApp(0)
    app.MainLoop()

 	  	 
