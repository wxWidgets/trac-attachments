
#ifndef _TEST_H_
#define _TEST_H_

/**
 * @short Application Main Window
 * @author Igor Korot <igor@IgorsGentoo>
 * @version 0.1
 */

class 
testapp : public wxApp
{
	public:
		virtual bool OnInit();
};

class 
testFrame : public wxFrame
{
	public:
		testFrame( const wxString& title, const wxPoint& pos, const wxSize& size );
		void OnQuit( wxCommandEvent& event );
		void OnAbout( wxCommandEvent& event );

	private:
		DECLARE_EVENT_TABLE()
};

enum
{
	Menu_File_Quit = 100,
	Menu_File_About
};

#endif // _TEST_H_
