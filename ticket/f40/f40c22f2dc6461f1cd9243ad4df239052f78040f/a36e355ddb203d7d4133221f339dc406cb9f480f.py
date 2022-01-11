import wx

class myFrame(wx.Frame):    ## {{{
    def __init__(self, *args, **kwds):
        wx.Frame.__init__(self, *args, **kwds)
        ##------ panel
        self.panel_=wx.Panel(self,-1)
        self.sizer_ = wx.BoxSizer( wx.VERTICAL )
        self.tree_ = wx.TreeCtrl(self.panel_,-1)
        ##------ put stuff into sizer
        self.sizer_.Add(self.tree_,proportion = 1,flag=wx.EXPAND)

        ## apply sizer
        self.panel_.SetSizer(self.sizer_)
        self.panel_.SetAutoLayout(True)
        ##
        root = self.tree_.AddRoot('untitled')
        font = wx.Font(9,wx.FONTFAMILY_DEFAULT,
                wx.FONTSTYLE_NORMAL,wx.FONTWEIGHT_NORMAL,False,'Courier New')
        self.tree_.SetItemFont(root,font)
        ## a workaround is setting text again for the root item.
        ## but this doesn't work for a .exe file created by py2exe
        ## self.tree_.SetItemText(root,'untitled')
##   }}}

def main():    ## {{{
    app = wx.PySimpleApp(0)
    frame = myFrame(None,-1,title='')
    frame.Show(True)
    app.SetTopWindow(frame)
    app.MainLoop()
##   }}}

if __name__ == "__main__":main()

 	  	 
