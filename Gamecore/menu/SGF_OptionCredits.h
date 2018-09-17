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
#ifndef _option_credits_h
#define _option_credits_h

#include <vector>
#include <locale.h>
#include "../SGF_Config.h"
#include "../graphics/all.h"
#include "SGF_MenuOption.h"
#include "SGF_MenuV2.h"
#include "SGF_MenuGlobal.h"
#include "../SGF_Global.h"
#include "../util/SGF_Util.h"
#include "../util/SGF_Debug.h"
#include "../util/SGF_FontSystem.h"
#include "../resource/all.h"


using namespace std;
namespace SGF {

class Token;
class CBitmap;
namespace Menu {
	class CMenuOption;
/*! Handles key reconfiguration */
class  SGE_API COptionCredits : public CMenuOption {
public:
    enum CreditKey{
        Exit
    };

		// Do logic before run part
		virtual void logic();

		// Finally it has been selected, this is what shall run
		// endGame will be set true if it is a terminating option
		//virtual void run(bool &endGame);
		virtual void run(const Menu::CContext &);

		COptionCredits(const Gui::CContextBox & parent,const Token *token)throw( CLoadException );

		virtual ~COptionCredits();
	private:
		Filesystem::CRelativePath background; //v2
		CBitmap *background_bitmap; //v1
		vector<string> credits;
		string music;
		 Colors::ColorDefinition color, title;
        CInputMap<CreditKey> input;
};
}
} //end SGF
#endif

