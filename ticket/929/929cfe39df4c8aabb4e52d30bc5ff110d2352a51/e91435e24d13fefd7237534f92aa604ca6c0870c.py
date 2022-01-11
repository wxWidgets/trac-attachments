import wx

class NotebookBug(wx.Frame):
    def __init__(self, parent, ID, **kwds):
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, parent, ID, "Notebook bug", **kwds)
     
        self.parent = parent

        self.nbNotebookBug = wx.Notebook(self, -1)
        #
        # Create each Notebook tab
        #
        self.pnF1 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF2 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF3 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF4 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF5 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF6 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF7 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF8 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF9 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        self.pnF10 = wx.ScrolledWindow(self.nbNotebookBug, -1, style=wx.TAB_TRAVERSAL)
        
        self.pnF5.Hide()
        self.pnF6.Hide()

        self.szrNotebookBug = wx.BoxSizer(wx.HORIZONTAL)
        self.nbNotebookBug.AddPage(self.pnF10, "1")
        self.nbNotebookBug.AddPage(self.pnF9, "2")
        self.nbNotebookBug.AddPage(self.pnF8, "3")
        self.nbNotebookBug.AddPage(self.pnF7, "4")
        self.nbNotebookBug.AddPage(self.pnF6, "5")
        self.nbNotebookBug.AddPage(self.pnF5, "6")
        self.nbNotebookBug.AddPage(self.pnF4, "7")
        self.nbNotebookBug.AddPage(self.pnF3, "8")
        self.nbNotebookBug.AddPage(self.pnF2, "9")
        self.nbNotebookBug.AddPage(self.pnF1, "11")
        self.szrNotebookBug.Add(wx.NotebookSizer(self.nbNotebookBug), 1, wx.EXPAND, 0)
        self.SetAutoLayout(1)
        self.SetSizer(self.szrNotebookBug)
        self.Layout()
        return

app = wx.PySimpleApp()
frame = NotebookBug(None,-1)
frame.Show()
app.MainLoop()

 	  	 
