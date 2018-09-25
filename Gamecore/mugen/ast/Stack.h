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

#ifndef _AST_STACK_H
#define _AST_STACK_H
#include "../../util/SGF_Debug.h"

#define AST_STACKSIZE 300

#include <stdio.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <fstream>
#include <stdlib.h>

using namespace std;
namespace SGF{

namespace Ast {
class CValue;

class  SGE_API CStack: public CValue
{
//Constructor & Destructor
public:
	CStack(string _name): nPos(0),
	name(_name){
		memset(m_Stack,0,sizeof(m_Stack)); }
	~CStack() {}

   void ResetStack(){
		Debug::debug(Debug::parsers,__FUNCTION__) << "Reseting Stack: "<<name.c_str() << endl;
   	nPos=0;
    memset(m_Stack,0,sizeof(m_Stack));

	}

   virtual void walk(CWalker & walker) const {
        walker.onStack(*this);
    }
   int size() const{
   		return nPos;
	}
	void push(CValue *value){
		if(nPos>AST_STACKSIZE) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "Stack overflow: "<<name.c_str()<< endl;
		}else {
			m_Stack[nPos]=value;
			Debug::debug(Debug::parsers,__FUNCTION__) <<" Pushing type: " << value->getType()<< " | value: " << value->toString() << "to Stack of name: "<<name <<" with : "<< size()<<"  elements"<<endl;
			nPos++;
		}
	 }

    CValue* pop() const{
		if(nPos<0) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "CStack name: "<<name.c_str()<<" Stack underflow"<< endl;
			return NULL;
		}else {
		CValue* temp= m_Stack[--nPos];
		Debug::debug(Debug::parsers,__FUNCTION__) << "CStack name: "<<name.c_str()<<" Popping value:"<<temp->toString().c_str()<< endl;
   		return temp;
		}
	}
	 CValue* getToView(int index) const{
		if(index<0) {
			Debug::debug(Debug::parsers,__FUNCTION__) << "CStack name: "<<name.c_str()<<" Stack underflow"<< endl;
			return NULL;
		}else if(index >=nPos){
			Debug::debug(Debug::parsers,__FUNCTION__) << "CStack name: "<<name.c_str()<<"Inexistent Element"<< endl;
			return NULL;
		}else{
		CValue* temp= m_Stack[index];
		Debug::debug(Debug::parsers,__FUNCTION__) << "CStack name: "<<name.c_str()<<" Geting value: "<<temp->toString().c_str()<< " of type: "<< temp->getType()<< endl;
   		return temp;
		}
	}
	 virtual string toString() const {
        ::stringstream out;
        out << "( ";
		if (nPos <=0) {
			out <<"  <none>  " ;
		}
        for (int i=0; i<nPos ; i++){

			out <<" [ " <<m_Stack[i]->toString()<<" ] " ;
		}
        out << " )";
		return out.str();
    }
	 	   class CStackView: public CViewImplementation {
    public:
        CStackView(const CStack * owner):
        owner(owner){
        }

        const CStack * owner;

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
        return CView(Util::CReferenceCount<CViewImplementation>(new CStackView(this)));
    }
 
    Token * serialize() const {
        Token * token = new Token();
        for (int i=0; i<nPos ; i++){
		*token << SERIAL_EXPRESSION_STACK << m_Stack[nPos]->serialize();
		}


	return token;
    }
	string getType()const {
		return "stack";
	}
	string getName()const {
		return " <stack: " + name + " > ";
	}
	bool empty() { if (nPos==0) return true;
	else return false;
	}
	CStack  & operator=( const CStack  &copy ) {
	// Check for self-assignment!
//	Debug::debug(Debug::error,__FUNCTION__) << " CStack::Operator = copy // BEGIN" << endl;
	if (this == &copy)      // Same object?
      return *this;        // Yes, so skip assignment, and just return *this.
	for (int i=0;i<=nPos;i++){
		//this->push((CValue *)copy.getToView(i)->copy());
		memcpy ( m_Stack[i], copy.m_Stack[i], sizeof(copy.m_Stack[i]) );;
	}

	}
	 virtual bool operator==(const CStack & him) const {
        // criar uma variável CStack nova e copiá-la para him
		/*return getExpressionType() == him.getExpressionType() &&
               *getLeft() == *him.getLeft() &&
               *getRight() == *him.getRight();*/
		bool temp = true;
		for (int i=0;i<nPos;i++){
		  if ( *m_Stack[i] != *him.m_Stack[i] ) temp =false;
		}
		return temp;
    }
	virtual CElement * copy() const  {
         CStack * tempStack=new CStack(getName());
		//Debug::debug(Debug::error,__FUNCTION__) << "  CStack->copy //   name: " << getName() << endl;
		for (int i =0; i < nPos; i++) {
			tempStack->push(( CValue*)getToView(i)->copy() );
		}
		//tempStack=this;
		//Debug::debug(Debug::error,__FUNCTION__) << "  CStack->copy //Returning value: " << &tempStack << endl;

		return (CElement *) tempStack;
	}

public:
    mutable int nPos;
    CValue * m_Stack[AST_STACKSIZE];
	string name;
	
};
} //end AST
} //end SGF
#endif /*STACK_H_*/
