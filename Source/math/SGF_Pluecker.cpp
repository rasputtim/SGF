/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the freeMem Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the freeMem Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#include "math/SGF_Pluecker.h"
#include "math/SGF_Plane.h"
//#pragma hdrstop

namespace SGF {
CPluecker pluecker_origin( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );

/*
================
CPluecker::FromPlanes

  pluecker coordinate for the intersection of two planes
================
*/
bool CPluecker::FromPlanes( const CPlane &p1, const CPlane &p2 ) {

	p[0] = -( p1[2] * -p2[3] - p2[2] * -p1[3] );
	p[1] = -( p2[1] * -p1[3] - p1[1] * -p2[3] );
	p[2] = p1[1] * p2[2] - p2[1] * p1[2];

	p[3] = -( p1[0] * -p2[3] - p2[0] * -p1[3] );
	p[4] = p1[0] * p2[1] - p2[0] * p1[1];
	p[5] = p1[0] * p2[2] - p2[0] * p1[2];

	return ( p[2] != 0.0f || p[5] != 0.0f || p[4] != 0.0f );
}

/*
================
CPluecker::Distance3DSqr

  calculates square of shortest distance between the two
  3D lines represented by their pluecker coordinates
================
*/
float CPluecker::Distance3DSqr( const CPluecker &a ) const {
	float d, s;
	CVector3D dir;

	dir[0] = -a.p[5] *  p[4] -  a.p[4] * -p[5];
	dir[1] =  a.p[4] *  p[2] -  a.p[2] *  p[4];
	dir[2] =  a.p[2] * -p[5] - -a.p[5] *  p[2];
	if ( dir[0] == 0.0f && dir[1] == 0.0f && dir[2] == 0.0f ) {
		return -1.0f;	// FIXME: implement for parallel lines
	}
	d = a.p[4] * ( p[2]*dir[1] - -p[5]*dir[0]) +
		a.p[5] * ( p[2]*dir[2] -  p[4]*dir[0]) +
		a.p[2] * (-p[5]*dir[2] -  p[4]*dir[1]);
	s = PermutedInnerProduct( a ) / d;
	return ( dir * dir ) * ( s * s );
}

/*
=============
CPluecker::ToString
=============
*/
const char *CPluecker::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

} //ens SGF