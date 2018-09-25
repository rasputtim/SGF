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
#ifndef _S_G_E_section_h_
#define _S_G_E_section_h_

#include <stdio.h>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "attribute.h"
#include "attribute-simple.h"
#include "Value.h"
#include "exception.h"
#include "ast.h"
#include "../../util/SGF_Debug.h"

using namespace std;
namespace SGF{

namespace Ast{

class CWalker;

class  SGE_API CSection: public CElement {
public:
    static string SERIAL_SECTION_ATTRIBUTE;
    static string SERIAL_SECTION_VALUE;

    CSection(const string * name):
    name(name){
        if (name == 0){
            cerr << "[" << __FILE__ << ": " << __LINE__ << "] Cannot create a section with an empty name" << endl;
            exit(-1);
        }
    }

    enum WalkList{
        WalkAttribute,
        WalkValue,
    };

    virtual void walk(CWalker & walker){
		Debug::debug(Debug::parsers,__FUNCTION__) << "Starting Walking on Section: " << this->getName() << endl;
		walker.onSection(*this);
        list<CAttribute*>::iterator attribute_it = attributes.begin();
        list<CValue*>::iterator value_it = values.begin();

        /* walk values in the order they came in. hopefully the number of values in the
         * walkList are the same number of items in the attributes+values lists.
         * I mean this should be the case since the only operations done to those lists
         * is adding elements. No one ever removes them.
         */
        for (list<WalkList>::iterator it = walkList.begin(); it != walkList.end(); it++){
            WalkList what = *it;
			switch (what){
                case WalkAttribute : {
                    CAttribute * attribute = *attribute_it;
					Debug::debug(Debug::parsers,__FUNCTION__) << " Walking on Section Attribute: " << attribute->toString() << endl;
		    		attribute->walk(walker);
                    attribute_it++;
                    break;
                }
                case WalkValue : {
                    CValue * value = *value_it;
					Debug::debug(Debug::parsers,__FUNCTION__) << "Walking on Section value: "<< value->toString()<< " // of Type: " << value->getType() << endl;
		    		value->walk(walker);
                    value_it++;
                    break;
                }
            }
        }

        /*
        for (list<CAttribute*>::iterator it = attributes.begin(); it != attributes.end(); it++){
            CAttribute * attribute = *it;
            attribute->walk(walker);
        }

        for (list<CValue*>::iterator it = values.begin(); it != values.end(); it++){
            CValue * value = *it;
            value->walk(walker);
        }
        */
        walker.onSectionFinished(*this);
    }

    string getName() const {
        return *name;
    }

	virtual CValue * getFirstValue()  {
       list<CValue*>::iterator value_it = values.begin();
		return *value_it;
    }

	virtual list<CValue*> * getValues() {
    return &values;
    }

    void addAttribute(CAttribute * attribute){
        attributes.push_back(attribute);
        walkList.push_back(WalkAttribute);
    }

    template <class Thing> static bool checkEquality(const list<Thing*> & my_list, const list<Thing*> & him_list){
        typename list<Thing*>::const_iterator my_it = my_list.begin();
        typename list<Thing*>::const_iterator him_it = him_list.begin();
        while (true){
            if (my_it == my_list.end() || him_it == him_list.end()){
                break;
            }
            Thing * mine = *my_it;
            Thing * him = *him_it;
            if (*mine != *him){
                return false;
            }

            my_it++;
            him_it++;
        }

        return my_it == my_list.end() && him_it == him_list.end();
    }

    using CElement::operator==;
    virtual bool operator==(const CSection & him) const {
        if (this == &him){
            return true;
        }

        return checkEquality(attributes, him.attributes) &&
               checkEquality(values, him.values);
    }

    virtual CElement * copy() const {
        CSection * out = new CSection(new string(getName()));
        out->walkList = walkList;
        for (list<CAttribute*>::const_iterator attribute_it = attributes.begin(); attribute_it != attributes.end(); attribute_it++){
            out->attributes.push_back((CAttribute*) (*attribute_it)->copy());
        }

        for (list<CValue*>::const_iterator value_it = values.begin(); value_it != values.end(); value_it++){
            out->values.push_back((CValue*) (*value_it)->copy());
        }

        return out;
    }

    const list<CAttribute *> & getAttributes() const {
        return attributes;
    }

    void addValue(CValue * value){
        values.push_back(value);
        walkList.push_back(WalkValue);
    }

