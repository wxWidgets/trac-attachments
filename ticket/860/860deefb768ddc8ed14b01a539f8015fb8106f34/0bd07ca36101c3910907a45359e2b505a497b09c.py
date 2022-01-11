import wx.lib.agw.ribbon as ribbon
import wx

app = wx.App()

frame = wx.Frame(None, wx.ID_ANY,"RibbonBar", wx.DefaultPosition,
                 size=(600,600))

panel = wx.Panel(frame, wx.ID_ANY)

boxSizer = wx.BoxSizer(wx.VERTICAL)

ribbonbar = ribbon.RibbonBar(panel, wx.ID_ANY)

ribbon_page = ribbon.RibbonPage(ribbonbar, wx.ID_ANY)

ribbon_panel = ribbon.RibbonPanel(ribbon_page, wx.ID_ANY, "Ribbon Panel",
                                  agwStyle= ribbon.RIBBON_PANEL_STRETCH)
Bitmap = wx.ArtProvider.GetBitmap
files = ribbon.RibbonToolBar(ribbon_panel)

files.AddHybridTool(wx.ID_NEW, Bitmap(wx.ART_NEW,
                                      wx.ART_OTHER, wx.Size(16, 15)))
files.AddTool(wx.ID_ANY, Bitmap(wx.ART_UNDO, wx.ART_OTHER, wx.Size(16, 15)))

files.AddToggleTool(files, wx.ID_ANY, Bitmap(wx.ART_FILE_OPEN, 
                                             wx.ART_OTHER, wx.Size(16, 15)))

boxSizer.Add(ribbonbar, 0, wx.EXPAND)
panel.SetSizer(boxSizer)
ribbonbar.Realize()
frame.Show()

app.MainLoop()
