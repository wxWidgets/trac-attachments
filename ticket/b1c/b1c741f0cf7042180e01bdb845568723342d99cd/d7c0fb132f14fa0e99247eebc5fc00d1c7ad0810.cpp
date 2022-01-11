//
// wxAny draft, version 2
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
#include "wx/meta/if.h"

class wxAny;
class wxAnyValueType;

#define WX_ANY_VALUE_BUFFER_SIZE    16

union wxAnyValueBuffer
{
    void*   m_ptr;
    wxByte  m_buffer[WX_ANY_VALUE_BUFFER_SIZE];
};

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
        Implement this for buffer-to-buffer copy. src.m_ptr can
        be excepted to be NULL if value type of previously stored
        data was different.
    */
    virtual void CopyBuffer(const wxAnyValueBuffer& src,
                            wxAnyValueBuffer& dst) const = 0;

    /**
        Equality test of two datas with same type.
    */
    virtual bool EqOfSameType(const wxAnyValueBuffer& buf1,
                              const wxAnyValueBuffer& buf2) const = 0;

    /**
        Convert value into buffer of different type. Return false if
        not possible.
    */
    virtual bool ConvertValue(const wxAnyValueBuffer& src,
                              wxAnyValueType* dstType,
                              wxAnyValueBuffer& dst) const = 0;

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


/**
    Following are helper classes for the wxAnyValueTypeImplBase.
*/
namespace wxPrivate
{

template<typename T>
class wxAnyValueTypeOpsMovable
{
public:
    static void DeleteData(wxAnyValueBuffer& buf)
    {
        wxUnusedVar(buf);
    }

    static void CopyBuffer(const wxAnyValueBuffer& src,
                           wxAnyValueBuffer& dst)
    {
        memcpy(dst.m_buffer, src.m_buffer, sizeof(T));
    }

    static void SetValue(const T& value,
                         wxAnyValueBuffer& buf)
    {
        memcpy(buf.m_buffer, &value, sizeof(T));
    }

    static const T& GetValue(const wxAnyValueBuffer& buf)
    {
        return *(reinterpret_cast<const T*>(&buf.m_buffer[0]));
    }

    static bool EqOfSameType(const wxAnyValueBuffer& buf1,
                             const wxAnyValueBuffer& buf2)
    {
        T v1;
        memcpy(&v1, buf1.m_buffer, sizeof(T));
        T v2;
        memcpy(&v2, buf2.m_buffer, sizeof(T));
        return v1 == v2;
    }
};


template<typename T>
class wxAnyValueTypeOpsGeneric
{
public:
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

    static void DeleteData(wxAnyValueBuffer& buf)
    {
        DataHolder<T>* holder = static_cast<DataHolder<T>*>(buf.m_ptr);
        delete holder;
    }

    static void CopyBuffer(const wxAnyValueBuffer& src,
                           wxAnyValueBuffer& dst)
    {
        // Free old data
        DataHolder<T>* holder;
        holder = static_cast<DataHolder<T>*>(dst.m_ptr);
        delete holder;

        // Allocate new data
        holder = static_cast<DataHolder<T>*>(src.m_ptr);
        holder = new DataHolder<T>(holder->m_value);
        dst.m_ptr = holder;
    }

    static void SetValue(const T& value,
                         wxAnyValueBuffer& buf)
    {
        DataHolder<T>* holder = new DataHolder<T>(value);
        buf.m_ptr = holder;
    }

    static const T& GetValue(const wxAnyValueBuffer& buf)
    {
        DataHolder<T>* holder = static_cast<DataHolder<T>*>(buf.m_ptr);
        return holder->m_value;
    }

    static bool EqOfSameType(const wxAnyValueBuffer& buf1,
                             const wxAnyValueBuffer& buf2)
    {
        DataHolder<T>* holder1 = static_cast<DataHolder<T>*>(buf1.m_ptr);
        DataHolder<T>* holder2 = static_cast<DataHolder<T>*>(buf2.m_ptr);
        return holder1->m_value == holder2->m_value;
    }
};

} // namespace wxPrivate


