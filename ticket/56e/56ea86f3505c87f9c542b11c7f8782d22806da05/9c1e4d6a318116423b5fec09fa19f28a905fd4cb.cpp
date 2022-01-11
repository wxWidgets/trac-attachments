/////////////////////////////////////////////////////////////////////////////
// Name:        src/xml/xml.cpp
// Purpose:     SAX2 implementation
// Author:      RedCAT
// Created:     2011/11/04
// Copyright:   (c) 2000 RedCAT
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"
#include "wx/xml/sax.h"
#include "expat.h"

/*
 * SAX Namespaces Support
 **/

wxXmlNamespaceSupport::wxXmlNamespaceSupport()
{
    Reset();
}

wxXmlNamespaceSupport::~wxXmlNamespaceSupport()
{
}

bool wxXmlNamespaceSupport::DeclarePrefix(const wxString& prefix, const wxString& uri)
{
    if (prefix == wxT("xml") || prefix == wxT("xmlns"))
        return false;

    m_ns[prefix] = uri;
    return true;
}

wxString wxXmlNamespaceSupport::GetPrefix(const wxString& uri) const
{
    NamespaceMap::const_iterator itc, it = m_ns.begin();
    while ((itc = it) != m_ns.end()) {
        ++it;
        if (itc->second == uri && !itc->first.empty())
            return itc->second;
    }
    return wxEmptyString;
}

wxString wxXmlNamespaceSupport::GetUri(const wxString& prefix) const
{
    NamespaceMap::const_iterator iter = m_ns.find(prefix);
    if (iter != m_ns.end())
        return iter->second;
    return wxEmptyString;
}

void wxXmlNamespaceSupport::SplitName(const wxString& qName, wxString& prefix, wxString& localName) const
{
    int pos = qName.Index(L':');
    if (pos == -1)
        pos = qName.size();

    prefix = qName.Left(pos);
    localName = qName.Mid(pos+1);
}

void wxXmlNamespaceSupport::ProcessName(const wxString& qName, bool isAttribute, wxString& nsUri, wxString& localName) const
{
    int pos = qName.Index(L':');
    if (pos != -1) {
        nsUri = GetUri(qName.Left(pos));
        localName = qName.Mid(pos+1);
        return;
    }

    nsUri.clear();

    if (!isAttribute && !m_ns.empty()) {
        NamespaceMap::const_iterator iter = m_ns.begin();
        if (iter->first.empty())
            nsUri = iter->second;
    }

    localName = qName;
}

wxArrayString wxXmlNamespaceSupport::GetPrefixes() const
{
    wxArrayString list;

    NamespaceMap::const_iterator itc, it = m_ns.begin();
    while ((itc = it) != m_ns.end()) {
        ++it;
        if (!itc->first.empty())
            list.Add(itc->first);
    }

    return list;
}

wxArrayString wxXmlNamespaceSupport::GetPrefixes(const wxString& uri) const
{
    wxArrayString list;

    NamespaceMap::const_iterator itc, it = m_ns.begin();
    while ((itc = it) != m_ns.end()) {
        ++it;
        if (itc->second == uri && !itc->first.empty())
            list.Add(itc->first);
    }

    return list;
}

void wxXmlNamespaceSupport::PushContext()
{
    m_nsStack.push(m_ns);
}

void wxXmlNamespaceSupport::PopContext()
{
    m_ns.clear();
    if (!m_nsStack.empty()) {
        m_ns = m_nsStack.top();
        m_nsStack.pop();
    }
}

void wxXmlNamespaceSupport::Reset()
{
    while (!m_nsStack.empty())
        m_nsStack.pop();
    m_ns.clear();
    m_ns["xml"] = "http://www.w3.org/XML/1998/namespace";
}


/*
 * SAX Attributes
 **/

wxXmlAttributes::wxXmlAttributes()
{
}

wxXmlAttributes::~wxXmlAttributes()
{
}

size_t wxXmlAttributes::GetIndex(const wxString& qName) const
{
    for (size_t i = 0; i < attrsList.size(); i++) {
        if (attrsList[i].qname == qName)
            return i;
    }

    return wxNOT_FOUND;
}

