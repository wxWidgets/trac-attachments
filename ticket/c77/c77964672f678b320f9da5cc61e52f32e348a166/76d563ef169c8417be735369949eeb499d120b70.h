
#include <wx/event.h>

// Implementation of weak references for classes that derive from wxEvtHandler,
// It relies on the patch for event handler destructor notifications. The 
// semantics is close to an ordinary pointer (operators =, ==, !=, ->, T*, ! ) 

// Even though weak references are cheap to use at the client side (size of 
// weak reference is same as size of simple pointer), it does add a dynamic 
// event table entry at the source side, so it comes with a cost. 

template <class T>
class wxWeakRef {
public:
    wxWeakRef( T* pt=NULL ) : m_pt(0) 
    { 
        if (pt) 
            Init(pt);
    }
    
    ~wxWeakRef( ){ Release( ); }
    
    T* Get() { return m_pt; }
    
    T* operator -> () { return m_pt; }
    operator T* (){ return m_pt; }
    T* operator = ( T* pt )
    { 
        Init(pt); 
        return pt;
    }
    bool operator == ( T* pt ){ return m_pt==pt; }
    bool operator != ( T* pt ){ return m_pt!=pt; }
    bool operator !(){ return !m_pt; }
    
    bool IsOk(){ return m_pt!=NULL; }
    
protected:    
    void OnEvtHandlerDestroyed(wxEvent& evt)
    {
        wxASSERT(m_pt==(wxEvtHandler*)evt.GetEventObject());
        m_pt = NULL;
    }
    
    void Init( T *pt ){
        if (pt!=m_pt)
        {
            Release( );
            if (pt) 
            {
                m_pt = pt;
                m_pt->Connect( wxEVT_DESTROY_EVTHANDLER, (wxObjectEventFunction)&wxWeakRef<T>::OnEvtHandlerDestroyed, NULL, (wxEvtHandler*)this );
            }
        }
    }
    
    void Release( ){
        if (m_pt)
        {
            m_pt->Disconnect( wxEVT_DESTROY_EVTHANDLER, (wxObjectEventFunction)&wxWeakRef<T>::OnEvtHandlerDestroyed, NULL, (wxEvtHandler*)this );
            m_pt = NULL;
        }
    }
    
    T *m_pt;
};


// Some typedefs for common cases
typedef wxWeakRef<wxEvtHandler> wxEvtHandlerRef;
typedef wxWeakRef<wxWindow> wxWindowRef;


 	  	 
