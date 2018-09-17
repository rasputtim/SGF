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
#include "math/SGF_Plane.h"
#include "util/SGF_StringUtils.h"


//#pragma hdrstop
namespace SGF {
CPlane plane_origin( 0.0f, 0.0f, 0.0f, 0.0f );

/*
================
CPlane::Type
================
*/
int CPlane::Type() const {
	if ( Normal()[0] == 0.0f ) {
		if ( Normal()[1] == 0.0f ) {
			return Normal()[2] > 0.0f ? PLANETYPE_Z : PLANETYPE_NEGZ;
		}
		else if ( Normal()[2] == 0.0f ) {
			return Normal()[1] > 0.0f ? PLANETYPE_Y : PLANETYPE_NEGY;
		}
		else {
			return PLANETYPE_ZEROX;
		}
	}
	else if ( Normal()[1] == 0.0f ) {
		if ( Normal()[2] == 0.0f ) {
			return Normal()[0] > 0.0f ? PLANETYPE_X : PLANETYPE_NEGX;
		}
		else {
			return PLANETYPE_ZEROY;
		}
	}
	else if ( Normal()[2] == 0.0f ) {
		return PLANETYPE_ZEROZ;
	}
	else {
		return PLANETYPE_NONAXIAL;
	}
}

/*
================
CPlane::HeightFit
================
*/
bool CPlane::HeightFit( const CVector3D *points, const int numPoints ) {
	int i;
	float sumXX = 0.0f, sumXY = 0.0f, sumXZ = 0.0f;
	float sumYY = 0.0f, sumYZ = 0.0f;
	CVector3D sum, average, dir;

	if ( numPoints == 1 ) {
		a = 0.0f;
		b = 0.0f;
		c = 1.0f;
		d = -points[0].z;
		return true;
	}
	if ( numPoints == 2 ) {
		dir = points[1] - points[0];
		Normal() = dir.Cross( CVector3D( 0, 0, 1 ) ).Cross( dir );
		Normalize();
		d = -( Normal() * points[0] );
		return true;
	}

	sum.Zero();
	for ( i = 0; i < numPoints; i++) {
		sum += points[i];
	}
	average = sum / numPoints;

	for ( i = 0; i < numPoints; i++ ) {
		dir = points[i] - average;
		sumXX += dir.x * dir.x;
		sumXY += dir.x * dir.y;
		sumXZ += dir.x * dir.z;
		sumYY += dir.y * dir.y;
		sumYZ += dir.y * dir.z;
	}

	CMatriz2D m( sumXX, sumXY, sumXY, sumYY );
	if ( !m.InverseSelf() ) {
		return false;
	}

	a = - sumXZ * m[0][0] - sumYZ * m[0][1];
	b = - sumXZ * m[1][0] - sumYZ * m[1][1];
	c = 1.0f;
	Normalize();
	d = -( a * average.x + b * average.y + c * average.z );
	return true;
}

/*
================
CPlane::PlaneIntersection
================
*/
bool CPlane::PlaneIntersection( const CPlane &plane, CVector3D &start, CVector3D &dir ) const {
	double n00, n01, n11, det, invDet, f0, f1;

	n00 = Normal().LengthSqr();
	n01 = Normal() * plane.Normal();
	n11 = plane.Normal().LengthSqr();
	det = n00 * n11 - n01 * n01;

	if ( CMath::Fabs(det) < 1e-6f ) {
		return false;
	}

	invDet = 1.0f / det;
	f0 = ( n01 * plane.d - n11 * d ) * invDet;
	f1 = ( n01 * d - n00 * plane.d ) * invDet;

	dir = Normal().Cross( plane.Normal() );
	start = f0 * Normal() + f1 * plane.Normal();
	return true;
}

/*
=============
CPlane::ToString
=============
*/
const char *CPlane::ToString( int precision ) const {
	return CMyString::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}

} //end SGF