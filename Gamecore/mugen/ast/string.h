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
#ifndef _ast_string_h_
#define _ast_string_h_

#include "Value.h"
#include "../../util/SGF_Debug.h"
#include <string>
using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CString: public CValue {
public:
    CString(const string * str):
	  str(str){
		  stringedLower = downcase(*str);
    }

    virtual void walk(CWalker & walker) const {
			
			walker.onString(*this);
    }

    virtual string toString() const {
        size_t found;
		found=str->find('"');
		if (found!=string::npos)
			return *str;
		else
			return "\"" + *str + "\"";
    }
	 virtual string toString2() const {
        return *str ;
    }
	static int lowerCase( int c ){
        return tolower(c);
    }

	 static string downcase(string str){
        std::transform(str.begin(), str.end(), str.begin(), lowerCase);
        return str;
    }
       virtual const string & toLowerString() const {
        return stringedLower;
    }
    using CValue::operator>>;
    virtual const CValue & operator>>(string & str) const {
        str = *(this->str);
        return *this;
    }
	
	using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CString & him) const {
        return *str == *him.str;
    }
	virtual bool operator==(const string & him) const {
        return *str == him;
    }	
	   class CStringView: public CViewImplementation {
    public:
        CStringView(const CString * owner):
        owner(owner){
        }

        const CString * owner;

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
        virtual CViewImplementation & operator>>(string & str){
            str = *(owner->str);
            return *this;
        }
    };

    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CStringView(this)));
    }
 
	Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_STRING << *str;
        return token;
    }

    static CString * deserialize(const Token * token){
        string out;
        token->view() >> out;
        return new CString(new string(out));
    }

    virtual string getType() const {
        return "string";
    }

    virtual CElement * copy() const {
        return new CString(new string(*str));
    }

    /*
    virtual bool referenced(const void * value) const {
        return CValue::referenced(value) ||
               str == value;
    }
    */

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        marks[str] = true;
    }

    virtual ~CString(){
        delete str;
    }

protected:
    const string * str;
	string stringedLower;
};

} //end AST
} //end SGF
#endif
