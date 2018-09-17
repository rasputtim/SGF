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


#include "Ghost.h"
#include "Settings.h"
#include "Game.h"
#include "PacGlobal.h"

#define GHOSTSIZE 40

extern Debug::CLog logtxt;

extern CPacConfiguration settings;
extern Game game;

void Ghost::draw(CBitmap * work, int rel_x, int rel_y) {

	b_ghostEl[0]->applyAlphaTrans(alpha);
	b_ghostEl[0]->Blit(rel_x, rel_y);
}
int Ghost::getXpix() {
    return xpix;
}

int Ghost::getYpix() {
    return ypix;
}
void Ghost::setTarget(int ix, int iy) {
    xtarget=ix;
    ytarget=iy;
}
bool Ghost::collision(int xtmp, int ytmp) {
    //error check
    if (xtmp < 0 || xtmp >= width || ytmp < 0 || ytmp >= height ) return 1;
    //collision detection
	if ( fieldMap.isWalkable(xtmp,ytmp) &&
		 fieldMap.isWalkable(xtmp+1,ytmp) &&
		 fieldMap.isWalkable(xtmp,ytmp+1) &&
		 fieldMap.isWalkable(xtmp+1,ytmp+1) ) return 0;

    return 1;
}
void Ghost::changeDifficulty(int spd, int iq) {
    defspeed += spd;
    baddie_iq += iq;
}
void Ghost::reset() {
    animcounter=0;
    x=startx;
    y=starty;
    xpix=startx*tilesize;
    ypix=starty*tilesize;
    xfloat= (float) xpix;
    yfloat= (float) ypix;
    dx=0;
    dy=0;
    nextdx=0;
    nextdy=0;

    spdmod=defspeed;
    state=NORMAL;
    gateopen=true;
}
int Ghost::getState() {
    return state;
}

