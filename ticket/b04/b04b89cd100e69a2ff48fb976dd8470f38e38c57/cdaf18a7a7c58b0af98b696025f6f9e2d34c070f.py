# Display html help file on a notebook page

import wx
import wx.html

class Apage(wx.html.HtmlHelpWindow):
    helpfile = 'testdoc.zip'
    def __init__(self, parent):
        wx.html.HtmlHelpWindow.__init__(self, parent, -1)
        helpcontrol = wx.html.HtmlHelpController(style=wx.html.HF_EMBEDDED)
        helpcontrol.SetHelpWindow(self)
        wx.FileSystem.AddHandler(wx.ZipFSHandler())     # add the Zip filesystem
        helpcontrol.AddBook(self.helpfile, 1)
        helpcontrol.DisplayContents()

class Aframe(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, 'Notebook Help viewer', size=(500,500))
        nbook = wx.Notebook(self, -1)
        nbook.AddPage(Apage(parent=nbook), 'Help')


if __name__ == '__main__':
    app = wx.PySimpleApp()
    Aframe().Show()
    app.MainLoop()

