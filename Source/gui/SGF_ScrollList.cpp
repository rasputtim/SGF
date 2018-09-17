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
#include "gui/SGF_ScrollList.h"
#include "util/SGF_FontSystem.h"
#include <math.h>

using namespace std;
namespace SGF{

using namespace Gui;

static const double FONT_SPACER = 1.3;
// static const int GradientMax = 50;

const double EPSILON = 0.01;

/*
static int selectedGradientStart(){
    static int color = Graphics::makeColor(19, 167, 168);
    return color;
}

static int selectedGradientEnd(){
    static int color = Graphics::makeColor(27, 237, 239);
    return color;
}
*/

int justify(Justify justification, int left, int right, int size){
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN ("<<left<<" , " << right<<" , "  <<size <<") " <<endl;

    switch (justification){
        case LeftJustify: return left;
        case RightJustify: return right - size;
        case CenterJustify: return (left + right) / 2 - size / 2;
    }
    return 0;
}

CScrollListInterface::CScrollListInterface():
allowWrap(true){
}

CScrollListInterface::~CScrollListInterface(){
}

CScrollItem::CScrollItem(){
}

CScrollItem::~CScrollItem(){
}

CScrollList::CScrollList():
currentIndex(0),
fontSpacingX(0),
fontSpacingY(0),
currentPosition(0),
scrollWait(0),
scrollWaitTime(4),
scrollMotion(1.2),
// selectedGradient(GradientMax, selectedGradientStart(), selectedGradientEnd()),
// useGradient(false),
useHighlight(false),
scroll(0),
justification(CenterJustify){}

CScrollList::CScrollList(const CScrollList & copy):
currentIndex(copy.currentIndex),
fontSpacingX(copy.fontSpacingX),
fontSpacingY(copy.fontSpacingY),
currentPosition(copy.currentPosition),
scrollWait(copy.scrollWait),
// selectedGradient(GradientMax, selectedGradientStart(), selectedGradientEnd()),
// useGradient(copy.useGradient),
useHighlight(copy.useHighlight),
scroll(0){}

CScrollList::~CScrollList(){}

CScrollList & CScrollList::operator=(const CScrollList & copy){
    return *this;
}

void CScrollList::act(){
    if (scrollWait == 0){
        if (scroll > EPSILON){
            // scroll -= SCROLL_MOTION;
            scroll /= scrollMotion;
        } else if (scroll < -EPSILON){
            // scroll += SCROLL_MOTION;
            scroll /= scrollMotion;
        } else {
            scroll = 0;
            currentPosition = currentIndex;
        }
    } else {
        scrollWait -= 1;
    }

    /*
    if (scrollWait > 0){
        scrollWait -= 1;
    } else {
        currentPosition = currentIndex;
    }
    */
}


/* this is the smooth scroll stuff from context-box */
void CScrollList::doDraw(int x, int y, int min_y, int max_y, const CFont & font, int current, int selected, const CBitmap & area, int direction) const {
   	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN " <<endl;
    Debug::debug(Debug::gui,__FUNCTION__) << "PARAMETERS-------------------------------- " <<endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "x,y,min_y,max_y / "<<x<<" , " <<y<<" , " <<min_y<<" , " <<max_y <<endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "FONTE (name,type,[ADD]) / ( "<<" na "<<" , "<< font.getType()<<" , ["<<&font<<"])" <<endl;

	/* sanity check */
    if (text.size() == 0){
		Debug::debug(Debug::gui,__FUNCTION__) << "Text size = 0 - returning " <<endl;

        return;
    }

    while (y < max_y && y > min_y){
        /* circuluar */
        int pick = current;
        while (pick < 0){
            pick += text.size();
        }
        pick = pick % text.size();
		Debug::debug(Debug::gui,__FUNCTION__) << "Will take option " <<endl;

        Util::CReferenceCount<CScrollItem> option = text[pick];
		Debug::debug(Debug::gui,__FUNCTION__) << "Option taken" <<endl;

        /* center justification */
        const int startx = justify(justification, 1, area.getWidth() - 1, option->size(font));
		Debug::debug(Debug::gui,__FUNCTION__) << "Start X: "<< startx <<endl;

        /* the selected option will have a distance of 0 */
        int distance = current - selected;
		Debug::debug(Debug::gui,__FUNCTION__) << "distance: "<< distance <<endl;

        option->draw(x + startx, y, area, font, distance);

        if (text.size() == 1){
            return;
        }

        current += direction;
        y += direction * font.getHeight() / FONT_SPACER;
    }
		Debug::debug(Debug::gui,__FUNCTION__) << "END " <<endl;

}

void CScrollList::render(const CBitmap & where, const CFont & font) const {
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN " <<endl;

    /* middle of the bitmap offset by the scroll amount. */
    int y = where.getHeight() / 2 + scroll * font.getHeight() / 2 - font.getHeight() / 2;

    /* allow options to be drawn a little off the bitmap */
    int min_y = 0 - font.getHeight() / FONT_SPACER;
    int max_y = where.getHeight();

    /* draw down starting from the current selection */
    doDraw(0, y, min_y, max_y, font, currentIndex, currentIndex, where, 1);

    /* then draw up, skipping the current selection */
    doDraw(0, y - font.getHeight() / FONT_SPACER, min_y, max_y, font, currentIndex - 1, currentIndex, where, -1);
	Debug::debug(Debug::gui,__FUNCTION__) << "END " <<endl;

}

void CScrollList::addItem(const Util::CReferenceCount<CScrollItem> text){
    this->text.push_back(text);
}

void CScrollList::addItems(const vector<Util::CReferenceCount<CScrollItem> > & texts){
    this->text.insert(text.end(), texts.begin(), texts.end());
}

const vector<Util::CReferenceCount<CScrollItem> > & CScrollList::getItems() const{
    return this->text;
}

void CScrollList::clearItems(){
    this->text.clear();
}

void CScrollList::setPosition(const Gui::CCoordinate & location){
    this->position = location;
}

bool CScrollList::next(){
    /* FIXME: probably if the current index goes past the boundary we shouldn't scroll */
    currentIndex++;
    scroll = 1;
    if (scrollWait == 0){
        scrollWait = scrollWaitTime;
    }
    if (currentIndex >= text.size()){
        if (allowWrap){
            currentIndex = 0;
            return true;
        } else {
            currentIndex = text.size()-1;
            return false;
        }
    }
    return true;
}

bool CScrollList::previous(){
    scroll = -1;
    if (scrollWait == 0){
        scrollWait = scrollWaitTime;
    }
    if (currentIndex > 0){
        currentIndex--;
    } else if (currentIndex == 0){
        if (allowWrap){
            currentIndex = text.size()-1;
            return true;
        } else {
            return false;
        }
    }
    return true;
}

bool CScrollList::setCurrentIndex(unsigned int index){
    if (index >= text.size()){
        return false;
    }
    currentIndex = index;
    return true;
}

CNormalList::CNormalList():
position(0),
endPosition(0),
first(-1),
last(-1),
justification(CenterJustify),
fontHeight(0),
moveToX(0),
moveToY(0),
currentX(0),
currentY(0),
fontBeginOffsetX(0),
fontBeginOffsetY(0),
fontSpaceX(0),
fontSpaceY(0),
visibleItems(0){
}

CNormalList::~CNormalList(){
}

void CNormalList::act(){
    /* FIXME smooth scrolling needed (location/current?) */
    const int speed = fontHeight/2;
    if (currentY < moveToY){
        currentY += speed;
        if (currentY > moveToY){
            currentY = moveToY;
        }
    } else if (currentY > moveToY){
        currentY -= speed;
        if (currentY < moveToY){
            currentY = moveToY;
        }
    }
}

void CNormalList::render(const CBitmap & work, const CFont & font) const {
    	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN " <<endl;

	/* FIXME
     *  - Get spacing somewhere else, for now update it here
     *  - Get visible items properly elsewhere */
    fontHeight = (font.getHeight() / FONT_SPACER) + fontSpaceY;
    visibleItems = (work.getHeight() / fontHeight);
    if (first == -1){
        first = 0;
        last = Util::min(visibleItems, text.size());
    }
    if (position < first){
        int difference = first - position;
        first = 0;
        last -= difference;
    }
    if (position > last){
        int difference = position - last;
        last = position;
        first += difference;
    }
    first = 0;
    last = text.size();

    double y = currentY;
    for (int index = first; index < last; index += 1){
        int distance = position - index;
        Util::CReferenceCount<CScrollItem> option = text[index];
        const int x = justify(justification, 1, work.getWidth() - 1, option->size(font));
        option->draw(x, y, work, font, distance);
        y += fontHeight;
    }
	Debug::debug(Debug::gui,__FUNCTION__) << "END " <<endl;

}

void CNormalList::addItem(const Util::CReferenceCount<CScrollItem> item){
    text.push_back(item);
}

void CNormalList::addItems(const vector<Util::CReferenceCount<CScrollItem> > & texts){
    this->text.insert(text.end(), texts.begin(), texts.end());
}

const vector<Util::CReferenceCount<CScrollItem> > & CNormalList::getItems() const{
    return this->text;
}

void CNormalList::clearItems(){
    this->text.clear();
}

unsigned int CNormalList::getCurrentIndex() const {
    return position;
}

bool CNormalList::next(){
    // First move forward check if endpostition has been set
    checkEndPosition();
    if ((unsigned int)position < text.size() - 1){
        position += 1;
        if (allItemsViewable()){
            if (position > endPosition){
                moveToY-=fontHeight;
                endPosition++;
            }
        }
        return true;
    } else {
        if (allowWrap){
            position = 0;
            if (allItemsViewable()){
                endPosition = visibleItems-1;
                moveToY = 0;
            }
            return false;
        }
    }
    return false;
}

bool CNormalList::previous(){
    if (position > 0){
        position -= 1;
        if (allItemsViewable()){
            if (position < (endPosition - visibleItems+1)){
                moveToY+=fontHeight;
                endPosition--;
            }
        }
        return true;
    } else {
        if (allowWrap){
            position = text.size()-1;
            if (allItemsViewable()){
                endPosition = position;
                moveToY = ((position - visibleItems+1) * fontHeight) * -1;
            }
            return false;
        }
    }
    return false;
}

void CNormalList::checkEndPosition(){
    if (endPosition == 0){
        endPosition = visibleItems-1;
    }
}

bool CNormalList::allItemsViewable(){
    return ((unsigned int)visibleItems < text.size());
}
} //end SGF