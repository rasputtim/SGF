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
#ifndef _S_G_E_ast_attribute_array_h_
#define _S_G_E_ast_attribute_array_h_

#include "attribute.h"
#include "keyword.h"
#include "identifier.h"
#include "exception.h"
#include "Value.h"
#include "walker.h"
#include <sstream>
#include "../../util/SGF_Debug.h"
using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CKeywordArray: public CKeyword {
public:

	CKeywordArray(const string name, const CValue * index):
    CKeyword(name),
    index(index)
    {
    }

    virtual CValue * copy() const {
       //FIXME
       //     return new CKeywordArray((CValue*) this->copy(), (CValue*) index->copy());
       return NULL;

    }

    virtual void walk(CWalker & walker){
        walker.onKeywordArray(*this);
	}

    using CElement::operator==;
    virtual bool operator==(const CKeyword & him) const {
        return him == *this;
    }

    virtual bool operator==(const CKeywordArray & him) const {

        return *index == *him.index;
    }

    virtual bool operator==(const string & str) const {
       // FIXME
            //return *keyword_name == str;

        return false;
    }

    static CKeywordArray * deserialize(const Token * token);

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_KEYWORD_ARRAY;

          *token << this->serialize();


        *token << index->serialize();

        return token;
    }



    int getIndex() const {
        int i;
        *index >> i;
        return i;
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



    }

    /* just the identifier */
    string idString() const {
         return this->toString();
               return "";
    }

    virtual string toString() const {
        ::std::ostringstream out;

        out << this->toString();

		out << index->toString() << ")" ;

        return out.str();
    }

    virtual ~CKeywordArray(){
        delete index;

    }

protected:
      const CValue * index;
   };

} //end ASt
} //end SGF
#endif
