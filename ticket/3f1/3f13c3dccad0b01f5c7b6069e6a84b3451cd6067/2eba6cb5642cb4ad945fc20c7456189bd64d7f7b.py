# import wxPython and necessary modules
import wx
import wx.richtext as richtext

# import win32 for determining GDI resources
from win32api import GetCurrentProcess
from win32con import GR_GDIOBJECTS
from win32process import GetGuiResources

def GdiReport(ctrl, desc):
   numGdi = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS)
   ctrl.WriteText("%s = %d\n" % (desc, numGdi))
   
class MainWindow(wx.Frame):

   """ This window displays and manipulates a RTFCtrl. """
   def __init__(self,parent,id,title):
      wx.Frame.__init__(self,parent,-1, title, size = (800,800), style=wx.DEFAULT_FRAME_STYLE|wx.NO_FULL_REPAINT_ON_RESIZE)
      self.SetBackgroundColour(wx.WHITE)
      self.CreateStatusBar()

      # Menu Bar
      menuBar = wx.MenuBar()
      menu1 = wx.Menu()
      MENU_FILE_NEW = wx.NewId()
      menu1.Append(MENU_FILE_NEW, "&New", "Clear the text control")
      menu1.AppendSeparator()
      
      MENU_FILE_LOAD_PROG = wx.NewId()
      menu1.Append(MENU_FILE_LOAD_PROG, "Populate &Programmatically", "Populate the text control programmatically")
      menu1.AppendSeparator()

      MENU_FILE_EXIT = wx.NewId()
      menu1.Append(MENU_FILE_EXIT, "E&xit", "Quit Application")
      #Place the Menu Item in the Menu Bar
      menuBar.Append(menu1, "&File")

      self.SetMenuBar(menuBar)
      #Define Events for the Menu Items
      self.Bind(wx.EVT_MENU, self.OnClear, id=MENU_FILE_NEW)
      self.Bind(wx.EVT_MENU, self.OnLoadProg, id=MENU_FILE_LOAD_PROG)
      self.Bind(wx.EVT_MENU, self.OnClose, id=MENU_FILE_EXIT)

      mainSizer = wx.BoxSizer(wx.VERTICAL)

      checkSizer = wx.BoxSizer(wx.HORIZONTAL)

      self.cbUsewxRichTextMethods = wx.CheckBox(self, -1, "Use wxRichTextCtrl Methods")
      checkSizer.Add(self.cbUsewxRichTextMethods, 2, wx.EXPAND | wx.ALL, 5)
      self.cbUsewxRichTextMethods.SetValue(True)

      self.cbUseNewline = wx.CheckBox(self, -1, "Use Newline()")
      checkSizer.Add(self.cbUseNewline, 1, wx.EXPAND | wx.ALL, 5)
      self.cbUseNewline.SetValue(True)

      self.cbUseBold = wx.CheckBox(self, -1, "Use Bold")
      checkSizer.Add(self.cbUseBold, 1, wx.EXPAND | wx.ALL, 5)
      self.cbUseBold.SetValue(True)

      self.cbUseItalic = wx.CheckBox(self, -1, "Use Italics")
      checkSizer.Add(self.cbUseItalic, 1, wx.EXPAND | wx.ALL, 5)
      self.cbUseItalic.SetValue(True)

      self.cbUseFontFace = wx.CheckBox(self, -1, "Change Font Face")
      checkSizer.Add(self.cbUseFontFace, 1, wx.EXPAND | wx.ALL, 5)
      self.cbUseFontFace.SetValue(True)

      self.cbUseFontSize = wx.CheckBox(self, -1, "Change Font Size")
      checkSizer.Add(self.cbUseFontSize, 1, wx.EXPAND | wx.ALL, 5)
      self.cbUseFontSize.SetValue(True)

      mainSizer.Add(checkSizer, 0, wx.EXPAND)
      
      self.txtCtrl = richtext.RichTextCtrl(self, -1, style=wx.VSCROLL|wx.HSCROLL)
      mainSizer.Add(self.txtCtrl, 10, wx.EXPAND | wx.ALL, 5)
      wx.CallAfter(self.txtCtrl.SetFocus)

      fontColor = wx.Colour(0, 0, 0)
      fontBgColor = wx.Colour(255, 255, 255)
      fontFace = 'Courier New'
      fontSize = 12
      self.textAttr = richtext.RichTextAttr()
      self.SetFontStyle(fontColor = fontColor, fontBgColor = fontBgColor, fontFace = fontFace, fontSize = fontSize,
                        fontBold = False, fontItalic = False, fontUnderline = False)

      self.txtCtrl.WriteText("Select the options you'd like to test using the check boxes above.")
      self.txtCtrl.Newline()
      self.txtCtrl.Newline()
      self.txtCtrl.WriteText("Select File > Populate Programmatically.  This will populate the wxRichTextCtrl with sample text.  (This may take a moment.)")
      self.txtCtrl.Newline()
      self.txtCtrl.Newline()
      self.txtCtrl.WriteText("Notice the number of GDI Resources used, as reported at the top and at the bottom of the report.")
      self.txtCtrl.Newline()
      self.txtCtrl.Newline()

      self.txtCtrl.Freeze()
      self.txtCtrl.BeginSuppressUndo()

      self.txtCtrl.EndSuppressUndo()
      self.txtCtrl.Thaw()

      self.SetSizer(mainSizer)
      self.SetAutoLayout(True)
      self.Layout()
      self.CenterOnScreen()
      self.Show(True)

   def SetFontStyle(self, fontColor = None, fontBgColor = None, fontFace = None, fontSize = None,
                    fontBold = None, fontItalic = None, fontUnderline = None):
      if fontColor:
         self.textAttr.SetTextColour(fontColor)
      if fontBgColor:
         self.textAttr.SetBackgroundColour(fontBgColor)
      if fontFace:
         self.textAttr.SetFontFaceName(fontFace)
      if fontSize:
         self.textAttr.SetFontSize(fontSize)
      if fontBold != None:
         if fontBold:
            self.textAttr.SetFontWeight(wx.FONTWEIGHT_BOLD)
         else:
            self.textAttr.SetFontWeight(wx.FONTWEIGHT_NORMAL)
      if fontItalic != None:
         if fontItalic:
            self.textAttr.SetFontStyle(wx.FONTSTYLE_ITALIC)
         else:
            self.textAttr.SetFontStyle(wx.FONTSTYLE_NORMAL)
      if fontUnderline != None:
         if fontUnderline:
            self.textAttr.SetFontUnderlined(True)
         else:
            self.textAttr.SetFontUnderlined(False)
      self.txtCtrl.SetDefaultStyle(self.textAttr)
      
   def OnClear(self, event):
      self.txtCtrl.Freeze()
      self.txtCtrl.BeginSuppressUndo()
      self.txtCtrl.Clear()
      GdiReport(self.txtCtrl, "GDI Resources used, when the control is almost empty")
      self.txtCtrl.EndSuppressUndo()
      self.txtCtrl.Thaw()
      
   def OnLoadProg(self, event):

      # When the RTC is empty, this app uses 43 GDI resources.

      UsewxRichTextCtrlMethods = self.cbUsewxRichTextMethods.IsChecked()
      NumIterations = 1000
      UseNewline    = self.cbUseNewline.IsChecked()
      UseBold       = self.cbUseBold.IsChecked()
      UseItalics    = self.cbUseItalic.IsChecked()
      UseFontFace   = self.cbUseFontFace.IsChecked()
      UseFontSize   = self.cbUseFontSize.IsChecked()
      
      self.txtCtrl.Freeze()
      self.txtCtrl.BeginSuppressUndo()
      self.txtCtrl.Clear()

      GdiReport(self.txtCtrl, "GDI Resources used, before")
      
      self.SetFontStyle(fontSize = 14)
      self.txtCtrl.WriteText('This is the RichTextCtrl from %s.' % wx.version())
      if UseNewline:
         self.txtCtrl.Newline()
      else:
         self.txtCtrl.WriteText('\n')
      self.SetFontStyle(fontSize = 12)

      for x in range(NumIterations):
         self.txtCtrl.WriteText('Line %5d: ' % (x + 1))
         self.txtCtrl.WriteText('Normal ')
         if UseBold:
            if UsewxRichTextCtrlMethods:
               self.txtCtrl.BeginBold()
            else:
               self.SetFontStyle(fontBold = True)
            self.txtCtrl.WriteText('Bold ')
            if UsewxRichTextCtrlMethods:
               self.txtCtrl.EndBold()
            else:
               self.SetFontStyle(fontBold = False)
         else:
            self.txtCtrl.WriteText('NOT Bold ')
         if UseItalics:
            if UsewxRichTextCtrlMethods:
               self.txtCtrl.BeginItalic()
            else:
               self.SetFontStyle(fontItalic = True)
            self.txtCtrl.WriteText('Italics ')
            if UsewxRichTextCtrlMethods:
               self.txtCtrl.EndItalic()
            else:
               self.SetFontStyle(fontItalic = False)
         else:
            self.txtCtrl.WriteText('NOT Italics ')
         if UseFontFace:
            self.SetFontStyle(fontFace = 'Times New Roman')
            self.txtCtrl.WriteText('Face ')
            self.SetFontStyle(fontFace = 'Courier New')
         if UseFontSize:
            self.SetFontStyle(fontSize = 16)
            self.txtCtrl.WriteText('Large ')
            self.SetFontStyle(fontSize = 12)
         self.txtCtrl.WriteText('Normal')

         if UseNewline:
            self.txtCtrl.Newline()
         else:
            self.txtCtrl.WriteText('\n')

      self.txtCtrl.EndSuppressUndo()
      self.txtCtrl.Thaw()

      GdiReport(self.txtCtrl, "GDI Resources used, after")

   def OnClose(self, event):
      self.Close()

class MyApp(wx.App):
   def OnInit(self):
      frame = MainWindow(None, -1, "RichTextCtrl Test")
      self.SetTopWindow(frame)
      return True


app = MyApp(0)
app.MainLoop()
