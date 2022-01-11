#include <wx/app.h>
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/menu.h>

class app : public wxApp
{
    public:
        bool OnInit();
};

class frame : public wxFrame
{
    public:
        frame();
        ~frame() {}
    protected:
        void append(wxCommandEvent&);
        void bugappend(wxCommandEvent&);
        
    private:
        wxGrid* grid;
};

IMPLEMENT_APP (app);

bool app::OnInit()
{
    wxFrame* f = new frame ();
    
    f->Show ();
    return (true);
}

enum {
    _myID_APPEND = wxID_HIGHEST,
    _myID_BUGAPPEND
};

frame::frame() : wxFrame(0, wxID_ANY, _("Append Test"))
{
    wxSizer* entire = new wxBoxSizer (wxVERTICAL);
    wxSizer* top = new wxBoxSizer (wxHORIZONTAL);
    wxSizerFlags flags;
    
    grid = new wxGrid (this, wxID_ANY);
    grid->CreateGrid (5, 15);
    
    wxGrid* other_grid = new wxGrid (this, wxID_ANY);
    other_grid->CreateGrid (10, 10);
    
    top->Add (grid, flags);
    entire->Add (top, flags);
    entire->Add (other_grid, flags);
    
    wxMenu* file = new wxMenu ();
    
    file->Append (_myID_APPEND, _("Normal Append\tF2"));
    file->Append (_myID_BUGAPPEND, _("Bugged Append\tF3"));
    
    wxMenuBar* menubar = new wxMenuBar ();
    menubar->Append (file, _("&File"));
    
    this->SetMenuBar (menubar);
    this->SetSizer (entire);
    entire->Fit (this);
    
    this->Connect (_myID_APPEND,
    wxEVT_COMMAND_MENU_SELECTED,
    wxCommandEventHandler(frame::append),
    NULL,
    this);
    this->Connect (_myID_BUGAPPEND,
    wxEVT_COMMAND_MENU_SELECTED,
    wxCommandEventHandler(frame::bugappend),
    NULL,
    this);
}

void frame::append(wxCommandEvent& event)
{
    grid->AppendRows (2);
    grid->AutoSizeColumns ();
    grid->AutoSizeRows ();
}

void frame::bugappend(wxCommandEvent& event)
{
    grid->AppendRows (2);
    grid->AutoSize ();
}