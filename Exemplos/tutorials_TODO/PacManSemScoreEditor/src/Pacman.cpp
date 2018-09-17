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


#include "Pacman.h"
#include "Game.h"
#include "PacGlobal.h"

#define PACSIZE 40

extern Debug::CLog logtxt;
extern Game game;

void Pacman::setSpeedMult( int s) {
    spdmult = s;
}
void Pacman::draw(CBitmap * work, int rel_x, int rel_y)
	 {
    b_pacEl[3]->applyAlphaTrans(alpha);
	b_pacEl[3]->Blit(rel_x, rel_y);
}
void Pacman::reset() {
    animcounter=0;
    curMapXpos=startx;
    curMapYpos=starty;
    xpix=startx*tilesize;
    ypix=starty*tilesize;
    xfloat= (float) xpix;
    yfloat= (float) ypix;
    dx=0;
    dy=0;
    nextdx=0;
    nextdy=0;
    paused=true;
}
void Pacman::nextIntersection(int &ix, int &iy) {
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "WILL SET PACMAN NEXT INTERSECTION" << endl;
    int
            xtmp=curMapXpos,
            ytmp=curMapYpos,
            i=0;
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "BEGIN WHILE LOOP TO FIND PACMEN NEXT INTERSECTION" << endl;

    while (i< ( height+width) / 2 ) {
		Debug::debug(Debug::gameEngine,__FUNCTION__) << "TRYING TO FIND PACMAN NEXT INTERSECTION LOOP: "<< i << " [x,y] "<< "[ "<<xtmp<<" , "<<ytmp<<" ]"<<endl;

        if (xtmp == 0 && dx == -1) xtmp = width-2;
        else if (xtmp == width-2 && dx == 1) xtmp = 0;
        else if (ytmp == 0 && dy == -1) ytmp = height-2;
        else if (ytmp == height-2 && dy == 1) ytmp = 0;

        if ( ! collision(xtmp+dx, ytmp+dy) ) {

            xtmp+= dx;
            ytmp += dy;
        }
        if ( ! collision(xtmp + dy, ytmp + dx) || ! collision(xtmp - dy, ytmp - dx) ) break;
        i++;
    }
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "END WHILE LOOP" << endl;
	Debug::debug(Debug::gameEngine, __FUNCTION__) << "END Seting Next Intersextion to:[ " << xtmp  <<" , "<< ytmp << " ]" <<endl;
    ix=xtmp;
    iy=ytmp;
}

