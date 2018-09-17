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
#include "gui/SGF_ContextBox.h"
#include "util/SGF_FontSystem.h"
#include "resource/SGF_ResourceManager.h"

using namespace std;
namespace SGF {
static const double FONT_SPACER = 1.3;
static const int GradientMax = 50;

static Colors::ColorDefinition selectedGradientStart(){
    static Colors::ColorDefinition color = { 19, 167, 168, 255 } ;
    return color;
}

static Colors::ColorDefinition  selectedGradientEnd(){
    static Colors::ColorDefinition  color = { 27, 237, 239, 255 } ;
    return color;
}

using namespace std;
namespace Gui{

Effects::Gradient standardGradient(int max){
    Effects::Gradient standard(max, selectedGradientStart(), selectedGradientEnd());
    return standard;
}

Effects::Gradient modifiedGradient(Colors::ColorDefinition low, Colors::ColorDefinition high, int max){
    Effects::Gradient modified(max, low, high);
    return modified;
}


CListValues::CListValues():
interpolate(true),
lowColor(selectedGradientStart()),
highColor(selectedGradientEnd()),
maxGradient(GradientMax),
selectedColor(selectedGradientStart()),
selectedAlpha(255),
otherColor(Colors::White),
otherAlpha(255),
distanceFadeMultiplier(35),
fade(true){
}

CListValues::CListValues(const CListValues & copy):
interpolate(copy.interpolate),
lowColor(copy.lowColor),
highColor(copy.highColor),
maxGradient(copy.maxGradient),
selectedColor(copy.selectedColor),
selectedAlpha(copy.selectedAlpha),
otherColor(copy.otherColor),
otherAlpha(copy.otherAlpha),
distanceFadeMultiplier(copy.distanceFadeMultiplier),
fade(copy.fade){
}

CListValues::~CListValues(){
}

const CListValues & CListValues::operator=(const CListValues & copy){
    interpolate = copy.interpolate;
    lowColor = copy.lowColor;
    highColor = copy.highColor;
    maxGradient = copy.maxGradient;
    selectedColor = copy.selectedColor;
    selectedAlpha = copy.selectedAlpha;
    otherColor = copy.otherColor;
    otherAlpha = copy.otherAlpha;
    distanceFadeMultiplier = copy.distanceFadeMultiplier;
    fade = copy.fade;

    return *this;
}

static Uint8 clamp(Uint8 in, Uint8 low = 0, Uint8 high = 255){
    return static_cast<Uint8>(Util::clamp(static_cast<int>(in),static_cast<int>(low),static_cast<int>(high)));
}


void CListValues::getValues(const Token * token){
    TokenView view = token->view();
    while (view.hasMore()){
        const Token * token;
        view >> token;
        try{
            Uint8 red = 0, green = 0, blue = 0, alpha = 0, gradient=1;
            if (token->match("interpolate-selected", interpolate)){
            } else if (token->match("color-low", red, green, blue)){
				Colors::ColorDefinition tempColor = {clamp(red), clamp(green), clamp(blue),255};
				lowColor = tempColor;

            } else if (token->match("color-high", red, green, blue)){
                Colors::ColorDefinition tempColor = {clamp(red), clamp(green), clamp(blue),255};
				highColor =  tempColor;
            } else if (token->match("interpolate-distance", gradient)){
                maxGradient = clamp(gradient, 1, 1000);
            } else if (token->match("selected-color", red, green, blue)){
                Colors::ColorDefinition tempColor = {clamp(red), clamp(green), clamp(blue),255};
				selectedColor =  tempColor;
            } else if (token->match("selected-color-alpha", alpha)){
                selectedAlpha = clamp(alpha);
            } else if (token->match("other-color", red, green, blue)){
                Colors::ColorDefinition tempColor = {clamp(red), clamp(green), clamp(blue),255};
				otherColor =  tempColor;
            } else if (token->match("other-color-alpha", alpha)){
                otherAlpha = clamp(alpha);
            } else if (token->match("distance-fade-multiplier", distanceFadeMultiplier)){
            } else if (token->match("distance-fade", fade)){
            }
        } catch (const CTokenException & ex){
            // Output something
        }
    }
}




/*
CContextItem::CContextItem(){
}
*/
CContextItem::CContextItem(const string & name, const CContextBox & parent):
text(name),
parent(parent){
}

void CContextItem::draw(int x, int y, const CBitmap & where, const CFont & font, int distance) const {
  	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN " <<endl;

	if (distance == 0){ //* 0 significa que é o item selecionado
        if (parent.getListValues().getInterpolate()){
            CBitmap::transBlender(0, 0, 0, parent.getFadeAlpha());
			font.drawText(x, y, parent.getSelectedColor(), where.translucent(), getText().c_str(), 0);
        } else {
            CBitmap::transBlender(0, 0, 0, parent.getListValues().getSelectedAlpha());
			font.drawText(x, y, parent.getListValues().getSelectedColor(), where.translucent(), getText().c_str(), 0);
        }
    } else {
        if (parent.getListValues().getDistanceFade()){
            int alpha = parent.getListValues().getOtherAlpha() - fabs((double) distance) * parent.getListValues().getDistanceFadeMultiplier();
            alpha = clamp(alpha);
            CBitmap::transBlender(0, 0, 0, alpha);
			font.drawText(x, y, parent.getListValues().getOtherColor(), where.translucent(), getText().c_str(), 0);
        } else {
            CBitmap::transBlender(0, 0, 0, parent.getListValues().getOtherAlpha());
			font.drawText(x, y, parent.getListValues().getOtherColor(), where.translucent(), getText().c_str(), 0);
        }
    }
	//CBitmap *t=NULL;
	//t->clear();

}

void CContextItem::setText(const CLanguageString & t){
    text = t;
}

int CContextItem::size(const CFont & font) const {

  return font.getTextLength(getText().c_str())+5;

}


CContextItem::~CContextItem(){
}


void CContextBox::setList(const vector<Util::CReferenceCount<CContextItem> > & list){
    this->list->clearItems();
    for (vector<Util::CReferenceCount<CContextItem> >::const_iterator it = list.begin(); it != list.end(); it++){
        const Util::CReferenceCount<CContextItem> & item = *it;
        this->list->addItem(item);
    }
}

void CContextBox::addItem(const Util::CReferenceCount<CContextItem> & item){
    this->list->addItem(item);
}

void CContextBox::setListType(const ListType & type){
    switch (type){
        case Normal:{
            Util::CReferenceCount<CScrollListInterface> newList(new CNormalList());
            newList->addItems(list->getItems());
            list = newList;
            break;
        }
        case Scroll:{
            Util::CReferenceCount<CScrollListInterface> newList(new CScrollList());
            newList->addItems(list->getItems());
            list = newList;
            break;
        }
        default:
            break;
    }
}

void CContextBox::setListWrap(bool wrap){
    list->setWrap(wrap);
}

CContextBox::CContextBox():
fadeState(NotActive),
list(new CScrollList()),
fadeSpeed(12),
fadeAlpha(0),
cursorCenter(0),
cursorLocation(0),
scrollWait(4),
selectedGradient(standardGradient(GradientMax)),
renderOnlyText(false){
}
CContextBox::CContextBox( const CContextBox & copy ):
fadeState(NotActive),
list(new CScrollList()),
selectedGradient(standardGradient(GradientMax)),
renderOnlyText(false){
    /*
    this->font = copy.font;
    this->fontWidth = copy.fontWidth;
    this->fontHeight = copy.fontHeight;
    */
    this->list = copy.list;
    this->fadeSpeed = copy.fadeSpeed;
    this->fadeAlpha = copy.fadeAlpha;
    this->cursorCenter = copy.cursorCenter;
    this->cursorLocation = copy.cursorLocation;
    this->scrollWait = copy.scrollWait;
    this->useGradient = copy.useGradient;
    this->renderOnlyText = copy.renderOnlyText;
}
CContextBox::~CContextBox(){
}
CContextBox & CContextBox::operator=( const CContextBox & copy){
    this->fadeState = NotActive;
    /*
    this->font = copy.font;
    this->fontWidth = copy.fontWidth;
    this->fontHeight = copy.fontHeight;
    */
	 this->list = copy.list;
    this->fadeSpeed = copy.fadeSpeed;
    this->fadeAlpha = copy.fadeAlpha;
    this->cursorCenter = copy.cursorCenter;
    this->cursorLocation = copy.cursorLocation;
    this->scrollWait = copy.scrollWait;
    this->useGradient = copy.useGradient;
    this->renderOnlyText = copy.renderOnlyText;
    return *this;
}

void CContextBox::act(const CFont & font){
    // update board
    boardBox.act(font);


    // do fade
    doFade();

    // Update gradient
    selectedGradient.update();
}

void CContextBox::render(const CBitmap & work){
}

void CContextBox::render(const CBitmap & work, const CFont & font){
	Debug::debug(Debug::menu,__FUNCTION__) << "Will Render The Box  " <<  endl;

    if (!renderOnlyText){
	  boardBox.render(work);
    }
	// Set clipping so that text won't go beyond it's boundaries
    //work.setClipRect(boardBox.location.getX()+2, boardBox.location.getY()+2,boardBox.location.getX2()-2,boardBox.location.getY2()-2);

	Debug::debug(Debug::menu,__FUNCTION__) << "Will Render The Text  " <<  endl;
    drawText(work, font);

}

bool CContextBox::next(const CFont & font){
    if (fadeState == FadeOut){
	return false;
    }
	 list->next();

    return true;

}

bool CContextBox::previous(const CFont & font){
    if (fadeState == FadeOut){
	return false;
    }

       list->previous();

    return true;
}

Colors::ColorDefinition CContextBox::getSelectedColor() const {
    return values.getInterpolate() ? selectedGradient.current() : values.getSelectedColor();
}

void CContextBox::setListValues(const Gui::CListValues & values){
    this->values = values;
    selectedGradient = modifiedGradient(values.getLowColor(), values.getHighColor(), values.getMaxGradient());
}

void CContextBox::adjustLeft(){
}

void CContextBox::adjustRight(){
}

void CContextBox::open(){
    Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN" << endl;
	// Set the fade stuff
    fadeState = FadeIn;
    //board.position = position;
	Debug::debug(Debug::gui,__FUNCTION__) << "Set CPopupBox Coordinates (x,y) " << location.getX()<<" , " << location.getY()<< endl;
    boardBox.location = location;
	boardBox.transforms = transforms;
    boardBox.colors = colors;
    Debug::debug(Debug::gui,__FUNCTION__) << "1 - Seted up CPopupBox Coordinates (x,y) " << boardBox.location.getX()<<" , " << boardBox.location.getY()<< endl;
	boardBox.open();
    fadeAlpha = 0;
    cursorLocation = 0;
	Debug::debug(Debug::gui,__FUNCTION__) << "2 - Seted up CPopupBox Coordinates (x,y) " << boardBox.location.getX()<<" , " << boardBox.location.getY()<< endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "END" << endl;
}

void CContextBox::close(){
    fadeState = FadeOut;
    boardBox.close();
    fadeAlpha = 255;
    cursorLocation = 480;
}


void CContextBox::doFade(){
    switch ( fadeState ){
	case FadeIn: {
	    if (fadeAlpha < 255){
		fadeAlpha += (fadeSpeed+2);
	    }

	    if (fadeAlpha >= 255){
		fadeAlpha = 255;
                if (boardBox.isActive()){
                    fadeState = Active;
                }
	    }
	    break;
	}
	case FadeOut: {
	    if (fadeAlpha > 0){
		fadeAlpha -= (fadeSpeed+2);
	    }

	    if (fadeAlpha <= 0){
		fadeAlpha = 0;
                if (!boardBox.isActive()){
                    fadeState = NotActive;
                }
	    }
	    break;
	}
	case Active:
	case NotActive:
	default:
	    break;
    }
}
#if 0
void CContextBox::calculateText(const CFont & vFont){
    if (contextItemVector.empty()){
        return;
    }

    // const CFont & vFont = CFont::getFont(font, fontWidth, fontHeight);

    cursorCenter = (location.getY() + (int)location.getHeight()/2) - vFont.getHeight()/2;//(position.y + (int)position.height/2) - vFont.getHeight()/2;

    if (cursorLocation == cursorCenter){
        scrollWait = 4;
    } else {
	if (scrollWait <= 0){
	    cursorLocation = (cursorLocation + cursorCenter)/2;
	    scrollWait = 4;
	} else {
	    scrollWait--;
	}
    }
}
#endif

void CContextBox::drawText(const CBitmap & bmp, const CFont & vFont){
    const int x1 = boardBox.getArea().getX()+(int)(boardBox.getTransforms().getRadius()/2);
    const int y1 = boardBox.getArea().getY()+2;//(board.getArea().radius/2);
    const int x2 = boardBox.getArea().getX2()-(int)(boardBox.getTransforms().getRadius()/2);
    const int y2 = boardBox.getArea().getY2()-2;//(board.getArea().radius/2);

    CBitmap area(bmp, x1, y1, x2 - x1, y2 - y1);

    list->render(area, vFont);
#if 0
	Debug::debug(Debug::gui,__FUNCTION__) << "=========================================" << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN  Context Vector Not Empty" <<  endl;
	// const CFont & vFont = CFont::getFont(font, fontWidth, fontHeight);
    bmp.setBitmapMode(CBitmap::DRAW_TYPE_TEXTURE);
	const int x1 = boardBox.getArea().getX()+(int)(boardBox.getArea().getRadius()/2);
    const int y1 = boardBox.getArea().getY()+2;//(board.getArea().radius/2);
    const int x2 = boardBox.getArea().getX2()-(int)(boardBox.getArea().getRadius()/2);
    const int y2 = boardBox.getArea().getY2()-2;//(board.getArea().radius/2);
    Debug::debug(Debug::menu,__FUNCTION__) << "location: " << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location X1: " << x1<< endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location Y1: " << y1 << endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location X2: " << x2<< endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "location Y2: " << y2<< endl;
	Debug::debug(Debug::gui,__FUNCTION__) << "=========================================" << endl;

	bmp.setClipRect(location.getX(), location.getY(), location.getX2(),location.getY2());


	int locationY = cursorLocation;
    int currentOption = current;
    int count = 0;
    while (locationY < location.getX2() + vFont.getHeight()){
        const int startx = (location.getWidth()/2)-(vFont.textLength(contextItemVector[currentOption]->getName().c_str())/2);
        if (count == 0){
            CBitmap::transBlender(0, 0, 0, fadeAlpha);
            CTranslucentBitmap translucent(bmp);
            // CBitmap::drawingMode( CBitmap::MODE_TRANS );
            const int color = useGradient ? selectedGradient.current_intcolor() : selectedGradientStart();

			if (location.getY() <= locationY && (location.getY2()- vFont.getHeight()) >= locationY) vFont.printf(location.getX() + startx, locationY, color, translucent, contextItemVector[currentOption]->getName(), 0 );

		// CBitmap::drawingMode( CBitmap::MODE_SOLID );
			 if (contextItemVector[currentOption]->isAdjustable()){
                const int triangleSize = 14;
                int cx = (location.getX() + startx) - 15;
                int cy = (int)(locationY + (vFont.getHeight()/FONT_SPACER) / 2 + 2);

                /*
                int cx1 = cx + triangleSize / 2;
                int cy1 = cy - triangleSize / 2;
                int cx2 = cx - triangleSize;
                int cy2 = cy;
                int cx3 = cx + triangleSize / 2;
                int cy3 = cy + triangleSize / 2;
                */

                /* do the triangles need to be translucent? */
                // translucent.triangle(cx1, cy1, cx2, cy2, cx3, cy3, context[currentOption]->getLeftColor());
                translucent.equilateralTriangle(cx, cy, 180, triangleSize, contextItemVector[currentOption]->getLeftColor());

                cx = (location.getX()+startx + vFont.textLength(contextItemVector[currentOption]->getName().c_str()))+15;
                translucent.equilateralTriangle(cx, cy, 0, triangleSize, contextItemVector[currentOption]->getLeftColor());
                // translucent.triangle( cx - triangleSize / 2, cy - triangleSize / 2, cx + triangleSize, cy, cx - triangleSize / 2, cy + triangleSize / 2, context[currentOption]->getRightColor() );
            }
            // CBitmap::drawingMode(CBitmap::MODE_SOLID);
        } else {
            int textAlpha = fadeAlpha - (count * 35);
            if (textAlpha < 0){
                textAlpha = 0;
            }
            CBitmap::transBlender(0, 0, 0, textAlpha);
            // CBitmap::drawingMode( CBitmap::MODE_TRANS );
            int color = CBitmap::makeColor(255,255,255);
			if (location.getY() <= locationY && (location.getY2()- vFont.getHeight()) >= (locationY)) vFont.printf(location.getX() + startx, locationY, color, bmp.translucent(), contextItemVector[currentOption]->getName(), 0 );

		// CBitmap::drawingMode( CBitmap::MODE_SOLID );
			// CBitmap::drawingMode( CBitmap::MODE_SOLID );
        }
        if (contextItemVector.size() == 1){
            bmp.setClipRect(0, 0, bmp.getWidth(), bmp.getHeight());
            return;
        }
        currentOption++;
        if (currentOption == (int)contextItemVector.size()){
            currentOption = 0;
        }
        locationY += (int)(vFont.getHeight()/FONT_SPACER);
        count++;
        /*if (context.size() < 2 && count == 2){
            break;
        }*/
    }
    locationY = cursorLocation - (int)(vFont.getHeight()/FONT_SPACER);
    currentOption = current;
    currentOption--;
    count = 0;
    while (locationY > location.getX() - vFont.getHeight()){
        if (currentOption < 0){
            currentOption = contextItemVector.size()-1;
        }
        const int startx = (location.getWidth()/2)-(vFont.textLength(contextItemVector[currentOption]->getName().c_str())/2);
        int textAlpha = fadeAlpha - (count * 35);
        if (textAlpha < 0){
            textAlpha = 0;
        }
        CBitmap::transBlender(0, 0, 0, textAlpha);
        // CBitmap::drawingMode( CBitmap::MODE_TRANS );
        const int color = CBitmap::makeColor(255,255,255);
        if (location.getY() <= locationY && (location.getY2()- vFont.getHeight()) >= locationY) vFont.printf(location.getX() + startx, locationY, color, bmp.translucent(), contextItemVector[currentOption]->getName(), 0 );

		// CBitmap::drawingMode( CBitmap::MODE_SOLID );
        currentOption--;
        locationY -= (int)(vFont.getHeight()/FONT_SPACER);
        count++;
        /*if (context.size() < 2 && count == 1){
            break;
        }*/
    }
    bmp.setClipRect(0, 0, bmp.getWidth(), bmp.getHeight());
	#endif
}

}
} //ens SGF