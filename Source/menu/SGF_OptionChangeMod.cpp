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
#include "menu/SGF_OptionChangeMod.h"

#include "util/tokenreader.h"
#include "util/SGF_Debug.h"
#include "game/all.h"
#include "SGF_Global.h"
#include "configuration/SGF_Configuration.h"
#include "exceptions/all.h"
//#include "menu/SGF_MenuV1.h"
#include "menu/SGF_MenuV2.h"
#include <iostream>

using namespace std;
namespace SGF {

namespace Menu {
COptionChangeMod::COptionChangeMod(const Gui::CContextBox & parent,const Token *token)throw (CLoadException):
CMenuOption(parent, token)
{
    if ( *token != "change-mod" ){
        throw CLoadException(__FILE__, __LINE__,"Not a change mod");
    }

    /* TODO: fix */
    setText("Change mod");
}

COptionChangeMod::~COptionChangeMod(){
	// Nothing
}

void COptionChangeMod::logic(){
}

static bool isModFile(const string & path){
    try{
        TokenReader reader(path);
        Debug::debug(Debug::menu,__FUNCTION__) << "Checking for a mod in " << path << endl;
        if (*reader.readToken() == "game"){
            return true;
        }
    } catch (const CTokenException & ex){
        Debug::debug(Debug::menu,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
		return false;
    }
    return false;
}

static vector<Filesystem::CAbsolutePath> findMods(){
    vector<Filesystem::CAbsolutePath> mods;
/*
    vector<Filesystem::CAbsolutePath> directories = Filesystem::getInstance().findDirectories(".");
    for (vector<Filesystem::CAbsolutePath>::iterator dir = directories.begin(); dir != directories.end(); dir++){
		string file = (*dir).path() + "/" + Filesystem::getInstance().cleanse(*dir).path() + ".txt";
        if (isModFile(file)){
            mods.push_back(file);
        }
    }
	*/
    return mods;
}


static string modNameMugen(const Filesystem::CAbsolutePath & path){
    try{
        TokenReader reader(path.path());
        Debug::debug(Debug::menu,__FUNCTION__) << "Checking for a mod in " << path.path() << endl;
        const Token * name_token = reader.readToken()->findToken("game/name");
        if (name_token != NULL){
            string name;
            name_token->view() >> name;
            return name;
        }
        return Filesystem::getInstance().cleanse(path).path();
    } catch (const CTokenException & e){
        return Filesystem::getInstance().cleanse(path).path();
    }
}

static string modNameOpenbor(const Filesystem::CAbsolutePath & path){
    return "OpenBor " + Filesystem::getInstance().cleanse(path).path();
}

static string modName(const string & path){
 /*   try{
        TokenReader reader(path);
        Debug::debug(Debug::menu,__FUNCTION__) << "modName - Checking for a mod in " << path << endl;
        const Token * name_token = reader.readToken()->findToken("game/name");
        if (name_token != NULL){
            string name;
            name_token->view() >> name;
            return name;
        }
        return Filesystem::getInstance().cleanse(path);
    } catch (const CTokenException & ex){
        Debug::debug(Debug::menu,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
		 return Filesystem::getInstance().cleanse(path);
    }  */
	return "";
}

static string modNameV2(const ModType & mod){
    switch (mod.type){
        case ModType::Mugen : return modNameMugen(mod.path);
        case ModType::Openbor : return modNameOpenbor(mod.path);
        default : return "unknown!!";
    }
}
static void changeMod(const string & path){
    size_t slash = path.rfind('/');
    size_t txt = path.rfind(".txt");
    if (slash != string::npos && txt != string::npos){
        string name = path.substr(slash + 1, path.length() - slash - 5);
		CConfiguration::gameModDir.setString(name.c_str());
		
        SGF::Mod::loadMod(name);
    } else {
        Debug::debug(Debug::menu,__FUNCTION__) << "changeMod - Could not change mod to " << path << endl;
    }
}

static void changeModV2(const ModType & mod){
    switch (mod.type){
        case ModType::Mugen : {
            string path = mod.path.path();
            size_t slash = path.rfind('/');
            size_t txt = path.rfind(".txt");
            if (slash != string::npos && txt != string::npos){
                string name = path.substr(slash + 1, path.length() - slash - 5);
				CConfiguration::gameModDir.setString(name.c_str());
                SGF::Mod::loadMugenMod(name);
            } else {
                Debug::debug(Debug::menu,__FUNCTION__) << "Could not change mod to " << path << endl;
            }
            break;
        }
        case ModType::Openbor : {
            SGF::Mod::loadOpenborMod(mod.path);
            break;
        }
    }

}
#if 0
void COptionChangeMod::run(bool &endGame) throw (CLoadException){
    try{

		//Todo: refazer esta op�ao corrigindo o problema com ao m�todo load
        int select = 0;
        // Menu::CMenu_v1 menu(Filesystem::getInstance().find("menu/change-mod.txt"));
        // menu.addOption(new OptionLevel(0, &select, 0));
        // menu.setupOptions();
        Menu::CMenu_v1 menu;
        menu.setParent(getParent());
		vector<Filesystem::CAbsolutePath> mods = findMods();
        int index = 0;
        for (vector<Filesystem::CAbsolutePath>::iterator it = mods.begin(); it != mods.end(); it++){
            // menu.addOption(new OptionLevel(0, &select, 0));
     /*       COptionLevel *opt = new COptionLevel(,0, &select, index);
			opt->setText(modName((*it).path()));
            opt->setInfoText("Choose this mod");
            menu.addOption(opt);
            index += 1;*/
        }

        if (index == 0){
            Debug::debug(Debug::menu,__FUNCTION__) << "No mods found!" << endl;
            return;
        }
		Filesystem::CRelativePath modPath("menu/change-mod.txt");
		if (modPath.exist()) {
			//s menu.load(modPath.completePath());
			menu.run();
			changeMod(mods[select].path());
		}else throw Exception::Filesystem::CNotFound(__FILE__,__LINE__,"Mod Path not Found");
    } catch (const CLoadException & le){
      //s  Debug::debug(Debug::menu,__FUNCTION__) << "COptionChangeMod::run - Could not load menu/change-mod.txt: " << le.getReason() << endl;
    } catch (const Exception::Filesystem::CNotFound & e){
        Debug::debug(Debug::menu,__FUNCTION__) << "Could not load menu/change-mod.txt: " << endl; //e.getReason() << endl;
    }
}
#endif
static bool isOpenBorPackfile(Filesystem::CAbsolutePath path){
  //  try{
  //      Bor::PackReader reader(path);
  //      return true;
  //  } catch (const Bor::PackError & error){
  //      Debug::debug(Debug::menu,__FUNCTION__) << "Error reading pak file: " << endl;
        return false;
  //  }
}

static vector<ModType> findModsV2(){
 /*   vector<ModType> mods;

    vector<Filesystem::CAbsolutePath> directories = Filesystem::getInstance().findDirectories(Filesystem::CRelativePath("."));
    for (vector<Filesystem::CAbsolutePath>::iterator dir = directories.begin(); dir != directories.end(); dir++){
        string file = (*dir).path() + "/" + Filesystem::getInstance().cleanse(*dir).path() + ".txt";
        if (isModFile(file)){
            mods.push_back(ModType(Filesystem::CAbsolutePath(file), ModType::Mugen));
        }
    }

    try{
        vector<Filesystem::CAbsolutePath> pakFiles = Filesystem::getFiles(Filesystem::getInstance().find(Filesystem::CRelativePath("paks")), "*", true);
        for (vector<Filesystem::CAbsolutePath>::iterator it = pakFiles.begin(); it != pakFiles.end(); it++){
            const Filesystem::CAbsolutePath & path = *it;
            if (isOpenBorPackfile(path)){
                Debug::debug(Debug::menu,__FUNCTION__) << "Found openbor pakfile " << path.path() << endl;
                mods.push_back(ModType(path, ModType::Openbor));
            }
        }
    } catch (const Exception::Filesystem::CNotFound & n){
        Debug::debug(Debug::menu,__FUNCTION__) << "Could not find any pak files: " << n.getTrace() << endl;
    }

    return mods;
	*/
}

void COptionChangeMod::run(const Menu::CContext & context){
 /*
 try{
        int select = 0;
        Menu::CMenu_v2 menu;
        vector<ModType> mods = findModsV2();
        map<int, ModType*> modMap;
        int index = 0;
        vector<COptionLevel *> options;
        for (vector<ModType>::iterator it = mods.begin(); it != mods.end(); it++){
            COptionLevel *opt = new COptionLevel(0, &select, index);
            string name = modNameV2(*it);
            modMap[index] = &(*it);
            opt->setText(name);
            opt->setInfoText("Choose this mod");
            if (name.compare(Util::upcase(CConfiguration::gameModDir.getString())) == 0){
                options.insert(options.begin(),opt);
            } else {
                options.push_back(opt);
            }
            index += 1;
        }

        for (vector<COptionLevel *>::iterator it = options.begin(); it != options.end(); ++it){
            menu.addOption(*it);
        }

        if (index == 0){
            Debug::debug(Debug::menu,__FUNCTION__) << "No mods found!" << endl;
            return;
        }

        try{
            menu.run(context);
        } catch (const Exception::Return & ignore){
            throw Menu::CReload(__FILE__, __LINE__);
        } catch (const Menu::CMenuException & ignore){
        }

        changeModV2(*modMap[select]);

        // Reload the menu
        throw CReloadMenuException();

    } catch (const LoadException & le){
        Debug::debug(Debug::menu,__FUNCTION__) << "Could not load menu/change-mod.txt: " << le.getTrace() << endl;
    } catch (const Exception::Filesystem::CNotFound & e){
        Debug::debug(Debug::menu,__FUNCTION__) << "Could not load menu/change-mod.txt: " << e.getTrace() << endl;
    }  */
}
}
} //end SGF