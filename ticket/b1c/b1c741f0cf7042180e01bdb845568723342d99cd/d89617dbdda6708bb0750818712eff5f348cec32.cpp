//
// wxAny, preliminary draft
//
// NOTE: This is not a complete minimal app. You will need to paste contents of
//       this file into existing minimal app and then call TestWxAny(), which is at
//       the bottom of the code.
//
// Tested on VC8.
//

////////////////////////////////////////////////////////////////////
//
// HEADER FILE PORTION
//
////////////////////////////////////////////////////////////////////

#include "wx/vector.h"
#include "wx/meta/movable.h"

class wxAny;
class wxAnyValueType;
class wxAnyValueTypeGlobals;

#define WX_ANY_VALUE_BUFFER_SIZE    16

union wxAnyValueBuffer
{
    void*   v_ptr;
    wxByte  v_buffer[WX_ANY_VALUE_BUFFER_SIZE];
};

wxAnyValueTypeGlobals* g_wxAnyValueTypeGlobals = NULL;

typedef void (*wxAnyClassInfo)();

// Use this macro for checking if wxAnyValueType represents a specific C++
// data type.
#define wxAnyTypeCheck(valueType, T) \
    (valueType->GetClassInfo() == wxAnyValueTypeImpl<T>::sm_classInfo)


class wxAnyValueType
{
public:
    /**
        Default constructor.
    */
    wxAnyValueType();

    /**
        Destructor.
    */
    virtual ~wxAnyValueType()
    {
    }

    /**
        For internal type matching.
    */
    virtual wxAnyClassInfo GetClassInfo() const = 0;

    /**
        For internal type matching.
    */
    virtual bool IsSameType(const wxAnyValueType* otherType) const = 0;

    /**
        This function is called every time the data in wxAny
        buffer needs to be freed.
    */
    virtual void DeleteData(wxAnyValueBuffer& buf) const = 0;

    /**
        This function is called every time the data in wxAny
        buffer needs to be refreshed from a raw source value.
    */
    virtual void DynamicSetData(const void* valuePtr,
                                wxAnyValueBuffer& buf) const = 0;

    /**
        Implement this for buffer-to-buffer copy. src.v_ptr can
        be excepted to be NULL if value type of previously stored
        data was different.
    */
    virtual void CopyBuffer(const wxAnyValueBuffer& src,
                            wxAnyValueBuffer& dst) const = 0;

    /**
        Equality test of two datas with same type.
    */
    virtual bool EqOfSameType(const wxAnyValueBuffer& buf1,
                              const wxAnyValueBuffer& buf2)
    {
        wxUnusedVar(buf1);
        wxUnusedVar(buf2);
        return false;
    }

    /**
        Convert value into buffer of different type. Return false if
        not possible.
    */
    virtual bool ConvertValue(const wxAnyValueBuffer& src,
                              wxAnyValueType* dstType,
                              wxAnyValueBuffer& dst) const
    {
        wxUnusedVar(src);
        wxUnusedVar(dstType);
        wxUnusedVar(dst);
        return false;
    }
private:
};

/**
    Helper macro for defining optimized user value types.
*/
#define WX_DECLARE_ANY_VALUE_TYPE_IN_CLASS(ValueType, TemplateClass) \
    friend class wxAny; \
private: \
    static TemplateClass<ValueType>*        sm_instance; \
public: \
    static void                             sm_classInfo() {} \
 \
    virtual wxAnyClassInfo GetClassInfo() const \
    { \
        return sm_classInfo; \
    } \
    static bool IsSameClass(const wxAnyValueType* otherType) \
    { \
        return sm_classInfo == otherType->GetClassInfo(); \
    } \
    virtual bool IsSameType(const wxAnyValueType* otherType) const \
    { \
        return IsSameClass(otherType); \
    } \
    static wxAnyValueType* GetInstance() \
    { \
        return sm_instance; \
    } \
private:

