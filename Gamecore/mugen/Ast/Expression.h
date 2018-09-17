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
#ifndef _ast_EXPRESSION_H_
#define _ast_EXPRESSION_H_

#include "Value.h"
#include "Stack.h"


using namespace std;
namespace SGF{

namespace Ast{



class  SGE_API CExpression: public CValue {
public:
    CExpression():
        CValue(){
    }

    /* TODO: get rid of this method, this class should not be instantiated */
    /*
    virtual CElement * copy() const {
        return new CExpression();
    }
    */

    virtual string getType() const {
        return "expression";
    }

    virtual ~CExpression(){
    }
};

class  SGE_API CExpressionUnary: public CExpression {
public:
    enum UnaryType{
        Not,
        Minus,
        Negation,
    };

    CExpressionUnary(UnaryType type, const CValue * expression):
    type(type),
    expression(expression){
    }

    UnaryType getExpressionType() const {
        return type;
    }

    const CValue * getExpression() const {
        return expression;
    }

    static CExpressionUnary * deserialize(const Token * token){
        int type;
        const Token * value;
        token->view() >> type >> value;
        return new CExpressionUnary(UnaryType(type), CValue::deserialize(value));
    }
	    class CExpressionView: public CViewImplementation {
    public:
        CExpressionView(const CExpressionUnary * owner):
        owner(owner){
        }

        const CExpressionUnary * owner;

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
        virtual CExpressionView & operator>>(double & x){
            owner->expression->view() >> x;
            switch (owner->type){
                case Minus : {
                    x = -x;
                    break;
                }
                default : {
                    break;
                }
            }
            return *this;
        }
    };

    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CExpressionView(this)));
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_EXPRESSION_UNARY << getExpressionType() << getExpression()->serialize();
        return token;
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CExpressionUnary & him) const {
        return getExpressionType() == him.getExpressionType() &&
               *getExpression() == *him.getExpression();
    }

    virtual string getType() const {
        return "unary expression";
    }

    virtual CElement * copy() const {
        return new CExpressionUnary(type, (CValue*) expression->copy());
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        expression->mark(marks);
    }

    using CValue::operator>>;

    virtual const CValue & operator>>(double & x) const {
        *expression >> x;
        switch (type){
            case Minus : {
                x = -x;
                break;
            }
            default : {
                break;
            }
        }
        return *this;
    }

    virtual void walk(CWalker & walker) const {
        walker.onExpressionUnary(*this);
    }

    virtual string toString() const {
        stringstream out;
        out << prefixName(type) << expression->toString();
        return out.str();
    }

    virtual const char * prefixName(UnaryType type) const {
        switch (type){
            case Not : return "!";
            case Minus : return "-";
            case Negation : return "~";
            default : return "?";
        }
    }

    virtual ~CExpressionUnary(){
        delete expression;
    }

protected:
    UnaryType type;
    const CValue * expression;
};

class  SGE_API CExpressionInfix: public CExpression {
public:
    enum InfixType{
        Or,
        XOr,
        And,
        BitwiseOr,
        BitwiseXOr,
        BitwiseAnd,
        Assignment,
        Equals,
        Unequals,
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

    CExpressionInfix(InfixType type, const CValue * left, const CValue * right):
    CExpression(),
    type(type),
    left(left),
    right(right){
    }

    virtual InfixType getExpressionType() const {
        return type;
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        left->mark(marks);
        right->mark(marks);
    }

    virtual void walk(CWalker & walker) const {
        walker.onExpressionInfix(*this);
    }

    virtual inline const CValue * getLeft() const {
        return left;
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_EXPRESSION_INFIX << getExpressionType() << getLeft()->serialize() << getRight()->serialize();
        return token;
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CExpressionInfix & him) const {
        return getExpressionType() == him.getExpressionType() &&
               *getLeft() == *him.getLeft() &&
               *getRight() == *him.getRight();
    }
	class CExpressionView: public CViewImplementation {
    public:
        CExpressionView(const CExpressionInfix * owner):
        owner(owner){
        }

        const CExpressionInfix * owner;

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
        return CView(Util::CReferenceCount<CViewImplementation>(new CExpressionView(this)));
    }
 
