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
#ifndef MENU_STRUCTS_H_
#define MENU_STRUCTS_H_
#include "../SGF_Config.h"

using namespace std;
namespace SGF {

struct MenuPoint{
    MenuPoint();
    double x;
    double y;
};

struct MenuArea{
    MenuArea();
    int x1;
    int y1;
    int x2;
    int y2;
};
struct ScreenSize{
    ScreenSize(int w, int h):w(w), h(h){}
    int w, h;
};




} //end SGF










#endif