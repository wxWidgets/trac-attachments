/////////////////////////////////////////////////////////////////////////////
// Name:        xml/sax.h
// Purpose:     SAX2 interfaces
// Author:      RedCAT
// Created:     2011/05/11
// RCS-ID:      $Id$
// Copyright:   (c) 2011 RedCAT
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxXmlNamespaceSupport
    
    Encapsulate Namespace logic for use by applications using SAX, 
    or internally by SAX drivers. 

    This class encapsulates the logic of Namespace processing: it 
    tracks the declarations currently in force for each context 
    and automatically processes qualified XML names into their 
    Namespace parts; it can also be used in reverse for generating 
    XML qnames from Namespaces.

    Namespace support objects are reusable, but the reset method must 
    be invoked between each session.

    Here is a simple session:

    @code
        wxString namespaceURI,
                 localName,
                 qualifiedName;

        wxXmlNamespaceSupport support;

        support.PushContext();
        support.DeclarePrefix(wxT(""), wxT("http://www.w3.org/1999/xhtml"));
        support.DeclarePrefix(wxT("dc"), wxT("http://docs.wxwidgets.org/stable"));

        qualifiedName = wxT("p");
        support.ProcessName(qualifiedName, false, namespaceURI, localName);
        wxMessageBox(wxString::Format("Namespace URI: %s\nLocal name: %s\nQualified name: %s", 
                     namespaceURI.c_str(),
                     localName.c_str(),
                     qualifiedName.c_str()));

        qualifiedName = wxT("dc:title");
        support.ProcessName(qualifiedName, false, namespaceURI, localName);
        wxMessageBox(wxString::Format("Namespace URI: %s\nLocal name: %s\nQualified name: %s", 
                     namespaceURI.c_str(),
                     localName.c_str(),
                     qualifiedName.c_str()));

        support.PopContext();
    @endcode

    @note
    Note that this class is optimized for the use case where most elements do not 
    contain Namespace declarations: if the same prefix/URI mapping is repeated 
    for each context (for example), this class will be somewhat less efficient.

    Although SAX drivers (parsers) may choose to use this class to implement 
    namespace handling, they are not required to do so. Applications must track 
    namespace information themselves if they want to use namespace information. 

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlNamespaceSupport {
public:
    /**
        Constructor.
    */
    wxXmlNamespaceSupport();

    /**
        Destructor.
    */
    ~wxXmlNamespaceSupport();

    /**
        Declare a Namespace prefix. All prefixes must be declared before 
        they are referenced. For example, a SAX driver (parser) would 
        scan an element's attributes in two passes: first for namespace 
        declarations, then a second pass using ProcessName() to 
        interpret prefixes against (potentially redefined) prefixes.

        This method declares a prefix in the current Namespace context; 
        the prefix will remain in force until this context is popped, 
        it is shadowed in a descendant context.

        To declare the default element Namespace, use the empty string 
        as the prefix.

        @note
        Note that you must not declare a prefix after you've pushed and
        popped another Namespace context, or treated the declarations 
        phase as complete by processing a prefixed name.

        @note
        Note that there is an asymmetry in this library: GetPrefix will
        not return the "" prefix, even if you have declared a default 
        element namespace. To check for a default namespace, you have 
        to look it up explicitly using GetUri. This asymmetry exists 
        to make it easier to look up prefixes for attribute names, 
        where the default prefix is not allowed.

        @param prefix
            The prefix to declare, or the empty string to indicate the 
            default element namespace. This may never have the value 
            "xml" or "xmlns".
        @param uri
            The Namespace URI to associate with the prefix.

        Returns true if the prefix was legal, false otherwise.

        @see ProcessName(), GetPrefix(), GetUri()
    */
    bool DeclarePrefix(const wxString& prefix, const wxString& uri);

    /**
        Return one of the prefixes mapped to a Namespace URI.

        If more than one prefix is currently mapped to the same URI, 
        this method will make an arbitrary selection; if you want all 
        of the prefixes, use the GetPrefixes() method instead.

        @note
        Note: this will never return the empty (default) prefix; to 
        check for a default prefix, use the GetUri method with an 
        argument of "".

        @param uri 
            the namespace URI

        Returns one of the prefixes currently mapped to the URI 
        supplied, or null if none is mapped or if the URI is 
        assigned to the default namespace.

        @see GetPrefixes(), GetUri()
    */
    wxString GetPrefix(const wxString& uri) const;

    /**
        Look up a prefix and get the currently-mapped Namespace URI. 

        This method looks up the prefix in the current context. 
        Use the empty string ("") for the default Namespace.

        @param prefix 
            The prefix to look up. 
        
        Returns associated Namespace URI, or null if the prefix 
        is undeclared in this context.

        @see GetPrefix(), GetPrefixes()
    */
    wxString GetUri(const wxString& prefix) const;

    /**
        Splits the qualified name at the ':' and returns the prefix 
        and the local name.

        @param qName
            Qualified name.
        @param prefix
            Returned prefix.
        @param localName
            Returned local name.
        @see ProcessName()
    */
    void SplitName(const wxString& qName, wxString& prefix, wxString& localName) const;

    /**
        Process a raw XML qualified name, after all declarations in the current context 
        have been handled by DeclarePrefix().

        @param qName
            Qualified name.
        @param isAttribute
            A flag indicating whether this is an attribute name (true) or 
            an element name (false). 
        @param nsUri
            The Namespace URI return value, or an empty string if none is in use.
        @param localName
            The local name return value (without prefix).
        @see DeclarePrefix(), SplitName()
    */
    void ProcessName(const wxString& qName, bool isAttribute, wxString& nsUri, wxString& localName) const;

    /**
        Return an enumeration of all prefixes whose declarations are 
        active in the current context. This includes declarations 
        from parent contexts that have not been overridden. 

        @note
        Note: if there is a default prefix, it will not be returned 
        in this enumeration; check for the default prefix using the 
        getURI with an argument of "".

        @see GetUri()
    */
    wxArrayString GetPrefixes() const;

    /**
        Return an enumeration of all prefixes for a given URI 
        whose declarations are active in the current context. 
        This includes declarations from parent contexts that 
        have not been overridden.

        This method returns prefixes mapped to a specific 
        Namespace URI. The xml: prefix will be included. 
        If you want only one prefix that's mapped to the 
        Namespace URI, and you don't care which one you 
        get, use the GetPrefix method instead.

        @note
        Note: the empty (default) prefix is never included 
        in this enumeration; to check for the presence of 
        a default Namespace, use the getURI method with 
        an argument of "".

        @param uri 
            The Namespace URI.
        @see GetPrefix(), GetUri()
    */
    wxArrayString GetPrefixes(const wxString& uri) const;

    /**
        Start a new Namespace context. The new context 
        will automatically inherit the declarations of 
        its parent context, but it will also keep track 
        of which declarations were made within this context.

        @see PopContext()
    */
    void PushContext();

    /**
        Revert to the previous Namespace context.

        Normally, you should pop the context at 
        the end of each XML element. After popping 
        the context, all Namespace prefix mappings 
        that were previously in force are restored.

        You must not attempt to declare additional 
        Namespace prefixes after popping a context, 
        unless you push another context first.

        @see PushContext()
    */
    void PopContext();

    /**
        Reset this Namespace support object for reuse.

        It is necessary to invoke this method before 
        reusing the Namespace support object for a new 
        session. If namespace declaration URIs are to 
        be supported, that flag must also be set to a 
        non-default value. 
    */
    void Reset();
};



