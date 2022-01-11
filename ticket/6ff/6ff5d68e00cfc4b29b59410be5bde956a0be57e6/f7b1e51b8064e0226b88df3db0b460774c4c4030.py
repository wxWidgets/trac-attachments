#Boa:Frame:Frame1

import wx
import wx.lib.masked.textctrl
import wx.lib.masked.maskededit

##import mypublisher as mypub

class TextCtrl(wx.lib.masked.textctrl.TextCtrl):    
    def __init__(self, parent, id, **kwargs):
        """ **kwargs = pass rest to maskedtextctrl
        """

        wx.lib.masked.textctrl.TextCtrl.__init__(self, parent, id,
                                    useFixedWidthFont=False, **kwargs)

        self.log = None

##    def _OnKillFocus(self,event):
##        """ Handler for EVT_KILL_FOCUS event.
##        """
##        self.log.AppendText('OnKill \n')
##        self.log.AppendText(self.GetValue())
##        self.log.AppendText('\n')        
##        if self.IsBeingDeleted() or self.GetParent().IsBeingDeleted():
##            return 
##        if self._mask and self._IsEditable():
##            try:
##                self._AdjustField(self._GetInsertionPoint())
##                self._CheckValid()   ## Call valid handler
##            except wx.PyAssertionError:
##                if self.log:
##                    self.log.AppendText('font is not recognized.')
##                    self.log.AppendText('\n')                    
##
##        self._LostFocus()    ## Provided for subclass use
##        event.Skip()
        
    def Paste(self):
        """
        This function redefines the externally accessible .Paste to be
        a smart "paste" of the text in question, so as not to corrupt the
        masked control.  NOTE: this must be done in the class derived
        from the base wx control.
        """
        self.log.AppendText('Paste \n')
        self.log.AppendText(self.GetValue())
        self.log.AppendText('\n')
        
        do = wx.TextDataObject()
        wx.TheClipboard.Open()
        success = wx.TheClipboard.GetData(do)
        wx.TheClipboard.Close()

        if success:
            self.log.AppendText('Clipboard value \n')
            self.log.AppendText(do.GetText())
            self.log.AppendText('\n')
        
##        wx.CallAfter(mypub.publisher.sendMessage, mypub.statusText, '')
        style = self.GetWindowStyleFlag()

        if style & wx.TE_AUTO_URL:
            return # otherwise I get the text twice, it might also "fix" the AssertionError

        if self._mask:
            try:
                self._Paste(raise_on_invalid=True) # call the mixin's Paste method
            except ValueError, e:
                if self.log:
                    self.log.AppendText('text will not fit.')
                    self.log.AppendText('\n')
##                text = _('The text "%s" will not fit into this field!') % e.value
##                wx.CallAfter(mypub.publisher.sendMessage, mypub.statusText, text)
##            except wx.PyAssertionError:
##                if self.log:
##                    self.log.WriteText('font is not recognized.')
##                    self.log.WriteText('\n')                    
##                text = _('The font is not recognized, paste might not work correctly.')
##                wx.CallAfter(mypub.publisher.sendMessage, mypub.statusText, text)
        else:
            wx.TextCtrl.Paste(self)   # else revert to base control behavior

def create(parent):
    return Frame1(parent)

[wxID_FRAME1, wxID_FRAME1PANEL1, wxID_FRAME1STATICTEXT1, 
 wxID_FRAME1STATICTEXT2, wxID_FRAME1STATICTEXT3, wxID_FRAME1TEXTCTRL1, 
 wxID_FRAME1TEXTCTRL2, wxID_FRAME1TEXTCTRL3, wxID_FRAME1TEXTCTRL4, 
] = [wx.NewId() for _init_ctrls in range(9)]

