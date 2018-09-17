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
#include <sstream>
#include <stdio.h>
#include "graphics/all.h"
#include "menu/SGF_OptionSpeed.h"
#include "util/SGF_Token.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuV2.h"
//#include "SGF_MenuGlobal.h"
#include "SGF_Global.h"
using namespace std;
namespace SGF {

namespace Menu {
COptionSpeed::COptionSpeed(const Gui::CContextBox & parent,const Token *token)throw( CLoadException ): 
CMenuOption(parent,token), 
	name(""), 
	lblue(255), 
	lgreen(255), 
	rblue(255), 
	rgreen(255)
{
    setRunnable(false);

    if ( *token != "speed" )
        throw CLoadException(__FILE__, __LINE__,"Not speed option");

    readName(token);
}

COptionSpeed::~COptionSpeed(){
	// Nothing
}


string COptionSpeed::getText(){
    ostringstream out;
    //todo resolver problema do queue na menu_globals
	//out << CMenuOption::getText() << ": " << CMenuGlobals::getGameSpeed();
    return out.str();
}

void COptionSpeed::logic(){
    /*
	//ostringstream temp;
	char temp[255];
	sprintf( temp, "%s: %0.2f", name.c_str(), CMenuGlobals::getGameSpeed() );
	setText(string(temp));
        */
	
	if(lblue < 255)lblue+=5;
	if(rblue < 255)rblue+=5;
	if(lgreen < 255)lgreen+=5;
	if(rgreen < 255)rgreen+=5;
	
//s	setLeftAdjustColor(Colors::makeColor( 255, lblue, lgreen ));
//s	setRightAdjustColor(Colors::makeColor( 255, rblue, rgreen ));
}
void COptionSpeed::run(const Menu::CContext & context){
}
bool COptionSpeed::leftKey()
{
	//todo resolver problema do queue na menu_globals
	//CMenuGlobals::setGameSpeed(CMenuGlobals::getGameSpeed() - 0.05);
	//if( CMenuGlobals::getGameSpeed() < 0.1 )CMenuGlobals::setGameSpeed(0.1);
	
	lblue = lgreen = 0;
	return false;
}
bool COptionSpeed::rightKey()
{
	//todo resolver problema do queue na menu_globals
	//CMenuGlobals::setGameSpeed(CMenuGlobals::getGameSpeed() + 0.05);
	
	rblue = rgreen = 0;
	return false;
}
}
} //end SGF