/**
    @class wxXmlAttributes

    The QXmlAttributes class provides XML attributes.

    If attributes are reported by QXmlContentHandler::startElement()
    this class is used to pass the attribute values.

    Use GetIndex() to locate the position of an attribute in the list, 
    GetLength() to retrieve the number of attributes, and Clear() to 
    remove the attributes. New attributes can be added with append().
    Use GetType() to get an attribute's type and GetValue() to get its value. 
    The attribute's name is available from GetLocalName() or GetName(), 
    and its namespace URI from GetUri().

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlAttributes {
public:
    /**
        Constructs an empty attribute list.
    */
    wxXmlAttributes();

    /**
        Destroys the attributes object.
    */
    virtual ~wxXmlAttributes();

    /**
        Looks up the index of an attribute by the qualified name.

        @param qName
            The qualified name.

        Returns the index of the attribute or @c wxNOT_FOUND if it wasn't found.
    */
    size_t GetIndex(const wxString& qName) const;

    /**
        This is an overloaded function.

        Looks up the index of an attribute by a namespace name.

        @param uri 
            specifies the namespace URI, or an empty string if 
            the name has no namespace URI. 

        @param localPart 
            specifies the attribute's local name

        Returns the index of the attribute, or -1 if it wasn't found.
    */
    size_t GetIndex(const wxString& uri, const wxString& localPart) const;

    /**
        Returns the number of attributes in the list.
    */
    size_t GetLength() const;

    /**
        Returns the number of attributes in the list. 
        This function is equivalent to GetLength().
    */
    size_t count() const;

    /**
        Looks up an attribute's local name for the attribute 
        at position index. If no namespace processing is done,
        the local name is an empty string.
    */
    wxString GetLocalName(size_t index) const;

    /**
        Looks up an attribute's XML 1.0 qualified name 
        for the attribute at position index.
    */
    wxString GetName(size_t index) const;

    /**
        Looks up an attribute's namespace URI for the attribute
        at position index. If no namespace processing is 
        done or if the attribute has no namespace, the namespace
        URI is an empty string.
    */
    wxString GetUri(size_t index) const;

    /**
        Looks up an attribute's type for the attribute at position index.

        Currently only "CDATA" is returned.
    */
    wxString GetType(size_t index) const;

    /**
        This is an overloaded function.

        Looks up an attribute's type for the qualified name.

        @param name
            The qualified name.

        Currently only "CDATA" is returned.
    */
    wxString GetType(const wxString& name) const;

    /**
        This is an overloaded function.

        Looks up an attribute's type by namespace name.

        @param uri 
            specifies the namespace URI. If the name has
            no namespace URI, use an empty string.
        @param localName 
            specifies the local name. 

        Currently only "CDATA" is returned.
    */
    wxString GetType(const wxString& namespaceUri, const wxString& localName) const;

    /**
        Returns an attribute's value for the attribute at
        position index. The index must be a valid position
        (i.e., 0 <= index < count()).
    */
    wxString GetValue(size_t index) const;

    /**
        This is an overloaded function.

        Returns an attribute's value for the qualified name, or
        an empty string if no attribute exists for the name given.

        @param name
            The qualified name.
    */
    wxString GetValue(const wxString& name) const;

    /**
        This is an overloaded function.

        Returns an attribute's value by namespace name.

        @param namespaceUri
            specifies the namespace URI, or an empty string 
            if the name has no namespace URI. 
        @param localName 
            specifies the attribute's local name.
    */
    wxString GetValue(const wxString& namespaceUri, const wxString& localName) const;

    void SetUri(size_t index, const wxString& value);
    void SetLocalName(size_t index, const wxString& value);
    void SetValue(size_t index, const wxString& value);

    /**
        Clears the list of attributes.
    */
    void Clear();

    /**
        Appends a new attribute entry to the list of attributes.

        @param qName
            The qualified name of the attribute.
        @param uri
            The namespace URI.
        @param localName
            The local name. 
        @param value
            The value of the attribute.

        @see GetName(), GetUri(), GetLocalName(), and GetValue().
    */
    void Append(const wxString& qName, const wxString& uri, const wxString localName, const wxString& value);
};



