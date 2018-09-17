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
#ifndef _sgf_world_h
#define _sgf_world_h


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
class CBitmap;
namespace Script{
    class CEngine;
}


class CBaseObject;


/**
 * \class CWorld
 *
 * \ingroup SGF_Game
 *
 * \brief Controla informações sobre o jogo Theater, Objects, Resources, etc
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class CBitmap;
namespace Script{
    class CEngine;
}


class CBaseObject;



class  SGE_API CWorld{
public:
	CWorld(){};
	virtual ~CWorld(){};
/*
	virtual void Quake( int q );

	inline int getQuake() const {
		return quake_time;
	}

	virtual void act() = 0;
	virtual void draw( CBitmap * work ) = 0;
	virtual void addObject( CBaseObject * o );

	virtual bool isFinished() const = 0;

	virtual void reloadLevel() = 0;

    //s virtual Script::CEngine * getEngine() const = 0;

	// upper left hand corner of the screen 
	//virtual int getX() = 0;
	//virtual int getY() = 0;

    virtual double ticks(const double in) const;



	virtual inline  const vector< CBaseObject* > & getObjects() const {
        return objects;
    }

    // set to paused 
    virtual void pause() = 0;
    // set to unpaused 
    // virtual void unpause() = 0;
    // set to paused if unpaused, or vice-versa 
    //virtual void changePause() = 0;
    virtual bool isPaused() = 0;

    // an object has notified us that it is dying 
    virtual void dyingObject(const CObject & obj);
    virtual void dyingObject(const CPlayer & obj);

    // bleh.. 
    //virtual void addEnemy(::CEnemy * obj) = 0;

    virtual  CBaseObject * findObject(int id);

//	virtual int getMaximumZ()=0 ;
//	virtual int getMinimumZ()=0;

//	virtual void drawMiniMaps( bool b )=0;
//	virtual bool shouldDrawMiniMaps()=0;

	virtual void killAllHumans( CObject * player ){};

	virtual void addMessage(Network::Message m, Network::Socket from = 0, Network::Socket to = 0) = 0;
	//virtual Network::Message createBangMessage( int x, int y, int z ) = 0;

protected:
	int quake_time;
	vector< CBaseObject *> objects;

public:
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
            /* remove object and delete it 
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
		*/
};
} // end SGF
#endif
