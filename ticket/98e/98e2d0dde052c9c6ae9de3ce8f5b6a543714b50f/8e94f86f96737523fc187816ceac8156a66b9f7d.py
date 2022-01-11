#!/usr/bin/env python

import wx
import wx.lib.docview

class MDIFrame(wx.lib.docview.DocMDIParentFrame):
    def __init__(self, manager, frame, id, title,
                 pos = wx.DefaultPosition,
                 size = wx.DefaultSize,
                 style = wx.DEFAULT_FRAME_STYLE,
                 name = 'frame'):
        wx.lib.docview.DocMDIParentFrame.__init__(self, manager, frame, id, title, pos, size, style, name)

        fileMenu = wx.Menu()
        fileMenu.Append(wx.ID_OPEN, '&Open...')
        fileMenu.Append(wx.ID_CLOSE, '&Close')
        fileMenu.AppendSeparator()
        fileMenu.Append(wx.ID_EXIT, 'E&xit')

        menubar = wx.MenuBar()
        menubar.Append(fileMenu, '&File')
        self.SetMenuBar(menubar)

        self.CreateStatusBar()

class Document(wx.lib.docview.Document):
    def OnOpenDocument(self, filename):
        # Pretend we fail to open the document.
        return False

class View(wx.lib.docview.View):
    def OnCreate(self, doc, flags):
        frame = wx.lib.docview.DocMDIChildFrame(doc, self,
                                                wx.GetApp().GetTopWindow(),
                                                -1,
                                                doc.GetFilename())
        self.SetFrame(frame)
        return True


# Application class for DDView
class App(wx.App):
    def __init__(self):
        wx.App.__init__(self)

    def OnInit(self):
        self.SetAppName('Test')

        self.docManager = wx.lib.docview.DocManager(flags = wx.lib.docview.DOC_MDI)

        template = wx.lib.docview.DocTemplate(self.docManager,
                                              'Any',
                                              '*.*',
                                              None,
                                              '',
                                              'Document',
                                              'View',
                                              Document,
                                              View)
        
        self.docManager.AssociateTemplate(template)

        frame = MDIFrame(self.docManager, None, -1, 'Test',  size=(800, 600))
        frame.Show(True)
        self.SetTopWindow(frame)
        return True

    def Open(self, f):
        self.docManager.CreateDocument(f, wx.lib.docview.DOC_SILENT)

if __name__ == '__main__':
    app = App()
    app.MainLoop()

 	  	 
