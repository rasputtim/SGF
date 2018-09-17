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

#ifndef _PAC_GHOST_H_
#define _PAC_GHOST_H_

#include "../Gamecore/ai/all.h"

class CMap;
class Ghost :
	public CBaseObject
{
public:
	enum direction {
		Undef=-1,
		Up,
		Right,
		Down,
		Left

	};
	// 0 == normal, 1 == vulnerable, 2 == warning, 3 == dead
	enum ghostState {
		NORMAL,
		VULNERABLE,
		WARNING,
		DEAD
	};
    Ghost( int os, int ix, int iy, int ispdmod, int itilesize,
            int iheight, int iwidth, CMap &imap, std::string fn, std::string TexturesPath);
    ~Ghost();

	virtual void act( std::vector< ::CBaseObject *> * others, CWorld * world, std::vector< CBaseObject *> * add=NULL );
	virtual void draw(CBitmap * work, int rel_x, int rel_y);
	virtual int getWidth() const {return width;};
	virtual int getHeight() const {return height;}
	bool load();

    void draw();
    void Update( int time );
    
	void setState(ghostState st);
    int getState();
    void setTarget(int ix, int iy);
    bool find();
    bool collision_ignore_gate(int xtmp, int ytmp);
    bool collision(int xtmp, int ytmp);
    void pathCalcNormal();
    void pathCalcDead();
    void pathCalcVuln();
    bool tracePath();
    int calcF(int ix, int iy) const;
    void reset();
    void changeDifficulty(int spd, int iq);

    int getXpix();
    int getYpix();
private:
     CMap &fieldMap;
	int
            startx,
			starty,
			x,	//current position in tiles (all positions refer to upper left corner)
            y,

            dx,	//current direction in x and y
            dy,

            nextdx,	//queued direction
            nextdy,

            xpix,	//current position in pixels
            ypix,

            xpix_at_last_dirchange, //location where the last direction change has taken place
            ypix_at_last_dirchange,

            spdmod,	// speed modifier	- default 100?

            tilesize,
            height,
            width,

            xtarget,
            ytarget,

            defspeed,	//default speed

            
            *parentDir,	// direction to parent tile. -1 == parent dir, 4 == init state
            *closedF,	// F value of each closed square. -1 == init state

            animcounter,
            baddie_iq,		// increases the chance of choosing shortest path

            baddie_start_point_x,
            baddie_start_point_y;

	direction dirToTar;	    //stores direction to target
	ghostState state;		// 0 == normal, 1 == vulnerable, 2 == warning, 3 == dead
    
	float	xfloat,	//current position as floating point based on pixel pos - allows for infinite speed
            yfloat;	// variations because the xfloat can be reduced to xpix

    CBitmap
            *b_ghostEl[5];

    CAstarHeap
            heap;

    bool
            dirClear[3][3],	//dirClear[x][y], direction clear = 1, blocked = 0
            gateopen,		// determines if baddies can pass gate
            *closed;

    std::string
            filename;
};


#endif