size_t wxXmlAttributes::GetIndex(const wxString& uri, const wxString& localPart) const
{
    for (size_t i = 0; i < attrsList.size(); i++) {
        if (attrsList[i].uri == uri && attrsList[i].localname == localPart)
            return i;
    }

    return wxNOT_FOUND;
}

size_t wxXmlAttributes::GetLength() const
{
    return attrsList.size();
}

wxString wxXmlAttributes::GetLocalName(size_t index) const
{
    return attrsList[index].localname;
}

wxString wxXmlAttributes::GetName(size_t index) const
{
    return attrsList[index].qname;
}

wxString wxXmlAttributes::GetUri(size_t index) const
{
    return attrsList[index].uri;
}

wxString wxXmlAttributes::GetType(size_t/* index */) const
{
    return "CDATA";
}

wxString wxXmlAttributes::GetType(const wxString&/* name */) const
{
    return "CDATA";
}

wxString wxXmlAttributes::GetType(const wxString&/* namespaceUri */, const wxString&/* localName */) const
{
    return "CDATA";
}

wxString wxXmlAttributes::GetValue(size_t index) const
{
    return attrsList[index].value;
}

wxString wxXmlAttributes::GetValue(const wxString& name) const
{
    size_t i = GetIndex(name);
    if (i == wxNOT_FOUND)
        return wxEmptyString;
    return attrsList[i].value;
}

wxString wxXmlAttributes::GetValue(const wxString& namespaceUri, const wxString& localName) const
{
    size_t i = GetIndex(namespaceUri, localName);
    if (i != wxNOT_FOUND)
        return attrsList[i].value;
    return wxEmptyString;
}

void wxXmlAttributes::SetUri(size_t index, const wxString& value)
{
    attrsList[index].uri = value;
}

void wxXmlAttributes::SetLocalName(size_t index, const wxString& value)
{
    attrsList[index].localname = value;
}

void wxXmlAttributes::SetValue(size_t index, const wxString& value)
{
    attrsList[index].value = value;
}

void wxXmlAttributes::Clear()
{
    attrsList.clear();
}

void wxXmlAttributes::Append(const wxString& qName, const wxString& uri, const wxString localName, const wxString& value)
{
    Attribute attr;
    attr.localname = localName;
    attr.qname = qName;
    attr.uri = uri;
    attr.value = value;

    attrsList.push_back(attr);
}

/*
 * SAX Exception
 **/

wxXmlParseException::wxXmlParseException(const wxString &name, int col, int line, const wxString &p, const wxString &s)
    : m_col(col), m_line(line), m_publicId(p), m_systemId(s), m_message(name)
{
}

wxXmlParseException::wxXmlParseException(const wxXmlParseException &other)
{
    m_col = other.m_col;
    m_line = other.m_line;
    m_publicId = other.m_publicId;
    m_systemId = other.m_systemId;
    m_message = other.m_message;
}

wxXmlParseException::~wxXmlParseException()
{
}

int wxXmlParseException::GetColumnNumber() const
{
    return m_col;
}

int wxXmlParseException::GetLineNumber() const
{
    return m_line;
}

wxString wxXmlParseException::GetPublicId() const
{
    return m_publicId;
}

wxString wxXmlParseException::GetSystemId() const
{
    return m_systemId;
}

wxString wxXmlParseException::GetMessage() const
{
    return m_message;
}

/*
 * XML Reader
 **/
extern "C" {

void CharacterData(void* userData, const XML_Char* txt, int txtlen);
void StartElement(void* userData, const XML_Char* qName, const XML_Char** atts);
void EndElement(void* userData, const XML_Char* qName);
void ProcessingInstruction(void* userData, const XML_Char* target, const XML_Char* data);
void ElementDeclaration(void* userData, const XML_Char* name, XML_Content* model);
void convertXML_Content(wxString& str, const XML_Content* model, bool isChild = false);
void AttListDeclaration(void* userData,
                        const XML_Char* elname,
                        const XML_Char* attname,
                        const XML_Char* att_type,
                        const XML_Char* dflt,
                        int isrequired);
void EntityDeclaration(void* userData, 
                       const XML_Char* entityName,
                       int is_parameter_entity,
                       const XML_Char* value,
                       int value_length,
                       const XML_Char* base,
                       const XML_Char* systemId,
                       const XML_Char* publicId,
                       const XML_Char* notationName);
void NotationDeclaration(void* userData,
                         const XML_Char* notationName,
                         const XML_Char* /* base */,
                         const XML_Char* systemId,
                         const XML_Char* publicId);
void StartDoctypeDecl(void* userData,
 				      const XML_Char* doctypeName,
				      const XML_Char* systemId,
					  const XML_Char* publicId,
					  int /* has_internal_subset */);
void EndDoctypeDecl(void* userData);
void StartCdataSection(void* userData);
void EndCdataSection(void* userData);
void CommentHandler(void* userData, const XML_Char* data);
int ExternalEntityRefHandler(XML_Parser parser, 
                             const XML_Char* context,
                             const XML_Char* base,
                             const XML_Char* systemId,
                             const XML_Char* publicId);

};