#define WX_DECLARE_ANY_VALUE_TYPE(ValueType) \
    WX_DECLARE_ANY_VALUE_TYPE_IN_CLASS(ValueType, wxAnyValueTypeImpl)

/*
    Generic value type implementation. This is intermediate class
    so we can derive from this same value type for multiple
    actual types (for instance, we can have wxAnyValueTypeImplInt
    for all signed integer types).
*/
template<typename T>
class wxAnyValueTypeImplBase : public wxAnyValueType
{
    WX_DECLARE_ANY_VALUE_TYPE_IN_CLASS(T, wxAnyValueTypeImplBase)
public:
    wxAnyValueTypeImplBase() : wxAnyValueType() { }
    virtual ~wxAnyValueTypeImplBase() { }

    template<typename T>
    class DataHolder
    {
    public:
        DataHolder(const T& value)
        {
            m_value = value;
        }
        virtual ~DataHolder() { }

        T   m_value;
    };

    virtual void DeleteData(wxAnyValueBuffer& buf) const
    {
        // Let's hope compilers are smart enough to optimize out these
        // conditions.
        if ( wxIsMovable<T>::value && sizeof(T) <= WX_ANY_VALUE_BUFFER_SIZE )
        {
            // pass
        }
        else
        {
            DataHolder<T>* holder = (DataHolder<T>*) buf.v_ptr;
            delete holder;
        }
        buf.v_ptr = NULL;  // This is important
    }

    virtual void DynamicSetData(const void* valuePtr,
                                wxAnyValueBuffer& buf) const
    {
        const T& value = *((T*)valuePtr);
        if ( wxIsMovable<T>::value && sizeof(T) <= WX_ANY_VALUE_BUFFER_SIZE )
        {
            memcpy(buf.v_buffer, valuePtr, sizeof(T));
        }
        else
        {
            DataHolder<T>* holder = new DataHolder<T>(value);
            buf.v_ptr = holder;
        }
    }

    virtual void CopyBuffer(const wxAnyValueBuffer& src,
                            wxAnyValueBuffer& dst) const
    {
        if ( wxIsMovable<T>::value && sizeof(T) <= WX_ANY_VALUE_BUFFER_SIZE )
        {
            memcpy(dst.v_buffer, src.v_buffer, sizeof(T));
        }
        else
        {
            // Free old data
            DataHolder<T>* holder;
            holder = (DataHolder<T>*) dst.v_ptr;
            delete holder;

            // Allocate new data
            holder = (DataHolder<T>*) src.v_ptr;
            holder = new DataHolder<T>(holder->m_value);
            dst.v_ptr = holder;
        }
    }

    /**
        It is important to reimplement this in any specialized template
        classes that inherit from wxAnyValueTypeImplBase.
    */
    static void StaticSetData(const T& value,
                              wxAnyValueBuffer& buf)
    {
        if ( wxIsMovable<T>::value && sizeof(T) <= WX_ANY_VALUE_BUFFER_SIZE )
        {
            memcpy(buf.v_buffer, &value, sizeof(T));
        }
        else
        {
            DataHolder<T>* holder = new DataHolder<T>(value);
            buf.v_ptr = holder;
        }
    }

    /**
        It is important to reimplement this in any specialized template
        classes that inherit from wxAnyValueTypeImplBase.
    */
    static const T& GetValue(const wxAnyValueBuffer& buf)
    {
        if ( wxIsMovable<T>::value && sizeof(T) <= WX_ANY_VALUE_BUFFER_SIZE )
        {
            return *((T*)buf.v_buffer);
        }
        else
        {
            DataHolder<T>* holder = (DataHolder<T>*) buf.v_ptr;
            return holder->m_value;
        }
    }

