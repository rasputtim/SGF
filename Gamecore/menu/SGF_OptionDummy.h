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
#ifndef _option_dummy_h
#define _option_dummy_h

#include "SGF_MenuOption.h"
#include "SGF_MenuV2.h"
#include "../SGF_Config.h"
using namespace std;
namespace SGF {

class Token;
namespace Menu {
	class CMenuOption;
/*! Dummy option, to allow place fillers in menus */
class  SGE_API COptionDummy : public CMenuOption{
public:
	COptionDummy(const Gui::CContextBox & parent, const Token *token ) throw( CLoadException );
	COptionDummy(const Gui::CContextBox & parent, const string &name ) throw( CLoadException );

	// Do logic before run part
	virtual void logic();

	// Finally it has been selected, this is what shall run 
	// endGame will be set true if it is a terminating option
	//virtual void run(bool &endGame);
	virtual void run(const Menu::CContext &);
	virtual void load(const Token *token)throw( CLoadException ) {};
	virtual ~COptionDummy();
};
}
} //end SGF
#endif
