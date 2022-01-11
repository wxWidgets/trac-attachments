#!/usr/bin/python
'''
+-------------------------------------------------------------------+
| A Python module           Created by Bruce vanNorman on 18.Jun.10 |
| A rewrite of the CPUXA-IP server {VB-6 ==> Python}                |
| purpose: to connect DMXLeopard client applications to the ADI     |
|   Ocelot home automation server                                   |
| This module is the main entry point and provides the              |
|   initialization, termination, event handlers, and GUI            |
|   support for the dmx_server application                          |
|                                                                   |
| 14.Aug.10: v3.1 added logging                                     |
| - placed GUI on a separate thread from GIL (main) thread          |
| - gbl.TheApp.Yield's added to ocelot & inet control               |
| - separated GUI thread from ocelot & inet client threads          |
+-------------------------------------------------------------------+
'''
Version = '3.1.5'
import wx
from wx import App
from collections import deque
import pxa_wx, dmx, ocelot_control, ocelot, inet_server
import pxa_global as gbl
import sys, ConfigParser, glob, os, copy, time, thread

TheFrame = None
TextArea = None
TextLines = 0
TextLineHeight = 0
TextLineLimit = 0
TextList = [] # --- text message ring buffer
TEXT_MAX = 99
TextTail = 0  # --- first unused index
TextChangeSw = False

## === public data and call backs ===================================
RunSw = False   #--- the global termination switch

TheConfig = None
ConfigFrame = None
ControlFolder = ''
ControlFile = ''
ControlPort = ''
SERVICE_MIN =  1000
SERVICE_MAX = 20000
ControlServiceNum = 1000
NewServiceNum = 1000
Top =    -1  # --- main frame dimensions
Left =   -1
Height = -1
Width =  -1

## === initialization code ==========================================
def LoadIniControl ():
  global TheConfig, ControlFolder, ControlFile, ControlPort
  global ControlServiceNum, Top, Left, Width, Height
  # --- process config (ini) file and start threads -----------------
  TheConfig = ConfigParser.SafeConfigParser()
  ConfigFileName = sys.path[0] + '/pxa_server.ini'
  gbl.LogInfo('opening %s'%ConfigFileName)
  TheConfig.read(ConfigFileName)
  
  Section = 'geometry'
  if TheConfig.has_section(Section):
    OptionList = TheConfig.options(Section)
    for Option in OptionList:
      if Option == 'top':
        Top = TheConfig.getint(Section, 'top')
      elif Option == 'left':
        Left = TheConfig.getint(Section, 'left')
      elif Option == 'height':
        Height = TheConfig.getint(Section, 'height')
      elif Option == 'width':
        Width = TheConfig.getint(Section, 'width')
        
  Section = 'control'
  if TheConfig.has_section(Section):
    OptionList = TheConfig.options(Section)
    for Option in OptionList:
      if Option == 'folder':
        ControlFolder = TheConfig.get(Section, 'folder')
      elif Option == 'file':
        ControlFile = TheConfig.get(Section, 'file')
      elif Option == 'port':
        ControlPort = TheConfig.get(Section, 'port')
      elif Option == 'service':
        ControlServiceNum = int(TheConfig.get(Section, 'service'))
  gbl.LogInfo('Control: folder= %s, file= %s'%(
    ControlFolder, ControlFile))
  dmx.ProcessFile('%s/%s.dmx'%(ControlFolder, ControlFile))
  gbl.LogInfo('pgm version= %i. Ports: serial= %s, Inet= %i'%(
    dmx.PgmVersion, ControlPort, ControlServiceNum))

