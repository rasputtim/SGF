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
#ifndef _S_G_F_menu_option_h
#define _S_G_F_menu_option_h

#include <string>
#include <vector>
#include "../SGF_Config.h"
#include "../gui/SGF_Box.h"
#include "../gui/SGF_ContextBox.h"
#include "../exceptions/all.h"
#include "../util/SGF_LanguageString.h"


using namespace std;
namespace SGF{

class CBitmap;
class Token;
class CMenuAnimation;
namespace Gui {
	class CContentItem;
}

namespace Menu {
	class CContext;
	class CMenu;
//	class CMenu_v1;
	class CMenu_v2;


class  SGE_API CMenuOption: public Gui::CContextItem{
public:
    /* called when the menu containing this option is displayed to the user.
     * default behavior is to do nothing.
     */
    virtual void open();

    /* called when the menu containing this option returns.
     * default behavior is to do nothing.
     */
    virtual void close();


	// Do logic before run part
    virtual void logic()=0;

    // Do drawing or animations below text... If this is overridden need to cylce through the animations if useage is planned
    //virtual void drawBelow(CBitmap *work);

    // do draw or animations above text
    //virtual void drawAbove(CBitmap *work);

    // Finally it has been selected, this is what shall run
    // endGame will be set true if it is a terminating option
    //virtual void run(bool &endGame) = 0;
	virtual void run(const Menu::CContext &) = 0;
	virtual void load(const Token *token) throw( CLoadException ) = 0;

    // This is to pass paramaters to an option ie a bar or something
    // return true to pause key input
    virtual bool leftKey();
    virtual bool rightKey();

    // Reset animations
    //virtual void resetAnimations();

    // Update animations This is called regardless and only when the option is active
    //virtual void updateAnimations();

    //! Set parent
    virtual void setParent(Menu::CMenu *menu);

    enum state
    {
        Selected = 0,
        Deselected,
        Run
    };

    enum OptionType{
        Event = 0,
        COption,
        AdjustableOption
    };

    //CMenuOption(const Token *token, const OptionType t = COption, const string xmlDefFile="") throw(CLoadException);
    CMenuOption(const Gui::CContextBox & parent, const Token *token, const string xmlDefFile="") throw(CLoadException);


    virtual ~CMenuOption();
public:
    inline const string getName(){ return this->getText(); }

protected:

    //! This is the owner of this option
    Menu::CMenu *parent;
private:
    state currentState;
    OptionType mType;
    CLanguageString text;
    CLanguageString infoText;
    //CBitmap *bmp;
    //int adjustLeftColor;
    //int adjustRightColor;
    bool runnable;
    //bool forRemoval;
	string xmlDefFile;
    // Image resource for use in individual options
    //vector<CMenuAnimation *>backgroundAnimations;
    //vector<CMenuAnimation *>foregroundAnimations;
public:

	inline string getDefFile() const{ return xmlDefFile;}
    inline void setState(const state s) { currentState = s; }
    inline state getState() const { return currentState; }
    inline void setType(const OptionType t) { mType = t; }
    inline OptionType getType() const { return mType; }
    //inline void setText(const CLanguageString & t) { text = t; }
    //virtual inline string getText() const { return text.get(); }
    inline void setInfoText(const CLanguageString &t) { infoText = t; }
    inline string getInfoText(){ return infoText.get(); }
    //inline void setBitmap(CBitmap *b) { bmp = b; }
    //inline CBitmap *GetBitmap() const { return bmp; }
    //inline void setLeftAdjustColor(int c) { adjustLeftColor = c; }
    //inline int getLeftAdjustColor() const { return adjustLeftColor; }
    //inline void setRightAdjustColor(int c) { adjustRightColor = c; }
    //inline int getRightAdjustColor() const { return adjustRightColor; }
    inline void setRunnable(const bool r) { runnable = r; }
    inline bool isRunnable() const { return runnable; }
    //inline void setForRemoval(const bool r) { forRemoval = r; }
    //inline bool scheduledForRemoval() const { return forRemoval; }
    //inline Menu::CMenu *getParent() const { return parent; }
	//inline const CLanguageString & getLanguageText() const { return text; }
public:
    const string getName() const;
protected:
    void readName(const Token * token) throw(CLoadException);
    void readInfo(const Token * token) throw (CLoadException);
};
}
} //end SGF
#endif
