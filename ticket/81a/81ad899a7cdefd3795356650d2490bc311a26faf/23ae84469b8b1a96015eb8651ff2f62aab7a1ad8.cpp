
#include "wx/xrc/xmlres.h"

wxObject *LoadObjectTest( const wxChar* path, wxWindow *prnt, const wxChar *id ){
	if( !wxXmlResource::Get()->Load(path) )
		return NULL;
	wxObject *pobj = wxXmlResource::Get()->LoadObject( prnt, id, wxEmptyString );
	wxXmlResource::Get()->Unload( path );
	return pobj;
}


 	  	 
