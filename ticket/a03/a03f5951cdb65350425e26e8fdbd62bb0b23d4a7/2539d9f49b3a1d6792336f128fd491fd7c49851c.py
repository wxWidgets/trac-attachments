#!/usr/bin/python

import sys
from wxPython.wx import *

app = None

class wxbugs(wxApp):
    def __init__(self):
        wxApp.__init__(self, 0)

    def OnInit(self):
        wxInitAllImageHandlers()

        window = MainWindow()

        return true

class FileDropTarget(wxFileDropTarget):
    """ This object implements Drop Target functionality for Files """
    def __init__(self, obj):
        """ Initialize the Drop Target, passing in the Object Reference to
        indicate what should receive the dropped files """
        # Initialize the wxFileDropTarget Object
        wxFileDropTarget.__init__(self)
        # Store the Object Reference for dropped files
        self.obj = obj

    def OnDragOver(self, a, b, c):
        self.obj.SetCursor(wxStockCursor(wxCURSOR_COPY_ARROW))
        return wxDragCopy

    def OnDropFiles(self, x, y, filenames):
        """ Implement File Drop """
        #speeds up the add, but makes the interface less active
        self.obj.SetCursor(wxStockCursor(wxCURSOR_ARROW))
        for file in filenames:
            print "Got file [" + file + "]"
 
