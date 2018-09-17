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
#ifndef _S_G_E_ast_number_h_
#define _S_G_E_ast_number_h_

#include "Value.h"
#include <string>
#include <sstream>
#include <math.h>
using namespace std;
namespace SGF{

namespace Ast{
	using namespace std;
class  SGE_API CNumber: public CValue {
public:
    CNumber(double value):
    CValue(-1,-1),
	value(value){
        /* arbitrary limit */
        /*
        if (value > 999999){
            value = 999999;
        }
        */
    }
	 CNumber(int line, int column, double value):
    CValue(line,column),
	value(value){
        /* arbitrary limit */
        /*
        if (value > 999999){
            value = 999999;
        }
        */
    }
    using CValue::operator>>;

    virtual const CValue & operator>>(const CValue *& v) const {
        v = this;
        return *this;
    }

    virtual const CValue & operator>>(int & x) const {
        x = (int) value;
        return *this;
    }

    virtual void walk(CWalker & walker) const {
        walker.onNumber(*this);
    }
	    class CNumberView: public CViewImplementation {
    public:
        CNumberView(const CNumber * owner):
        owner(owner){
        }

        const CNumber * owner;

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
        virtual CNumberView & operator>>(const CValue *& v){
            v = owner;
            return *this;
        }

        virtual CNumberView & operator>>(int & x){
            x = (int) owner->value;
            return *this;
        }

        virtual CNumberView & operator>>(double & x){
            x = owner->value;
            return *this;
        }


        virtual CNumberView & operator>>(bool & item){
            /* cast to int here? probably not because then 0.1 would become false
             * can an IEEE floating point value be exactly 0 in binary?
             */
            if (owner->value == 0){
                item = false;
            } else {
                item = true;
            }
            return *this;
        }
    };

    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CNumberView(this)));
    }

    static CNumber * deserialize(const Token * token){
        double value;
        token->view() >> value;
        return new CNumber(value);
    }

    virtual CElement * copy() const {
        return new CNumber(value);
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CNumber & him) const {
        /* doubles are printed with a precision of 6 in the tokens */
        double epsilon = 0.00001;
        return fabs(value - him.value) < epsilon;
    }

    virtual const CValue & operator>>(double & x) const {
        x = value;
        return *this;
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_NUMBER << value;
        return token;
    }

    virtual const CValue & operator>>(bool & item) const {
        /* cast to int here? probably not because then 0.1 would become false
         * can an IEEE floating point value be exactly 0 in binary?
         */
        if (value == 0){
            item = false;
        } else {
            item = true;
        }
        return *this;
    }
	virtual const CValue & operator>>(vector<int> & itemList) const {
        
            itemList.push_back(value);
        
        return *this;
    }
    virtual string getType() const {
        return "number";
    }
	virtual void changeSignal() {
		value = value * -1;
	}
    virtual string toString() const {
        ::std::ostringstream out;
        // out << '[' << value << ']';
        out << value;
        return out.str();
    }

    virtual ~CNumber(){
    }
protected:
    double value;
};

/* this is hack to make double jumping work. try not to use this class if you
 * can help it.
 */
class  SGE_API MutableNumber: public CNumber {
public:
    MutableNumber(double value):
    CNumber(value){
    }

    virtual ~MutableNumber(){
    }

    double get() const {
        return this->value;
    }

    void set(double v){
        this->value = v;
    }
};

} //end ASt
} //end SGF

#endif
