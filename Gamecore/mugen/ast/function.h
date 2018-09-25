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
#ifndef _S_G_E_FUNCTION_H_
#define _S_G_E_FUNCTION_H_

#include "Value.h"
#include "value-list.h"
using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CFunction: public CValue {
public:
    CFunction(const string & name, const CValueList * args = NULL):
    CValue(-1,-1),
	name(name),
    args(args){
    }
	CFunction(int LINE, int COLUMN,const string & name, const CValueList * args = NULL):
    CValue(LINE,COLUMN),
	name(name),
    args(args){
    }
    virtual string toString() const {
        ::std::ostringstream out;
        out << name << "(";
        if (args != NULL){
            out << args->toString();
        }
        out << ")";
        return out.str();
    }

    virtual void walk(CWalker & walker) const {
        walker.onFunction(*this);
    }

    virtual const CValue * getArg(int n) const {
        if (args != NULL){
            return args->get(n);
        }
        return 0;
    }

    virtual const CValue * getArg1() const {
        return getArg(0);
    }

    virtual const CValue * getArg2() const {
        return getArg(1);
    }

    virtual const CValue * getArg3() const {
        return getArg(2);
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_FUNCTION << name;
        if (args != NULL){
            *token << args->serialize();
        }
        return token;
    }

    static CFunction * deserialize(const Token * token);

    static string downcase(string str){
        std::transform(str.begin(), str.end(), str.begin(), lowerCase);
        return str;
    }

    static int lowerCase( int c ){
        return tolower(c);
    }

    const string & getName() const {
        return name;
    }

    using CElement::operator==;
    bool operator==(const CValue & him) const {
        return him == *this;
    }

    bool operator==(const CFunction & him) const {
        if (name != him.name){
            return false;
        }

        if (args != NULL && him.args != NULL){
            return *args == *him.args;
        }

        if ((args == NULL && him.args != NULL) ||
            (args != NULL && him.args == NULL)){
            return false;
        }

        return true;
    }

    bool operator==(const string & str) const {
        return downcase(name) == downcase(str);
    }
	    class CFunctionView: public CViewImplementation {
    public:
        CFunctionView(const CFunction * owner):
        owner(owner){
        }

        const CFunction * owner;

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
        return CView(Util::CReferenceCount<CViewImplementation>(new CFunctionView(this)));
    }

    virtual CElement * copy() const {
        CValueList * args_copy = 0;
        if (args){
            args_copy = (CValueList*) args->copy();
        }
        return new CFunction(name, args_copy);
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        if (args){
            args->mark(marks);
        }
    }

    virtual string getType() const {
        return "function";
    }

    virtual ~CFunction(){
        delete args;
    }

protected:
    virtual void fail(const string & what) const {
        throw CException("Cannot read a " + what + " from function " + getName());
    }

    string name;
    const CValueList * args;
};

} //end AST
} // end SGF
#endif
