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
#ifndef _SGF_menu_globals_h
#define _SGF_menu_globals_h

#include <iostream>
#include <string>
#include "../SGF_Config.h"
#include "../level/SGF_LevelUtils.h"
#include "../exceptions/all.h"


using namespace std;
namespace SGF {

class CSound;
class CStackString;
namespace Menu { 
	
class CMenu_v1; 


class  SGE_API CMenuGlobals{
    public:
	/*! ctor dtor */
	CMenuGlobals();
	virtual ~CMenuGlobals();
	
	/*! set the music */
	static void setMusic(const string &file);
	
	/*! set the select sound */
	static void setSelectSound(const string &file);
	
	/*! get current select sound */
	static const string currentSelectSound();
	
	/*! play current select sound */
	static void playSelectSound() throw(CLoadException);
	
	/*! pop select sound */
	static void popSelectSound();
	
	/*! game speed */
	static double getGameSpeed();
	
	/*! set speed */
	static void setGameSpeed(double s);
	
	/*! invincible */
	static bool getInvincible();
	
	/*! set invincible */
	static void setInvincible(bool i);
	
	/*! game fullscreen */
	static bool getFullscreen();
	
	/*! set speed */
	static void setFullscreen(bool f);
	
	/*! game lives */
	static int getLives();
	
	/*! set lives */
	static void setLives(int l);

	static int getNpcBuddies();
	static void setNpcBuddies( int i );
	
        /*
	inline static void setLevel(const string &l){ level = l; }
	inline static const string &getLevel(){ return level; }
        */
	
	static Level::CLevelInfo doLevelMenu(const string dir, Menu::CMenu_v1 *parent) throw(CLoadException);

        /* free for all lets players attack each other in network mode.
         * cooperative means they are on the same team.
         */
        static bool freeForAll();
        static bool cooperative();
        static void setFreeForAll();
        static void setCooperative();
	
private:
	
	static CStackString selectSound;
	
	// static string level;
};
}
} //end SGF
#endif
