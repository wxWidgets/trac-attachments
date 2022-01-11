import wx
import wx.lib.newevent
import wx.lib.scrolledpanel

MyEvent, EVT_MINE = wx.lib.newevent.NewCommandEvent()
class Inner(wx.Panel):
    def __init__(self, parent):
	super(Inner, self).__init__(parent, -1)
	self.button = wx.Button(self, -1, label = 'press me')
	self.Bind(wx.EVT_BUTTON, self.fire_zero)

    def fire_zero(self, event):
	print 'fire_zero'
	evt = MyEvent(self.GetId(), foo = 3)
	wx.PostEvent(self, evt)


class Outer(wx.lib.scrolledpanel.ScrolledPanel):
    def __init__(self, parent):
	super(Outer, self).__init__(parent, -1)
	self.Bind(EVT_MINE, self.fire_one)

    def fire_one(self, event):
	print 'fire one'
	event.Skip()

class junk(wx.App):
    def __init__(self):
	super(junk, self).__init__(redirect = False)
	self.old_event = None

    def OnInit(self):
	self.top_frame = wx.Frame(None)
	outer_panel = Outer(self.top_frame)
	inner_panel = Inner(outer_panel)
	self.Bind(EVT_MINE, self.fire_two)
	self.top_frame.Show()
	return True

    def fire_two(self, event):
	print 'fire two'
	if event is self.old_event:
	    print 'old is new'
	self.old_event = event

my_app = junk()
my_app.MainLoop()
