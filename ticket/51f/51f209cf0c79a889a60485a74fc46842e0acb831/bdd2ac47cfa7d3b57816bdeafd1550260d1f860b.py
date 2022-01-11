import wx

[wxID_FRAME1, wxID_FRAME1BUTTON1, wxID_FRAME1BUTTON2, wxID_FRAME1COMBOBOX1, 
 wxID_FRAME1COMBOBOX2, wxID_FRAME1COMBOBOX3, wxID_FRAME1PANEL1, 
 wxID_FRAME1STATICTEXT1, wxID_FRAME1STATICTEXT2, wxID_FRAME1STATICTEXT3, 
] = [wx.NewId() for _init_ctrls in range(10)]

class Frame1(wx.Frame):
    def _init_coll_flexGridSizer1_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticText1, 0, border=0, flag=0)
        parent.AddWindow(self.comboBox1, 0, border=0, flag=0)
        parent.AddWindow(self.staticText2, 0, border=0, flag=0)
        parent.AddWindow(self.comboBox2, 0, border=0, flag=0)
        parent.AddWindow(self.staticText3, 0, border=0, flag=0)
        parent.AddWindow(self.comboBox3, 0, border=0, flag=0)

    def _init_coll_boxSizer1_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.panel1, 1, border=0, flag=wx.EXPAND)

    def _init_sizers(self):
        # generated method, don't edit
        self.boxSizer1 = wx.BoxSizer(orient=wx.VERTICAL)

        self.flexGridSizer1 = wx.FlexGridSizer(cols=2, hgap=2, rows=3, vgap=10)

        self._init_coll_boxSizer1_Items(self.boxSizer1)
        self._init_coll_flexGridSizer1_Items(self.flexGridSizer1)

        self.SetSizer(self.boxSizer1)
        self.panel1.SetSizer(self.flexGridSizer1)

    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME1, name='', parent=prnt,
              pos=wx.Point(255, 212), size=wx.Size(400, 250),
              style=wx.DEFAULT_FRAME_STYLE, title='Frame1')
        self.SetClientSize(wx.Size(392, 223))

        self.panel1 = wx.Panel(id=wxID_FRAME1PANEL1, name='panel1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(392, 223),
              style=wx.TAB_TRAVERSAL)

        self.comboBox1 = wx.ComboBox(choices=[], id=wxID_FRAME1COMBOBOX1,
              name='comboBox1', parent=self.panel1, pos=wx.Point(56, 0),
              size=wx.Size(130, 21), style=0, value='comboBox1')

        self.staticText1 = wx.StaticText(id=wxID_FRAME1STATICTEXT1,
              label='staticText1', name='staticText1', parent=self.panel1,
              pos=wx.Point(0, 0), size=wx.Size(54, 13), style=0)

        self.staticText2 = wx.StaticText(id=wxID_FRAME1STATICTEXT2,
              label='staticText2', name='staticText2', parent=self.panel1,
              pos=wx.Point(0, 31), size=wx.Size(54, 13), style=0)

        self.staticText3 = wx.StaticText(id=wxID_FRAME1STATICTEXT3,
              label='staticText3', name='staticText3', parent=self.panel1,
              pos=wx.Point(0, 62), size=wx.Size(54, 13), style=0)

        self.comboBox2 = wx.ComboBox(choices=[], id=wxID_FRAME1COMBOBOX2,
              name='comboBox2', parent=self.panel1, pos=wx.Point(56, 31),
              size=wx.Size(130, 21), style=0, value='comboBox2')

        self.comboBox3 = wx.ComboBox(choices=[], id=wxID_FRAME1COMBOBOX3,
              name='comboBox3', parent=self.panel1, pos=wx.Point(56, 62),
              size=wx.Size(130, 21), style=0, value='comboBox3')

        self.button1 = wx.Button(id=wxID_FRAME1BUTTON1, label='button1',
              name='button1', parent=self.panel1, pos=wx.Point(8, 96),
              size=wx.Size(75, 23), style=0)
        self.button1.Bind(wx.EVT_BUTTON, self.OnButton1Button,
              id=wxID_FRAME1BUTTON1)

        self.button2 = wx.Button(id=wxID_FRAME1BUTTON2, label='button2',
              name='button2', parent=self.panel1, pos=wx.Point(104, 96),
              size=wx.Size(75, 23), style=0)
        self.button2.Bind(wx.EVT_BUTTON, self.OnButton2Button,
              id=wxID_FRAME1BUTTON2)

        self._init_sizers()

    def __init__(self, parent):
        self._init_ctrls(parent)

    def OnButton1Button(self, event):
        self.comboBox2.Destroy()
        self.comboBox2 = wx.ComboBox(choices=[], id=wxID_FRAME1COMBOBOX2,
              name='comboBox2', parent=self.panel1, pos=wx.Point(56, 31),
              size=wx.Size(130, 21), style=wx.CB_SIMPLE, value='comboBox2')
        self.flexGridSizer1.Insert(3,self.comboBox2,border=0, flag=0)
        self.comboBox3.Destroy()
        self.comboBox3 = wx.ComboBox(choices=[], id=wxID_FRAME1COMBOBOX3,
              name='comboBox3', parent=self.panel1, pos=wx.Point(56, 62),
              size=wx.Size(130, 21), style=wx.CB_SIMPLE, value='comboBox3')
        self.flexGridSizer1.Insert(5,self.comboBox3,border=0, flag=0)
        self.flexGridSizer1.Layout()
        event.Skip()

    def OnButton2Button(self, event):
        for i in range(0,6):
            print self.flexGridSizer1.GetItem(i).GetWindow().GetName()
        print "all right"

app = wx.App()
frame = Frame1(None)
frame.Show(1);frame.Hide();frame.Show(1);
app.MainLoop()

 	  	 
