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

#include "gui/SGF_Rectarea.h"
#include <string>
using namespace std;
namespace SGF {

RectArea::RectArea() : x(0), y(0),
width(0),
height(0),
bodyAlpha(255),
borderAlpha(255), 
radius(0),
bodyColor(Colors::Transparent),
borderColor(Colors::Transparent)
{

}

RectArea::RectArea(int x, int y, int w, int h):
x(x),
y(y),
width(w),
height(h),
bodyAlpha(255),
borderAlpha(255), 
radius(0),
bodyColor(Colors::Transparent),
borderColor(Colors::Transparent)
{
}

bool RectArea::empty(){
    return (x==0 && y==0 && width==0 && height==0);
}

void RectArea::clear(){
    x=0;
	y=0; 
	width=0; 
	height=0;
	bodyAlpha=255;
	borderAlpha=255;
	radius=0;
	bodyColor=Colors::Transparent;
	borderColor=Colors::Transparent;

}

RectArea & RectArea::operator= (const RectArea &copy){
	if (this == &copy)      // Same object?
      return *this;

	x=copy.x;
	y=copy.y;
	width=copy.width; 
	height=copy.height;
	bodyAlpha=copy.bodyAlpha;
	borderAlpha=copy.borderAlpha;
	radius=copy.radius;
	bodyColor=copy.bodyColor; 
	borderColor=copy.borderColor; 
	return *this;

}
bool RectArea::operator==( const RectArea &rect){
    return ( (x == rect.x) &&
            (y == rect.y) &&
            (width == rect.width) &&
            (height == rect.height));
}

bool RectArea::operator!=( const RectArea &rect){
    return ( (x != rect.x) ||
            (y != rect.y) ||
            (width != rect.width) ||
            (height != rect.height));
}

} //end SGF