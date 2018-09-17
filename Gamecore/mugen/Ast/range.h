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
#ifndef _range_h
#define _range_h

#include "Value.h"
using namespace std;
namespace SGF{

class CValue;

using namespace std;
namespace Ast{

class SGE_API  CRange: public CValue {
public:
    enum RangeType{
        AllInclusive,
        AllExclusive,
        LeftInclusiveRightExclusive,
        LeftExclusiveRightInclusive,
    };

	CRange(RangeType _type, const CValue * _low, const Ast::CValue * _high):
    type(_type),
    _low(_low),
    _high(_high){
    }

    virtual void walk(CWalker & walker) const {
        walker.onRange(*this);
    }

    virtual string toString(char left, char right) const {
        ::std::ostringstream out;
        out << left << _low->toString() << ", " << _high->toString() << right;
        return out.str();
    }

    virtual RangeType getRangeType() const {
        return type;
    }

    virtual string toString() const {
        switch (type){
            case AllInclusive : return toString('[', ']');
            case AllExclusive : return toString('(', ')');
            case LeftInclusiveRightExclusive : return toString('[', ')');
            case LeftExclusiveRightInclusive : return toString('(', ']');
            default : return "";
        }
    }

    virtual const CValue * getLow() const {
        return _low;
    }

    virtual const CValue * getHigh() const {
        return _high;
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CRange & him) const {
        return getRangeType() == him.getRangeType() &&
               *getLow() == *him.getLow() &&
               *getHigh() == *him.getHigh();
    }
   class CRangeView: public CViewImplementation {
    public:
        CRangeView(const CRange * owner):
        owner(owner){
        }

        const CRange * owner;

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
        return CView(Util::CReferenceCount<CViewImplementation>(new CRangeView(this)));
    }

    Token * serialize() const {
        Token * token = new Token();
        *token << SERIAL_RANGE << getRangeType() << getLow()->serialize() << getHigh()->serialize();
        return token;
    }

    static CRange * deserialize(const Token * token){
        int type;
        const Token * _low;
        const Token * _high;
        token->view() >> type >> _low >> _high;
        return new CRange(RangeType(type), CValue::deserialize(_low), CValue::deserialize(_high));
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        _low->mark(marks);
        _high->mark(marks);
    }

    virtual CElement * copy() const {
        return new CRange(type, (CValue*) _low->copy(), (CValue*) _high->copy());
    }

    virtual string getType() const {
        return "range";
    }

    virtual ~CRange(){
        delete _low;
        delete _high;
    }

protected:
    RangeType type;
    const CValue * _low;
    const CValue * _high;

};

} //end ASt
} //end SGF
#endif
