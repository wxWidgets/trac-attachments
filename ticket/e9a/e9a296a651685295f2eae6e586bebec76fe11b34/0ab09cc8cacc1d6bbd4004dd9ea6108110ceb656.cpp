#include <wx/wx.h>
#include <iostream>

using namespace std;

class MyApp : public wxApp 
{ 
    virtual bool OnInit(); 
};
IMPLEMENT_APP(MyApp)

class MyFrame : public wxFrame 
{ 
    public: MyFrame(); 
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame;
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, -1, "My Frame")

{
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *menu = new wxMenu;
    const char* labels[2] = {"Without accelerator", "&With accelerator"};
    menu->Append(150, labels[0]);
    menu->Append(151, labels[1]);

    menuBar->Append(menu, "Menu");
    SetMenuBar(menuBar);

    for (int i = 0; i < 2; ++i) 
        if (menu->FindItem(labels[i]) == wxNOT_FOUND)
            cout << "Menu item " << labels[i] << " not found" << endl;
        else
            cout << "Menu item " << labels[i] << " found" << endl;
}

