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

#include <string>
#include "util/SGF_Debug.h"
#include "mugen/Ast/attribute.h"
#include "mugen/Ast/attribute-simple.h"
#include "mugen/Ast/attribute-array.h"
#include "mugen/Ast/attribute-keyword.h"
#include "mugen/Ast/helper.h"
#include "mugen/Ast/function.h"
#include "mugen/Ast/hitdef.h"
#include "mugen/Ast/value-list.h"
#include "mugen/Ast/range.h"
#include "mugen/Ast/string.h"
#include "mugen/Ast/Section.h"
#include "mugen/Ast/filename.h"
#include "mugen/Ast/Expression.h"
#include "mugen/Ast/number.h"
#include "mugen/Ast/key.h"

using ::std::string;
using namespace std;
namespace SGF{

namespace Ast{

string CElement::SERIAL_STRING = "a";
string CElement::SERIAL_FUNCTION = "b";
string CElement::SERIAL_RANGE = "c";
string CElement::SERIAL_SECTION_LIST = "d";
string CElement::SERIAL_IDENTIFIER = "e";
string CElement::SERIAL_KEYWORD = "f";
string CElement::SERIAL_HITDEF_ATTRIBUTE = "g";
string CElement::SERIAL_HITDEF_ATTACK_ATTRIBUTE = "h";
string CElement::SERIAL_EXPRESSION_UNARY = "i";
string CElement::SERIAL_EXPRESSION_INFIX = "j";
string CElement::SERIAL_VALUE_LIST = "k";
string CElement::SERIAL_ATTRIBUTE_SIMPLE = "l";
string CElement::SERIAL_ATTRIBUTE_ARRAY = "m";
string CElement::SERIAL_HELPER = "n";
string CElement::SERIAL_NUMBER = "o";
string CElement::SERIAL_FILENAME = "p";
string CElement::SERIAL_ATTRIBUTE_KEYWORD = "q";
string CElement::SERIAL_KEY_SINGLE = "r";
string CElement::SERIAL_KEY_MODIFIER = "s";
string CElement::SERIAL_KEY_COMBINED = "t";
string CElement::SERIAL_KEY_LIST = "u";
string CElement::SERIAL_EXPRESSION_POSTFIX = "v";
string CElement::SERIAL_OPERAND = "x";
string CElement::SERIAL_KEYWORD_ARRAY = "z";
string CSection::SERIAL_SECTION_ATTRIBUTE = "s1";
string CSection::SERIAL_SECTION_VALUE = "s2";
string CElement::SERIAL_EXPRESSION_STACK = "s3";
string CElement::SERIAL_RESOURCE = "s4";
string CElement::SERIAL_ARGUMENT="s5";

CAttributeSimple * CAttributeSimple::deserialize(const Token * token){
    int line, column;
    TokenView view = token->view();
    view >> line;
    view >> column;
    const Token * nameToken;
    view >> nameToken;
    CIdentifier * name = CIdentifier::deserialize(nameToken);
    CValue * value = NULL;
    try{
        const Token * valueToken;
        view >> valueToken;
        value = CValue::deserialize(valueToken);
    } catch (const CTokenException & ex){
		 Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
    }

    return new CAttributeSimple(line, column, name, value);
}

CAttributeArray * CAttributeArray::deserialize(const Token * token){
    const Token * name;
    int line, column;
    TokenView view = token->view();
    view >> line >> column >> name;
    CIdentifier * identifier = NULL;
    CKeyword * keyword = NULL;
    if (*name == SERIAL_IDENTIFIER){
        identifier = CIdentifier::deserialize(name);
    } else if (*name == SERIAL_KEYWORD){
        keyword = CKeyword::deserialize(name);
    }
    const Token * indexToken;
    const Token * valueToken;
    view >> indexToken >> valueToken;
    CValue * index = CValue::deserialize(indexToken);
    CValue * value = CValue::deserialize(valueToken);
    if (identifier != NULL){
        return new CAttributeArray(/*line, column,*/ identifier, index, value);
    } else if (keyword != NULL){
        return new CAttributeArray(/*line, column,*/ keyword, index, value);
    }
    throw CException("Deserialization error: no name given for an attribute array");
}

CIdentifier * CIdentifier::deserialize(const Token * token){
    int line, column;
    string name;
    token->view() >> line >> column >> name;
    return new CSimpleIdentifier(line, column, name);
}

CAttribute * CAttribute::deserialize(const Token * token){
    if (*token == SERIAL_ATTRIBUTE_SIMPLE){
        return CAttributeSimple::deserialize(token);
    }
    if (*token == SERIAL_ATTRIBUTE_ARRAY){
        return CAttributeArray::deserialize(token);
    }
    if (*token == SERIAL_ATTRIBUTE_KEYWORD){
        return CAttributeKeyword::deserialize(token);
    }

    throw CException("Don't know how to deserialize attribute " + token->getName());
}

CValue * CValue::deserialize(const Token * token){
    if (*token == SERIAL_RESOURCE){
        return SGF::Ast::CResource::deserialize(token);
    }
    if (*token == SERIAL_NUMBER){
        return CNumber::deserialize(token);
    }

	if (*token == SERIAL_ARGUMENT){
        return CArgument::deserialize(token);
    }
	if (*token == SERIAL_EXPRESSION_INFIX){
        return CExpressionInfix::deserialize(token);
    }
	if (*token == SERIAL_EXPRESSION_POSTFIX){
        return CExpressionPostfix::deserialize(token);
    }
    if (*token == SERIAL_EXPRESSION_UNARY){
        return CExpressionUnary::deserialize(token);
    }
    if (*token == SERIAL_KEYWORD){
        return CKeyword::deserialize(token);
    }
	if (*token == SERIAL_KEYWORD_ARRAY){
        return CKeyword::deserialize(token);
    }
    if (*token == SERIAL_FUNCTION){
        return CFunction::deserialize(token);
    }
    if (*token == SERIAL_IDENTIFIER){
        return CIdentifier::deserialize(token);
    }
    if (*token == SERIAL_HELPER){
        return CHelper::deserialize(token);
    }
    if (*token == SERIAL_STRING){
        return CString::deserialize(token);
    }
    if (*token == SERIAL_VALUE_LIST){
        return CValueList::deserialize(token);
    }
    if (*token == SERIAL_RANGE){
        return CRange::deserialize(token);
    }
    if (*token == SERIAL_HITDEF_ATTRIBUTE){
        return CHitDefAttribute::deserialize(token);
    }
    if (*token == SERIAL_HITDEF_ATTACK_ATTRIBUTE){
        return CHitDefAttackAttribute::deserialize(token);
    }
    if (*token == SERIAL_KEY_LIST){
        return CKeyList::deserialize(token);
    }
    if (*token == SERIAL_KEY_SINGLE){
        return CKeySingle::deserialize(token);
    }
    if (*token == SERIAL_KEY_MODIFIER){
        return CKeyModifier::deserialize(token);
    }
    if (*token == SERIAL_KEY_COMBINED){
        return CKeyCombined::deserialize(token);
    }
    if (*token == SERIAL_FILENAME){
        return CFilename::deserialize(token);
    }

    throw CException("Don't know how to deserialize value " + token->getName());
}

CFunction * CFunction::deserialize(const Token * token){
    string name;
    TokenView view = token->view();
     int line = -1;
    int column = -1;
    view >> line >> column;
    CValueList * args = NULL;
    try{
        const Token * next;
        view >> next;
        args = CValueList::deserialize(next);
    } catch (const CTokenException & ex){
		 Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
    }

    return new CFunction(line, column,name, args);
}

}
} //end SGF
