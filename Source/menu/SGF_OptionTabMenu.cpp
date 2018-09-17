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
#include "menu/options.h"
#include "util/SGF_Token.h"
#include "menu/SGF_OptionTabMenu.h"
using namespace std;
namespace SGF {

namespace Menu {
COptionTabMenu::COptionTabMenu(const Gui::CContextBox & parent, const Token *token, const Menu::COptionFactory & factory)throw (CLoadException):
CMenuOption(parent, token),
menu(0){
    if (token->numTokens() == 1){
        string temp;
        token->view() >> temp;
        menu = new Menu::CMenu_v2(Filesystem::getInstance().find(Filesystem::CRelativePath(temp)), factory, Menu::CMenu_v2::Tabbed);
    } else {
        menu = new Menu::CMenu_v2(token, factory, Menu::CMenu_v2::Tabbed);
    }

    // this->setText(menu->getName());
    // token->print("Menu: ");
    const Token * tok = token->findToken("_/name");
    if (tok != NULL){
        string name;
        tok->view() >> name;
        // Debug::debug(0, "menu") << "Menu name: " << name << endl;
        this->setText(name);
    } else {
        // No name?
        throw CLoadException(__FILE__, __LINE__, "Menu has no name");
    }
}

COptionTabMenu::~COptionTabMenu(){
    // Delete our menu
    if (menu){
        delete menu;
    }
}

void COptionTabMenu::logic(){
	// Nothing
}

void COptionTabMenu::run(const Menu::CContext & context){
    // Do our new menu
    // menu->run(context);
    try{
        menu->run(context);
    } catch (const Exception::Return ignore){
        throw Menu::CReload(__FILE__, __LINE__);
    }
}

}
}//end SGF