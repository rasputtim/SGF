#ifndef _sgf_ast_resource_h_
#define _sgf_ast_resource_h_

#include "Value.h"
#include <string>
#include <sstream>
#include <math.h>
#include "../../util/SGF_Pointer.h"
#include "../../util/SGF_Token.h"

/* This class deals with sounds/animations that might come from either the
 * player's own sff files or fightfx.
 *
 * f800 = fightfx.sff
 * s800 = players own sff file
 */

using namespace std;
namespace SGF{

class Token;


namespace Ast{

class CResource: public CValue {
public:
    CResource(int line, int column, CValue * value, bool fightfx, bool own):
    CValue(line, column),
    value(value),
    fightfx(fightfx),
    own(own){
    }

    class CResourceView: public CViewImplementation {
    public:
        CResourceView(const CResource * owner):
        owner(owner){
        }

        const CResource * owner;

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
        virtual CResourceView & operator>>(const CValue *& v){
            v = owner;
            return *this;
        }
    };

    using CValue::view;
    virtual CView view() const {
        return CView(Util::CReferenceCount<CViewImplementation>(new CResourceView(this)));
    }

    virtual void walk(CWalker & walker) const {
        walker.onResource(*this);
    }

    virtual const CValue * getValue() const {
        return value;
    }
    
    virtual CElement * copy() const {
        return new CResource(getLine(), getColumn(), (CValue*) value->copy(), fightfx, own);
    }

    using CElement::operator==;
    virtual bool operator==(const CValue & him) const {
        return him == *this;
    }

    virtual bool operator==(const CResource & him) const {
        return *value == *him.value &&
               fightfx == him.fightfx &&
               own == him.own;
    }
   
    static CResource * deserialize(const  Token * token){
        const  Token * value;
        int line, column;
        bool fightfx, own;
        token->view() >> line >> column >> value >> fightfx >> own;
        return new CResource(line, column, CValue::deserialize(value), fightfx, own);
    }

     Token * serialize() const {
         Token * token = new  Token();
        *token << SERIAL_RESOURCE << getLine() << getColumn() << value->serialize() << fightfx << own;
        return token;
    }

    /* if it starts with 'f' */
    bool isFight() const {
        return fightfx;
    }

    /* if it starts with 's' */
    bool isOwn() const {
        return own;
    }

    virtual string getType() const {
        return "resource";
    }

    virtual void mark(map<const void*, bool> & marks) const {
        marks[this] = true;
        value->mark(marks);
    }

    virtual string toString() const {
        ::std::ostringstream out;
        if (fightfx){
            out << "f";
        }
        if (own){
            out << "s";
        }
        out << "(" << value->toString() << ")";
        return out.str();
    }

    virtual ~CResource(){
    }

protected:
    const CValue * value;
    bool fightfx;
    bool own;
};

} //end AST
} //end SGF

#endif
