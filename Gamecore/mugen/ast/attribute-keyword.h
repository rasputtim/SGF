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
#ifndef _ast_attribute_keyword_h_
#define _ast_attribute_keyword_h_

#include "attribute.h"
#include "keyword.h"
#include "Value.h"
#include "walker.h"
#include <sstream>
using namespace std;
namespace SGF{
namespace Ast{

class  SGE_API CAttributeKeyword: public CAttribute {
public:

    CAttributeKeyword(const CKeyword * name, const CValue * value):
    CAttribute(KeywordAttribute),
    name(name),
    value(value){
    }

    CAttributeKeyword(const CKeyword * name):
    CAttribute(KeywordAttribute),
    name(name),
    value(0){
    }

    virtual void walk(CWalker & walker){
        walker.onAttributeKeyword(*this);
    }

    virtual CElement * copy() const {
        if (value == NULL){
            return new CAttributeKeyword((CKeyword*) name->copy());
        } else {
            return new CAttributeKeyword((CKeyword*) name->copy(), (CValue*) value->copy());
        }
    }
	
	const void setValue(CValue *valor) {
        value = valor;
    }

    using CAttribute::operator==;
    virtual bool operator==(const string & str) const {
        return *name == str;
    }

    virtual bool operator==(const CAttribute & him) const {
        return him == *this;
    }

    virtual bool operator==(const CAttributeKeyword & him) const {
        if (value != NULL && him.value != NULL){
            if (*value != *him.value){
                return false;
            }
        }
        if ((value != NULL && him.value == NULL) ||
            (value == NULL && him.value != NULL)){
            return false;
        }
        return *name == *him.name;
    }

    string valueAsString() const {
        string str;
        *this >> str;
        return str;
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_ATTRIBUTE_KEYWORD << name->serialize();
        if (value != NULL){
            *token << value->serialize();
        }
        return token;
    }

    static CAttributeKeyword * deserialize(const Token * token){
        const Token * keyword;
        TokenView view = token->view();
        view >> keyword;
        try{
            const Token * value;
            view >> value;
            return new CAttributeKeyword(CKeyword::deserialize(keyword), CValue::deserialize(value));
        } catch (const CTokenException & ex){
			 Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
            return new CAttributeKeyword(CKeyword::deserialize(keyword));
        }
    }

    template <typename X>
    const CAttributeKeyword & operator>>(X & v) const {
        if (value != 0){
            try{
                *value >> v;
            } catch (const CException & ex){
                throw CException("tried to read the wrong type for expression: '" + this->toString() + "' this type is CAttributeKeyword / reason: " + ex.getReason());
            }
        }
        return *this;
    }

    /*
    virtual bool referenced(const void * value) const {
        return CAttribute::referenced(value) ||
               name->referenced(value) ||
               (this->value != 0 && this->value->referenced(value));
    }
    */

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        if (value != 0){
            value->mark(marks);
        }
        name->mark(marks);
    }
	
	void debugExplain() {
         if (value != 0){
            Debug::debug(Debug::parsers,__FUNCTION__) << "debugExplain(AttributeKeyword) //  name: " << name->toString() << " / value: " << value->toString() <<endl;
        }else{
			Debug::debug(Debug::parsers,__FUNCTION__) << "debugExplain(AttributeKeyword) //  name: " << name->toString() << " / value: <none>" <<endl;
		}
	  
        
        }
    /* just the identifier */
    string idString() const {
        return name->toString();
    }

    virtual string toString() const {
        ::std::ostringstream out;
        if (value != 0){
            out << name->toString() << " = " << value->toString();
        } else {
            out << name->toString() << " = <none>";
        }

        return out.str();
    }

    virtual ~CAttributeKeyword(){
        delete name;
        delete value;
    }

protected:
    const CKeyword * name;
    const CValue * value;
};

} //end AST
} //end SGF
#endif
