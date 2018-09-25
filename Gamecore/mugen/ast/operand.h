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
#ifndef _S_G_E_ast_operand_h_
#define _S_G_E_ast_operand_h_

#include "Value.h"
#include <string>
#include <sstream>
#include <math.h>

using namespace std;
namespace SGF{


namespace Ast{

class SGE_API  COperand: public CValue {

public:
enum OperandType{
        Or,
        XOr,
        And,
		Not,
        BitwiseOr,
        BitwiseXOr,
        BitwiseAnd,
		Negation,
        Assignment,
        NotEquals,
		Equals,
        GreaterThanEquals,
        GreaterThan,
        LessThanEquals,
        LessThan,
        Add,
        Subtract,
        Multiply,
        Divide,
        Modulo,
        Power,
		
    };

    COperand(OperandType type):
    type(type){
        /* arbitrary limit */
        /*
        if (type > 999999){
            type = 999999;
        }
        */
    }

    using CValue::operator>>;

    virtual const CValue & operator>>(const CValue *& v) const {
        v = this;
        return *this;
    }

    virtual const CValue & operator>>(int & x) const {
        x = (int) type;
        return *this;
    }

    virtual void walk(CWalker & walker) const {
        walker.onOperand(*this);
    }
		class COperandView: public CViewImplementation {
    public:
        COperandView(const COperand * owner):
        owner(owner){
        }

        const COperand * owner;

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
        return CView(Util::CReferenceCount<CViewImplementation>(new COperandView(this)));
    }

    static COperand * deserialize(const Token * token){
        int type;
        token->view() >> type;
        return new COperand(OperandType(type));
    }

    virtual CElement * copy() const {
        return new COperand(type);
    } 

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const COperand & him) const {
        return getOperandType() == him.getOperandType();
    }

    virtual const CValue & operator>>(OperandType & x) const {
        x = type;
        return *this;
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_OPERAND << type;
        return token;
    }
/*
    virtual const CValue & operator>>(bool & item) const {
        // cast to int here? probably not because then 0.1 would become false
         // can an IEEE floating point value be exactly 0 in binary?
         //
        if (type == 0){
            item = false;
        } else {
            item = true;
        }
        return *this;
    }*/

    virtual string getType() const {
        return "operand";
    }

   
   virtual string toString() const {
        stringstream out;
        out << "<" << " " << operandName(type) << " "  << ">";
        return out.str();
    }

	virtual OperandType getOperandType() const {
        return type;
    }
    virtual const char * operandName(OperandType type) const {
        switch (type){
            case Or : return "||";
            case And : return "&&";
            case XOr : return "^^";
            case BitwiseOr : return "|";
            case BitwiseXOr : return "^";
            case BitwiseAnd : return "&";
            case Assignment : return ":=";
            case Equals : return "=";
            case NotEquals : return "!=";
            case GreaterThanEquals : return ">=";
            case GreaterThan : return ">";
            case LessThanEquals : return "<=";
            case LessThan : return "<";
            case Add : return "+";
            case Subtract : return "-";
            case Multiply : return "*";
            case Divide : return "/";
            case Modulo : return "%";
            case Power : return "**";
			case Not : return "!";
			case Negation : return "~";
            default : return "?";
        }
    }

    virtual ~COperand(){
    }
protected:
    OperandType type;
};


} //end AST
} //end SGF

#endif
