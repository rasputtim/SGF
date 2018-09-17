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

#include "level/SGF_LevelUtils.h"
#include "util/tokenreader.h"
#include "exceptions/all.h"
#include "SGF_Global.h"
#include "util/SGF_Debug.h"

using namespace std;
namespace SGF {
namespace Level{

CLevelInfo::CLevelInfo():
playerPath("players/"),
name("Level set"),
_loadingMessage("Loading Game"),
_loadingBackground(::SGF::Global::titleScreen()),
background(NULL),
x(-1),
y(-1){
}

CLevelInfo::CLevelInfo(const CLevelInfo & info){
    this->levels = info.levels;
    this->_loadingMessage = info._loadingMessage;
    this->_loadingBackground = info._loadingBackground;
    this->playerPath = info.getPlayerPath();
    this->name = info.getName();
    this->background = info.getBackground();
    this->x = info.getPositionX();
    this->y = info.getPositionY();
}

CLevelInfo & CLevelInfo::operator=(const CLevelInfo & info){
    this->levels = info.levels;
    this->_loadingMessage = info._loadingMessage;
    this->_loadingBackground = info._loadingBackground;
    this->playerPath = info.getPlayerPath();
    this->name = info.getName();
    this->background = info.getBackground();
    this->x = info.getPositionX();
    this->y = info.getPositionY();
    return *this;
}

void CLevelInfo::setLoadingMessage(const string & str){
    this->_loadingMessage = str;
}

void CLevelInfo::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

const string & CLevelInfo::loadingMessage() const {
    return this->_loadingMessage;
}

const string & CLevelInfo::loadingBackground() const {
    return this->_loadingBackground;
}

const string & CLevelInfo::getPlayerPath() const {
    return this->playerPath;
}

void CLevelInfo::addLevel(const string & s){
    levels.push_back(s);
}

const vector<string> & CLevelInfo::getLevels() const {
    return levels;
}

void CLevelInfo::setPlayerPath(const string & s){
    this->playerPath = s;
}

void CLevelInfo::setName(const string & s){
    this->name = s;
}

const string & CLevelInfo::getName() const {
    return name;
}

CLevelInfo::~CLevelInfo(){
}

CLevelInfo readLevel(const  Token * level) {
    CLevelInfo info;
	try{

        const Token * token_name = level->findToken("level-set/name");
        const Token * token_levels = level->findToken("level-set/levels");
        //const Token * token_player = level->findToken("level-set/player-path");

        string name;
        token_name->view() >> name;
        info.setName(name);
		TokenView view = token_levels->view();
        while (view.hasMore()){
            const Token * next;
            view >> next;
            Debug::debug(1,__FUNCTION__) << "Add level " << next->getName() << endl;
            info.addLevel(next->getName());
        }

    } catch (const CTokenException & e){
        Debug::debug( 0 ,__FUNCTION__) << "Error while reading level set: " << e.getTrace() << endl;
    }

    return info;
}

#if 0
CLevelInfo readLevels( const string & filename ){
    CLevelInfo info;
    try{
        TokenReader tr( filename );
        Token * head = tr.readToken();

        readName(&info, head->findToken("level-set/name"));
        readLevels(&info, head->findToken("level-set/levels"));
        readPlayerPath(&info, head->findToken("level-set/player-path"));

        /*
        if ( *head == "levels" ){
            while (head->hasTokens()){
                Token * next;
                *head >> next;
                / * old way * /
                if (!next->hasTokens()){
                    Debug::debug(1,__FUNCTION__) << "Add level " << next->getName() << endl;
                    info.addLevel(next->getName());
                } else if (*next == "level"){
                } else if (*next == "player-path"){
                    string s;
                    *next >> s;
                    Debug::debug(1,__FUNCTION__) << "Set player path to " << s << endl;
                    info.setPlayerPath(s);
                }
            }
        }
        */

        return info;

    } catch ( const CTokenException & lex ){
        Debug::debug( 0,__FUNCTION__ ) << "Could not load " << filename << ". Reason: " << lex.getTrace() << endl;
        return info;
    }
}
#endif

}
} //end SGF
