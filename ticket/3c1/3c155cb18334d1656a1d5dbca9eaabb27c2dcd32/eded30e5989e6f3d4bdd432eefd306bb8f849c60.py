from wxPython.wx import *

class mailbox_window(wxSplitterWindow):
    def __init__(self, parent, frame, mailbox):
        splitterId = wxNewId()
        wxSplitterWindow.__init__(self, parent, splitterId)
        listId = wxNewId()
        self.msglist = wxListCtrl(self, listId,
                                  style=wxLC_REPORT|wxNO_BORDER)
        self.msglist.InsertColumn(0, 'From/To')
        self.msglist.InsertColumn(1, 'Subject')
        self.msglist.InsertColumn(2, 'Date')
        self.msglist.InsertColumn(3, 'Size')
        self.text = wxPanel(self, -1)
        self.sashPosition = 200
        self.SplitHorizontally(self.msglist, self.text, self.sashPosition)
        self.SetSashPosition(self.sashPosition)

        for i in range(20):
            s = str(i)
            row = i
            self.msglist.InsertStringItem(row, s)
            self.msglist.SetStringItem(row, 1, s)
            self.msglist.SetStringItem(row, 2, s)
            self.msglist.SetStringItem(row, 3, s)

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
        self.splitter = wxSplitterWindow(self, -1)
        self.boxtree = wxPanel(self.splitter, -1)
        self.mailboxes = MailboxNotebook(self.splitter, style=wxNB_BOTTOM)
        self.splitter.SplitVertically(self.boxtree, self.mailboxes, 200)
        self.Show(true)
        self.AddMailbox('{localhost}INBOX')

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


 	  	 
