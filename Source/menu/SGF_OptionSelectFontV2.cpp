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
#include "menu/SGF_OptionSelectFontV2.h"
#include "util/SGF_Token.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuV2.h"
#include "level/SGF_LevelUtils.h"
#include "configuration/SGF_Configuration.h"
#include "SGF_Global.h"
#include "util/SGF_Loading.h"

#include <sstream>
#include <iterator>
#include <algorithm>
#include "exceptions/all.h"

using namespace std;
namespace SGF {

class CLoadException;


namespace Menu {

COptionSelectFont_v2::COptionSelectFont_v2(const Gui::CContextBox & parent,const Token *token) throw(CLoadException):
CMenuOption(parent,token),
typeAdjust(fontName),
lblue(255),
lgreen(255),
rblue(255),
rgreen(255){
    setRunnable(false);

    if ( *token != "font-select" ){
        throw CLoadException(__FILE__, __LINE__, "Not a font selector");
    }

    TokenView view = token->view();
    while (view.hasMore()){
        try{
            const Token * tok;
            view >> tok;
            if ( *tok == "adjust" ){
                string temp;
                tok->view() >> temp;
                if ( temp == "name" ) typeAdjust = fontName;
                else if ( temp == "width" ) typeAdjust = fontWidth;
                else if ( temp == "height" ) typeAdjust = fontHeight;
                else throw CLoadException(__FILE__, __LINE__, "Incorrect value \"" + temp + "\" in font-select");
            } else {
                Debug::debug(Debug::menu,__FUNCTION__) << "Unhandled menu attribute: " << endl;
                //if (Debug::getDebug() >= 3){
                //    tok->print(" ");
                //}
            }
        } catch ( const CTokenException & ex ) {
            throw CLoadException(__FILE__, __LINE__, ex, "Menu parse error");
        } catch ( const CLoadException & ex ) {
            // delete current;
            throw ex;
        }
    }
}

void COptionSelectFont_v2::open(){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN " << endl;
    // Find and set fonts now
    if (typeAdjust == fontName){
		fonts = CFontList::GetInstance()->getAvailableFonts();
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "END " << endl;
}

void COptionSelectFont_v2::close(){
    if (typeAdjust == fontName){
        /* the user probably loaded a bunch of different fonts that will
         * never be used again, so clear the font cache
         * TODO: dont clear the currently selected font
         */
        //s CFontFactory::clear();
    }
}

COptionSelectFont_v2::~COptionSelectFont_v2(){
    // Nothing
}

void COptionSelectFont_v2::logic(){
	Debug::debug(Debug::menu,__FUNCTION__) << "Show font information on the screen"<< endl;
    /* FIXME Get current font and display info */
    switch (typeAdjust){
        case fontName:{
			string name="";
            name = (CConfiguration::getMenuFont_v2()!=NULL ?CConfiguration::getMenuFont_v2()->getName():"Arial.ttf");
            setText("Current Font: " + name);
            break;
	}
        case fontWidth:{
            ostringstream temp;
            temp << "Font Width: " << CConfiguration::menuFontSize.getInteger();
            setText(temp.str());
            break;
        }
        case fontHeight:{
            ostringstream temp;
            temp << "Font Height: " << CConfiguration::menuFontSize.getInteger();
            setText(temp.str());
            break;
        }
        default: break;
    }
    if (lblue < 255){
        lblue += 5;
    }

    if (rblue < 255){
        rblue += 5;
    }

    if (lgreen < 255){
        lgreen += 5;
    }

    if (rgreen < 255){
        rgreen += 5;
    }
}

void COptionSelectFont_v2::run(const Menu::CContext & context){
     //throw Menu::CMenuException(__FILE__, __LINE__);
    /* throw something to quit back to the previous menu */
}

bool COptionSelectFont_v2::leftKey(){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN" <<endl;
    switch (typeAdjust){
        case fontName:
            nextIndex(false);
            break;
        case fontWidth:
           CConfiguration::menuFontSize.setInteger(CConfiguration::menuFontSize.getInteger() - 1);
			
			break;
        case fontHeight:
            CConfiguration::menuFontSize.setInteger(CConfiguration::menuFontSize.getInteger() - 1);
            break;
        default:
            break;
    }
    lblue = lgreen = 0;
	Debug::debug(Debug::menu,__FUNCTION__) << "END" <<endl;
    return true;
}

bool COptionSelectFont_v2::rightKey(){
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN" <<endl;
    switch (typeAdjust){
        case fontName:
            nextIndex(true);
            break;
        case fontWidth:
           CConfiguration::menuFontSize.setInteger(CConfiguration::menuFontSize.getInteger() + 1);
            break;
        case fontHeight:
            CConfiguration::menuFontSize.setInteger(CConfiguration::menuFontSize.getInteger() + 1);
            break;
        default:
            break;
    }
    rblue = rgreen = 0;
    return true;
	Debug::debug(Debug::menu,__FUNCTION__) << "END" <<endl;
}

void COptionSelectFont_v2::nextIndex(bool forward){
   Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN" <<endl;
	if (fonts.size() == 0){
        return;
    }
    Debug::debug(Debug::menu,__FUNCTION__) << "Number of Fonts in the vector fonts:  "<< fonts.size() <<endl;
    int index = 0;
    if (CConfiguration::getMenuFont_v2() != NULL){
	for (unsigned int i = 0 ; i < fonts.size() ; ++i){
	    if (CConfiguration::getMenuFont_v2() == fonts[i]){
		index = i;
	    }
	}
    }

    if (forward){
	index++;
	if (index >= (int) fonts.size()){
	    index = 0;
	}
    } else {
	index--;
	if (index < 0){
	    index = (int)fonts.size()-1;
	}
    }
	/*
Todo // Solve problem with sane fonts
while (!CFontInfo::saneFont(fonts[index])){
        Debug::debug(Debug::menu,__FUNCTION__) << "Warning: erasing font `" << fonts[index]->getName() << "'" << endl;
        int where = 0;
        vector<Util::CReferenceCount<Menu::CFontInfo> >::iterator it;
        for (it = fonts.begin(); it != fonts.end() && where != index; it++, where++){
        }
        fonts.erase(it);
        if (index >= (int) fonts.size()){
            index = fonts.size() - 1;
        }
    }
	*/
    CConfiguration::setMenuFont_v2(fonts[index]);
	Debug::debug(Debug::menu,__FUNCTION__) << "END" <<endl;
    /* FIXME */
    /*
    if (fonts[index] == "Default"){
	Configuration::setMenuFont_v2("");
    } else {
	Configuration::setMenuFont_v2(fonts[index]);
    }
    */
}
}
} //end SGF