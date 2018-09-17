// XmlNode.h: interface for the CXmlNode class.
//  http://www.codeguru.com/cpp/data/mfc_database/xml/article.php/c4317
//////////////////////////////////////////////////////////////////////
#ifndef _S_G_F_xmlnode_h
#define _S_G_F_xmlnode_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely_used stuff from Windows headers

//#include "portable.h"
#include <fstream>
#include <string>
#include <map>
#ifdef _WIN32
#include <tchar.h>
#define local_uint64 unsigned __int64
#define local_long unsigned long
#else

#include <inttypes.h>
#define __int64 int64_t
#define local_uint64 uint64_t
#define local_long uint32_t

#define _T(x)       __T(x)
#ifdef  _UNICODE
#define __T(x)      L ## x    //TODO SOLVE THE DEFINITON WHEN USING UNICODE DEFINED   --  This works for windows...only
#else   /* ndef _UNICODE */
#define __T(x)      x
#endif  /* _UNICODE */



#endif




/*
 
size of long integer type on different architecture and OS

Submitted by (not verified) on Mon, 11/03/2008 - 08:35

The size of a "long" integer varies between architectures and operating systems.

The Intel Compiler is compatible and inter-operable with Microsoft* Visual C++ on Windows* and with gcc* on Linux* and Mac OS X*. Consequently, the sizes of fundamental types are the same as for these compilers. The size of  a long integer in particular depends on the operating system and the targeted architecture as follows:

      OS           arch           size
Windows       IA-32        4 bytes
Windows       Intel 64     4 bytes
Windows       IA-64        4 bytes
Linux            IA-32        4 bytes
Linux            Intel 64     8 bytes
Linux            IA-64        8 bytes
Mac OS X      IA-32        4 bytes
Mac OS X      Intel 64     8 bytes 

*/


using namespace std;
namespace SGF{
namespace XmlTools{
//================================================================================

void UTL_PutXmlHeader(ofstream & ofs);

//================================================================================

class CXmlAttributeSet
{
protected:
   map<string, string>     m_AttributeMap;
public:
   CXmlAttributeSet();
   CXmlAttributeSet(const char * name, const char * value);
   virtual ~CXmlAttributeSet();

   CXmlAttributeSet & operator = (CXmlAttributeSet & r);


   virtual int AddAttribute(const char * name, const char * value);

   friend class CXmlNodeBase;
};

//================================================================================
//================================================================================
/*
   UTF-8 :

   All characters in the range '\u0001' to '\u007F' are represented by a single byte:

      0 : bits 0-7

   Characters in the range '\u0080' to '\u07FF' are represented by a pair of bytes:

   1 1 0 : bits 6-10
   1 0   : bits 0-5


   Characters in the range '\u0800' to '\uFFFF' are represented by three bytes:
   1 1 1 0  : bits 12-15
   1 0      : bits 6-11
   1 0      : bits 0-5

  (For more information, see X/Open Company Ltd., "File System Safe UCS
   Transformation Format (FSS_UTF)", X/Open Preliminary Specification,
   Document Number: P316. This information also appears in ISO/IEC 10646, Annex P.)

*/
/**
 * \class CXmlNodeBase
 *
 * \ingroup SGF_Util
 *
 * \brief Grava arquivos XML
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class CXmlNodeBase
{
protected:
   unsigned long     m_cRef;;
   static const char *    m_szValueTrue;
   static const char *    m_szValueFalse;


   string       m_tag;
   bool              m_bDidStart;
   string       m_text;
   ::ofstream    &   m_ofs;

   CXmlAttributeSet  m_attribs;

   void  PutUTF8Char(int const wChar, string & outs);

   void  PutValue(const char * value, string & outs);
   void  PutValue(const wchar_t* value, string & outs);

   // replaces special characters that might occur in the obuject name
   void  ReplaceSpecial(void);

public:
   static const char *    EMPTY_DATA;

   static void ValidateTagBuffer(  const char * tag);
   static void ReplaceInvalidTagChars(   char* tag);

   CXmlNodeBase(::ofstream & ofs,   const char * tag);
   virtual ~CXmlNodeBase();

   virtual void StartNode(void);
   virtual void AssignAttributeSet(CXmlAttributeSet & ras);

   unsigned long AddRef(void);
   unsigned long  Release(void);

public:
   // The exception that will be thrown if the tag contains special characters
   class CXmlNodeException
   {
   public:
      const char m_chTheWrongCharacter; // const => can be set only where it is set below
      CXmlNodeException(char ch) : m_chTheWrongCharacter(ch) {}
   };
};

class CXmlNode : public CXmlNodeBase
{
public:
   CXmlNode(::ofstream & ofs,   const char * tag);
   CXmlNode(::ofstream & ofs,   const char * tag,   const char * value);
   CXmlNode(::ofstream & ofs,   const char * tag,   const wchar_t* value);
   CXmlNode(::ofstream & ofs,   const char * tag,   const int nValue);
   CXmlNode(::ofstream & ofs,   const char * tag,   const local_long nValue);
   CXmlNode(::ofstream & ofs,   const char * tag,   const local_uint64 nValue);
   CXmlNode(::ofstream & ofs,   const char * tag,   const bool bValue);
   CXmlNode(::ofstream & ofs,   const char * tag,   const double dValue);
   virtual ~CXmlNode();

   unsigned long  AddRef(void)  {return CXmlNodeBase::AddRef();}
   unsigned long  Release(void) {return CXmlNodeBase::Release();}
};


//================================================================================
#define START_NODE_V(F,N,V)     {  XmlTools::CXmlNode   xxxml((F),(N),(V)); xxxml.StartNode();
#define START_NODE(F,N)     {  XmlTools::CXmlNode   xxxml((F),(N)); xxxml.StartNode();
#define START_NODE_A(F,N,V,A) {  XmlTools::CXmlNode   xxxml((F),(N),(V)); \
                                 xxxml.AssignAttributeSet(A) ; xxxml.StartNode();
#define CLOSE_NODE            }
#define DO_NODE(F,N,V)        START_NODE(F,N,V); CLOSE_NODE
#define DO_NODE_A(F,N,V,A)    START_NODE_A(F,N,V,A); CLOSE_NODE
//================================================================================
//================================================================================

} //end XMLTOOLS
}// End SGF

#endif // _S_G_F_xmlnode_h