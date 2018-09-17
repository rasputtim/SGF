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
#include "menu/SGF_OptionMenu.h"
//#include "menu/SGF_MenuV1.h"

#include "util/SGF_Debug.h"
#include "SGF_Global.h"
#include "configuration/SGF_Configuration.h"
using namespace std;
namespace SGF {

namespace Menu {
COptionMenu::COptionMenu(const Gui::CContextBox & parent,const Token *token,const Menu::COptionFactory & factory) throw( CLoadException ):
CMenuOption(parent,token),
menu(0),
menuV2(0){
	bool use_v1 = false;
	bool use_v2 = true;
	switch(use_v2 /*CConfiguration::getMenuVersion()*/) {
	case 1: use_v1 = true;
			use_v2 = false;
			break;
	case 2: use_v1 = false;
			use_v2 = true;
			break;
	}

    if (use_v1) {
#if 0
Menu::CMenu_v1 *menuV1;
	 Debug::debug(Debug::menu,__FUNCTION__) << "Creating Option Menu v_1: "  << endl;
	// Check whether we have a menu or tabmenu
    if ( *token == "menu" ){
	menuV1 = new Menu::CMenu_v1();
	menu = menuV1;
    } else {
	throw CLoadException(__FILE__, __LINE__,"COptionMenu::COptionMenu - Not a menu");
    }
    // Set this menu as an option
    menuV1->setAsOption(true);


    if (token->numTokens() == 1){
        string temp;
		token->view() >> temp;
		Filesystem::CRelativePath menuPath(temp);
		if (menuPath.exist()) {
			menuV1->load(menuPath.completePath(),factory);

		}else {
			ostringstream out;
			out << "CRelativePath Cannot find: " << menuPath.completePath() <<endl;
			throw CLoadException(__FILE__, __LINE__,out.str());
		}
    } else {
        menuV1->load(token,factory);
    }

    this->setText(menuV1->getName());

    // Lets check if this menu is going bye bye
    if ( menuV1->checkRemoval() ) setForRemoval(true);
#endif
	} //end menu v1
	if (use_v2) {
		//Menu::CMenu_v2 *menuV2;
		Debug::debug(Debug::menu,__FUNCTION__) << "Creating Option Menu v_2: "  << endl;
		if (*token != "menu"){
        throw CLoadException(__FILE__, __LINE__, "Not a menu");
		}

    if (token->numTokens() == 1){
        string temp;
        token->view() >> temp;
        menuV2 = new Menu::CMenu_v2(Filesystem::getInstance().find(Filesystem::CRelativePath(temp)), factory);
    } else {
        menuV2 = new Menu::CMenu_v2(token, factory);
    }
	menu = menuV2;
    this->setText(menuV2->getName());
    this->setInfoText(menuV2->getInfo());
	} //end use v2

	}

COptionMenu::~COptionMenu()
{
	// Delete our menu
	if(menu)delete menu;
	if(menuV2)delete menuV2;
}

void COptionMenu::logic()
{
	// Nothing
}
/*
void COptionMenu::run(bool &endGame){
	// Do our new menu
	Menu::CMenu_v1 * menuV1= (Menu::CMenu_v1 *) menu;
	menuV1->run();
}
*/
void COptionMenu::run(const Menu::CContext & context){
    // Do our new menu
	//menuV2= (Menu::CMenu_v2 *) menu;
    try{
        menuV2->run(context);
    } catch (const Exception::Return ignore){
        throw Menu::CReload(__FILE__, __LINE__);
    }

}


}
} //end SGF