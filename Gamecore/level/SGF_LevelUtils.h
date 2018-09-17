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
#ifndef _level_utils_h
#define _level_utils_h

#include <string>
#include <vector>
#include "../util/SGF_Token.h"
#include "../SGF_Config.h"
namespace SGF{

class Token;
class CBitmap;

namespace Level{

class  SGE_API CLevelInfo{
public:
    CLevelInfo();
    CLevelInfo(const CLevelInfo & info);

    CLevelInfo & operator=(const CLevelInfo & info);

    virtual void addLevel(const string & s);
    virtual const vector<string> & getLevels() const;
    virtual const string & loadingMessage() const;
    virtual const string & loadingBackground() const;
    virtual const string & getPlayerPath() const;
    virtual void setPosition(int x, int y);

    virtual inline int getPositionX() const {
        return x;
    }

    virtual inline int getPositionY() const {
        return y;
    }

    virtual inline void setBackground(const CBitmap * background){
        this->background = background;
    }

    virtual inline const CBitmap * getBackground() const {
        return this->background;
    }

    virtual void setLoadingMessage(const string & str);

    /* descriptive name of this set of levels */
    virtual const string & getName() const;
    virtual void setPlayerPath(const string & s);
    virtual void setName(const string & s);

    virtual ~CLevelInfo();

protected:
    vector<string> levels;
    string playerPath;
    string name;
    string _loadingMessage;
    string _loadingBackground;
    const CBitmap * background;

    int x, y;
};

// CLevelInfo readLevels(const string & filename);
CLevelInfo readLevel(const Token * level);

//todo
//Loader::Info convert(const LevelInfo & info);


}
} //end SGF
#endif
