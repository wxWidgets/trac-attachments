/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xml/sax.h
// Purpose:     SAX2 implementation
// Author:      RedCAT
// Created:     2011/11/04
// Copyright:   (c) 2011 RedCAT
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_SAX_H_
#define _WX_SAX_H_

#include "wx/wx.h"
#include "wx/hashmap.h"
#include "wx/stack.h"

class wxXmlNamespaceSupport;
class wxXmlAttributes;
class wxXmlContentHandler;
class wxXmlDefaultHandler;
class wxXmlDTDHandler;
class wxXmlEntityResolver;
class wxXmlErrorHandler;
class wxXmlLexicalHandler;
class wxXmlDeclHandler;
class wxXmlInputSource;
class wxXmlLocator;
class wxXmlNamespaceSupport;
class wxXmlParseException;
class wxXmlReader;
class wxXmlSimpleReader;
class wxXmlSimpleReaderImpl;

/*
 * SAX Namespaces Support
 **/

WX_DECLARE_STRING_HASH_MAP(wxString, NamespaceMap);

class WXDLLIMPEXP_XML wxXmlNamespaceSupport {
public:
    wxXmlNamespaceSupport();
    ~wxXmlNamespaceSupport();

    bool DeclarePrefix(const wxString& prefix, const wxString& uri);

    wxString GetPrefix(const wxString& uri) const;
    wxString GetUri(const wxString& prefix) const;
    void SplitName(const wxString& qName, wxString& prefix, wxString& localName) const;
    void ProcessName(const wxString& qName, bool isAttribute, wxString& nsUri, wxString& localName) const;
    wxArrayString GetPrefixes() const;
    wxArrayString GetPrefixes(const wxString& uri) const;

    void PushContext();
    void PopContext();
    void Reset();

private:
    friend class wxXmlSimpleReader;
    
    wxStack<NamespaceMap> m_nsStack;
    NamespaceMap m_ns;
};

/*
 * SAX Attributes
 **/

class WXDLLIMPEXP_XML wxXmlAttributes {
public:
    wxXmlAttributes();
    virtual ~wxXmlAttributes();

    size_t GetIndex(const wxString& qName) const;
    size_t GetIndex(const wxString& uri, const wxString& localPart) const;
    size_t GetLength() const;
    size_t count() const { return GetLength(); }
    wxString GetLocalName(size_t index) const;
    wxString GetName(size_t index) const;
    wxString GetUri(size_t index) const;
    wxString GetType(size_t index) const;
    wxString GetType(const wxString& name) const;
    wxString GetType(const wxString& namespaceUri, const wxString& localName) const;
    wxString GetValue(size_t index) const;
    wxString GetValue(const wxString& name) const;
    wxString GetValue(const wxString& namespaceUri, const wxString& localName) const;

    void SetUri(size_t index, const wxString& value);
    void SetLocalName(size_t index, const wxString& value);
    void SetValue(size_t index, const wxString& value);

    void Clear();
    void Append(const wxString& qName, const wxString& uri, const wxString localName, const wxString& value);

private:
    struct Attribute {
        wxString qname, uri, localname, value;
    };

    wxVector<Attribute> attrsList;
};

/*
 * SAX Input Source
 **/

class WXDLLIMPEXP_XML wxXmlInputSource {
public:
    wxXmlInputSource() { m_input = NULL; }
    wxXmlInputSource(wxInputStream* input) { m_input = input; }

    virtual ~wxXmlInputSource() {}

    virtual wxInputStream* GetByteStream() const { return m_input; }
    virtual void SetByteStream(wxInputStream* byteStream) { m_input = byteStream; }

    virtual wxString GetPublicId() const { return m_publicId; }
    virtual wxString GetSystemId() const { return m_systemId; }
    virtual void SetPublicId(const wxString& val) { m_publicId = val; }
    virtual void SetSystemId(const wxString& val) { m_systemId = val; }

private:
    wxInputStream* m_input;
    wxString m_publicId;
    wxString m_systemId;
};

/*
 * SAX Exception
 **/

class WXDLLIMPEXP_XML wxXmlParseException {
public:
    explicit wxXmlParseException(const wxString &name = wxEmptyString, int col = -1, int line = -1,
                                 const wxString &p = wxEmptyString, const wxString &s = wxEmptyString);
    wxXmlParseException(const wxXmlParseException &other);
    ~wxXmlParseException();

