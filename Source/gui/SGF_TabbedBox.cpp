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
#include "gui/SGF_TabbedBox.h"
#include "util/SGF_FontSystem.h"
#include "graphics/SGF_Poligon.h"
#include "gui/SGF_ContextBox.h"

using namespace std;
namespace SGF{

using namespace Gui;

#if 0
/* FIXME add rounded tabs */
static void roundTab( const CBitmap & work, int radius, int x1, int y1, int x2, int y2, int color, bool bottom = true ){
    const int width = x2 - x1;
    const int height = y2 - y1;
    radius = Mid(0, radius, Min((x1+width - x1)/2, (y1+height - y1)/2));

    work.circleFill(x1+radius, y1+radius, radius, color);
    work.circleFill((x1+width)-radius, y1+radius, radius, color);
    work.circleFill(x1+radius, (y1+height)-radius, radius, color);
    work.circleFill((x1+width)-radius, (y1+height)-radius, radius, color);
    work.rectangleFill( x1+radius, y1, x2-radius, y1+radius, color);
    work.rectangleFill( x1, y1+radius, x2, y2-radius, color);
    work.rectangleFill( x1+radius, y2-radius, x2-radius, y2, color);

    work.line(x1+radius, y1, x1+width-radius, y1, color);
    work.line(x1+radius, y1+height, x1+width-radius,y1+height, color);
    work.line(x1, y1+radius,x1, y1+height-radius, color);
    work.line(x1+width, y1+radius,x1+width, y1+height-radius, color);

    arc(work, x1+radius, y1+radius, S_PI-1.115, radius, color);
    arc(work, x1+radius + (width - radius *2), y1+radius, -S_PI/2 +0.116, radius, color);
    arc(work, x1+width-radius, y1+height-radius, -0.110, radius ,color);
    arc(work, x1+radius, y1+height-radius, S_PI/2-0.119, radius, color);
}
#endif
/*
CTab::CTab():
context(new CContextBox()),
active(false){
    // Set alpha to 0 as we are not interested in the box
    context->setRenderOnlyText(true);
}

CTab::~CTab(){
    delete context;
}*/

CTab::CTab():
active(false){
    // Set alpha to 0 as we are not interested in the box
	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN CREATING CTAB "<< &context << endl;
	context.setRenderOnlyText(true);
	Debug::debug(Debug::menu,__FUNCTION__) << "END CREATING CTAB "<< &context << endl;
}

CTab::~CTab(){

}

void CTab::addOption(const Util::CReferenceCount<CContextItem> & item){
 context.addItem(item);
}

void CTab::render(const CBitmap & area, const CFont & font){
 context.render(area, font);
}

void CTab::act(const CFont & font){
context.act(font);
}

void CTab::setList(const vector<Util::CReferenceCount<CContextItem> > & list){
 context.setList(list);
}

void CTab::setName(const string & name){
    this->name = name;
}

void CTab::close(){
  context.close();
}

void CTab::open(){
 context.open();
}

void CTab::previous(const CFont & font){
 context.previous(font);
}

void CTab::next(const CFont & font){
 context.next(font);
}

void CTab::adjustLeft(){
	context.adjustLeft();
}

void CTab::adjustRight(){
    context.adjustRight();
}

int CTab::getCurrentIndex(){
    return context.getCurrentIndex();
}


CTabbedBox::CTabbedBox():
current(0),
fontWidth(24),
fontHeight(24),
inTab(false),
tabWidthMax(0),
tabFontColor(Colors::White),
currentTabFontColor(Colors::Blue){
    activeTabFontColor = new Effects::Gradient(50, tabFontColor, currentTabFontColor);
}

CTabbedBox::CTabbedBox(const CTabbedBox & b):
activeTabFontColor(NULL){
    this->location = b.location;
    this->workArea = b.workArea;
}

CTabbedBox::~CTabbedBox(){
    for (vector<Gui::CTab *>::iterator i = tabs.begin(); i != tabs.end(); ++i){
        Gui::CTab * tab = *i;
        if (tab){
            delete tab;
        }
    }

    if (activeTabFontColor){
	delete activeTabFontColor;
    }
}

CTabbedBox &CTabbedBox::operator=( const CTabbedBox &copy){
    location = copy.location;
    workArea = copy.workArea;

    return *this;
}

// Logic
void CTabbedBox::act(const CFont & font){
    if (!tabs.empty()){
	        const int width = font.getTextLength(tabs[current]->name.c_str()) + 5;
        if (tabs.size() > 1){
            tabWidthMax = (location.getWidth() - width) / (tabs.size() - 1);
        } else {
            tabWidthMax = location.getWidth() - width;
        }
     } else {
	return;
    }
    if (!tabs[current]->active){
	tabs[current]->active = true;
    }
    tabs[current]->act(font);
    if (inTab){
		if (activeTabFontColor){
			activeTabFontColor->update();
		}
	}
}

void CTabbedBox::render(const CBitmap & work){
    /* nothing */
}

// Render
void CTabbedBox::render(const CBitmap & work, const CFont & font){
    const int tabHeight = fontHeight + 5;
    // checkWorkArea();
    CBitmap area(work, location.getX(), location.getY(), location.getWidth(), location.getHeight());
    // Check if we are using a rounded box
    if (location.getRadius() > 0){
        //roundRectFill( *workArea, (int)location.getRadius(), 0, 0, location.getWidth()-1, location.getHeight()-1, colors.body );
        //roundRect( *workArea, (int)location.getRadius(), 0, 0, location.getWidth()-1, location.getHeight()-1, colors.border );
    /*  para verificar
	      const int offset = transforms.getRadius() * 4;
        const Graphics::Bitmap & temp = Graphics::Bitmap::temporaryBitmap(location.getWidth(), offset/2);
        temp.clearToMask();
        temp.roundRectFill((int)transforms.getRadius(), 0, offset/2 * -1, location.getWidth()-1, (offset/2)-1, colors.body);
        temp.roundRect((int)transforms.getRadius(), 0, offset/2 * -1, location.getWidth()-1, (offset/2)-1, colors.border);
        temp.translucent().draw(0,location.getHeight() - offset/2, area);

        area.translucent().rectangleFill(0, tabHeight+1, location.getWidth()-1, location.getHeight()-1 - offset/2, colors.body );
        area.translucent().vLine(tabHeight,0,location.getHeight()-1 - offset/2,colors.border);
        area.translucent().vLine(tabHeight,location.getWidth()-1,location.getHeight()-1 - offset/2,colors.border);
 	*/
	} else {
        area.translucent().rectangleFill(0, tabHeight+1, location.getWidth()-1, location.getHeight()-1, colors.body );
        //area.translucent().rectangle(0, tabHeight, location.getWidth()-1, location.getHeight()-1, colors.border );
	area.translucent().polygon().vLine(tabHeight,0,location.getHeight()-1,colors.border);
	area.translucent().hLine(0,location.getHeight()-1,location.getWidth()-1,colors.border);
	area.translucent().polygon().vLine(tabHeight,location.getWidth()-1,location.getHeight()-1,colors.border);
    }

    tabs[current]->render(area, font);

    renderTabs(area, font);

    /* FIXME: only render the background in translucent mode, the text should
     * not be translucent
     */
    // workArea->draw(location.getX(), location.getY(), work);
}

// Add tab

// Add tab
void CTabbedBox::addTab(const string & name, const vector<Util::CReferenceCount<CContextItem> > & list){
    for (vector<CTab *>::iterator i = tabs.begin(); i != tabs.end(); ++i){
        CTab * tab = *i;
        if (tab->name == name){
            return;
        }
    }
    CTab * tab = new CTab();
    tab->name = name;
    tab->setList(list);

    addTab(tab);
}


void CTabbedBox::addTab(CTab * tab){
    const int modifier = fontHeight * .35;
    tab->getContext().location.setPosition(Gui::CAbsolutePoint(0, fontHeight + modifier));
    tab->getContext().location.setPosition2(Gui::CAbsolutePoint(location.getWidth(), location.getHeight()- modifier));
    tab->open();
    tabs.push_back(tab);
}

void CTabbedBox::moveTab(int direction){
    tabs[current]->close();
    tabs[current]->active = false;
    current = (unsigned int) ((int)current + direction + (int) tabs.size()) % tabs.size();
    /*
    if (current == 0){
        current = tabs.size()-1;
    } else {
        current--;
    }
    */
    tabs[current]->open();
    tabs[current]->active = true;
}

void CTabbedBox::_up(const CFont & font){
    if (tabs.size() == 0){
        return;
    }
    if (!inTab){
        moveTab(-1);
    } else {
        tabs[current]->previous(font);
    }
}

void CTabbedBox::down(const CFont & font){
    if (tabs.size() == 0){
        return;
    }
    if (!inTab){
        moveTab(1);
    } else {
        tabs[current]->next(font);
    }
}

void CTabbedBox::left(const CFont & font){
    if (tabs.size() == 0){
        return;
    }
    if (!inTab){
        moveTab(-1);
    } else {
        tabs[current]->adjustLeft();
    }
}

void CTabbedBox::right(const CFont & font){
    if (tabs.size() == 0){
        return;
    }
    if (!inTab){
        moveTab(1);
    } else {
        tabs[current]->adjustRight();
    }
}

void CTabbedBox::toggleTabSelect(){
    inTab = !inTab;
}

unsigned int CTabbedBox::getCurrentIndex() const {
    if (tabs.size() == 0){
        return 0;
    }
    return this->tabs[current]->getCurrentIndex();
}

void CTabbedBox::setTabFontColor(Colors::ColorDefinition color){
    tabFontColor = color;
    if (activeTabFontColor){
	delete activeTabFontColor;
    }
    activeTabFontColor = new Effects::Gradient(50, tabFontColor, currentTabFontColor);
}

void CTabbedBox::setSelectedTabFontColor(Colors::ColorDefinition color){
    currentTabFontColor = color;
    if (activeTabFontColor){
	delete activeTabFontColor;
    }
    activeTabFontColor = new Effects::Gradient(50, tabFontColor, currentTabFontColor);
}

void CTabbedBox::renderTabs(const CBitmap & bmp, const CFont & vFont){
    const int tabHeight = fontHeight + 5;
    // const CFont & vFont = CFont::getFont(font, fontWidth, fontHeight);

    int x = 0;
    CBitmap::transBlender(0, 0, 0, colors.body.a);

    for (vector<Gui::CTab *>::iterator i = tabs.begin(); i != tabs.end(); ++i){
        Gui::CTab * tab = *i;
        const int textWidth = vFont.getTextLength(tab->name.c_str()) + 5;
	// for last tab
	int modifier = 0;
	// Check last tab so we can ensure proper sizing
	if ( i == (tabs.begin() + tabs.size() -1)){
	    if ( ( (tabWidthMax * (tabs.size() - 1) ) + textWidth ) != (unsigned int)location.getWidth() ){
		modifier = location.getWidth() - x - (tab->active ? textWidth : tabWidthMax);
	    }
	}

	if (transforms.getRadius() > 0){
#if 0
		           const int offset = transforms.getRadius() * 4;
            if (tab->active){
                Graphics::Bitmap area(bmp, x, 0, x+textWidth+modifier-1, tabHeight+1);
                if (!inTab){
                    area.translucent().roundRectFill((int)transforms.getRadius(), 0, 0, textWidth+modifier-1, tabHeight*2, colors.body);
                    area.translucent().roundRect((int)transforms.getRadius(), 0, 0, textWidth+modifier-1, tabHeight*2, colors.border);
                    vFont.printf((((textWidth + modifier)/2)-(((textWidth + modifier) - 5)/2)), 0, currentTabFontColor, area, tab->name, 0 );
                } else {
                    area.translucent().roundRectFill((int)transforms.getRadius(), 0, 0, textWidth+modifier-1, tabHeight*2, colors.body);
                    area.translucent().roundRect((int)transforms.getRadius(), 0, 0, textWidth+modifier-1, tabHeight*2, colors.border);
                    vFont.printf((((textWidth + modifier)/2)-(((textWidth + modifier) - 5)/2)), 0, activeTabFontColor->current(), area, tab->name, 0 );
                }
                x+=textWidth + modifier;
            } else {
                const int heightMod = tabHeight * .15;
                Graphics::Bitmap area(bmp, x, 1 + heightMod, x+tabWidthMax+modifier-1, tabHeight-heightMod);
                area.translucent().roundRectFill((int)transforms.getRadius(),0,0,tabWidthMax+modifier-1,tabHeight*2,Graphics::makeColor(105, 105, 105));
                area.translucent().roundRect((int)transforms.getRadius(),0,0,tabWidthMax+modifier-1,tabHeight*2,Graphics::makeColor(58, 58, 58));
                area.translucent().hLine(0,tabHeight,tabWidthMax+modifier-1,colors.border);
                vFont.printf((((tabWidthMax + modifier)/2)-((textWidth + modifier)/2)), 0, tabFontColor, area, tab->name, 0 );
                x += tabWidthMax + modifier;
            }



#endif
	} else {
            if (tab->active){
				CBitmap area(bmp, x, 0, x+textWidth+modifier-1, tabHeight+1);
		if (!inTab){
		    //bmp.translucent().rectangle(x, 0, x+textWidth + modifier - 1, tabHeight, colors.border);
		    area.translucent().polygon().vLine(0,x,tabHeight,colors.border);
		    area.translucent().hLine(x,0,x+textWidth+modifier-1,colors.border);
		    area.translucent().polygon().vLine(0,x+textWidth+modifier-1,tabHeight,colors.border);
		    area.translucent().rectangleFill( x+1, 1, x+textWidth + modifier - 2, tabHeight, colors.body);

		    area.setClipRect(x, 0, x+textWidth + modifier, tabHeight-1);
#if 0
			        area.translucent().rectangleFill(0, 0, textWidth+modifier-1, tabHeight*2, colors.body);
                    area.translucent().rectangle(0, 0, textWidth+modifier-1, tabHeight*2, colors.border);

#endif
					vFont.drawText(x + (((textWidth + modifier)/2)-(((textWidth + modifier) - 5)/2)), 0, currentTabFontColor, bmp, tab->name.c_str(), 0 );
		} else {
		    //bmp.translucent().rectangle(x, 0, x+textWidth + modifier -1, tabHeight, colors.border);
		    area.translucent().polygon().vLine(0,x,tabHeight,colors.border);
		    area.translucent().hLine(x,0,x+textWidth+modifier-1,colors.border);
		    area.translucent().polygon().vLine(0,x+textWidth+modifier-1,tabHeight,colors.border);
		    area.translucent().rectangleFill( x+1, 1, x+textWidth-2 + modifier, tabHeight, colors.body );

		    area.setClipRect(x, 0, x+textWidth + modifier, tabHeight-1);
#if 0
			        area.translucent().rectangleFill(0, 0, textWidth+modifier-1, tabHeight*2, colors.body);
                    area.translucent().rectangle(0, 0, textWidth+modifier-1, tabHeight*2, colors.border);

#endif

					vFont.drawText(x + (((textWidth + modifier)/2)-(((textWidth + modifier) - 5)/2)), 0, activeTabFontColor->current_intcolor(), bmp, tab->name.c_str(), 0 );
		}

		x+=textWidth + modifier;
        } else {
		const int heightMod = tabHeight * .15;
		CBitmap area(bmp, x, 1 + heightMod, x+tabWidthMax+modifier-1, tabHeight-heightMod);


		area.translucent().rectangle(x, 1 + heightMod, x+tabWidthMax + modifier -1, tabHeight, tabColors.border);
		area.translucent().hLine(x,tabHeight,x+tabWidthMax+modifier-1,colors.border);
		area.translucent().rectangleFill( x+1, 2 + heightMod, x+tabWidthMax + modifier -2, tabHeight-2, tabColors.body);
		area.setClipRect(x+2, 6 + heightMod, x+tabWidthMax + modifier -3, tabHeight-1);
#if 0
	                area.translucent().rectangleFill(0,0,tabWidthMax+modifier-1,tabHeight*2,Graphics::makeColor(105, 105, 105));
                area.translucent().rectangle(0,0,tabWidthMax+modifier-1,tabHeight*2,Graphics::makeColor(58, 58, 58));
                area.translucent().hLine(0,tabHeight,tabWidthMax+modifier-1,colors.border);
#endif

				vFont.drawText(x + (((tabWidthMax + modifier)/2)-((textWidth + modifier)/2)), 0, tabFontColor, bmp, tab->name.c_str(), 0 );
		x += tabWidthMax + modifier;
            }
	    bmp.setClipRect(0, 0, bmp.getWidth(), bmp.getHeight());
        }
    }
}
} //end SGF