#include <wx/wx.h>

class Application : public wxApp
{
public:
    
    enum {
        BoxWidth = 45,
        BoxHeight = 45,
    };
    
    wxPanel* CreatePanel(wxWindow* parent, const wxColour& backgroundColor)
    {
        wxPanel* panel = new wxPanel(parent);
        panel->SetBackgroundColour(backgroundColor);
        panel->SetMinSize(wxSize(BoxWidth, BoxHeight));
        return panel;
    }
    
    bool OnInit()
    {
        wxInitAllImageHandlers();
        mainFrame = new wxFrame(nullptr, wxID_ANY, "Test");
        
        auto panel = new wxPanel(mainFrame);
        auto boxSizer = new wxBoxSizer(wxHORIZONTAL);
        
        std::vector<wxColour> colours {
            {255, 0, 0},
            {255, 51, 0},
            {255, 102, 0},
            {255, 128, 0},
            {255, 153, 0},
            {255, 178, 0},
            {255, 204, 0},
            {255, 229, 0},
            {255, 255, 0},
            {204, 255, 0},
            {153, 255, 0},
            {51, 255, 0},
            {0, 204, 0},
            {0, 178, 102},
            {0, 153, 153},
            {0, 102, 178},
            {0, 51, 204},
            {25, 25, 178},
            {51, 0, 153},
            {64, 0, 153},
            {102, 0, 153},
            {153, 0, 153},
            {204, 0, 153},
            {229, 0, 102},
        };
        
        for(auto c : colours)
        {
            boxSizer->Add(CreatePanel(panel, c), 1, wxEXPAND, 0);
        }
        
        mainFrame->SetSize((int)(BoxWidth*colours.size()), 200);
        
        panel->SetSizerAndFit(boxSizer);
        
        SetTopWindow(mainFrame);
        mainFrame->Show(true);
        
        return true;
    }
    
private:
    wxFrame* mainFrame;
};


IMPLEMENT_APP(Application)
