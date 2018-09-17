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
#ifndef _S_G_E_ast_value_list_h_
#define _S_G_E_ast_value_list_h_

#include "Value.h"
#include <list>
#include <string>
#include <sstream>
#include "../../util/SGF_Debug.h"
#include "../../exceptions/all.h"


using namespace std;
namespace SGF{

namespace Ast{

class CWalker;

class  SGE_API CValueList: public CValue {
public:
    CValueList(const list<CValue*> & values):
    values(values){
        current_value = this->values.begin();
    }

    CValueList(CValue * value){
        values.push_back(value);
        current_value = this->values.begin();
    }

    virtual void walk(CWalker & walker) const {
        walker.onValueList(*this);
    }

    virtual void reset() const {
        current_value = this->values.begin();
    }

	virtual void addValue(CValue *valor) {
		 values.push_back(valor);
    }
	virtual void addValuetoFront(CValue *valor) {
		if(valor != NULL) values.push_front(valor);
    }
    virtual bool hasMultiple() const {
        return true;
    }
	 void listfail() const {
        if (getLine() != -1 && getColumn() != -1){
            ::std::ostringstream out;
            out << "No more values in this value list at line " << getLine() << " column " << getColumn() << ": " << toString();
            throw CException(out.str());
        } else {
            throw CException("No more values in this value list: " + toString());
        }
    }

	class CValueListView: public CViewImplementation {
    public:
        CValueListView(const CValueList * owner):
        owner(owner){
            current_value = owner->values.begin();
        }
    
        const CValueList * owner;
        list<CValue*>::const_iterator current_value;

        virtual string getType() const {
            return owner->getType();
        }
        
        virtual const CValue * self() const {
            return owner;
        }
        
        virtual string toString() const {
            return owner->toString();
        }

        /* why doesn't this work?
        using ViewImplementation::operator>>;
        template <typename Kind>
        ViewImplementation & operator>>(Kind & value){
            if (current_value == owner->values.end()){
                owner->listfail();
            }
            (*current_value)->view() >> value;
            current_value++;
            return *this;
        }
        */

        virtual CViewImplementation & operator>>(const CValue *& value){
            if (current_value == owner->values.end()){
                owner->listfail();
            }
            (*current_value)->view() >> value;
            current_value++;
            return *this;
        }

        virtual CViewImplementation & operator>>(string & value){
            if (current_value == owner->values.end()){
                owner->listfail();
            }
            (*current_value)->view() >> value;
            current_value++;
            return *this;
        }

        virtual CViewImplementation & operator>>(int & x){
            if (current_value == owner->values.end()){
                owner->listfail();
            }
            (*current_value)->view() >> x;
            current_value++;
            return *this;
        }

        virtual CViewImplementation & operator>>(double & x){
            if (current_value == owner->values.end()){
                owner->listfail();
            }
            (*current_value)->view() >> x;
            current_value++;
            return *this;
        }

        virtual CViewImplementation & operator>>(bool & x){
            if (current_value == owner->values.end()){
                owner->listfail();
            }
            (*current_value)->view() >> x;
            current_value++;
            return *this;
        }

        virtual CViewImplementation & operator>>(vector<int> & x){
            while (current_value != owner->values.end()){
                int get;
                (*current_value)->view() >> get;
                x.push_back(get);
                current_value++;
            }
            return *this;
        }

