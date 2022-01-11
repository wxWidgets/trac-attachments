// BUILD: g++.wrapper -std=c++17 %f -Wall -O0 -ggdb3 $(wx-config --cxxflags --libs base) -lstdc++fs
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <wx/filesys.h> // for class wxFileSystem
#include <wx/fs_mem.h> // for class wxMemoryFSHandler
#include <wx/wx.h>

class CApp : public wxApp
{
public:
	bool OnInit() {
		wxFileSystem::AddHandler(new wxMemoryFSHandler);
		// Read a file.
#if 0
		const char *szFileName = "cjk.utf8.txt";
#else
		const char *szFileName = "ascii_only.txt";
#endif
		std::ifstream fin(szFileName, std::ios_base::in | std::ios_base::binary);
		size_t cbFile = std::filesystem::file_size(szFileName);
		std::string sFileContents(cbFile, '\0');
		fin.read(&sFileContents[0], sFileContents.size());
		fin.close();
		// Add a virtual file.
		wxMemoryFSHandler::AddFile("foo.txt", sFileContents);
		// Create the virtual file-system.
		wxFileSystem *fs = new wxFileSystem;
		// Get the virtual file.
		wxFSFile *vfile = fs->OpenFile("memory:foo.txt");
		wxInputStream *istrm = vfile->GetStream();
		// Get the file size from the input stream.
		istrm->SeekI(0, wxFromEnd);
		auto cbBuf = istrm->TellI(); // Returns zero, if there are CJK chars.
		istrm->SeekI(0, wxFromStart);
		// Read from the input stream.
		std::string sBuf(cbBuf, '\0');
		if (istrm->ReadAll(&sBuf[0], sBuf.size())) {
			std::cout << "case 1: ";
			std::cout.write(&sBuf[0], sBuf.size());
		}
		else {
			std::cerr << "case 1 failed\n";
		}
		// Read from the input stream again with the correct size.
		istrm->SeekI(0, wxFromStart);
		std::string sBuf2(cbFile, '\0');
		if (istrm->ReadAll(&sBuf2[0], sBuf2.size())) {
			std::cout << "case 2: ";
			std::cout.write(&sBuf2[0], sBuf2.size());
		}
		else {
			std::cerr << "case 2 failed\n";
		}
		// Clean up.
		delete vfile;
		return false;
	}
};
wxDECLARE_APP(CApp);
wxIMPLEMENT_APP(CApp);
