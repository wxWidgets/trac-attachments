#include <wx/mstream.h>

class XmlSaveThread : private wxThreadHelper
{
public:
	XmlSaveThread(void) {}
	virtual ~XmlSaveThread(void) {}

	void StartThread(void)
	{
		CreateThread();
		GetThread()->Run();
	}

protected:
	void *Entry(void)
	{
		for (int i = 0; i < 100; ++i)
		{
			wxMemoryOutputStream output;
			wxXmlDocument xmlDoc;
		
			wxXmlNode *pRootNode = 	new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxT("testroot"));
			wxXmlNode *pNode = new wxXmlNode(pRootNode, wxXML_ELEMENT_NODE, wxT("value"));
			new wxXmlNode(pNode, wxXML_TEXT_NODE, wxEmptyString, wxT("1234"));
		
			xmlDoc.SetRoot(pRootNode);
			xmlDoc.Save(output);
		}

		return NULL;
	}
};


void testFunc(void)
{
	for (int i = 0; i < 4; ++i)
	{
		XmlSaveThread *pThread = new XmlSaveThread;
		pThread->StartThread();
	}

	wxSleep(10);
}