bool Ghost::find() {
    int
            i,
            currentx = xpix / tilesize,
            currenty = ypix / tilesize,
            tmppos;

    //if target is not clear

    if ( collision( xtarget, ytarget) ) return 0;

    // reset arrays

    for (i=0; i<width*height; i++) {
        closed[i]=0;
        parentDir[i]=4;
        closedF[i]=-1;
      }
	fieldMap.clear();  //clear Gcost

    // reset heap

    heap.reset();

    //init loop

    parentDir[ currenty*width + currentx ]= -1;
	//reset starting square's G value to 0
	fieldMap.setGcost(x,y,0);
    //4.Add the starting location to the open list of squares to be checked.
	heap.add( currentx , currenty , calcF(currentx,currenty) );

    // loop start
	//5.Do the following until a path is found or deemed nonexistent.

    while ( true ) {

        //set focus coords
		//7. Pop the first item off the open list.
        currentx=heap.getX();
        currenty=heap.getY();

        // remember F, set status as closed

        closedF[currenty*width+currentx]=heap.getF();
        closed[currenty*width+currentx]=1;

        // if current tile == target, terminate loop

        if (currentx == xtarget && currenty == ytarget) return 1;

        //remove from open list

        heap.remove();

        // first up: RIGHT NEIGHBOR SQUARE
        // special case : current == width-2

        i=1;
        if ( currentx == width-2 ) {

            //if neighbor tile is clear and not on closed list

            if ( ! collision_ignore_gate(0, currenty) && !closed[currenty*width+0] ) {

                // if not already on openlist

                if ( !(tmppos=heap.find(0, currenty)) ) {

                    fieldMap.setGcost(0,currenty,fieldMap.getGcost(currentx,currenty)+1);
                    heap.add(0, currenty, calcF(0, currenty));	//add to openlist

                    parentDir[currenty*width+0]=3;				//set parent square
                }

                // if already on openlist -> this path lower G?

                else {
					if ( fieldMap.getGcost(0,currenty) > fieldMap.getGcost(currentx,currenty)+1) //Gstore[currenty*width+0] > Gstore[currenty*width+currentx] + 1 )
					{
                        fieldMap.setGcost(0,currenty,fieldMap.getGcost(currentx,currenty)+1); //update G
						parentDir[currenty*width+0]=3;							//update parent direction
                        heap.changeF( heap.find(0, currenty), calcF(0,currenty));	//update F stored in openList
                    }
                }
            }
        }

        // usual case: current != width -2

        else {
            if (! collision_ignore_gate(currentx+i, currenty) && !closed[currenty*width+currentx +i] ) {
                if ( !(tmppos=heap.find(currentx+i, currenty)) ) {
					fieldMap.setGcost(currentx+i,currenty, fieldMap.getGcost(currentx,currenty)+1);
					heap.add(currentx+i, currenty, calcF(currentx+i, currenty));
                    parentDir[currenty*width+currentx+i]=3;
                }
                //if already on openlist
                else {			//if this path has a lower G
                    //if ( Gstore[currenty*width+currentx+i] > Gstore[currenty*width+currentx] + 1 )
					if (fieldMap.getGcost(currentx+i,currenty) > fieldMap.getGcost(currentx,currenty)+1)
					{
						fieldMap.setGcost(currentx+i,currenty,fieldMap.getGcost(currentx,currenty)+1);
						parentDir[currenty*width+currentx+i]=3;
                        heap.changeF( heap.find(currentx+i, currenty), calcF(currentx+i,currenty));
                    }
                }
            }
        }

        // LEFT NEIGHBOR SQUARE
        //special case : currentx == 0

        i = -1;

        if (currentx == 0 ) {
            if (! collision_ignore_gate(width-2, currenty) && !closed[currenty*width+width-2] ) {
                if ( !(tmppos=heap.find(width-2, currenty)) ) {
					fieldMap.setGcost(width-2,currenty, fieldMap.getGcost(currentx,currenty)+1);
                    heap.add(width-2, currenty, calcF(width-2, currenty));
                    parentDir[currenty*width+width-2]=1;
                }
                else {
                    if (fieldMap.getGcost(width-2,currenty) > fieldMap.getGcost(currentx,currenty)+1)
					{
                        //Gstore[currenty*width+width-2] = Gstore[currenty*width+currentx] + 1;
                        fieldMap.setGcost(width-2,currenty, fieldMap.getGcost(currentx,currenty)+1);
                    	parentDir[currenty*width+width-2]=1;
                        heap.changeF( heap.find(width-2, currenty), calcF(width-2,currenty));
                    }
                }
            }
        }

        // normal case
        else {
            if (! collision_ignore_gate(currentx+i, currenty) && !closed[currenty*width+currentx+i] ) {
                if ( !(tmppos=heap.find(currentx+i, currenty)) ) {
                    fieldMap.setGcost(currentx + i,currenty, fieldMap.getGcost(currentx,currenty)+1);
                    heap.add(currentx+i, currenty, calcF(currentx+i, currenty));
                    parentDir[currenty*width+currentx+i]=1;
                }
                else {
                    if (fieldMap.getGcost(currentx+i,currenty) > fieldMap.getGcost(currentx,currenty)+1)
					{
                        //Gstore[currenty*width+currentx+i] = Gstore[currenty*width+currentx] + 1;
                        fieldMap.setGcost(currentx + i,currenty, fieldMap.getGcost(currentx,currenty)+1);
                        parentDir[currenty*width+currentx+i]=1;
                        heap.changeF( heap.find(currentx+i, currenty), calcF(currentx+i,currenty));
                    }
                }
            }
        }

        // LOWER NEIGHBOR SQUARE

        i=1;

        // special case

        if ( currenty == height -2 ) {
            if ( ! collision_ignore_gate(currentx, 0) && !closed[0*width+currentx] ) {

                // if not already on openlist

                if ( !(tmppos=heap.find(currentx, 0)) ) {

                   fieldMap.setGcost(currentx,0, fieldMap.getGcost(currentx,currenty)+1);

                    heap.add(currentx, 0, calcF(currentx, 0));	//add to openlist

                    parentDir[0*width+currentx]=0;				//set parent square
                }

                // if already on openlist -> this path lower G?

                else {
                    if (fieldMap.getGcost(currentx,0) > fieldMap.getGcost(currentx,currenty)+1)
					{

                        //Gstore[0*width+currentx] = Gstore[currenty*width+currentx] + 1;	//update G
                        fieldMap.setGcost(currentx + i,0, fieldMap.getGcost(currentx,currenty)+1);
                        parentDir[0*width+currentx]=0;							//update parent direction
                        heap.changeF( heap.find(currentx, 0), calcF(currentx, 0));	//update F stored in openList
                    }
                }
            }
        }

        //normal case

        else {

            if (! collision_ignore_gate(currentx, currenty+i) && !closed[(currenty+i)*width+currentx] ) {
                if ( !(tmppos=heap.find(currentx, currenty+i)) ) {
                    fieldMap.setGcost(currentx,(currenty+i), fieldMap.getGcost(currentx,currenty)+1);
                    heap.add(currentx, currenty+i, calcF(currentx, currenty+i));
                    parentDir[(currenty+i)*width+currentx]=0;
                }
                else {
                    //if ( Gstore[(currenty+i)*width+currentx] > Gstore[currenty*width+currentx] + 1 )
					if (fieldMap.getGcost(currentx,(currenty+i)) > fieldMap.getGcost(currentx,currenty)+1)
					{
                        fieldMap.setGcost(currentx,(currenty+i), fieldMap.getGcost(currentx,currenty)+1);
                        parentDir[(currenty+i)*width+currentx]=0;
                        heap.changeF( heap.find(currentx, currenty+i), calcF(currentx,currenty+i));
                    }
                }
            }
        }

        // UPPER NEIGHBOR SQUARE

        i=-1;

        //special case
        if (currenty == 0 ) {
            if (! collision_ignore_gate(currentx, height-2) && !closed[(height-2)*width+currentx] ) {
                if ( !(tmppos=heap.find(currentx, height-2)) ) {
                    fieldMap.setGcost(currentx,(height-2), fieldMap.getGcost(currentx,currenty)+1);
                    heap.add(currentx, height-2, calcF(currentx, height-2));
                    parentDir[(height-2)*width+currentx]=2;
                }
                else {
                    if (fieldMap.getGcost(currentx,(height-2)) > fieldMap.getGcost(currentx,currenty)+1)
					{
                        fieldMap.setGcost(currentx,(height-2), fieldMap.getGcost(currentx,currenty)+1);
                        parentDir[(height-2)*width+currentx]=2;
                        heap.changeF( heap.find(currentx, height-2), calcF(currentx,height-2));
                    }
                }
            }
        }

        //normal case
        else {
            if (! collision_ignore_gate(currentx, currenty+i) && !closed[(currenty+i)*width+currentx] ) {
                if ( !(tmppos=heap.find(currentx, currenty+i)) ) {
                       fieldMap.setGcost(currentx,(currenty+i), fieldMap.getGcost(currentx,currenty)+1);
                        heap.add(currentx, currenty+i, calcF(currentx, currenty+i));
                        parentDir[(currenty+i)*width+currentx]=2;
                }
                else {
                    if (fieldMap.getGcost(currentx,(currenty+i)) > fieldMap.getGcost(currentx,currenty)+1)
					{
                        fieldMap.setGcost(currentx,(currenty+i), fieldMap.getGcost(currentx,currenty)+1);
                        parentDir[(currenty+i)*width+currentx]=2;
                        heap.changeF( heap.find(currentx, currenty+i), calcF(currentx,currenty+i));
                    }
                }
            }
        }

        // if open list is empty, terminate

        if ( heap.isEmpty() ) return 0;
    }
}
int Ghost::calcF(int ix, int iy) const {
    //  http://www.policyalmanac.org/games/aStarTutorial.htm
/*	F = G + H

where
 G = the movement cost to move from the starting point A to a given square on the grid, following the path generated to get there.
 H = the estimated movement cost to move from that given square on the grid to the final destination, point B. This is often referred to as the heuristic, which can be a bit confusing. The reason why it is called that is because it is a guess. We really don’t know the actual distance until we find the path, because all sorts of things can be in the way (walls, water, etc.). You are given one way to calculate H in this tutorial, but there are many others that you can find in other articles on the web.
 */
 int g,b;

    //!a = distância do tile atual para  o tile inicial
	g = fieldMap.getGcost(ix,iy);

    // b= distâncis x(horizontal) do tile atual para tile alvo

    b= ix > xtarget ? (ix-xtarget) : (xtarget-ix);  //current to target =H

    //special cases: target left edge, baddie right edge

    if ( ( width-1)-ix+xtarget < b ) 	b=(width-2)-ix+xtarget;	//width -1 to get correct F

    //				target right edge, baddie left edge

    if (ix + (width+1) -xtarget < b )	b=ix + (width-2) -xtarget;


	// a = a + distância horizontal para o alvo
    g+=b;

    // b= distância y do tile atual para o tile alvo

    b= iy > ytarget ? (iy-ytarget) : (ytarget-iy);

    //special case: target upper edge, baddie lower edge

    if ( ( height-1)-iy+ytarget < b ) 	b=(height-2)-iy+ytarget;

    // vice versa

    if (iy + (height+1) -ytarget < b )	b=iy + (height-2) -ytarget;

	// a = a + distância vertical para o alvo
    g+=b;

    return g;
}

