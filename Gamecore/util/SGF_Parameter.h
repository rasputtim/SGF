/*
  SGF - Salvat Game Fabric  (https://sourceforge.net/projects/sgfabric/)
  Copyright (C) 2010-2011 Salvatore Giannotta Filho <a_materasu@hotmail.com>

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
//C++_Class_Templates.cpp
#ifndef _S_G_F_PARAMETER_
#define _S_G_F_PARAMETER_
#include <iostream>
#include <vector>
#include "SGF_Config.h"

/**
 * \class CParameter
 *
 * \ingroup SGF_Util
 *
 * \brief Template para uma Fila (Queue) de tipo Genérico
 *
 * \author (last to touch it) $Autor: Salvatore Giannotta Filho $
 *
 * \note sintaxe:
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: a_materasu@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */

/* parameters are to be used to control the dynamic extent of values. values
 * can be pushed onto the current extent and are automatically popped off
 * upon function return.
 * this is similar to 'parameters' in Racket.
 * http://docs.racket-lang.org/reference/eval-model.html#%28part._parameter-model%29
 * This class is not thread safe.
 */

#include <vector>
#include "SGF_Pointer.h"

namespace Util{

/* the static variable `stack' has to be defined somewhere. use this syntax to define it
 *  template <class Value> typename Util::CParameter<Value>::container Util::CParameter<Value>::stacks;
 */
template <class Value>
class CParameter{
public:
    /* push a new value on the stack */
    CParameter(CParameter & parent, const Value & what):
    stack(parent.stack),
    items(0){
        push(what);
    }

    CParameter(CParameter & parent):
    stack(parent.stack),
    items(0){
    }

    CParameter():
    items(0){
        stack = new std::vector<Value>();
    }

    /* pop last value */
    virtual ~CParameter(){
        for (int i = 0; i < items; i++){
            if (stack->size() > 0){
                stack->pop_back();
            }
        }
    }

    void push(const Value & what){
        items += 1;
        stack->push_back(what);
    }

    /* get the current value */
    Value current(){
        if (stack->size() > 0){
            return stack->back();
        }
        return Value();
    }

    CReferenceCount<std::vector<Value> > stack;

protected:
    /* number of things pushed onto the stack by this object. note this is
     * not the number of items on the stack because if there are multiple
     * parameter objects then each one could have pushed 1 object on. thus
     * the stack will have 2 things in it but each parameter will have an
     * 'items' count of 1.
     */
    int items;
};

}


#endif