        virtual CViewImplementation & operator>>(vector<double> & x){
            while (current_value != owner->values.end()){
                double get;
                (*current_value)->view() >> get;
                x.push_back(get);
                current_value++;
            }
            return *this;
        }
    };
    
    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CValueListView(this)));
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_VALUE_LIST;
        for (list<CValue*>::const_iterator it = values.begin(); it != values.end(); it++){
            const CValue * value = *it;
            *token << value->serialize();
        }
        return token;
    }

    static CValueList * deserialize(const Token * token){
        list<CValue*> values;
        try{
            TokenView view = token->view();
            while (true){
                const Token * next;
                view >> next;
                values.push_back(CValue::deserialize(next));
            }
        } catch (const CTokenException & ex){
			 Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
        }
        return new CValueList(values);
    }

    virtual CValue * get(unsigned int index) const {
        if (index >= 0 && index < values.size()){
            unsigned int count = 0;
            list<CValue*>::const_iterator it;
            for (it = values.begin(); count < index && it != values.end(); it++, count++){
            }
            return *it;
        }
        return 0;
    }

    virtual CElement * copy() const {
        list<CValue*> copied;
        for (list<CValue*>::const_iterator it = values.begin(); it != values.end(); it++){
            const CValue * value = *it;
            copied.push_back((CValue*) value->copy());
        }
        return new CValueList(copied);
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CValueList & him) const {
        list<CValue*>::const_iterator my_it = values.begin();
        list<CValue*>::const_iterator him_it = him.values.begin();
        while (true){
            if (my_it == values.end() || him_it == him.values.end()){
                break;
            }
			/*
			     Expression        Type      Equivalent expressions (yield same value)     
       ----------        ----      -----------------------------------------
              ptr        char **   &ptr[0]
             *ptr        char *    ptr[0] 
         *(ptr+i)        char *    ptr[i]; &ptr[i][0]
            **ptr        char      ptr[0][0]
      *(*(ptr+i))        char      ptr[i][0]; *ptr[i]
    *(*(ptr+i)+j)        char      ptr[i][j]


			*/
            if (**my_it != **him_it){
                return false;
            }

            my_it++;
            him_it++;
        }

        return my_it == values.end() && him_it == him.values.end();
    }

    using CValue::operator>>;

    virtual const CValue & operator>>(const CValue *& value) const {
        if (current_value == this->values.end()){
            throw CException("No more values in this value list: " + toString());
        }
        value = *current_value;
        current_value++;
        return *this;
    }

    virtual const CValue & operator>>(string & item) const {
        if (current_value == this->values.end()){
            throw CException("No more values in this value list: " + toString());
        }
        CValue * value = *current_value;
        *value >> item;
        current_value++;
        return *this;
    }
	virtual int getSize() {
		return values.size();
	}
    virtual const CValue & operator>>(int & item) const {
        if (current_value == this->values.end()){
            throw CException("No more values in this value list: " + toString());
        }
        CValue * value = *current_value;
        *value >> item;
        current_value++;
        return *this;
    }

    virtual const CValue & operator>>(vector<int> & itemList) const {
        while (current_value != this->values.end()){
            int item;
            CValue * value = *current_value;
            *value >> item;
            itemList.push_back(item);
            current_value++;
        }
        return *this;
    }

    virtual const CValue & operator>>(vector<double> & itemList) const {
        while (current_value != this->values.end()){
            double item;
            CValue * value = *current_value;
            *value >> item;
            itemList.push_back(item);
            current_value++;
        }
        return *this;
    }

    virtual const CValue & operator>>(double & item) const {
        if (current_value == this->values.end()){
            throw CException("No more values in this value list: " + toString());
        }
        CValue * value = *current_value;
        *value >> item;
        current_value++;
        return *this;
    }

    virtual const CValue & operator>>(bool & item) const {
        if (current_value == this->values.end()){
            throw CException("No more values in this value list: " + toString());
        }
        CValue * value = *current_value;
        *value >> item;
        current_value++;
        return *this;
    }


    /*
    virtual const CValue & operator>>(string & str) const {
        str = toString();
        return *this;
    }
    */

    virtual string getType() const {
        return "list of values";
    }

    virtual string toString() const {
        ::std::ostringstream out;
        bool first = true;
        for (list<CValue*>::const_iterator it = values.begin(); it != values.end(); it++){
            if (!first){
                out << ", ";
            } else {
                first = false;
            }
            CValue * value = *it;
            if (value != 0){
                out << value->toString();
            }
        }
        return out.str();
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        for (list<CValue*>::const_iterator it = values.begin(); it != values.end(); it++){
            CValue * value = *it;
            value->mark(marks);
        }
    }

    virtual ~CValueList(){
        for (list<CValue*>::iterator it = values.begin(); it != values.end(); it++){
            delete *it;
        }
    }

protected:
    list<CValue*> values;
    mutable list<CValue*>::const_iterator current_value;
};

} //end AST
} //end SGF
#endif
