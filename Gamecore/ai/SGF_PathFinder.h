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
#ifndef _S_G_F_PATH_FINDER_h
#define _S_G_F_PATH_FINDER_h

#include "../SGF_Config.h"
#include "SGF_AstarLib.h"
#include "../gui/SGF_Coordinate.h"
#include "SGF_Map.h"
#include "SGF_AstarHeap.h"
namespace SGF {
class CMap;
class CAstarHeap;
/**
 * \class CPathFinder
 *
 * \ingroup SGF_AI_Map
 *
 * \brief Esta Classe Encontra Caminhos dentro de um mapa específico
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
class  SGE_API CPathFinder{

public:
	typedef enum status{
		notStarted,
		notFinished=notStarted,
		found,
		nonExistent
	}Status;
	enum path{
		walkable,
		unwalkable
	};
	CPathFinder(CMap &ourMap);
	~CPathFinder();

	void readPath(Gui::CAbsolutePoint currentPosition, int pixelsPerFrame);
	int readPathX(int pathPosition);
	int readPathY(int pathPosition);
	int findPath (Gui::CAbsolutePoint startlocation, Gui::CAbsolutePoint targetLocation); //! Desc: Finds a path using A*
	int getStatus() { return pathStatus;}
	void generateStatus(Gui::CAbsolutePoint origem, Gui::CAbsolutePoint destino) { pathStatus=(Status)findPath(origem,destino) ;};
	int getPosition() {return pathPosition;}
	int getPathLenght() { return pathLength; };
	Gui::CAbsolutePoint locationPath;
private:
	//Path reading variables
	int pathLength;     //stores length of the found path for critter
	int pathPosition;   //stores current position along the chosen path for critter
	int* pathBank;
	Status pathStatus;
	CMap &ourMap;
	CAstarHeap *heap;

};
}//end namespace SGF
#endif
