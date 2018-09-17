
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

#ifndef _SGF_Keyboard_MAPPING_h
#define _SGF_Keyboard_MAPPING_h

#include "SGF_Keyboard.h"
#include <vector>

using namespace std;
namespace SGF{

class CKeyboard;


/**
 * \class CKeyMapping
 *
 * \ingroup SGF_Input
 *
 * \brief Mapeamento de Botões do teclado do provedor (SDL) para SGF
 *
 * \note para permitir futuramente usar outros gerenciadores d teclado diferentes do SDL
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class CKeyMapping{
public:
    CKeyMapping(){
    }

    virtual ~CKeyMapping(){
    }

    virtual int toNative(int key) = 0;
    virtual int fromNative(int key) = 0;
   // virtual CKeyboard::Key toKey(int key) = 0;

};

class SDLKeyMapping: public CKeyMapping {
public:
    int toNative(int key){
        return key;
    }

    int fromNative(int key){
        return key;
    }

    static CKeyboard::Key toKey(int SDLkeyCode);

};
} //end SGF
#endif