//====================================================
/** @fn tracePath()
@brief método que traça um caminho para o Ghost
@return true: se o caminho foi traçado
        false: se não conseguiu traçar um caminho
@warning nenhum aviso
**/
bool Ghost::tracePath() {
    int xtmp, ytmp;

    //reset dirToTar

    dirToTar = Undef;

    //set coords

    xtmp= heap.getX();
    ytmp= heap.getY();

    if (ytmp == ytarget && xtmp == xtarget ) {	//error check

        while ( parentDir[ ytmp*width + xtmp ] != -1 ) {

            int tempdir= parentDir[ytmp*width+xtmp];		//not sure about dtotarget -1, maybe without -1
			if (tempdir < 0 || tempdir > 3 ) return 0;	//error check
			dirToTar = (direction) tempdir;
            if (dirToTar == Up) {
                if (ytmp==0) ytmp=height-2;
                else ytmp--;
            }
            else if (dirToTar == Right) {
                if ( xtmp== width-2) xtmp=0;
                else xtmp++;
            }
            else if (dirToTar == Down) {
                if (ytmp == height -2 ) ytmp=0;
                else ytmp++;
            }
            else if (dirToTar == Left) {
                if (xtmp == 0) xtmp= width-2;
                else xtmp--;
            }
        }

        if ( dirToTar == Up ) dirToTar = Down;
        else if ( dirToTar == Right ) dirToTar = Left;
        else if ( dirToTar == Down ) dirToTar = Up;
        else if ( dirToTar == Left ) dirToTar = Right;



        return 1; //path found
    }

    else return 0;	//error
}
void Ghost::pathCalcVuln() {
    int newdir = -1;
    //bool pathFound;

    //find path
    //if ( find() ) pathFound=tracePath();

    // RANDOM PATH, one not in shortest direction to pacman is preferred (dirToTar)

    //if within the starting square
    if (gateopen) {
        if ( dirToTar == 0) {
            nextdx = 0;
            nextdy = -1;
        }
        else if ( dirToTar == 1 ) {
            nextdx = 1;
            nextdy = 0;
        }
        else if ( dirToTar == 2 ) {
            nextdx = 0;
            nextdy = 1;
        }
        else if ( dirToTar == 3 ) {
            nextdx = -1;
            nextdy = 0;
        }
    }

    //if dead end
    else if ( !dirClear[1+dx][1+dy] && !dirClear[1+dy][1+dx] && !dirClear[1-dy][1-dx] && dx != dy ) {
        nextdx = -dx;
        nextdy = -dy;
    }
    //generate random dir != - current dir
    else {
        nextdx = -dx;
        nextdy = -dy;
        while ( nextdx == -dx && nextdy == -dy ) {

            newdir = rand()%4;

            //the following 2 lines make the baddies prefer directions other than shortest way to pacman

            if (newdir == dirToTar ) newdir = rand()%4;
            if (newdir == dirToTar ) newdir = rand()%4;

            if ( newdir == 0 ) {
                nextdx = 0;
                nextdy = -1;
            }
            else if ( newdir == 1 ) {
                nextdx = 1;
                nextdy = 0;
            }
            else if ( newdir == 2 ) {
                nextdx = 0;
                nextdy = 1;
            }
            else if ( newdir == 3 ) {
                nextdx = -1;
                nextdy = 0;
            }
            if ( !dirClear[1+nextdx][1+nextdy] ) {
                nextdx = -dx;
                nextdy = -dy;
            }
        }
    }

    dx=nextdx;
    dy=nextdy;
}