// Implemetation class

WX_DECLARE_STRING_HASH_MAP(wxString, EntitiesMap);

class wxXmlSimpleReaderImpl {
public:
    wxXmlSimpleReaderImpl()
    {
        m_useNamespaces = true;
        m_useNamespacePrefixes = false;
        m_externalResolving = false;
        m_entityResolver = NULL;
        m_DTDHandler = NULL;
        m_contentHandler = NULL;
        m_errorHandler = NULL;
        m_lexHandler = NULL;
        m_declHandler = NULL;
        m_incrementalParsing = false;
        m_opTags = 0;
    }

    void DoError(const wxString& name, bool fatal = false)
    {
        if (m_errorHandler) {
            if (fatal)
                m_errorHandler->FatalError(wxXmlParseException(name, 
                                                               XML_GetCurrentColumnNumber(m_parser), 
                                                               XML_GetCurrentLineNumber(m_parser),
                                                               m_publicId,
                                                               m_systemId));
            else
                m_errorHandler->Error(wxXmlParseException(name, 
                                                          XML_GetCurrentColumnNumber(m_parser), 
                                                          XML_GetCurrentLineNumber(m_parser),
                                                          m_publicId,
                                                          m_systemId));
        }

        m_incrementalParsing = false;
    }

    bool DoParse(const wxXmlInputSource& src, XML_Parser parser)
    {
        const size_t BUFSIZE = 1024;
        char buf[BUFSIZE];
        bool done = false;
        do {
            size_t len = src.GetByteStream()->Read(buf, BUFSIZE).LastRead();
            done = (len < BUFSIZE);
            if (!XML_Parse(parser, buf, len, done)) {
                DoError(wxString::Format(_("XML parsing error: '%s'"), XML_ErrorString(XML_GetErrorCode(parser))), true);
                return false;
            }
        } while (!done);
        return true;
    }

    void SetParserCallbacks()
    {
        XML_SetUserData(m_parser, this);
        XML_SetCharacterDataHandler(m_parser, CharacterData);
        XML_SetElementHandler(m_parser, StartElement, EndElement);
        XML_SetElementDeclHandler(m_parser, ElementDeclaration);
        XML_SetAttlistDeclHandler(m_parser, AttListDeclaration);
        XML_SetEntityDeclHandler(m_parser, EntityDeclaration);
        XML_SetNotationDeclHandler(m_parser, NotationDeclaration);
        XML_SetDoctypeDeclHandler(m_parser, StartDoctypeDecl, EndDoctypeDecl);
        XML_SetCdataSectionHandler(m_parser, StartCdataSection, EndCdataSection);
        XML_SetCommentHandler(m_parser, CommentHandler);
        XML_SetExternalEntityRefHandler(m_parser, ExternalEntityRefHandler);
        XML_SetProcessingInstructionHandler(m_parser, ProcessingInstruction);
    }

    bool m_useNamespaces;
    bool m_useNamespacePrefixes;
    bool m_externalResolving;

    wxString m_publicId;
    wxString m_systemId;

    wxXmlEntityResolver* m_entityResolver;
    wxXmlDTDHandler* m_DTDHandler;
    wxXmlContentHandler* m_contentHandler;
    wxXmlErrorHandler* m_errorHandler;
    wxXmlLexicalHandler* m_lexHandler;
    wxXmlDeclHandler* m_declHandler;

    wxXmlInputSource m_input;

    wxMBConv* m_conv;

    wxXmlNamespaceSupport namespaceSupport;