    virtual bool EqOfSameType(const wxAnyValueBuffer& buf1,
                              const wxAnyValueBuffer& buf2)
    {
        if ( wxIsMovable<T>::value && sizeof(T) <= WX_ANY_VALUE_BUFFER_SIZE )
        {
            T v1;
            memcpy(&v1, buf1.v_buffer, sizeof(T));
            T v2;
            memcpy(&v2, buf2.v_buffer, sizeof(T));
            return v1 == v2;
        }
        else
        {
            DataHolder<T>* holder1 = (DataHolder<T>*) buf1.v_ptr;
            DataHolder<T>* holder2 = (DataHolder<T>*) buf2.v_ptr;
            return holder1->m_value == holder2->m_value;
        }
    }

    /**
        Convert value into buffer of different type. Return false if
        not possible.
    */
    virtual bool ConvertValue(const wxAnyValueBuffer& src,
                              wxAnyValueType* dstType,
                              wxAnyValueBuffer& dst) const
    {
        wxUnusedVar(src);
        wxUnusedVar(dstType);
        wxUnusedVar(dst);
        return false;
    }
private:
};

template<typename T>
wxAnyValueTypeImplBase<T>* wxAnyValueTypeImplBase<T>::sm_instance =
    new wxAnyValueTypeImpl<T>();


/*
    Generic value type template implementation.
*/
template<typename T>
class wxAnyValueTypeImpl : public wxAnyValueTypeImplBase<T>
{
public:
    wxAnyValueTypeImpl() : wxAnyValueTypeImplBase<T>() { }
    virtual ~wxAnyValueTypeImpl() { }
};


/**
    Helper macro for implementing user value types.
*/
#define WX_IMPLEMENT_ANY_VALUE_TYPE(ValueType) \
wxAnyValueTypeImpl<ValueType>* \
    wxAnyValueTypeImpl<ValueType>::sm_instance = \
        new wxAnyValueTypeImpl<ValueType>();


/*
    Signed integer value type implementation.
*/
#define WX_ANY_BASE_SIGNED_INT_TYPE     signed long

class wxAnyValueTypeImplInt :
    public wxAnyValueTypeImplBase<WX_ANY_BASE_SIGNED_INT_TYPE>
{
public:
    wxAnyValueTypeImplInt() :
        wxAnyValueTypeImplBase<WX_ANY_BASE_SIGNED_INT_TYPE>() { }
    virtual ~wxAnyValueTypeImplInt() { }

    /**
        Convert value into buffer of different type. Return false if
        not possible.
    */
    virtual bool ConvertValue(const wxAnyValueBuffer& src,
                              wxAnyValueType* dstType,
                              wxAnyValueBuffer& dst) const;
};

#define WX_ANY_DEFINE_SIGNED_INT_TYPE(T) \
template<> \
class wxAnyValueTypeImpl<T> : public wxAnyValueTypeImplInt \
{ \
public: \
    wxAnyValueTypeImpl() : wxAnyValueTypeImplInt() { } \
    virtual ~wxAnyValueTypeImpl() { } \
    static void StaticSetData(const T& value, wxAnyValueBuffer& buf) \
    { \
        *((WX_ANY_BASE_SIGNED_INT_TYPE*)buf.v_buffer) = \
            (WX_ANY_BASE_SIGNED_INT_TYPE) value; \
    } \
    static T GetValue(const wxAnyValueBuffer& buf) \
    { \
        return (T) (*((WX_ANY_BASE_SIGNED_INT_TYPE*)buf.v_buffer)); \
    } \
};

WX_ANY_DEFINE_SIGNED_INT_TYPE(signed long)
WX_ANY_DEFINE_SIGNED_INT_TYPE(signed int)
WX_ANY_DEFINE_SIGNED_INT_TYPE(signed short)
WX_ANY_DEFINE_SIGNED_INT_TYPE(signed char)


/*
    String value type implementation.
*/
class wxAnyValueTypeImplString :
    public wxAnyValueTypeImplBase<wxString>
{
public:
    wxAnyValueTypeImplString() :
        wxAnyValueTypeImplBase<wxString>() { }
    virtual ~wxAnyValueTypeImplString() { }

    /**
        Convert value into buffer of different type. Return false if
        not possible.
    */
    virtual bool ConvertValue(const wxAnyValueBuffer& src,
                              wxAnyValueType* dstType,
                              wxAnyValueBuffer& dst) const;

};

