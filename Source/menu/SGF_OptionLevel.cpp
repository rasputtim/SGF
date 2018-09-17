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
#include "menu/SGF_OptionLevel.h"
#include "util/SGF_Debug.h"
#include "menu/SGF_MenuGlobal.h"
#include "menu/SGF_MenuV2.h"
#include "util/SGF_Util.h"
#include <string>
#include "exceptions/all.h"
using namespace std;
namespace SGF {

class CLoadException;
namespace Menu {
COptionLevel::COptionLevel(const Gui::CContextBox & parent,const Token *token, int * set, int value) throw( CLoadException ):
CMenuOption(parent,token),
set(set),
value(value){
  // Nothing
}

COptionLevel::~COptionLevel(){
}

void COptionLevel::logic(){
}

/* redo this to not use global state 
void COptionLevel::run(bool &endGame){
	endGame = true;
    *set = value;
}*/

void COptionLevel::run(const Menu::CContext & context){
    *set = value;
    throw Menu::CMenuException(__FILE__, __LINE__);
}

}
} //end SGF