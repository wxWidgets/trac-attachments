import wx
from wx import html

ID_TEST = 101

class TTT(wx.Frame):
    def __init__(self, *args, **kwds):
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        
        self.frame_1_menubar = wx.MenuBar()
        self.SetMenuBar(self.frame_1_menubar)
        wxglade_tmp_menu = wx.Menu()
        wxglade_tmp_menu.Append(ID_TEST, "open a HtmlWindow", "", wx.ITEM_NORMAL)
        self.frame_1_menubar.Append(wxglade_tmp_menu, "Test")

        self.Bind(wx.EVT_MENU, self._OnOpenHtmlWindow, id=ID_TEST)

    def _OnOpenHtmlWindow(self, event):

	testFrame = wx.Frame(self, -1, "test", size = (600, 600))
	sizer = wx.BoxSizer(wx.HORIZONTAL)
	testFrame.SetSizer(sizer)
	html = wx.html.HtmlWindow(testFrame)
	html.SetPage("testing ...")
	testFrame.Show(True)
        event.Skip()

if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()
    ttt = TTT(None, -1, "")
    ttt.Move(wx.Point(0,0))
    app.SetTopWindow(ttt)
    ttt.Show()

    app.MainLoop()

 	  	 