template<>
class wxAnyValueTypeImpl<wxString> : public wxAnyValueTypeImplString
{
public:
    wxAnyValueTypeImpl() : wxAnyValueTypeImplString() { }
    virtual ~wxAnyValueTypeImpl() { }
};

/*
    String specializations.
    NB: Not able to implement them properly, so just added operator
        overloads into wxAny class itself.
*/
/*
template<>
class wxAnyValueTypeImpl<const char*> : public wxAnyValueTypeImplString
{
public:
    wxAnyValueTypeImpl() : wxAnyValueTypeImplString() { }
    virtual ~wxAnyValueTypeImpl() { }
    static void StaticSetData(const char* value,
                              wxAnyValueBuffer& buf)
    {
        wxString str(value);
        wxAnyValueTypeImplString::StaticSetData(str, buf);
    }
    static const char* GetValue(const wxAnyValueBuffer& buf)
    {
        return wxAnyValueTypeImplString::GetValue(buf).c_str();
    }
};

#if wxUSE_WCHAR_T
template<>
class wxAnyValueTypeImpl<const wchar_t*> : public wxAnyValueTypeImplString
{
public:
    wxAnyValueTypeImpl() : wxAnyValueTypeImplString() { }
    virtual ~wxAnyValueTypeImpl() { }
    static void StaticSetData(const wchar_t* value,
                              wxAnyValueBuffer& buf)
    {
        wxString str(value);
        wxAnyValueTypeImplString::StaticSetData(str, buf);
    }
    static const wchar_t* GetValue(const wxAnyValueBuffer& buf)
    {
        return wxAnyValueTypeImplString::GetValue(buf).c_str();
    }
};
#endif
*/

/*
    Let's define a discrete Null value so we don't have to really
    ever check if type pointer is NULL or not.
*/
class wxAnyNullValue
{
public:
    void*   m_servesNoPurpose;
};

template <>
class wxAnyValueTypeImpl<wxAnyNullValue> : public wxAnyValueType
{
    WX_DECLARE_ANY_VALUE_TYPE(wxAnyNullValue)
public:
    virtual void DeleteData(wxAnyValueBuffer& buf) const
    {
        buf.v_ptr = NULL;  // This is important
    }

    virtual void DynamicSetData(const void* valuePtr,
                                wxAnyValueBuffer& buf) const
    {
        wxUnusedVar(valuePtr);
        wxUnusedVar(buf);
    }

    virtual void CopyBuffer(const wxAnyValueBuffer& src,
                            wxAnyValueBuffer& dst) const
    {
        wxUnusedVar(src);
        wxUnusedVar(dst);
    }

private:
};

typedef wxAnyValueTypeImpl<wxAnyNullValue> wxAnyNullValueType;


/**
    Helper class to manage wxAnyValueType instances and other
    related global variables.
*/
class wxAnyValueTypeGlobals
{
public:
    wxAnyValueTypeGlobals()
    {
    }
    ~wxAnyValueTypeGlobals()
    {
        for ( size_t i=0; i<m_valueTypes.size(); i++ )
            delete m_valueTypes[i];
    }

    void AddValueType(wxAnyValueType* valueType)
    {
        m_valueTypes.push_back(valueType);
    }

private:
    wxVector<wxAnyValueType*>   m_valueTypes;
};


/**
    The wxAny class represents a container for any type.
*/
class wxAny
{
public:
    /**
        Default constructor.
    */
    wxAny()
    {
        m_type = wxAnyNullValueType::sm_instance;
    }

    /**
        Destructor.
    */
    ~wxAny()
    {
        m_type->DeleteData(m_buffer);
    }

