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
#ifndef _S_G_E_AST_KEY_H_
#define _S_G_E_AST_KEY_H_

#include "ast.h"
#include "walker.h"
#include <map>
#include <vector>
#include "../../util/SGF_Debug.h"
using namespace std;
namespace SGF{

namespace Ast{

class CKeySingle;

class  SGE_API CKey: public CValue {
public:
    CKey(){
    }

    virtual string getType() const {
        return "key";
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }
	   class CKeyView: public CViewImplementation {
    public:
        CKeyView(const CKey * owner):
        owner(owner){
        }

        const CKey * owner;

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
        return CView(Util::CReferenceCount<CViewImplementation>(new CKeyView(this)));
    }

    /*
    virtual bool same(const CKey & key) const {
        return false;
    }

    virtual bool same(const CKeySingle & key) const {
        return false;
    }
    */

    /*
    using CElement::operator==;
    virtual bool operator==(const CKey & key) const {
        return false;
    }
    */

    virtual ~CKey(){
    }
};

class  SGE_API CKeySingle: public CKey {
public:
    explicit CKeySingle(const char * name):
        CKey(),
        name(name){
        }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
    }

    using CElement::operator==;
    virtual bool operator==(const string & that) const {
        return name == that;
    }

    virtual bool operator==(const CKeySingle & key) const {
        return name == key.name;
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_KEY_SINGLE << name;
        return token;
    }

    static CKeySingle * deserialize(const Token * token){
        string what;
        token->view() >> what;
        return new CKeySingle(what.c_str());
    }

    virtual bool operator==(const CKey & key) const {
        return key == *this;
    }

    virtual void walk(CWalker & walker) const {
        walker.onKeySingle(*this);
    }

    virtual string toString() const {
        return name;
    }

    virtual CElement * copy() const {
        return new CKeySingle(name.c_str());
    }

    virtual ~CKeySingle(){
    }

protected:
    string name;
};

class  SGE_API CKeyModifier: public CKey {
public:
    enum ModifierType{
        /* slash (/) - means the key must be held down
         * egs. command = /D       ;hold the down direction
         * command = /DB, a   ;hold down-back while you press a
         */
        MustBeHeldDown,

        /*  tilde (~) - to detect key releases
         *  egs. command = ~a       ;release the a button
         *  command = ~D, F, a ;release down, press fwd, then a
         *  If you want to detect "charge moves", you can specify
         *  the time the key must be held down for (in game-ticks)
         *  egs. command = ~30a     ;hold a for at least 30 ticks, then release
         */
        Release,

        /*  dollar ($) - Direction-only: detect as 4-way
         *  egs. command = $D       ;will detect if D, DB or DF is held
         *  command = $B       ;will detect if B, DB or UB is held
         */
        Direction,

        /* greater-than (>) - means there must be no other keys pressed or released
         * between the previous and the current symbol.
         * egs. command = a, >~a   ;press a and release it without having hit
         * or released any other keys in between
         */
        Only,
    };

    CKeyModifier(ModifierType type, const CKey * key, int ticks = 0):
        CKey(),
        type(type),
        key(key),
        extra(ticks){
        }

    virtual void walk(CWalker & walker) const {
        walker.onKeyModifier(*this);
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        key->mark(marks);
    }

    virtual ModifierType getModifierType() const {
        return type;
    }

    virtual inline int getExtra() const {
        return extra;
    }

    virtual const CKey * getKey() const {
        return key;
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_KEY_MODIFIER << getModifierType() << getExtra() << getKey()->serialize();
        return token;
    }

    static CKeyModifier * deserialize(const Token * token){
        int type = 0;
        int extra = 0;
        const Token * next;
        token->view() >> type >> extra >> next;
        return new CKeyModifier(ModifierType(type), (CKey*) CValue::deserialize(next), extra);
    }

    using CElement::operator==;
    virtual bool operator==(const CKey & key) const {
        return key == *this;
        // return key.same(*this);
    }

    virtual bool operator==(const CKeyModifier & him) const {
        return getModifierType() == him.getModifierType() &&
               getExtra() == him.getExtra() &&
               *getKey() == *him.getKey();
    }

    virtual string toString() const {
        ::std::ostringstream out;
        out << modifierName(type);
        if (type == Release && extra != 0){
            out << extra;
        }
        out << key->toString();
        return out.str();
    }

