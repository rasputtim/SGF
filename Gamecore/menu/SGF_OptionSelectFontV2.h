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
#ifndef _select_font_v2_h
#define _select_font_v2_h

#include <vector>
#include "../SGF_Config.h"
#include "SGF_MenuOption.h"
#include "../exceptions/all.h"

#include "SGF_MenuV2.h"
using namespace std;
namespace SGF {

class Token;
namespace Menu {
	class CMenuOption;
/*! Handles font selection */
/*! Handles font selection */
class  SGE_API COptionSelectFont_v2 : public CMenuOption {
public:
    COptionSelectFont_v2(const Gui::CContextBox & parent,const Token *token) throw(CLoadException);

    virtual void open();
    virtual void close();

    // Do logic before run part
    virtual void logic();

    // Finally it has been selected, this is what shall run
    // endGame will be set true if it is a terminating option
    virtual void run(const Menu::CContext &);
	//virtual void run(bool &endGame) {} // compatibilidade com a vers�o V1
	virtual void load(const Token *token)throw( CLoadException ) {};
    // This is to pass paramaters to an option ie a bar or something
    virtual bool leftKey();
    virtual bool rightKey();

    virtual ~COptionSelectFont_v2();

protected:

private:
    // Type of selector
    enum Adjust{
      fontName=0,
      fontHeight,
      fontWidth
    };
    // Current type of menu to adjust
    Adjust typeAdjust;

    int lblue, lgreen;
    int rblue, rgreen;

    vector<Util::CReferenceCount<CFontInfo> > fonts;

    void nextIndex(bool forward);

};
}
} //end SGF
#endif

