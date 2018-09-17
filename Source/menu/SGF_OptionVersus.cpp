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
#include "menu/SGF_OptionVersus.h"
//#include "../game.h"
#include "SGF_Global.h"
#include "util/SGF_Token.h"
//#include "../input/keyboard.h"
#include "exceptions/all.h"
#include "level/SGF_LevelUtils.h"
//#include "../objects/versus_player.h"
//#include "../objects/versus_enemy.h"

using namespace std;
namespace SGF {

namespace Menu {
COptionVersus::COptionVersus( const Gui::CContextBox & parent,const Token *token ) throw( CLoadException ):
CMenuOption(parent, token), human(false){
    if ( *token != "versus" ){
        throw CLoadException(__FILE__, __LINE__,"Not versus");
    }

    readName(token);

      TokenView view = token->view();
      while ( view.hasMore()){

        try{
            const Token * tok;
            view >> tok;
            if( *tok == "cpu" ) {
                human = false;
            } else if( *tok == "human" ) {
                human = true;
            } else {
                Debug::debug(Debug::menu,__FUNCTION__) <<"Unhandled menu attribute: "<<endl;
                //if (Debug::getDebug() >= 3){
                //    tok->print(" ");
                //}
            }
        } catch ( const CTokenException & ex ) {
            // delete current;
            string m( "COptionVersus::COptionVersus - Menu parse error: " );
            m += ex.getTrace();
            throw CLoadException(__FILE__, __LINE__, m);
        } catch ( const CLoadException & ex ) {
            // delete current;
            throw ex;
        }
    }
}

COptionVersus::~COptionVersus(){
}

void COptionVersus::logic(){
}
void COptionVersus::run(const Menu::CContext & context){
}
#if 0
void COptionVersus::run(bool &endGame){

	/*
	CKeyboard key;
	CObject * player = NULL;
	CObject * enemy = NULL;
	try{
		if ( human ){
			vector<CObject *>temp = Game::versusSelect( false );
			player = temp[0];
			enemy = temp[1];
			if ( ! player || !enemy ){
				throw LoadException(__FILE__, __LINE__,"Null player");
			}

			//player = selectPlayer( false );
			//enemy = selectPlayer( false );
			enemy->setAlliance( ALLIANCE_ENEMY );

			for ( int i = 0; i < 3; i += 1 ){
				VersusPlayer en(*(CPlayer *) enemy );
				VersusPlayer pl(*(CPlayer *) player );
                                en.setConfig(1);
                                pl.setConfig(0);
				Game::playVersusMode( &pl, &en, i + 1 );
			}
		} else {
                    Level::CLevelInfo info;
			player = Game::selectPlayer( false, "Pick your player", info);
			enemy = Game::selectPlayer( false, "Pick enemy", info);
			enemy->setAlliance( ALLIANCE_ENEMY );

			for ( int i = 0; i < 3; i += 1 ){
				VersusEnemy en( *(Player *) enemy );
				VersusPlayer pl( *(Player *) player );
                                pl.setConfig(0);
				Game::playVersusMode( &pl, &en, i + 1 );
			}
		}
		key.wait();
	} catch ( const LoadException & le ){
		Debug::debug( 0 ) << "COptionVersus::COptionVersus - Could not load player: " << le.getReason() << endl;
	} catch ( const Exception::Return & r ){
		key.wait();
	}

	if ( player != NULL ){
		delete player;
	}
	if ( enemy != NULL ){
		delete enemy;
	} */
}
#endif
}
}//end SGF