    const char * modifierName(ModifierType type) const {
        switch (type){
            case MustBeHeldDown : return "/";
            case Release : return "~";
            case Direction : return "$";
            case Only : return ">";
            default : return "?";
        }
    }

    virtual CElement * copy() const {
        return new CKeyModifier(type, (CKey*) key->copy(), extra);
    }

    virtual ~CKeyModifier(){
        delete key;
    }

protected:
    const ModifierType type;
    const CKey * key;
    const int extra;
};

class  SGE_API CKeyCombined: public CKey {
public:
    CKeyCombined(const CKey * key1, const CKey * key2):
    CKey(),
    key1(key1),
    key2(key2){
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        key1->mark(marks);
        key2->mark(marks);
    }

    virtual void walk(CWalker & walker) const {
        walker.onKeyCombined(*this);
    }

    virtual const CKey * getKey1() const {
        return key1;
    }

    virtual const CKey * getKey2() const {
        return key2;
    }

    using CElement::operator==;
    virtual bool operator==(const CKey & key) const {
        return key == *this;
        // return key.same(*this);
    }

    virtual bool operator==(const CKeyCombined & him) const {
        return *getKey1() == *him.getKey1() &&
               *getKey2() == *him.getKey2();
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_KEY_COMBINED << key1->serialize() << key2->serialize();
        return token;
    }

    static CKeyCombined * deserialize(const Token * token){
        const Token * left;
        const Token * right;
        token->view() >> left >> right;
        return new CKeyCombined((CKey*) CValue::deserialize(left),
                               (CKey*) CValue::deserialize(right));
    }

    virtual string toString() const {
        ::std::ostringstream out;
        out << key1->toString() << "+" << key2->toString();
        return out.str();
    }

    virtual CElement * copy() const {
        return new CKeyCombined((CKey*) key1->copy(), (CKey*) key2->copy());
    }

    virtual ~CKeyCombined(){
        delete key1;
        delete key2;
    }

protected:
    const CKey * key1;
    const CKey * key2;
};

class  SGE_API CKeyList: public CKey {
public:
    CKeyList(const vector<CKey*> & keys):
        CKey(),
        keys(keys){
        }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        for (vector<CKey*>::const_iterator it = keys.begin(); it != keys.end(); it++){
            CKey * key = (CKey *) *it;
            key->mark(marks);
        }
    }

    using CElement::operator==;
    virtual bool operator==(const CKey & key) const {
        return key == *this;
        // return key.same(*this);
    }

    virtual bool operator==(const CKeyList & him) const {
        vector<CKey*>::const_iterator my_it = keys.begin();
        vector<CKey*>::const_iterator him_it = him.keys.begin();
        while (true){
            if (my_it == keys.end() || him_it == him.keys.end()){
                break;
            }

            if (**my_it != **him_it){
                return false;
            }

            my_it++;
            him_it++;
        }

        return my_it == keys.end() && him_it == him.keys.end();
    }

    virtual CElement * copy() const {
        vector<CKey*> copied;
        for (vector<CKey*>::const_iterator it = keys.begin(); it != keys.end(); it++){
            copied.push_back((CKey*) (*it)->copy());
        }
        return new CKeyList(copied);
    }

    virtual const vector<CKey*> & getKeys() const {
        return keys;
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_KEY_LIST;
        for (vector<CKey*>::const_iterator it = keys.begin(); it != keys.end(); it++){
            CKey * key = *it;
            *token << key->serialize();
        }
        return token;
    }

    static CKeyList * deserialize(const Token * token){
        vector<CKey*> keys;
        try{
            TokenView view = token->view();
            while (true){
                const Token * next;
                view >> next;
                keys.push_back((CKey*) CValue::deserialize(next));
            }
        } catch (const CTokenException & ex){
			 Debug::debug(1,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
        }
        return new CKeyList(keys);
    }

    virtual string toString() const {
        ::std::ostringstream out;

        for (vector<CKey*>::const_iterator it = keys.begin(); it != keys.end(); it++){
            if (it != keys.begin()){
                out << ", ";
            }
            out << (*it)->toString();
        }

        return out.str();
    }
	 virtual string getType() const {
        return "keyList";
    }
    virtual ~CKeyList(){
        for (vector<CKey*>::const_iterator it = keys.begin(); it != keys.end(); it++){
            delete (*it);
        }
    }

protected:
    const vector<CKey*> keys;
};

} //end AST
} //end SGF
#endif
