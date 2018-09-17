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


#include "ai/SGF_Map.h"


SGF::CMap::CMap(unsigned int width,unsigned int height):
ClosedList(10),
openedList(0),
mapWidth(width),
mapHeight(height),
tyleSize(0),
centralizedTyle(false)
{
	walkability.resize(width+1,height+1);
	whichList.resize(width+1,height+1);
	locationParent.resize(width+1,height+1);
	Gcost.resize(width+1,height+1);
	Hcost.resize(width+1,height+1);
	tyleType.resize(width+1,height+1);
	clear();
}

SGF::CMap::CMap(unsigned int width,unsigned int height, int tyleSize):
ClosedList(10),
openedList(0),
mapWidth(width),
mapHeight(height),
tyleSize(tyleSize),
centralizedTyle(false)
{
	walkability.resize(width,height);
	whichList.resize(width+1,height+1);
	locationParent.resize(width+1,height+1);
	Gcost.resize(width+1,height+1);
	Hcost.resize(width+1,height+1);
	tyleType.resize(width,height);
	clear();
}

void SGF::CMap::resize(unsigned int width,unsigned int height)
{
	ClosedList=10;
	openedList=0;
	mapWidth=width;
	mapHeight=height;
	walkability.resize(width,height);
	whichList.resize(width+1,height+1);
	locationParent.resize(width+1,height+1);
	Gcost.resize(width+1,height+1);
	Hcost.resize(width+1,height+1);
	tyleType.resize(width,height);
	clear();
}
void SGF::CMap::walkable(unsigned int x,unsigned int y){
	if(isInsideMap(x,y) ) {
		Debug::debug(Debug::gameEngine,__FUNCTION__) << " Seting walkability" <<endl;
	walkability[x][y]=true;
	}
}
void SGF::CMap::unwalkable(unsigned int x,unsigned int y){
	 if(isInsideMap(x,y)) {
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " Seting unWalkability" <<endl;
	walkability[x][y]=false;
	 }
}

bool SGF::CMap::isUnwalkable(unsigned int x,unsigned int y){
	if(isInsideMap(x,y)) 	return !walkability[x][y];
}
bool SGF::CMap::isWalkable(unsigned int x,unsigned int y){
     if(isInsideMap(x,y)) return walkability[x][y];
}

void SGF::CMap::onClosedList(unsigned int x,unsigned int y){
	if(isInsideMap(x,y)) whichList[x][y]=ClosedList;
}

void SGF::CMap::onOpenList(unsigned int x,unsigned int y){
	if(isInsideMap(x,y)) whichList[x][y]=openedList;
}

void SGF::CMap::setGcost (unsigned int x,unsigned int y,unsigned int val) {
	if(isInsideMap(x,y)) Gcost[x][y]=val;
}
unsigned int SGF::CMap::getGcost(unsigned int x,unsigned int y){
	if(isInsideMap(x,y)) return Gcost[x][y];
}
void SGF::CMap::setHcost (unsigned int x,unsigned int y,unsigned int val) {
	if(isInsideMap(x,y)) Hcost[x][y]=val;
}
unsigned int SGF::CMap::getHcost(unsigned int x,unsigned int y){
	if(isInsideMap(x,y)) return Hcost[x][y];
}
SGF::Gui::CAbsolutePoint & SGF::CMap::getparentLocation(unsigned int x,unsigned int y){
	if(isInsideMap(x,y)) return locationParent[x][y];
}

void SGF::CMap::clear() {
	for (unsigned int x = 0; x < mapWidth;x++) {
			for (unsigned int y = 0; y < mapHeight;y++)
				this->setGcost(x,y,-1);
		}
}
void SGF::CMap::reset() {


if (ClosedList > 1000000) //reset whichList occasionally
	{
	for (unsigned int x = 0; x < mapWidth;x++) {
			for (unsigned int y = 0; y < mapHeight;y++)
				onOpenList(x,y);
		}
		ClosedList = 10;
		openedList=0;
	}
}

SGF::CMap::~CMap()
{

}

bool SGF::CMap::loadCharMap(string file){
	Debug::debug(Debug::gameEngine,__FUNCTION__) << " LOADING MAP" <<endl;

    //int x,y;
	string tmp;
    char val('i');
    ifstream filein;

    filein.open( file.c_str() );

    if (!filein ) {
        //logtxt.print(file + " - Loading error");
        return false;
    }
	for (unsigned int x = 0; x <mapWidth; x++){  // linha
			for (unsigned int y = 0; y <mapHeight; y++){  //coluna

			filein >> val;
			if (val == '/' ) {	// enable comments in map file by prefixing line with  a slash
                getline(filein, tmp);
				y--;
            }else {
			if (val=='0') {
				walkable(y,x);
			}else {
				unwalkable(y,x);
			}
			Debug::debug(Debug::gameEngine) <<" Map Read Value [ " << y <<" , " <<x<<" ]: " << val-48 << endl;
			setTyleType(y,x,val-48);
			}
		}}

/*    if (count != size) {
        logtxt.print(file + " - Loading error");
        gameControl->setQuit(true);
        return false;
    }
	*/
    //logtxt.print(file + " loaded");
    return true;

}
bool SGF::CMap::loadBinMap(string file){
ifstream filein;
	filein.open(file.c_str(),ios::in);
	if(!filein) {
	// file in não existe
	}else {
		//foile in existe
	filein.close();
	filein.open(file.c_str(),ios::out);
	if (filein)
	{
		char val;
		for (unsigned int x = 0; x <mapWidth; x++){
			for (unsigned int y = 0; y <mapHeight; y++){

			filein >> val;
			if (val==0 || val >1 ) {
				walkable(x,y);
			}
			if (val==1 ) {
				unwalkable(x,y);
			}

		}}
		filein.close();
	}
	else //initialize the map to completely walkable
	{
		for (unsigned int x = 0; x < mapWidth; x++){
			for (unsigned int y = 0; y < mapHeight; y++){
				walkable(x,y);

		}}
	}

	}
	return true;
}


int SGF::CMap::getXpixel(const unsigned int x,const unsigned int y) const {
	if (isInsideMap(x,y) && tyleSize >0) {
		if(! isCentralizedTyle()) {
			return x * tyleSize;
		}else return ((x* tyleSize) + (tyleSize/2));
	}else {
		//Todo: throw error outside the map or tileSize nbot initialized
	}

}
int SGF::CMap::getYpixel(const unsigned int x, const unsigned int y) const{
	if (isInsideMap(x,y) && tyleSize >0) {
		if(! isCentralizedTyle()) {
			return y * tyleSize;
		}else return ((y* tyleSize) + (tyleSize/2));
	}else {
		//Todo: throw error outside the map or tileSize nbot initialized
	}
}
SGF::Gui::CAbsolutePoint & SGF::CMap::getPixelPoint(const unsigned int x, const unsigned int y) const{
Gui::CAbsolutePoint ponto;
	if (isInsideMap(x,y) && tyleSize >0) {
		if(! isCentralizedTyle()) {
		    ponto = Gui::CAbsolutePoint(x * tyleSize,y*tyleSize);
			return ponto; //Gui::CAbsolutePoint(x * tyleSize,y*tyleSize);
		}else {

		    ponto =Gui::CAbsolutePoint(((x* tyleSize) + (tyleSize/2)),((y* tyleSize) + (tyleSize/2)));
		    return ponto;
		}
	}else {
		//Todo: throw error outside the map or tileSize nbot initialized
	}

}

