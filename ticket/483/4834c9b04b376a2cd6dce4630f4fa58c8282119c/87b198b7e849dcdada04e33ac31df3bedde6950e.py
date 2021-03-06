import wx

try:
    from wx import glcanvas
    haveGLCanvas = True
except ImportError:
    haveGLCanvas = False

try:
    from OpenGL.GL import *
    from OpenGL.GLUT import *
    from OpenGL.GLU import *

    haveOpenGL = True
except ImportError:
    haveOpenGL = False
    
##---------------------------------------
##---------------------------------------
class GLPanePixelSel(glcanvas.GLCanvas):
    def __init__(self, parent, ID = wx.ID_ANY, pos = wx.DefaultPosition, size = wx.DefaultSize,
             style = 0, name = wx.EmptyString, gl_attr = None):
        glcanvas.GLCanvas.__init__(self, parent, ID, pos, size, style = wx.FULL_REPAINT_ON_RESIZE, name = wx.EmptyString, attribList = None)
        self.Bind(wx.EVT_ERASE_BACKGROUND, self.OnEraseBackground)
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.init_fl = False
        self.m_imgHight = size[1]
        self.m_imgWidth = size[0]
        self.SetMinSize([25,25])
        self.m_panHight = 0
        self.m_panWidth = 0
        self.m_zoomH = 1
        self.m_zoomW = 1
        
    def initGL(self):
        ##openGL required!!
        glClearColor(0, 0, 0, 0)
        glShadeModel(GL_FLAT)
        glPixelStorei(GL_UNPACK_ALIGNMENT,1)
        size = self.GetClientSize()
        self.m_panWidth,self.m_panHight = size.width, size.height
        self.m_zoomH = (1.0*self.m_panHight)/self.m_imgHight
        self.m_zoomW = (1.0*self.m_panWidth)/self.m_imgWidth
        if self.GetContext():
            self.SetCurrent()
            glViewport(0, 0, self.m_panWidth,self.m_panHight)
            glMatrixMode (GL_PROJECTION)
            glLoadIdentity ()
            gluOrtho2D (0.0, self.m_panWidth, self.m_panHight, 0.0)
        self.init_fl = True
   
    def onDraw(self):
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT )
        glPushMatrix()
        glPopMatrix()                 
        glFlush()
        self.SwapBuffers()

    def OnPaint(self, event):
        dc = wx.PaintDC(self)##required only on win, otherwise paint will be called continously. see http://www.wxpython.org/docs/api/wx.PaintEvent-class.html and http://groups.google.com/group/wxpython-users/browse_thread/thread/49c9e4b8f7db30c9/ebee891d7114b218?lnk=gst&q=opengl+mac#ebee891d7114b218    
        if not self.GetContext():
            print "No Context!!!"
            return
        if not self.init_fl:
             self.initGL()        
        self.SetCurrent()
        self.onDraw()             

    def OnSize(self, event):
        print 'ogl cought a size event'
        self.originalparent.Update()
        self.originalparent.Refresh()
        self.originalparent.SendSizeEvent()
        size = self.GetClientSize()
        self.m_panWidth,self.m_panHight = size.width, size.height
        self.m_zoomH = (1.0*self.m_panHight)/self.m_imgHight
        self.m_zoomW = (1.0*self.m_panWidth)/self.m_imgWidth
        cont = 0  
        if self.GetContext():
            self.SetCurrent()
            glViewport(0, 0, self.m_panWidth,self.m_panHight)
            glMatrixMode (GL_PROJECTION)
            glLoadIdentity ()
            gluOrtho2D (0.0, self.m_panWidth, self.m_panHight, 0.0)
        event.Skip()
        
    def OnEraseBackground(self, event):
        pass
        
##--------------------------------
class MyFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, "Click for mouseposition", size=(400,300),
                      style=wx.DEFAULT_FRAME_STYLE |wx.NO_FULL_REPAINT_ON_RESIZE)        

        self.panelBackground=wx.Panel(self,-1)
        self.panelBackground.SetBackgroundColour('Goldenrod')        
                
        self.panelright=wx.Panel(self.panelBackground,-1)
        self.panelright.SetBackgroundColour('red')
        self.panelleft=wx.Panel(self.panelBackground,-1)

        self.bitmap1=GLPanePixelSel(self.panelleft, size=(200,100))
        
        self.btn = wx.Button(self.panelleft,-1,'pressme')

        self.Bind(wx.EVT_BUTTON,self.OnButton,self.btn)
        self.large=False
        
        self.sizerOuter=wx.BoxSizer(wx.HORIZONTAL)
        self.sizerModifiable=wx.BoxSizer(wx.HORIZONTAL)
        self.sizerPanelLeft=wx.BoxSizer(wx.VERTICAL)        
        
        self.sizerModifiable.Add(self.panelleft, 1, wx.ALL|wx.EXPAND, 5)
        self.sizerModifiable.Add(self.panelright, 1, wx.ALL|wx.EXPAND, 5)
        self.panelleft.SetSizer(self.sizerPanelLeft)
        self.sizerPanelLeft.Add(self.bitmap1, 5, wx.ALL|wx.EXPAND|wx.SHAPED|wx.ALIGN_CENTER, 5)
        self.sizerPanelLeft.Add(self.btn, 1, wx.ALL|wx.EXPAND|wx.ALIGN_CENTER, 5)
              
        self.panelBackground.SetSizer(self.sizerModifiable)
        self.sizerOuter.Add(self.panelBackground,1,wx.EXPAND, 0)
        self.SetSizer(self.sizerOuter)
        self.sizerOuter.Fit(self)
        self.Layout()
        
    def OnButton(self,evt):
        print "ONButton"
        id = self.sizerModifiable.GetItem(self.panelleft)
        if self.large:
            self.large=False
            id.SetProportion(1)
        else:
            self.large=True
            id.SetProportion(3)
        
        self.panelBackground.SendSizeEvent()
        ## ?? why these does not work?
        #self.Update()
        #self.Refresh()
        

##--------------------------------
app = wx.PySimpleApp()
frame = MyFrame(None)
frame.Show(True)
app.MainLoop()

