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
#ifndef _S_G_E_ast_helper_h_
#define _S_G_E_ast_helper_h_

#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

#include "Value.h"
#include "../../util/SGF_Util.h"
#include "../../util/SGF_Debug.h"

using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CHelper: public CValue {
public:
     CHelper(int line, int column, const string & name, CValue * expression, CValue * original):
    CValue(line, column),
    name(name),
    expression(expression),
    original(original){
    }

    static int lowerCase( int c ){
        return tolower(c);
    }
    
    virtual CElement * copy() const {
        CValue * expression = NULL;
        if (this->expression != NULL){
            expression = (CValue*) this->expression->copy();
        }
        return new CHelper(getLine(), getColumn(), name, expression, (CValue*) original->copy());
    }

    static string downcase(string str){
        std::transform(str.begin(), str.end(), str.begin(), lowerCase);
        return str;
    }

    virtual CValue * getOriginal() const {
        return original;
    }

    /* might be NULL */
    virtual CValue * getArgument() const {
        return expression;
    }
    
    virtual void walk(CWalker & walker) const {
        walker.onHelper(*this);
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_HELPER << getLine() << getColumn() << name << original->serialize();
        *token << (expression != NULL);
        if (expression != NULL){
            *token << expression->serialize();
        }
        return token;
    }

    static CHelper * deserialize(const Token * token){
        string name;
        const Token * next;
        const Token * expression = NULL;
        int line, column;
        bool hasExpression = false;
        TokenView view = token->view();
        view >> line >> column >> name >> next >> hasExpression;
        if (hasExpression){
            view >> expression;
            return new CHelper(line, column, name, CValue::deserialize(expression), CValue::deserialize(next));
        }
        return new CHelper(line, column, name, NULL, CValue::deserialize(next));
    }

    using CElement::operator==;
    bool operator==(const CValue & him) const {
        return him == *this;
    }

    bool operator==(const CHelper & him) const {
        return name == him.name &&
               *original == *him.original &&
               ((expression == NULL && him.expression == NULL) ||
                ((expression != NULL && him.expression != NULL) &&
                 (*expression == *him.expression)));
    }

    bool operator==(const string & str) const {
        return downcase(name) == downcase(str);
    }
    
    virtual string getType() const {
        return "helper";
    }

    virtual string toString() const {
        ::std::ostringstream out;
        out << name;
        if (expression != NULL){
            out << "(" << expression->toString() << ")";
        }
        out << ", " << original->toString();
        return Util::trim(out.str());
    }

    class CHelperView: public CViewImplementation {
    public:
        CHelperView(const CHelper * owner):
        owner(owner){
        }

        const CHelper * owner;

        virtual string getType() const {
            return owner->getType();
        }
        
        virtual const CValue * self() const {
            return owner;
        }

        virtual string toString() const {
            return owner->toString();
        }
    };

    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CHelperView(this)));
    }
    
    /*
    virtual bool referenced(const void * value) const {
        if (value == this){
            return true;
        }
        
        for (list<string*>::const_iterator it = names.begin(); it != names.end(); it++){
            if (value == *it){
                return true;
            }
        }

        return false;
    }
    */
    
    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        original->mark(marks);
        if (expression != NULL){
            expression->mark(marks);
        }
    }

    virtual ~CHelper(){
        delete original;
        if (expression!=NULL) delete expression;
    }

protected:
    string name;
    CValue * expression;
    CValue * original;
};

} //end AST
} //end SGF

#endif
