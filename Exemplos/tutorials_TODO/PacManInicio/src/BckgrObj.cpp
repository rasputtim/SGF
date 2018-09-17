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


#include "BckgrObj.h"
#include "settings.h"

extern Debug::CLog logtxt;
extern CPacConfiguration settings;
extern Game game;


void BckgrObj::Draw(int ix, int iy, int obj, int type, int alp) {
    SDL_Rect pos;

    pos.x=ix;
    pos.y=iy;
    pos.h=pos.w=20;

    if (type == 1) {
		//CBitmap
			foodObj[obj]->applyAlphaTrans(alp);
			foodObj[obj]->Blit(ix,iy);
	}
    else {
		//CBitmap
		b_mapEl[obj]->applyAlphaTrans(alp);
		b_mapEl[obj]->Blit(ix,iy);

    }
}

void BckgrObj::Draw(int ix, int iy, int obj, int type) {
    Draw(ix,iy,obj,type,255);
}

void BckgrObj::setFruitAlpha(int a) {
    fruitalpha = a;
}

void BckgrObj::draw() {
    CMap fieldMap;
	CMap objMap;
    int height,
    width,
    linha,
    coluna;
    SDL_Rect pos;

    height = settings.fieldheight;
    width = settings.fieldwidth;
    game.getMaps(&fieldMap, &objMap);

    pacFoodCounter = 0;
	b_mapEl[0]->Blit();

	//DRAW FIELD
    for (linha=0;linha<width;linha++) { //coluna
        for (coluna=0; coluna<height; coluna++) { //linha

            pos.x=coluna*settings.tilesize;
            pos.y=linha*settings.tilesize;
            pos.h=20;
            pos.w=20;
			//Debug::debug(Debug::gameEngine) <<" Map Draw Read Value [ " << linha <<" , " <<coluna<<" ]: " << fieldMap.getTyleType(linha,coluna) << endl;
			int typetype = fieldMap.getTyleType(coluna,linha);
			switch (typetype) {
				case upper_left_corner:
					{		//upper left corner
					//Debug::debug(Debug::gameEngine) <<" Map Will Blit upper left corner to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					b_mapEl[3]->applyAlphaTrans(alpha);
					b_mapEl[3]->Blit(pos.x,pos.y);
					break;
					}
				case upper_right_corner:
					{ // upper right corner
                	//Debug::debug(Debug::gameEngine) <<" Map Will Blit upper right corner to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					b_mapEl[4]->applyAlphaTrans(alpha);
					b_mapEl[4]->Blit(pos.x,pos.y);
					break;
					}
				case lower_right_corner:
					{		// lower  right corner
                	//Debug::debug(Debug::gameEngine) <<" Map Will Blit lower  right corner to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					b_mapEl[5]->applyAlphaTrans(alpha);
					b_mapEl[5]->Blit(pos.x,pos.y);
					break;
					}
				case lower_left_corner:
					{		// lower left corner
					//Debug::debug(Debug::gameEngine) <<" Map Will Blit lower left corner to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					b_mapEl[6]->applyAlphaTrans(alpha);
					b_mapEl[6]->Blit(pos.x,pos.y);
					break;
					}
				case line:
					{
					//Debug::debug(Debug::gameEngine) <<" Map Will Blit line to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					if (linha==0 || linha == height-1 || (fieldMap.isUnwalkable(coluna-1,linha) && fieldMap.isUnwalkable(coluna+1,linha)))
					{// horizontal line
						b_mapEl[1]->applyAlphaTrans(alpha);
						b_mapEl[1]->Blit(pos.x,pos.y);
					 }else {	// vertical line

						b_mapElRot[1][0]->applyAlphaTrans(alpha);
						b_mapElRot[1][0]->Blit(pos.x,pos.y);
					}
					break;
					}
				case door:
					{
					//Debug::debug(Debug::gameEngine) <<" Map Will Blit door to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					if (fieldMap.isWalkable(coluna,linha-1) && fieldMap.isWalkable(coluna,linha+1))
					{//ghost door

						b_mapEl[2]->applyAlphaTrans(alpha);
						b_mapEl[2]->Blit(pos.x,pos.y);

					}else 	{	// vertical ghost door

						b_mapElRot[2][0]->applyAlphaTrans(alpha);
						b_mapElRot[2][0]->Blit(pos.x,pos.y);
					}
					break;
					}
				case left_t:
					{
					//Debug::debug(Debug::gameEngine) <<" Map Will Blit left t to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					if (fieldMap.isUnwalkable(coluna,linha-1) && fieldMap.isUnwalkable(coluna,linha+1))
					{ // left T

						b_mapEl[7]->applyAlphaTrans(alpha);
						b_mapEl[7]->Blit(pos.x,pos.y);
					}
					else if (fieldMap.isUnwalkable(coluna-1,linha) && fieldMap.isUnwalkable(coluna+1,linha))
					{	// upside down T

						b_mapElRot[7][0]->applyAlphaTrans(alpha);
						b_mapElRot[7][0]->Blit(pos.x,pos.y);
					}
					break;
					}
				case right_t:
					{
					//Debug::debug(Debug::gameEngine) <<" Map Will Blit right t to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					if (fieldMap.isUnwalkable(coluna,linha-1) && fieldMap.isUnwalkable(coluna,linha+1))
					{ // right T

						b_mapEl[8]->applyAlphaTrans(alpha);
						b_mapEl[8]->Blit(pos.x,pos.y);
					}
					else if (fieldMap.isUnwalkable(coluna-1,linha) && fieldMap.isUnwalkable(coluna+1,linha))
					{	// upright  T

						b_mapElRot[8][0]->applyAlphaTrans(alpha);
						b_mapElRot[8][0]->Blit(pos.x,pos.y);
					}
					break;
					}
				case stub:
					{
					//Debug::debug(Debug::gameEngine) <<" Map Will Blit stub t to [ " << linha <<" , " <<coluna<<" ]: " <<  endl;
					if (fieldMap.getTyleType(coluna-1,linha)==line && fieldMap.isWalkable(coluna+1,linha))
					{//right stub

						b_mapEl[9]->applyAlphaTrans(alpha);
						b_mapEl[9]->Blit(pos.x,pos.y);
					}else if (fieldMap.getTyleType(coluna+1,linha)==line && fieldMap.isWalkable(coluna-1,linha))
					{	// left stub
               			b_mapElRot[9][1]->applyAlphaTrans(alpha);
						b_mapElRot[9][1]->Blit(pos.x,pos.y);
					}else if (fieldMap.getTyleType(coluna,linha+1)==line && fieldMap.isWalkable(coluna,linha-1))
					{	// upper stub
						b_mapElRot[9][0]->applyAlphaTrans(alpha);
						b_mapElRot[9][0]->Blit(pos.x,pos.y);
					}else if (fieldMap.getTyleType(coluna,linha-1)==line && fieldMap.isWalkable(coluna,linha+1))
					{// lower stub
						b_mapElRot[9][2]->applyAlphaTrans(alpha);
						b_mapElRot[9][2]->Blit(pos.x,pos.y);
					}
						break;
					}
			}


        }
    }

    //DRAW FOOD OBJECTS

    for (coluna=0;coluna<height;coluna++) {
        for (linha=0; linha<width; linha++) {

            pos.x=coluna*settings.tilesize+10; // +10 are needed for correct placement
            pos.y=linha*settings.tilesize+10;
            pos.h=20;
            pos.w=20;
			if (objMap.getTyleType(coluna,linha)==1)
           	{  //dots
                foodObj[1]->applyAlphaTrans(alpha);
				foodObj[1]->Blit(pos.x,pos.y);
                pacFoodCounter++;
            }
            if (objMap.getTyleType(coluna,linha)==2)

			{	// BIG DOTS!
                foodObj[2]->applyAlphaTrans(alpha);
				foodObj[2]->Blit(pos.x,pos.y);
                pacFoodCounter++;
            }
            if (objMap.getTyleType(coluna,linha)==3 && specialspawned && !specialeaten)

			{	// fruit
                foodObj[3]->applyAlphaTrans(alpha);
				foodObj[3]->Blit(pos.x,pos.y);
                pacFoodCounter++;
            }
        }
    }


}