/**
    @class wxXmlInputSource
    
    A single input source for an XML entity.

    This class allows a SAX application to encapsulate information 
    about an input source in a single object, which may include a 
    public identifier, a system identifier, and byte stream.

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlInputSource {
public:
    /**
        Constructs an input source which contains no data.
    */
    wxXmlInputSource();

    /**
        Constructs an input source with a input stream.
    */
    wxXmlInputSource(wxInputStream* input);

    /**
        Destructor.
    */
    virtual ~wxXmlInputSource();

    /**
        Get the byte stream for this input source.
    */
    virtual wxInputStream* GetByteStream();

    /**
        Set the byte stream for this input source.

        @param byteStreaam
            Pointer to input stream.
    */
    virtual void SetByteStream(wxInputStream* byteStream);

    /**
        Get the public identifier for this input source. 
    */
    virtual wxString GetPublicId() const;
    
    /**
        Get the system identifier for this input source. 
    */
    virtual wxString GetSystemId() const;

    /**
        Set the public identifier for this input source. 
    */
    virtual void SetPublicId(const wxString& val);

    /**
        Set the system identifier for this input source. 
    */
    virtual void SetSystemId(const wxString& val);
};



/**
    @class wxXmlParseException

    Encapsulate an XML parse error.

    The wxXmlParseException class is used to report errors 
    with the wxXmlErrorHandler interface.

    The XML subsystem constructs an instance of this class when 
    it detects an error. You can retrieve the place where the
    error occurred using GetSystemId(), GetPublicId(), 
    GetLineNumber() and GetColumnNumber(), along with the 
    error GetMessage().

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlParseException {
public:
    /**
        Create a new SAXParseException.

        This constructor is most useful for parser writers.

        All parameters except the message are as if they were provided by a wxXmlLocator. 
        For example, if the system identifier is a URL (including relative filename),  
        the caller must resolve it fully before creating the exception.

        @param name
            The error or warning message.
        @param col
            The column number of the end of the text that cause the error or warning.
        @param line
            The line number of the end of the text that caused the error or warning.
        @param p
            The public identifier of the entity that generated the error or warning.
        @param s
            The system identifier of the entity that generated the error or warning.
    */
    explicit wxXmlParseException(const wxString &name = wxEmptyString, int col = -1, int line = -1,
                                 const wxString &p = wxEmptyString, const wxString &s = wxEmptyString);

    /**
        Creates a copy of other.
    */
    wxXmlParseException(const wxXmlParseException &other);

    /**
        Destroys the wxXmlParseException.
    */
    ~wxXmlParseException();

    /**
        Returns the column number where the error occurred.
    */
    int GetColumnNumber() const;

    /**
        Returns the line number where the error occurred.
    */
    int GetLineNumber() const;

    /**
        Returns the public identifier where the error occurred.
    */
    wxString GetPublicId() const;

    /**
        Returns the system identifier where the error occurred.
    */
    wxString GetSystemId() const;

    /**
        Returns the error message.
    */
    wxString GetMessage() const;
};



/**
    @class wxXmlLocator

    Interface for associating a SAX event with a document location.

    If a SAX parser provides location information to the SAX application, 
    it does so by implementing this interface and then passing an instance 
    to the application using the content handler's SetDocumentLocator method.
    The application can use the object to obtain the location of any other 
    SAX event in the XML source document.

    Note that the results returned by the object will be valid only during the
    scope of each callback method: the application will receive unpredictable
    results if it attempts to use the locator at any other time, or after 
    parsing completes.

    SAX parsers are not required to supply a locator, but they are very 
    strongly encouraged to do so. If the parser supplies a locator, it 
    must do so before reporting any other document events. If no locator 
    has been set by the time the application receives the StartDocument 
    event, the application should assume that a locator is not available.

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlLocator {
public:
    /**
        Destructor.
    */
    virtual ~wxXmlLocator();

    /**
        Return the column number where the current document event ends.
    */
    virtual int GetColumnNumber() const = 0;

    /**
        Return the line number where the current document event ends.
    */
    virtual int GetLineNumber() const = 0;

    /**
        Return the public identifier for the current document event. 
    */
    virtual wxString GetPublicId() const = 0;

    /**
        Return the system identifier for the current document event.
    */
    virtual wxString GetSystemId() const = 0;
};



