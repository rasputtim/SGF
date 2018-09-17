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


#ifndef _S_G_F_ASTARHEAP_h
#define _S_G_F_ASTARHEAP_h


// http://www.policyalmanac.org/games/binaryHeaps.htm
//
// BINARY HEAP class by Rasputtim
//
//
//   Árvore Binária de Busca
//

/* Heap implementado em  array
If node x is in location i
left_child(x) -------------> 2 i
right_child(x) -----------> 2i + 1
parent(x) ----------------> [i / 2]
root----------------------> [1]
*/

#include "../SGF_Config.h"
#include "SGF_AstarLib.h"

using namespace std;
namespace SGF {
class CAStarData;
/**
 * \class CAstarHeap
 *
 * \ingroup SGF_AI_Map
 * 
 * \brief Esta Classe implementa um Heap Binário 
 *
 * \note Usar apenas no algoritmo AStar
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
  */
class SGE_API CAstarHeap
{
	
private:

	CAStarData
            *aStarData;
    int
 		  size,
            newOpenListItemID,
            numberOfOpenListItems;
public:
    CAstarHeap(int width, int height);
    ~CAstarHeap(void);

    void add(int x , int y, int f);
    void remove();
	
	int getopenListItemID() { return newOpenListItemID;}
	
	CAStarData getData() { return aStarData[1]; }
	int getF() {return aStarData[1].getF(); } // aStarData[1] é o primeiro elemento da lista, com o menor Fcost
	int getX() {return aStarData[1].getX(); }
    int getY() {return aStarData[1].getY(); }
	
    void reset();

    bool isEmpty();

    bool changeF(int pos, unsigned int newF);	//only works for newF < oldF; returns 0 on success, 1 on failure
    
    int find(int, int);	//returns position in openlist, if not found : 0
};

} //end namespace SGF
#endif