bool BckgrObj::load() {
	Debug::debug(Debug::gameObject,__FUNCTION__) << "BEGIN" << endl;
	std::string path =  this->getObjectPath();
    int i;
    std::string num[NUMOFMAPTEX];


    for (i=0;i<NUMOFMAPTEX;i++)
        num[i]='0'+i;

    try {
        for (i=0;i<NUMOFMAPTEX;i++) {
            b_mapEl[i] = new CBitmap((path + "m" + num[i] + ".png").c_str());

			if (b_mapEl[i]->getError() )
                throw CGeneralError(num[i] + ": Failed to load map texture: "+(path + "m" + num[i] + ".png").c_str() + " - "+"CGeneralError: " + SDL_GetError() );
			else Debug::debug(Debug::gameObject,__FUNCTION__) << "Bitmap created: "<< num[i]<< " -> "<< (path + "m" + num[i] + ".png").c_str()<< endl;

            //set the transparent color key to RGB 255 0 255
            b_mapEl[i]->applyDefTrans();

            for (int j=0;j<3;j++) {
                Debug::debug(Debug::gameObject,__FUNCTION__) << "Criando Rotated Bitmaps" << endl;
				b_mapElRot[i][j] = new CBitmap(*b_mapEl[i],true);
				b_mapElRot[i][j]->applyDefTrans();
				b_mapElRot[i][j]->rotateFromBitmap((j+1)*90);


				Debug::debug(Debug::gameObject,__FUNCTION__) << "Rotated Bitmap created: texture:"<< b_mapElRot[i][j]->GetTexture()<< endl;
            }
        }
        for (i=1;i<5;i++) {
            foodObj[i] = new CBitmap((path + "o" + num[i] + ".png").c_str());
			if ( foodObj[i]->getError() )
                throw CGeneralError(num[i] + "Failed to load object texture");

           //set the transparent color key to RGB 255 0 255
            foodObj[i]->applyDefTrans();

        }

        logtxt.print("Field textures loaded");
    }
    catch ( CGeneralError &err) {
        std::cerr << err.getFullReason().c_str();
       game.getGameControl()->setQuit(true);
        logtxt.print( err.getFullReason() );
        return false;
    }
    catch ( ... ) {
        std::cerr << "Unexpected exception in BckgrObj::LoadTextures";
		game.getGameControl()->setQuit(true);
        logtxt.print( "Unexpected error during Game()" );
        return false;
    }
	Debug::debug(Debug::gameObject,__FUNCTION__) << "END" << endl;
    return true;
}