/*
    Generic value type implementation. This is intermediate class
    so we can derive from this same value type for multiple
    actual types (for instance, we can have wxAnyValueTypeImplInt
    for all signed integer types).
*/
template<typename T>
class wxAnyValueTypeImplBase : public wxAnyValueType
{
    typedef typename wxIf< wxIsMovable<T>::value &&
                                sizeof(T) <= WX_ANY_VALUE_BUFFER_SIZE,
                           wxPrivate::wxAnyValueTypeOpsMovable<T>,
                           wxPrivate::wxAnyValueTypeOpsGeneric<T> >::value
            Ops;

    WX_DECLARE_ANY_VALUE_TYPE_IN_CLASS(T, wxAnyValueTypeImplBase)
public:
    wxAnyValueTypeImplBase() : wxAnyValueType() { }
    virtual ~wxAnyValueTypeImplBase() { }

    virtual void DeleteData(wxAnyValueBuffer& buf) const
    {
        Ops::DeleteData(buf);
        buf.m_ptr = NULL;  // This is important
    }

    virtual void CopyBuffer(const wxAnyValueBuffer& src,
                            wxAnyValueBuffer& dst) const
    {
        return Ops::CopyBuffer(src, dst);
    }

    /**
        It is important to reimplement this in any specialized template
        classes that inherit from wxAnyValueTypeImplBase.
    */
    static void SetValue(const T& value,
                         wxAnyValueBuffer& buf)
    {
        return Ops::SetValue(value, buf);
    }

    /**
        It is important to reimplement this in any specialized template
        classes that inherit from wxAnyValueTypeImplBase.
    */
    static const T& GetValue(const wxAnyValueBuffer& buf)
    {
        return Ops::GetValue(buf);
    }

    virtual bool EqOfSameType(const wxAnyValueBuffer& buf1,
                              const wxAnyValueBuffer& buf2) const
    {
        return Ops::EqOfSameType(buf1, buf2);
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
    Integer value type implementation.
*/

#ifdef wxLongLong_t
    typedef wxLongLong_t wxAnyBaseIntType;
    typedef wxULongLong_t wxAnyBaseUintType;
#else
    typedef long wxAnyBaseIntType;
    typedef unsigned long wxAnyBaseUintType;
#endif


class wxAnyValueTypeImplInt :
    public wxAnyValueTypeImplBase<wxAnyBaseIntType>
{
public:
    wxAnyValueTypeImplInt() :
        wxAnyValueTypeImplBase<wxAnyBaseIntType>() { }
    virtual ~wxAnyValueTypeImplInt() { }

    virtual bool ConvertValue(const wxAnyValueBuffer& src,
                              wxAnyValueType* dstType,
                              wxAnyValueBuffer& dst) const;
};


class wxAnyValueTypeImplUint :
    public wxAnyValueTypeImplBase<wxAnyBaseUintType>
{
public:
    wxAnyValueTypeImplUint() :
        wxAnyValueTypeImplBase<wxAnyBaseUintType>() { }
    virtual ~wxAnyValueTypeImplUint() { }

    virtual bool ConvertValue(const wxAnyValueBuffer& src,
                              wxAnyValueType* dstType,
                              wxAnyValueBuffer& dst) const;
};


#define WX_ANY_DEFINE_INT_TYPE(T, INTTYPE) \
template<> \
class wxAnyValueTypeImpl<T> : public wxAnyValueTypeImpl##INTTYPE \
{ \
    typedef wxAnyBase##INTTYPE##Type UseIntType; \
public: \
    wxAnyValueTypeImpl() : wxAnyValueTypeImpl##INTTYPE() { } \
    virtual ~wxAnyValueTypeImpl() { } \
    static void SetValue(const T& value, wxAnyValueBuffer& buf) \
    { \
        *(reinterpret_cast<UseIntType*>(&buf.m_buffer[0])) = \
            static_cast<UseIntType>(value); \
    } \
    static T GetValue(const wxAnyValueBuffer& buf) \
    { \
        return static_cast<T>( \
            *(reinterpret_cast<const UseIntType*>(&buf.m_buffer[0]))); \
    } \
};

WX_ANY_DEFINE_INT_TYPE(signed long, Int)
WX_ANY_DEFINE_INT_TYPE(signed int, Int)
WX_ANY_DEFINE_INT_TYPE(signed short, Int)
WX_ANY_DEFINE_INT_TYPE(signed char, Int)
#ifdef wxLongLong_t
WX_ANY_DEFINE_INT_TYPE(wxLongLong_t, Int)
#endif

WX_ANY_DEFINE_INT_TYPE(unsigned long, Uint)
WX_ANY_DEFINE_INT_TYPE(unsigned int, Uint)
WX_ANY_DEFINE_INT_TYPE(unsigned short, Uint)
WX_ANY_DEFINE_INT_TYPE(unsigned char, Uint)
#ifdef wxLongLong_t
WX_ANY_DEFINE_INT_TYPE(wxULongLong_t, Uint)
#endif

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


namespace wxPrivate
{

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

    void RegisterValueType(wxAnyValueType* valueType)
    {
        m_valueTypes.push_back(valueType);
    }

private:
    wxVector<wxAnyValueType*>   m_valueTypes;
};

extern wxAnyValueTypeGlobals* g_wxAnyValueTypeGlobals;


/*
    Let's define a discrete Null value so we don't have to really
    ever check if wxAny.m_type pointer is NULL or not. This is an
    optimization, mostly. Implementation of this value type is
    "hidden" in the source file.
*/
extern wxAnyValueType* wxAnyNullValueType;

} // namespace wxPrivate


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
        m_type = wxPrivate::wxAnyNullValueType;
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
        m_type = wxPrivate::wxAnyNullValueType;
        Assign(wxString(value));
    }
