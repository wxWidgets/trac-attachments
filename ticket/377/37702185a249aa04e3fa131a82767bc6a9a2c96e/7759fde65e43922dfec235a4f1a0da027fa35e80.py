import wx

class FRAME(wx.Frame):
    def __init__(self, *args, **kargs):
        wx.Frame.__init__(self, *args, **kargs)
        sizer = wx.BoxSizer(wx.VERTICAL)

        scrolled_window = wx.ScrolledWindow(self)
        main_sizer = wx.GridBagSizer(0,0)
        #panel1
        panel1 = wx.Panel(scrolled_window)
        panel1_sizer = wx.StaticBoxSizer( wx.StaticBox( panel1, 0, 'tralala'), wx.VERTICAL)

        lbl = wx.StaticText(panel1, -1, 'test\nlabel')
        text = wx.TextCtrl(panel1, style=wx.TE_MULTILINE)
        gsz1 = wx.GridBagSizer(10,10)
        gsz1.Add( lbl, pos=(0,0), flag=wx.ALIGN_CENTER_VERTICAL)
        gsz1.Add( text, pos=(0,1), flag=wx.GROW, span=(1,1))
        gsz1.AddGrowableCol(1, proportion=0)
        gsz1.AddGrowableRow(0, proportion=0)
        panel1_sizer.Add(gsz1, flag=wx.GROW, proportion=1, border=0)
        panel1.SetSizer(panel1_sizer)

        main_sizer.Add( panel1, flag=wx.EXPAND, pos=(0,0), border=5, span=(1,1))

        #panel2 - this one gets distorsion
        panel2 = wx.Panel(scrolled_window)
        panel2.SetBackgroundColour('#33cc33')
        panel2_sizer = wx.BoxSizer( wx.VERTICAL)
        gsz2 = wx.GridBagSizer(10,10)
        btn1 = wx.Button( panel2, label='test1')
        btn1.SetDefault()
        btn2 = wx.Button( panel2, label='test2')
        gsz2.Add( btn1, pos=(0,0), flag=0)
        gsz2.Add( btn2, pos=(0,1), flag=0)
        panel2_sizer.Add(gsz2, proportion=1, border=5)
        panel2.SetSizer(panel2_sizer)

        main_sizer.Add( panel2, flag=wx.ALIGN_RIGHT, pos=(1,0) , border=5, span=(1,1))
        main_sizer.AddGrowableCol(0, proportion=0)
        main_sizer.AddGrowableRow(0, proportion=0)

        scrolled_window.SetSizer( main_sizer)
        sizer.Add(scrolled_window, flag=wx.GROW | wx.ALL | wx.EXPAND, proportion=1, border=0)

        self.CreateStatusBar()
        self.SetSizer(sizer)
        self.SetMinSize( (200,200) )
        sizer.Fit(self)

if __name__ == '__main__':
    app = wx.App(0)
    f = FRAME(parent=None)
    f.Show()
    app.MainLoop()

# vim:ts=4:sw=4:expandtab

 	  	 
