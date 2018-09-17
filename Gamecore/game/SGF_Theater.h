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
#ifndef _sgf_Theater_h
#define _sgf_Theater_h

#include "../objects/all.h"

class CObject;
class CPlayer;
class CEnemy;



class CScene;
class CBlock;

class CBaseObject;

#include <vector>
#include <deque>
#include <map>
#include <string>
#include "../SGF_Config.h"
#include "../exceptions/all.h"
#include "../util/SGF_Pointer.h"
#include "../objects/all.h"
#include "../network/SGF_Network.h"

using namespace std;
namespace SGF {
/**
 * \class CTheater
 *
 * \ingroup SGF_Game
 *
 * \brief Theater é onde a ação do jogo ocorre. Controla informações sobre o jogo , timing etc
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CTheater{
public:
	CTheater():name(""){};
	virtual ~CTheater(){};

	INLINE const std::string &getName() const {
        return name;
    }
	INLINE const void setStageName(const std::string Name) {
        name=Name;
    }
	INLINE bool getDebug() { return my_stateData.debug;}
	INLINE void setDebug(bool debug) { my_stateData.debug= debug;}
       //! Set match
    virtual void setMatchOver(bool over){
        this->my_stateData.gameOver = over;
    }

    //! Check match
    virtual bool isMatchOver() const {
        return this->my_stateData.gameOver;
    }

	virtual bool replayEnabled() const {
    return this->my_stateData.replay;
	}

	virtual void setReplay(bool what){
    this->my_stateData.replay = what;
	}

	virtual bool isLoaded() {
		return  this->my_stateData.loaded;
	}
	virtual void setLoaded(){
		this->my_stateData.loaded = true;
	}
	virtual void unsetLoaded(){
		this->my_stateData.loaded = false;
	}
struct TheaterStateData{

	TheaterStateData():
	loaded(false),
	gameOver(false),
	replay(false),
	debugMode(false),
	debug(false),
    number_of_players(1)
	{}

	 TheaterStateData(const TheaterStateData & copy):
            SGFCpConstr(loaded)
			SGFCpConstr(gameOver)
			SGFCpConstr(replay)
			SGFCpConstr(debugMode)
			SGFCpConstr(debug)
			SGFCpConstrLast(number_of_players)
			{}

	 bool operator==(const TheaterStateData & him) const {
            return  SGFequalOper(loaded) &&
					SGFequalOper(gameOver) &&
					SGFequalOper(replay) &&
					SGFequalOper(debugMode) &&
					SGFequalOper(debug) &&
					SGFequalOper(number_of_players);
        }

	 bool operator!=(const TheaterStateData & him) const {
        return !(*this == him);
    }
		TheaterStateData & operator=( const TheaterStateData &copy ){
		// Check for self assignment!
		if (this == &copy)      // Same object?
			return *this;
			SGFCpField(loaded)
			SGFCpField(gameOver)
			SGFCpField(replay)
			SGFCpField(debugMode)
			SGFCpField(debug)
			SGFCpField(number_of_players)

			return *this;
	}
	// true if stage data has been loaded
    bool loaded;
	// true if the game is over
	bool gameOver;
	// true if doing in-game replay */
    bool replay;
	 // Debug enabled?
    bool debugMode;
	bool debug;
    int number_of_players;

};

		void addObject(CBaseObject * o);
		CBaseObject * findObject(CObjectId id);
        // serialized actions the world can take. mostly for use with networking
         // WARNING: changing these values (like moving them around) will break
         // backwards compatibility.
         // If a message with one of these types is sent then the message
         // id *must* be set to 0, which indicates a server message.

        enum{
            // sanity check, no one should ever pass `NOTHING' around
            NOTHING = 0,
            // create a new character
            CREATE_CHARACTER,
            // create a cat
            CREATE_CAT,
            // create a bang effect
            CREATE_BANG,
            // create an item
            CREATE_ITEM,
            // create a projectile
            CREATE_PROJECTILE,
            // advance a block in the game
            NEXT_BLOCK,
            // the level is finished
            FINISH,
            // remove object from world
            REMOVE,
            // set id of the player
            SET_ID,
            // acknowledge a message
            OK,
            // load a new level
            LOAD_LEVEL,
            // remove object and delete it
            DELETE_OBJ,
            // grab a character
            GRAB,
            // throw a character
            THROWN,
            // dummy message (different from NOTHING)
            IGNORE_MESSAGE,
            // entire game is over, time to go outside
            GAME_OVER,
            // create a player. used to differentiate between players and
             //regular characters

            IS_PLAYER,
            // pause the game
            PAUSE,
            // unpause the game
            UNPAUSE,
            // request a ping
            PING_REQUEST,
            // reply to a ping
            PING_REPLY,
            // client has quit
            QUIT,
            // chat message
            CHAT,
            // client name and stuff
            CLIENT_INFO,
        };

		CObjectList objects;

private:

	TheaterStateData my_stateData;
    string name;
};//end class
} // end SGF
#endif
