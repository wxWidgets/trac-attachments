

from wxPython.wx import *


class Frame(wxFrame):
    def __init__(self):
        wxFrame.__init__(self, None, -1, "Clip Bitmaps", size=(640,480))
        menu = wxMenu()
        menu.Append(101, "Clip")
        menu.Append(102, "Exit")
        mb = wxMenuBar()
        mb.Append(menu, "SPAM")
        self.SetMenuBar(mb)
        EVT_MENU(self, 101, self.OnDoClip)
        EVT_MENU(self, 102, self.OnDoExit)

        self.panel = wxPanel(self, -1)
        bmp = wxEmptyBitmap(1,1)
        self.statbmp = wxStaticBitmap(self.panel, -1, bmp)


    def OnDoClip(self, evt):
        wxTheClipboard.Open()
        if wxTheClipboard.IsSupported(wxDataFormat(wxDF_BITMAP)):
            do = wxBitmapDataObject()
            wxTheClipboard.GetData(do)
            bmp = do.GetBitmap()
            print "Got bitmap of size: ", (bmp.GetWidth(), bmp.GetHeight())
            self.statbmp.Destroy()
            self.statbmp = wxStaticBitmap(self.panel, -1, bmp)
        else:
            print "clipboard does not have a bitmap in it"
        wxTheClipboard.Close()


    def OnDoExit(self, evt):
        self.Close()


app = wxPySimpleApp()
frame = Frame()
frame.Show()
app.MainLoop()




 	  	 