/**
    @class wxXmlReader

    The wxXmlReader class provides an interface for XML readers (i.e. parsers).

    This abstract class provides an interface for all XML readers. Currently here is only
    t one implementation of a reader included in wxXML module: wxXmlSimpleReader.  

    The design of the XML classes follows the SAX2 Java interface, with the names adapted 
    to fit Wx naming conventions. It should be very easy for anybody who has worked with 
    SAX2 to get started with the wxXML classes.

    All readers use the class wxXmlInputSource to read the input document. Since you are
    normally interested in particular content in the XML document, the reader reports 
    the content through special handler classes (wxXmlDTDHandler, wxXmlDeclHandler, 
    wxXmlContentHandler, wxXmlEntityResolver, wxXmlErrorHandler and wxXmlLexicalHandler),
    which you must subclass, if you want to process the contents.

    Since the handler classes only describe interfaces you must implement all the functions.
    We provide the wxXmlDefaultHandler class to make this easier: it implements a default 
    behavior (do nothing) for all functions, so you can subclass it and just implement 
    the functions you are interested in.

    Features and properties of the reader can be set with SetFeature() and SetProperty() 
    respectively. You can set the reader to use your own subclasses with SetEntityResolver(), 
    SetDTDHandler(), SetContentHandler(), SetErrorHandler(), SetLexicalHandler() and 
    SetDeclHandler(). The parse itself is started with a call to parse().

    @see wxXmlSimpleReader

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlReader {
public:
    /**
        Destroys the reader.
    */
    virtual ~wxXmlReader();

    /**
        If the reader has the feature called name, the feature's value is returned.
        If no such feature exists the return value is undefined.

        @param name
            The feature name.
        @param ok
            If ok is not NULL: *ok is set to true if the reader has the feature
            called name; otherwise *ok is set to false.

        @see SetFeature(), HasFeature()
    */
    virtual bool GetFeature(const wxString& name, bool *ok = 0) const = 0;

    /**
        Sets the feature called name to the given value. If the reader doesn't 
        have the feature nothing happens.

        @param name
            The feature name.
        @param value
            Value which needs to be set for the given feature.

        @see GetFeature(), HasFeature()
    */
    virtual void SetFeature(const wxString& name, bool value) = 0;

    /**
        Returns true if the reader has the feature called name; otherwise returns false.

        @param name
            The feature name.

        @see GetFeature(), SetFeature()
    */
    virtual bool HasFeature(const wxString& name) const = 0;

    /**
        If the reader has the property name, this function returns the value of the property;
        otherwise the return value is undefined.

        @param name
            The property name.
        @param ok
            If ok is not 0: if the reader has the name property *ok is set to true; otherwise 
            *ok is set to false.
        
        @see SetProperty() and HasProperty().
    */
    virtual void* GetProperty(const wxString& name, bool *ok = 0) const = 0;

    /**
        Sets the property name to value. If the reader doesn't have the 
        property nothing happens.

        @param ok
            If ok is not 0: if the reader has the name property *ok is set to true; otherwise 
            *ok is set to false.

        @see HasProperty() and GetProperty()
    */
    virtual void SetProperty(const wxString& name, void* value) = 0;

    /**
        Returns true if the reader has the property; otherwise returns false.

        @param name
            The property name.

        @see GetProperty() and SetProperty()
    */
    virtual bool HasProperty(const wxString& name) const = 0;

    /**
        Sets the entity resolver.

        @param handler
            Entity resolver handler.

        @see wxXmlEntityResolver, GetEntityResolver()
    */
    virtual void SetEntityResolver(wxXmlEntityResolver* handler) = 0;

    /**
        Returns the entity resolver or NULL if none was set.

        @see wxXmlEntityResolver, SetEntityResolver()
    */
    virtual wxXmlEntityResolver* GetEntityResolver() const = 0;

    /**
        Sets the DTD handler.

        @param handler
            The DTD handler.

        @see wxXmlDTDHandler, GetDTDHandler()
    */
    virtual void SetDTDHandler(wxXmlDTDHandler* handler) = 0;

    /**
        Returns the DTD handler or NULL if none was set.

        @see wxXmlDTDHandler, SetDTDHandler()
    */
    virtual wxXmlDTDHandler* GetDTDHandler() const = 0;

    /**
        Sets the content handler.

        @param handler
            The content handler.
        
        @see wxXmlContentHandler, GetContentHandler()
    */
    virtual void SetContentHandler(wxXmlContentHandler* handler) = 0;

    /**
        Returns the content handler or NULL if none was set.

        @see wxXmlContentHandler, SetContentHandler()
    */
    virtual wxXmlContentHandler* GetContentHandler() const = 0;

    /**
        Sets the error handler.

        @param handler
            The error handler.

        @see wxXmlErrorHandler, GetErrorHandler()
    */
    virtual void SetErrorHandler(wxXmlErrorHandler* handler) = 0;

    /**
        Returns the error handler or NULL if none was set.

        @see wxXmlErrorHandler, SetErrorHandler()
    */
    virtual wxXmlErrorHandler* GetErrorHandler() const = 0;

    /**
        Sets the lexical handler.

        @param handler
            The lexical handler.

        @see wxXmlLexicalHandler, GetLexicalHandler()
    */
    virtual void SetLexicalHandler(wxXmlLexicalHandler* handler) = 0;

    /**
        Returns the lexical handler or NULL if none was set.

        @see wxXmlLexicalHandler, SetLexicalHandler()
    */
    virtual wxXmlLexicalHandler* GetLexicalHandler() const = 0;

    /**
        Sets the declaration handler.

        @param handler
            The declaration handler.

        @see wxXmlDeclHandler, GetDeclHandler()
    */
    virtual void SetDeclHandler(wxXmlDeclHandler* handler) = 0;

    /**
        Returns the declaration handler or NULL if none was set.

        @see wxXmlDeclHandler, SetDeclHandler()
    */
    virtual wxXmlDeclHandler* GetDeclHandler() const = 0;

    /**
        Reads an XML document and parses it. Returns true if 
        the parsing was successful; otherwise returns false.
    */
    virtual bool Parse(wxXmlInputSource& input) = 0;
};



