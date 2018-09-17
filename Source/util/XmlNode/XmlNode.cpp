// XmlNode.cpp: implementation of the CXmlNodeBase class.
//
//////////////////////////////////////////////////////////////////////

#include "util/XmlNode/XmlNode.h"
//#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


namespace SGF {

namespace XmlTools{


void UTL_PutXmlHeader(::ofstream & ofs)
{
   ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CXmlAttributeSet::CXmlAttributeSet()
{
}

CXmlAttributeSet::CXmlAttributeSet(const char * name, const char * value)
{
   AddAttribute(name, value);
}

CXmlAttributeSet & CXmlAttributeSet::operator = (CXmlAttributeSet & r)
{
   map<string, string>::iterator    it;

   for ( it = r.m_AttributeMap.begin(); it != r.m_AttributeMap.end(); it++ ) {
      this->m_AttributeMap.insert(*it);
   }

   return *this;
}

CXmlAttributeSet::~CXmlAttributeSet()
{
}

//==============================================================================

int CXmlAttributeSet::AddAttribute(const char * name, const char * value)
{
   int ret = -1;

   try {
      CXmlNodeBase::ValidateTagBuffer(name);
      m_AttributeMap[name] = value;
      ret = 0;
   } catch (CXmlNodeBase::CXmlNodeException e) {
      //e;
   }

   return (ret);
}


//==============================================================================
//==============================================================================
//==============================================================================

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char * CXmlNodeBase::EMPTY_DATA = (const char *)NULL;
const char * CXmlNodeBase::m_szValueTrue = "true";
const char * CXmlNodeBase::m_szValueFalse = "false";

CXmlNodeBase::CXmlNodeBase(::ofstream & ofs, const char * tag)
 : m_cRef(0),
   m_tag(tag),
   m_bDidStart(false),
    m_ofs(ofs)
{
   ReplaceSpecial();
}

CXmlNodeBase::~CXmlNodeBase()
{
   if ( m_bDidStart ) {
      m_ofs << "</" << m_tag.c_str() << ">" << endl;
   }
}


void CXmlNodeBase::ReplaceSpecial(void)
{
   if ( m_tag.size() == 0 ) {
      throw CXmlNodeException('\0');
   }

   for ( unsigned int idx = 0; idx < m_tag.size(); idx++ ) {

      switch ( m_tag[idx] ) {
         case '&':
         case '<':
         case '>':
         case '\"':
         case '\'':
            throw CXmlNodeException(m_tag[idx]);
            break;
         case ' ':
            m_tag[idx] = '_';
            break;
         default:
            // OK
            break;
      }
   }
}

//==============================================================================
//==============================================================================

void CXmlNodeBase::ValidateTagBuffer(  const char * tag)
{
   if ( strlen(tag) == 0 ) {
      throw CXmlNodeException('\0');
   }

   for ( unsigned int idx = 0; idx < strlen(tag); idx++ ) {

      switch ( tag[idx] ) {
         case '&':
         case '<':
         case '>':
         case '\"':
         case '\'':
            throw CXmlNodeException(tag[idx]);
            break;
         default:
            // OK
            break;
      }
   }
}

void CXmlNodeBase::ReplaceInvalidTagChars(   char* tag)
{
   for ( unsigned int idx = 0; idx < strlen(tag); idx++ ) {
      switch ( tag[idx] ) {
         case '&':
         case '<':
         case '>':
         case '\"':
         case '\'':
         case ' ':
            tag[idx] = '_';
            break;
         default:
            // OK
            break;
      }
   }
}

//==============================================================================
//==============================================================================

void CXmlNodeBase::StartNode(void)
{
   m_ofs << "<" << m_tag.c_str();

   map<string, string>::iterator    it;

   for ( it = m_attribs.m_AttributeMap.begin(); it != m_attribs.m_AttributeMap.end(); it++ ) {
      string    strAttribValue;

      PutValue(it->second.c_str(), strAttribValue);

      m_ofs << " " << it->first.c_str() << "=\"" << strAttribValue.c_str() << "\"";
   }

   m_ofs << _T(">") << endl;

   if ( m_text.size() > 0 ) {
      m_ofs << m_text.c_str() << endl;
   }

   m_bDidStart = true;
}

void CXmlNodeBase::AssignAttributeSet(CXmlAttributeSet & ras)
{
   m_attribs = ras;
}

void  CXmlNodeBase::PutUTF8Char(int const wChar, string & outs)
{
   if ( wChar <= 0x7F ) {
      outs += (char)wChar;
   } else if ( wChar <= 0x07FF ) {
      outs += (char)(0xC0 | (wChar >> 6));
      outs += (char)(0x80 | (wChar & 0x3F));
   } else {
      outs += (char)(0xE0 | (wChar >> 12));
      outs += (char)(0x80 | (wChar & 0x3F));
      outs += (char)(0x80 | ((wChar >> 6) & 0x3F));
   }
}

void CXmlNodeBase::PutValue(const char * value, string & outs)
{
   for ( const unsigned char * szChar = (const unsigned char *)value; *szChar != '\0'; szChar++ ) {
      switch ( *szChar ) {
         case '&':
            outs += "&amp;";
            break;
         case '<':
            outs += "&lt;";
            break;
         case '>':
            outs += "&gt;";
            break;
         case '\"':
            outs += "&quot;";
            break;
         case '\'':
            outs += "&apos;";
            break;
         default:
            PutUTF8Char(szChar[0], outs);
            break;
      }
   }
}

void CXmlNodeBase::PutValue(const wchar_t* value, string & outs)
{
   for ( const wchar_t * szwChar = (const wchar_t *)value; *szwChar != L'\0'; szwChar++ ) {
      switch ( *szwChar ) {
         case L'&':
            outs += "&amp;";
            break;
         case L'<':
            outs += "&lt;";
            break;
         case L'>':
            outs += "&gt;";
            break;
         case L'\"':
            outs += "&quot;";
            break;
         case L'\'':
            outs += "&apos;";
            break;
         default:
            PutUTF8Char(szwChar[0], outs);
            break;
      }
   }
}

unsigned long  CXmlNodeBase::AddRef(void)
{
   assert((int)m_cRef >= 0);

   return ++m_cRef;
}

unsigned long  CXmlNodeBase::Release(void)
{
   assert((int)m_cRef > 0);

   if (--m_cRef != 0) {
      return m_cRef;
   }
   delete this;
   return 0;
}


//==============================================================================
//==============================================================================
//==============================================================================

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CXmlNode::CXmlNode (
   ::ofstream & ofs,
     const char * tag
)
 : CXmlNodeBase(ofs,tag)
{

}

CXmlNode::CXmlNode (
   ::ofstream & ofs,
     const char * tag,
     const char * value
)
 : CXmlNodeBase(ofs,tag)
{
   if ( value != NULL ) {
      PutValue(value, m_text);
   }
}

CXmlNode::CXmlNode (
   ::ofstream & ofs,
     const char * tag,
     const wchar_t* value
)
 : CXmlNodeBase(ofs,tag)
{
   if ( value != NULL ) {
      PutValue(value, m_text);
   }
}

CXmlNode::CXmlNode (
   ::ofstream & ofs,
     const char * tag,
     const int nValue
)
 : CXmlNodeBase(ofs,tag)
{
   char    szNumberBuf[64];

   sprintf(szNumberBuf, "%d", nValue);
   PutValue(szNumberBuf, m_text);
}

CXmlNode::CXmlNode (
   ::ofstream & ofs,
     const char * tag,
     const local_long nValue
)
 : CXmlNodeBase(ofs,tag)
{
   char    szNumberBuf[64];

   sprintf(szNumberBuf, "%lu", nValue);
   PutValue(szNumberBuf, m_text);
}

CXmlNode::CXmlNode (
   ::ofstream & ofs,
     const char * tag,
     const local_uint64 nValue
)
 : CXmlNodeBase(ofs,tag)
{
   char    szNumberBuf[64];

   sprintf(szNumberBuf, "%I64u", nValue);
   PutValue(szNumberBuf, m_text);
}

CXmlNode::CXmlNode (
   ::ofstream & ofs,
     const char * tag,
     const bool bValue
)
 : CXmlNodeBase(ofs,tag)
{
   if ( bValue ) {
      PutValue(m_szValueTrue, m_text);
   } else {
      PutValue(m_szValueFalse, m_text);
   }
}

CXmlNode::CXmlNode (
   ::ofstream & ofs,
     const char * tag,
     const double dValue
   )
 : CXmlNodeBase(ofs,tag)
{
   char    szNumberBuf[64];

   sprintf(szNumberBuf, "%f", dValue);
   PutValue(szNumberBuf, m_text);
}

CXmlNode::~CXmlNode()
{
}

} //end namespace
} //end SGF