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
#ifndef _S_G_E_value_h
#define _S_G_E_value_h

#include <iostream>
#include <map>
#include <vector>
#include "walker.h"
#include "exception.h"
#include "ast.h"
#include "../../util/SGF_Debug.h"
#include "../../util/SGF_Pointer.h"

using namespace std;
namespace SGF{

class Token;

using namespace ::std;
namespace Ast{
class CValue;
class CViewImplementation{
public:
    virtual CViewImplementation & operator>>(const CValue *& value){
        value = self();
        return *this;
    }

    virtual CViewImplementation & operator>>(string & value){
        value = toString();
        return *this;
    }
    
    virtual CViewImplementation & operator>>(int & x){
        fail("int");
        return *this;
    }

    virtual CViewImplementation & operator>>(double & x){
        fail("double");
        return *this;
    }
    
    virtual CViewImplementation & operator>>(bool & x){
        fail("bool");
        return *this;
    }
    
    virtual CViewImplementation & operator>>(vector<int> & x){
        fail("list of int");
        return *this;
    }
    
    virtual CViewImplementation & operator>>(vector<double> & x){
        fail("list of double");
        return *this;
    }

    virtual ~CViewImplementation(){
    }

protected:
    virtual string getType() const = 0;
    virtual string toString() const = 0;
    virtual const CValue * self() const = 0;

    virtual void fail(const string & what) const {
        throw CException("Cannot read a " + what + " from a " + getType()+ " descrition: " + toString());
    }
};

class CView{
public:
    CView(const Util::CReferenceCount<CViewImplementation> & view):
    view(view){
    }

    CView(const CView & copy):
    view(copy.view){
    }

    CView & operator=(const CView & copy){
        view = copy.view;
        return *this;
    }

    template <typename X>
    CView & operator>>(X & value){
        view->operator>>(value);
        return *this;
    }

   Util::CReferenceCount<CViewImplementation> view;
};

class  SGE_API CValue: public CElement {
public:

    CValue():
	CElement(-1,-1){
    }

	CValue(int line, int column):
	CElement(line,column){
    }

public:
    virtual string toString() const {
        return "";
    }

    virtual void walk(CWalker & walker) const {
        walker.onValue(*this);
    }

    /* true if this value has multiple values in it
     * should only be true for value-list
     */
    virtual bool hasMultiple() const {
        return false;
    }

    /* resets the internals so that operator>> starts over */
    virtual void reset() const {
    }

    virtual void debugExplain(){
        //cout << toString() << endl;
		Debug::debug(Debug::parsers,__FUNCTION__) << "==> " <<toString() <<endl;
        
    }

    static CValue * deserialize(const Token * token);

    /*
    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        throw Exception("Override this method");
    }
    */

    virtual const CValue & operator>>(const CValue *& value) const {
        value = this;
        // fail("value");
        return *this;
    }

    virtual const CValue & operator>>(string & str) const {
        str = toString();
        return *this;
    }

    virtual const CValue & operator>>(int & x) const {
        fail("int");
        return *this;
    }

    virtual const CValue & operator>>(double & x) const {
        fail("double");
        return *this;
    }

    virtual const CValue & operator>>(bool & x) const {
        fail("bool");
        return *this;
    }

    virtual const CValue & operator>>(vector<int> & x) const {
        fail("bool");
        return *this;
    }

    virtual const CValue & operator>>(vector<double> & x) const {
        fail("bool");
        return *this;
    }
	
    /*
    virtual bool referenced(const void * value) const {
        return value == this;
    }
    */
	   class CValueView: public CViewImplementation {
    public:
        CValueView(const CValue * owner):
        owner(owner){
        }

        using CViewImplementation::operator>>;
        virtual const CValueView & operator>>(const CValue *& value) const {
            value = owner;
            // fail("value");
            return *this;
        }
		 virtual const CValue * self() const {
            return owner;
        }
        const CValue * owner;

    protected:
        virtual string getType() const {
            return owner->getType();
        }

        virtual string toString() const {
            return owner->toString();
        }
    };

    /*
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CValueView(this)));
    }*/
    

    virtual CView view() const = 0;
	
 
    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
    }

    virtual string getType() const = 0;

    virtual ~CValue(){
    }

protected:
    virtual void fail(const string & what) const {
        throw CException("Cannot read a " + what + " from a " + getType()+ " description: " + toString());
    }
};

} //end AST
} //end SGF
#endif