    XML_Parser m_parser;
    bool m_incrementalParsing;
    size_t m_opTags;
    void OpenTag() { m_opTags++; }
    void CloseTag()
    {
        if (m_opTags > 0)
            m_opTags--;
    }

    EntitiesMap m_declaredExternalEnts;
};

// Expat handlers

extern "C" {

void CharacterData(void* userData, const XML_Char* txt, int txtlen)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (reader->m_contentHandler) {
        wxString textWithoutWs = wxString::FromUTF8(txt, txtlen).Trim();
        if (textWithoutWs.empty())
            reader->m_contentHandler->IgnorableWhitespace(wxString::FromUTF8(txt, txtlen));
        else
            reader->m_contentHandler->Characters(textWithoutWs);
    }
}

void StartElement(void* userData, const XML_Char* qName, const XML_Char** atts)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    reader->OpenTag();
    if (!reader->m_contentHandler)
        return;

    wxXmlAttributes attributes;
     
    if (!reader->m_useNamespaces) {
        while (atts) { 
            wxString attrQName = wxString::FromUTF8(*atts++);
            wxString attrValue = wxString::FromUTF8(*atts++);
            attributes.Append(attrQName, wxEmptyString, wxEmptyString, attrValue);
        }
        reader->m_contentHandler->StartElement(wxEmptyString, 
                                               wxEmptyString, 
                                               wxString::FromUTF8(qName), 
                                               attributes);
        return;
    }

    // OK we're doing Namespaces
    reader->namespaceSupport.PushContext();

    if (atts && *atts != NULL) {
        const XML_Char** a1 = atts;
        while (*a1 != NULL) {
            wxString attrQName = wxString::FromUTF8(*a1++);
            wxString attrValue = wxString::FromUTF8(*a1++);

            if (attrQName.find(wxT("xmlns")) == 0) {
                wxString prefix;
                size_t n = attrQName.find(L':');
                if (n != wxNOT_FOUND)
                    prefix = attrQName.Mid(n + 1);
                if (!reader->namespaceSupport.DeclarePrefix(prefix, attrValue))
                    reader->DoError(_("Illegal namespace prefix ") + prefix);
                reader->m_contentHandler->StartPrefixMapping(prefix, attrValue);
                if (reader->m_useNamespacePrefixes)
                    attributes.Append(attrQName, wxEmptyString, wxEmptyString, attrValue);
            }
        }

        while (*atts != 0) {
            wxString attrQName = wxString::FromUTF8(*atts++);
            wxString attrValue = wxString::FromUTF8(*atts++);

            // declaration?
            if (attrQName.find(wxT("xmlns")) != 0) {
                wxString localName,
                         namespaceUri;
                reader->namespaceSupport.ProcessName(attrQName, true, namespaceUri, localName);
                attributes.Append(attrQName, namespaceUri, localName, attrValue);
            }
        }
    }

    // at last! report the event
    wxString name = wxString::FromUTF8(qName),
             localName, 
             namespaceUri;

    reader->namespaceSupport.ProcessName(name, false, namespaceUri, localName);
    reader->m_contentHandler->StartElement(namespaceUri, localName, name, attributes);
}

void EndElement(void* userData, const XML_Char* qName)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);    
    reader->CloseTag();
    if (!reader->m_contentHandler)
        return;

    wxString name = wxString::FromUTF8(qName);

    if (!reader->m_useNamespaces) {
        reader->m_contentHandler->EndElement(wxEmptyString, wxEmptyString, name);
        return;
    }

    wxString namespaceUri,
             localName;

    reader->namespaceSupport.ProcessName(name, false, namespaceUri, localName);
    reader->m_contentHandler->EndElement(namespaceUri, localName, name);

    wxArrayString prefixes = reader->namespaceSupport.GetPrefixes();
    for (size_t i = 0; i < prefixes.size(); i++) 
        reader->m_contentHandler->EndPrefixMapping(prefixes[i]); 

    reader->namespaceSupport.PopContext();
}

void ProcessingInstruction(void* userData, const XML_Char* target, const XML_Char* data)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (reader->m_contentHandler)
        reader->m_contentHandler->ProcessingInstruction(wxString::FromUTF8(target),
                                                        wxString::FromUTF8(data));
}