#if wxUSE_WCHAR_T
    wxAny(const wchar_t* value)
    {
        m_type = wxPrivate::wxAnyNullValueType;
        Assign(wxString(value));
    }
#endif

    wxAny(const wxAny& any)
    {
        m_type = wxPrivate::wxAnyNullValueType;
        Assign(any);
    }

    template<typename T>
    wxAny(const T& value)
    {
        m_type = wxAnyValueTypeImpl<T>::sm_instance;
        wxAnyValueTypeImpl<T>::SetValue(value, m_buffer);
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
        wxAnyValueTypeImpl<T>::SetValue(value, m_buffer);
    }

    /**
        Returns current wxAnyValueType.
    */
    wxAnyValueType* GetType() const
    {
        return m_type;
    }

    /**
        Makes wxAny null, ie. clears it.
    */
    void MakeNull()
    {
        m_type->DeleteData(m_buffer);
        m_type = wxPrivate::wxAnyNullValueType;
    }

    /**
        Assignment operators.
    */
    wxAny& operator=(const wxAny &any)
    {
        Assign(any);
        return *this;
    }

    template<typename T>
    wxAny& operator=(const T &value)
    {
        m_type->DeleteData(m_buffer);
        m_type = wxAnyValueTypeImpl<T>::sm_instance;
        wxAnyValueTypeImpl<T>::SetValue(value, m_buffer);
        return *this;
    }

    wxAny& operator=(const char* value)
        { Assign(wxString(value)); }
    wxAny& operator=(const wchar_t* value)
        { Assign(wxString(value)); }

    /**
        Equality operators.
    */
    template<typename T>
    bool operator==(T value) const
    {
        if ( !wxAnyValueTypeImpl<T>::IsSameClass(m_type) )
            return false;

        return value ==
            static_cast<T>(wxAnyValueTypeImpl<T>::GetValue(m_buffer));
    }

    bool operator==(const wxAny& any) const
    {
        if ( !m_type->IsSameType(any.m_type) )
            return false;

        return m_type->EqOfSameType(m_buffer, any.m_buffer);
    }

    bool operator==(const char* value) const
        { return (*this) == wxString(value); }
    bool operator==(const wchar_t* value) const
        { return (*this) == wxString(value); }

    /**
        Inequality operators.
    */
    template<typename T>
    bool operator!=(T value) const
    {
        return !((*this) == T);
    }

    bool operator!=(const wxAny& any) const
    {
        return !((*this) == any);
    }

    bool operator!=(const char* value) const
        { return !((*this) == value); }
    bool operator!=(const wchar_t* value) const
        { return !((*this) == value); }

    /**
        Explicit conversions from wxAny.
    */
    template<typename T>
    T As() const
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
            T retval =
                static_cast<T>(wxAnyValueTypeImpl<T>::GetValue(temp_buf));
            otherType->DeleteData(temp_buf);
            return retval;
        }
        return static_cast<T>(wxAnyValueTypeImpl<T>::GetValue(m_buffer));
    }

    template<typename T>
    bool GetAs(T* value) const
    {
        if ( !wxAnyValueTypeImpl<T>::IsSameClass(m_type) )
        {
            wxAnyValueType* otherType =
                wxAnyValueTypeImpl<T>::sm_instance;
            wxAnyValueBuffer temp_buf;

            if ( !m_type->ConvertValue(m_buffer, otherType, temp_buf) )
                return false;

            *value =
                static_cast<T>(wxAnyValueTypeImpl<T>::GetValue(temp_buf));
            otherType->DeleteData(temp_buf);

            return true;
        }
        *value = static_cast<T>(wxAnyValueTypeImpl<T>::GetValue(m_buffer));
        return true;
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

using namespace wxPrivate;

wxAnyValueType::wxAnyValueType()
{
    if ( !g_wxAnyValueTypeGlobals )
        g_wxAnyValueTypeGlobals = new wxAnyValueTypeGlobals();

    g_wxAnyValueTypeGlobals->RegisterValueType(this);
}

wxAnyValueTypeGlobals* wxPrivate::g_wxAnyValueTypeGlobals = NULL;

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
        delete wxPrivate::g_wxAnyValueTypeGlobals;
        wxPrivate::g_wxAnyValueTypeGlobals = NULL;
    }