void Ghost::pathCalcDead() {
    bool
            pathFound = 1;
    //int     cur_opp_dir;
    int     newdir = -1;
            	// opposite of current direction

    //translate dx + dy into dir -> 0 = up, 1 = right, 2 = down, 3 = left
	// if (dx == 1) cur_opp_dir = Left;
    //else if (dx == -1) cur_opp_dir = Right;
    //else if (dy == 1) cur_opp_dir = Up;
    //else if (dy == -1) cur_opp_dir = Down;




    xtarget= baddie_start_point_x ;
    ytarget= baddie_start_point_y ;

    //find path
    if ( find() ) pathFound=tracePath();

    //if find and trace successful
    // TRACE PATH

    if (pathFound ) {		// pathfinding + trace successful
        if ( dirToTar == Up) {
            nextdx = 0;
            nextdy = -1;
        }
        else if ( dirToTar == Right ) {
            nextdx = 1;
            nextdy = 0;
        }
        else if ( dirToTar == Down ) {
            nextdx = 0;
            nextdy = 1;
        }
        else if ( dirToTar == Left ) {
            nextdx = -1;
            nextdy = 0;
        }
    }

    // ELSE RANDOM PATH	-- only happens of trace not successful
    else {

        //if dead end
        if ( !dirClear[1+dx][1+dy] && !dirClear[1+dy][1+dx] && !dirClear[1-dy][1-dx] && dx != dy ) {
            nextdx = -dx;
            nextdy = -dy;
        }
        //generate random dir != - current dir
        else {
            nextdx = -dx;
            nextdy = -dy;
            while ( nextdx == -dx && nextdy == -dy ) {

                newdir = rand()%4;

                if ( newdir == 0 ) {
                    nextdx = 0;
                    nextdy = -1;
                }
                else if ( newdir == 1 ) {
                    nextdx = 1;
                    nextdy = 0;
                }
                else if ( newdir == 2 ) {
                    nextdx = 0;
                    nextdy = 1;
                }
                else if ( newdir == 3 ) {
                    nextdx = -1;
                    nextdy = 0;
                }
                if ( !dirClear[1+nextdx][1+nextdy] ) {
                    nextdx = -dx;
                    nextdy = -dy;
                }
            }
        }
    }
    dx=nextdx;
    dy=nextdy;
}

