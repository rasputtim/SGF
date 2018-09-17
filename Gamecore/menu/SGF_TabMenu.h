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
#ifndef _S_G_F_TABMENU_h
#define _S_G_F_TABMENU_h
#include "../SGF_Config.h"
#include "../gui/SGF_Box.h"
using namespace std;
namespace SGF {

class CTTFFont;
class CBitmap;
class CMenuOption;
class Token;
class CMenuAnimation;
namespace Menu{
//class CMenu_v1;
}


// Cria um buffer para ir de uma cor para outra
class  SGE_API CColorBuffer{
    public:
	CColorBuffer( Colors::ColorDefinition color1,  Colors::ColorDefinition color2);
	virtual ~CColorBuffer();

    static const int maxColors = 100;
	 Colors::ColorDefinition colors[maxColors];
	int index;
	bool forward;
	
	 Colors::ColorDefinition update();
	
	void reset();
};
} //end SGF


#endif