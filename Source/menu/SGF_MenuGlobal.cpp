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
#include "menu/SGF_MenuGlobal.h"
#include "structures/SGF_StackString.h"
#include "configuration/SGF_Configuration.h"
#include "util/SGF_AudioSystem.h"
#include "exceptions/SGF_FileExceptions.h"
#include "game/SGF_Mod.h"



using namespace std;
namespace SGF {

class CBitmap;
namespace Menu {
CStackString CMenuGlobals::selectSound;

CMenuGlobals::CMenuGlobals(){
}

CMenuGlobals::~CMenuGlobals(){
}

void CMenuGlobals::setMusic(const string &file) {
	if (CResource::getMusic(Filesystem::CRelativePath(file))){
		CMusic::pause();
		CMusic::play();
    }
}

void CMenuGlobals::setSelectSound(const string &file){
	selectSound.push(file);
}

const string CMenuGlobals::currentSelectSound(){
	if(!selectSound.empty()){
		return selectSound.top();
	}
	else return string();
}

void CMenuGlobals::playSelectSound() throw(CLoadException){
	if (!selectSound.empty()){
		try{
			//Debug::debug( Debug::menu,__FUNCTION__ ) << "Sound: " << selectSound.top().my_string << endl;
		CSound * select = CResource::getSound(selectSound.top());

		if (select->GetError()==0)
			select->play();
		} catch ( const CLoadException & ex ) {
		      throw ex;
	      }
	}

}

void CMenuGlobals::popSelectSound(){
	if(!selectSound.empty()){
		selectSound.pop();
	}
}

/*! game speed */
double CMenuGlobals::getGameSpeed(){
	return CConfiguration::gameSpeed.getFloat();
}

/*! set speed */
void CMenuGlobals::setGameSpeed(double s){
	CConfiguration::gameSpeed.setFloat( s );
	CConfiguration::gameSpeed.setFloat(s);
}

/*! invincible */
bool CMenuGlobals::getInvincible(){
//	return CConfiguration::getInvincible();
	return false;
}

/*! set invincible */
void CMenuGlobals::setInvincible(bool i){
//	CConfiguration::setInvincible( i );
}

/*! game fullscreen */
bool CMenuGlobals::getFullscreen(){
	return CConfiguration::fullScreen.getBool();
}

/*! set speed */
void CMenuGlobals::setFullscreen(bool f){
	CConfiguration::fullScreen.setBool( f );
}

/*! game lives */
int CMenuGlobals::getLives(){
	return 4;//CConfiguration::playerLives.getInteger();
}

/*! set lives */
void CMenuGlobals::setLives(int l){
	//CConfiguration::playerLives.setInteger(l);
}

int CMenuGlobals::getNpcBuddies(){
	//return CConfiguration::getNpcBuddies();
	return false;
}

void CMenuGlobals::setNpcBuddies( int i ){
	//CConfiguration::setNpcBuddies( i );
}

Level::CLevelInfo CMenuGlobals::doLevelMenu(const string dir, Menu::CMenu_v1 *parent) throw(CLoadException){
#if 0
    vector<string> possible = Util::getFiles(Filesystem::getInstance().find(dir + "/"), "*.txt" );

    /* count is the number of pixels the menu can be. try not to hard code
     * if possible. it should probably be based on the size of the font.
     */
    int count = 0;
    for ( vector<string>::iterator it = possible.begin(); it != possible.end(); it++ ){
        string & path = *it;
        path = Filesystem::getInstance().cleanse(path);
        /*
        path.erase(0, Util::getDataPath().length() + 1);
        */
        count += 60;
    }

    if (count > 250){
        count = 250;
    }

    if (possible.size() == 0){
        throw CLoadException(__FILE__, __LINE__,"No level files found");
    }

    if (possible.size() == 1){
        return Level::readLevels(Filesystem::getInstance().find(possible[0]));
    }
#endif

	vector<Level::CLevelInfo> & possible = SGF::Mod::getCurrentMod()->getLevels();
    if (possible.size() == 0){
        throw CLoadException(__FILE__, __LINE__,"No level sets defined!");
    }

    if (possible.size() == 1){
        return possible[0];
    }
	// FIXME what is this crap? Do we need it?
    /* don't hardcode 60, base it on the size of the font */
    int count = possible.size() * 60;
    /* what is 250?? */
    if (count > 250){
        count = 250;
    }
#if 0
    try{
        Menu::CMenu_v1 temp;
        temp.setParent(parent);
        int index = 0;
        for ( unsigned int i = 0; i < possible.size(); i++ ){
         /*   COptionLevel *opt = new COptionLevel(,NULL, &index, i);
            opt->setText(possible[i].getName());
            opt->setInfoText("Select a set of levels to play");
            temp.addOption(opt);*/
        }
		Filesystem::CRelativePath menuPath("menu/level_select.txt");
		if (menuPath.exist()) {
			temp.load(menuPath.completePath(),temp.defaultOptionFactory);
			temp.backboard.position.height = count;
			// Run it
			temp.run();
		}else throw CLoadException(__FILE__, __LINE__,"Could not find MenuPath " );
        return possible[index];
    } catch (const CTokenException & ex){
        Debug::debug(Debug::menu,__FUNCTION__) << "There was a problem with the token. Error was:\n  " << ex.getTrace() << endl;
        throw CLoadException(__FILE__, __LINE__,"Could not load levels " + ex.getTrace());
    }
    throw CLoadException(__FILE__, __LINE__,"No level chosen!");
#endif
    /*
    // Now lets get the level or return
    string l = level;
    level = "";

    return l;
    */
}

bool CMenuGlobals::freeForAll(){
  //  return CConfiguration::getPlayMode() == CConfiguration::FreeForAll;
	return false;
}

bool CMenuGlobals::cooperative(){
 //   return CConfiguration::getPlayMode() == CConfiguration::Cooperative;
	return false;
}

void CMenuGlobals::setFreeForAll(){
  //  CConfiguration::setPlayMode(CConfiguration::FreeForAll);
}

void CMenuGlobals::setCooperative(){
  //  CConfiguration::setPlayMode(CConfiguration::Cooperative);
}

}

} //end SGF