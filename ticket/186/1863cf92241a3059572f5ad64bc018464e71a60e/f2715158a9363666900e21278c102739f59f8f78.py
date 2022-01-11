import wx

class Frame(wx.Frame):
    def __init__(self, *args, **kwargs):
        super(Frame, self).__init__(*args, **kwargs)
        bar = wx.MenuBar()
        bitmaps = [wx.ArtProvider.GetBitmap(bitmapId, wx.ART_MENU, (16,16)) \
                   for bitmapId in wx.ART_TIP, wx.ART_GO_UP]
        for menuIndex, bitmapArgs in enumerate([(None, None), 
                                                (bitmaps[0], None), bitmaps]):
            self.addMenu(bar, 'menu %d'%menuIndex, *bitmapArgs)
        self.SetMenuBar(bar)

    def addMenu(self, bar, title, bitmap1, bitmap2):
        menu = wx.Menu()
        for menuItemIndex in range(3):
            self.addMenuItem(menu, 'radio %d'%menuItemIndex, bitmap1, bitmap2)
        bar.Append(menu, title)

    def addMenuItem(self, menu, text, bitmap1, bitmap2):
        item = wx.MenuItem(menu, id=wx.NewId(), text=text, kind=wx.ITEM_RADIO)
        if bitmap1:
            if bitmap2:
                item.SetBitmaps(bitmap1, bitmap2)
            else:
                item.SetBitmap(bitmap1)
        menu.AppendItem(item)


app = wx.App(False)
frame = Frame(None)
frame.Show()
app.MainLoop()

 	  	 