void ElementDeclaration(void* userData, const XML_Char* name, XML_Content* model)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (!reader->m_declHandler)
        return;

    wxString _model;
    convertXML_Content(_model, model);
    reader->m_declHandler->ElementDecl(wxString::FromUTF8(name), _model);
}

void convertXML_Content(wxString& str, const XML_Content* model, bool isChild)
{
    wchar_t separator = L' ';
    switch (model->type) {
        case XML_CTYPE_EMPTY:
            str += wxT("EMPTY");
            break;
        case XML_CTYPE_ANY:
            str += wxT("ANY");
            break;
        case XML_CTYPE_MIXED:
            if (model->numchildren == 0)
                str += wxT("(#PCDATA)");
            else
                str += wxT("(#PCDATA");
            separator = L'|';
            break;
        case XML_CTYPE_NAME:
            if (!isChild) {
                str += L'(';
                str += model->name;
                str += L')';
            } else
                str += model->name;
            break;
        case XML_CTYPE_CHOICE:
            separator = L'|';
            break;
        case XML_CTYPE_SEQ:
            separator = L',';
            break;
    }

    // do children here
    if (model->numchildren > 0) {
        if (model->type != XML_CTYPE_MIXED)
            str += L'(';

        for (size_t i = 0; i < model->numchildren; i++) {
            if (i > 0)
                str += separator;
            convertXML_Content(str, &(model->children[i]), true);
        }

        str += L')';
    }

    switch (model->quant) {
        case XML_CQUANT_OPT:
            str += wxT("?");
            break;
        case XML_CQUANT_REP:
            str += wxT("*");
            break;
        case XML_CQUANT_PLUS:
            str += wxT("+");
            break;
    }
}

void AttListDeclaration(void* userData,
                        const XML_Char* elname,
                        const XML_Char* attname,
                        const XML_Char* att_type,
                        const XML_Char* dflt,
                        int isrequired)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (reader->m_declHandler) {
        wxString defType = wxT("#IMPLIED");
        if (isrequired)
            defType = dflt ? wxT("#FIXED") : wxT("#REQUIRED");
        reader->m_declHandler->AttributeDecl(wxString::FromUTF8(elname),
                                             wxString::FromUTF8(attname),
                                             wxString::FromUTF8(att_type),
                                             defType,
                                             wxString::FromUTF8(dflt));
    }
}

void EntityDeclaration(void* userData, 
                       const XML_Char* entityName,
                       int /* is_parameter_entity */,
                       const XML_Char* value,
                       int value_length,
                       const XML_Char* /* base */,
                       const XML_Char* systemId,
                       const XML_Char* publicId,
                       const XML_Char* notationName)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    wxString _entityName = wxString::FromUTF8(entityName);
    if (!systemId && !publicId && !notationName) {
        // internal entity!
        if (reader->m_declHandler)
            reader->m_declHandler->InternalEntityDecl(_entityName, wxString::FromUTF8(value, value_length));
        return;
    }

    wxString _publicId = wxString::FromUTF8(publicId),
             _systemId = wxString::FromUTF8(systemId);

    if (notationName == NULL) {
        if (reader->m_declHandler)
            reader->m_declHandler->ExternalEntityDecl(_entityName, _publicId, _systemId);
        reader->m_declaredExternalEnts[_publicId] = _entityName;
        reader->m_declaredExternalEnts[_systemId] = _entityName;
    } else {
        if (reader->m_DTDHandler)
            reader->m_DTDHandler->UnparsedEntityDecl(_entityName, _publicId, _systemId, wxString::FromUTF8(notationName));
    }
}

void NotationDeclaration(void* userData,
                         const XML_Char* notationName,
                         const XML_Char* /* base */,
                         const XML_Char* systemId,
                         const XML_Char* publicId)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (reader->m_DTDHandler) 
        reader->m_DTDHandler->NotationDecl(wxString::FromUTF8(notationName),
                                           wxString::FromUTF8(publicId),
                                           wxString::FromUTF8(systemId));
}

void StartDoctypeDecl(void* userData,
 				      const XML_Char* doctypeName,
				      const XML_Char* systemId,
					  const XML_Char* publicId,
					  int /* has_internal_subset */)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (!reader->m_lexHandler)
        return;

    wxString _publicId = wxString::FromUTF8(publicId),
             _systemId = wxString::FromUTF8(systemId);
    reader->m_declaredExternalEnts[_publicId] = wxT("[dtd]");
    reader->m_declaredExternalEnts[_systemId] = wxT("[dtd]");
    reader->m_lexHandler->StartDTD(wxString::FromUTF8(doctypeName), _publicId, _systemId);
}

