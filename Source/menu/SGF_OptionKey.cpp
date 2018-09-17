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
#include "util/SGF_FontSystem.h"

#include "menu/SGF_OptionKey.h"
#include "util/SGF_Debug.h"
#include "configuration/SGF_Configuration.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuV2.h"
#include "SGF_Global.h"
//#include "../input/keyboard.h"
#include "util/SGF_Util.h"

#include "gui/SGF_Box.h"

using namespace std;
namespace SGF {

namespace Menu {
static COptionKey::keyType convertToKey(const string &k)
{
	string temp = k;
	for(unsigned int i=0;i<temp.length();i++)
	{
		temp[i] = tolower(temp[i]);
	}
	if(temp == "up")return COptionKey::_up;
	if(temp == "down")return COptionKey::down;
	if(temp == "left")return COptionKey::left;
	if(temp == "right")return COptionKey::right;
	if(temp == "jump")return COptionKey::jump;
	if(temp == "attack1")return COptionKey::attack1;
	if(temp == "attack2")return COptionKey::attack2;
	if(temp == "attack3")return COptionKey::attack3;
	if(temp == "attack4")return COptionKey::attack4;
	if(temp == "attack5")return COptionKey::attack5;
	if(temp == "attack6")return COptionKey::attack6;

	return COptionKey::invalidkey;
}

static int getKey(int player, COptionKey::keyType k)
{
	switch(k)
	{
		case COptionKey::_up:
			return CConfiguration::getConfig( player )->getKey("key-up");
			break;
		case COptionKey::down:
			return CConfiguration::getConfig( player )->getKey("key-down");
			break;
		case COptionKey::left:
			return CConfiguration::getConfig( player )->getKey("key-left");
			break;
		case COptionKey::right:
			return CConfiguration::getConfig( player )->getKey("jey-right");
			break;
		case COptionKey::jump:
			return CConfiguration::getConfig( player )->getKey("key-jump");
			break;
		case COptionKey::attack1:
			return CConfiguration::getConfig( player )->getKey("key-action1");
			break;
		case COptionKey::attack2:
			return CConfiguration::getConfig( player )->getKey("key-action2");
			break;
		case COptionKey::attack3:
			return CConfiguration::getConfig( player )->getKey("key-action3");
			break;
		case COptionKey::attack4:
		case COptionKey::attack5:
		case COptionKey::attack6:
		default:
			break;
	}

	return 0;
}

static void setKey(int player, COptionKey::keyType k, CKeyboard::Key key)
{
	switch(k)
	{
		case COptionKey::_up:
			CConfiguration::getConfig( player )->setKey("key-up", key );
			break;
		case COptionKey::down:
			CConfiguration::getConfig( player )->setKey("key-down", key );
			break;
		case COptionKey::left:
			CConfiguration::getConfig( player )->setKey("key-left", key );
			break;
		case COptionKey::right:
			CConfiguration::getConfig( player )->setKey("key-right", key );
			break;
		case COptionKey::jump:
			CConfiguration::getConfig( player )->setKey("key-jump", key );
			break;
		case COptionKey::attack1:
			CConfiguration::getConfig( player )->setKey("key-action1", key );
			break;
		case COptionKey::attack2:
			CConfiguration::getConfig( player )->setKey("key-action2", key );
			break;
		case COptionKey::attack3:
			CConfiguration::getConfig( player )->setKey("key-action3", key );
			break;
		case COptionKey::attack4:
		case COptionKey::attack5:
		case COptionKey::attack6:
		default:
			break;
	}
}

static CKeyboard::Key readKey( CKeyboard & key ){
	key.wait();
	key.clear();
	int k = key.readKey();
	key.wait();
	return CConfiguration::intToKeyboard(k);
}

COptionKey::COptionKey(const Gui::CContextBox & parent,const Token *token) throw( CLoadException ):
CMenuOption(parent,token), name(""), player(-1), type(invalidkey), keyCode(CKeyboard::Invalid)
{
	if ( *token != "key" )
		throw CLoadException(__FILE__, __LINE__,"Not key option");

	 TokenView view = token->view();
      while ( view.hasMore()){
	  	try
		{
			const Token * tok;
			view >> tok;
			if ( *tok == "name" )
			{
				tok->view() >> name;
			}
			else if ( *tok == "player" )
			{
				tok->view() >> player;
			}
			else if ( *tok == "type" )
			{
				string temp;
				tok->view() >> temp;
				type = convertToKey(temp);
			}
			else
			{
				Debug::debug( 3 ) <<"Unhandled menu attribute: "<<endl;
				tok->print(" ");
			}
		}
		catch ( const CTokenException & ex )
		{
			// delete current;
			string m( "Menu parse error: " );
			m += ex.getTrace();
			throw CLoadException(__FILE__, __LINE__, m);
		}
		catch ( const CLoadException & ex )
		{
			// delete current;
			throw ex;
		}
	}

	if(name.empty())throw CLoadException(__FILE__, __LINE__,"No name set, this option should have a name!");
	if(type == invalidkey)throw CLoadException(__FILE__, __LINE__,"Invalid key, should be up, down, left, right, up, down, jump, attack1-6!");
	if(player == -1)throw CLoadException(__FILE__, __LINE__,"Player not specified in key configuration");

        char temp[255];
	std::sprintf( temp, "%s: %s", name.c_str(), CKeyboard::keyToName(getKey(player,type)));
	setText(string(temp));
}

COptionKey::~COptionKey()
{
	// Nothing
}

void COptionKey::logic(){
	char temp[255];
	std::sprintf( temp, "%s: %s", name.c_str(), CKeyboard::keyToName(getKey(player,type)));
	setText(string(temp));
}

void COptionKey::run(const Menu::CContext & context){
    // Do dialog
    //Box::messageDialog(Menu::CMenu_v2::Width, Menu::CMenu_v2::Height, "Press a Key!",2);

    /*
    Keyboard key;
    key.wait();
    */
/*    CBitmap temp(Menu::CMenu_v2::Width, Menu::CMenu_v2::Height);
    // Menu::CContext tempContext = context;
    Menu::CContext tempContext(context);
    tempContext.initialize();
    Menu::CInfoBox keyDialog;
    // keyDialog.setFont(tempContext.getFont());
    //keyDialog.location.set(-1,-1,1,1);
    const int width = temp.getWidth();
    const int height = temp.getHeight();
    const CFont & font = CConfiguration::getMenuFont()->get(context.getFont()->get());
    const int radius = 15;
    keyDialog.setText("Press a Key!");
    keyDialog.location.setDimensions(font.textLength("Press a Key!") + radius, font.getHeight() + radius);
    keyDialog.location.setCenterPosition(Gui::CRelativePoint(0, 0));
    // keyDialog.location.setPosition(Gui::AbsolutePoint((width/2)-(keyDialog.location.getWidth()/2), (height/2)-(keyDialog.location.getHeight()/2)));
    // keyDialog.location.setPosition2(Gui::AbsolutePoint((
    keyDialog.location.setRadius(radius);
    keyDialog.colors.body = CBitmap::makeColor(0,0,0);
    keyDialog.colors.bodyAlpha = 180;
    keyDialog.colors.border = CBitmap::makeColor(255,255,255);
    keyDialog.colors.borderAlpha = 255;
    keyDialog.open();
    CInputManager::waitForClear();
    while (!CInputManager::anyInput() && keyDialog.isActive()){
        CInputManager::HandleNonEventInput();
	keyDialog.act(font);

	//if (keyDialog.isActive()){
    //        InputManager::poll();
	//}

	tempContext.act();
	tempContext.render(0, temp);
	keyDialog.render(temp, font);
	temp.BlitToScreen();
    }
    tempContext.finish();
    keyCode = CInputManager::readKey();
    setKey(player,type, keyCode);
    CInputManager::waitForClear();
	*/
	}
}
} //end SGF