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
#include "menu/SGF_OptionAdventure.h"
#include "menu/SGF_MenuGlobal.h"

/* todo: replace keyboard with input-map */

#include "util/SGF_Debug.h"
#include "util/SGF_Util.h"
#include "level/SGF_LevelUtils.h"
//#include "../objects/player.h"
//#include "../gameEngine.h"
#include "SGF_Global.h"

//#include "menu/SGF_MenuV1.h"

#include <iostream>
#include "exceptions/all.h"
using namespace std;
namespace SGF {

class CLoadException;

namespace Menu {
COptionAdventure::COptionAdventure(const Gui::CContextBox & parent,const Token *token) throw( CLoadException ):
CMenuOption(parent, token)
{
    if ( *token != "adventure" ){
        throw CLoadException(__FILE__, __LINE__,"Not an adventure");
    }

    readName(token);
}

COptionAdventure::~COptionAdventure(){
	// Nothing
}

void COptionAdventure::logic(){
}
#if 0
void COptionAdventure::run(bool &endGame){
    CKeyboard key;
    CObject * player = NULL;
    try{
        //string level = Game::selectLevelSet( Util::getDataPath() + "/levels" );
		Level::CLevelInfo info = CMenuGlobals::doLevelMenu("/levels",(Menu::CMenu_v1*) parent);

        /*
        if (level.empty()){
            Debug::debug(1,__FUNCTION__) << "*bug* Level name is empty?" << endl;
            throw an error or something
            return;
        */
        key.wait();
        /* retirado por enquanto - Rasputtim - até implementar a classe Game completa
        player = CGame::selectPlayer(CMenuGlobals::getInvincible(), "Pick a player", info);
        player->setObjectId(-1);
        ((CPlayer *)player)->setLives( CMenuGlobals::getLives() );
        vector< CObject * > players;
        players.push_back( player );
        CGame::realGame(players, info); */
    } catch ( const CLoadException & le ){
//        Debug::debug( 0 ) << "Error while loading: " << le.getReason() << endl;
    } catch ( const Exception::Return & r ){
        /* Game::selectPlayer can throw Exception::Return, he will wait
         * for the keypress to be released, so we don't have to do it
         */
        // key.wait();
    }

    /* player will be null if an exception occurred before selectPlayer was called */
    if ( player != NULL ){
        delete player;
    }
}
#endif
void COptionAdventure::run(const Menu::CContext & context){
   

}
}
}//end SGF