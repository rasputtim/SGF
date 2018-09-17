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

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <ostream>
#include <sstream>
#include <iostream>

// To aid in filesize
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "objects/SGF_Element.h"


using namespace std;
namespace SGF {

CElement::CElement():
CBaseObject(CBaseObject::SGFElement),
ID(0),
layer(Background){
}
CElement::CElement(CElement & copy):
CBaseObject(copy),
ID(0),
SGFCpConstrLast(layer)
{}



CElement::~CElement(){
}


//=============== CBackground========================

CBackgroundElement::CBackgroundElement(const string & name):
isLinked(0),
visible(true),
enabled(true),
start(Gui::CAbsolutePoint(0,0,0)),
deltaX(1),
deltaY(1),
tile(Gui::CAbsolutePoint(0,0,0)),
tileSpacing(Gui::CAbsolutePoint(0,0,0)),
window(0,0,319,239),
windowDeltaX(0),
windowDeltaY(0),
velocityX(0),
velocityY(0),
linkedElement(0)
{
    //Set CElement Properties
	setName(name);
	setLayer(CElement::Background);

}

CBackgroundElement::CBackgroundElement(const CBackgroundElement &copy){
    this->setID(copy.getID());
    this->setLayer(copy.getLayer());
    this->setName(copy.getName());
    this->visible = copy.visible;
    this->enabled = copy.enabled;
    this->start = copy.start;
    this->deltaX = copy.deltaX;
    this->deltaY = copy.deltaY;
    this->tile = copy.tile;
    this->tileSpacing = copy.tileSpacing;
    this->window = copy.window;
    this->windowDeltaX = copy.windowDeltaX;
    this->windowDeltaY = copy.windowDeltaY;
    this->isLinked = copy.isLinked;
    this->velocityX = copy.velocityX;
    this->velocityY = copy.velocityY;
    this->linkedElement = copy.linkedElement;
}

CBackgroundElement::~CBackgroundElement(){
}


/* Copy the contents of this into element
 * If this element is linked then we will call it recursively until we've come to the end of the chain
 * and then copy the contents of the last link of the chain into our passed element
 */
void CBackgroundElement::setLink(CBackgroundElement *element){
    element->linkedElement = this;
    if (isLinked){
	if (linkedElement){
	    linkedElement->setLink(element);
	    return;
	}
    }
    Gui::CPoint newStart = element->getStart();
	newStart.x += start.x;
    newStart.y += start.y;
    element->setStart(newStart);
    element->setDelta(deltaX, deltaY);
    element->setVelocity(velocityX, velocityY);

}

void CBackgroundElement::reset(){
    setX(0);
    setY(0);
    /* TODO: set velocity to its original velocity and whatever else */
}

double CBackgroundElement::getCurrentX() const {

	///Debug::debug(1,__FUNCTION__) << " CBackgroundElement::getCurrentX()"<< endl;
	//Debug::debug(1,__FUNCTION__) << " GetStart = "<< getStart().x << endl;
    //Debug::debug(1,__FUNCTION__) << " GetX = "<< getX()  << endl;
	//Debug::debug(1,__FUNCTION__) << " GetSin = "<< getSinX().get() << endl;
    return getStart().x + getX();
}

double CBackgroundElement::getCurrentY() const {
    return getStart().y + getY();
}
} //end SGF