/**
    @class wxXmlSimpleReader

    The QXmlSimpleReader class provides an implementation of a simple XML parser.

    This XML reader is suitable for a wide range of applications. It is able to 
    parse well-formed XML and can report the namespaces of elements to a content
    handler.

    The easiest pattern of use for this class is to create a reader instance, 
    define an input source, specify the handlers to be used by the reader, 
    and parse the data.

    Example:
    @code
        class MySAXHandler: public wxXmlDefaultHandler {
        public:
            virtual void StartDocument()
            {
                wxMessageBox(wxT("Start document!"));
            }

            virtual void EndDocument()
            {
                wxMessageBox(wxT("End of document!"));
            }
            
            virtual void StartElement(const wxString& namespaceURI, 
                                      const wxString& localName, 
                                      const wxString& qName, 
                                      const wxXmlAttributes& attrs)
            {
                wxMessageBox(wxT("Element: ") + qName);
            }

            virtual void Error(const wxXmlParseException& exception) 
            {
                wxMessageBox(wxString::Format(wxT("Error!\nLine: %d\nColumn: %d\n%s"), 
                                              exception.GetLineNumber(), 
                                              exception.GetColumnNumber(), 
                                              exception.GetMessage().c_str()), 
                             wxT("SAX Error"), wxICON_ERROR | wxOK | wxCENTRE);
            }

            virtual void FatalError(const wxXmlParseException& exception)
            {
                Error(exception);
            }
        };
        
        wxFileInputStream xmlFile(wxT("test.xml"));
        wxXmlSimpleReader reader;
        MySAXHandler handler;
        // Setting handlers for SAX events
        reader->SetContentHandler(&handler);
        reader->SetErrorHandler(&handler);
        // Parse!
        reader->Parse(wxXmlInputSource(&xmlFile));
    @endcode

    @see wxXmlDefaultHandler

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlSimpleReader: public wxXmlReader,
                                         public wxXmlLocator
{
public:
    /**
        Constructs a simple XML reader.
    */
    wxXmlSimpleReader();

    /**
        Destroys the simple XML reader.
    */
    virtual ~wxXmlSimpleReader();

    virtual bool GetFeature(const wxString& name, bool *ok = 0) const;
    virtual void SetFeature(const wxString& name, bool value);
    virtual bool HasFeature(const wxString& name) const;

    virtual void* GetProperty(const wxString& name, bool *ok = 0) const;
    virtual void SetProperty(const wxString& name, void* value);
    virtual bool HasProperty(const wxString& name) const;

    virtual void SetEntityResolver(wxXmlEntityResolver* handler);
    virtual wxXmlEntityResolver* GetEntityResolver() const;
    virtual void SetDTDHandler(wxXmlDTDHandler* handler);
    virtual wxXmlDTDHandler* GetDTDHandler() const;
    virtual void SetContentHandler(wxXmlContentHandler* handler);
    virtual wxXmlContentHandler* GetContentHandler() const;
    virtual void SetErrorHandler(wxXmlErrorHandler* handler);
    virtual wxXmlErrorHandler* GetErrorHandler() const;
    virtual void SetLexicalHandler(wxXmlLexicalHandler* handler);
    virtual wxXmlLexicalHandler* GetLexicalHandler() const;
    virtual void SetDeclHandler(wxXmlDeclHandler* handler);
    virtual wxXmlDeclHandler* GetDeclHandler() const;

    /**
        Reimplemented from wxXmlReader::Parse().

        Reads an XML document from input and parses it in one pass 
        (non-incrementally). Returns true if the parsing was 
        successful; otherwise returns false.
    */
    virtual bool Parse(wxXmlInputSource& input);

    /**
        Reads an XML document from input and parses it. Returns true if the parsing
        is completed successfully; otherwise returns false, indicating that an 
        error occurred.

        @param incremental
            If incremental is false, this function will return false if the XML file is
            not read completely. The parsing cannot be continued in this case.

            If incremental is true, the parser does not return false if it reaches the
            end of the input before reaching the end of the XML file. Instead, it 
            stores the state of the parser so that parsing can be continued later 
            when more data is available. In such a case, you can use the function 
            ParseContinue() to continue with parsing. This class stores a pointer 
            to the input source input and the ParseContinue() function tries to read 
            from that input source. Therefore, you should not delete the input source 
            input until you no longer need to call ParseContinue().

        If this function is called with incremental set to true while an incremental 
        parse is in progress, a new parsing session will be started, and the 
        previous session will be lost.

        @see ParseContinue()
    */
    virtual bool Parse(wxXmlInputSource& input, bool incremental);

    /**
        Continues incremental parsing, taking input from the wxXmlInputSource that was 
        specified with the most recent call to Parse(). To use this function, you must
        have called Parse() with the incremental argument set to true.

        Returns false if a parsing error occurs; otherwise returns true, even if the 
        end of the XML file has not been reached. You can continue parsing at a later 
        stage by calling this function again when there is more data available to parse.

        Calling this function when there is no data available in the input source 
        indicates to the reader that the end of the XML file has been reached. If the 
        input supplied up to this point was not well-formed then a parsing error occurs,
        and false is returned. If the input supplied was well-formed, true is returned. 
        It is important to end the input in this way because it allows you to reuse the 
        reader to parse other XML files.

        Calling this function after the end of file has been reached, but without 
        available data will cause false to be returned whether the previous input 
        was well-formed or not.
    */
    virtual bool ParseContinue();

    // Locator
    virtual int GetColumnNumber() const;
    virtual int GetLineNumber() const;
    virtual wxString GetPublicId() const;
    virtual wxString GetSystemId() const;
};



/**
    @class wxXmlContentHandler

    The QXmlContentHandler class provides an interface to report the 
    logical content of XML data.

    If the application needs to be informed of basic parsing events, 
    it can implement this interface and activate it using 
    wxXmlReader::SetContentHandler(). The reader can then report 
    basic document-related events like the start and end of elements
    and character data through this interface.

    The order of events in this interface is very important, and 
    mirrors the order of information in the document itself. 
    or example, all of an element's content (character data, 
    processing instructions, and sub-elements) appears, in order,
    between the StartElement() event and the corresponding 
    EndElement() event.

    The class wxXmlDefaultHandler provides a default implementation
    for this interface; subclassing from the wxXmlDefaultHandler 
    class is very convenient if you only want to be informed of 
    some parsing events.

    The StartDocument() function is called at the start of the 
    document, and EndDocument() is called at the end. Before 
    parsing begins SetDocumentLocator() is called. For each 
    element StartElement() is called, with EndElement() being 
    called at the end of each element. The Characters() function
    is called with chunks of character data; IgnorableWhitespace()
    is called with chunks of whitespace and ProcessingInstruction()
    is called with processing instructions. If an entity is skipped
    SkippedEntity() is called. At the beginning of prefix-URI 
    scopes StartPrefixMapping() is called.

    @see wxXmlDTDHandler, wxXmlDeclHandler, wxXmlEntityResolver, wxXmlErrorHandler and wxXmlLexicalHandler

    @library{wxxml}
    @category{xml}    
*/
class WXDLLIMPEXP_XML wxXmlContentHandler {
public:
    /**
        Destroys the content handler.
    */
    virtual ~wxXmlContentHandler();

