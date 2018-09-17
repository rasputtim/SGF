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
#include "graphics/all.h"
#include "menu/SGF_OptionDummy.h"
#include "util/SGF_Debug.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuV2.h"
#include "SGF_Global.h"
//#include "init.h"

using namespace std;
namespace SGF {

namespace Menu {
COptionDummy::COptionDummy(const Gui::CContextBox & parent,const Token *token) throw( CLoadException ):
CMenuOption(parent, token){
    if ( *token != "dummy" ){
        throw CLoadException(__FILE__, __LINE__,"Not dummy option");
    }

    readName(token);

    if (getText().empty()){
        this->setText("Dummy");
    }
}

COptionDummy::COptionDummy( const Gui::CContextBox & parent,const string &name ) throw( CLoadException ):
CMenuOption(parent,0){
    if (name.empty()){
	throw CLoadException(__FILE__, __LINE__,"No name given to dummy");
    }
    this->setText(name);
}

COptionDummy::~COptionDummy(){
}

void COptionDummy::logic(){
}

void COptionDummy::run(const Menu::CContext & context){
}
}
} //end sGF