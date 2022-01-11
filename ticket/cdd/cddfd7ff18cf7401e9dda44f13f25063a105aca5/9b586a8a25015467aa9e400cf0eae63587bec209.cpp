

#include <wx/wx.h>
#include <wx/datetime.h>

int
main() {
	wxDateTime mydate=wxDateTime::Now();
	mydate.SetYear(1937);
	puts(mydate.Format("%x").c_str());
	puts(mydate.Format("%Y").c_str());
	puts(mydate.Format("%c").c_str());
}

 	  	 