void EndDoctypeDecl(void* userData)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (reader->m_lexHandler)
        reader->m_lexHandler->EndDTD();
}

void StartCdataSection(void* userData)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (reader->m_lexHandler)
        reader->m_lexHandler->StartCDATA();
}

void EndCdataSection(void* userData)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (reader->m_lexHandler)
        reader->m_lexHandler->EndCDATA();
}

void CommentHandler(void* userData, const XML_Char* data)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(userData);
    if (reader->m_lexHandler)
        reader->m_lexHandler->Comment(wxString::FromUTF8(data));
}

int ExternalEntityRefHandler(XML_Parser parser, 
                             const XML_Char* context,
                             const XML_Char* /* base */,
                             const XML_Char* systemId,
                             const XML_Char* publicId)
{
    wxXmlSimpleReaderImpl* reader = static_cast<wxXmlSimpleReaderImpl*>(XML_GetUserData(parser));

    wxString _publicId = wxString::FromUTF8(publicId),
             _systemId = wxString::FromUTF8(systemId);

    wxString entityName;
    if (publicId)
        entityName = reader->m_declaredExternalEnts[_publicId];
    else if (systemId)
        entityName = reader->m_declaredExternalEnts[_systemId];

    if (!reader->m_externalResolving) {
        if (!entityName.empty() && reader->m_contentHandler)
            reader->m_contentHandler->SkippedEntity(entityName);
        return 1;
    }

    // resolve external entity
    if (!entityName.empty() && reader->m_lexHandler)
        reader->m_lexHandler->StartEntity(entityName);
    else
        return 0;

    wxXmlInputSource source;
    if (reader->m_entityResolver) 
        source = reader->m_entityResolver->ResolveEntity(_publicId, _systemId);

    if (source.GetByteStream()) {
        if (source.GetPublicId().empty() && source.GetSystemId().empty()) {
            source.SetPublicId(_publicId);
            source.SetSystemId(_systemId);
        }

        XML_Parser externalParser = XML_ExternalEntityParserCreate(parser, context, 0);
        bool ok = reader->DoParse(source, externalParser);
        XML_ParserFree(externalParser);
        if (!entityName.empty() && reader->m_lexHandler)
            reader->m_lexHandler->EndEntity(entityName);
        return ok;
    }

    return 0;
}

};

// wxXmlSimpleReader class

wxXmlSimpleReader::wxXmlSimpleReader()
{
    m_impl = new wxXmlSimpleReaderImpl;
}

wxXmlSimpleReader::~wxXmlSimpleReader()
{
    delete m_impl;
}

bool wxXmlSimpleReader::GetFeature(const wxString& name, bool *ok) const
{
    if (ok)
        *ok = true;
    if (name == wxT("http://xml.org/sax/features/namespaces"))
        return m_impl->m_useNamespaces;
    if (name == wxT("http://xml.org/sax/features/namespace-prefixes"))
        return m_impl->m_useNamespacePrefixes;
    if (name == wxT("http://xml.org/sax/features/external-resolving"))
        return m_impl->m_externalResolving;

    if (ok)
        *ok = false;

    return false;
}

void wxXmlSimpleReader::SetFeature(const wxString& name, bool value)
{
    if (name == wxT("http://xml.org/sax/features/namespaces"))
        m_impl->m_useNamespaces = value;
    else if (name == wxT("http://xml.org/sax/features/namespace-prefixes"))
        m_impl->m_useNamespacePrefixes = value;
    else if (name == wxT("http://xml.org/sax/features/external-resolving"))
        m_impl->m_externalResolving = value;
}

bool wxXmlSimpleReader::HasFeature(const wxString& name) const
{
    if (name == wxT("http://xml.org/sax/features/namespaces") ||
        name == wxT("http://xml.org/sax/features/namespace-prefixes") ||
        name == wxT("http://xml.org/sax/features/external-resolving"))
        return true;
    return false;
}

void* wxXmlSimpleReader::GetProperty(const wxString&/* name */, bool *ok) const
{
    if (ok)
        *ok = false;
    return NULL;
}

