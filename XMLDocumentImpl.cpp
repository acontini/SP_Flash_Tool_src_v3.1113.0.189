/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/
#include <vcl.h>
#pragma hdrstop

#include <cassert>
#include <sstream>
#include <stdexcept>

#include "XMLNodeImpl.h"
#include "XMLDocumentImpl.h"
#include "XMLNode.h"
//Header sequence adjustment: <atlbase.h> should be after <utilcls.h>
#include <atlbase.h>

using XML::NodeImpl;
using XML::DocumentImpl;
using Msxml2_tlb::TCOMIXMLDOMElement;
using Msxml2_tlb::TCOMIXMLDOMParseError;
using std::endl;
//using std::runtime_error; using vcl Exception
using std::string;
using std::wstring;

/**
 * Take care of COM library initialization and deinitialization
 */
class COMInitializer : private NonCopyable
{
public:
    COMInitializer()
    {
        const HRESULT errorCode =
                ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

        if (FAILED(errorCode))
        {
            assert(0);
        }
    }

    ~COMInitializer()
    {
        ::CoUninitialize();
    }
};

static const COMInitializer g_COMInitializer;
//const COMInitializer g_COMInitializer;

DocumentImpl::DocumentImpl(const wstring &xmlFile)
    : m_MainDoc()
{
    InitDoc();
    Load(xmlFile);
}

DocumentImpl::DocumentImpl(const wstring &xmlVersion,
                           const wstring &encoding,
                           const wstring &rootNodeName)
    : m_MainDoc()
{
    InitDoc();

    std::wostringstream oss;
    oss << L"version=\""  << xmlVersion << "\" "
        << L"encoding=\"" << encoding   << "\"";

    CreateProcessingInstruction(L"xml", oss.str());
    CreateRootNode(rootNodeName);
}

DocumentImpl::~DocumentImpl()
{
}

void DocumentImpl::Load(const wstring &xmlFile)
{
    const WideString ws(xmlFile.c_str());

    VARIANT filename;
    ::VariantInit(&filename);

    filename.bstrVal = ws;
    filename.vt = VT_BSTR;

    if (m_MainDoc->load(filename) != VARIANT_TRUE)
    {
    	//assert(0); //load XML failed
    	//FormatParseError here will cause Access Violation
        //throw runtime_error(FormatParseError(m_MainDoc->parseError));
    	XMLEXCEPTION(FormatParseError(m_MainDoc->parseError));
    }
}

void DocumentImpl::Save(const wstring &xmlFile)
{
    const WideString ws(xmlFile.c_str());

    VARIANT filename;
    ::VariantInit(&filename);

    filename.bstrVal = ws;
    filename.vt      = VT_BSTR;

    if (!SUCCEEDED(m_MainDoc->save(filename)))
    {
        XMLEXCEPTION("Failed to save the XML document");
    }
}

NodeImpl* DocumentImpl::GetRootNode()
{
    return new NodeImpl(m_MainDoc->documentElement);
}

void DocumentImpl::InitDoc()
{  
        const COMInitializer g_COMInitializer;
    if (FAILED(::CoCreateInstance(Msxml2_tlb::CLSID_DOMDocument60,
                                  NULL,
                                  CLSCTX_INPROC_SERVER,
                                  Msxml2_tlb::IID_IXMLDOMDocument2,
                                  (void **) &m_MainDoc)))
    {
        XMLEXCEPTION("Failed to create an XML document\n"
        		"[Hint] Please check if MSXML6 is installed.");
    }

    m_MainDoc->set_async(VARIANT_FALSE);
    m_MainDoc->set_validateOnParse(VARIANT_FALSE);
}

void DocumentImpl::Validate(const std::wstring &schemaFile)
{
    Msxml2_tlb::TCOMIXMLDOMDocument schemaDoc;

    //
    // Create an document
    //
    if (FAILED(::CoCreateInstance(Msxml2_tlb::CLSID_DOMDocument60,
                                  NULL,
                                  CLSCTX_INPROC_SERVER,
                                  Msxml2_tlb::IID_IXMLDOMDocument,
                                  (void **) &schemaDoc)))
    {
        XMLEXCEPTION("Failed to create an XML schema document");
    }

    schemaDoc->set_async(VARIANT_FALSE);

    //
    // Load the schema file into the document
    //
    
    // Should check whether the file exists
    const WideString _schemaFile(schemaFile.c_str());

    VARIANT variant;
    ::VariantInit(&variant);

    variant.bstrVal = _schemaFile;
    variant.vt = VT_BSTR;

    if (schemaDoc->load(variant) != VARIANT_TRUE)
    {
        XMLEXCEPTION(
                string("[Schema] ") + FormatParseError(schemaDoc->parseError));
    }

    //
    // Create a schema cache
    //
    Msxml2_tlb::IXMLDOMSchemaCollectionPtr schemaCache;

    if (FAILED(schemaCache.CreateInstance(Msxml2_tlb::CLSID_XMLSchemaCache60)))
    {
        XMLEXCEPTION("Cannot create schema cache");
    }

    //
    // Add the schema document to the schema cache
    //
    variant.punkVal = schemaDoc;
    variant.vt = VT_UNKNOWN;

    if (schemaCache->add(L"", variant) == E_FAIL)
    {
        XMLEXCEPTION("Failed to add schema to schema cache");
    }

    //
    // Associate the main document with the schema cache
    //
    variant.punkVal = schemaCache;
    variant.vt = VT_UNKNOWN;

    if (FAILED(m_MainDoc->_set_schemas(variant)))
    {
        XMLEXCEPTION("Failed to set schema");
    }

    //
    // Validate the main document
    //
    TCOMIXMLDOMParseError parseError;

    if (m_MainDoc->validate(&parseError) != S_OK)
    {
        XMLEXCEPTION(FormatParseError(parseError));
    }
}

void DocumentImpl::CreateProcessingInstruction(const wstring &target,
                                               const wstring &data)
{
    Msxml2_tlb::TCOMIXMLDOMProcessingInstruction processingInstruction;

    HRESULT result = m_MainDoc->createProcessingInstruction(
                                        WideString(target.c_str()),
                                        WideString(data.c_str()),
                                        &processingInstruction);

    if (FAILED(result))
    {
        XMLEXCEPTION("Failed to create processing instruction");
    }

    if (FAILED(m_MainDoc->appendChild(processingInstruction, NULL)))
    {
        XMLEXCEPTION("Failed to add processing instruction");
    }
}

void DocumentImpl::CreateRootNode(const wstring &rootNodeName)
{
    TCOMIXMLDOMElement rootNode(
                m_MainDoc->createElement(WideString(rootNodeName.c_str())));

    if (FAILED(m_MainDoc->appendChild(rootNode, NULL)))
    {
        XMLEXCEPTION("Failed to create a root element");
    }
}

string DocumentImpl::FormatParseError(const TCOMIXMLDOMParseError &parseError)
{
    USES_CONVERSION;
    std::ostringstream oss;

    if (parseError->line != 0)
    {
        oss << "Syntax error: line " << parseError->line << endl
            << W2CA(TOleString(parseError->reason));
    }
    else
    {
        oss << "Syntax error" << endl << W2CA(TOleString(parseError->reason));
    }

    return oss.str();
}
