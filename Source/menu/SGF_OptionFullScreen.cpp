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
#include "menu/SGF_OptionFullscreen.h"
#include "util/SGF_Debug.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuV2.h"
#include "menu/SGF_MenuGlobal.h"
#include "SGF_Global.h"
//#include "init.h"
#include <sstream>


using namespace std;
namespace SGF {

namespace Menu {
COptionFullscreen::COptionFullscreen(const Gui::CContextBox & parent,const Token *token) throw( CLoadException ):
CMenuOption(parent,token),
lblue(255),
lgreen(255),
rblue(255),
rgreen(255){
	setRunnable(false);
	
	if ( *token != "fullscreen" )
		throw CLoadException(__FILE__, __LINE__,"Not fullscreen option");

        readName(token);
}

COptionFullscreen::~COptionFullscreen()
{
	// Nothing
}
    
string COptionFullscreen::getText(){
    ostringstream out;
    out << CMenuOption::getText() << ": " << (CMenuGlobals::getFullscreen() ? "Yes" : "No");
    return out.str();
}

void COptionFullscreen::logic(){
	if(lblue < 255)lblue+=5;
	if(rblue < 255)rblue+=5;
	if(lgreen < 255)lgreen+=5;
	if(rgreen < 255)rgreen+=5;
	
//s	setLeftAdjustColor(Colors::makeColor( 255, lblue, lgreen ));
//s	setRightAdjustColor(Colors::makeColor( 255, rblue, rgreen ));
}

bool COptionFullscreen::leftKey()
{
	CMenuGlobals::setFullscreen(!CMenuGlobals::getFullscreen());
	lblue = lgreen = 0;
	CMenuGlobals::getFullscreen() ? CBitmap::_my_state->Screen[0]->SetFullScreen() : CBitmap::_my_state->Screen[0]->SetWindowed();

	//int gfx = (CMenuGlobals::getFullscreen() ? Global::FULLSCREEN : Global::WINDOWED);
	//CBitmap::setGraphicsMode( gfx, SCREEN_W,SCREEN_H );
	return true;
}
bool COptionFullscreen::rightKey()
{
	CMenuGlobals::setFullscreen(!CMenuGlobals::getFullscreen());
	rblue = rgreen = 0;
	CMenuGlobals::getFullscreen() ? CBitmap::_my_state->Screen[0]->SetFullScreen() : CBitmap::_my_state->Screen[0]->SetWindowed();
	//CSDLManager::GetInstance()->state->window_flags |= SDL_WINDOW_FULLSCREEN;
	//SDL_SetWindowFullscreen(CBitmap::Screen[0]->GetWindow(),1);

	//int teste= CBitmap::setGraphicsMode( CSDLManager::GetInstance()->state,0 );
	//CBitmap::setGraphicsMode( gfx, SCREEN_W,SCREEN_H );
	return true;
}

static void changeScreenMode(){
    CMenuGlobals::setFullscreen(!CMenuGlobals::getFullscreen());
	//rblue = rgreen = 0;
	CMenuGlobals::getFullscreen() ? CBitmap::_my_state->Screen[0]->SetFullScreen() : CBitmap::_my_state->Screen[0]->SetWindowed();
	
	//CConfiguration::fullScreen.setBool(!CConfiguration::fullScreen.getBool());
    //int gfx = (CConfiguration::fullScreen.getBool() ? Global::FULLSCREEN : Global::WINDOWED);
    //CBitmap::setGraphicsMode(gfx, Global::getScreenWidth(), Global::getScreenHeight());
}

void COptionFullscreen::run(const Menu::CContext & context){
    changeScreenMode();
}
}
} //end SGF