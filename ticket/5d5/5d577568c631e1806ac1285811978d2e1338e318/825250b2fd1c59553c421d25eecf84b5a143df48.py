import wx, wx.lib.calendar
import sys, datetime

print "Python", sys.version, "on", sys.platform
print "wxPython version:", wx.VERSION_STRING

app = wx.PySimpleApp(0)

# Choose as a default date Saturday of the current week.
newdate = datetime.date.today()
print "Today is", newdate
newdate += datetime.timedelta(5 - newdate.weekday())
print "Changing date to", newdate

dlg = wx.lib.calendar.CalenDlg(None, newdate.month, newdate.day, newdate.year)
if dlg.ShowModal() == wx.ID_OK:
    print "CalenDlg returns", dlg.result
else:
    print "No date selected"
 	  	 