void wxXmlSimpleReader::SetProperty(const wxString&, void*)
{
}

bool wxXmlSimpleReader::HasProperty(const wxString&/* name */) const
{
    return false;
}

void wxXmlSimpleReader::SetEntityResolver(wxXmlEntityResolver* handler)
{
    m_impl->m_entityResolver = handler;
}

wxXmlEntityResolver* wxXmlSimpleReader::GetEntityResolver() const
{
    return m_impl->m_entityResolver;
}

void wxXmlSimpleReader::SetDTDHandler(wxXmlDTDHandler* handler)
{
    m_impl->m_DTDHandler = handler;
}

wxXmlDTDHandler* wxXmlSimpleReader::GetDTDHandler() const
{
    return m_impl->m_DTDHandler;
}

void wxXmlSimpleReader::SetContentHandler(wxXmlContentHandler* handler)
{
    m_impl->m_contentHandler = handler;
}

wxXmlContentHandler* wxXmlSimpleReader::GetContentHandler() const
{
    return m_impl->m_contentHandler;
}

void wxXmlSimpleReader::SetErrorHandler(wxXmlErrorHandler* handler)
{
    m_impl->m_errorHandler = handler;
}

wxXmlErrorHandler* wxXmlSimpleReader::GetErrorHandler() const
{
    return m_impl->m_errorHandler;
}

void wxXmlSimpleReader::SetLexicalHandler(wxXmlLexicalHandler* handler)
{
    m_impl->m_lexHandler = handler;
}

wxXmlLexicalHandler* wxXmlSimpleReader::GetLexicalHandler() const
{
    return m_impl->m_lexHandler;
}

void wxXmlSimpleReader::SetDeclHandler(wxXmlDeclHandler* handler)
{
    m_impl->m_declHandler = handler;
}

wxXmlDeclHandler* wxXmlSimpleReader::GetDeclHandler() const
{
    return m_impl->m_declHandler;
}

bool wxXmlSimpleReader::Parse(wxXmlInputSource& input)
{
    return Parse(input, false);
}

bool wxXmlSimpleReader::Parse(wxXmlInputSource& input, bool incremental)
{
    m_impl->m_incrementalParsing = incremental;
    m_impl->m_parser = XML_ParserCreate(NULL);
    m_impl->m_input = input;
    m_impl->SetParserCallbacks();

    m_impl->m_publicId = input.GetPublicId();
    m_impl->m_systemId = input.GetSystemId();

    if (m_impl->m_contentHandler)
        m_impl->m_contentHandler->SetDocumentLocator(this);

    if (m_impl->m_contentHandler)
        m_impl->m_contentHandler->StartDocument();

    XML_SetParamEntityParsing(m_impl->m_parser, m_impl->m_externalResolving ? XML_PARAM_ENTITY_PARSING_ALWAYS : XML_PARAM_ENTITY_PARSING_NEVER);
    
    if (!m_impl->DoParse(m_impl->m_input, m_impl->m_parser))
        return false;    
    
    if (m_impl->m_opTags > 0)
        return incremental;
    else {
        if (m_impl->m_contentHandler)
            m_impl->m_contentHandler->EndDocument();
        XML_ParserReset(m_impl->m_parser, 0);
    }

    return true;
}

bool wxXmlSimpleReader::ParseContinue()
{
    if (m_impl->m_incrementalParsing && m_impl->m_opTags > 0) {
        if (!m_impl->DoParse(m_impl->m_input, m_impl->m_parser))
            return false;
        if (m_impl->m_opTags == 0) {
            if (m_impl->m_contentHandler)
                m_impl->m_contentHandler->EndDocument();
            m_impl->m_incrementalParsing = false;
            XML_ParserReset(m_impl->m_parser, 0);
        }
    } else
        return false;
    return true;
}

int wxXmlSimpleReader::GetColumnNumber() const
{
    return XML_GetCurrentColumnNumber(m_impl->m_parser);
}

int wxXmlSimpleReader::GetLineNumber() const
{
    return XML_GetCurrentLineNumber(m_impl->m_parser);
}

wxString wxXmlSimpleReader::GetPublicId() const
{
    return m_impl->m_publicId;
}

wxString wxXmlSimpleReader::GetSystemId() const
{
    return m_impl->m_systemId;
}