void Ghost::pathCalcNormal() {
    bool
            pathFound = 1;
    int
            newdir = -1,
            cur_opp_dir=-1;	// opposite of current direction

    //translate dx + dy into dir -> 0 = up, 1 = right, 2 = down, 3 = left

    if (dx == 1) cur_opp_dir = Left;
    else if (dx == -1) cur_opp_dir = Right;
    else if (dy == 1) cur_opp_dir = Up;
    else if (dy == -1) cur_opp_dir = Down;


    if ( gateopen && !collision(settings.gatex, settings.gatey) )
        setTarget(settings.gatex, settings.gatey);

    //find path
    if ( find() ) pathFound=tracePath();  //true = path traced  false= path not traced

    //if find and trace successful, random roll successful AND calculated direction != opposite of current dir
    // chance based on Gstore[target square] = distance
    // TRACE PATH

    if ( pathFound &&		// pathfinding + trace successful
        rand()%(( width+height) / 2 ) + baddie_iq > fieldMap.getGcost(xtarget,ytarget) && // random roll successful
        dirToTar != cur_opp_dir) {	//and pathfinding direction is not the opposite of current direction

        if ( dirToTar == 0) {
            nextdx = 0;
            nextdy = -1;
        }
        else if ( dirToTar == 1 ) {
            nextdx = 1;
            nextdy = 0;
        }
        else if ( dirToTar == 2 ) {
            nextdx = 0;
            nextdy = 1;
        }
        else if ( dirToTar == 3 ) {
            nextdx = -1;
            nextdy = 0;
        }
    }

    // ELSE RANDOM PATH
    else {

        //if dead end
        if ( !dirClear[1+dx][1+dy] && !dirClear[1+dy][1+dx] && !dirClear[1-dy][1-dx] && dx != dy ) {
            nextdx = -dx;
            nextdy = -dy;
        }
        //generate random dir != - current dir
        else {
            nextdx = -dx;
            nextdy = -dy;
            while ( nextdx == -dx && nextdy == -dy ) {

                newdir = rand()%4;

                if ( newdir == 0 ) {
                    nextdx = 0;
                    nextdy = -1;
                }
                else if ( newdir == 1 ) {
                    nextdx = 1;
                    nextdy = 0;
                }
                else if ( newdir == 2 ) {
                    nextdx = 0;
                    nextdy = 1;
                }
                else if ( newdir == 3 ) {
                    nextdx = -1;
                    nextdy = 0;
                }
                if ( !dirClear[1+nextdx][1+nextdy] ) {
                    nextdx = -dx;
                    nextdy = -dy;
                }
            }
        }
    }
    dx=nextdx;
    dy=nextdy;
}

