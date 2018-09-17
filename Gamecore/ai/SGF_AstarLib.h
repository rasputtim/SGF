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



#ifndef _S_G_F_ASTARLIB_h
#define _S_G_F_ASTARLIB_h

#include "../SGF_Config.h"

using namespace std;
namespace SGF {
/**
 * \class CAStarData
 *
 * \ingroup SGF_AI_Map
 * 
 * \brief Esta Classe agrupa os dados necessários para rodar o algorítmo A*
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
class  SGE_API CAStarData{
public:
	CAStarData();
	CAStarData( const CAStarData & b );
	~CAStarData();
	// copy
	CAStarData &operator=( const CAStarData &);

	bool operator==(const CAStarData & who) const;
	bool operator==(unsigned int value) const;
	bool operator!=(unsigned int value) const;

	int getF() {return Fcost; } 
    int getX() {return openX; }
    int getY() {return openY; }
	void setF(unsigned int f) {Fcost=f; } 
	void setX(int x) {openX=x; }
    void setY(int y) {openY=y; }
	void reset() { Fcost=0;  openX=0; openY=0;}
	void remove() { Fcost=0; openX=0; openY=0;}

protected:
	unsigned int	Fcost;		//heap sorted by this
    int				openX;
    int				openY;

};
} //end namespace SGF
#endif
