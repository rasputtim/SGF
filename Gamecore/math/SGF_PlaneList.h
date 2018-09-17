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


#ifndef __SGF_PLANELIST_H__
#define __SGF_PLANELIST_H__
#include "../SGF_Config.h"
#include "../structures/SGF_List.h"
#include "SGF_Plane.h"
#include "../structures/SGF_HashTableFast.h"
namespace SGF {
	
/*
===============================================================================

	Plane List

===============================================================================
*/

class CPlaneList : public CList<CPlane> {
public:

	void					clear() { CList<CPlane>::clear(); m_hash.freeMem(); }

	int						findPlane( const CPlane &plane, const float normalEps, const float distEps );

private:
	CHashTableFast				m_hash;
};

SGF_INLINE_FORCED int CPlaneList::findPlane( const CPlane &plane, const float normalEps, const float distEps ) {
	int i, border, hashKey;

	assert( distEps <= 0.125f );

	hashKey = (int)( CMath::Fabs( plane.Dist() ) * 0.125f );
	for ( border = -1; border <= 1; border++ ) {
		for ( i = m_hash.getFirst( hashKey + border ); i >= 0; i = m_hash.getNext( i ) ) {
			if ( (*this)[i].Compare( plane, normalEps, distEps ) ) {
				return i;
			}
		}
	}

	if ( plane.Type() >= PLANETYPE_NEGX && plane.Type() < PLANETYPE_TRUEAXIAL ) {
		append( -plane );
		m_hash.Add( hashKey, getNum()-1 );
		append( plane );
		m_hash.Add( hashKey, getNum()-1 );
		return ( getNum() - 1 );
	}
	else {
		append( plane );
		m_hash.Add( hashKey, getNum()-1 );
		append( -plane );
		m_hash.Add( hashKey, getNum()-1 );
		return ( getNum() - 2 );
	}
}
} // end SGF
#endif /* !__SGF_PLANELIST_H__ */
