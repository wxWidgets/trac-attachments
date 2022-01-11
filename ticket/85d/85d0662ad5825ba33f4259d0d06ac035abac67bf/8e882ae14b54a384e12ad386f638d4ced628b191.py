""" crash.xrc
<?xml version="1.0" ?>
<resource>
  <object class="wxDialog" name="FIRST">
    <title></title>
    <object class="wxBoxSizer">
      <orient>wxVERTICAL</orient>
      <object class="sizeritem">
        <object class="wxStaticText">
          <label>FIRST</label>
        </object>
        <flag>wxALIGN_CENTRE_HORIZONTAL | wxALL</flag>
        <border>8</border>
      </object>
      <object class="sizeritem">
        <object class="wxBoxSizer">
          <orient>wxHORIZONTAL</orient>
          <object class="sizeritem">
            <object class="wxButton" name="FIRST_OK">
              <label>OK</label>
            </object>
            <flag>wxALL</flag>
            <border>4</border>
          </object>
          <object class="sizeritem">
            <object class="wxButton" name="FIRST_CANCEL">
              <label>Cancel</label>
            </object>
            <flag>wxALL</flag>
            <border>4</border>
          </object>
        </object>
      </object>
    </object>
  </object>
  <object class="wxDialog" name="SECOND">
    <title></title>
    <object class="wxBoxSizer">
      <orient>wxVERTICAL</orient>
      <object class="sizeritem">
        <object class="wxStaticText">
          <label>SECOND</label>
        </object>
        <flag>wxALL|wxALIGN_CENTRE_HORIZONTAL</flag>
        <border>8</border>
      </object>
      <object class="sizeritem">
        <object class="wxBoxSizer">
          <orient>wxHORIZONTAL</orient>
          <object class="sizeritem">
            <object class="wxButton" name="SEC_OK">
              <label>OK</label>
            </object>
            <flag>wxALL</flag>
            <border>4</border>
          </object>
          <object class="sizeritem">
            <object class="wxButton" name="SEC_CANCEL">
              <label>Cancel</label>
            </object>
            <flag>wxALL</flag>
            <border>4</border>
          </object>
        </object>
      </object>
    </object>
  </object>
</resource>

"""

from wxPython.wx import *
from wxPython.xrc import *

class MainWnd(wxFrame):
    def __init__(self, parent, id, title, pos = wxDefaultPosition,
            size = wxDefaultSize, style = wxDEFAULT_FRAME_STYLE, name = ''):
        wxFrame.__init__(self, parent, id, title, pos, size, style, name)
        
        self.res = wxXmlResource('crash.xrc')
        
        self.dlg1 = self.res.LoadDialog(self, 'FIRST')
        self.dlg2 = self.res.LoadDialog(self.dlg1, 'SECOND')
        
        EVT_BUTTON(self.dlg1, XRCID('FIRST_CANCEL'), lambda e:self.dlg1.EndModal(wxID_CANCEL))
        EVT_BUTTON(self.dlg1, XRCID('FIRST_OK'), lambda e:self.dlg2.ShowModal())
        EVT_BUTTON(self.dlg2, XRCID('SEC_CANCEL'), lambda e:self.dlg2.EndModal(wxID_CANCEL))
        EVT_BUTTON(self.dlg2, XRCID('SEC_OK'), lambda e:[self.dlg1.EndModal(wxID_OK), self.dlg2.EndModal(wxID_OK)])
        
        if self.dlg1.ShowModal() == wxID_OK:
	     self.Show(True)
	else:
             self.Destroy()


class crashApp(wxApp):
    def OnInit(self):
        wxInitAllImageHandlers()
        EVT_TIMER(self,999999,self.OnTimer)
        self.timer=wxTimer(self,999999)
        self.timer.Start(250,False)
        
        self.main = MainWnd(None, -1, "crashtest")
        self.SetTopWindow(self.main)
        return True

    def OnTimer(self, event):
        print "Still running"

    def __del__(self):
        self.timer.stop()
        wxApp.__del__(self)

def main():
    application = crashApp(0)
    application.MainLoop()

if __name__ == '__main__':
    main()

 	  	 
