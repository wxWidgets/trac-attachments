# Testdatei fuer wxpython 2.5.2.7
# bei dieser Version funktioniert die SetSingleStyle Methode nicht mehr


# Python, fme, 2003-06-12
# GUI_2_xx, Entstehung einer Gui-Anwendung
# Rahmen für die Anwendungg
# Menubar mit Basis-Einträgen hinzufügenen
# Untermenueinträge und Eventhandler hinzufügenen
# die restlichen Untermenueintraege und Handler einfuegen
# ListCtrl hinzufuegen
# Statusbar hinzufuegen
# bei Aktualisieren etwas Text im ListCtrl ausgeben

"""GUI_2_xx

Nach und nach eine GUI-Anwendung zusammenbauen.

    Frank Mersmann (mersmann@szut.uni-bremen.de)
"""

import wx


class CAppFrame(wx.Frame):
# in unserem Konstruktor rufen wir den Konstruktor der Oberklasse auf
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, wx.DefaultPosition, wx.Size(640, 480))

        # falls der Windowmanager des Fenster schliesst
        self.Bind(wx.EVT_CLOSE, self.OnCloseWindow);

        # Menubar mit Einträgen hinzufügenen
        self.mainmenu = wx.MenuBar()         # Menubar erzeugen

        menu = wx.Menu()                     # Dateimenu erzeugen 208 usw sind frei waehlbare IDs
        menu.Append(208, '&Neue Verbindung', 'SQL Server wählen')   # Untereintrag Neue Verbindung
        self.Bind(wx.EVT_MENU, self.OnDateiNeu, id = 208)                        # Eventhandler fuer Neue Verbindung
        menu.Append(209, 'B&eenden', 'Beenden der Anwendung')       # Untereintrag Beenden
        self.Bind(wx.EVT_MENU, self.OnDateiBeenden, id = 209)
        self.mainmenu.Append(menu, '&Datei')

        menu = wx.Menu()                     # gleiche Variable, neues Objekt
        menu.Append(210, '&Aktualisieren', 'Ansicht aktualisieren')
        self.Bind(wx.EVT_MENU, self.OnAktualisieren, id = 210)
        self.mainmenu.Append(menu, '&Ansicht')

        menu = wx.Menu()
        menu.Append(230, '&Über ...', 'etwas Dokumentation');
        self.Bind(wx.EVT_MENU, self.OnHilfe, id = 230)
        self.mainmenu.Append(menu, '&Hilfe')

        self.SetMenuBar(self.mainmenu)          # Mainmenue in Frame einhaengenn

    # ListCtrl hinzufuegen, Report Style, 2 Spalten
        self.list = wx.ListCtrl(self, 1100, style = wx.LC_REPORT | wx.LC_HRULES | wx.LC_VRULES)
        self.list.InsertColumn(0, 'Datum')
        self.list.InsertColumn(1, 'Url')
        self.list.SetColumnWidth(0, 110)
        self.list.SetColumnWidth(1, 500)
        #self.list.SetSingleStyle(wx.LC_HRULES, True)    # Gitterlinien setzen PROBLEM!!!!

    # Statusbar mit 2 Feldern hinzufuegen
        self.CreateStatusBar(2)
        self.SetStatusWidths([-1, 150])
        self.SetStatusText('nicht verbunden', 1)


    def OnDateiNeu(self, event):
        pass                        # noch nichts machen

    def OnDateiBeenden(self, event):
        self.Destroy()              # und Fertig

    def OnCloseWindow(self, event):
        self.Destroy()

    def OnAktualisieren(self, event):
        self.SetStatusText('generiere Werte')
        self.list.DeleteAllItems()
        i = 0
        while i < 1000:
            self.list.InsertStringItem(i, '2003-06-12 18:19:20')
            self.list.SetStringItem(i, 1, 'http://www.szut.de/projekte/python ist super')
            i += 1
        self.SetStatusText('1.000 Werte eingesetzt')

    def OnHilfe(self, event):
    # Dialogbox oeffnen und den Doc-Text anzeigen
        dlg = wx.MessageDialog(self, __doc__, "powerd by wxPython", wx.OK | wx.ICON_INFORMATION)
        dlg.ShowModal()
        self.list.SetSingleStyle(wx.LC_HRULES, False)    #  CRASH!!!!
        self.list.SetSingleStyle(wx.LC_VRULES, False)    # CRASH !!!!


# das Hauptprogramm / der Rahmen
version = 'GUI_2_06, 1.1.20030612'

if __name__ == '__main__':

    class CMyApp(wx.App):
        def OnInit(self):
            frame = CAppFrame(None, -1, version)
            frame.Show(True)
            return True

    app = CMyApp(0)
    app.MainLoop()


 	  	 
