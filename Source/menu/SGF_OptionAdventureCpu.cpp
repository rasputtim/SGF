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
#include "menu/SGF_OptionAdventureCpu.h"
#include "util/SGF_Debug.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuGlobal.h"
#include "SGF_Global.h"

#include "level/SGF_LevelUtils.h"
#include "util/SGF_Util.h"

/* todo: replace keyboard with input-map */

#include <sstream>

using namespace std;
namespace SGF {

namespace Menu {
COptionAdventureCpu::COptionAdventureCpu(const Gui::CContextBox & parent,const Token *token) throw( CLoadException ):
CMenuOption(parent, token)
{
    if (*token != "adventure-cpu"){
        throw CLoadException(__FILE__, __LINE__,"Not an adventure");
    }

    readName(token);
}

COptionAdventureCpu::~COptionAdventureCpu(){
}

void COptionAdventureCpu::logic(){
}

void COptionAdventureCpu::run(const Menu::CContext & context){
 
}
}
} //end SGF