/*
 *
 */
#include <iostream>
#include <wx/wx.h>
#include <wx/config.h>

class CLI1 : public wxAppConsole
{
    int OnRun();
};
wxDECLARE_APP(CLI1);

int CLI1::OnRun()
{
    std::cout << wxConfig::GetLocalFileName("hugin") << std::endl;
    std::cout << wxConfig::GetLocalFileName("hugin", wxCONFIG_USE_SUBDIR) << std::endl;
}

wxIMPLEMENT_APP(CLI1);
