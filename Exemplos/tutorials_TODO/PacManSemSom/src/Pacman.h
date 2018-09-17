/*
  SGPacMan - Salvat Game Pacman (https://sourceforge.net/projects/sgfpacman/)
  Copyright (C) 2010-2011 Salvatore Giannotta Filho <a_materasu@hotmail.com>

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


#ifndef _PAC_PACMAN_H_
#define _PAC_PACMAN_H_

#include "../Gamecore/ai/SGF_Map.h"
#include "../Gamecore/objects/SGF_Object.h"

#define NUMPACANIM 8

class CMap;
class CBaseObject;

class Pacman :
	public CBaseObject
{
public:
    Pacman( int os, int ix, int iy, int ispdmod, int itilesize, int iheight, int iwidth, CMap &imap,std::string TexturesPath);
    ~Pacman();

	virtual void act( std::vector< ::CBaseObject *> * others, CWorld * world, std::vector< CBaseObject *> * add=NULL );
	virtual void draw(CBitmap * work, int rel_x, int rel_y);
	virtual int getWidth() const {return width;};
	virtual int getHeight() const {return height;}
	bool load();

    void draw();
	void setNextDir(int next);
    bool collision(int xtmp, int ytmp);

    void setSpeedMult( int s);

    void Update( int time );
    void nextIntersection(int &ix, int &iy);
    void reset();

    int getXpix();
    int getYpix();

private:
	CMap & fieldMap;
    int

		    startx,   //Object start position
			starty,

			curMapXpos,	//current position in tiles (all positions refer to upper left corner)
            curMapYpos,

            dx,	//current direction in x and y
            dy,

            nextdx,	//queued direction
            nextdy,

            xpix,	//current position in pixels
            ypix,

            spdmod,	// speed modifier	- default 100?
            spdmult,

            tilesize,
            height,
            width;

           // *map;

    unsigned int
            animcounter;

    float	xfloat,	//current position as floating point based on pixel pos - allows for infinite speed
            yfloat;	// variations because xfloat can be reduced to xpix


	CBitmap
		    *b_pacEl[NUMPACANIM],
            *b_pacElRot[NUMPACANIM][3];

};


#endif
