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
#ifndef _S_G_E_ast_collectable_h_
#define _S_G_E_ast_collectable_h_

#include <list>
#include <iostream>
#include "all.h"
using namespace std;
namespace SGF{

#define constructor(type, str_val, element_val, section_list_val, number_val) \
    CCollectable(const type * x):\
        str(str_val),\
        element(element_val),\
        section_list(section_list_val),\
        number(number_val),\
        _destroy(false){}


namespace Ast{

class  SGE_API CCollectable{
public:

    constructor(string,        x, 0, 0, 0)
    constructor(CElement,      0, x, 0, 0)
    constructor(list<CSection*>,0, 0, x, 0)
    constructor(double,         0, 0, 0, x)

    /* is this needed? */
    CCollectable(const CCollectable & copy):
        str(copy.str),
        element(copy.element),
        section_list(copy.section_list),
        number(copy.number),
        _destroy(copy._destroy){
    }

    void destroy(){
        _destroy = true;
    }

    const void * pointer(){
        if (str){ return str; }
        if (element){ return element; }
        if (section_list){ return section_list; }
        if (number){ return number; }
        return 0;
    }

    void mark(map<const void *, bool> & marks) const {
        if (str){ marks[str] = true; }
        if (element){ element->mark(marks); }
        if (section_list){
            marks[section_list] = true;
            for (list<CSection*>::const_iterator it = section_list->begin(); it != section_list->end(); it++){
                CSection * section = *it;
                section->mark(marks);
            }
        }
        if (number){ marks[number] = true; }
    }

    virtual ~CCollectable(){
        if (_destroy){
            // cout << "Collect " << pointer() << endl;
            delete str;
            delete element;
            if (section_list != 0){
                for (list<CSection*>::const_iterator it = section_list->begin(); it != section_list->end(); it++){
                    delete (*it);
                }
            }
            delete section_list;
            delete number;
        }
    }

protected:
    const string * str;
    const CElement * element;
    const list<CSection*>* section_list;
    const double * number;
    bool _destroy;
};

} //end AST

#undef constructor
} //end SGF
#endif