    int GetColumnNumber() const;
    int GetLineNumber() const;
    wxString GetPublicId() const;
    wxString GetSystemId() const;
    wxString GetMessage() const;

private:
    int m_col, m_line;
    wxString m_publicId, m_systemId;
    wxString m_message;
};

/*
 * SAX Locator
 **/

class WXDLLIMPEXP_XML wxXmlLocator {
public:
    virtual ~wxXmlLocator() {}
    virtual int GetColumnNumber() const = 0;
    virtual int GetLineNumber() const = 0;
    virtual wxString GetPublicId() const = 0;
    virtual wxString GetSystemId() const = 0;
};

/*
 * XML Reader
 **/

class WXDLLIMPEXP_XML wxXmlReader {
public:
    virtual ~wxXmlReader() {}
    virtual bool GetFeature(const wxString& name, bool *ok = 0) const = 0;
    virtual void SetFeature(const wxString& name, bool value) = 0;
    virtual bool HasFeature(const wxString& name) const = 0;
    virtual void* GetProperty(const wxString& name, bool *ok = 0) const = 0;
    virtual void SetProperty(const wxString& name, void* value) = 0;
    virtual bool HasProperty(const wxString& name) const = 0;
    virtual void SetEntityResolver(wxXmlEntityResolver* handler) = 0;
    virtual wxXmlEntityResolver* GetEntityResolver() const = 0;
    virtual void SetDTDHandler(wxXmlDTDHandler* handler) = 0;
    virtual wxXmlDTDHandler* GetDTDHandler() const = 0;
    virtual void SetContentHandler(wxXmlContentHandler* handler) = 0;
    virtual wxXmlContentHandler* GetContentHandler() const = 0;
    virtual void SetErrorHandler(wxXmlErrorHandler* handler) = 0;
    virtual wxXmlErrorHandler* GetErrorHandler() const = 0;
    virtual void SetLexicalHandler(wxXmlLexicalHandler* handler) = 0;
    virtual wxXmlLexicalHandler* GetLexicalHandler() const = 0;
    virtual void SetDeclHandler(wxXmlDeclHandler* handler) = 0;
    virtual wxXmlDeclHandler* GetDeclHandler() const = 0;
    virtual bool Parse(wxXmlInputSource& input) = 0;
};

class WXDLLIMPEXP_XML wxXmlSimpleReader: public wxXmlReader,
                                         public wxXmlLocator
{
public:
    wxXmlSimpleReader();
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

    virtual bool Parse(wxXmlInputSource& input);
    virtual bool Parse(wxXmlInputSource& input, bool incremental);
    virtual bool ParseContinue();

    // Locator
    virtual int GetColumnNumber() const;
    virtual int GetLineNumber() const;
    virtual wxString GetPublicId() const;
    virtual wxString GetSystemId() const;

private:
    wxXmlSimpleReaderImpl* m_impl;
};

/*
 * SAX handler classes
 **/

class WXDLLIMPEXP_XML wxXmlContentHandler {
public:
    virtual ~wxXmlContentHandler() {}
    virtual void SetDocumentLocator(wxXmlLocator* locator) = 0;
    virtual void StartDocument() = 0;
    virtual void EndDocument() = 0;
    virtual void StartPrefixMapping(const wxString& prefix, const wxString& uri) = 0;
    virtual void EndPrefixMapping(const wxString& prefix) = 0;
    virtual void StartElement(const wxString& namespaceURI, const wxString& localName, const wxString& qName, const wxXmlAttributes& attrs) = 0;
    virtual void EndElement(const wxString& namespaceURI, const wxString& localName, const wxString& qName) = 0;
    virtual void Characters(const wxString& ch) = 0;
    virtual void IgnorableWhitespace(const wxString& ch) = 0;
    virtual void ProcessingInstruction(const wxString& target, const wxString& data) = 0;
    virtual void SkippedEntity(const wxString& name) = 0;
};


class WXDLLIMPEXP_XML wxXmlErrorHandler {
public:
    virtual ~wxXmlErrorHandler() {}
    virtual void Warning(const wxXmlParseException& exception) = 0;
    virtual void Error(const wxXmlParseException& exception) = 0;
    virtual void FatalError(const wxXmlParseException& exception) = 0;
};