void Pacman::act( std::vector< ::CBaseObject *> * others, CWorld * world, std::vector< CBaseObject *> * add)
{
    Debug::debug(Debug::gameEngine,__FUNCTION__) << "WILL RUN THE PACMAN LOGIC" << endl;

	int time =20; //getQuake();
	bool dirclear=false;
    int oldx, oldy;

    //screen wrappers
    if ( curMapXpos == width-2 && dx == 1 ) {  //SAIR PARA FORA DO MAPA PELA DIREITA
        curMapXpos = 0;  //VOLTA PARA ACOLUNA 0 DO MAPA
        xpix = 0;
        xfloat = 0;
    }
    else if (xpix == 0 && dx == -1 ) {   // SAIR PARA FORA DO MAPA PELA ESQUERA
        curMapXpos = width-2;   // VOLTA PARA A ULTIMA COLUNA DO MAPA
        xpix = curMapXpos*tilesize;
        xfloat = (float)xpix;
    }
    else if ( curMapYpos == height-2 && dy == 1 ) { //sair para fora do mapa por baixo
        curMapYpos = 0;  // vOLTA PARA A lINHA 0 DO MAPA
        ypix = 0;
        yfloat = 0;
    }
    else if ( ypix == 0 && dy == -1 ) {   //SAIR DO MAPA POR CIMA
        curMapYpos = height-2;  //VOLTA PARA A ÚLTIMA LINHA DO MAPA
        ypix = curMapYpos*tilesize;
        yfloat = (float)ypix;
    }

    //remember old coords for adjustments at end
    oldx=xpix;
    oldy=ypix;


    //if turnaround, apply dirchange immediately
    if ( dx == -nextdx && dy == -nextdy && dx!=dy ) {
        dx=nextdx;
        dy=nextdy;
    }

     //if node is reached
    if ( xpix%tilesize == 0 && ypix%tilesize == 0 ) {
        if ( dx != nextdx || dy != nextdy ) {
            //if nextdir is clear, apply dirchange
            if ( (dirclear = (! collision(curMapXpos+nextdx, curMapYpos+nextdy))) ) {
                dx=nextdx;
                dy=nextdy;
            }
        }
    }

    //if nextdir not clear check current dir
    if ( ! dirclear ) {
        if ( dx >= 0 && dy >= 0)
            dirclear = ! collision(curMapXpos+dx,curMapYpos+dy);
        else if ( dx <= 0 && dy <= 0)
            dirclear = ! collision( (xpix+dx) / tilesize, (ypix+dy) / tilesize);
    }

    //MOVEMENT PART STARTS HERE

    if ( dirclear ) {
        //  dir    *       speed in percent
        xfloat += ( (float)(time * dx * spdmod * spdmult) / MOVEMOD );
        yfloat += ( (float)(time * dy * spdmod * spdmult) / MOVEMOD );
    }

    //COORD ADJUSTMENTS

    if ( xfloat > (float)(curMapXpos+1)*tilesize ) xfloat = (float)(curMapXpos+1)*tilesize;
    if ( yfloat > (float)(curMapYpos+1)*tilesize ) yfloat = (float)(curMapYpos+1)*tilesize;

    if ( xfloat < (float)(curMapXpos)*tilesize && oldx > (float)(curMapXpos)*tilesize )
        xfloat = (float)(curMapXpos)*tilesize;
    if ( yfloat < (float)(curMapYpos)*tilesize && oldy > (float)(curMapYpos)*tilesize)
        yfloat = (float)(curMapYpos)*tilesize;

    //COORD UPDATES

    xpix=(int)xfloat;
    ypix=(int)yfloat;

    curMapXpos= xpix/tilesize;
    curMapYpos=ypix/tilesize;
	Debug::debug(Debug::gameEngine,__FUNCTION__) << "END RUN THE PACMAN LOGIC" << endl;
}
void Pacman::draw() {

    int i;
    SDL_Rect pos;

    //calculate displayed animation frame from animcounter.. abs is not the right function
    //there's probably a better way to handle this:
    if ( animcounter < 2 ) i=0;
    else if ( animcounter >= 2 && animcounter < 4 ) i=1;
    else if ( animcounter >= 4 && animcounter < 6 ) i=2;
    else if ( animcounter >= 6 && animcounter < 8 ) i=3;
    else if ( animcounter >= 8 && animcounter < 10 ) i=4;
    else if ( animcounter >= 10 && animcounter < 12 ) i=5;
    else if ( animcounter >= 12 && animcounter < 14 ) i=6;
    else if ( animcounter >= 14 && animcounter < 16 ) i=7;
    else if ( animcounter >= 16 && animcounter < 18 ) i=7;
    else if ( animcounter >= 18 && animcounter < 20 ) i=6;
    else if ( animcounter >= 20 && animcounter < 22 ) i=5;
    else if ( animcounter >= 22 && animcounter < 24 ) i=4;
    else if ( animcounter >= 24 && animcounter < 26 ) i=3;
    else if ( animcounter >= 26 && animcounter < 28 ) i=2;
    else if ( animcounter >= 28 && animcounter < 30 ) i=1;
    else if ( animcounter >= 30 && animcounter < 32 ) i=0;
    else i=0; //avoid compiler warning

    pos.y=ypix;
    pos.x=xpix;
    pos.w=PACSIZE;
    pos.h=PACSIZE;

    if (dx == 1 && dy == 0) {	//right
        b_pacEl[i]->applyAlphaTrans(alpha);
		b_pacEl[i]->Blit(xpix,ypix);
    }
    else if (dx == -1 && dy == 0) {	//left
        b_pacElRot[i][1]->applyAlphaTrans(alpha);
		b_pacElRot[i][1]->Blit(xpix,ypix);
    }
    else if (dx == 0 && dy == -1) {	//up
        b_pacElRot[i][2]->applyAlphaTrans(alpha);
		b_pacElRot[i][2]->Blit(xpix,ypix);
    }
    else if (dx == 0 && dy == 1) {	//down
        b_pacElRot[i][0]->applyAlphaTrans(alpha);
		b_pacElRot[i][0]->Blit(xpix,ypix);
    }
    else if (dx == 0 && dy == 0) {	//init position
        b_pacEl[i]->applyAlphaTrans(alpha);
		b_pacEl[i]->Blit(xpix,ypix);
    }

    if ( !paused) {
        if (animcounter == 31) animcounter = 0;
        else animcounter++;
    }
}


