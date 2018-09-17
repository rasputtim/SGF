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
#ifndef __option_change_mod_h
#define __option_change_mod_h

#include "../SGF_Config.h"
#include "SGF_MenuOption.h"
#include "SGF_MenuV2.h"
#include "../util/SGF_Token.h"
#include "../exceptions/all.h"


using namespace std;
namespace SGF {

class Token;
namespace Menu {
	class CMenuOption;
struct ModType{
    enum Kind{
        Mugen,
        Openbor
    };

    ModType(const Filesystem::CAbsolutePath & path, Kind type):
    path(path),
    type(type){
    }

    Filesystem::CAbsolutePath path;
    Kind type;
};

/* Change game mod */
class  SGE_API COptionChangeMod: public CMenuOption {
public:
    COptionChangeMod(const Gui::CContextBox & parent,const Token *token)throw (CLoadException);
    virtual ~COptionChangeMod();
    virtual void logic();
   // virtual void run(bool &endGame)throw (CLoadException);
	virtual void run(const Menu::CContext &);
	virtual void load(const Token *token)throw( CLoadException ) {};
};
}
} //end SGF
#endif