def SaveIniControl():
  global TheFrame, TheConfig, Top, Left, Height, Width
  global ControlFolder, ControlFile, ControlPort, ControlServiceNum
  #TheConfig = ConfigParser.SafeConfigParser()
    # --- save configuration ------------------------------------------
  Section = 'geometry'
  if TheFrame <> None: Left, Top = TheFrame.GetPosition()
  gbl.LogInfo('recording position: top %i x left %i'%(Top, Left))
  TheConfig.set(Section, 'top',     str(Top))
  TheConfig.set(Section, 'left',    str(Left))
  if TheFrame <> None: Width, Height = TheFrame.GetSize()
  gbl.LogInfo('recording size W %i x H %i'%(Width, Height))
  TheConfig.set(Section, 'height',  str(Height))
  TheConfig.set(Section, 'width',   str(Width))
  
  Section = 'control'
  TheConfig.set(Section, 'folder',  ControlFolder)
  TheConfig.set(Section, 'file',    ControlFile)
  TheConfig.set(Section, 'port',    ControlPort)
  TheConfig.set(Section, 'service', str(ControlServiceNum))
  
  hFile = open(sys.path[0] + 'pxa_server.ini','w')
  TheConfig.write(hFile)
  hFile.close()
  gbl.LogInfo('configuration saved')
  
## === GUI events ===================================================
def SaveConfig(Event):
  global ConfigFrame, ControlFolder, ControlFile, ControlPort
  global ControlServiceNum, NewServiceNum
  CurrFile = ConfigFrame.label_curr_file.GetLabel()
  if CurrFile <> '':
    ControlFolder = ConfigFrame.label_curr_folder.GetLabel()
    ControlFile   = ConfigFrame.label_curr_file.GetLabel()
    dmx.ProcessFile('%s/%s.dmx'%(ControlFolder, ControlFile))
  if ControlPort <> ConfigFrame.label_curr_port.GetLabel():
    ocelot_control.Stop()
    ControlPort = ConfigFrame.label_curr_port.GetLabel()
    ocelot_control.Start(ControlPort)
  if NewServiceNum <> ControlServiceNum:
    # need to stop and restart inet, clients will auto restart
    ControlServiceNum = NewServiceNum
  ConfigFrame.Hide()

def BailConfig(Event):
  global ConfigFrame
  ConfigFrame.Hide()
  
def HomeConfig(Event):
  global ConfigFrame
  if sys.platform == 'linux2':
    ConfigFrame.label_curr_folder.SetLabel(os.getenv('HOME'))
  else: # hope for Windows
    Drive = os.getenv('HOMEDRIVE')
    Path = os.getenv('HOMEPATH')
    Home = '%s\\%s\\%s'%(Drive, Path, 'My Documents')
    gbl.LogInfo('setting home to %s'%Home)
    ConfigFrame.label_curr_folder.SetLabel(Home)
  ResetConfigDirnames()
  ResetConfigFilenames()
  
def UpConfig(Event):
  global ConfigFrame
  CurrDir = ConfigFrame.label_curr_folder.GetLabel()
  ParentDir = os.path.dirname(CurrDir)
  ConfigFrame.label_curr_folder.SetLabel(ParentDir)
  ResetConfigDirnames()
  ResetConfigFilenames()

def ChoiceConfig(Event):
  global ConfigFrame
  gbl.LogInfo('choice event')
  TheChoice = Event.GetEventObject()
  if TheChoice == ConfigFrame.choice_folder:
    Selection = TheChoice.GetStringSelection()
    ConfigFrame.label_curr_folder.SetLabel(Selection)
    ResetConfigDirnames()
    ResetConfigFilenames()
    gbl.LogInfo('chose folder %s'%Selection)
  elif TheChoice == ConfigFrame.choice_file:
    Selection = TheChoice.GetStringSelection()
    ConfigFrame.label_curr_file.SetLabel(Selection)
    gbl.LogInfo('chose file %s'%Selection)
  elif TheChoice == ConfigFrame.choice_port:
    Selection = TheChoice.GetStringSelection()
    ConfigFrame.label_curr_port.SetLabel(Selection)
    gbl.LogInfo('chose port %s'%Selection)
  else:
    gbl.LogInfo('chose ???')

def StopPoll(Event):
  ocelot_control.Stop()

def KickPoll(Event):
  pass

def StartPoll(Event):
  ocelot_control.Start()

