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
#ifndef _ast_keyword_h_
#define _ast_keyword_h_

#include "Value.h"
#include <string>
using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CKeyword: public CValue {
public:
    /* do not pass in a dynamically allocated string!!! */
    CKeyword(string str):
    str(str){
    }

    using CValue::operator>>;

    virtual const CValue & operator>>(string & str) const {
        str = this->str;
        return *this;
    }

    virtual void walk(CWalker & walker) const {
        walker.onKeyword(*this);
    }

    virtual CElement * copy() const {
        return new CKeyword(str);
    }

    using CElement::operator==;
    bool operator==(const CValue & him) const {
        return him == *this;
    }

    bool operator==(const CKeyword & him) const {
        return str == him.str;
    }

    bool operator==(const string & str) const {
        return downcase(toString()) == downcase(str);
    }

    static int lowerCase( int c ){
        return tolower(c);
    }
   class CKeywordView: public CViewImplementation {
    public:
        CKeywordView(const CKeyword * keyword):
        keyword(keyword){
        }

        const CKeyword * keyword;

        using CViewImplementation::operator>>;
        virtual const CKeywordView & operator>>(string & str) const {
            str = keyword->str;
            return *this;
        }

        virtual string getType() const {
            return keyword->getType();
        }
        
        virtual const CValue * self() const {
            return keyword;
        }
        
        virtual string toString() const {
            return keyword->toString();
        }
    };

    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CKeywordView(this)));
    }
 
    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_KEYWORD << toString();
        return token;
    }

    static CKeyword * deserialize(const Token * token){
        string name;
        token->view() >> name;
        return new CKeyword(name);
    }

    static string downcase(string str){
        std::transform(str.begin(), str.end(), str.begin(), lowerCase);
        return str;
    }

    virtual string getType() const {
        return "keyword";
    }

    virtual string toString() const {
        return str;
    }

    virtual ~CKeyword(){
        /* don't delete str */
    }

protected:
    string str;
};

} //end AST
} //end SGF
#endif
