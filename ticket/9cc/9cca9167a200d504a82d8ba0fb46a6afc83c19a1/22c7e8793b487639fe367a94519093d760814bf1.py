import platform
import sys
import wx
import wx.richtext as richtext

class BugTest(wx.Frame):
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, wx.ID_ANY, title, size = (600, 300), style=wx.DEFAULT_FRAME_STYLE)

        self.txtCtrl = richtext.RichTextCtrl(self, wx.ID_ANY, style=wx.VSCROLL | wx.HSCROLL)

        self.txtAttr = richtext.RichTextAttr()
        # Add whitespace between paragraphs and tabs
        self.txtAttr.SetParagraphSpacingAfter(40)
        self.txtAttr.SetTabs([254, 508, 762])
        self.txtCtrl.SetDefaultStyle(self.txtAttr)

        if sys.platform == 'win32':
            sysVer = platform.win32_ver()[0]
        elif sys.platform == 'darwin':
            sysVer = platform.mac_ver()[0]
        else:
            sysVer = 'unknown'
        
        self.txtCtrl.WriteText("Platform: {0}  OS Version: {1}  Python: {2}  wxPython: {3}".format(sys.platform, sysVer, sys.version[:6].strip(), wx.VERSION_STRING))
        self.txtCtrl.Newline()
        self.txtCtrl.WriteText("If you include a TAB in a line, then clicking the mouse in that line selects the ")
        self.txtCtrl.WriteText("wrong position on that line in the wx.RichTextCtrl() on MacOS.  ")
        self.txtCtrl.WriteText("Both paragraphs below have a TAB character near the start of the first line.")
        self.txtCtrl.Newline()
        # Add left indent with left-hanging first line
        self.txtAttr.SetLeftIndent(0, 254)
        self.txtCtrl.SetDefaultStyle(self.txtAttr)
        self.txtCtrl.WriteText("\tThis is an indented paragraph with a different first line.  The left margin is ")
        self.txtCtrl.WriteText("at 254, which is 1 inch.  The first line indent is 0, so the first line is not indented.  The right margin is 0.  There are no ")
        self.txtCtrl.WriteText("tabs.  So left indent of 1 inch with a left-hanging first line.")
        self.txtCtrl.Newline()
        self.txtCtrl.SetDefaultStyle(self.txtAttr)
        self.txtCtrl.WriteText("1.\tThis is an indented paragraph with a different first line allowing for a number and followed by a tab.  The left margin is ")
        self.txtCtrl.WriteText("at 254, which is 1 inch.  The first line indent is 0, so the first line is not indented.  The right margin is 0.  ")
        self.txtCtrl.WriteText("This paragraph has tabs at 1, 2, and 3 inches.  It has a tab at the beginning.  So left indent of 1 inch ")
        self.txtCtrl.WriteText("with a left-hanging first line and tab suitable for numbering the paragraph.")
        self.txtCtrl.Newline()
        self.txtCtrl.WriteText("")

        self.CenterOnScreen()
        self.Show(True)

class BugTestApp(wx.App):
    def OnInit(self):
        frame = BugTest(None, "RichTextCtrl Bug Test")
        self.SetTopWindow(frame)
        return True

app = BugTestApp()
app.MainLoop()