def SelectXctlFile(Event):
  global ConfigFrame, ControlServiceNum, NewServiceNum
  global TheConfig, ControlFolder, ControlFile, ControlPort
  ConfigFrame.label_curr_config.SetLabel(
  'Current configureation: ' +
    ControlFolder + '/' + ControlFile +
    '.dmx on port ' + ControlPort)
  
  if ControlFolder == '':
    ControlFolder = os.getenv('HOME')
  ConfigFrame.label_curr_folder.SetLabel(ControlFolder)
  ResetConfigDirnames()
  ResetConfigFilenames()
  ConfigFrame.label_curr_file.SetLabel(ControlFile)

  ConfigFrame.label_curr_port.SetLabel(ControlPort)
  Choice = ConfigFrame.choice_port
  Choice.Clear()
  if sys.platform == 'linux2':
    FullPortList = glob.glob('/dev/tty*')
    for Port in FullPortList:
      Temp, SimpleName = os.path.split(Port)
      Choice.Append(SimpleName)
  else: # hope this is windows
    import scanwin32
    for Port, Desc, Hwid in scanwin32.comports():
      gbl.LogInfo('%s: %s (%s)'%(Port, Desc, Hwid))
      Choice.Append(Port)
  
  NewServiceNum = ControlServiceNum
  DisplayServiceNum()
  ConfigFrame.Show()

def ExitApp(Event):
  if gbl.ShutdownSw:
    gbl.LogDebug('recursive shutdown')
    sys.exit()
  gbl.ShutdownSw = True
  gbl.LogInfo('starting shutdown')
  PxaServerStop()
  GuiStop()

def Resize(Event):
  global TheFrame, TextArea, TextLineLimit, TextLineHeight, TextList
  global Top, Left, Height, Width
  global TextChangeSw
  if TextArea <> None:
    Width, Height = TheFrame.GetSize()
    #print 'define text area %i x %i'%(Width, Height)
    if sys.platform == 'linux2':
      Height -= 76
    else:
      Height -= 100
    TextArea.SetSize((Width, Height))
    TextLineLimit = Height / TextLineHeight
    StatW = (Width / 3) - 8
    TheFrame.dmx_statusbar.SetStatusWidths([StatW, StatW, StatW])
    TextChangeSw = True
    DisplayTextList()
    DisplayStatus()
    #GuiReport('resize: line count %i, limit %i'%(TextArea.GetNumberOfLines(), TextLineLimit))

def UpServiceNum(Event):
  global NewServiceNum
  if NewServiceNum < SERVICE_MAX:
    NewServiceNum += 1
    DisplayServiceNum()

def DownServiceNum(Event):
  global NewServiceNum
  if NewServiceNum > SERVICE_MIN:
    NewServiceNum -= 1
    DisplayServiceNum()
    
PulseCount = 0
PULSE_DURATION = 3
def Pulse(Event):
  global PulseCount, ControlPort
  DisplayStatus()
  if len(gbl.MsgQ): DisplayTextList()
  #wx.Yield() # this call is recursive
  PulseCount += 1
   
## === GUI support ==================================================
def DisplayStatus():
  global TheFrame
  I = ocelot_control.PollCount
  TheFrame.dmx_statusbar.SetStatusText('Ocelot: %i polls'%I, 0)
  TheFrame.dmx_statusbar.SetStatusText('Ocelot: %s poll %0.2f sec.'%(
    ocelot.StatusMsg(), ocelot_control.PollInterval),
    1)
  TheFrame.dmx_statusbar.SetStatusText('Inet: %s poll %0.2f sec.'%(
    inet_server.StatusMsg(), inet_server.PollInterval),
    2)

def DisplayTextList():
  global TextList, TextTail, TextChangeSw, TextArea, TextLineLimit
  #PostLock.acquire()
  while len(gbl.MsgQ):
    Msg = gbl.MsgQ.popleft()
    TextList[TextTail] = Msg
    if TextTail >= TEXT_MAX:
      TextTail = 0
    else:
      TextTail += 1
    #print 'TextTail is now %i'%TextTail
    TextChangeSw = True

  if TextLineLimit: # then initialized
    if TextChangeSw:
      TextHead = TextTail - TextLineLimit + 1
      if TextHead < 0:
        TextHead += TEXT_MAX
      #print 'text head is %i'%TextHead
      TextArea.Clear()
      I = TextHead
      while True:
        #print 'showing %i <%s>'%(I, TextList[I])
        TextArea.AppendText(TextList[I] + '\n')
        I += 1
        if I >= TEXT_MAX:
          I = 0
        if I == TextTail: break
    TextChangeSw = False
  #else: print 'TextArea not ready'
  #PostLock.release()
  
