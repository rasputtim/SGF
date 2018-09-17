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
#ifndef _S_G_E_ast_hitdef_h_
#define _S_G_E_ast_hitdef_h_

#include "Value.h"
#include <string>
#include <sstream>
using namespace std;
namespace SGF{

namespace Ast{



class  SGE_API CHitDefAttribute: public CValue {
public:
    CHitDefAttribute(const string & value):
    CValue(-1,-1),
	value(value){
    }
	CHitDefAttribute(int line, int column,const string & value):
    CValue(line,column),
	value(value){
    }
    using CValue::operator>>;

    virtual const CValue & operator>>(string & str) const {
        str = value;
        return *this;
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CHitDefAttribute & him) const {
        return value == him.value;
    }

    virtual void walk(CWalker & walker) const {
        walker.onHitDefAttribute(*this);
    }
	class CHitDefAttributeView: public CViewImplementation {
    public:
        CHitDefAttributeView(const CHitDefAttribute * owner):
        owner(owner){
        }

        const CHitDefAttribute * owner;

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
        virtual CHitDefAttributeView & operator>>(string & str){
            str = owner->value;
            return *this;
        }
    };

    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CHitDefAttributeView(this)));
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_HITDEF_ATTRIBUTE << value;
        return token;
    }

    static CHitDefAttribute * deserialize(const Token * token){
        string value;
        token->view() >> value;
        return new CHitDefAttribute(value);
    }

    virtual CElement * copy() const {
        return new CHitDefAttribute(value);
    }

    virtual string getType() const {
        return "hitdef attribute";
    }

    virtual string toString() const {
        return value;
    }

    virtual ~CHitDefAttribute(){
    }

protected:
    string value;
};

class  SGE_API CHitDefAttackAttribute: public CValue {
public:
    CHitDefAttackAttribute():
	CValue(-1,-1){
    }
	CHitDefAttackAttribute(int line, int column):
	CValue(line, column){
    }
    using CValue::operator>>;

    virtual const CValue & operator>>(string & str) const {
        if (current != values.end()){
            str = *current;
            current++;
        } else {
            throw CException("No more values in this hitdef attack attribute: " + toString());
        }
        return *this;
    }

    virtual void walk(CWalker & walker) const {
        walker.onHitDefAttackAttribute(*this);
    }

    virtual void addAttribute(const string & value){
        values.push_back(value);
    }
	virtual void addAttribute(const string * value){
        string x=*value;
		values.push_back(x);
    }
    class CHitDefAttackAttributeView: public CViewImplementation {
    public:
        CHitDefAttackAttributeView(const CHitDefAttackAttribute * owner):
        owner(owner){
            current = owner->values.begin();
        }

        const CHitDefAttackAttribute * owner;
        vector<string>::const_iterator current;

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
        virtual CHitDefAttackAttributeView & operator>>(string & str){
            if (current != owner->values.end()){
                str = *current;
                current++;
            } else {
                throw CException("No more values in this hitdef attack attribute: " + owner->toString());
            }
            return *this;
        }
    };

    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CHitDefAttackAttributeView(this)));
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_HITDEF_ATTACK_ATTRIBUTE;
        for (vector<string>::const_iterator it = values.begin(); it != values.end(); it++){
            *token << *it;
        }
        return token;
    }

    static CHitDefAttackAttribute * deserialize(const Token * token){
        CHitDefAttackAttribute * attribute = new CHitDefAttackAttribute();
        try{
            TokenView view = token->view();
            while (true){
                string value;
                view >> value;
                attribute->addAttribute(value);
            }
        } catch (const CTokenException & ex){
			 Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
        }
        return attribute;
    }

    virtual void reset() const {
        current = values.begin();
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CHitDefAttackAttribute & him) const {
        vector<string>::const_iterator my_it = values.begin();
        vector<string>::const_iterator him_it = him.values.begin();
        while (true){
            if (my_it == values.end() || him_it == him.values.end()){
                break;
            }

            if (*my_it != *him_it){
                return false;
            }

            my_it++;
            him_it++;
        }

        return my_it == values.end() && him_it == him.values.end();
    }

    virtual CElement * copy() const {
        CHitDefAttackAttribute * attribute = new CHitDefAttackAttribute();
        for (vector<string>::const_iterator it = values.begin(); it != values.end(); it++){
            attribute->addAttribute(*it);
        }
        attribute->reset();
        return attribute;
    }

    virtual string getType() const {
        return "hitdef attack attribute";
    }

    virtual string toString() const {
        ::std::ostringstream out;
        bool first = true;
        for (vector<string>::const_iterator it = values.begin(); it != values.end(); it++){
            if (!first){
                out << ", ";
            }
            out << *it;
            first = false;
        }
        return out.str();
    }

    virtual ~CHitDefAttackAttribute(){
    }

protected:
    vector<string> values;
    mutable vector<string>::const_iterator current;
};

} // end AST
} //end SGF
#endif
