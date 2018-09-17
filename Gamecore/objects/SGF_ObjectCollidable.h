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

#ifndef _S_G_F_object_collidable_h
#define _S_G_F_object_collidable_h

#include <string>
#include <vector>
#include "../SGF_Config.h"
#include "all.h"
#include "../SGF_Global.h"
#include "../util/all.h"

namespace SGF{

class CBaseObject;
class CECollide;

/**
 * \class CObjectAttack
 *
 * \ingroup SGF_Objects
 * 
 * \brief Classe para  Objetos que podem sofrer colisão com outros objetos
 *
 * \note rever esta classe. Talvez tornar ObjectAtack uma classe derivada desta
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CObjectCollidable : public CBaseObject {
public:
	CObjectCollidable( const int x, const int y);
	CObjectCollidable( const CObjectCollidable & obj );
	~CObjectCollidable();

	//TODO: set width and height
	/* getWidth:
	 * Returns the width of the object
	 */
	virtual int getWidth() const{return 0;};

	/* getHeight:
	 * Returns the height of the object
	 */
	virtual int getHeight() const{return 0;};

	/* getCollide
	 * Returns the ECollide object that encompasses this object
	 */
	virtual CECollide  *getCollide() const;
	void initColision(CBitmap *pic);
	bool collision( CObjectCollidable * obj );
		
	protected:
	string no_name;
	Util::CReferenceCount<CECollide> collide;
   

};
} //end SGF
#endif
