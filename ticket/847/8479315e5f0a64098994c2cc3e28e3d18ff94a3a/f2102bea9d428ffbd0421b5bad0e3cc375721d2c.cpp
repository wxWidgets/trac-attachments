
#include <wx/wx.h>
#include <wx/hashmap.h>

// Parent class
class CParent
{
public:
	~CParent();
};

// Parent dtor
CParent::~CParent()
{
	// Called ==> correct
}

// Child class, derive from parent class
class CChild : public CParent
{
public:
	~CChild();
};

// Child dtor
CChild::~CChild()
{
	// Never called ! ! !
}

// The hash map of CParent* objects, keys are strings
WX_DECLARE_STRING_HASH_MAP(CParent*, CParentList);


// The application
class CTest : public wxApp
{
public :
	virtual bool OnInit();
};

DECLARE_APP(CTest)
IMPLEMENT_APP(CTest)


bool CTest::OnInit()
{
	// Create the table
	CParentList list;

	// Create a new child object
	CChild* newChild = new CChild();

	// Append it to the table
	list["child1"] = newChild;


	// Some code...


	// Delete the content of the list
	CParentList::iterator it;
	for( it = list.begin(); it != list.end(); ++it )
		delete it->second;

	// Caused the application to exit
	return false;
}


 	  	 