    /**
        The reader calls this function before it starts parsing the document. 
        
        @param locator
            Pointer to a wxXmlLocator which allows the application to get 
            the parsing position within the document.

        Do not destroy the locator; it is destroyed when the reader is 
        destroyed. (Do not use the locator after the reader is destroyed).
    */
    virtual void SetDocumentLocator(wxXmlLocator* locator) = 0;

    /**
        The reader calls this function when it starts parsing the document.
        The reader calls this function just once, after the call to 
        SetDocumentLocator(), and before any other functions in this class 
        or in the wxXmlDTDHandler class are called.
        
        @see EndDocument()
    */
    virtual void StartDocument() = 0;

    /**
        The reader calls this function after it has finished parsing. 
        It is called just once, and is the last handler function called.
        It is called after the reader has read all input or has abandoned
        parsing because of a fatal error.

        @see StartDocument()
    */
    virtual void EndDocument() = 0;

    /**
        The reader calls this function to signal the begin of a prefix-URI 
        namespace mapping scope. This information is not necessary for normal
        namespace processing since the reader automatically replaces prefixes 
        for element and attribute names.

        Note that StartPrefixMapping() and EndPrefixMapping() calls are not 
        guaranteed to be properly nested relative to each other: all 
        StartPrefixMapping() events occur before the corresponding StartElement() 
        event, and all EndPrefixMapping() events occur after the corresponding 
        EndElement() event, but their order is not otherwise guaranteed.

        @param prefix
            The namespace prefix being declared.
        @param uri 
            The namespace URI the prefix is mapped to.
        @see EndPrefixMapping()
    */
    virtual void StartPrefixMapping(const wxString& prefix, const wxString& uri) = 0;

    /**
        The reader calls this function to signal the end of a prefix mapping 
        for the given prefix.

        @see StartPrefixMapping
    */
    virtual void EndPrefixMapping(const wxString& prefix) = 0;

    /**
        The reader calls this function when it has parsed a start element tag.

        There is a corresponding EndElement() call when the corresponding end 
        element tag is read. The StartElement() and EndElement() calls are always
        nested correctly. Empty element tags (e.g. <x/>) cause a StartElement() 
        call to be immediately followed by an EndElement() call.

        The attribute list provided only contains attributes with explicit values.
        The attribute list contains attributes used for namespace declaration 
        (i.e. attributes starting with xmlns) only if the namespace-prefix 
        property of the reader is true.

        @param namespaceURI
            The namespace URI, or an empty string if the element has no namespace URI
            or if no namespace processing is done. 
        @param localName 
            The local name (without prefix), or an empty string if no namespace 
            processing is done
        @param qName 
            The qualified name (with prefix).
        @param attrs 
            The attributes attached to the element. If there are no attributes, 
            atts is an empty attributes object.
        @see EndElement()
    */
    virtual void StartElement(const wxString& namespaceURI, const wxString& localName, const wxString& qName, const wxXmlAttributes& attrs) = 0;
    
    /**
        The reader calls this function when it has parsed an end element tag.
        
        @param qName
            The qualified element name.
        @param localName
            The local name.
        @param namespaceURI
            The namespace URI.
        @see StartElement()
    */
    virtual void EndElement(const wxString& namespaceURI, const wxString& localName, const wxString& qName) = 0;

    /**
        The reader calls this function when it has parsed a chunk of 
        character data (either normal character data or character 
        data inside a CDATA section; if you need to distinguish between
        those two types you must use wxXmlLexicalHandler::StartCDATA()
        and wxXmlLexicalHandler::EndCDATA()). The character data is 
        reported in ch.

        Some readers report whitespace in element content using the 
        IgnorableWhitespace() function rather than using this one.

        @see IgnorableWhitespace()
    */
    virtual void Characters(const wxString& ch) = 0;

    /**
        Some readers may use this function to report each chunk
        of whitespace in element content.
    */
    virtual void IgnorableWhitespace(const wxString& ch) = 0;

    /**
        The reader calls this function when it has parsed a 
        processing instruction.

        @param target
            The target name of the processing instruction.
        @param data
            The data in the processing instruction.
    */
    virtual void ProcessingInstruction(const wxString& target, const wxString& data) = 0;

    /**
        Some readers may skip entities if they have not seen the declarations
        (e.g. because they are in an external DTD). If they do so they report 
        that they skipped the entity called name by calling this function.
    */
    virtual void SkippedEntity(const wxString& name) = 0;
};



/**
    @class wxXmlErrorHandler

    The wxXmlErrorHandler class provides an interface to report errors in XML data.

    If you want your application to report errors to the user or to perform 
    customized error handling, you should subclass this class.

    You can set the error handler with wxXmlReader::SetErrorHandler().

    Errors can be reported using Warning(), Error() and FatalError().

    @see wxXmlDTDHandler, wxXmlDeclHandler, wxXmlContentHandler, wxXmlEntityResolver and wxXmlLexicalHandler

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlErrorHandler {
public:
    /**
        Destroys the error handler.
    */
    virtual ~wxXmlErrorHandler();

    /**
        A reader might use this function to report a warning. 
        Warnings are conditions that are not errors or fatal 
        errors as defined by the XML 1.0 specification.    

        @param exception
            Details of this warning.
    */
    virtual void Warning(const wxXmlParseException& exception) = 0;

    /**
        A reader might use this function to report a recoverable error. 
        A recoverable error corresponds to the definiton of "error" 
        in section 1.2 of the XML 1.0 specification. The reader must 
        continue to provide normal parsing events after invoking 
        this function.
        
        @param exception
            Details of this error.
    */
    virtual void Error(const wxXmlParseException& exception) = 0;

    /**
        A reader must use this function to report a non-recoverable error.

        @param exception
            Details of this error.
    */
    virtual void FatalError(const wxXmlParseException& exception) = 0;
};