def ResetConfigFilenames():
  global ConfigFrame
  WorkingFolder = ConfigFrame.label_curr_folder.GetLabel()
  ConfigFrame.label_curr_file.SetLabel('')
  Choice = ConfigFrame.choice_file
  Choice.Clear()
  FullFileList = glob.glob(WorkingFolder + '/*.dmx')
  FullFileList.sort()
  FileList = []
  for File in FullFileList:
    Temp, FileName = os.path.split(File)
    NameList = FileName.split('.')
    Choice.Append(NameList[0])

def ResetConfigDirnames():
  global ConfigFrame
  WorkingFolder = ConfigFrame.label_curr_folder.GetLabel()
  ConfigFrame.label_curr_file.SetLabel('')
  Choice = ConfigFrame.choice_folder
  Choice.Clear()
  FullNameList = glob.glob(WorkingFolder + '/*')
  FullNameList.sort()
  for Name in FullNameList:
    if os.path.isdir(Name):
      Choice.Append(Name)
      
def DisplayServiceNum():
  global NewServiceNum, ConfigFrame, PulseTimer
  ConfigFrame.label_curr_servicenum.SetLabel(str(NewServiceNum))

def GuiRun():
  global TheFrame, TextArea, ConfigFrame, PulseTimer
  global TextLineHeight, TextList, TextTail
  global Top, Left, Height, Width

  try:
    gbl.TheApp = wx.PySimpleApp()
    wx.InitAllImageHandlers()
    TheFrame = pxa_wx.MyFrame(None, -1, "")
    ConfigFrame = pxa_wx.MyFrame1(None, -1, "")
    gbl.TheApp.SetTopWindow(TheFrame)
    gbl.TheApp.SetExitOnFrameDelete(True)
    TextArea = TheFrame.text_ctrl_1
    Trash, TextLineHeight = TextArea.GetTextExtent('MjgI')
    while len(TextList) <= TEXT_MAX: # create text ring buffer
      TextList.append('')
    TextTail = 0
    PulseTimer = wx.Timer(TheFrame, 1)
    
    ## === binds
    #TheFrame.Bind(wx.EVT_IDLE,  Idle)
    #TheFrame.Bind(wx.EVT_PAINT, RePaint)
    TheFrame.Bind(wx.EVT_TIMER, Pulse)
    TheFrame.Bind(wx.EVT_TOOL,  StopPoll,        id=1)
    TheFrame.Bind(wx.EVT_TOOL,  KickPoll,        id=2)
    TheFrame.Bind(wx.EVT_TOOL,  StartPoll,       id=3)
    TheFrame.Bind(wx.EVT_TOOL,  SelectXctlFile,  id=4)
    TheFrame.Bind(wx.EVT_TOOL,  ExitApp,         id=5)
    TheFrame.Bind(wx.EVT_CLOSE, ExitApp)
    TheFrame.Bind(wx.EVT_SIZE,  Resize)
    ConfigFrame.Bind(wx.EVT_CHOICE, ChoiceConfig)
    ConfigFrame.Bind(wx.EVT_TOOL, SaveConfig,   id=10)
    ConfigFrame.Bind(wx.EVT_TOOL, BailConfig,   id=11)
                    # set folder tools
    ConfigFrame.Bind(wx.EVT_TOOL, HomeConfig,   id=12) # home
    ConfigFrame.Bind(wx.EVT_TOOL, UpConfig,     id=13) # up level
    ConfigFrame.Bind(wx.EVT_SPIN_UP, UpServiceNum)
    ConfigFrame.Bind(wx.EVT_SPIN_DOWN, DownServiceNum)
    ## ===
    if (Top >= 0) and (Left >= 0):
      TheFrame.SetPosition((Left, Top))
      gbl.LogInfo('moving to: top %i x left %i'%(Top, Left))
      
    if (Height >= 0) and (Width >= 0):
      TheFrame.SetSize((Width, Height))
      gbl.LogInfo('sizing to: width %i x height %i'%(Width, Height))
    # --- start asychronous threads -----------------------------------
    PulseTimer.Start(3000)  # 3 sec poll
    # --- make the GUI appear -----------------------------------------
    ConfigFrame.Hide()
    TheFrame.Show()
    gbl.TheApp.MainLoop()
    gbl.Log('pxa server shutting down')
    gbl.StillRunningSw = False
  except:
    gbl.LogException('crash in GUI code')
      
