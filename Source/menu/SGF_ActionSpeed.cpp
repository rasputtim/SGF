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
#include "menu/SGF_ActionSpeed.h"
#include "menu/SGF_MenuGlobal.h"
#include "util/SGF_Token.h"
using namespace std;
namespace SGF {

CActionSpeed::CActionSpeed(const Token *token): speed(0.1)
{
	Debug::debug(Debug::menu,__FUNCTION__) << "CONSTRUCTOR // CActionSpeed //" << endl;
	token->view() >> speed;
}

CActionSpeed::~CActionSpeed()
{
}

void CActionSpeed::act()
{
	if(speed < 0.1)speed = 0.1;
	//CMenuGlobals::setGameSpeed(speed);
}

}//end SGF