/**
    @class wxXmlDTDHandler

    The wxXmlDTDHandler class provides an interface to report DTD content of XML data.

    If an application needs information about notations and unparsed entities, it can
    implement this interface and register an instance with wxXmlReader::SetDTDHandler().

    Note that this interface includes only those DTD events that the XML 
    recommendation requires processors to report, i.e. notation and unparsed entity 
    declarations using NotationDecl() and UnparsedEntityDecl() respectively.

    @see wxXmlDeclHandler, wxXmlContentHandler, wxXmlEntityResolver, wxXmlErrorHandler, wxXmlLexicalHandler

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlDTDHandler {
public:
    /**
        Destroys the DTD handler.
    */
    virtual ~wxXmlDTDHandler();

    /**
        The reader calls this function when it has parsed a notation declaration.

        @param name 
            The notation name.
        @param publicId 
            The notation's public identifier.
        @param systemId 
            The notation's system identifier.
    */
    virtual void NotationDecl(const wxString& name, const wxString& publicId, const wxString& systemId) = 0;

    /**
        The reader calls this function when it finds an unparsed entity declaration.

        @param name 
            The unparsed entity's name.
        @param publicId 
            The entity's public identifier.
        @param systemId 
            The entity's system identifier.
        @param notationName 
            The name of the associated notation.
    */
    virtual void UnparsedEntityDecl(const wxString& name, const wxString& publicId, const wxString& systemId, const wxString& notationName) = 0;
};



/**
    @class wxXmlEntityResolver

    The wxXmlEntityResolver class provides an interface to resolve 
    external entities contained in XML data.

    If an application needs to implement customized handling for 
    external entities, it must implement this interface, i.e. 
    ResolveEntity(), and register it with 
    wxXmlReader::SetEntityResolver().

    @see wxXmlDTDHandler, wxXmlDeclHandler, wxXmlContentHandler, wxXmlErrorHandler and wxXmlLexicalHandler

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlEntityResolver {
public:
    /**
        Destroys the entity resolver.
    */
    virtual ~wxXmlEntityResolver();

    /**
        Allow the application to resolve external entities.

        The parser will call this method before opening any external entity
        except the top-level document entity. Such entities include the 
        external DTD subset and external parameter entities referenced 
        within the DTD (in either case, only if the parser reads external 
        parameter entities), and external general entities referenced 
        within the document element (if the parser reads external 
        general entities). The application may request that the parser 
        locate the entity itself, that it use an alternative URI, or 
        that it use data provided by the application.

        @param publicId
            The public identifier of the external entity being referenced, 
            or null if none was supplied.
        @param systemId
            The system identifier of the external entity being referenced.

        Returns wxXmlInputSource object describing the new input source, 
        or null object to request that the parser open a regular URI 
        connection to the system identifier. 
    */
    virtual wxXmlInputSource ResolveEntity(const wxString& publicId, const wxString& systemId) = 0;
};



/**
    @class wxXmlLexicalHandler

    The wxXmlLexicalHandler class provides an interface to report the 
    lexical content of XML data.

    The events in the lexical handler apply to the entire document, 
    not just to the document element, and all lexical handler events 
    appear between the content handler's StartDocument and 
    EndDocument events.

    You can set the lexical handler with wxXmlReader::setLexicalHandler().

    This interface's design is based on the SAX2 extension LexicalHandler.

    The interface provides the StartDTD(), EndDTD(), StartEntity(), 
    EndEntity(), StartCDATA(), EndCDATA() and Comment() functions.

    @see wxXmlDTDHandler, wxXmlDeclHandler, wxXmlContentHandler, wxXmlEntityResolver, wxXmlErrorHandler

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlLexicalHandler {
public:
    /**
        Destroys the lexical handler.
    */
    virtual ~wxXmlLexicalHandler();

    /**
        The reader calls this function to report the start of a DTD declaration, 
        if any. It reports the name of the document type in name, the public 
        identifier in publicId and the system identifier in systemId.

        If the public identifier is missing, publicId is set to an empty string. 
        If the system identifier is missing, systemId is set to an empty string. 
        Note that it is not valid XML to have a public identifier but no system 
        identifier; in such cases a parse error will occur.

        All declarations reported through wxXmlDTDHandler or wxXmlDeclHandler 
        appear between the StartDTD() and EndDTD() calls.

        @see EndDTD()
    */
    virtual void StartDTD(const wxString& name, const wxString& publicId, const wxString& systemId) = 0;

    /**
        The reader calls this function to report the end of a DTD declaration, if any.
    */
    virtual void EndDTD() = 0;

    /**
        The reader calls this function to report the start of an entity called.

        @param name
            The entity name.

        @note
        Note that if the entity is unknown, the reader reports it through 
        wxXmlContentHandler::SkippedEntity() and not through this function.

        @see EndEntity()
    */
    virtual void StartEntity(const wxString& name) = 0;

    /**
        The reader calls this function to report the end of an entity called.

        For every StartEntity() call, there is a corresponding EndEntity() call. 
        The calls to StartEntity() and EndEntity() are properly nested.

        @param name
            The entity name.

        @see StartEntity(), wxXmlContentHandler::SkippedEntity()
    */
    virtual void EndEntity(const wxString& name) = 0;

    /**
        The reader calls this function to report the start of a CDATA section.
        The content of the CDATA section is reported through the 
        wxXmlContentHandler::Characters() function. This function is intended
        only to report the boundary.

        @see EndCDATA(), wxXmlContentHandler::Characters()
    */
    virtual void StartCDATA() = 0;

    /**
        The reader calls this function to report the end of a CDATA section.

        @see StartCDATA(), wxXmlContentHandler::Characters()
    */
    virtual void EndCDATA() = 0;

    /**
        The reader calls this function to report an XML comment anywhere 
        in the document.

        @param ch
            Text of the comment.
    */
    virtual void Comment(const wxString& ch) = 0;
};



