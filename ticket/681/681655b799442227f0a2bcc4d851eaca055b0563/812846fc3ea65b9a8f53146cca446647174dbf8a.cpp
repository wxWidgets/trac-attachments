#include <wx/wx.h>
#include <wx/treectrl.h>

class MyTreeCtrl : public wxTreeCtrl
	{
	public:
		MyTreeCtrl(wxWindow *parent) : wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_MULTIPLE) {}
		void OnLeftDown(wxMouseEvent &event) { wxMessageBox("Left Down"); event.Skip(); }
		void OnLeftUp(wxMouseEvent &event) { wxMessageBox("Left Up"); event.Skip(); }

	private:
		DECLARE_EVENT_TABLE()
	};

BEGIN_EVENT_TABLE(MyTreeCtrl, wxTreeCtrl)
	EVT_LEFT_DOWN(MyTreeCtrl::OnLeftDown)
	EVT_LEFT_UP(MyTreeCtrl::OnLeftUp)
	END_EVENT_TABLE()


class MyFrame : public wxFrame
	{
	public:
		MyFrame() : wxFrame(NULL, -1, "Text wxTreeCtrl")
			{
			wxBoxSizer *top_sizer = new wxBoxSizer(wxHORIZONTAL);

			MyTreeCtrl *tree = new MyTreeCtrl(this);
			wxTreeItemId root = tree->AddRoot("Root");
			tree->AppendItem(root, "one");
			tree->AppendItem(root, "two");
			tree->AppendItem(root, "three");
			tree->ExpandAll();

			top_sizer->Add(tree, 1, wxEXPAND);
			SetSizer(top_sizer);
			top_sizer->Fit(this);
			}
	};

class MyApp : public wxApp
	{
	public:
		virtual bool OnInit()
			{
			MyFrame *frame = new MyFrame();
			frame->Show(true);
			return true;
			}
	};

IMPLEMENT_APP(MyApp)

 	  	 
