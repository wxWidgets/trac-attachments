#include <wx/wx.h>
#include <wx/app.h>
#include <wx/xrc/xmlres.h>
#include <wx/wizard.h>


class MyApp : public wxApp {

	public:
		virtual bool OnInit();

};

IMPLEMENT_APP(MyApp);

class MyPage : public wxWizardPageSimple {

	public:
		MyPage(wxWizard* parent) : wxWizardPageSimple(parent) {
			wxXmlResource::Get()->LoadPanel(this, parent, wxT("MyPage"));
		}

};

class MyWizard : public wxWizard {

	private:
		MyPage* m_page1;

	public:
		MyWizard(wxWindow* parent = NULL) : wxWizard(parent, wxID_ANY, wxT("Test XRC wizard")) {
			m_page1 = new MyPage(this);
			GetPageAreaSizer()->Add(m_page1);
		}

		bool RunWizard() {
			return wxWizard::RunWizard(m_page1);
		}

};


bool MyApp::OnInit() {

	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load(wxT("MyWizard.xrc"));

	MyWizard* wizard = new MyWizard;
	wizard->RunWizard();
	wizard->Destroy();

	return true;

}

 	  	 
