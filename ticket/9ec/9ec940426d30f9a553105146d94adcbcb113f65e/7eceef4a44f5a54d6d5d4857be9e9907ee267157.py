# -*- coding: utf8 -*-
import wx
import wx.richtext as richtext
import os, sys, traceback

class MainWindow(wx.Frame):
    """ This window displays and manipulates a RTFCtrl. """
    def __init__(self,parent,id,title):
        wx.Frame.__init__(self,parent,-1, title, size = (800,800), style=wx.DEFAULT_FRAME_STYLE|wx.NO_FULL_REPAINT_ON_RESIZE)
        self.SetBackgroundColour(wx.WHITE)

        # Menu Bar
        # Create a MenuBar
        menuBar = wx.MenuBar()
        # Build a Menu Object to go into the Menu Bar
        menu1 = wx.Menu()
        MENU_FILE_NEW = wx.NewId()
        menu1.Append(MENU_FILE_NEW, "&New", "Clear the text control")
        menu1.AppendSeparator()
        MENU_FILE_EXIT = wx.NewId()
        menu1.Append(MENU_FILE_EXIT, "E&xit", "Quit Application")
        #Place the Menu Item in the Menu Bar
        menuBar.Append(menu1, "&File")

        menu2 = wx.Menu()
        MENU_FORMAT_BOLD = wx.NewId()
        menu2.Append(MENU_FORMAT_BOLD, "&Bold", "Toggle Bold for the current selection")
        MENU_FORMAT_ITALICS = wx.NewId()
        menu2.Append(MENU_FORMAT_ITALICS, "&Italics", "Toggle Italics for the current selection")
        MENU_FORMAT_UNDERLINE = wx.NewId()
        menu2.Append(MENU_FORMAT_UNDERLINE, "&Underline", "Toggle Underline for the current selection")
        menuBar.Append(menu2, "F&ormat")

        self.SetMenuBar(menuBar)
        #Define Events for the Menu Items
        self.Bind(wx.EVT_MENU, self.OnClear, id=MENU_FILE_NEW)
        self.Bind(wx.EVT_MENU, self.OnBold, id=MENU_FORMAT_BOLD)
        self.Bind(wx.EVT_MENU, self.OnItalics, id=MENU_FORMAT_ITALICS)
        self.Bind(wx.EVT_MENU, self.OnUnderline, id=MENU_FORMAT_UNDERLINE)
        self.Bind(wx.EVT_MENU, self.OnClose, id=MENU_FILE_EXIT)

        mainSizer = wx.BoxSizer(wx.VERTICAL)

        self.txtCtrl = richtext.RichTextCtrl(self, -1, style=wx.VSCROLL|wx.HSCROLL)
        mainSizer.Add(self.txtCtrl, 1, wx.EXPAND | wx.ALL, 5)
        wx.CallAfter(self.txtCtrl.SetFocus)

        self.SetSizer(mainSizer)
        self.SetAutoLayout(True)
        self.Layout()
        self.CenterOnScreen()
        self.OnClear(None)
        self.Show(True)

    def OnClear(self, event):
        self.txtCtrl.Freeze()
        self.txtCtrl.BeginSuppressUndo()
        self.txtCtrl.Clear()

        tmpStyle = richtext.RichTextAttr()
        tmpStyle.SetFontFaceName('Courier New')
        tmpStyle.SetFontSize(12)
        tmpStyle.SetTextColour(wx.Colour(255, 0, 255))
        self.txtCtrl.SetBasicStyle(tmpStyle)
        self.txtCtrl.SetDefaultStyle(tmpStyle)

        version = wx.__version__
        self.txtCtrl.WriteText("wx Version:  %s" % (version, ))
        self.txtCtrl.Newline()
        self.txtCtrl.Newline()
        self.txtCtrl.WriteText('Make a selection and apply underlining.  Then move your selection.')
        self.txtCtrl.Newline()
        self.txtCtrl.Newline()
        self.txtCtrl.WriteText("Don't see any underlining?  Try making a DIFFERENT selection and underling that.  ")
        self.txtCtrl.WriteText("The FIRST selection's formatting shows up when the SECOND selection is formatted!")
        self.txtCtrl.Newline()
        self.txtCtrl.Newline()
        self.txtCtrl.WriteText('Underlining is removed immediately.  It is just not applied immediately.')
        self.txtCtrl.EndSuppressUndo()
        self.txtCtrl.Thaw()
      
    def OnBold(self, event):
        self.txtCtrl.ApplyBoldToSelection()

    def OnItalics(self, event):
        self.txtCtrl.ApplyItalicToSelection()

    def OnUnderline(self, event):
        self.txtCtrl.ApplyUnderlineToSelection()

#        self.txtCtrl.Update()
#        self.txtCtrl.Refresh()
#        self.txtCtrl.UpdateWindowUI()

    def OnClose(self, event):
        self.Close()


class MyApp(wx.App):
    def OnInit(self):
        frame = MainWindow(None, -1, "wxRichTextCtrl Format Problem")
        self.SetTopWindow(frame)
        return True

app = MyApp(0)
app.MainLoop()