private:
};

IMPLEMENT_DYNAMIC_CLASS(wxAnyValueTypeGlobalsManager, wxModule)


bool wxAnyValueTypeImplInt::ConvertValue(const wxAnyValueBuffer& src,
                                         wxAnyValueType* dstType,
                                         wxAnyValueBuffer& dst) const
{
    wxAnyBaseIntType value = GetValue(src);
    if ( wxAnyTypeCheck(dstType, wxString) )
    {
#ifdef wxLongLong_t
        wxLongLong ll(value);
        wxString s = ll.ToString();
#else
        wxString s = wxString::Format(wxS("%ld"), (long)value);
#endif
        wxAnyValueTypeImpl<wxString>::SetValue(s, dst);
    }
    else if ( wxAnyTypeCheck(dstType, wxAnyBaseUintType) )
    {
        if ( value < 0 )
            return false;
        wxAnyBaseUintType ul = (wxAnyBaseUintType) value;
        wxAnyValueTypeImplUint::SetValue(ul, dst);
    }
    else
        return false;

    return true;
}

bool wxAnyValueTypeImplUint::ConvertValue(const wxAnyValueBuffer& src,
                                          wxAnyValueType* dstType,
                                          wxAnyValueBuffer& dst) const
{
    wxAnyBaseUintType value = GetValue(src);
    if ( wxAnyTypeCheck(dstType, wxString) )
    {
#ifdef wxLongLong_t
        wxULongLong ull(value);
        wxString s = ull.ToString();
#else
        wxString s = wxString::Format(wxS("%lu"), (long)value);
#endif
        wxAnyValueTypeImpl<wxString>::SetValue(s, dst);
    }
    else if ( wxAnyTypeCheck(dstType, wxAnyBaseIntType) )
    {
#ifdef wxLongLong_t
        const wxAnyBaseUintType UseIntMax = wxINT64_MAX;
#else
        const wxAnyBaseUintType UseIntMax = LONG_MAX;
#endif
        if ( value > UseIntMax )
            return false;
        wxAnyBaseIntType l = (wxAnyBaseIntType) value;
        wxAnyValueTypeImplInt::SetValue(l, dst);
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
    if ( wxAnyTypeCheck(dstType, wxAnyBaseIntType) )
    {
        wxAnyBaseIntType value2;
#ifdef wxLongLong_t
        if ( !value.ToLongLong(&value2) )
#else
        if ( !value.ToLong(&value2) )
#endif
            return false;
        wxAnyValueTypeImplInt::SetValue(value2, dst);
    }
    else if ( wxAnyTypeCheck(dstType, wxAnyBaseUintType) )
    {
        wxAnyBaseUintType value2;
#ifdef wxLongLong_t
        if ( !value.ToULongLong(&value2) )
#else
        if ( !value.ToULong(&value2) )
#endif
            return false;
        wxAnyValueTypeImplUint::SetValue(value2, dst);
    }
    else
        return false;

    return true;
}

//
//  wxAnyNullValueType implementation.
//
class wxAnyNullValue
{
public:
    void*   m_dummy;
};

template <>
class wxAnyValueTypeImpl<wxAnyNullValue> : public wxAnyValueType
{
    WX_DECLARE_ANY_VALUE_TYPE(wxAnyNullValue)
public:
    virtual void DeleteData(wxAnyValueBuffer& buf) const
    {
        buf.m_ptr = NULL;  // This is important
    }

    // Dummy implementations
    virtual void CopyBuffer(const wxAnyValueBuffer& src,
                            wxAnyValueBuffer& dst) const
    {
        wxUnusedVar(src);
        wxUnusedVar(dst);
    }

    virtual bool EqOfSameType(const wxAnyValueBuffer& buf1,
                              const wxAnyValueBuffer& buf2) const
    {
        wxUnusedVar(buf1);
        wxUnusedVar(buf2);
        return false;
    }

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

WX_IMPLEMENT_ANY_VALUE_TYPE(wxAnyNullValue)

wxAnyValueType* wxPrivate::wxAnyNullValueType =
    wxAnyValueTypeImpl<wxAnyNullValue>::GetInstance();

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
    wxAny anyLongLong;
    wxAny anyULongLong;
    wxAny anyShort((short)15);
    wxAny anyChar;
    wxAny anyString("abc");

    anyChar = (signed char) 15;
    anyInt = (int)15;
    anyLong = (long)15;
    anyLongLong = wxLL(15);
    anyULongLong = wxULL(15);

    wxLogDebug("anyChar = %i",anyChar.As<long>());
    wxLogDebug("anyShort = %i",anyShort.As<long>());
    wxLogDebug("anyInt = %i",anyInt.As<long>());
    wxLogDebug("anyLong = %i",anyLong.As<long>());
    wxLogDebug("anyLongLong = %i",anyLong.As<long>());
    wxLogDebug("anyULongLong = %i",anyLong.As<unsigned long>());
    wxLogDebug("anyString = %s",anyString.As<wxString>().c_str());
    wxLogDebug("anyInt == anyChar -> %i",(int)(anyInt==anyChar));
    wxLogDebug("anyInt == anyShort -> %i",(int)(anyInt==anyShort));
    wxLogDebug("anyInt == anyLong -> %i",(int)(anyInt==anyLong));
    wxLogDebug("anyInt == anyLongLong -> %i",(int)(anyInt==anyLongLong));

    //
    // Note that while underlying numeric values here are the same,
    // the comparison returns false since signed and unsigned integers
    // use different class types (ie. explicit conversion is required).
    wxLogDebug("anyInt == anyULongLong -> %i",(int)(anyInt==anyULongLong));

    // Like here...
    wxLogDebug("anyInt == anyULongLong.As<int>() -> %i",
               (int)(anyInt==anyULongLong.As<int>()));

    wxLogDebug("anyString(\"abc\") == \"abc\" -> %i",
               (int)(anyString==wxS("abc")));

    wxString strFromAnyString = anyString.As<wxString>();
    wxString strFromAnyInt;

    if ( !anyInt.GetAs(&strFromAnyInt) )
        strFromAnyInt = "<conversion failed>";

    wxLogDebug("strFromAnyString = %s",strFromAnyString.c_str());
    wxLogDebug("strFromAnyInt = %s",strFromAnyInt.c_str());
}

