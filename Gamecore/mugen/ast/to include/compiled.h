#ifndef _SGF_c566d5b5f2dc27b39785c29f660bef1a
#define _SGF_c566d5b5f2dc27b39785c29f660bef1a

#include "Value.h"

namespace Ast{

class CompiledValue: public CValue {
public:
    CompiledValue(){
    }

    virtual void walk(CWalker & walker) const {
        walker.onCompiledValue(*this);
    }
};

}

#endif
