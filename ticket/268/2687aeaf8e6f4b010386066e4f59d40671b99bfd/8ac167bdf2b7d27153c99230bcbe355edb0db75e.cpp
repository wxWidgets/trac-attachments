#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/treectrl.h>

class App : public wxApp
{
public:
	virtual bool OnInit() override;
};

DECLARE_APP(App);

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Frame");
    
    // 1. wxPanel as managed window (BestSize() is NOT honoured on wxAuiManager::Update())
    wxPanel* panel = new wxPanel(frame, wxID_ANY);
    wxWindow* managedWindow = panel;

    // 2. wxFrame as managed window (BestSize() works as expected) (uncomment this and comment out 1. to see this working)
    // wxWindow* managedWindow = frame;

    wxAuiManager* manager = new wxAuiManager(managedWindow);
    
    wxAuiNotebook* notebook = new wxAuiNotebook(managedWindow, wxID_ANY);
    manager->AddPane(notebook, wxAuiPaneInfo().CenterPane());
    
    wxTreeCtrl* tree = new wxTreeCtrl(managedWindow, wxID_ANY);
    manager->AddPane(tree, wxAuiPaneInfo().DefaultPane().Left().BestSize(100, 100));
    
    manager->Update();
    frame->Show();
    
    return true;
}