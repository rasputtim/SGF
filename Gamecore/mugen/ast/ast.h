/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */
#ifndef _S_G_E_AST_H_
#define _S_G_E_AST_H_

#include <map>
#include <string>
#include "../../SGF_Config.h"
#include "../../util/SGF_Token.h"

using namespace std;

namespace SGF {
namespace Ast{

class CSection;
class CAttributeSimple;
class CAttributeArray;
class CAttributeKeyword;
class CNumber;
class CAttribute;
class CIdentifier;
class CValue;
class CNumber;
class CExpressionInfix;
class CExpressionPostfix;
class CExpressionUnary;
class CFunction;
class CFilename;
class CValueList;
class CHitDefAttribute;
class CHitDefAttackAttribute;
class CString;
class CRange;
class CHelper;
class CKeyword;
class CKeywordArray;
class CKey;
class CKeySingle;
class CKeyModifier;
class CKeyCombined;
class CKeyList;
class CResource;
class CArgument;



class CElement{
public:
    CElement():
	line(-1),
	column(-1){
    }
	CElement(int line, int column):
    line(line),
    column(column){
    }
    static string SERIAL_STRING;
    static string SERIAL_FUNCTION;
    static string SERIAL_RANGE;
    static string SERIAL_SECTION_LIST;
    static string SERIAL_IDENTIFIER;
    static string SERIAL_KEYWORD;
    static string SERIAL_KEYWORD_ARRAY;
	static string SERIAL_HITDEF_ATTRIBUTE;
    static string SERIAL_HITDEF_ATTACK_ATTRIBUTE;
    static string SERIAL_EXPRESSION_UNARY;
    static string SERIAL_EXPRESSION_INFIX;
	static string SERIAL_EXPRESSION_POSTFIX;
    static string SERIAL_VALUE_LIST;
    static string SERIAL_ATTRIBUTE_SIMPLE;
    static string SERIAL_ATTRIBUTE_ARRAY;
    static string SERIAL_ATTRIBUTE_KEYWORD;
    static string SERIAL_HELPER;
    static string SERIAL_NUMBER;
    static string SERIAL_FILENAME;
    static string SERIAL_KEY_SINGLE;
    static string SERIAL_KEY_MODIFIER;
    static string SERIAL_KEY_COMBINED;
    static string SERIAL_KEY_LIST;
	static string SERIAL_OPERAND;
	static string SERIAL_EXPRESSION_STACK;
	static string SERIAL_RESOURCE;
	static string SERIAL_ARGUMENT;
    /* This synchronizes on-disk serialized files with the code.
     * If anything in the AST structure changes and causes an incompatibility
     * between the code and any existing serialized files then you *must*
     * increment this variable.
     */
    static const int SERIAL_VERSION = 1;

    virtual void mark(map<const void*, bool> & marks) const = 0;

#define define_equals(class_name) virtual bool operator!=(const class_name & him) const { return !(*this == him); } virtual bool operator==(const class_name & him) const { return false; }

    define_equals(CElement)
    define_equals(CSection)
    define_equals(CAttribute)
    define_equals(CAttributeSimple)
    define_equals(CAttributeArray)
    define_equals(CAttributeKeyword)
    define_equals(CIdentifier)
    define_equals(CValue)
    define_equals(CNumber)
    define_equals(CExpressionInfix);
    define_equals(CExpressionUnary);
    define_equals(CFunction);
    define_equals(CValueList);
    define_equals(CHitDefAttribute);
    define_equals(CHitDefAttackAttribute);
    define_equals(CString);
    define_equals(CRange);
    define_equals(CHelper);
    define_equals(CKeyword);
    define_equals(CKeywordArray);
	define_equals(CKey);
    define_equals(CKeySingle);
    define_equals(CKeyModifier);
    define_equals(CKeyCombined);
    define_equals(CKeyList);
    define_equals(CFilename);
	define_equals(CExpressionPostfix);
	define_equals(CResource);
#undef define_equals

    /*
    virtual bool operator!=(const CElement & him) const {
        return !(*this == him);
    }

    virtual bool operator!=(const CSection & him) const {
        return !(*this == him);
    }

    virtual bool operator!=(const CAttributeSimple & him) const {
        return !(*this == him);
    }

    virtual bool operator==(const CAttributeSimple & him) const {
        return false;
    }

    virtual bool operator==(const CSection & him) const {
        return false;
    }

    virtual bool operator==(const CElement & him) const {
        if (this == &him){
            return true;
        }

        return false;
    }
    */

    virtual ::SGF::Token * serialize() const = 0;

    /* create a deep copy of this object */
    virtual CElement * copy() const = 0;

    virtual ~CElement(){
    }
	
	virtual int getLine() const {
        return line;
    }

    virtual int getColumn() const {
        return column;
    }
	private:
		int line, column;
};

};
} //end SGF
#endif
