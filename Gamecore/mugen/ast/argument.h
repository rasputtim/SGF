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
#ifndef _S_G_E_ast_argument_h_
#define _S_G_E_ast_argument_h_

#include "Value.h"
#include <string>
#include <sstream>

/* CArgument will extract the argN field from the Environment at runtime and evaluate it
 * where N is the 'argument' field.
 */
using namespace std;
namespace SGF {
namespace Ast{

class CArgument: public CValue {
public:
    CArgument(int line, int column, int argument):
    CValue(line, column),
    argument(argument){
    }

    class ArgumentView: public CViewImplementation {
    public:
        ArgumentView(const CArgument * owner):
        owner(owner){
        }

        const CArgument * owner;

        virtual string getType() const {
            return owner->getType();
        }
    
        virtual const CValue * self() const {
            return owner;
        }
        
        virtual string toString() const {
            return owner->toString();
        }

        using CViewImplementation::operator>>;
        virtual ArgumentView & operator>>(const CValue *& v){
            v = owner;
            return *this;
        }

        virtual ArgumentView & operator>>(int & v){
            v = owner->argument;
            return *this;
        }
    };

    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new ArgumentView(this)));
    }

    virtual void walk(CWalker & walker) const {
        walker.onArgument(*this);
    }
    
    virtual CElement * copy() const {
        return new CArgument(getLine(), getColumn(), argument);
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CArgument & him) const {
        return argument == him.argument;
    }
   
    static CArgument * deserialize(const Token * token){
        int line, column;
        int argument;
        token->view() >> line >> column >> argument;
        return new CArgument(line, column, argument);
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_ARGUMENT << getLine() << getColumn() << argument;
        return token;
    }
        
    virtual string getType() const {
        return "argument";
    }

    virtual string toString() const {
        ::std::ostringstream out;
        out << "x" << argument;
        return out.str();
    }

    virtual ~CArgument(){
    }
protected:
    int argument;
};

}
} //end SGF
#endif
