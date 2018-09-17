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
/**
* \file optionfactory.cpp
* \brief Funções do Menu
**
Descricao mais detalhada do arquivo .
* Em geral tem mais de uma l i n h a .
**
 \sa optionfactory.h
**/
#include "util/SGF_Token.h"
#include "menu/options.h"
#include "SGF_Global.h"


using namespace std;
namespace SGF {

namespace Menu {

COptionFactory::COptionFactory(){
}

COptionFactory::~COptionFactory(){
}
void COptionFactory::registerOption(CMenuOption * option,const string & tokenName){
	registeredOption *temp = new registeredOption;
	temp->enabled=true;
	temp->option=option;
	temp->tokenName=tokenName;
	map<string,const registeredOption*>::iterator first_it;
	first_it = optionsMap.find(tokenName);
	if( first_it == optionsMap.end() ) {
			optionsMap[tokenName] = temp;
		}


}
/** @fn COptionFactory::getOption(const Gui::CContextBox & parent,Token *token)
@brief Lê o Token de uma opção e cria uma Classe para ela
O Objetivo é receber um token de opção e Criar uma Classe para esta nova opção
@param *Token: Ponteiro para um Token que já foi carregado previamente na memória
@return Ponteiro para a Nova Classe Criada
@warning nenhum aviso
**/
CMenuOption * COptionFactory::getOption(const Gui::CContextBox & parent, const Token *token) const{
	const Token * tok;
	token->view() >> tok;
	string temp = tok->getName();
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN//   Token: // " << temp <<endl;

	if ( *tok == "menu" ){
		Debug::debug(Debug::menu,__FUNCTION__) << "************************************** "<<endl;
		Debug::debug(Debug::menu,__FUNCTION__) << "WILL CREATE A SUBMENU OPTION "<<endl;

		// Create a sub menu
		const Token * typeToken = tok->findToken("_/type");
			if (typeToken != NULL){
				string type;
				typeToken->view() >> type;
				if (type == "tabbed"){
				return new COptionTabMenu(parent,tok,*this);
				}
		}

		CMenuOption *temp=NULL;
		// Create a sub menu
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	temp= new COptionMenu(parent,tok,*this);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
		Debug::debug(Debug::menu,__FUNCTION__) << "END CREATING A SUBMENU OPTION "<<endl;
		Debug::debug(Debug::menu,__FUNCTION__) << "************************************** "<<endl;
	}

	else if (*tok == "tabmenu" ){
		CMenuOption *temp=NULL;
		//! Create a tab menu
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	temp =  new COptionTabMenu(parent,tok,*this);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	}

	else if ( *tok == "key" ){
		// Reconfigure a given key
		CMenuOption *temp=NULL;
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	temp =  new COptionKey(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "joystick" ){
		// Reconfigure a given joystick button
		CMenuOption *temp=NULL;
		temp =  new COptionJoystick(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "adventure" ){
		// Adventure mode
		CMenuOption *temp=NULL;
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	temp =  new COptionAdventure(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "adventure-cpu" ){
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =  new COptionAdventureCpu(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "versus" ){
		// Versus mode
		CMenuOption *temp=NULL;
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	temp =   new COptionVersus(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "network-host" ){
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		#ifdef HAVE_NETWORKING
		temp =   new COptionNetworkHost(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
		#endif
		return temp;
    } else if (*tok == "change-mod"){
        Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =   new COptionChangeMod(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "network-join" ){
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		#ifdef HAVE_NETWORKING
		temp =   new COptionNetworkJoin(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
		#endif
		return temp;
        } else if (*tok == "screen-size"){
            Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	    CMenuOption *temp=NULL;
			temp =   new COptionScreenSize(parent,tok);
			Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "npc" ){
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =   new COptionNpcBuddies(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
        } else if (*tok == "play-mode"){

			Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	    CMenuOption *temp=NULL;
			temp =   new COptionPlayMode(parent,tok);
			Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    		return temp;
	} else if ( *tok == "credits" ){
		// Credits mode
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		//temp =   new COptionCredits(tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "speed" ){
		// Speed
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =   new COptionSpeed(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "invincible" ){
		// Invincible
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =   new COptionInvincible(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "fullscreen" ){
		// Invincible
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
        temp =   new COptionFullscreen(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "quit" ){
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =  new COptionQuit(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "lives" ){
		// Invincible
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =   new COptionLives(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	} else if ( *tok == "font-select" ){
		// Invincible
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
	//	if(CConfiguration::getMenuVersion() == 1) {
	//	temp =   new COptionSelectFont_v1(parent,tok);
	//	}else {
		temp =   new COptionSelectFont_v2(parent,tok);
	//	}

		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	}
	else if ( *tok == "dummy" ){
		// Invincible
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =   new COptionDummy(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	}else if ( *tok == "configuration" ){
		// Configuration
		Debug::debug(Debug::menu,__FUNCTION__) << " Creating Class: " << tok->getName() <<endl;
    	CMenuOption *temp=NULL;
		temp =   new COptionConfig(parent,tok);
		Debug::debug(Debug::menu,__FUNCTION__) << " Class: " << tok->getName() << " Created Ok at Address: "<< temp <<endl;
    	return temp;
	}

	else { //! Handles options created by user program (not by gameengine) and registered
		if(!optionsMap.empty()) {   // E se não for vazio, mas não tiver a opção correta no map?
		map<string,const registeredOption*>::const_iterator second_it;
		second_it = optionsMap.find(tok->getName());
		if( second_it != optionsMap.end() ) {
			Debug::debug(Debug::menu,__FUNCTION__) << " FOUND OPTION: " << second_it->second->option <<" :  " << second_it->second->tokenName <<endl;
			second_it->second->option->load(tok);
		}else{
			Debug::debug(Debug::menu,__FUNCTION__) << " NOT FOUND OPTION: " << second_it->second->option <<endl;
		}
		return second_it->second->option;

		}

		else{

		CMenuOption *temp=NULL;
		Debug::debug(30,__FUNCTION__) <<" Unhandled menu attribute: "<< tok->getName() <<endl;
		return temp;
		}
	//}else {

		//tok->print(" ");
	}

	Debug::debug(Debug::menu,__FUNCTION__) << "END//   Token: //" << temp <<endl;

	return 0;
}

} // end namespace Menu
} //end SGF
