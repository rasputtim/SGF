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
#include "menu/SGF_OptionNetworkHost.h"
//#include "../input/keyboard.h"
#include "exceptions/all.h"
#include "util/SGF_Debug.h"
#include "util/SGF_Util.h"

#include "network/SGF_NetServer.h"
#include "SGF_Global.h"

#include <iostream>

using namespace std;
namespace SGF {



#ifdef HAVE_NETWORKING
namespace Menu {
COptionNetworkHost::COptionNetworkHost(const Gui::CContextBox & parent, const Token *token) throw( CLoadException ):
CMenuOption(parent,token){
    if ( *token != "network-host" ){
        throw CLoadException(__FILE__, __LINE__,"Not a network-host");
    }

    readName(token);
}

COptionNetworkHost::~COptionNetworkHost(){
	// Nothing
}

void COptionNetworkHost::logic(){
}


void COptionNetworkHost::run(const Menu::CContext & context){
    // Keyboard key;
    try{
        Network::networkServer();
    } catch (const Exception::Return &e){
    }
    /* FIXME */
    /*
    key.clear();
    key.poll();
    key.wait();
    */
    throw Menu::CReload(__FILE__, __LINE__);
    // throw Exception::Return(__FILE__, __LINE__);
}
}
} //end SGF
#endif