    virtual Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_SECTION_LIST << getName();
        list<CAttribute*>::const_iterator attribute_it = attributes.begin();
        list<CValue*>::const_iterator value_it = values.begin();
        for (list<WalkList>::const_iterator it = walkList.begin(); it != walkList.end(); it++){
            WalkList what = *it;
            switch (what){
                case WalkAttribute : {
                    CAttribute * attribute = *attribute_it;
                    Token * next = token->newToken();
                    *next << SERIAL_SECTION_ATTRIBUTE << attribute->serialize();
                    attribute_it++;
                    break;
                }
                case WalkValue : {
                    CValue * value = *value_it;
                    Token * next = token->newToken();
                    *next << SERIAL_SECTION_VALUE << value->serialize();
                    value_it++;
                    break;
                }
            }
        }

        return token;
    }

    static CSection * deserialize(const Token * token){
        const Token * next;
        string name;
        TokenView view = token->view();
        view >> name;
        CSection * section = new CSection(new string(name));
        while (view.hasMore()){
            view >> next;
            if (*next == SERIAL_SECTION_ATTRIBUTE){
                const Token * attribute;
                next->view() >> attribute;
                section->addAttribute(CAttribute::deserialize(attribute));
            } else if (*next == SERIAL_SECTION_VALUE){
                const Token * value;
                next->view() >> value;
                section->addValue(CValue::deserialize(value));
            } else {
                throw CException("Can't deserialize " + next->getName());
            }
        }

        return section;
    }

    string toString(){
        ::std::ostringstream out;

        out << "[" << *name << "]" << endl;

        list<CAttribute*>::iterator attribute_it = attributes.begin();
        list<CValue*>::iterator value_it = values.begin();
        for (list<WalkList>::iterator it = walkList.begin(); it != walkList.end(); it++){
            WalkList what = *it;
            switch (what){
                case WalkAttribute : {
                    CAttribute * attribute = *attribute_it;
                    out << attribute->toString() << endl;
                    attribute_it++;
                    break;
                }
                case WalkValue : {
                    CValue * value = *value_it;
                    out << value->toString() << endl;
                    value_it++;
                    break;
                }
            }
        }

        return out.str();
    }

    void debugExplain() {
        // printf("[%s]\n", stringData.c_str());
        //cout << "[" << *name << "]" << endl;
		Debug::debug(Debug::parsers,__FUNCTION__) << "Section Name :" <<*name <<endl;

		if(!values.empty()) {
			Debug::debug(Debug::parsers,__FUNCTION__) << " values for section: " <<*name <<endl;
 			for (list<CValue*>::iterator it = values.begin(); it != values.end(); it++){
            CValue * value = *it;
            value->debugExplain();
			}
		}
		 if(!attributes.empty()) {
			Debug::debug(Debug::parsers,__FUNCTION__) << " attributes for Section: " <<*name <<endl;
 			for (list<CAttribute*>::iterator it = attributes.begin(); it != attributes.end(); it++){
            CAttribute * attribute = *it;
            attribute->debugExplain();
			}
		}
    }

    virtual CAttributeSimple * findAttribute(const string & find) const {
        for (list<CAttribute*>::const_iterator attribute_it = getAttributes().begin(); attribute_it != getAttributes().end(); attribute_it++){
            CAttribute * attribute = *attribute_it;
            if (attribute->getKind() == CAttribute::Simple){
                CAttributeSimple * simple = (CAttributeSimple*) attribute;
                if (*simple == find){
                    return simple;
                }
            }
        }

        throw CException("Could not find attribute " + find + " in section " + getName());
    }

    /* mark phase of garbage collection. all live pointers are marked 'true' */
    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        marks[name] = true;
        for (list<CAttribute*>::const_iterator it = attributes.begin(); it != attributes.end(); it++){
            CAttribute * attribute = *it;
            attribute->mark(marks);
        }
        for (list<CValue*>::const_iterator it = values.begin(); it != values.end(); it++){
            CValue * value = *it;
            value->mark(marks);
        }
    }

    /*
    virtual bool referenced(const void * value) const {
        if (value == this){
            return true;
        }

        if (value == name){
            return true;
        }

        for (list<CAttribute*>::const_iterator it = attributes.begin(); it != attributes.end(); it++){
            CAttribute * attribute = *it;
            if (attribute->referenced(value)){
                return true;
            }
        }
        for (list<CValue*>::const_iterator it = values.begin(); it != values.end(); it++){
            CValue * v = *it;
            if (v->referenced(value)){
                return true;
            }
        }
        return false;
    }
    */

    virtual ~CSection(){
        delete name;
        for (list<CAttribute*>::iterator it = attributes.begin(); it != attributes.end(); it++){
            delete *it;
        }
        for (list<CValue*>::iterator it = values.begin(); it != values.end(); it++){
            delete *it;
        }
    }

private:
    const string * name;
    list<CAttribute *> attributes;
    list<CValue *> values;
    list<WalkList> walkList;
};

} //end AST
} //end SGF
#endif