    /**
        Various constructors.
    */
    wxAny(const char* value)
    {
        m_type = wxAnyNullValueType::sm_instance;
        Assign(wxString(value));
    }
#if wxUSE_WCHAR_T
    wxAny(const wchar_t* value)
    {
        m_type = wxAnyNullValueType::sm_instance;
        Assign(wxString(value));
    }
#endif

    wxAny(const wxAny& any)
    {
        m_type = wxAnyValueTypeImpl<wxAnyNullValue>::sm_instance;
        Assign(any);
    }

    template<typename T>
    wxAny(const T& value)
    {
        m_type = wxAnyValueTypeImpl<T>::sm_instance;
        wxAnyValueTypeImpl<T>::StaticSetData(value, m_buffer);
    }

    /**
        Assignment functions.
    */
    void Assign(const wxAny &any)
    {
        if ( !any.m_type->IsSameType(m_type) )
        {
            m_type->DeleteData(m_buffer);
            m_type = any.m_type;
        }
        m_type->CopyBuffer(any.m_buffer, m_buffer);
    }

    template<typename T>
    void Assign(const T &value)
    {
        m_type->DeleteData(m_buffer);
        m_type = wxAnyValueTypeImpl<T>::sm_instance;
        wxAnyValueTypeImpl<T>::StaticSetData(value, m_buffer);
    }

    /**
        Assignment operators.
    */
    wxAny& operator=(const wxAny &any)
    {
        Assign(any);
        return *this;
    }

    wxAny& operator=(const char* value)
    {
        wxString str(value);
        Assign(str);
    }
#if wxUSE_WCHAR_T
    wxAny& operator=(const wchar_t* value)
    {
        wxString str(value);
        Assign(str);
    }
#endif
    template<typename T>
    wxAny& operator=(const T &value)
    {
        m_type->DeleteData(m_buffer);
        m_type = wxAnyValueTypeImpl<T>::sm_instance;
        wxAnyValueTypeImpl<T>::StaticSetData(value, m_buffer);
        return *this;
    }

    /**
        Equality operators.
    */
    template<typename T>
    bool operator==(T value) const
    {
        if ( !wxAnyValueTypeImpl<T>::IsSameClass(m_type) )
        {
            wxAnyValueType* otherType = wxAnyValueTypeImpl<T>::sm_instance;
            wxAnyValueBuffer temp_buf;

            bool res = m_type->ConvertValue(m_buffer,
                                            otherType,
                                            temp_buf);
            if ( !res )
                return false;
            res = value == (T) wxAnyValueTypeImpl<T>::GetValue(temp_buf);
            any.m_type->DeleteData(temp_buf);
            return res;
        }

        return value == (T) wxAnyValueTypeImpl<T>::GetValue(m_buffer);
    }

    bool operator==(const wxAny& any) const
    {
        if ( !m_type->IsSameType(any.m_type) )
        {
            wxAnyValueBuffer temp_buf;
            bool res = any.m_type->ConvertValue(any.m_buffer,
                                                m_type,
                                                temp_buf);
            if ( !res )
                return false;
            res = m_type->EqOfSameType(m_buffer, temp_buf);
            any.m_type->DeleteData(temp_buf);
            return res;
        }

        return m_type->EqOfSameType(m_buffer, any.m_buffer);
    }

    /**
        Implicit conversions from wxAny.
    */
    operator wxAny() const
    {
        wxAny any(*this);
        return any;
    }

    template<typename T>
    operator T() const
    {
        if ( !wxAnyValueTypeImpl<T>::IsSameClass(m_type) )
        {
            wxAnyValueType* otherType =
                wxAnyValueTypeImpl<T>::sm_instance;
            wxAnyValueBuffer temp_buf;

            if ( !m_type->ConvertValue(m_buffer, otherType, temp_buf) )
            {
                wxFAIL_MSG("Incorrect or non-convertible data type");
            }
            T retval = (T) wxAnyValueTypeImpl<T>::GetValue(temp_buf);
            otherType->DeleteData(temp_buf);
            return retval;
        }
        return (T) wxAnyValueTypeImpl<T>::GetValue(m_buffer);
    }

private:
    // Data
    wxAnyValueType*     m_type;
    wxAnyValueBuffer    m_buffer;
};


