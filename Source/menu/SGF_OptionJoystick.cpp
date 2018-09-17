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

#include "menu/SGF_OptionJoystick.h"
#include "util/SGF_Debug.h"
#include "configuration/SGF_Configuration.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuV2.h"
//#include "../input/all.h"
#include "SGF_Global.h"
//#include "../input/keyboard.h"
#include "util/SGF_Util.h"
#include "resource/all.h"
#include <sstream>

#include "gui/SGF_Box.h"


using namespace std;
namespace SGF {

namespace Menu {
static COptionJoystick::JoystickType convertToKey(const string &k){
    string temp = k;
    for(unsigned int i=0;i<temp.length();i++){
        temp[i] = tolower(temp[i]);
    }

    if (temp == "up") return COptionJoystick::Up;
    if (temp == "down") return COptionJoystick::Down;
    if (temp == "left") return COptionJoystick::Left;
    if (temp == "right") return COptionJoystick::Right;
    if (temp == "jump") return COptionJoystick::Jump;
    if (temp == "attack1") return COptionJoystick::Attack1;
    if (temp == "attack2") return COptionJoystick::Attack2;
    if (temp == "attack3") return COptionJoystick::Attack3;
    if (temp == "attack4") return COptionJoystick::Attack4;
    if (temp == "attack5") return COptionJoystick::Attack5;
    if (temp == "attack6") return COptionJoystick::Attack6;

    return COptionJoystick::Invalidkey;
}

static CConfiguration::JoystickInput getKey(int player, COptionJoystick::JoystickType k){
    switch(k){
        case COptionJoystick::Up:
            return CConfiguration::getConfig(player)->getJoyKey("joykey-up");
        case COptionJoystick::Down:
            return CConfiguration::getConfig(player)->getJoyKey("joykey-down");
        case COptionJoystick::Left:
            return CConfiguration::getConfig(player)->getJoyKey("joykey-left");
        case COptionJoystick::Right:
            return CConfiguration::getConfig(player)->getJoyKey("joykey-right");
        case COptionJoystick::Jump:
            return CConfiguration::getConfig(player)->getJoyKey("joykey-jump");
        case COptionJoystick::Attack1:
            return CConfiguration::getConfig(player)->getJoyKey("joykey-action1");
        case COptionJoystick::Attack2:
            return CConfiguration::getConfig(player)->getJoyKey("joykey-action2");
        case COptionJoystick::Attack3:
            return CConfiguration::getConfig(player)->getJoyKey("joykey-action3");
        case COptionJoystick::Attack4:
        case COptionJoystick::Attack5:
        case COptionJoystick::Attack6:
        default:
            break;
    }
	// code will never each here
	return CJoystick::Invalid;
}

static void setKey(int player, COptionJoystick::JoystickType k, CConfiguration::JoystickInput key){
    switch(k){
        case COptionJoystick::Up:
            CConfiguration::getConfig(player)->setKey("joykey-up", key );
            break;
        case COptionJoystick::Down:
            CConfiguration::getConfig(player)->setKey("joykey-down", key );
            break;
        case COptionJoystick::Left:
            CConfiguration::getConfig(player)->setKey("joykey-left", key );
            break;
        case COptionJoystick::Right:
            CConfiguration::getConfig(player)->setKey("joykey-right", key );
            break;
        case COptionJoystick::Jump:
            CConfiguration::getConfig(player)->setKey("joykey-jump", key );
            break;
        case COptionJoystick::Attack1:
            CConfiguration::getConfig(player)->setKey("joykey-action1", key );
            break;
        case COptionJoystick::Attack2:
            CConfiguration::getConfig(player)->setKey("joykey-action2", key );
            break;
        case COptionJoystick::Attack3:
            CConfiguration::getConfig(player)->setKey("joykey-action3", key );
            break;
        case COptionJoystick::Attack4:
        case COptionJoystick::Attack5:
        case COptionJoystick::Attack6:
        default:
            break;
    }
}

static CConfiguration::JoystickInput readJoystick(){
    vector<CJoystick::Key> keys;
    keys.push_back(CJoystick::Up);
    keys.push_back(CJoystick::Down);
    keys.push_back(CJoystick::Left);
    keys.push_back(CJoystick::Right);
    keys.push_back(CJoystick::Button1);
    keys.push_back(CJoystick::Button2);
    keys.push_back(CJoystick::Button3);
    keys.push_back(CJoystick::Button4);

    CInputMap<CJoystick::Key> input;
    for (vector<CJoystick::Key>::iterator it = keys.begin(); it != keys.end(); it++){
        input.set(*it, 0, true, *it);
    }
    input.set(CKeyboard::Key_ESC, 0, true, CJoystick::Invalid);

    while (true){
        CInputManager::poolEvents();
		 vector<CInputMap<CJoystick::Key>::InputEvent> out = CInputManager::getEvents(input, CInputSource());
        for (vector<CInputMap<CJoystick::Key>::InputEvent>::iterator it = out.begin(); it != out.end(); it++){
            const CInputMap<CJoystick::Key>::InputEvent & event = *it;
            if (event.enabled){
               Debug::debug(Debug::input,__FUNCTION__) << "Press: " << event.out << endl;
                if (event.out == CJoystick::Invalid){
                    CInputManager::waitForRelease(input, CInputSource(), CJoystick::Invalid);
                    throw Exception::Return(__FILE__, __LINE__);
                }
                return event.out;
            }
        }
        Util::rest(1);
    }
    return CJoystick::Up;
}

COptionJoystick::COptionJoystick(const Gui::CContextBox & parent,const Token *token) throw( CLoadException ):
CMenuOption(parent,token),
name(""),
player(-1),
type(Invalidkey),
keyCode(0){
    if (*token != "joystick"){
        throw CLoadException(__FILE__, __LINE__,"Not joystick option");
    }

    TokenView view = token->view();
    while (view.hasMore()){
		try{
            const Token * tok;
            view >> tok;
            if ( *tok == "name" ){
				tok->view() >> name;
            } else if ( *tok == "player" ) {
                tok->view()  >> player;
            } else if ( *tok == "type" ) {
                string temp;
                tok->view()  >> temp;
                type = convertToKey(temp);
            } else {
                Debug::debug(Debug::menu,__FUNCTION__) <<"Unhandled menu attribute: "<<endl;
                tok->print(" ");
            }
        } catch ( const CTokenException & ex ) {
            // delete current;
            string m( "Menu parse error: " );
            m += ex.getTrace();
            throw CLoadException(__FILE__, __LINE__, m);
        } catch ( const CLoadException & ex ) {
            // delete current;
            throw ex;
        }
    }

    if(name.empty())throw CLoadException(__FILE__, __LINE__,"No name set, this option should have a name!");
    if(type == Invalidkey)throw CLoadException(__FILE__, __LINE__,"Invalid key, should be up, down, left, right, up, down, jump, attack1-6!");
    if(player == -1)throw CLoadException(__FILE__, __LINE__,"Player not specified in key configuration");

    ostringstream out;
    out << name << ": " << CJoystick::keyToName(getKey(player, type));
    setText(out.str());
}

COptionJoystick::~COptionJoystick(){
    // Nothing
}

void COptionJoystick::logic(){
    /*
    char temp[255];
    sprintf( temp, "%s: %s", name.c_str(), Joystick::keyToName(getKey(player,type)));
    setText(string(temp));
    */
}
#if 0
void COptionJoystick::run(bool &endGame){

	Menu::CMenu_v1 *menu_v1 = (Menu::CMenu_v1 *)getParent();//int x, y, width, height;
    CTTFFont *vFont = NULL;
	try {
			vFont = CResource::getTTFont(Menu::CMenu_v1::getFont(),Menu::CMenu_v1::getFontWidth(),Menu::CMenu_v1::getFontHeight());

			}catch (Exception::Filesystem::CNotFound &ex) {
				 ostringstream out;
				 out << "CFont not found " << ex.getTrace()<< endl;
				 Debug::debug(Debug::font,__FUNCTION__) << out.str() << endl;
			}
	const char * message = "Press a joystick button!";
    const int width = vFont->textLength(message) + 10;
    const int height = vFont->getHeight() + 10;
    const int x = (menu_v1->getWork()->getWidth()/2) - (width/2);
    const int y = (menu_v1->getWork()->getHeight()/2) - (height/2);
    Gui::CBox dialog;
    dialog.position.x = 0;
    dialog.position.y = 0;
    dialog.position.width = vFont->textLength(message) + 10;
    dialog.position.height = vFont->getHeight() + 10;
    dialog.position.radius = 0;
	dialog.position.bodyColor.r = 0;
	dialog.position.bodyColor.g = 0;
	dialog.position.bodyColor.b = 0;

    dialog.position.bodyAlpha = 200;
    dialog.position.borderColor.r = 255;
	dialog.position.borderColor.g = 255;
	dialog.position.borderColor.b = 255;
    dialog.position.borderAlpha = 255;
	 Colors::ColorDefinition cor1;
	cor1.r=255;
	cor1.g=255;
	cor1.b=255;

    CBitmap temp = CBitmap::temporaryBitmap(width,height);
    dialog.render(temp);
	vFont->DrawTextNew(5,5,cor1,temp,message,-1);//>printf( 5, 5, cor1, temp, message, -1);
    temp.BlitToScreen(x,y);

    setKey(player, type, readJoystick());

    ostringstream out;
    out << name << ": " << CJoystick::keyToName(getKey(player, type));
    setText(out.str());

    /*
    CKeyboard key;
    keyCode = readKey(key);
    setKey(player,type, keyCode);
    */
}
#endif
void COptionJoystick::run(const Menu::CContext & context){
	/*
	//int x, y, width, height;
    const CFont & vFont = CConfiguration::getMenuFont()->get(context.getFont()->get());
    const char * message = "Press a joystick button!";
    const int width = vFont.textLength(message) + 10;
    const int height = vFont.getHeight() + 10;
    // const int x = (getParent()->getWork()->getWidth()/2) - (width/2);
    // const int y = (getParent()->getWork()->getHeight()/2) - (height/2);
    const int x = Menu::CMenu_v2::Width / 2 - width/2;
    const int y = Menu::CMenu_v2::Height / 2 - height/2;
    CBox dialog;
    dialog.location.setPosition(Gui::CAbsolutePoint(0,0));
    dialog.location.setDimensions(vFont.textLength(message) + 10, vFont.getHeight() + 10);
    dialog.location.setRadius(0);
    dialog.colors.body = CBitmap::makeColor(0,0,0);
    dialog.colors.bodyAlpha = 200;
    dialog.colors.border = CBitmap::makeColor(255,255,255);
    dialog.colors.borderAlpha = 255;
    CBitmap temp = CBitmap::temporaryBitmap(width,height);
    dialog.render(temp, vFont);
    vFont.printf( 5, 5, CBitmap::makeColor(255,255,255), temp, message, -1);
    temp.BlitToScreen(x,y);

    setKey(player, type, readJoystick());

    ostringstream out;
    out << name << ": " << CJoystick::keyToName(getKey(player, type));
    setText(out.str());
	*/
    /*
    Keyboard key;
    keyCode = readKey(key);
    setKey(player,type, keyCode);
    */
}
}
} //end SGF