bool Pacman::load() {
	std::string path = this->getObjectPath();
    int i,j;
    std::string num[10];

    for (i=0;i<10;i++)
        num[i]='0'+i;

    try {
        for (i=0;i<NUMPACANIM;i++) {
            b_pacEl[i]= new CBitmap((path + "pac" + num[i] + ".png").c_str());
			if ( b_pacEl[i]->getError() )
                throw CGeneralError("Failed to load pacman texture: " + num[i]);

           b_pacEl[i]->applyDefTrans();
            //cache rotated sprites
            for (j=0;j<3;j++) {
                if (j==1) {
					b_pacElRot[i][j] = new CBitmap(*b_pacEl[i],true);
					b_pacElRot[i][j]->applyDefTrans();
					b_pacElRot[i][j]->rotateFromBitmap(0,-1,1);


				} else {
					b_pacElRot[i][j] = new CBitmap(*b_pacEl[i],true);
					b_pacElRot[i][j]->applyDefTrans();
					b_pacElRot[i][j]->rotateFromBitmap(360-(j+1)*90);

				}
            }
        }


        logtxt.print("Pacman textures loaded");
    }
    catch ( CGeneralError &err) {
        std::cerr << err.getFullReason();
		game.getGameControl()->setQuit(true);
        logtxt.print( err.getFullReason() );
        return false;
    }
    catch ( ... ) {
        std::cerr << "Unexpected exception in Pacman::LoadTextures()";
        game.getGameControl()->setQuit(true);
        logtxt.print( "Unexpected error  in Pacman::LoadTextures()" );
        return false;
    }
    return true;
}
int Pacman::getXpix() {
    return xpix;
}

int Pacman::getYpix() {
    return ypix;
}
bool Pacman::collision(int xtmp, int ytmp) {
    //error check
    if (xtmp < 0 || xtmp >= width || ytmp < 0 || ytmp >= height ) return 1;
    //collision detection
	if ( fieldMap.isWalkable(xtmp,ytmp) &&
		 fieldMap.isWalkable(xtmp+1,ytmp) &&
		 fieldMap.isWalkable(xtmp,ytmp+1) &&
		 fieldMap.isWalkable(xtmp+1,ytmp+1) ) return 0;

    return 1;
}

void Pacman::setNextDir(int next) {

    if (next >= 0 && next <=3 ) {
		if (next == Game::Up) {
			Debug::debug(Debug::gameEngine,__FUNCTION__) << " setting Next Dir to UP" << endl;
			nextdx=0;
            nextdy=-1;
        }
		if (next == Game::Right) {
            Debug::debug(Debug::gameEngine,__FUNCTION__) << " setting Next Dir to RIGHT" << endl;
			nextdx=1;
            nextdy=0;
        }
		if (next == Game::Down) {
            Debug::debug(Debug::gameEngine,__FUNCTION__) << " setting Next Dir to DOWN" << endl;
			nextdx=0;
            nextdy=1;
        }
        if (next == Game::Left) {
            Debug::debug(Debug::gameEngine,__FUNCTION__) << " setting Next Dir to LEFT" << endl;
			nextdx=-1;
            nextdy=0;
        }

    }
}
Pacman::Pacman( int os, int ix, int iy, int ispdmod,
			   int itilesize, int iheight, int iwidth, CMap &imap,std::string TexturesPath )
:   CBaseObject(os),
    fieldMap(imap),
    startx(ix),
	starty(iy),
	curMapXpos(ix),
    curMapYpos(iy),
    dx(0),
    dy(0),
    nextdx(0),
    nextdy(0),
    spdmod(ispdmod),
    spdmult(1),
    tilesize(itilesize),
    height(iheight),
    width(iwidth),
    animcounter(0)
{
    this->setObjectPath(TexturesPath);
	int i,j;

    for (i=0;i<NUMPACANIM;i++) {
        b_pacEl[i]=NULL;
        for (j=0;j<3;j++)
        b_pacElRot[i][j]=NULL;
    }

    xpix=curMapXpos*tilesize;
    ypix=curMapYpos*tilesize;

    xfloat=(float)xpix;
    yfloat=(float)ypix;

	load();
}

Pacman::~Pacman()
{
    Debug::debug(Debug::gameEngine,__FUNCTION__) << " START DELETING PACMAN==========================" << endl;

	int i,j;

    for (i=0;i<NUMPACANIM;i++) {
        if (b_pacEl[i]) delete b_pacEl[i];
        for (j=0;j<3;j++)
        if (b_pacElRot[i][j]) delete b_pacElRot[i][j];
    }
	 Debug::debug(Debug::gameEngine,__FUNCTION__) << " END DELETING PACMAN==========================" << endl;

}
