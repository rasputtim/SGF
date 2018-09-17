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
#ifndef _gui_scroll_list_h
#define _gui_scroll_list_h

#include <string>
#include <vector>
#include "../SGF_Config.h"
#include "SGF_Coordinate.h"

#include "../util/SGF_Pointer.h"
#include "../util/SGF_Util.h"

namespace SGF{
class CFont;

namespace Gui{

enum Justify{
    LeftJustify,
    RightJustify,
    CenterJustify
};


/**
 * \class CScrollItem
 *
 * \ingroup SGF_Gui
 * 
 * \brief Item da caixa de Scroll
 *
 * \note Classe Puramente Virtual
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CScrollItem{
public:
    CScrollItem();

    
	/** 
	* distance significa quão longe do item selecionado nós estamos.
	* 0 significa que é o item selecionado
	* distance pode ser negativa ou positiva
	*/
    virtual void draw(int x, int y, const CBitmap & where, const CFont & font, int distance) const = 0;

    /* size in pixels, used for justification */
    virtual int size(const CFont & font) const = 0;

    virtual ~CScrollItem();
};


/**
 * \class CScrollListInterface
 *
 * \ingroup SGF_Gui
 * 
 * \brief Classe Base da Interface de Scroll
 *
 * \note Classe Puramente Virtual
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CScrollListInterface{
public:
    CScrollListInterface();
    virtual ~CScrollListInterface();

    //! Logic
    virtual void act() = 0;

    //! Render
    virtual void render(const CBitmap &, const CFont & font) const = 0;

    //! Add item
    virtual void addItem(const Util::CReferenceCount<CScrollItem> item) = 0;

    //! Add vector of text
    virtual void addItems(const vector<Util::CReferenceCount<CScrollItem> > & items) = 0;
    
    //! Get vector of text
    virtual const vector<Util::CReferenceCount<CScrollItem> > & getItems() const = 0;
    
    virtual void clearItems() = 0;
    
    virtual unsigned int getCurrentIndex() const = 0;

    virtual bool next() = 0;

    //! Previous
    virtual bool previous() = 0;
    
    //! Set wrap
    virtual inline void setWrap(bool wrap){
        this->allowWrap = wrap;
    }
    
    //! Get wrap
    virtual inline bool getWrap() const {
        return this->allowWrap;
    }
    //! Number of Intens

	virtual int getNumberOfItens() =0;
protected:
    
    //! Is wrappable
    bool allowWrap;

};

/**
 * \class CScrollList
 *
 * \ingroup SGF_Gui
 * 
 * \brief Lista de Scroll
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CScrollList: public CScrollListInterface {
public:
    CScrollList();

    CScrollList(const CScrollList &);

    virtual ~CScrollList();

    //! copy
    CScrollList & operator=(const CScrollList &);

    //! Logic
    virtual void act();

    //! Render
    virtual void render(const CBitmap &, const CFont & font) const;

    //! Add item
    virtual void addItem(const Util::CReferenceCount<CScrollItem> item);

    //! Add vector of text
    virtual void addItems(const vector<Util::CReferenceCount<CScrollItem> > & items);
    
    virtual const vector<Util::CReferenceCount<CScrollItem> > & getItems() const;

    virtual void clearItems();
    
    //! Set Position
    virtual void setPosition(const Gui::CCoordinate &);
    
    //! Set font spacing
    inline virtual void setFontSpacing(int x, int y){
        this->fontSpacingX = x;
        this->fontSpacingY = y;
    }
    
    //! Set font spacing X
    inline virtual void setFontSpacingX(int x){
        this->fontSpacingX = x;
    }
    
    //! Set font spacing X
    inline virtual void setFontSpacingY(int y){
        this->fontSpacingY = y;
    }

    //! Next
    virtual bool next();

    //! Previous
    virtual bool previous();

    //! Set current index
    virtual bool setCurrentIndex(unsigned int index);
    
    //! Get current index
    virtual inline unsigned int getCurrentIndex() const {
        return this->currentIndex;
    }

    /*
    //! Set gradient
    virtual inline void setGradient(bool use){
	this->useGradient = use;
    }
    
    //! Get gradient
    virtual inline bool gradientActive() const {
	return this->useGradient;
    }
    */
    virtual inline double getScrollMotion() const {
        return scrollMotion;
    }

    virtual inline void setScrollMotion(double what){
        if (what < 1.01){
            what = 1.01;
        }
        scrollMotion = what;
    }

    virtual inline void setScrollWaitTime(int what){
        scrollWaitTime = what;
    }

    virtual inline int getScrollWaitTime() const {
        return scrollWaitTime;
    }
    
    //! Set highlight
    virtual inline void setHighlight(bool use){
        this->useHighlight = use;
    }
    
    //! Get highlight
    virtual inline bool highlightActive() const {
        return this->useHighlight;
    }
    
    virtual inline void setJustification(Justify what){
        this->justification = what;
    }
    
	virtual int getNumberOfItens(){ return text.size();}

private:
    /* smooth drawing */
    void doDraw(int x, int y, int min_y, int max_y, const CFont & font, int current, int selected, const CBitmap & area, int direction) const;

    //! Text
    vector<Util::CReferenceCount<CScrollItem> > text;

    //! Current index
    unsigned int currentIndex;

    //! Coordinates (size of)
    Gui::CCoordinate position;

    //! Font Spacing
    int fontSpacingX, fontSpacingY;

    //! Current position for smooth scrolling
    int currentPosition;

    //! Scroll wait
    int scrollWait;
    int scrollWaitTime;

    /* speed at which the menu scrolls */
    double scrollMotion;

    //! Gradient for selected cursor
    // Effects::Gradient selectedGradient;

    //! Use gradient
    // bool useGradient;

    //! Use highlight
    bool useHighlight;

    /* how much to scroll by */
    double scroll;

    Justify justification;
};


/**
 * \class CNormalList
 *
 * \ingroup SGF_Gui
 * 
 * \brief Lista de Scroll Normalizada
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CNormalList: public CScrollListInterface {
public:
    CNormalList();
    virtual ~CNormalList();

    //! Logic
    virtual void act();

    //! Render
    virtual void render(const CBitmap &, const CFont & font) const;

    //! Add item
    virtual void addItem(const Util::CReferenceCount<CScrollItem> item);

    //! Add vector of text
    virtual void addItems(const vector<Util::CReferenceCount<CScrollItem> > & items);
    
    virtual const vector<Util::CReferenceCount<CScrollItem> > & getItems() const;

    virtual void clearItems();
    
    virtual unsigned int getCurrentIndex() const;

    virtual bool next();
    virtual bool previous();
    
    virtual inline void setJustification(Justify what){
        this->justification = what;
    }
	virtual int getNumberOfItens(){ return text.size();}
protected:
    virtual void checkEndPosition();
    virtual bool allItemsViewable();
    
    vector<Util::CReferenceCount<CScrollItem> > text;
    int position;
    mutable int endPosition;
    mutable int first, last;
    Justify justification;
    mutable double fontHeight;
    double moveToX, moveToY;
    double currentX, currentY;
    int fontBeginOffsetX, fontBeginOffsetY;
    int fontSpaceX, fontSpaceY;
    mutable int visibleItems;
};

}
} //end SGF
#endif
