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
#ifndef _S_G_E_ast_attribute_simple_h_
#define _S_G_E_ast_attribute_simple_h_

#include "attribute.h"
#include "identifier.h"
#include "Value.h"
#include "walker.h"
#include <sstream>
#include "../../util/SGF_Debug.h"

using namespace std;
namespace SGF{

namespace Ast{

class SGE_API  CAttributeSimple: public CAttribute {
public:
    CAttributeSimple(int line, int column, const CIdentifier * name, const CValue * value):
    CAttribute(line,column,Simple),
    name(name),
    value(value){
    }

    CAttributeSimple(const CIdentifier * name, const CValue * value):
    CAttribute(-1,-1,Simple),
    name(name),
    value(value){
    }

    CAttributeSimple(const CIdentifier * name):
    CAttribute(-1,-1,Simple),
    name(name),
    value(0){
    }

    virtual void walk(CWalker & walker){
        walker.onAttributeSimple(*this);
    }

    using CAttribute::operator==;
    virtual bool operator==(const CAttribute & him) const {
        return him == *this;
    }

    virtual bool operator==(const CAttributeSimple & him) const {
        bool same_values = true;
        if (value != NULL && him.value != NULL){
            same_values = *value == *him.value;
        } else if (value != NULL){
            same_values = false;
        } else if (him.value != NULL){
            same_values = false;
        }

        return getLine() == him.getLine() &&
               getColumn() == him.getColumn() &&
               *name == *him.name &&
               same_values;
    }

    virtual bool operator==(const string & str) const {
        return *name == str;
    }

    virtual CElement * copy() const {
        if (value != 0){
            return new CAttributeSimple(getLine(), getColumn(), (CIdentifier*) name->copy(), (CValue*) value->copy());
        } else {
            return new CAttributeSimple((CIdentifier*) name->copy());
        }
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_ATTRIBUTE_SIMPLE << getLine() << getColumn() << name->serialize();
        if (value != NULL){
            *token << value->serialize();
        }
        return token;
    }

    static CAttributeSimple * deserialize(const Token * token);

    string valueAsString() const {
        string str;
         view() >> str;
        return str;
    }

    const CValue * getValue() const {
        
		return value;
    }
	   virtual CView view() const {
        if (value != NULL){
            return value->view();
        } else {
            ::std::ostringstream out;
            out << "no values available for attribute '" << this->toString() << "'";
            if (getLine() != -1 && getColumn() != -1){
                out << " at line " << getLine() << " column " << getColumn();
            }
            throw CException(out.str());
        }
    }

	const void setValue(CValue *valor) {
        value = valor;
    }
	/*
    template <typename X>
    const CAttributeSimple & operator>>(X & v) const {
		if (value != 0){
            try{
                *value >> v;
            } catch (const CException & ex){
                ::std::ostringstream out;
                out << "tried to read the wrong type for '" << this->toString() << "' : " << ex.getReason();
                if (line != -1 && column != -1){
                    out << " at line " << line << " column " << column;
                }
                throw CException(out.str());
            }
        }
        return *this;
    } */
   void debugExplain() {
         if (value != 0){
            Debug::debug(Debug::parsers,__FUNCTION__) << "Attribute Name: " << name->toString() << " / value: " << value->toString() <<endl;
        }else{
			Debug::debug(Debug::parsers,__FUNCTION__) << "Attribute Name: " << name->toString() << " / value: <none>" <<endl;
		}
	  
        
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

    /* just the identifier */
    virtual string idString() const {
        return name->toString();
    }
	 
    virtual string toString() const {
        ::std::ostringstream out;
        if (value != 0){
			out << name->toString() << " = " << value->toString() << " // value of type: " << value->getType() << " //";
        } else {
            out << name->toString() << " = <none>";
        }

        return out.str();
    }

    virtual ~CAttributeSimple(){
        delete name;
        delete value;
    }

protected:
    const CIdentifier * name;
    const CValue * value;
};

} //end AST
} //end SGF
#endif