bool Ghost::collision_ignore_gate(int xtmp, int ytmp) {
    //error check
    if (xtmp < 0 || xtmp >= width-1|| ytmp < 0 || ytmp >= height-1 ) return 1;
    //collision detection
	if ( (fieldMap.isWalkable(xtmp,ytmp)||fieldMap.getTyleType(xtmp,ytmp)==2) &&
		 (fieldMap.isWalkable(xtmp+1,ytmp)||fieldMap.getTyleType(xtmp+1,ytmp)==2) &&
		 (fieldMap.isWalkable(xtmp,ytmp+1)||fieldMap.getTyleType(xtmp,ytmp+1)==2) &&
		 (fieldMap.isWalkable(xtmp+1,ytmp+1)||fieldMap.getTyleType(xtmp+1,ytmp+1)==2) ) return 0;

    return 1;
}
void Ghost::setState(ghostState st) {
    direction curdir;

    //vulnerable mode
    if (st == VULNERABLE && state != DEAD) {
        state =  st;

        spdmod= 2*defspeed/3;

        if (dx == 1) curdir=Right;
        else if (dx == -1) curdir=Left;
        else if (dy == 1) curdir=Down;
        else if (dy == -1) curdir=Up;

        if (curdir == dirToTar ) {
            dx=-dx;
            dy=-dy;
        }
    }
    //warning mode
    else if (st == WARNING && state == VULNERABLE) {
        state = st;
        spdmod= 2*defspeed/3;
        animcounter=0;
    }
    //dead mode
    else if (st == DEAD && state != NORMAL) {
        gateopen = 1;
        state = st;
        spdmod= 4*defspeed/3;
    }
    //normal mode
    else if (st == NORMAL && state == DEAD) {
        gateopen = 1;
        state = st;
        spdmod =defspeed;
    }
    else if (st == NORMAL && state != NORMAL) {
        state = st;
        spdmod =defspeed;
    }
}
void Ghost::act( std::vector< ::CBaseObject *> * others, CWorld * world, std::vector< CBaseObject *> * add)
 {
	int time=10;
    bool
            cont = 0;
    int
            oldx,
            oldy;

    //if target reached, set normal state

    if ( state == DEAD &&
        x == baddie_start_point_x &&
        y == baddie_start_point_y) setState(NORMAL);


    //screen wrappers

    if ( x == width-2 && dx == 1 ) {
        x = 0;
        xpix = 0;
        xfloat = 0;
    }
    else if ( xpix == 0 && dx == -1 ) {
        x = width-2;
        xpix = x*tilesize;
        xfloat = (float)xpix;
    }
    if ( y == height-2 && dy == 1 ) {
        y = 0;
        ypix = 0;
        yfloat = 0;
    }
    else if ( ypix == 0 && dy == -1 ) {
        y = height-2;
        ypix = y*tilesize;
        yfloat = (float)ypix;
    }


    //remember old coords for adjustments at end

    oldx=xpix;
    oldy=ypix;

    // if at tile beginning
    // and we haven't processed this location yet
    if ( xpix % tilesize == 0 && ypix % tilesize == 0 &&
         !(xpix == xpix_at_last_dirchange && ypix == ypix_at_last_dirchange) ) {

        //init dirClear array
        //to the right
        if ( gateopen ) {
            //right
            if (collision_ignore_gate( xpix / tilesize + 1, ypix / tilesize ) ) dirClear[1+1][1+0]=0;
            else dirClear[1+1][1+0]=1;

            //left

            if (collision_ignore_gate( xpix / tilesize - 1, ypix / tilesize ) ) dirClear[1-1][1+0]=0;
            else dirClear[1-1][1+0]=1;

            //up

            if (collision_ignore_gate( xpix / tilesize , ypix / tilesize - 1) ) dirClear[1+0][1-1]=0;
            else dirClear[1+0][1-1]=1;

            //down

            if (collision_ignore_gate( xpix / tilesize , ypix / tilesize +1) ) dirClear[1+0][1+1]=0;
            else dirClear[1+0][1+1]=1;
        }
        else {
            //right
            if (collision( xpix / tilesize + 1, ypix / tilesize ) ) dirClear[1+1][1+0]=0;
            else dirClear[1+1][1+0]=1;

            //left

            if (collision( xpix / tilesize - 1, ypix / tilesize ) ) dirClear[1-1][1+0]=0;
            else dirClear[1-1][1+0]=1;

            //up

            if (collision( xpix / tilesize , ypix / tilesize - 1) ) dirClear[1+0][1-1]=0;
            else dirClear[1+0][1-1]=1;

            //down

            if (collision( xpix / tilesize , ypix / tilesize +1) ) dirClear[1+0][1+1]=0;
            else dirClear[1+0][1+1]=1;
        }

        // switch gateopen status if current tile is a gate tile.
		if (!fieldMap.getTyleType(x,y) == 2) gateopen = !gateopen;
        //if ( map[ y*width + x] == 2 ) gateopen = !gateopen;

        // if a direction perpendicular to current direction is clear
        // OR current direction is blocked ( = dead end)
        // OR if dx == dy (starting state) set cont flag to 1.
        // cont flag determines whether new dir will be calculated or not

        if ( dirClear[1+dy][1+dx] || dirClear[1-dy][1-dx] || !dirClear[1+dx][1+dy] || dx == dy ) cont = 1;

        // if cont == 1, calc new direction
        // newdir cannot be the opposite of curdir UNLESS it is the only way.

        if (cont == 1 && state == NORMAL) pathCalcNormal();
        else if (cont == 1 && ( state == VULNERABLE || state == WARNING) ) pathCalcVuln();
        else if (cont == 1 && state == DEAD ) pathCalcDead();

        //store location
        xpix_at_last_dirchange = xpix;
        ypix_at_last_dirchange = ypix;
    }

    //MOVEMENT PART STARTS HERE


    //  dir    *       speed in percent
    xfloat += ( (float)(time * dx * spdmod) / MOVEMOD );
    yfloat += ( (float)(time * dy * spdmod) / MOVEMOD );

    //COORD ADJUSTMENTS

    if ( xfloat > (float)(x+1)*tilesize ) xfloat = (float)(x+1)*tilesize;
    if ( yfloat > (float)(y+1)*tilesize ) yfloat = (float)(y+1)*tilesize;

    if ( xfloat < (float)(x)*tilesize && oldx > (float)(x)*tilesize )
        xfloat = (float)(x)*tilesize;
    if ( yfloat < (float)(y)*tilesize && oldy > (float)(y)*tilesize)
        yfloat = (float)(y)*tilesize;

    //COORD UPDATES

    xpix=(int)xfloat;
    ypix=(int)yfloat;

    x= xpix/tilesize;
    y=ypix/tilesize;
}
void Ghost::draw() {

    SDL_Rect pos;

    pos.x=xpix;
    pos.y=ypix;
    pos.h=GHOSTSIZE;
    pos.w=GHOSTSIZE;

    //normal state

    if (state == NORMAL) {
        b_ghostEl[0]->applyAlphaTrans(alpha);
		b_ghostEl[0]->Blit(pos.x,pos.y);
    }

    //vulnerable state

    else if (state == VULNERABLE) {
        b_ghostEl[2]->applyAlphaTrans(alpha);
		b_ghostEl[2]->Blit(pos.x,pos.y);
    }

    //warning state

    else if (state == WARNING) {
        if ( !paused ) animcounter++;
        if (animcounter%30 < 15) {
            b_ghostEl[3]->applyAlphaTrans(alpha);
			b_ghostEl[3]->Blit(pos.x,pos.y);
        }
        else {
            b_ghostEl[2]->applyAlphaTrans(alpha);
			b_ghostEl[2]->Blit(pos.x,pos.y);
        }
    }
    //if dead, only eyes are drawn

    else if (state == DEAD) {
        b_ghostEl[4]->applyAlphaTrans(alpha);
		b_ghostEl[4]->Blit(pos.x,pos.y);
    }

    if (dx == 1)
        pos.x=pos.x+2;
    else if (dx == -1)
        pos.x=pos.x-2;
    else if (dy == -1)
        pos.y=pos.y-2;
    else if (dy == 1)
        pos.y=pos.y+2;

    //draw eyes
    b_ghostEl[1]->applyAlphaTrans(alpha);
	b_ghostEl[1]->Blit(pos.x,pos.y);
}