////////////////////////////////////////////////////////////////////
//
// SOURCE FILE PORTION
//
////////////////////////////////////////////////////////////////////

wxAnyValueType::wxAnyValueType()
{
    if ( !g_wxAnyValueTypeGlobals )
        g_wxAnyValueTypeGlobals = new wxAnyValueTypeGlobals();
    g_wxAnyValueTypeGlobals->AddValueType(this);
}

WX_IMPLEMENT_ANY_VALUE_TYPE(wxAnyNullValue)

/**
    This class is to make sure that wxAnyValueType instances
    etc. get freed correctly.
*/
class wxAnyValueTypeGlobalsManager : public wxModule
{
    DECLARE_DYNAMIC_CLASS(wxAnyValueTypeGlobalsManager)
public:
    wxAnyValueTypeGlobalsManager() : wxModule() {}
    virtual ~wxAnyValueTypeGlobalsManager() { }

    virtual bool OnInit()
    {
        return true;
    }
    virtual void OnExit()
    {
        delete g_wxAnyValueTypeGlobals;
        g_wxAnyValueTypeGlobals = NULL;
    }
private:
};

IMPLEMENT_DYNAMIC_CLASS(wxAnyValueTypeGlobalsManager, wxModule)


bool wxAnyValueTypeImplInt::ConvertValue(const wxAnyValueBuffer& src,
                                         wxAnyValueType* dstType,
                                         wxAnyValueBuffer& dst) const
{
    WX_ANY_BASE_SIGNED_INT_TYPE value = GetValue(src);
    if ( wxAnyTypeCheck(dstType, wxString) )
    {
        wxString s = wxString::Format(wxS("%ld"), (long)value);
        wxAnyValueTypeImpl<wxString>::StaticSetData(s, dst);
    }
    else
        return false;

    return true;
}

bool wxAnyValueTypeImplString::ConvertValue(const wxAnyValueBuffer& src,
                                            wxAnyValueType* dstType,
                                            wxAnyValueBuffer& dst) const
{
    wxString value = GetValue(src);
    if ( wxAnyTypeCheck(dstType, WX_ANY_BASE_SIGNED_INT_TYPE) )
    {
        WX_ANY_BASE_SIGNED_INT_TYPE value2;
        if ( !value.ToLong(&value2) )
            return false;
        wxAnyValueTypeImplInt::StaticSetData(value2, dst);
    }
    else
        return false;

    return true;
}

////////////////////////////////////////////////////////////////////
//
// TEST CODE
//
////////////////////////////////////////////////////////////////////

void TestWxAny()
{
    wxAny a(123234);
    wxAny b("abc");
    wxAny c;

    wxAny anyInt;
    wxAny anyLong;
    wxAny anyShort((short)15);
    wxAny anyChar;
    wxAny anyString("abc");

    anyChar = (signed char) 15;
    anyInt = (int)15;
    anyLong = (long)15;

    wxLogDebug("anyChar = %i",(long)anyChar);
    wxLogDebug("anyShort = %i",(long)anyShort);
    wxLogDebug("anyInt = %i",(long)anyInt);
    wxLogDebug("anyLong = %i",(long)anyLong);
    wxLogDebug("anyString = %s",((const wxString&)anyString).c_str());
    wxLogDebug("anyInt == anyChar -> %i",(int)(anyInt==anyChar));
    wxLogDebug("anyInt == anyShort -> %i",(int)(anyInt==anyShort));
    wxLogDebug("anyInt == anyLong -> %i",(int)(anyInt==anyLong));

    wxString strFromAnyString = anyString;
    wxString strFromAnyInt = anyInt;

    wxLogDebug("strFromAnyString = %s",strFromAnyString.c_str());
    wxLogDebug("strFromAnyInt = %s",strFromAnyInt.c_str());
}

