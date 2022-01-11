///////////////////////////////////////////////////////////////////////////////
// Name:        stack.h
// Purpose:     STL stack clone
// Author:      Lindsay Mathieson
// Modified by:
// Created:     30.07.2001
// Copyright:   (c) 2001 Lindsay Mathieson <lindsay@mathieson.org>
// Licence:     wxWindows license
///////////////////////////////////////////////////////////////////////////////

#ifndef   WX_STL_STACK_H
#define   WX_STL_STACK_H

#ifdef __GNUG__
#pragma interface "stack.h"
#endif

#include "wx/defs.h"
#include "wx/vector.h"

#define WX_DECLARE_STL_STACK(obj, cls)\
class cls : public wxVectorBase\
{\
	WX_DECLARE_STL_VECTORBASE(obj, cls);\
public:\
	void push(const obj& o)\
	{\
		bool rc = Alloc(size() + 1);\
		wxASSERT(rc);\
		Append(new obj(o));\
	};\
\
	void pop()\
	{\
		RemoveAt(size() - 1);\
	};\
\
	obj& top()\
	{\
		return *(obj *) GetItem(size() - 1);\
	};\
	const obj& top() const\
	{\
		return *(obj *) GetItem(size() - 1);\
	};\
}


#endif
 	  	 