def GuiStop(Force = False):
  global TheFrame, TextArea, ConfigFrame, PulseTimer
  gbl.Log('shutting down GUI')
  if Force:
    gbl.TheApp.ExitMainLoop() # kill GUI ASAP
  elif gbl.TheApp <> None:
    PulseTimer.Stop()
    ConfigFrame.Destroy()
    TheFrame.Destroy()
  TheFrame = None
  TextArea = None
  ConfigFrame = None
  PulseTimer = None

def PxaServerStart():
  ## --- start non-GUI threads
  global ControlPort, ControlServiceNum
  while gbl.TheApp == None:
    time.sleep(2)
  LastOcelotPollCount = ocelot_control.PollCount
  DisplayStatus()
  # --- assume that the configuration has been setup
  ocelot_control.Start(ControlPort)
  if ((ocelot.Status <> ocelot.CLOSED)
    and (LastOcelotPollCount <> ocelot_control.PollCount)):
      inet_server.Start(ControlServiceNum)
    
def PxaServerStop():
  ocelot_control.Stop()
  inet_server.Stop()
  while ((ocelot.Status <> ocelot.CLOSED)
    or len(gbl.MsgQ)
    or (inet_server.Status <> inet_server.CLOSED)):
      gbl.LogInfo('waiting ....')
      time.sleep(2)
      if gbl.TheApp <> None: gbl.TheApp.Yield()

if __name__ == "__main__":
  gbl.StillRunningSw = True
  gbl.Logger.critical('=============================================')
  gbl.Log('BvN\'s Python pxa/IP TCP/IP server v' + Version)
  gbl.LogInfo('running on %s'%sys.platform) # looking for 'linux2' or 'win32'
  LoadIniControl()
  ## --- main thread ------------------------------------------------
  thread.start_new_thread(GuiRun, ())
  PxaServerStart() # --- start the server
  LastPulseCount = -1
  while gbl.StillRunningSw:
    if gbl.TheApp <> None: gbl.TheApp.Yield()
    
    TimeStruct = time.localtime()
    #gbl.Log('on %i.%i at %i:%i the pulse count is %s'%(
    LogMsg = 'on %i.%i at %i:%i pulse: %i'%(
      TimeStruct.tm_mon,
      TimeStruct.tm_mday,
      TimeStruct.tm_hour,
      TimeStruct.tm_min,
      PulseCount)
    LogMsg += ', clients:('
    for Client in inet_server.ClientList:
      LogMsg += ' %i:%i '%(Client.Ordinal, Client.PollCount)
    LogMsg += '), ocelot: %i'%ocelot_control.PollCount
    gbl.Log(LogMsg)
    while PulseCount == LastPulseCount:
      #PxaPauseSw = True
      gbl.Log('force pulse')
      GuiStop()
      #GuiStop(Force = True)
      PxaServerStop()
      time.sleep(5)
      thread.start_new_thread(GuiRun, ())
      PxaServerStart()
    LastPulseCount = PulseCount
    time.sleep(300)
  ## --- termination ------------------------------------------------
  SaveIniControl()
  time.sleep(2)
  PxaServerStop()
  if gbl.TheApp <> None: gbl.TheApp.Yield()
  GuiStop()
pass  