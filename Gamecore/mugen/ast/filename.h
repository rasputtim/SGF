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
#ifndef _S_G_E_ast_filename_h_
#define _S_G_E_ast_filename_h_

#include "Value.h"
#include <string>
#include "../../util/SGF_Util.h"
using namespace std;
namespace SGF{

namespace Ast{

class  SGE_API CFilename: public CValue {
public:
    CFilename(const string * str):
    str(str){
    }

    virtual string toString() const {
        return Util::trim(*str);
    }

    using CValue::operator>>;

    virtual const CValue & operator>>(string & str) const {
        str = Util::trim(*(this->str));
        return *this;
    }

    virtual CElement * copy() const {
        return new CFilename(new string(*str));
    }

    virtual string getType() const {
        return "filename";
    }
   class CFilenameView: public CViewImplementation {
    public:
        CFilenameView(const CFilename * owner):
        owner(owner){
        }

        const CFilename * owner;

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
        virtual CFilenameView & operator>>(string & str){
            str = Util::trim(*(owner->str));
            return *this;
        }
    };

    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CFilenameView(this)));
    }
 
    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_FILENAME << *str;
        return token;
    }

    static CFilename * deserialize(const Token * token){
        string out;
        token->view() >> out;
        return new CFilename(new string(out));
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CFilename & him) const {
        return *str == *him.str;
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        marks[str] = true;
    }

    /*
    virtual bool referenced(const void * value) const {
        return CValue::referenced(value) ||
               value == str;
    }
    */

    virtual ~CFilename(){
        delete str;
    }

protected:
    const string * str;
};

} // end AST
} //end SGF
#endif
