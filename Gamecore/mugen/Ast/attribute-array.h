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
#ifndef _keyword_array_h_
#define _keyword_array_h_

#include "all.h"
#include <sstream>
#include "../../util/SGF_Debug.h"
using namespace std;
namespace SGF{
namespace Ast{

class SGE_API  CAttributeArray: public CAttribute {
public:

    CAttributeArray(const CKeyword * name, const CValue * index, const CValue * value):
    CAttribute(Array),
    keyword_name(name),
    identifier_name(0),
    index(index),
    value(value){
    }
	CAttributeArray(const CIdentifier * name, const CValue * index):
    CAttribute(Array),
    keyword_name(0),
    identifier_name(name),
    index(index),
    value(0){
    }

    CAttributeArray(const CIdentifier * name, const CValue * index, const CValue * value):
    CAttribute(Array),
    keyword_name(0),
    identifier_name(name),
    index(index),
    value(value){
    }

    virtual CElement * copy() const {
        if (keyword_name != 0){
            return new CAttributeArray((CKeyword*) keyword_name->copy(), (CValue*) index->copy(), (CValue*) value->copy());
        } else if (identifier_name != 0){
            return new CAttributeArray((CIdentifier*) identifier_name->copy(), (CValue*) index->copy(), (CValue*) value->copy());
        }
        throw CException("don't copy that floppy!");
    }
    const void setValue(CValue *valor) {
        value = valor;
    }
    virtual void walk(CWalker & walker){
        walker.onAttributeArray(*this);
    }

    using CElement::operator==;
    virtual bool operator==(const CAttribute & him) const {
        return him == *this;
    }

    virtual bool operator==(const CAttributeArray & him) const {
        if (keyword_name != NULL && him.keyword_name != NULL){
            if (*keyword_name != *him.keyword_name){
                return false;
            }
        }

        if ((keyword_name == NULL && him.keyword_name != NULL) ||
            (keyword_name != NULL && him.keyword_name == NULL)){
            return false;
        }

        if (identifier_name != NULL && him.identifier_name != NULL){
            if (*identifier_name != *him.identifier_name){
                return false;
            }
        }

        if ((identifier_name == NULL && him.identifier_name != NULL) ||
            (identifier_name != NULL && him.identifier_name == NULL)){
            return false;
        }

        return *index == *him.index &&
               *value == *him.value;
    }

    virtual bool operator==(const string & str) const {
        if (keyword_name != 0){
            return *keyword_name == str;
        } else if (identifier_name != 0){
            return *identifier_name == str;
        }
        return false;
    }

    static CAttributeArray * deserialize(const Token * token);

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_ATTRIBUTE_ARRAY;
        if (keyword_name != NULL){
            *token << keyword_name->serialize();
        }
        if (identifier_name != NULL){
            *token << identifier_name->serialize();
        }
        *token << index->serialize();
        *token << value->serialize();
        return token;
    }

    string valueAsString() const {
        string str;
        *this >> str;
        return str;
    }

    int getIndex() const {
        int i;
        *index >> i;
        return i;
    }

    const CValue * getValue() const {
        return value;
    }

	

    template <typename X>
    const CAttributeArray & operator>>(X & v) const {
        if (value != 0){
            try{
                *value >> v;
            } catch (const CException & ex){
				throw CException("tried to read the wrong type for expression: '" + this->toString() + "' : this->type is CAttributeArray "+   ex.getReason());
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
        index->mark(marks);
        value->mark(marks);
        if (keyword_name != 0){
            keyword_name->mark(marks);
        }
        if (identifier_name != 0){
            identifier_name->mark(marks);
        }
    }

    /* just the identifier */
    string idString() const {
        if (keyword_name != 0){
            return keyword_name->toString();
        } else if (identifier_name != 0){
            return identifier_name->toString();
        }

        return "";
    }

    virtual string toString() const {
        ::std::ostringstream out;
        if (keyword_name != 0){
            out << keyword_name->toString();
        } else if (identifier_name != 0){
            out << identifier_name->toString();
        }
        out << "[" << index->toString() << "] = " << value->toString();

        return out.str();
    }
void debugExplain() {
        
	Debug::debug(Debug::parsers,__FUNCTION__) << "debugExplain(AttributeArray) //  : " << toString() <<endl;
        
        
        }
    virtual ~CAttributeArray(){
        delete keyword_name;
        delete identifier_name;
        delete index;
        delete value;
    }

protected:
    const CKeyword * keyword_name;
    const CIdentifier * identifier_name;
    const CValue * index;
    const CValue * value;
};

} //end ast
} //end SGF
#endif
