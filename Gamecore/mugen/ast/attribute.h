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
#ifndef _S_G_E_attribute_h
#define _S_G_E_attribute_h

#include "walker.h"
#include <map>
#include <string>
#include "ast.h"
#include "exception.h"
#include "../../util/SGF_Debug.h"
using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CAttribute: public CElement {
public:
    enum Kind{
        None = 0,
        Simple = 1,
        /* to avoid name clash with the CKeyword class */
        KeywordAttribute = 2,
        Array = 3,
    };

    CAttribute(Kind kind):
    CElement(-1,-1),
	kind(kind){
    }

	CAttribute(int line,int column,Kind kind):
    CElement(line,column),
	kind(kind){
    }
    virtual void walk(CWalker & walker){
        walker.onAttribute(*this);
    }

    static CAttribute * deserialize(const Token * token);

    using CElement::operator==;
    virtual bool operator==(const string & str) const = 0;

    virtual Kind getKind(){
        return kind;
    }

    virtual void debugExplain(){
    }

    virtual string toString() const = 0;
	virtual const void setValue(CValue *value) =0;

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
    }

	  
	/*
    virtual bool referenced(const void * value) const {
        return value == this;
    }
    */

    virtual ~CAttribute(){
    }
protected:
    Kind kind;
};

} //end ast
} // end sgf
#endif