class WXDLLIMPEXP_XML wxXmlDTDHandler {
public:
    virtual ~wxXmlDTDHandler() {}
    virtual void NotationDecl(const wxString& name, const wxString& publicId, const wxString& systemId) = 0;
    virtual void UnparsedEntityDecl(const wxString& name, const wxString& publicId, const wxString& systemId, const wxString& notationName) = 0;
};


class WXDLLIMPEXP_XML wxXmlEntityResolver {
public:
    virtual ~wxXmlEntityResolver() {}
    virtual wxXmlInputSource ResolveEntity(const wxString& publicId, const wxString& systemId) = 0;
};


class WXDLLIMPEXP_XML wxXmlLexicalHandler {
public:
    virtual ~wxXmlLexicalHandler() {}
    virtual void StartDTD(const wxString& name, const wxString& publicId, const wxString& systemId) = 0;
    virtual void EndDTD() = 0;
    virtual void StartEntity(const wxString& name) = 0;
    virtual void EndEntity(const wxString& name) = 0;
    virtual void StartCDATA() = 0;
    virtual void EndCDATA() = 0;
    virtual void Comment(const wxString& ch) = 0;
};


class WXDLLIMPEXP_XML wxXmlDeclHandler {
public:
    virtual ~wxXmlDeclHandler() {}
    virtual void ElementDecl(const wxString& name, const wxString& model) = 0;
    virtual void AttributeDecl(const wxString& eName, 
                               const wxString& aName, 
                               const wxString& type, 
                               const wxString& valueDefault, 
                               const wxString& value) = 0;
    virtual void InternalEntityDecl(const wxString& name, const wxString& value) = 0;
    virtual void ExternalEntityDecl(const wxString& name, const wxString& publicId, const wxString& systemId) = 0;
};



class WXDLLIMPEXP_XML wxXmlDefaultHandler: public wxXmlContentHandler, 
                                           public wxXmlErrorHandler, 
                                           public wxXmlDTDHandler, 
                                           public wxXmlEntityResolver, 
                                           public wxXmlLexicalHandler, 
                                           public wxXmlDeclHandler
{
public:
    wxXmlDefaultHandler() {}
    virtual ~wxXmlDefaultHandler() {}

    // wxXmlContentHandler interface
    virtual void SetDocumentLocator(wxXmlLocator*) {}
    virtual void StartDocument() {}
    virtual void EndDocument() {}
    virtual void StartPrefixMapping(const wxString&, const wxString&) {}
    virtual void EndPrefixMapping(const wxString&) {}
    virtual void StartElement(const wxString&, const wxString&, const wxString&, const wxXmlAttributes&) {}
    virtual void EndElement(const wxString&, const wxString&, const wxString&) {}
    virtual void Characters(const wxString&) {}
    virtual void IgnorableWhitespace(const wxString&) {}
    virtual void ProcessingInstruction(const wxString&, const wxString&) {}
    virtual void SkippedEntity(const wxString&) {}

    // wxXmlErrorHandler interface
    virtual void Warning(const wxXmlParseException&) {}
    virtual void Error(const wxXmlParseException&) {}
    virtual void FatalError(const wxXmlParseException&) {}

    // wxXmlDTDHandler interface
    virtual void NotationDecl(const wxString&, const wxString&, const wxString&) {}
    virtual void UnparsedEntityDecl(const wxString&, const wxString&, const wxString&, const wxString&) {}

    // wxXmlEntityResolver interface
    virtual wxXmlInputSource ResolveEntity(const wxString&, const wxString&) { return wxXmlInputSource(); }

    // wxXmlLexicalHandler interface
    virtual void StartDTD(const wxString&, const wxString&, const wxString&) {}
    virtual void EndDTD() {}
    virtual void StartEntity(const wxString&) {}
    virtual void EndEntity(const wxString&) {}
    virtual void StartCDATA() {}
    virtual void EndCDATA() {}
    virtual void Comment(const wxString&) {}

    // wxXmlDeclHandler interface
    virtual void ElementDecl(const wxString&, const wxString&) {}
    virtual void AttributeDecl(const wxString&, 
                               const wxString&, 
                               const wxString&, 
                               const wxString&, 
                               const wxString&) {}
    virtual void InternalEntityDecl(const wxString&, const wxString&) {}
    virtual void ExternalEntityDecl(const wxString&, const wxString&, const wxString&) {}
};

#endif