bool Ghost::load() {

	Debug::debug(Debug::menu,__FUNCTION__) << "BEGIN" << endl;
	std::string path = this->getObjectPath();
    std::string files[5];

    files[0]=path + "baddie" + filename + ".png";
    files[1]=path + "baddie_eyes.png";
    files[2]=path + "baddie" + filename + "vuln.png";
    files[3]=path + "baddie" + filename + "warn.png";
    files[4]=path + "baddie_dead.png";

    try {

        for (int i = 0; i<5; i++) {
            b_ghostEl[i]=new CBitmap(files[i].c_str());
			if ( b_ghostEl[i]->getError() )
                throw CGeneralError("Failed to load ghost texture: " + files[i]);

          b_ghostEl[i]->applyDefTrans();
        }
        logtxt.print(filename + " ghost textures loaded");

   }
    catch ( CGeneralError &err) {
        std::cerr << err.getFullReason();
        game.getGameControl()->setQuit(true);
        logtxt.print( err.getFullReason() );
        return false;
    }
    catch ( ... ) {
        std::cerr << "Unexpected exception in Ghost::LoadTextures()";
        game.getGameControl()->setQuit(true);
        logtxt.print( "Unexpected error in Ghost::LoadTextures()" );
        return false;
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "END" << endl;
    return true;
}

Ghost::Ghost( int os, int ix, int iy, int ispdmod, int itilesize,
			 int iheight, int iwidth, CMap &imap, std::string fn, std::string TexturesPath)
:   CBaseObject(os),
    startx(ix),
	starty(iy),
	x(ix),
    y(iy),
    dx(0),
    dy(0),
    nextdx(0),
    nextdy(0),
    xpix_at_last_dirchange(1),
    ypix_at_last_dirchange(1),
    spdmod(ispdmod),
    tilesize(itilesize),
    height(iheight),
    width(iwidth),
    fieldMap(imap),
    dirToTar(Undef),
    state(NORMAL),
    animcounter(0),
    baddie_iq(0),
    heap(iwidth, iheight),
    gateopen(1)
{
    this->setObjectPath(TexturesPath);
	int i,j;

    filename = fn;

    for (i=0;i<5;i++) b_ghostEl[i]=NULL;

    xpix=x*tilesize;
    ypix=y*tilesize;

    xfloat=(float)xpix;
    yfloat=(float)ypix;

    defspeed=spdmod;

    baddie_start_point_x=ix;
    baddie_start_point_y=iy;

    closed = new bool[height*width];
    parentDir = new int[height*width];
    //Gstore = new int[height*width];
    closedF = new int[height*width];

    for (i=0;i<3;i++) for (j=0; j<3; j++) dirClear[j][i]=0;

	load();
}

Ghost::~Ghost()
{
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " START DELETING GHOST==========================" << endl;

    int i;

    for (i=0;i<5;i++) if ( b_ghostEl[i] ) delete b_ghostEl[i];

    if  ( closed != NULL ) delete[] closed;
    if ( parentDir != NULL ) delete[] parentDir;
    //if ( Gstore != NULL ) delete[] Gstore;
    if ( closedF != NULL ) delete[] closedF;
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " END DELETING GHOST==========================" << endl;

}
