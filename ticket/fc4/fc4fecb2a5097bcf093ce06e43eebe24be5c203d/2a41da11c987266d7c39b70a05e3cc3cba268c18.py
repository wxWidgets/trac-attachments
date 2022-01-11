#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

import wx
import wx.propgrid as wxpg
import random

class CoordProperty(wxpg.PyProperty):
    def __init__(self, label, name, value=(0,0,0)):
        wxpg.PyProperty.__init__(self, label, name)
        self.SetValue(value)

    def GetClassName(self):
        return "CoordProperty"

    def GetEditor(self):
        return "TextCtrl"

    def ValueToString(self, value, flags):
        x,y,z = value
        return "%f,%f,%f"%(x,y,z)


app = wx.App(False)
frame = wx.Frame(None, -1, "Test")
pg = wxpg.PropertyGridManager(frame)
props = {}

for i in range(1000):
    prop_name = "prop_%d"%i
    prop = CoordProperty("Coord", prop_name)
    pg.Append(prop)
    props[prop_name] = prop

def OnTimer(event):
    global props
    for key in props:
        props[key].SetValue((random.random(), random.random(), random.random()))

timer = wx.Timer(frame, 1)
frame.Bind(wx.EVT_TIMER, OnTimer)
timer.Start(10) # 100Hz

frame.Show()

app.MainLoop()
timer.Stop()