    static CExpressionInfix * deserialize(const Token * token){
        int type;
        const Token * left;
        const Token * right;
        token->view() >> type >> left >> right;
        return new CExpressionInfix(InfixType(type), CValue::deserialize(left), CValue::deserialize(right));
    }

    virtual inline const CValue * getRight() const {
        return right;
    }

    virtual CElement * copy() const {
        return new CExpressionInfix(type, (const CValue*) left->copy(), (const CValue*) right->copy());
    }

    virtual string toString() const {
        stringstream out;
        out << "(" << left->toString() << " " << infixName(type) << " " << right->toString() << ")";
        return out.str();
    }

    virtual const char * infixName(InfixType type) const {
        switch (type){
            case Or : return "||";
            case And : return "&&";
            case XOr : return "^^";
            case BitwiseOr : return "|";
            case BitwiseXOr : return "^";
            case BitwiseAnd : return "&";
            case Assignment : return ":=";
            case Equals : return "=";
            case Unequals : return "!=";
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
            default : return "?";
        }
    }

    virtual string getType() const {
        return "infix expression";
    }

    virtual ~CExpressionInfix(){
        delete left;
        delete right;
    }

protected:
    InfixType type;
    const CValue * left;
    const CValue * right;
};
class  SGE_API CExpressionPostfix: public CExpression {
public:


	CExpressionPostfix(Ast::CStack *_stack):
			CExpression(),stack(_stack)
			{ }

   CExpressionPostfix():
			CExpression(),stack(NULL)
			{ }

   // virtual PostfixType getExpressionType() const {
   //     return type;
   // }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
       stack->mark(marks);

    }

    virtual void walk(CWalker & walker) const {
        walker.onExpressionPostfix(*this);
    }

    virtual inline  CValue * getInstruction() {
		return stack->pop();
    }
	virtual inline  bool haveInstruction() {
		return !stack->empty();
    }
	virtual string getInstructionType() const {
		return stack->getType();
    }

	virtual bool isOperand() const {
		string type= stack->getType();
		if (type == "operand")
			return true;
		else
			return false;
    }

	virtual bool isOperator() const {
		string type= stack->getType();
		if (type == "operand")
			return false;
		else
			return true;
    }
	   class CExpressionView: public CViewImplementation {
    public:
        CExpressionView(const CExpressionPostfix * owner):
        owner(owner){
        }

        const CExpressionPostfix * owner;

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
        return CView(Util::CReferenceCount<CViewImplementation>(new CExpressionView(this)));
    }
 
    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_EXPRESSION_POSTFIX << stack->serialize();
        return token;
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CExpressionPostfix & him) const {
        // criar uma variável CStack nova e copiá-la para him
		/*return getExpressionType() == him.getExpressionType() &&
               *getLeft() == *him.getLeft() &&
               *getRight() == *him.getRight();*/
		return *stack==*him.stack;
    }

    static CExpressionPostfix * deserialize(const Token * token){
        //int type;
        //const Token * left;
        //const Token * right;
        //token->view() >> type >> left >> right;
        //return new CExpressionPostfix(PostfixType(type), CValue::deserialize(left), CValue::deserialize(right));
		return NULL;
	}

    virtual inline const CValue * getStack() const {
        return stack;
    }

    virtual CElement * copy() const {
		//CStack * tempStack = (CStack *) stack->copy();
		//Debug::debug(Debug::error,__FUNCTION__) << " CExpressionPostfix->copy //stack returned value: " << &tempStack << endl;
		//tempStack->toString();
		CExpressionPostfix *tempExpression =  new CExpressionPostfix((CStack *) stack->copy());
		//Debug::debug(Debug::error,__FUNCTION__) << " CExpressionPostfix->copy //toString: " << endl;
		//tempExpression->toString();
	return tempExpression;
}

    virtual string toString() const {
        return stack->toString();
    }
	//using CValue::operator>>;

	virtual const CExpressionPostfix & operator>>(CExpressionPostfix & x) const {
		x.stack =(CStack*) (this->stack->copy());
        return *this;
    }

    virtual string getType() const {
        return "postfix expression";
    }

    virtual ~CExpressionPostfix(){
    }
	virtual void AddInstruction(CValue *value){
		stack->push(value);
	}
protected:
    CStack *stack;

};


} // end AST
} //end SGF
#endif
