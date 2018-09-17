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
#ifndef _S_G_F_MAP_LIB_h
#define _S_G_F_MAP_LIB_h

#include "../SGF_Config.h"
#include "../gui/SGF_Coordinate.h"
#include "../structures/SGF_DynamicArray.h"
#include <fstream>
#include <sstream>

using namespace ::std;
namespace SGF {
namespace Gui{
class CAbsolutePoint;
}
/**
 * \class CMap
 *
 * \ingroup SGF_AI_Map
 *
 * \brief Esta Classe Manipula Um Mapa de Tela
 *
 * \note O mapa está em Tiles e não em pixels
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CMap {
public:
    CMap():
    ClosedList(0),
    openedList(0),
    mapWidth(0),
    mapHeight(0),
	tyleSize(0),
	centralizedTyle(false) {}
	CMap(unsigned int width,unsigned int height);
	CMap(unsigned int width,unsigned int height, int tyleSize);
	~CMap();

	bool loadCharMap(string file);
	bool loadBinMap(string file);

    void resize(unsigned int width,unsigned int height);
    void walkable(unsigned int x,unsigned int y);
    void unwalkable(unsigned int x,unsigned int y);
	bool isUnwalkable(unsigned int x,unsigned int y);
	bool isWalkable(unsigned int x,unsigned int y);

	void onClosedList(unsigned int x,unsigned int y);  // coloca posição na lista fechada
	void onOpenList(unsigned int x,unsigned int y);  // coloca posição na lista aberta
	bool isOnClosedList(unsigned int x,unsigned int y) { return whichList[x][y] == ClosedList;};
	bool isOnOpenedList(unsigned int x,unsigned int y) { return whichList[x][y] == openedList;};

	void setGcost (unsigned int x,unsigned int y,unsigned int val);
	unsigned int getGcost(unsigned int x,unsigned int y);
    void setHcost (unsigned int x,unsigned int y,unsigned int val);
	unsigned int getHcost(unsigned int x,unsigned int y);

	Gui::CAbsolutePoint & getparentLocation(unsigned int x,unsigned int y);
	void reset();
	void clear(); //clear to initial state Gcost, etc;
    void addToClosedList(int value) { ClosedList+=value;};
	void addToOpenedList(int value) { openedList+=value;};

    int getTyleType(unsigned int x,unsigned int y) {if(isInsideMap(x,y)) return tyleType[x][y]; }
    void setTyleType(unsigned int x,unsigned int y, int val) {if(isInsideMap(x,y)) tyleType[x][y]=val;}

	void setTileSize(int size) { tyleSize=size;}
	int getTyleSize() { return tyleSize;}
	//! return true if the tyle control of pixel coordinates is to the center of the tyle
	bool isCentralizedTyle() const { return centralizedTyle; }
	void setCentralizedTyles() { centralizedTyle=true;}
	void setUncentralizedTyles() { centralizedTyle=false;}

	//! to work is pixel coordinates
	int getXpixel(const unsigned int x,const unsigned int y) const ;
	int getYpixel(const unsigned int x, const unsigned int y) const;
	Gui::CAbsolutePoint & getPixelPoint(const unsigned int x, const unsigned int y) const;

	__inline unsigned int getWidth() { return mapWidth;}
	__inline unsigned int getHeight() { return mapHeight;}

private:
	inline bool isInsideMap(const unsigned int x, const unsigned int y)const { if (x < mapWidth && x >=0 && y >=0 && y < mapHeight) return true;
	else return false; };
	unsigned int ClosedList,openedList;
    unsigned int mapWidth,mapHeight;
	CDynamic2DArray<bool> walkability;
    CDynamic2DArray<unsigned int> whichList;  //2 dimensional array used to record
	// 		whether a cell is on the open list or on the closed list.
	CDynamic2DArray<unsigned int> Gcost; //2d array to store G cost for each cell.  -1 == init state
	CDynamic2DArray<Gui::CAbsolutePoint> locationParent; //2d array to store parent of each cell (x,y)
    CDynamic2DArray<int> tyleType;  //tyletype is defined by the user
    int tyleSize;  //! to store the tyle sizo used to convert map coordinates to pixel coordinates
	bool centralizedTyle;  //! 1 => x,y pixel coordinates correspond to de center of the tyle
						   //! 0 => x,y pixel coordinates correspond to the position 0,0 of the type
    CDynamic2DArray<unsigned int> Hcost; //2d array to store G cost for each cell.  -1 == init state

};
} //end namespace SGF
#endif
