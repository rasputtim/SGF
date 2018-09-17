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
#include "menu/SGF_OptionInvencible.h"
#include "util/SGF_Debug.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuV2.h"
#include "menu/SGF_MenuGlobal.h"
#include "SGF_Global.h"
#include <sstream>

using namespace std;
namespace SGF {

namespace Menu {
COptionInvincible::COptionInvincible(const Gui::CContextBox & parent,const Token *token) throw( CLoadException ):
CMenuOption(parent,token),
lblue(255),
lgreen(255),
rblue(255),
rgreen(255){
	setRunnable(false);
	
	if ( *token != "invincible" )
		throw CLoadException(__FILE__, __LINE__,"Not invincible option");

        readName(token);
}

COptionInvincible::~COptionInvincible()
{
	// Nothing
}
                
string COptionInvincible::getText(){
    ostringstream out;
    out << CMenuOption::getText() << ": " << (CMenuGlobals::getInvincible() ? "Yes" : "No");
    return out.str();
}

void COptionInvincible::logic()
{
	
	if(lblue < 255)lblue+=5;
	if(rblue < 255)rblue+=5;
	if(lgreen < 255)lgreen+=5;
	if(rgreen < 255)rgreen+=5;
	
//s	setLeftAdjustColor(Colors::makeColor( 255, lblue, lgreen ));
//s	setRightAdjustColor(Colors::makeColor( 255, rblue, rgreen ));
}


void COptionInvincible::run(const Menu::CContext & context){
}
bool COptionInvincible::leftKey()
{
	CMenuGlobals::setInvincible(!CMenuGlobals::getInvincible());
	lblue = lgreen = 0;
	return true;
}
bool COptionInvincible::rightKey()
{
	CMenuGlobals::setInvincible(!CMenuGlobals::getInvincible());
	rblue = rgreen = 0;
	return true;
}

}
} //end SGF