class Frame1(wx.Frame):
    _custom_classes = {'wx.TextCtrl': ['TextCtrl',],}

    def _init_coll_flexGridSizer1_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticText1, 0, border=0, flag=wx.EXPAND)
        parent.AddWindow(self.textCtrl1, 0, border=0, flag=wx.EXPAND)
        parent.AddWindow(self.staticText2, 0, border=0, flag=wx.EXPAND)
        parent.AddWindow(self.textCtrl2, 0, border=0, flag=wx.EXPAND)
        parent.AddWindow(self.staticText3, 0, border=0, flag=wx.EXPAND)
        parent.AddWindow(self.textCtrl3, 0, border=0, flag=wx.EXPAND)
        parent.AddWindow(self.textCtrl4, 1, border=0, flag=wx.EXPAND)

    def _init_coll_flexGridSizer1_Growables(self, parent):
        # generated method, don't edit

        parent.AddGrowableRow(3)
        parent.AddGrowableCol(0)
        parent.AddGrowableCol(1)

    def _init_sizers(self):
        # generated method, don't edit
        self.flexGridSizer1 = wx.FlexGridSizer(cols=2, hgap=5, rows=0, vgap=5)

        self._init_coll_flexGridSizer1_Items(self.flexGridSizer1)
        self._init_coll_flexGridSizer1_Growables(self.flexGridSizer1)

        self.panel1.SetSizer(self.flexGridSizer1)

    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME1, name='', parent=prnt,
              pos=wx.Point(293, 328), size=wx.Size(1007, 297),
              style=wx.DEFAULT_FRAME_STYLE, title='Frame1')
        self.SetClientSize(wx.Size(991, 261))

        self.panel1 = wx.Panel(id=wxID_FRAME1PANEL1, name='panel1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(991, 261),
              style=wx.TAB_TRAVERSAL)

        self.staticText1 = wx.StaticText(id=wxID_FRAME1STATICTEXT1,
              label='wx.textctrl and AUTO_URL', name='staticText1',
              parent=self.panel1, pos=wx.Point(0, 0), size=wx.Size(526, 21),
              style=0)

        self.textCtrl1 = wx.TextCtrl(id=wxID_FRAME1TEXTCTRL1, name='textCtrl1',
              parent=self.panel1, pos=wx.Point(531, 0), size=wx.Size(459, 21),
              style=wx.TE_AUTO_URL, value='')
        self.textCtrl1.Bind(wx.EVT_KILL_FOCUS, self.OnTextCtrl1KillFocus)
        self.textCtrl1.Bind(wx.EVT_TEXT_MAXLEN, self.OnTextCtrl1TextMaxlen,
              id=wxID_FRAME1TEXTCTRL1)

        self.staticText2 = wx.StaticText(id=wxID_FRAME1STATICTEXT2,
              label='masked and AUTO_URL', name='staticText2',
              parent=self.panel1, pos=wx.Point(0, 26), size=wx.Size(526, 22),
              style=0)

        self.textCtrl2 = TextCtrl(id=wxID_FRAME1TEXTCTRL2, name='textCtrl2',
              parent=self.panel1, pos=wx.Point(531, 26), size=wx.Size(459, 22),
              style=wx.TE_AUTO_URL, value='')

        self.staticText3 = wx.StaticText(id=wxID_FRAME1STATICTEXT3,
              label='masked', name='staticText3', parent=self.panel1,
              pos=wx.Point(0, 53), size=wx.Size(526, 22), style=0)

        self.textCtrl3 = TextCtrl(id=wxID_FRAME1TEXTCTRL3, name='textCtrl3',
              parent=self.panel1, pos=wx.Point(531, 53), size=wx.Size(459, 22),
              style=0, value='')

        self.textCtrl4 = wx.TextCtrl(id=wxID_FRAME1TEXTCTRL4, name='textCtrl4',
              parent=self.panel1, pos=wx.Point(0, 80), size=wx.Size(526, 181),
              style=wx.TE_MULTILINE, value='')

        self._init_sizers()

    def __init__(self, parent):
        self._init_ctrls(parent)
        
        self.textCtrl1.SetMaxLength(50)
        
        self.textCtrl2.log = self.textCtrl4
        self.textCtrl2.SetCtrlParameters(mask = "X{100}", formatcodes = "_S>",
                                        includeChars = '-',
                                        emptyInvalid = False)

        self.textCtrl3.log = self.textCtrl4
        self.textCtrl3.SetCtrlParameters(mask = "X{100}", formatcodes = "_S>",
                                        includeChars = '-',
                                        emptyInvalid = False)

    def OnTextCtrl1KillFocus(self, event):
        self.textCtrl4.AppendText(str(len(event.GetEventObject().GetValue())))
        event.Skip()

    def OnTextCtrl1TextMaxlen(self, event):
        self.textCtrl4.AppendText('maxlenght')
        self.textCtrl4.AppendText(str(len(event.GetEventObject().GetValue())))
        event.Skip()
        


if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = create(None)
    frame.Show()

    app.MainLoop()

 	  	 
