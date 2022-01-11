from wxPython.wx import *

bug = 2

class mailbox_window(wxSplitterWindow):
    def __init__(self, parent, frame, mailbox):
        splitterId = wxNewId()
        wxSplitterWindow.__init__(self, parent, splitterId)
        if bug <= 2:
            self.msglist = wxListCtrl(self, -1, style=wxLC_REPORT|wxNO_BORDER)
            self.msglist.InsertColumn(0, 'From/To')
            for i in range(20):
                s = str(i)
                row = i
                self.msglist.InsertStringItem(row, s)

        elif bug > 2:
            self.msglist = wxTreeCtrl(self, -1)
            self.root = self.msglist.AddRoot('root')
            for i in range(20):
                s = str(i)
                self.msglist.AppendItem(self.root, s)
            self.msglist.Expand(self.root)

        self.text = wxPanel(self, -1)
        self.sashPosition = 200
        self.SplitHorizontally(self.msglist, self.text, self.sashPosition)
        self.SetSashPosition(self.sashPosition)
        
class MailboxNotebook(wxNotebook):
    def __init__(self, parent, style):
        self.parent = parent
        self.currentPage = None
        id = wxNewId()
        wxNotebook.__init__(self, parent, id, style=style)

    def AddIndexedPage(self, page, label, selected, index):
        self.AddPage(page, label, selected)

class GBMailFrame(wxFrame):
    def __init__(self, parent, title):
        id = wxNewId()
        wxFrame.__init__(self, parent, id, title)
        self.mailboxes = MailboxNotebook(self, style=wxNB_BOTTOM)
        self.AddMailbox('{localhost}INBOX')
        self.Show(true)

    def AddMailbox(self, boxname):
        win = mailbox_window(self.mailboxes, self, boxname)
        self.mailboxes.AddIndexedPage(win, 'INBOX', 1, boxname)

class GBMailApp(wxApp):
    def OnInit(self):
        self.frame = GBMailFrame(None, "GBMail")
        return true

def main():
    app = GBMailApp(0)
    app.MainLoop()

main()


 	  	 
