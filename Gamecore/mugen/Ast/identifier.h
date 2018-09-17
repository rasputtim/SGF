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
#ifndef _S_G_E_ast_identifier_h_
#define _S_G_E_ast_identifier_h_

#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

#include "Value.h"
#include "../../util/SGF_Token.h"
#include "../../util/SGF_Util.h"


using namespace ::std;
namespace SGF{

namespace Ast{

class  SGE_API CIdentifier: public CValue {
public:
    CIdentifier(int line, int column, const list<string> & names):
    names(names),
    line(line),
    column(column){
        stringed = toStringSlow();
		stringedLower = downcase(stringed);
    }

    CIdentifier(const list<string> & names):
    //CValue(-1, -1),
    names(names),
    line(-1),
    column(-1){
        stringed = toStringSlow();
		stringedLower = downcase(stringed);
    }

    static int lowerCase( int c ){
        return tolower(c);
    }

    virtual CElement * copy() const {
        return new CIdentifier(line, column, names);
    }

    static string downcase(string str){
        std::transform(str.begin(), str.end(), str.begin(), lowerCase);
        return str;
    }

    virtual void walk(CWalker & walker) const {
        walker.onIdentifier(*this);
    }
	class CIdentifierView: public CViewImplementation {
    public:
        CIdentifierView(const CIdentifier * owner):
        owner(owner){
        }

        const CIdentifier * owner;

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
	using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CIdentifierView(this)));
    }
    static CIdentifier * deserialize(const Token * token);

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CIdentifier & him) const {
        return getLine() == him.getLine() &&
               getColumn() == him.getColumn() &&
               toString() == him.toString();
    }

    bool operator==(const string & str) const {
        return toLowerString() == downcase(str);
    }

    virtual string getType() const {
        return "identifier";
    }
		
    virtual int getLine() const {
        return line;
    }

    virtual int getColumn() const {
        return column;
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_IDENTIFIER << line << column << toString();
        return token;
    }

    virtual string toString() const {
        return stringed;
    }

	virtual void addIdentifier(string string)  {
		names.push_back(string);
		stringed = toStringSlow();
    }
	virtual void addIdentifierToBegin(string string)  {
		names.push_front(string);
		stringed = toStringSlow();
    }
	   virtual const string & toLowerString() const {
        return stringedLower;
    }

    virtual string toStringSlow() const {
        ::std::ostringstream out;
        bool first = true;
        for (list<string>::const_iterator it = names.begin(); it != names.end(); it++){
            if (!first){
                out << ".";
            } else {
                first = false;
            }
            out << *it;
        }
        return Util::trim(out.str());
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
    }

    virtual ~CIdentifier(){
    }

protected:
    list<string> names;
    string stringed;
	string stringedLower;
    int line, column;
};

static list<string> toList(const string & s){
    list<string> out;
    out.push_back(s);
    return out;
}

class CSimpleIdentifier: public CIdentifier {
public:
    CSimpleIdentifier(const string & name):
    CIdentifier(-1, -1, toList(name)){
    }

    CSimpleIdentifier(int line, int column, const string & name):
    CIdentifier(line, column, toList(name)){
    }
};

}
} //end SGF
#endif
