
import wx

def menu1(event):
    menu = wx.Menu('test')
    m = menu.Append(wx.NewId(), 'first')
    m.SetBitmap(wx.ArtProvider.GetBitmap(wx.ART_GO_UP, wx.ART_MENU))
    m = menu.Append(wx.NewId(), 'second')
    m.SetBitmap(wx.ArtProvider.GetBitmap(wx.ART_GO_DOWN, wx.ART_MENU))
    frame.PopupMenu(menu)
    menu.Destroy()

def menu2(event):
    menu = wx.Menu('test')
    m = wx.MenuItem(menu, wx.NewId(), 'first')
    m.SetBitmap(wx.ArtProvider.GetBitmap(wx.ART_GO_UP, wx.ART_MENU))
    menu.AppendItem(m)
    m = wx.MenuItem(menu, wx.NewId(), 'second')
    m.SetBitmap(wx.ArtProvider.GetBitmap(wx.ART_GO_DOWN, wx.ART_MENU))
    menu.AppendItem(m)
    frame.PopupMenu(menu)
    menu.Destroy()

app = wx.App(0)
frame = wx.Frame(None, wx.ID_ANY)
wx.EVT_LEFT_DOWN(frame, menu1)
wx.EVT_RIGHT_DOWN(frame, menu2)
frame.Show()
app.MainLoop()

 	  	 