BckgrObj::BckgrObj( int os, std::string TexturesPath)
    : CBaseObject(os),
	pacFoodCounter(0),
    fruitalpha(255),
    specialspawned(false),
    specialeaten(false),
    alpha(255)

{
	this->setObjectPath(TexturesPath);
	int i;

    for (i=0;i<10;i++) {
        b_mapEl[i]=NULL;
        foodObj[i]=NULL;
        for (int j=0;j<3;j++)
            b_mapElRot[i][j]=NULL;
    }
	load();
}

BckgrObj::~BckgrObj()
{
    int i;
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " START DELETING BACKGRUND==========================" << endl;

    for (i=0;i<NUMOFMAPTEX;i++) {

        if ( b_mapEl[i] ) {
			Debug::debug(Debug::gameEngine,__FUNCTION__) << " DELETING MAPEL==========================" << endl;
			delete b_mapEl[i];
		}
        if ( foodObj[i] )  {
			Debug::debug(Debug::gameEngine,__FUNCTION__) << " DELETING FOODOBJ==========================" << endl;
			delete foodObj[i];
		}
        for (int j=0;j<3;j++)
            if ( b_mapElRot[i][j] ) {
				Debug::debug(Debug::gameEngine,__FUNCTION__) << " DELETING MAPELROT==========================" << endl;
				delete b_mapElRot[i][j];
			}
    }
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " END DELETING BACKGRUND==========================" << endl;

}
