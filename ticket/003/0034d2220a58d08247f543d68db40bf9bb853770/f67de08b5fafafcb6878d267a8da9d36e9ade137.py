
import wx
import wx.lib.agw.ultimatelistctrl as ULC

class MyFrame(wx.Frame):

    def __init__(self, parent):

        wx.Frame.__init__(self, parent, wx.ID_ANY, "Insert First Demo")
        
        def create_list(name):
            if hasattr(self, "list"):
                self.list.Destroy()
            if name == "wx.ListCtrl":
                self.list = wx.ListCtrl(
                    self.panel, style=wx.LC_REPORT|wx.LC_HRULES)
            elif name == "case 1":
                self.list = ULC.UltimateListCtrl(
                    self.panel,
                    agwStyle=wx.LC_REPORT
                    |wx.LC_HRULES
                    )
            elif name in ("case 2", "case 3"):
                self.Hide()
                self.list = ULC.UltimateListCtrl(
                    self.panel,
                    agwStyle=wx.LC_REPORT
                    |ULC.ULC_SINGLE_SEL
                    |ULC.ULC_HAS_VARIABLE_ROW_HEIGHT
                    |wx.LC_HRULES
                    )

            self.list.InsertColumn(0, "Column 1")
            self.list.InsertColumn(1, "Column 2")

            self.counter = 0

            for i in xrange(1, 5):
                insert_item()
            
            self.sizer.Prepend(self.list, 1, wx.ALL|wx.EXPAND)
            self.sizer.RecalcSizes()
            self.Show()
            if name == "case 3":
                insert_item(True)
            
        
        def insert_item(win=None):
            index = self.list.InsertStringItem(0, "Item %i" % self.counter)
            text = "Sub-item %i" % self.counter
            self.list.SetStringItem(index, 1, "" if win else text)
            if win:
                button = wx.Button(self.list, label=text)
                self.list.SetItemWindow(index, col=1, wnd=button, expand=True)
            self.counter += 1

        self.panel = wx.Panel(self)
        
        lc_button = wx.Button(self.panel, label="wx.ListCtrl")
        lc_button.Bind(wx.EVT_BUTTON,
                       lambda _: create_list("wx.ListCtrl"))
        c1_button = wx.Button(self.panel, label="case 1")
        c1_button.Bind(wx.EVT_BUTTON,
                        lambda _: create_list("case 1"))
        c2_button = wx.Button(self.panel, label="case 2")
        c2_button.Bind(wx.EVT_BUTTON,
                        lambda _: create_list("case 2"))
        c3_button = wx.Button(self.panel, label="case 3")
        c3_button.Bind(wx.EVT_BUTTON,
                        lambda _: create_list("case 3"))
        insert_button = wx.Button(self.panel, label="insert")
        insert_button.Bind(wx.EVT_BUTTON, lambda _: insert_item())
        
        buttons = wx.BoxSizer(wx.HORIZONTAL)
        buttons.AddMany([lc_button, c1_button, c2_button, c3_button, insert_button])

        self.sizer = wx.BoxSizer(wx.VERTICAL)
        
        self.sizer.Add(buttons, 0)
        create_list("wx.ListCtrl")
        
        self.panel.SetSizer(self.sizer)


# our normal wxApp-derived class, as usual

app = wx.App(0)

frame = MyFrame(None)
app.SetTopWindow(frame)
frame.Center()
frame.Show()

app.MainLoop()
