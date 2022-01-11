# # -*- coding: iso-8859-1 -*-
import wx, wx.aui

ID_MODEL_QUALITY_MATRIX = 10198
ID_MODEL_QUALITY_INFOS = 10199

def PAGE_MODEL_QUALITY( parent, call_fit = True, set_sizer = True ):
    item0 = wx.BoxSizer( wx.VERTICAL )
    
    item1 = wx.TextCtrl(parent, ID_MODEL_QUALITY_MATRIX)
    item0.Add( item1, 0, wx.GROW|wx.ALIGN_CENTER_VERTICAL, 5 )

    item2 = wx.TextCtrl(parent, ID_MODEL_QUALITY_INFOS)
    item0.Add( item2, 0, wx.GROW|wx.ALIGN_CENTER_VERTICAL, 5 )

    if set_sizer == True:
        parent.SetSizer( item0 )
        if call_fit == True:
            item0.SetSizeHints( parent )
    
    return item0


def makeNotebook(parent, id, pagesInfos):
    notebook = wx.Notebook(parent, id)
    
    for pageInfos in pagesInfos :
        # Get page constructor and caption
        constructor = pageInfos[0]
        caption = pageInfos[1]
        
        # Build panel
        panel = wx.Panel(notebook, -1)
        
        print caption
        
        # Build page
        constructor(panel, False)
        
        # Insert page
        notebook.AddPage(panel, caption)
    
    return notebook
    

NOTEBOOK_RULES = 10036

def SPLIT_NOTEBOOK_RULES( parent, call_fit = True, set_sizer = True ):
    item0 = wx.FlexGridSizer( 0, 1, 0, 0 )
    item0.AddGrowableCol( 0 )
    item0.AddGrowableRow( 0 )
    
    item1 = makeNotebook(parent, NOTEBOOK_RULES, ([PAGE_MODEL_QUALITY, "Quality"], ))
    item0.Add( item1, 1, wx.GROW, 5 )

    #### CRASH WITH THESE LINES. Just comment it and it works fine
    if set_sizer == True:
        parent.SetSizer( item0 )
        
    return item0


if __name__ == "__main__" :

    import locale
    class TestFrame(wx.Frame):
        def __init__(self, parent):
            wx.Frame.__init__(self, parent, -1)

            self.nb = SPLIT_NOTEBOOK_RULES(self)
            
            sizer = wx.BoxSizer()
            sizer.Add(self.nb, 1, wx.EXPAND)
            self.SetSizer(sizer)


    class MainApp(wx.App):
        def __init__(self) :
            wx.App.__init__(self, 0)
            
        def OnInit(self):
            wx.InitAllImageHandlers()
            self._frame = TestFrame(None)
            self._frame.Show(True)
            self.SetTopWindow(self._frame)
            return True

    def main() :
        app = MainApp()
        app.MainLoop()
    main()
