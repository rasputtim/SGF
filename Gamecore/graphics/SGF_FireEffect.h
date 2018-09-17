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
#ifndef _fire_93c6678306f3542737be4288dc09cfa9
#define _fire_93c6678306f3542737be4288dc09cfa9

#include "../../ExternalLibs/SDL2/include/SDL.h"
#include "../SGF_Config.h"
#include "../graphics/SGF_Color.h"

using namespace std;
namespace SGF{
class CBitmap;

struct Wisp{
    double x, y;
    int life;
    int angle;
};


/**
 * \class CFire
 *
 * \ingroup SGF_Graphics
 * 
 * \brief Efeito de Fogo
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */

class  SGE_API CFire{
public:
    CFire();

    void update();
    void draw(const CBitmap & work);

    virtual ~CFire();

protected:
    void updateHotspots();
    void updateWisps();

protected:
    unsigned char ** data;
    /* enough to fill an unsigned char */
    static const int MAX_COLORS = 256;
    Colors::ColorDefinition colors[MAX_COLORS];
    static const int MAX_HOTSPOTS = 10;
    double hotspots[MAX_HOTSPOTS];
    double directions[MAX_HOTSPOTS];
    static const int MAX_WISPS = 30;
    Wisp wisps[MAX_WISPS];
};

}

#endif