class MainWindow(wxFrame):
    def __init__(self):
        
        FRAME_ID = 9090

        wxFrame.__init__(self, NULL, FRAME_ID, 'bugs',
                         wxDefaultPosition,
                         wxSize(200, 85),
                         style = (wxNO_FULL_REPAINT_ON_RESIZE |
                                  wxDEFAULT_FRAME_STYLE),
                         )

        if (sys.platform.startswith("darwin")):
            wxsucks = wxACCEL_ALT #also meta
        else:
            wxsucks = wxACCEL_CTRL

        menubar = wxMenuBar()
        
        filemenu = wxMenu()
        filemenu.Append(wxID_NEW, "&New Item\tCtrl-N", "Create an item", wxITEM_NORMAL)
        EVT_MENU(self, wxID_NEW, self.OnNew)
        filemenu.AppendSeparator()
        filemenu.Append(wxID_EXIT, "E&xit\tCtrl-X", "Exit Nebula", wxITEM_NORMAL)
        EVT_MENU(self, wxID_EXIT, self.OnQuit)

        self.editmenu = wxMenu()
        #self.editmenu.Append(wxID_CUT, "Cut", "Cut item(s)", wxITEM_NORMAL)
        #EVT_MENU(self, wxID_CUT, self.OnCut)
        self.editmenu.Append(wxID_COPY, "Copy\tCtrl-C", "Copy item(s)")
        EVT_MENU(self, wxID_COPY, self.OnCopy)
        self.editmenu.Append(wxID_PASTE, "Paste\tCtrl-V", "Paste item(s)")
        EVT_MENU(self, wxID_PASTE, self.OnPaste)
        self.editmenu.Append(wxID_DELETE, "Delete\tDel", "Delete item(s)")
        EVT_MENU(self, wxID_DELETE, self.OnDelete)
        self.editmenu.AppendSeparator()
        self.editmenu.Append(wxID_SELECTALL, "Select &All\tCtrl-A", "Select all items")
        EVT_MENU(self, wxID_SELECTALL, self.OnSelectAll)
        
        menubar.Append(filemenu, "&File")
        menubar.Append(self.editmenu, "&Edit")
        self.SetMenuBar(menubar)
        
        self.mainsizer = wxBoxSizer(wxVERTICAL)
        self.mainsizer.SetMinSize(wxSize(220,115))

        self.CreateStatusBar()

        self.panel = wxPanel(self, wxID_ANY, style = wxNO_FULL_REPAINT_ON_RESIZE)
        #self.panel = wxTextCtrl(self, wxID_ANY, style = wxTE_MULTILINE | wxNO_FULL_REPAINT_ON_RESIZE)
        
        self.mainsizer.Add(self.panel, 1, wxALIGN_CENTER|wxEXPAND|wxALL , 0)

        self.panelsizer = wxBoxSizer(wxVERTICAL)

        if (sys.platform.startswith("darwin")):
            wxsucks = wxACCEL_ALT #also meta
        else:
            wxsucks = wxACCEL_CTRL

        entries = []
        
        EVT_MENU(self, wxID_CUT, self.OnCut)
        
        entries.append((wxsucks, ord('X'), wxID_CUT))
        entries.append((wxsucks, ord('C'), wxID_COPY))
        entries.append((wxsucks, ord('V'), wxID_PASTE))
        entries.append((wxsucks, ord('A'), wxID_SELECTALL))
                     
        entries.append((wxACCEL_NORMAL, WXK_DELETE, wxID_DELETE))
        #entries.append((wxACCEL_NORMAL, WXK_BACK, wxID_DELETE))
        
        self.SetAcceleratorTable(wxAcceleratorTable(entries))
        
        
        bug_list = []
        
        bug_sep = "\n------------------------------\n"
        
        bug_list.append("Bugs follow:")
        bug_list.append(bug_sep)
        bug  = "HelpText\n"
        bug += "\tTo test, highlight menu items in the menubar and popup menu, and look at the StatusBar\n"
        bug += "\twxMac - no help text is displayed ever\n"
        bug += "\twxMSW - help text is displayed only on items which have ids in the menubar\n"

        bug = bug.expandtabs(4)
        bug_list.append(bug)
        bug_list.append(bug_sep)
                    
        bug  = "Is Menu?\n"
        bug += "\tTo test, open any menu, or generate any menu events\n"
        bug += "\twxMac -\n"
        bug += "\t\tno menu is ever received\n"
        bug += "\t\tmenu is never flagged as a popup (even when it is a popup)\n"
        bug += "\t\tleft-clicking outside the popup to close it creates another popup\n"
        bug += "\t\t\tthis is viewable in the PopupMenu.py sample too - event.RightDown() is still true\n"
        bug += "\twxMSW -\n"
        bug += "\t\tno menu is received on popup (and on highlight all when an item is selected)\n"
        bug += "\t\tmenu is flagged as a popup only on popup close\n"
        
        bug = bug.expandtabs(4)
        bug_list.append(bug)
        bug_list.append(bug_sep)
        
        bug = "DnD Problems\n"
        bug += "\twxMac - DnD to see the cursor get confused during drag, and stick as wxCURSOR_COPY_ARROW\n"
        
        bug += "\twxMSW - console should print error on drop:\n"
        bug += "\t\twx._core.PyAssertionError: droptgt.cpp(405) \"strange - did supported formats list change?\"\n"
        
        bug = bug.expandtabs(4)
        bug_list.append(bug)
        bug_list.append(bug_sep)

        bug = "Flicker\n"
        bug += "\twxMSW - flicker on resize\n"
        
        bug = bug.expandtabs(4)
        bug_list.append(bug)
        bug_list.append(bug_sep)
 
        bug  = "Tabs\n"
        bug += "\twxMac stops diplaying text in the wxStaticText if it reaches a tab character:\n"
        
        bug = bug.expandtabs(4)
        
        bug += "[\t]<-That's a tab"
        
        bug_list.append(bug)
        
        bug_text = ""
        for bug in bug_list:
            bug_text += bug
        
        self.statictext = wxStaticText(self.panel, wxID_ANY, bug_text, style = wxNO_FULL_REPAINT_ON_RESIZE)
        self.panelsizer.Add(self.statictext, 1, wxALIGN_CENTER|wxEXPAND|wxALL , 0)

        #self.panel.AppendText(bug_text)
        
        # win32 acts weird on which window receives events,
        #   so switch on OS to prove the bug is not related to two drop sources or targets
        if (sys.platform.startswith("win32")):
            dt = FileDropTarget(self.panel)
            self.panel.SetDropTarget(dt)
        else:
            dt2 = FileDropTarget(self.statictext)
            self.statictext.SetDropTarget(dt2)

        
        self.SetSizeHints(190, 85, -1, -1)

        self.panel.SetSizer(self.panelsizer)
        self.panelsizer.SetSizeHints(self.panel)

        self.SetSizer(self.mainsizer)
        self.mainsizer.SetSizeHints(self)
        
        self.SetFocus()
        self.Show(True)
        
        
        # win32 acts weird on which window receives events,
        #   so switch on OS to prove the bug is not related to two drop sources or targets
        if (sys.platform.startswith("win32")):
            EVT_MOUSE_EVENTS(self.panel, self.OnMouseDnD)
        else:
            EVT_MOUSE_EVENTS(self.statictext, self.OnMouseDnD)
            
        EVT_MOUSE_EVENTS(self.statictext, self.OnMousePopup)
        
        self.statictext.SetFocus()
        
        EVT_MENU_OPEN(self, self.OnMenuOpen)
        EVT_MENU_CLOSE(self, self.OnMenuClose)
        EVT_MENU_HIGHLIGHT_ALL(self, self.OnMenuHighlightAll)
        
    def OnMenuOpen(self, event):
        print "Menu Open:"
        self.LogMenuEvent(event)
        
    def OnMenuClose(self, event):
        print "Menu Close:"
        self.LogMenuEvent(event)
        
    def OnMenuHighlightAll(self, event):
        print "Menu Highlight All:"
        self.LogMenuEvent(event)
        
    def LogMenuEvent(self, event):
        popup = "\tis "
        if (not event.IsPopup()):
            popup += "not "
        popup += "popup menu."
        
        print popup

        menu = "\tdid "        
        if (not event.GetMenu()):
            menu += "not "
        menu += "get menu."
        
        print menu
        
        menuid = "\tdid "        
        if (not event.GetMenuId()):
            menu += "not "
        menuid += "get menuId."
        
        print menuid
        
    
    def OnNew(self, event):
        self.SetStatusText("OnNew")
        
    def OnMouseDnD(self, event):
        if (event.Dragging() and event.LeftIsDown()):
            if (sys.platform.startswith("win32")):
                win = self.panel
            else:
                win = self.statictext
            dragSource = wxDropSource(win)
            data = wxTextDataObject("text from sample DnD")
            dragSource.SetData(data)
            result = dragSource.DoDragDrop(1)
            
        event.Skip()
            
    def OnMousePopup(self, event):                
        if (event.RightDown()):
            win = self.statictext
                
            popupmenu = wxMenu()
            popupmenu.Append(wxID_COPY, "Copy", "Copy items")
            popupmenu.Append(wxID_PASTE, "Paste", "Paste items")
            #EVT_MENU(self, MENU_APPEND, self.OnAppend)
            popupmenu.AppendSeparator()
            popupmenu.Append(wxID_DELETE, "Delete", "Delete items")
            popupmenu.Append(wxID_REPLACE, "Rename", "Rename items")
            popupmenu.AppendSeparator()
            popupmenu.Append(wxID_PROPERTIES, "HelpTextTest", "Help Text works if you see this")

            self.PopupMenu(popupmenu, event.GetPosition())
                
        event.Skip()        
        
    def OnQuit(self, event):
        self.Hide()
        self.Destroy()
        
    def OnSelectAll(self, event = None):
        {}
        
    def DeleteSelected(self):
        {}

        
    def OnCut(self, event = None):
        self.OnCopy(event)
        
    def OnCopy(self, event = None):
        selected = self.panel.GetSelections()
        if (len(selected)):
            all = None
            for file in selected:
                itemtext = "copied from clipboard sample"
            if (wxTheClipboard.Open()):
                wxTheClipboard.SetData(wxTextDataObject(itemtext))
                wxTheClipboard.Close()
                
    def OnPaste(self, event = None):
        # Read the clipboard
        if (wxTheClipboard.Open()):
            text = ""
            
            # paste text
            if (wxTheClipboard.IsSupported( wxDataFormat(wxDF_TEXT) )):
                data = wxTextDataObject()
                wxTheClipboard.GetData(data)
                text = data.GetText()
                
            # paste from a file manager
            if (wxTheClipboard.IsSupported( wxDataFormat(wxDF_FILENAME) )):
                data = wxFileDataObject()
                wxTheClipboard.GetData(data)
                files = data.GetFilenames()
                for file in files:
                    text += "[" + file + "]"
                
            if (len(text) > 0):
                self.SetStatusText("Pasted from clipboard: (" + text + ")")
                
            wxTheClipboard.Close()
            

    def OnDelete(self, event = None):
        {}

if __name__ == '__main__':

    app = wxbugs()
    
    app.MainLoop()

 	  	 
