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

#include "game/SGF_Mod.h"
#include "util/SGF_Debug.h"
#include "graphics/SGF_Bitmap.h"
#include "util/SGF_TokenReader_xml.h"
#include "util/SGF_FileSystem.h"
#include "level/SGF_LevelUtils.h"
#include "util/SGF_FilesystemBase.h"

using namespace std;

	
SGF::Mod * SGF::Mod::currentMod = NULL;

namespace SGF {
Mod::Mod(const string & name, const Filesystem::CAbsolutePath & path) throw (CLoadException):
 name(name) {
	 try{
		SGF::CTokenReaderXML reader(path.path());
        SGF::Token * head = reader.readToken();

        //const Token * name = head->findToken("game/name");
        const Token * token_menu = head->findToken("game/menu");
        if (token_menu == NULL){
            throw CLoadException(__FILE__, __LINE__,"No game/menu token found. Add (menu some/path) to the mod file.");
        }
        token_menu->view() >> menu;

        vector<const Token*> token_level = head->findTokens("game/level-set");
        Debug::debug(1,__FUNCTION__) << "Found " << token_level.size() << " level sets" << endl;
        for (vector<const Token*>::iterator it = token_level.begin(); it != token_level.end(); it++){
            const Token * set = *it;
            levels.push_back(Level::readLevel(set));
        }

    } catch (const CTokenException & e){
        Debug::debug(1,__FUNCTION__) << "Error while reading mod " << path.path() << ":" << e.getTrace() << endl;
    }
}

CBitmap * Mod::createBitmap(const Filesystem::CRelativePath & path){
    return new CBitmap(Filesystem::getInstance().find(path).path());
}

CBitmap SGF::Mod::makeBitmap(const Filesystem::CRelativePath & path){
    CBitmap * what = createBitmap(path);
    CBitmap out(*what);
    delete what;
    return out;
}
Mod::Mod(){
}
Mod::~Mod(){
}

vector<Level::CLevelInfo> & Mod::getLevels(){
    return levels;
}

const string & Mod::getMenu(){
    return menu;
}

void Mod::loadDefaultMod(){
    loadMugenMod("Mugen");
}

void Mod::setMod(Mod * mod){
    if (currentMod != NULL){
        delete currentMod;
    }
    currentMod = mod;
}
void Mod::loadOpenborMod(const Filesystem::CAbsolutePath & path){
    //setMod(new OpenborMod(path));
}

void Mod::loadMugenMod(const string & name){
   string path = name + "/" + name + ".txt";
   setMod(new Mod(name, Filesystem::getInstance().find(Filesystem::CRelativePath(path))));
}

Filesystem::CAbsolutePath Mod::find(const Filesystem::CRelativePath & path){
    Filesystem::CStorage & filesystem = Filesystem::getInstance();
    string totalFailure;
    /* first search in the mod directory */
    try{
        return filesystem.find(Filesystem::CRelativePath(name).join(path));
    } catch (const Exception::Filesystem::CNotFound & fail){
        totalFailure = fail.getTrace();
    }

    /* then search in the regular place */
    try{
        return Filesystem::getInstance().find(path);
    } catch (const Exception::Filesystem::CNotFound & fail){
        /* if a file can't be found then combine the errors */
        totalFailure += fail.getTrace();
        throw Exception::Filesystem::CNotFound(__FILE__, __LINE__, fail, totalFailure);
    }
}


void Mod::loadMod(const string & name) throw (CLoadException, Exception::Filesystem::CNotFound){
    Debug::debug(1,__FUNCTION__) << "CONSTRUCTOR // Mod::loadMod" << endl;
	//string data = "data/";
	Filesystem::CAbsolutePath path(name + "/" + "mod/" + "mod.xml");
   // não dá mensagem nenhuma quando o diretório não existe. Apenas trava
   Debug::debug(1,__FUNCTION__) << "CONSTRUCTOR // Mod::loadMod path="<<path.path() << endl;

   Mod * newMod = new Mod("default",path);
   if (currentMod != NULL){
       delete currentMod;
   }
   currentMod = newMod;
}

Mod * Mod::getCurrentMod(){
    return currentMod;
}


} //end SGF