/**
    @class wxXmlDeclHandler

    The wxXmlDeclHandler class provides an interface to report declaration
    content of XML data.

    You can set the declaration handler with wxXmlReader::SetDeclHandler().

    This interface is based on the SAX2 extension DeclHandler.

    The interface provides ElementDecl(), AttributeDecl(), InternalEntityDecl()
    and ExternalEntityDecl() functions.

    @see wxXmlDTDHandler, wxXmlContentHandler, wxXmlEntityResolver, wxXmlErrorHandler, wxXmlLexicalHandler

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlDeclHandler {
public:
    /**
        Destroys the declaration handler.
    */
    virtual ~wxXmlDeclHandler();

    /**
        Report an element type declaration.
        The content model will consist of the string "EMPTY", the string "ANY",
        or a parenthesised group, optionally followed by an occurrence indicator.
        The model will be normalized so that all parameter entities are fully 
        resolved and all whitespace is removed,and will include the enclosing 
        parentheses. Other normalization (such as removing redundant parentheses
        or simplifying occurrence indicators) is at the discretion of the parser.

        @param name
            The element type name.
        @param model
            The content model as a normalized string.
    */
    virtual void ElementDecl(const wxString& name, const wxString& model) = 0;

    /**
        The reader calls this function to report an attribute type declaration. 
        Only the effective (first) declaration for an attribute is reported.

        The reader passes the name of the associated element in eName and the 
        name of the attribute in aName. It passes a string that represents the
        attribute type in type and a string that represents the attribute 
        default in valueDefault. This string is one of "#IMPLIED", "#REQUIRED",
        "#FIXED" or an empty string (if none of the others applies). The reader
        passes the attribute's default value in value. If no default value is 
        specified in the XML file, value is an empty string.
    */
    virtual void AttributeDecl(const wxString& eName, 
                               const wxString& aName, 
                               const wxString& type, 
                               const wxString& valueDefault, 
                               const wxString& value) = 0;

    /**
        The reader calls this function to report an internal entity declaration.
        Only the effective (first) declaration is reported.

        The reader passes the name of the entity in name and the value of the 
        entity in value.
    */
    virtual void InternalEntityDecl(const wxString& name, const wxString& value) = 0;

    /**
        The reader calls this function to report a parsed external entity declaration. 
        Only the effective (first) declaration for each entity is reported.

        The reader passes the name of the entity in name, the public identifier in 
        publicId and the system identifier in systemId. If there is no public 
        identifier specified, it passes an empty string in publicId.
    */
    virtual void ExternalEntityDecl(const wxString& name, const wxString& publicId, const wxString& systemId) = 0;
};



/**
    @class wxXmlDefaultHandler

    The wxXmlDefaultHandler class provides a default implementation of 
    all the XML handler classes.

    This class gathers together the features of the specialized handler 
    classes, making it a convenient starting point when implementing 
    custom handlers for subclasses of wxXmlReader, particularly 
    wxXmlSimpleReader. The virtual functions from each of the base 
    classes are reimplemented in this class, providing sensible default
    behavior for many common cases. By subclassing this class, and 
    overriding these functions, you can concentrate on implementing 
    the parts of the handler relevant to your application.

    The XML reader must be told which handler to use for different 
    kinds of events during parsing. This means that, although 
    wxXmlDefaultHandler provides default implementations of 
    functions inherited from all its base classes, we can still 
    use specialized handlers for particular kinds of events.

    @see wxXmlDTDHandler, wxXmlDeclHandler, wxXmlContentHandler, wxXmlEntityResolver, wxXmlErrorHandler, wxXmlLexicalHandler

    @library{wxxml}
    @category{xml}
*/
class WXDLLIMPEXP_XML wxXmlDefaultHandler: public wxXmlContentHandler, 
                                           public wxXmlErrorHandler, 
                                           public wxXmlDTDHandler, 
                                           public wxXmlEntityResolver, 
                                           public wxXmlLexicalHandler, 
                                           public wxXmlDeclHandler
{
public:
    /**
        Constructs a handler for use with subclasses of QXmlReader.
    */
    wxXmlDefaultHandler();

    /**
        Destroys the handler.
    */
    virtual ~wxXmlDefaultHandler();

    // wxXmlContentHandler interface
    virtual void SetDocumentLocator(wxXmlLocator*);
    virtual void StartDocument();
    virtual void EndDocument();
    virtual void StartPrefixMapping(const wxString&, const wxString&);
    virtual void EndPrefixMapping(const wxString&);
    virtual void StartElement(const wxString&, const wxString&, const wxString&, const wxXmlAttributes&);
    virtual void EndElement(const wxString&, const wxString&, const wxString&);
    virtual void Characters(const wxString&);
    virtual void IgnorableWhitespace(const wxString&);
    virtual void ProcessingInstruction(const wxString&, const wxString&);
    virtual void SkippedEntity(const wxString&);

    // wxXmlErrorHandler interface
    virtual void Warning(const wxXmlParseException&);
    virtual void Error(const wxXmlParseException&);
    virtual void FatalError(const wxXmlParseException&);

    // wxXmlDTDHandler interface
    virtual void NotationDecl(const wxString&, const wxString&, const wxString&);
    virtual void UnparsedEntityDecl(const wxString&, const wxString&, const wxString&, const wxString&);

    // wxXmlEntityResolver interface
    virtual wxXmlInputSource ResolveEntity(const wxString&, const wxString&);

    // wxXmlLexicalHandler interface
    virtual void StartDTD(const wxString&, const wxString&, const wxString&);
    virtual void EndDTD();
    virtual void StartEntity(const wxString&);
    virtual void EndEntity(const wxString&);
    virtual void StartCDATA();
    virtual void EndCDATA();
    virtual void Comment(const wxString&);

    // wxXmlDeclHandler interface
    virtual void ElementDecl(const wxString&, const wxString&);
    virtual void AttributeDecl(const wxString&, 
                               const wxString&, 
                               const wxString&, 
                               const wxString&, 
                               const wxString&);
    virtual void InternalEntityDecl(const wxString&, const wxString&);
    virtual void ExternalEntityDecl(const wxString&, const wxString&, const wxString&);
};