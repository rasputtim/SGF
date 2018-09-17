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

#ifndef _S_G_F_optionfactory_h
#define _S_G_F_optionfactory_h

#include "../SGF_Config.h"
#include "../exceptions/all.h"
#include "../gui/SGF_ContextBox.h"

#include <map>
using namespace std;
namespace SGF {

class Token;


namespace Menu {




class CMenuOption;
class  SGE_API COptionFactory{
public:

struct registeredOption{
        registeredOption():
        tokenName(""),
		enabled(false),
		option(NULL){
        };

        string tokenName;
        bool enabled;
       CMenuOption *option;
    };

map<string,const registeredOption*> optionsMap;
COptionFactory();
virtual ~COptionFactory();
CMenuOption * getOption(const Gui::CContextBox & parent,const Token *token) const;
void registerOption(CMenuOption * option,const string & token);

//registeredOption regOption;
//optionsMapType optionsMap;
};

}
} //end SGF
#endif

